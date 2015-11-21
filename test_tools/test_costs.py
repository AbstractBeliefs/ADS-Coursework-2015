import glob, subprocess
files = glob.glob("data/*prob.csv")

for f in files:
    print "Testing %s" %f
    p = subprocess.Popen(
        ["./CourseWork1", f, f+"solution.csv"],
        stdout=subprocess.PIPE
    )
    print p.communicate()[0]
    p = subprocess.Popen(
        ["java", "-jar", "Verify.jar", f, f+"solution.csv"],
        stdout=subprocess.PIPE
    )
    print p.communicate()[0]
    s = raw_input()

