f = open ("aplusbb.in")
a,b = map(int, f.readline().split())
f2 = open ("aplusbb.out","w")
print((a+(b*b)), file=f2)
f2.close()

