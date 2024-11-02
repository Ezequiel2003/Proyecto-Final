import cv2
import numpy as np
import colorsys
import serial
import time



#flags y variables de configuracion

COM = 'COM3'
#com_serial = serial.Serial(COM,9600,8,stopbits=1)

#com_serial.close()
#if(not(com_serial.isOpen())): #si el puerto está cerrado, lo abre
#    com_serial.open()


"""Variables de ciclos y tiempo, para el cálculo de fps"""
ciclo_ini = 0 
ciclos_trans = 0
elap_viejo = 0
elap = 0
tiempo_frame = 0
tiempo_frame_min = 10000
tiempo_frame_max = 0
frec = 0
cuadros = 0
fps = 0

"""
La función cv.getTickCount() devuelve el número de ciclos de reloj después de 
un evento de referencia hasta el momento en que se llama a esta función.
Entonces, si se lo llama antes y después de la ejecución de una función, se 
obtiene la cantidad de ciclos de reloj que consume la función

La función cv.getTickFrequency() devuelve la frecuencia de los ciclos de reloj,
 o la cantidad de ciclos de reloj por segundo.
"""

"""Fin variable de tiempo""" 


x_ini = 0
y_ini = 0
calib = 0
alto = 480
ancho = 640
font = cv2.FONT_HERSHEY_SIMPLEX
fontScale = 1
fontColor = (255,255,0)
thick = 3
position = (int(ancho/2)-170,40)
position2 = (350,40)
position3 = (0,40)
position4 = (0,80)
position5 = (0,120)
position6 = (0,160)

h_low_ini = 82
s_low_ini = 122
v_low_ini = 100 
lower_blue = np.array([h_low_ini,s_low_ini,v_low_ini])

#lower_blue = np.array([30,50,35]) #original 

"""
Valor mínimo calibrado
(h,s,v) -> ( 31 , 57 , 71 )
"""


h_max_ini = 120
s_max_ini = 217
v_max_ini = 255  
upper_blue = np.array([h_max_ini,s_max_ini,v_max_ini])

#upper_blue = np.array([120,210,230]) #original
"""
Valor máximo calibrado
(h,s,v) -> ( 120 , 217 , 255)
"""

cap = cv2.VideoCapture(1, cv2.CAP_DSHOW)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, ancho)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,alto)
cap.set(cv2.CAP_PROP_FPS,60)

#Crea una función que no hace nada
def nada(x):
     pass

def Mouse(event,x,y,flags,param):
    global upper_blue,lower_blue,h_min,s_min,v_min,h_max,s_max,v_max,x_ini,y_ini
    """
    Si aprieto el botón del medio, veré en la consola la posición y valores BGR
    como su conversión a HSV, de esta forma me sirve para tener una idea y 
    modificar los valores máximos y mínimos del hsv.
    """
    if event == cv2.EVENT_MBUTTONDOWN:
       b_in = frame[y,x,0]
       g_in = frame[y,x,1]
       r_in = frame[y,x,2]
       #entrada
       (r,g,b) = (r_in,g_in,b_in)
       #normalizo
       (r,g,b) = (r/255,g/255,b/255)
       #convierto a hsv 
       (h,s,v) = colorsys.rgb_to_hsv(r, g, b)
       #expandir a rango hsv
       (h,s,v) = (int(h*179),int(s*255),int(v*255))
       
       
       print("Valor azul:")
       print("(x,y) -> ","(",x,",",y,")")
       print("(b,g,r) -> (",b_in,",",g_in,",",r_in,")")
       print("(h,s,v) -> (",h,",",s,",",v,")")
       print("\n") 
    
    elif event == cv2.EVENT_LBUTTONDOWN:
        h_min = cv2.getTrackbarPos("h_min", "barra")
        s_min = cv2.getTrackbarPos("s_min", "barra")
        v_min = cv2.getTrackbarPos("v_min", "barra")
        print("Valor mínimo calibrado")
        print("(h,s,v) -> (",h_min,",",s_min,",",v_min,")")
        print("\n") 
        lower_blue = np.array([h_min,s_min,v_min]) 
        
    elif event == cv2.EVENT_RBUTTONDOWN:
        x_ini = x
        y_ini = y
        
        """h_max = cv2.getTrackbarPos("h_max", "barra")
        s_max = cv2.getTrackbarPos("s_max", "barra")
        v_max = cv2.getTrackbarPos("v_max", "barra")
        print("Valor máximo calibrado")
        print("(h,s,v) -> (",h_max,",",s_max,",",v_max,")")
        print("\n") 
        upper_blue = np.array([h_max,s_max,v_max])
        """
    
cv2.namedWindow("frame")
cv2.setMouseCallback("frame",Mouse)
cv2.namedWindow("barra")
cv2.createTrackbar("h_min","barra",h_low_ini,180,nada)
cv2.createTrackbar("s_min","barra",s_low_ini,255,nada)
cv2.createTrackbar("v_min","barra",v_low_ini,255,nada)

cv2.createTrackbar("h_max","barra",h_max_ini,180,nada)
cv2.createTrackbar("s_max","barra",s_max_ini,255,nada)
cv2.createTrackbar("v_max","barra",v_max_ini,255,nada)


