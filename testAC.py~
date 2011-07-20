import commands
import time

def testAudioCompression():
	regularTime = 0
	reverseTime = 0
	binTime = 0
	for i in range(0, 255):
		regularTime += float(commands.getstatusoutput('./audioCompression.o '+str(i))[1])
		reverseTime += float(commands.getstatusoutput('./audioCompression.o '+str(i)+' reverse')[1])
		binTime += float(commands.getstatusoutput('./audioCompression.o '+str(i)+' reverse'+' binsearch')[1])


	print 'regular: '+str(regularTime)
	print 'reverse: '+str(reverseTime)
	print 'binary: '+str(binTime)

def getStats(regularTimes, reverseTimes, binTimes):
	bin = 0
	reg = 0
	rev = 0
	for time in binTimes:
		print time
	print 'binary: '+bin
	for time in regularTimes:
		print time
	print 'regular: '+reg
	for time in reverseTimes:
		print time
	print 'reverse: '+rev
	

if __name__ == "__main__":
    testAudioCompression()
