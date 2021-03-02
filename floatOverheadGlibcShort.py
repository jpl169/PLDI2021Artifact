import matplotlib
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

matplotlib.rcParams['pdf.fonttype'] = 42
matplotlib.rcParams['ps.fonttype'] = 42

overallLabel = ["ln", "log2", "log10", "exp", "exp2", "exp10", "sinh", "cosh", "avg."]

labels = overallLabel
# Here we have to set up the values
againstFloat = []
againstDouble = []

fileName = ["Log_FG_Result.txt", "Log2_FG_Result.txt", "Log10_FG_Result.txt", "Exp_FG_Result.txt", "Exp2_FG_Result.txt", "Exp10_FG_Result.txt", "Sinh_FG_Result.txt", "Cosh_FG_Result.txt"]

for i in range(0, 8) :
    fp = open("overheadtest/float/glibc/" + fileName[i], "r")
    line = fp.readline()
    line = line.split(",")
    againstFloat.append(float(line[0]))
    againstDouble.append(float(line[1]))

# Calculate averages:
afCount = len(againstFloat)
afSum = sum(againstFloat)
againstFloat.append(afSum / afCount)

adCount = len(againstDouble)
adSum = sum(againstDouble)
againstDouble.append(adSum / adCount)

x = np.arange(len(labels))  # the label locations
width = 0.35  # the width of the bars

fig, ax = plt.subplots()
ax.set_ylim(0, 2.5)
ax.axhline(0.5, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
ax.axhline(1, color="k", ls = '--', linewidth = 1, zorder = 0)
ax.axhline(1.5, color="gray", ls = '--', linewidth = 0.5, zorder = 0)
ax.axhline(2.0, color="k", ls = '--', linewidth = 1, zorder = 0)
rects1 = ax.bar(x - width/2, againstFloat, width, color="tab:orange", label='Speedup over float libm', zorder = 100)
rects2 = ax.bar(x + width/2, againstDouble, width, color="tab:blue", label='Speedup over double libm', zorder = 100)

# Add some text for labels, title and custom x-axis tick labels, etc.
#plt.xticks(rotation=15, ha="right", rotation_mode="anchor")
ax.set_ylabel('Speedup')
#ax.set_title('Performance speedup')
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend(bbox_to_anchor=(-0.1, 0.98, 1.1, 0.2), loc="lower left", mode="expand", ncol=2)
ax.yaxis.set_major_formatter(ticker.FormatStrFormatter('$%.f x$'))

fig.tight_layout()

plt.gcf().set_size_inches(5, 1.2)
plt.savefig('floatAgainstGlibcShort.pdf', bbox_inches='tight', pad_inches = -0.001)
