from bs4 import BeautifulSoup
import urllib
###mechanize!!!...

strpic = 'https://www.facebook.com/ferga97?hc_ref=ARTgjnpLyJqiL54Te8QRQ9_30nJA1mAhZ5wmaClNkVwJs2ulAxMKTCvBjOitfH1eGUU&fref=nf'
strpic = 'https://www.facebook.com/photo.php?fbid=10153351227769836&set=a.444641839835&type=3&theater'
strpic = 'https://www.facebook.com/photo.php?fbid=818754151508916&set=a.122901464427525&type=3&theater'
urlData = urllib.urlopen(strpic)
data = str(urlData.readlines())
bs = BeautifulSoup(data)
imgUrl = bs.find('img', attrs={'class': 'scaledImageFitWidth img'}).get('src')
#imgUrl = bs.find('img', attrs={'class': 'fbPhotoImage img'}).get('src')
urllib.urlretrieve(imgUrl, "plane.jpg")
