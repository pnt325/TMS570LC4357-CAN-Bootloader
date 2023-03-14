from datetime import datetime

now = datetime.now()
dtime_txt = now.strftime("%x")

filename = input("Enter file name:")
fileinfo = input("Enter file info:")

# Replace space by underline
filename = filename.replace(" ", "_")
print("File name:", filename)

sfile = open("tfile.txtc", "r")
hfile = open("tfile.txth", "r")

sfile_txt = sfile.read()
hfile_txt = hfile.read()

sfile.close()
hfile.close()

sfile_txt = sfile_txt.replace("<fname>", filename)
sfile_txt = sfile_txt.replace("<datetime>", dtime_txt)
sfile_txt = sfile_txt.replace("<finfo>", fileinfo + " Source")
hfile_txt = hfile_txt.replace("<datetime>", dtime_txt)
hfile_txt = hfile_txt.replace("<finfo>", fileinfo + " Header")
hfile_txt = hfile_txt.replace("<fname>", filename)
hfile_txt = hfile_txt.replace("<FNAME>", filename.upper())

print(sfile_txt)
print(hfile_txt)

# Create file
fh = open(filename + ".h", "x")
fs = open(filename + ".c", "x")

fs.write(sfile_txt)
fh.write(hfile_txt)

fh.close()
fs.close()

