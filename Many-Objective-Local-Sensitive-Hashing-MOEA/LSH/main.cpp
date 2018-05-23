#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>



using namespace std;
#define prime (1 << 32 - 5) //This is a prime value used in the function hashes...
class LSH
{
   public:
      LSH(vector< vector< double > >  &Points, int number_hash_families, int size_hash_familiy, double len_bucket, int dimension, int map_size );
      void updateHashTable(vector<double> &point, int &indexPoint);
      vector<int> searchNearestsPoints(vector<double> &point);
   private:
       int dimension, size_hash_familiy, number_hash_families, len_bucket, map_size; 
       vector<vector<vector<double> > > p_stable_distribution_a; //The p-Stable distribution with dimensions.... L*K*d -
       vector<vector<double> > uniform_vector_b; //It is to calculate the projection
       vector<vector<int> > uniform_vector_hash;
       unordered_map<int, unordered_map<int, vector<int> > > lsh_location_hash_map;
	
       int HashKey1(vector<int> &Ids_map_familiy_hash, int hash_index);
       int HashKey2(vector<int> &Ids_map_familiy_hash, int hash_index);
       void generateRandomVectors();
       int callHashFamilies(vector<double> &point, vector<int> &Ids_map_family_hashes,int &index_gi_function);
};

vector<int> LSH::searchNearestsPoints(vector<double> &point)
{
  //This is the index of indexes that are inside the buckest or nearest points...
     vector<int> index_list;

  for(int i = 0; i < number_hash_families; i++){

      vector<int> Ids_map_family_hashes(size_hash_familiy);
     //get all the hash values form the g_i family...
      callHashFamilies(point, Ids_map_family_hashes, i); 

     //This section could change, maybe a different hash technique is better....
     //get the first hash transformation from this family hash
      int index_hash1 = HashKey1(Ids_map_family_hashes, i);
     //get the second hash transformation from this family hash
      int index_hash2 = HashKey2(Ids_map_family_hashes, i);
     // lsh_location_hash_map[index_hash1][index_hash2].push_back(indexPoint); //here a list structure instead of vector could work better...

      vector<int>::iterator it = lsh_location_hash_map[index_hash1][index_hash2].begin();
     
      for(int cont = 0 ; it != lsh_location_hash_map[index_hash1][index_hash2].end() && cont < number_hash_families*3; it++, cont++)
	{
         index_list.push_back(*it);
	}
  }

  sort(index_list.begin(), index_list.end());
  index_list.erase(unique(index_list.begin(), index_list.end()), index_list.end());

  return index_list;
}
int LSH::callHashFamilies(vector<double> &point, vector<int> &Ids_map_family_hashes,int &index_gi_function)
{
   for(int j = 0; j < this->size_hash_familiy; j++)
   {
	   double dot_product = 0;
	   for(int d = 0 ; d < this->dimension; d++)
	     dot_product += (p_stable_distribution_a[index_gi_function][j][d] * point[d]); 
	  Ids_map_family_hashes[j]   =  (int)((dot_product+uniform_vector_b[index_gi_function][j]) / (double)this->len_bucket);
   }
}
int LSH::HashKey1(vector<int> &Ids_map_family_hash, int hash_index)
{
  int result = 0;
  for(int m = 0; m < size_hash_familiy; m++)
    result += Ids_map_family_hash[m] * uniform_vector_hash[hash_index * 2][m]; 

  return ((result % prime) % map_size);
}
int LSH::HashKey2(vector<int> &Ids_map_family_hash, int hash_index)
{
  int result = 0;
  for(int m = 0; m < size_hash_familiy; m++)
    result += Ids_map_family_hash[m] * uniform_vector_hash[hash_index * 2 + 1][m];

  return (result % prime);
}
//Add a specific point in the detemined point or feature...
void LSH::updateHashTable(vector<double> &point, int &indexPoint)
{
   for(int i = 0; i < number_hash_families; i++)
   {
      vector<int> Ids_map_family_hashes(size_hash_familiy);
     //get all the hash values form the g_i family...
      callHashFamilies(point, Ids_map_family_hashes, i); 

     //This section could change, maybe a different hash technique is better....
     //get the first hash transformation from this family hash
      int index_hash1 = HashKey1(Ids_map_family_hashes, i);
     //get the second hash transformation from this family hash
      int index_hash2 = HashKey2(Ids_map_family_hashes, i);
      lsh_location_hash_map[index_hash1][index_hash2].push_back(indexPoint); //here a list structure instead of vector could work better...
   }
}
//Generate the normal vectors and the uniform points of each hash function....
void LSH::generateRandomVectors()
{
   p_stable_distribution_a.resize(number_hash_families);
   uniform_vector_b.resize(number_hash_families);
   for(int i = 0; i < number_hash_families; i++)
   {
	p_stable_distribution_a[i].resize(size_hash_familiy);
      for(int j = 0; j < size_hash_familiy; j++)
      {
	   random_device rd;
	   mt19937 gen(rd()); //Spetial uniform generator....
	  // uniform_int_distribution<int> rd_int(0, len_bucket); //This should be a continuous distribution...
	   uniform_real_distribution<double> rd_int(0, len_bucket); //This should be a continuous distribution...
	   normal_distribution<double> distribution(0.0, 1.0); //Alternatively could work the box-muller method...
	   vector<double> a;
  	   for(int d = 0 ; d< dimension; d++) p_stable_distribution_a[i][j].push_back(distribution(gen));
	   uniform_vector_b[i].push_back(rd_int(gen));
      }
   }
   //Its transforms each id from the family in two hash maps
   for(int i = 0; i < 2*number_hash_families; i++)
   {
      random_device rd;
      mt19937 gen(rd());
      uniform_int_distribution<int> rd_int(0, dimension);
      vector<int> ui (size_hash_familiy);
      for(int i = 0; i < size_hash_familiy; i++)
         ui[i] = rd_int(gen);

       uniform_vector_hash.push_back(ui);
   }
}