ciclo_ini = cv2.getTickCount()

while(1):
   
  # Take each frame
  ret, frame = cap.read()
  if(ret):
      hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
     
      # Threshold the HSV image to get only Green and Red colors
      mask3 = cv2.inRange(hsv, lower_blue, upper_blue)
      
      blue = cv2.bitwise_and(frame,frame, mask= mask3)
  
  

      contornos2,_ = cv2.findContours(mask3, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
      for c in contornos2:
          area = cv2.contourArea(c)
          if area > 1000: #dibuja contornos de objetos area > a 4000
              #print("El área es:",area)
              #Encontramos el centro del controno:
              M = cv2.moments(c)
              # if (M["m00"]==0): M["m00"]=1 #si el m00 es cero lo iguala a 1 para no dividir por 0
              x = int(M["m10"]/M["m00"])
              y = int(M['m01']/M['m00'])
              cv2.circle(frame, (x,y), 7, (0,255,0), -1)
              cv2.putText(frame, '{},{}'.format(x,y),(x+10,y), font, 0.75,(0,0,255),1,cv2.LINE_AA)
              contorno = cv2.convexHull(c) #dibuja contorno aplicando cerco Convexo
              cv2.drawContours(frame, [contorno], 0, (255,0,0), 3)
              
              if calib == 1: #si está calibrado, se dibujan líneas verticales limitando la imagen, para calcular después el ángulo
                  cat_op = (x_ini - x) #cateto opuesto
                  cat_ady = alto-1 -y #cateto adyacente
                  theta = np.arctan(cat_op/cat_ady) #devuelve el valor en radianes
                  theta = np.rad2deg(theta) #lo convierto en grados
                  theta = round(theta,2)
                  print("Ángulo de inclinación:",theta) 
                  #com_serial.write(str(theta).encode() + b'\r\n')
                  cv2.line(frame,(x_ini,0),(x_ini,alto-1),(0,255,255),thickness=1) #dibuja una linea recta que pasa por el punto donde se calibró el "péndulo"
                  cv2.line(frame,(x_ini,alto-1),(x,y),(0,255,255),thickness=2) #dibuja una linea recta que va desde abajo hasta el punto donde se encuentra actualmente el "péndulo"
                  cv2.putText(frame, "Angulo:"+str(theta)+"Deg", position2, font, fontScale, fontColor,thick)
              
      if calib == 0:
          cv2.putText(frame,'Pulse "c" para calibrar ',position,font,fontScale,fontColor,thick)
      
      ciclos_trans = cv2.getTickCount() - ciclo_ini #Diferencia entre ciclo transcurrido y ciclo inicial hasta que se procesó el frame
      frec = cv2.getTickFrequency()
      elap = ciclos_trans/frec
      tiempo_frame = elap - elap_viejo #Tiempo entre frame en segundos
      tiempo_frame = round(tiempo_frame*1000,2) #Diferencia en ms, limitado a dos decimales
      
      
      if(tiempo_frame_min > tiempo_frame):
          tiempo_frame_min = tiempo_frame
      if(tiempo_frame_max < tiempo_frame):
          tiempo_frame_max = tiempo_frame
          
      
      #print("Tiempo entre frames en ms:",tiempo_frame)
      #print("Tiempo mínimo en ms por frame:",tiempo_frame_min)
      #print("Tiempo máximo en ms por frame:",tiempo_frame_max)
      #print("\n")
      
      
      elap_viejo = elap
      cuadros+=1 #aumento la cuenta de la cantidad de cuadros  
      
      #cv2.putText(frame, "T_min(ms):"+str(tiempo_frame_min), position5, font, fontScale*0.5, fontColor,thick-1)
      #cv2.putText(frame, "T_max(ms):"+str(tiempo_frame_max), position6, font, fontScale*0.5, fontColor,thick-1)
      cv2.putText(frame, "T_frame(ms):"+str(tiempo_frame), position4, font, fontScale*0.5, fontColor,thick-1)
      
      if elap > 1:
          elap_viejo = 0
          fps = int(cuadros/elap)
          cuadros = 0
          #tiempo_frame_min = 1000
          #tiempo_frame_max = 0
          ciclo_ini = cv2.getTickCount()
          
      cv2.putText(frame, "FPS:"+str(fps), position3, font, fontScale, fontColor,thick)      
      cv2.imshow('frame',frame)
      cv2.imshow('Azul',blue)
     
      k = cv2.waitKey(1); 0xFF
      # si pulsa q se rompe el ciclo
      if k == ord("q"):
        break
      if k == ord("c") and not calib :
        calib = 1
        print("Posicion inicial calibrada")
        #x_ini = x
        #y_ini = y

  else:
      print("Eror con la cámara")
      img = cv2.imread("gatito.jpg")
      cv2.imshow('gatito',img)
      k = cv2.waitKey(1); 0xFF
      if k == ord("q"):
        break
  # Convert BGR to HSV
  
cv2.destroyAllWindows()
cap.release()
#com_serial.close()