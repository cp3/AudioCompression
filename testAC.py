import commands
import time

def testAudioCompression():
	regularTimes = []
	reverseTimes = []
	for i in range(2, 255):
		regularTime = commands.getstatusoutput('./audioCompression.o '+str(i))
		reverseTime = commands.getstatusoutput('./audioCompression.o '+str(i)+' reverse')
		regularTimes.append(regularTime);
		reverseTimes.append(reverseTime);

	getStats(regularTimes, reverseTimes)

def getStats(regularTimes, reverseTimes):
	
	

if __name__ == "__main__":
    testAudioCompression()
