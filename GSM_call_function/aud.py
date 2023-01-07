from gtts import gTTS
import os
import playsound
mytext = "Hi, Vimal, thanks for applying Internship at krishtec. This is a bot speaking here, not a real human!"
audio = gTTS(text=mytext, lang="en", slow=False)
audio.save("example.mp3")
playsound.playsound("example.mp3")
#os.system("start example.mp3")