LSH::LSH(vector< vector< double > >  &Points, int number_hash_families, int size_hash_familiy, double len_bucket, int dimension, int map_size )
{
   this->number_hash_families = number_hash_families;	
   this->size_hash_familiy = size_hash_familiy;
   this->len_bucket = len_bucket;
   this->dimension = dimension;
   this->map_size = map_size;
   generateRandomVectors();
}



///int LSH::GenerateHashFunction(int L, int K, vector<double> &Point)
///{
///
///   int sum = 0 , p = 0, r, w = 4;
///   double res , v;
///   float t;
///   long long M = pow(2.0,32) - 5;
///
///   vector<int> h(k)
///   srand(time(NULL));    
///   for(int i = 0; i  < k; i++)
///   {
///      int n = 0;
///      t = float (rand() / (RAND_MAX + 1.0)) * ( w + 1);
///      v = marsagliarandom(i);
///        
///      for (int j = 0; j < Point.size(); j++)
///      {
///         res += Point[j]*v;        //inner product           
///      }
///      h[i] = int((res + t) / w);
///   }
///   for (int i = 0; i < k; i++)
///    {   
///        r = (rand() / (RAND_MAX + 1.0)) * ( (pow(2.0,31)-1) + 1);       
///        sum = mod((h[i] * r), M) + sum;        //(a+b)modm = ((amodm)+(bmodm))modm
///    }
///    
///    ID = mod(sum, M);
///
///    return mod(ID, L);     //mod
///}

int main()
{
   int d = 24,N=100;
   vector< vector< double> > Points(N);
	random_device rd;
	  mt19937 gen(rd()); //Spetial uniform generator....
	   uniform_real_distribution<double> rd_int(0, 2); //This should be a continuous distribution...

   for(int i = 0; i < N; i++)
   {

	for(int j =0 ; j < d; j++)
     Points[i].push_back(  (double)j/d + 1.0 );// rd_int(gen) );
   }
//	Points[1][0] = 1000;
//	Points[1][1] = 10;

//LSH::LSH(vector< vector< double > >  &Points, int number_hash_families, int size_hash_familiy, double len_bucket, int dimension, int map_size )
   LSH obj(Points, log(N), 2, 100, d, 5435); 
for(int i = 0; i < N; i++)
   {
    obj.updateHashTable(Points[i], i);
   }
	for(int j =0 ; j < d; j++)
   		Points[30][j] +=1.0;
   vector<int>ind = obj.searchNearestsPoints(Points[30]);
  
   for(int i =  0 ; i < ind.size(); i++)
    cout << ind[i] << endl; 
 //  LSH(vector< vector< double > >  &Points, int number_hash_families, int size_hash_familiy, double len_bucket, int dimension, int map_size );
 //     void updateHashTable(vector<double> &point, int &indexPoint);
 //     vector<int> searchNearestsPoints(vector<double> &point); 



   //In the parameters should be the bucket-size, number_functions(g)- l , hash-family-size (k)
//   LSH obj();
//   //Update LSH
//   obj.updateHashTable();
   //Query LSH
   //Search the most neares points...
   //obj.searchNearestPoints()

//   obj.Build_Hash();


   
   return 0;
}
