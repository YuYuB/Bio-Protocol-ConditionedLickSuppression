#/dev/cu.usbmodem1421
#/dev/cu.wchusbserial1420
import csv
import serial # import serial library
#import matplotlib.pyplot as plt
import time
import os

# /dev/cu.wchusbserial1410
SerialP = input("Enter the Serial Port of your Black Box:")
print ("Your Serial Port is =", SerialP)
print ("")
File = input("Enter a file name :")
FileE = File + ".csv"
print ("Your file name is =", FileE)
print ("")
#Time = input("Enter the duration of the session in seconds:")
#print "The session will last) =", Time
#print""
Tableau = []
#Tableaux = [0]
#Tableauy = [1]
#TableauLx = [2]
arduino = serial.Serial(SerialP, 250000) # Creating our serial object named arduino
#arduino = serial.Serial('com8', 115200) # Creating our serial object named arduino
# arduino = serial.Serial('/dev/cu.usbmodem1411', 115200) # Creating our serial object named arduino

connected = False
while not connected:
    serin = arduino.read()
    connected = True
E = 0
message = arduino.readline()
print(message[0])
if message[0] == ("T") :
    timeout_start = time.time()

    # timeout variable can be omitted, if you use specific value in the while condition
    #timeout = 5   # [seconds]

    #while time.time() < timeout_start + Time:
    while E == 0:
    
        # while True : # Boucle a l infini
        while (arduino.inWaiting()==0): # Boucle ici tant qu il n y a pas d entree de donnees
            pass # Ne rien faire
        arduinoString = arduino.readline()      #lire la ligne de texte venant du port seriel
        dataArray = arduinoString.split(';')    #Split en array appele dataArray
        dataArray[0] = float (dataArray[0])
        dataArray[0] = dataArray[0]/1000
        dataArray[1] = float (dataArray[1])
        dataArray[2] = float (dataArray[2])
        dataArray[3] = float (dataArray[3])
        dataArray[4] = float (dataArray[4])
        dataArray[5] = float (dataArray[5])
        dataArray[6] = float (dataArray[6])
        dataArray[7] = float (dataArray[7])
        dataArray[8] = float (dataArray[8])
        dataArray[9] = float (dataArray[9])
        dataArray[10] = float (dataArray[10])    
        dataArray[11] = str (dataArray[11])
        dataArray.remove(dataArray[11])
        
        if dataArray[10] == 1 :
            E = 1
    
    
        print (dataArray)
        Tableau.append(dataArray)
#        Tableaux.append(dataArray[0])
#        Tableauy.append(dataArray[2])
#        TableauLx.append(dataArray[3])


#    print Tableau 
#    print Tableaux
#    print Tableauy
    with open(FileE, "w") as output:
        writer = csv.writer(output, lineterminator='\n')
        for val in Tableau:
            writer.writerow(val)

        
#    plt.figure(num=1, figsize=(38, 5), dpi=50, facecolor='w', edgecolor='k')
#    plt.subplots_adjust(left=0.020, bottom=0.08, right=1.0, top=0.95, wspace=-0.1, hspace=0.1)
#    x = Tableaux[1:]
#    y = Tableauy[1:]
#    Lx = TableauLx[1:]
    #print x
    #print y
    #print Lx
#    z = Tableaux[-1] + 1
#    plt.grid(True)
#    plt.axis([0, Time, 0, 2.1])
#    plt.xlabel('Temps')
#    plt.ylabel('Lick')
#    plt.plot(x, Lx,color = 'red', linewidth = 1, markersize = 0.05)
#    plt.stem(x,y, markerfmt=" ",markerLines = 0.05)                    #bars 
#    plt.scatter(x, y, marker = 'o') #dots
#    FileG = File + ".pdf"
#    plt.savefig(FileG ,bbox_inches='tight')
    
#    plt.show()    




