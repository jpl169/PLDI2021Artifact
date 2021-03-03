# Here we have to set up the values
againstDouble = []

fileName = ["Log_PI_Result.txt", "Log2_PI_Result.txt", "Log10_PI_Result.txt"]

for i in range(0, 3) :
    fp = open("overheadtestShort/posit32/intel/" + fileName[i], "r")
    line = fp.readline()
    againstDouble.append(float(line))

# Calculate averages:
afCount = len(againstDouble)
afSum = sum(againstDouble)
spdOverhead = afSum / afCount

print("PWLibm Speedup vs Intel double: " + str(spdOverhead))
