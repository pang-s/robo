
def main():
    
    height = 10
    ypoints = []
    xpoints = []
    step = 1
    a = -0.05 # makes parabola fatter , put negative if want upside down
    x = -20
    for i in range(x*-2 + step):
        y = a*x**2
        
        xpoints.append(x)
        ypoints.append(y)
        x += step
        
    
    #print(ypoints)
    #print(xpoints)
    factor = 1
    # convert to decimal
    #for i in range(len(ypoints)):
        #ypoints[i] = ypoints[i] / factor
        #xpoints[i] = xpoints[i] / factor
    print(ypoints)
    print(xpoints)                   
    print(len(ypoints))
    

main()