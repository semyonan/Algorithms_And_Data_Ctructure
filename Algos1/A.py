f = open ("aplusb.in")
a,b = map(int, f.readline().split())
f2 = open ("aplusb.out","w")
print(a+b, file=f2)
f2.close()

