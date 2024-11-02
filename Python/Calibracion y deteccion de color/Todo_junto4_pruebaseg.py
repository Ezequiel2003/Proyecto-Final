import cv2
import numpy as np
import colorsys
import serial
import time
import matplotlib.pyplot as plt
from matplotlib import pyplot
from matplotlib.animation import FuncAnimation


#flags y variables de configuracion

#--------- Configuración puerto COM de datos de inclinación

COM = 'COM3'

com_serial = serial.Serial(COM,9600,8,stopbits=1)

com_serial.close()
if(not(com_serial.isOpen())): #si el puerto está cerrado, lo abre
    com_serial.open()
#--------

#-------- Configuración puerto COM de seguridad
COM_seg = 'COM5'

com_serial_seg = serial.Serial(COM_seg,9600,8,stopbits=1)

com_serial_seg.close()
if(not(com_serial_seg.isOpen())): #si el puerto está cerrado, lo abre
    com_serial_seg.open()
    
flag_seg = 0
#---------


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

#---Para función búsqueda de puntos blancos
p_anterior = (0,0)
x1 = 0
x2 = 0
y1 = 0
y2 = 0



h_low_ini = 54
s_low_ini = 119
v_low_ini = 88 
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

def encontrar_puntob(img2,flag):
    global p_anterior,x1,x2,y1,y2,p_ini #guardo la última vez en donde estuvo el punto blanco
    img = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    mask = np.zeros(img.shape[:2], np.uint8)
    mask2 = np.zeros(img.shape[:2], np.uint8)
    p_ref = (0,0)
    p_blanco = (0,0)
    seg = 0
    
    #Obtener las posiciones actuales de los 3 Trackbars
    x_ini_mask = cv2.getTrackbarPos('X_ini', 'Mask')
    x_fin_mask = cv2.getTrackbarPos('X_final', 'Mask')
    y_ini_mask = cv2.getTrackbarPos('Y_ini', 'Mask')
    y_fin_mask = cv2.getTrackbarPos('Y_final', 'Mask')
    desplazamiento_mask = cv2.getTrackbarPos('Copia Desplazada', 'Mask')
    
    if not(flag): #Cuando no está calibrado
        """    
        #Obtener las posiciones actuales de los 3 Trackbars
        x_ini_mask = cv2.getTrackbarPos('X_ini', 'Mask')
        x_fin_mask = cv2.getTrackbarPos('X_final', 'Mask')
        y_ini_mask = cv2.getTrackbarPos('Y_ini', 'Mask')
        y_fin_mask = cv2.getTrackbarPos('Y_final', 'Mask')
        desplazamiento_mask = cv2.getTrackbarPos('Copia Desplazada', 'Mask')
        """
        a = y_fin_mask+desplazamiento_mask
        b = (2*y_fin_mask) + desplazamiento_mask - y_ini_mask
        
        x1 = x_ini_mask
        x2 = x_fin_mask
        y1 = a
        y2 = b
        
        mask[y_ini_mask:y_fin_mask,x_ini_mask:x_fin_mask] = 255
        mask[a:b,x_ini_mask:x_fin_mask] = 255
        img = cv2.bitwise_and(mask, img)
        #img = cv2.bitwise_and(mask2, img)
        
        #binarización OTSU
        _,binarizado = cv2.threshold(img, 0,255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)
        
        
        #Dilatación para agrandar los puntos blancos
        kernel = np.ones((5,5),np.uint8)
        binarizado = cv2.dilate(binarizado, kernel, iterations = 1)
        #img = cv2.GaussianBlur(img,(9,9),0)
        circulos = cv2.HoughCircles(binarizado, cv2.HOUGH_GRADIENT, dp = 2, minDist=50, param1=90,param2=7, minRadius=2,maxRadius=7)
        #circulos = cv2.HoughCircles(binarizado, cv2.HOUGH_GRADIENT, dp = 2, minDist=1, param1=90,param2=70,minRadius=10,maxRadius=40)
        print('\n')
        print(circulos)
        print(len(circulos[0,:]))
        if circulos is not(None):
            
            circulos = np.uint16(np.around(circulos))
            
            binarizado = cv2.cvtColor(binarizado,cv2.COLOR_GRAY2BGR)
            if(len(circulos[0,:]) == 2):
                print(circulos[0,0,0:2],circulos[0,1,0:2])
                if(circulos[0,0,1] < circulos[0,1,1]): #Si el primer elemento encontrado es el punto de referencia
                    p_ref = circulos[0,0,0],circulos[0,0,1]        
                    p_blanco = circulos[0,1,0],circulos[0,1,1]
                else: #si el primer elemento encontrado es el punto blanco
                    p_blanco = circulos[0,0,0],circulos[0,0,1]        
                    p_ref = circulos[0,1,0],circulos[0,1,1]
                
                p_anterior = p_blanco
                for i in circulos[0,:]:
                  # draw the outer circle
                  cv2.circle(binarizado,(i[0],i[1]),i[2],(0,255,0),2)
                  cv2.circle(img2,(i[0],i[1]),i[2],(0,255,0),2)
                  # draw the center of the circle
                  cv2.circle(binarizado,(i[0],i[1]),2,(0,0,255),3)
                  cv2.circle(img2,(i[0],i[1]),2,(0,0,255),3)
            cv2.imshow('img', img)
    #dst2 = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 3)
    #cv2.imshow()
    else:
        
        print("\n")
        """
        print("Punto anterior[0]",p_anterior[0])
        print("Punto anterior[1]",p_anterior[1])
        """
        print("x1",x1)
        print("x2",x2)
        print("y1",y1)
        print("y2",y2)
        
        """
        tolerancia = 5
        if(p_anterior[0] - x1 <= tolerancia+2): #Si el punto blanco anterior estaba cerca del borde izquierdo
            x1 -= tolerancia
            x2 -= tolerancia
            print("Corrige a la izquierda")
            #time.sleep(2)
        elif(x2 - p_anterior[0] <= tolerancia+2): #Si el punto blanco anterior estaba cerca del borde derecho
            x1 += tolerancia
            x2 += tolerancia
            print("Corrige a la derecha")
            #time.sleep(2)
        if(p_anterior[1] - y1 <= tolerancia+2): #Si el punto blanco anterior estaba cerca del borde inferior
            y1 -= tolerancia
            y2 -= tolerancia
            print("Corrige hacia abajo")
            #time.sleep(2)
        elif(y2 - p_anterior[1] <= tolerancia+2): #Si el punto blanco anterior estaba cerca del borde superior
            y1 += tolerancia
            y2 += tolerancia
            print("Corrige hacia arriba")
            #time.sleep(2)
        """
        
        mask[y1:y2,x1:x2] = 255
        img = cv2.bitwise_and(mask, img)
        
        #binarización OTSU
        _,binarizado = cv2.threshold(img, 0,255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)
        
        
        #Dilatación para agrandar los puntos blancos
        kernel = np.ones((5,5),np.uint8)
        binarizado = cv2.dilate(binarizado, kernel, iterations = 1)
        #img = cv2.GaussianBlur(img,(9,9),0)
        
        #----------------Búsqueda del punto blanco con contorno y momentos
        
        contornos,_ = cv2.findContours(binarizado, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        binarizado = cv2.cvtColor(binarizado,cv2.COLOR_GRAY2BGR)
        
        for c in contornos:
            
            area = cv2.contourArea(c)
            print("area:",area)
            if(area <= 65 and area >= 42):
                seg = 1
                M = cv2.moments(c)
                # if (M["m00"]==0): M["m00"]=1 #si el m00 es cero lo iguala a 1 para no dividir por 0
                x = int(M["m10"]/M["m00"])
                y = int(M['m01']/M['m00'])
                p_blanco = (x,y)
                print("Punto blanco:",p_blanco)
                p_anterior = p_blanco
                cv2.circle(img2, (x,y), 3, (0,255,0), -1)
                cv2.circle(binarizado, (x,y), 3, (0,255,0), -1)
                contorno = cv2.convexHull(c) #dibuja contorno aplicando cerco Convexo
                cv2.drawContours(img2, [contorno], 0, (255,0,0), 3)
                cv2.drawContours(binarizado, [contorno], 0, (255,0,0), 3)
            else:
                #seg = 0
                p_blanco = p_ini
                cv2.circle(img2, (p_blanco), 3, (0,255,0), -1)
                cv2.circle(binarizado, (p_blanco), 3, (0,255,0), -1)
        #---------------
        
        
        #---------------Búsqueda del punto blanco con transformada circular de Hough
        
        """
        circulos = cv2.HoughCircles(binarizado, cv2.HOUGH_GRADIENT, dp = 2, minDist=50, param1=90,param2=7, minRadius=2,maxRadius=7)
        
        if circulos is not(None):
            
            circulos = np.uint16(np.around(circulos))
            
            binarizado = cv2.cvtColor(binarizado,cv2.COLOR_GRAY2BGR)
            if(len(circulos[0,:]) == 1):
                #print(circulos[0,:,:],circulos[0,:,:])
                #print("Punto anterior:",p_anterior)
                p_blanco = circulos[0,0,0],circulos[0,0,1]
                print("Punto blanco:",p_blanco)
                p_anterior = p_blanco
                for i in circulos[0,:]:
                  # draw the outer circle
                  cv2.circle(binarizado,(i[0],i[1]),i[2],(0,255,0),2)
                  cv2.circle(img2,(i[0],i[1]),i[2],(0,255,0),2)
                  # draw the center of the circle
                  cv2.circle(binarizado,(i[0],i[1]),2,(0,0,255),3)
                  cv2.circle(img2,(i[0],i[1]),2,(0,0,255),3)
        """
        #------------ seguir el punto blanco
        if(seg):
            tolerancia = 10
            x1 = p_blanco[0] - tolerancia*1
            x2 = p_blanco[0] + tolerancia*1
            y1 = p_blanco[1] - tolerancia
            y2 = p_blanco[1] + tolerancia
        else:
            tolerancia = 10
            x1 = p_blanco[0] - int(tolerancia/2)
            x2 = p_blanco[0] + int(tolerancia/2)
            y1 = p_blanco[1] - tolerancia
            y2 = p_blanco[1] + tolerancia
        
        
        """
        tolerancia = 5
        if(p_anterior[0] - x1 <= tolerancia+2): #Si el punto blanco anterior estaba cerca del borde izquierdo
            x1 -= tolerancia
            x2 -= tolerancia
            print("Corrige a la izquierda")
            #time.sleep(2)
        elif(x2 - p_anterior[0] <= tolerancia+2): #Si el punto blanco anterior estaba cerca del borde derecho
            x1 += tolerancia
            x2 += tolerancia
            print("Corrige a la derecha")
            #time.sleep(2)
        if(p_anterior[1] - y1 <= tolerancia+2): #Si el punto blanco anterior estaba cerca del borde inferior
            y1 -= tolerancia
            y2 -= tolerancia
            print("Corrige hacia abajo")
            #time.sleep(2)
        elif(y2 - p_anterior[1] <= tolerancia+2): #Si el punto blanco anterior estaba cerca del borde superior
            y1 += tolerancia
            y2 += tolerancia
            print("Corrige hacia arriba")
        """
        
    cv2.imshow('binarizado', binarizado)
    cv2.imshow('Mask', mask)
    
    return p_ref,p_blanco,seg   #retorna el punto de referencia, es decir el superior para calibración, punto blanco actual, y seguridad    


#Crea una función que no hace nada
def nada(x):
     pass

def Mouse(event,x,y,flags,param):
    global upper_blue,lower_blue,h_min,s_min,v_min,h_max,s_max,v_max
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
    """
    elif event == cv2.EVENT_LBUTTONDOWN:
        h_min = cv2.getTrackbarPos("h_min", "Azul")
        s_min = cv2.getTrackbarPos("s_min", "Azul")
        v_min = cv2.getTrackbarPos("v_min", "Azul")
        print("Valor mínimo calibrado")
        print("(h,s,v) -> (",h_min,",",s_min,",",v_min,")")
        print("\n") 
        lower_blue = np.array([h_min,s_min,v_min]) 
        
    elif event == cv2.EVENT_RBUTTONDOWN:
        h_max = cv2.getTrackbarPos("h_max", "Azul")
        s_max = cv2.getTrackbarPos("s_max", "Azul")
        v_max = cv2.getTrackbarPos("v_max", "Azul")
        print("Valor máximo calibrado")
        print("(h,s,v) -> (",h_max,",",s_max,",",v_max,")")
        print("\n") 
        upper_blue = np.array([h_max,s_max,v_max])   
    """


#--------Barras deslizantes
cv2.destroyAllWindows()
#Crear una ventana llamada canny
#cv2.namedWindow('Controles - Canny')
#cv2.resizeWindow('Controles - Canny', ancho,alto)

cv2.namedWindow('Mask')
cv2.resizeWindow('Mask', ancho,alto)


cv2.createTrackbar('X_ini', 'Mask', 325, ancho, nada)
cv2.createTrackbar('X_final', 'Mask', 347, ancho, nada)
cv2.createTrackbar('Y_ini', 'Mask', 52, alto, nada)#38
cv2.createTrackbar('Y_final', 'Mask', 80, alto, nada)#60
cv2.createTrackbar('Copia Desplazada', 'Mask', 87, alto, nada)#128

cv2.namedWindow("frame")
cv2.createTrackbar('Rot(-d)', 'frame',0,90,nada)
cv2.setMouseCallback("frame",Mouse)

#-------- Fin barras deslizantes

ciclo_ini = cv2.getTickCount()
f_anterior = np.zeros([360,640,3], np.uint8) #Cambiar por los valores correspondientes (480,640)

while(1):
   
  # Take each frame
  #ret, frame = cap.read() #COMENTADO SOLAMENTE PARA PRUEBA CON IMÁGENES ESTÁTICAS
  ret = True
  frame2 = cv2.imread('arriba_1_n.png',1)
  #frame2 = cv2.imread('monedas_4x8.jpg',1)
  if(ret): #Si no hay fallo en capturar el frame
      
      theta = 0
      if not calib :
        #f_anterior = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY) #Comentado únicamente para imágenes estáticas
        f_anterior = cv2.cvtColor(frame2, cv2.COLOR_BGR2GRAY) #Comentar cuando no se usen imágenes estáticas
        #p_ref,p_ini = encontrar_puntob(frame,calib) #Comentado únicamente para imágenes estáticas
        p_ref,p_ini,seg = encontrar_puntob(frame2,calib) #Comentar cuando no se usen imágenes estáticas
        print("Punto de referencia: ",p_ref)
        print("Punto inicial: ",p_ini)
        com_serial_seg.write(str(seg).encode() + b'\r\n')
        #cv2.putText(frame,'Pulse "c" para calibrar ',position,font,fontScale,fontColor,thick) #Comentado únicamente para imágenes estáticas
        cv2.putText(frame2,'Pulse "c" para calibrar ',position,font,fontScale,fontColor,thick) #Comentar cuando no se usen imágenes estáticas
      else:
#          Comentar cuando no se utilicen imágenes estáticas
          frame = frame2.shape
          Ang_rot = 1*cv2.getTrackbarPos('Rot(-d)', 'frame')      
          centro = p_ref
#          #print("Centro de rotacion: ",centro)
          matriz_rot = cv2.getRotationMatrix2D(center = centro, angle = Ang_rot, scale = 1)
          frame = cv2.warpAffine(src=frame2, M = matriz_rot,dsize=(frame2.shape[1],frame2.shape[0]))
          
          frame_nuevo = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
          f_dif = cv2.subtract(frame_nuevo, f_anterior)
          
          _,p_blanco,seg = encontrar_puntob(frame,calib)
          #Si ya está calibrado, devuelve la posición del punto blanco del brazo
          
          
          #Imprime las líneas y busca los puntos blancos
          cv2.line(frame, p_ref, p_blanco, (0,255,255),2)
          cv2.line(frame, p_ref, p_ini, (0,255,255),2)
          #print("\n")
          print("p_ini",p_ini)
          print("p_ref",p_ref)
          
          cat_ady = int(p_blanco[1]) - int(p_ref[1]) #En teoría no nos interesa con respecto al eje y dónde se encuentra el punto blanco
          
          if(p_ini[0] < p_ref[0]): #Si el punto inicial está a la izquierda del centro de la imagen respecto al punto de referencia
              if(p_ini[0] <= p_blanco[0] and p_blanco[0] < p_ref[0]): #Si el punto blanco que buscamos está entre el punto inicial y la mitad de imagen
                   cat_op = (int(p_ref[0])-int(p_ini[0])) - (int(p_ref[0]) - int(p_blanco[0]))
                   
              elif(p_blanco[0]>=p_ref[0]): #Si el punto blanco pasa la mitad derecha de la imagen
                  cat_op = (int(p_ref[0])-int(p_ini[0])) + (int(p_blanco[0]) - int(p_ref[0]))
              else: #Si el punto blanco está en la mitad izquierda de la imagen
                  cat_op = (int(p_ref[0])-int(p_blanco[0])) - (int(p_ref[0])-int(p_ini[0]))
                  cat_op *= -1
                  
          else: #O sea si p_ini[0] >= p_ref[0] quiere decir si el punto inicial está a la derecha del centro de la imagen respecto al punto de referencia
              if(p_ini[0] >= p_blanco[0] and p_blanco[0] > p_ref[0]): #Si el punto blanco que buscamos está entre el punto inicial y la mitad de imagen
                   cat_op = (int(p_ini[0])-int(p_ref[0])) - (int(p_blanco[0]) - int(p_ref[0]))
                   cat_op *= -1 
                   
              elif(p_blanco[0]>=p_ini[0]): #Si el punto blanco pasa la mitad derecha de la imagen y el punto inicial
                  cat_op =  (int(p_blanco[0]) - int(p_ref[0])) - (int(p_ini[0])-int(p_ref[0]))
                  
              else: #Si el punto blanco está en la mitad izquierda de la imagen
                  cat_op = (int(p_blanco[0])-int(p_ref[0])) + (int(p_ini[0])-int(p_ref[0]))
                  cat_op *= -1
            
          #print("Cat_ady",cat_ady)
          #print("Cat_op",cat_op)
          theta = np.arctan(cat_op/cat_ady) #devuelve el valor en radianes
          theta_d = np.rad2deg(theta) #lo convierto en grados
          theta = round(theta,2)
          theta_d = round(theta_d,2)
          print("Ángulo de inclinación (rad):",theta)
          print("Ángulo de inclinación (deg):",theta_d)
          com_serial.write(str(theta).encode() + b'\r\n')
         
          if(not seg): 
              flag_seg = 0 #Cuando no hay "seguridad", envía constantemente el 0, para asegurarse que no funcione el motor
              com_serial_seg.write(str(seg).encode() + b'\r\n')
              com_serial.write(str(theta).encode() + b'\r\n')
                  
          else:
              if(flag_seg):
                  com_serial.write(str(theta).encode() + b'\r\n') 
              
          #Si no hay seguridad, es decir que perdió el punto blanco, entonces envía un cero para detener el uso del motor.
          #Pero en cambio si seg es 1, entonces manda habilitar el uso del motor.
              
          
         
          #cv2.putText(frame, "Angulo:"+str(theta)+"Deg", position2, font, fontScale, fontColor,thick)
          cv2.putText(frame, "Angulo:"+str(theta)+"Rad", position2, font, fontScale, fontColor,thick)
          
          
          #cv2.imshow('Dif',f_dif)
          cv2.imshow('frame',frame) #COMENTAR CUANDO NO SE USEN IMÁGENES ESTÁTICAS
      #rota la imagen
      
      
        
      ciclos_trans = cv2.getTickCount() - ciclo_ini #Diferencia entre ciclo transcurrido y ciclo inicial hasta que se procesó el frame
      frec = cv2.getTickFrequency()
      elap = ciclos_trans/frec
      tiempo_frame = elap - elap_viejo #Tiempo entre frame en segundos
      tiempo_frame = round(tiempo_frame*1000,2) #Diferencia en ms, limitado a dos decimales
      
      
      if(tiempo_frame_min > tiempo_frame):
          tiempo_frame_min = tiempo_frame
      if(tiempo_frame_max < tiempo_frame):
          tiempo_frame_max = tiempo_frame
          
      """
      print("Tiempo entre frames en ms:",tiempo_frame)
      print("Tiempo mínimo en ms por frame:",tiempo_frame_min)
      print("Tiempo máximo en ms por frame:",tiempo_frame_max)
      print("\n")
      """
      
      
      elap_viejo = elap
      cuadros+=1 #aumento la cuenta de la cantidad de cuadros  
      
      #cv2.putText(frame, "T_min(ms):"+str(tiempo_frame_min), position5, font, fontScale*0.5, fontColor,thick-1)
      #cv2.putText(frame, "T_max(ms):"+str(tiempo_frame_max), position6, font, fontScale*0.5, fontColor,thick-1)
      #cv2.putText(frame, "T_frame(ms):"+str(tiempo_frame), position4, font, fontScale*0.5, fontColor,thick-1)
      
      if elap > 1:
          elap_viejo = 0
          fps = int(cuadros/elap)
          cuadros = 0
          tiempo_frame_min = 1000
          tiempo_frame_max = 0
          if(seg and flag_seg):
              com_serial_seg.write(str(seg).encode() + b'\r\n')
          ciclo_ini = cv2.getTickCount()
          
      
      
      #cv2.putText(frame, "FPS:"+str(fps), position3, font, fontScale, fontColor,thick)      
      #cv2.imshow('frame',frame) # COMENTADO ÚNICAMENTE PARA IMÁGENES ESTÁTICAS
      
      cv2.imshow('frame2',frame2) # comentar cuando no se usen imágenes estáticas
      
     
      k = cv2.waitKey(1); 0xFF
      # si pulsa q se rompe el ciclo
      if k == ord("q"):
        break
      if k == ord("c"):
          print("Posición inical calibrada")
          calib = 1
          cv2.destroyWindow('img')
      if k == ord("r") and not flag_seg:
          flag_seg = 1
          print("Reset")
          
          
          
        
        
  else:
       print("Error en la cámara :c")
       
cv2.destroyAllWindows()
com_serial.close()
com_serial_seg.close()