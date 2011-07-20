import commands
import time
import math

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
	
def log2(x):
	return math.log( x ) / math.log( 2 )


def calcErrors():
	
	differences = []
	maxVal = 0
	minVal = 0
	maxIndex = -1
	minIndex = -1
	avrError = 0
	for i in range(0, 9):
		approx = float(commands.getstatusoutput('./audioCompression.o '+str(i)+ ' calc approx error')[1])
		print approx		
		actual = log2(i)
		
		if(approx != actual):
			difference = math.fabs(((approx - actual)/actual)*100)
			differences.append([difference, i])
			#print str(difference)+'\t'+str(i)
			
	'''
	Find the worst estimate and best as well as the avrError
	'''
	for i in range(0, len(differences)):
		if (differences[i][0] > maxVal):
			maxVal = differences[i][0]
			maxIndex = differences[i][1]
		if (differences[i][0] < maxVal):
			minVal = differences[i][0]
			minIndex = differences[i][1]
		avrError += differences[i][0]
	avrError = avrError/len(differences)

	
	
	'''
	print '=====================================\n\t\tSTATS\n====================================='
	print 'Number of exact values: '+str(256 - len(differences))
	print 'Worst Estimate: '+str(maxVal)+'% off for value '+str(maxIndex)
	print 'Best non-exact Estimate '+str(minVal)+'% off for value '+str(minIndex)
	print 'Avr Estimate error: '+str(avrError)
	print '====================================='
	'''

if __name__ == "__main__":
    #testAudioCompression()
    calcErrors()
