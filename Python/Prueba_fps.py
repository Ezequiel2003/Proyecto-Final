import cv2
import numpy as np
import colorsys
import serial
import time



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

h_low_ini = 31
s_low_ini = 57
v_low_ini = 71 
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

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, ancho)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,alto)
cap.set(cv2.CAP_PROP_FPS, 60)


ciclo_ini = cv2.getTickCount()

while(1):
   
  # Take each frame
  ret, frame = cap.read()

  if(ret):
      ciclos_trans = cv2.getTickCount() - ciclo_ini #Diferencia entre ciclo transcurrido y ciclo inicial hasta que se procesó el frame
      frec = cv2.getTickFrequency()
      elap = ciclos_trans/frec
      tiempo_frame = elap - elap_viejo #Tiempo entre frame en segundos
      tiempo_frame = round(tiempo_frame*1000,2) #Diferencia en ms, limitado a dos decimales
      
      
      if(tiempo_frame_min > tiempo_frame):
          tiempo_frame_min = tiempo_frame
      if(tiempo_frame_max < tiempo_frame):
          tiempo_frame_max = tiempo_frame
          
      
      print("Tiempo entre frames en ms:",tiempo_frame)
      print("Tiempo mínimo en ms por frame:",tiempo_frame_min)
      print("Tiempo máximo en ms por frame:",tiempo_frame_max)
      print("\n")
      
      
      elap_viejo = elap
      cuadros+=1 #aumento la cuenta de la cantidad de cuadros  
      
      cv2.putText(frame, "T_min(ms):"+str(tiempo_frame_min), position5, font, fontScale*0.5, fontColor,thick-1)
      cv2.putText(frame, "T_max(ms):"+str(tiempo_frame_max), position6, font, fontScale*0.5, fontColor,thick-1)
      cv2.putText(frame, "T_frame(ms):"+str(tiempo_frame), position4, font, fontScale*0.5, fontColor,thick-1)
      
      if elap > 1:
          elap_viejo = 0
          fps = int(cuadros/elap)
          cuadros = 0
          ciclo_ini = cv2.getTickCount()
          
      cv2.putText(frame, "FPS:"+str(fps), position3, font, fontScale, fontColor,thick)      
      cv2.imshow('frame',frame)
      
     
      k = cv2.waitKey(1); 0xFF
      # si pulsa q se rompe el ciclo
      if k == ord("q"):
        break
  else:
      print("Error de la cámara")
      break
cv2.destroyAllWindows()
cap.release()