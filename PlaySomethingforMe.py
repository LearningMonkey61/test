import argparse
import requests
import random
import time
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from bs4 import BeautifulSoup

## css =  span[class="style-scope yt-formatted-string"]
## songlist = open('songlist.txt','r+')

chromeOptions = Options()
chromeOptions.add_experimental_option("detach",True)

parser = argparse.ArgumentParser(description="Plays Good Music for you ")
group = parser.add_mutually_exclusive_group()
group.add_argument('-p','--please',action='store_true',help='The Magic Word')
group.add_argument('-s','--sing',type=str,default="Do I Wanna Know",help='Play the song specified')
group.add_argument('-l','--list',action='store_true',help='Play a song from the collected song Library')
parser.add_argument('-S','--savelist',action='store_true',help='Save Scrapped Songs into a List')
args = parser.parse_args()

NMEURL = "https://www.nme.com/list/150-best-tracks-of-the-past-15-years-1257"

def SongParserNME():
    page = requests.get(NMEURL)
    soup = BeautifulSoup(page.text,'html.parser')
    topTracks = soup.find_all('h2')
    i = random.randint(0,149)
    SearchQuery = topTracks[i].get_text()
    SearchQuery = SearchQuery.split()
    SearchQuery.pop(0)
    s = '+'
    s = s.join(SearchQuery)
    return s

def PlaySong():
    
    URL = "https://music.youtube.com/search"
    driver = webdriver.Chrome(options=chromeOptions)
    
    if args.please:
        songName = SongParserNME()
    elif args.list:
        songName = "to+be+decided"
    elif args.sing:
        songName = '+'
        songName = songName.join(args.sing.split())
    
    
    URL = URL + "?q=" + songName

    driver.get(URL)
    play = driver.find_element_by_class_name("style-scope ytmusic-play-button-renderer")
    play.click()
    if args.savelist:
        time.sleep(10)
        song = driver.find_elements_by_css_selector('span#style-scope yt-formatted-string')
        ## song = driver.find_elements_by_class_name("style-scope yt-formatted-string")
        for s in song:
            print(s.text)
        
if __name__ == "__main__":
    PlaySong()
