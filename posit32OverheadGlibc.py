# Here we have to set up the values
againstDouble = []

fileName = ["Log_PG_Result.txt", "Log2_PG_Result.txt", "Log10_PG_Result.txt"]

for i in range(0, 8) :
    fp = open("overheadtest/posit32/glibc/" + fileName[i], "r")
    line = fp.readline()
    againstDouble.append(float(line))

# Calculate averages:
afCount = len(againstDouble)
afSum = sum(againstDouble)
spdOverhead = afSum / afCount

print("PWLibm Speedup vs Glibc double: " + str(spdOverhead))
