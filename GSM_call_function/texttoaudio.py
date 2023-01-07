from gtts import gTTS
from io import BytesIO
import pygame
import time
 
def speak(text, language='en'):
    mp3_fo = BytesIO()
    tts = gTTS(text, lang=language)
    tts.write_to_fp(mp3_fo)
    return mp3_fo
pygame.init()
pygame.mixer.init()
sound = speak("Hi, Karthi, thanks for applying Internship at krishtec. This is a bot speaking here, not a real human!")
pygame.mixer.music.load(sound, 'mp3')
pygame.mixer.music.play()
while(pygame.mixer.music.get_busy()):
    print("playing....")
time.sleep(5)