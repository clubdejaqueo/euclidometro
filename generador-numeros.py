numeros = """
 000   1 222 333 4 4 555 666 777 888 999
 0 0   1   2   3 4 4 5   6     7 8 8 9 9
 0 0   1 222 333 444 555 666   7 888 999
 0 0   1 2     3   4   5 6 6   7 8 8   9
 000   1 222 333   4 555 666   7 888   9
"""

print """const byte PROGMEM numeros[] = {"""

lineas = [l for l in numeros.split("\n") if l.strip()]

for n in range(65):
    d, u = divmod(n, 10)
    print " ",
    for l in lineas:
        linea = l[d*4:(d+1)*4] + l[u*4:(u+1)*4]
        b = sum([(1 if c.strip() else 0) << n for n, c in enumerate(linea)])
        print ("0x%02X," % b), 
    print
    
print """};"""
