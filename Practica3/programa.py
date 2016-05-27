import cProfile

def g(t,y):
    w=list()
    for i in range(t):
        w.append(i)

def f(a):
    z=0
    for i in range(a):
        z=g(i,z)

    return z

cProfile.run('f(5000)')
