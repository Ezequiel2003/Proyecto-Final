import cv2
import numpy as np
import colorsys
import serial
import time



#flags y variables de configuracion
"""
COM = 'COM4'
com_serial = serial.Serial(COM,9600,8,stopbits=1)

com_serial.close()
if(not(com_serial.isOpen())): #si el puerto está cerrado, lo abre
    com_serial.open()
"""

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

cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, ancho)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,alto)


def calibracion(img2):
    img = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    mask = np.zeros(img.shape[:2], np.uint8)
    
    #Obtener las posiciones actuales de los 3 Trackbars
    x_ini_mask = cv2.getTrackbarPos('X_ini', 'Mask')
    x_fin_mask = cv2.getTrackbarPos('X_final', 'Mask')
    y_ini_mask = cv2.getTrackbarPos('Y_ini', 'Mask')
    y_fin_mask = cv2.getTrackbarPos('Y_final', 'Mask')
    hab_mask = cv2.getTrackbarPos('Hab', 'Mask')
    #low = cv2.getTrackbarPos('lower', 'Controles - Canny')
    low = 255
    #up = cv2.getTrackbarPos('upper', 'Controles - Canny')
    up = 255
    
    threshold = cv2.getTrackbarPos('Thresh', 'Hough')
    
    #Generar la matriz rotada
    #Nota: rota en contra de las agujas del reloj
    mask[y_ini_mask:y_fin_mask,x_ini_mask:x_fin_mask] = 255
    
    if(hab_mask):
        #imagen ya con la mascara aplicada, aplicando operación and bit a bit
        img = cv2.bitwise_and(mask, img)
    
    edges = cv2.Canny(img,low,up)
    
    #lines = cv2.HoughLinesP(edges,rho = rho+1,theta = np.pi/theta,threshold = threshold,minLineLength=minLineLength,maxLineGap=maxLineGap)
    lines = cv2.HoughLines(edges,rho = 1, theta = np.pi/180,threshold = threshold)
   
    #transforma la imagen de los bordes a bgr
    cedges = cv2.cvtColor(edges, cv2.COLOR_GRAY2BGR)
    cedges2 = cedges.copy()
    
    A_45 = np.array([[],[],[]],dtype=np.uint8) #Creo matrices vacías de 3x... para concatenar después con las rectas que encuentre
    A_135 = np.array([[],[],[]],dtype=np.uint8)
    x_ini = 0
    y_ini = 0
    if(lines is not None):
        x01 = 0
        y01 = 0

        x02 = 0
        y02 = 0

        m0 = 0

        x11 = 0
        y11 = 0

        x12 = 0
        y12 = 0

        m1 = 0
        
        x01a = 0
        y01a = 0

        m0a = 0

        x11b = 0
        y11b = 0

        m1b = 0
        
        cont_45 = 0
        cont_135 = 0
        
        #print("Lines:",len(lines))
        for i in range(0, len(lines)):
            #print("\n")
            #print("i",i)
            rho = lines[i][0][0] #saca de la matriz "lines" el valor de rho y tita
            #print("rho:",rho)
            theta = lines[i][0][1]
            theta_d = 180*theta/np.pi
            #print("theta:", theta)
            #print("theta_d:", theta_d)
            
            theta_tol = 3 #ángulo en grados de tolerancia para que sea considerada como recta de interés
            theta_tol2 = 3
            
            if(abs(theta_d -45) <= theta_tol) :
                cont_45 += 1
                #print("theta_d válido:", theta_d)
                
                a = np.cos(theta)  #variables auxiliares a y b
                b = np.sin(theta)
                x0 = a*rho  #calcula el punto (x0,y0) por donde pasa la recta que se quiere encontrar
                y0 = b*rho
                #print(i)
                #print(x0,y0)
                x01 = int(x0 + 5000*(-b))
                y01 = int(y0 + 5000*(a))         
                pt1 = (x01, y01)  #usando las variables a y b se encuentran
                
                x02 = int(x0 - 5000*(-b))
                y02 = int(y0 - 5000*(a))
                
                pt2 = (x02, y02)  # los puntos que pasan por la recta buscada.
                m0 = (y02-y01)/(x02-x01) #pendiente de la recta
                
                P = np.array([[m0,0],pt1,pt2]) #Matriz auxiliar de 3x2
                #P = [ m0	 0
                #     (x01  y01) -> pt1
                #     (x02  y02)] -> pt2
                A_45 = np.append(A_45,P,1) #Voy agregando en la matriz todas las rectas de 45° encontradas
                
                cv2.line(cedges, pt1, pt2, (0,0,255), 1, cv2.LINE_AA) #dibuja la recta sobre la imagen BGR
                #imagen, punto1, punto2, color, ancho linea, tipo linea
                
                
                
            if(abs(theta_d -135) <= theta_tol2):
                #print("theta_d válido:", theta_d)
                cont_135 += 1
                a = np.cos(theta)  #variables auxiliares a y b
                b = np.sin(theta)
                x0 = a*rho  #calcula el punto (x0,y0) por donde pasa la recta que se quiere encontrar
                y0 = b*rho
                #print(i)
                #print(x0,y0)
                x11 = int(x0 + 5000*(-b))
                y11 = int(y0 + 5000*(a))         
                
                pt1 = (x11, y11)  #usando las variables a y b se encuentran
                
                x12 = int(x0 - 5000*(-b))
                y12 = int(y0 - 5000*(a))
                
                pt2 = (x12, y12)  # los puntos que pasan por la recta buscada.
                m1 = (y12-y11)/(x12-x11) #pendiente de la recta
                
                P = np.array([[m1,0],pt1,pt2]) #Matriz auxiliar de 3x2
                
                #P = [ m1	 0
                #     (x11  y11) -> pt1
                #     (x12  y12)] -> pt2
                
                
                A_135 = np.append(A_135,P,1) #Voy agregando en la matriz todas las rectas de 135° encontradas
                
                cv2.line(cedges, pt1, pt2, (0,0,255), 1, cv2.LINE_AA) #dibuja la recta sobre la imagen BGR
                #imagen, punto1, punto2, color, ancho linea, tipo linea
                
                
                
        #print("\n") 
        
        
        
        recta_45 = cv2.getTrackbarPos("Recta 45d", "Hough")
        recta_135 = cv2.getTrackbarPos("Recta 135d", "Hough")
        
        if(recta_45+1 <= cont_45 ):
        
            #pt1_45 = tuple(int(A_45[1][(2*recta_45):(2+2*recta_45)])) #según la recta elegida saca el pt1 y pt2 para graficar la recta. Recordar que P es de 3x2
            #pt2_45 = tuple(A_45[2][(2*recta_45):(2+2*recta_45)])
            pt1_45 = (int(A_45[1][(2*recta_45)]),int(A_45[1][(1+2*recta_45)]))
            pt2_45 = (int(A_45[2][(2*recta_45)]),int(A_45[2][(1+2*recta_45)]))
            m0a = A_45[0][recta_45*2]
            x01a = A_45[1][recta_45*2]
            y01a = A_45[1][1+recta_45*2]
            cv2.line(cedges2, pt1_45, pt2_45, (0,0,255), 1, cv2.LINE_AA) #dibuja la recta sobre la imagen BGR
        
        if(recta_135+1 <= cont_135 ):
        
            #pt1_135 = tuple(A_135[1][(2*recta_45):(2+2*recta_45)]) #según la recta elegida saca el pt1 y pt2 para graficar la recta. Recordar que P es de 3x2
            #pt2_135 = tuple(A_135[2][(2*recta_45):(2+2*recta_45)])
            pt1_135 = (int(A_135[1][(2*recta_135)]),int(A_135[1][(1+2*recta_135)]))
            pt2_135 = (int(A_135[2][(2*recta_135)]),int(A_135[2][(1+2*recta_135)]))
            m1b = A_135[0][recta_135*2]
            x11b = A_135[1][recta_135*2]
            y11b = A_135[1][1+recta_135*2]
            cv2.line(cedges2, pt1_135, pt2_135, (0,0,255), 1, cv2.LINE_AA) #dibuja la recta sobre la imagen BGR
        
        
        
       
        
        A = np.array([[m0a,-1],[m1b,-1]]) #Matrices para solucionar el sistema Ax = b y encontrar la intersección entre las rectas
        b = np.array([(m0a*x01a - y01a),(m1b*x11b - y11b)])
        #print("A",A)
        #print("b",b)
        
        if (cont_45 >= 1 and cont_135 >= 1): #Si encuentra al menos una recta de cada una, así evitar tener una matriz singular como solución
            sol = np.linalg.solve(A, b) # x = A\b 
            x_ini = int(sol[0])
            y_ini = int(sol[1])
            #print("Coordenadas intersección ({},{}) \n".format(x_ini,y_ini))
            
            cv2.circle(img2, (x_ini,y_ini), 5, (0,0,255),-1)
            cv2.line(img2, (x_ini,0), (x_ini,alto), (0,255,255), 1, cv2.LINE_AA)    
    
    cv2.imshow('Mask', mask)
    cv2.imshow('Rectas elegidas para el centro',cedges2)
    cv2.imshow('Hough',cedges)
    return x_ini,y_ini        


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

cv2.namedWindow('Hough')
cv2.resizeWindow('Hough', ancho,alto)

cv2.namedWindow('Mask')
cv2.resizeWindow('Mask', ancho,alto)

#Crear las barras para los valores inferiores y superiores
#cv2.createTrackbar('lower', 'Controles - Canny', 255, 255, nada)
#cv2.createTrackbar('upper', 'Controles - Canny', 255, 255, nada)

cv2.createTrackbar('Thresh', 'Hough', 102, 255, nada)
cv2.createTrackbar('Recta 45d', 'Hough', 0, 20, nada) #Se puede elegir hasta 10 rectas
cv2.createTrackbar('Recta 135d', 'Hough', 0, 20, nada) #Se puede elegir hasta 10 rectas



cv2.createTrackbar('Hab', 'Mask', 0, 1, nada)
cv2.createTrackbar('X_ini', 'Mask', 211, ancho, nada)
cv2.createTrackbar('X_final', 'Mask', 400, ancho, nada)
cv2.createTrackbar('Y_ini', 'Mask', 70, alto, nada)
cv2.createTrackbar('Y_final', 'Mask', 252, alto, nada)

cv2.namedWindow("frame")
cv2.createTrackbar('Rot(-d)', 'frame',0,90,nada)
cv2.setMouseCallback("frame",Mouse)

cv2.namedWindow("Azul")
cv2.createTrackbar("h_min","Azul",h_low_ini,180,nada)
cv2.createTrackbar("s_min","Azul",s_low_ini,255,nada)
cv2.createTrackbar("v_min","Azul",v_low_ini,255,nada)

cv2.createTrackbar("h_max","Azul",h_max_ini,180,nada)
cv2.createTrackbar("s_max","Azul",s_max_ini,255,nada)
cv2.createTrackbar("v_max","Azul",v_max_ini,255,nada)
cv2.resizeWindow('Azul', ancho,alto)
#-------- Fin barras deslizantes

ciclo_ini = cv2.getTickCount()

while(1):
   
  # Take each frame
  #ret, frame = cap.read() #COMENTADO SOLAMENTE PARA PRUEBA CON IMÁGENES ESTÁTICAS
  ret = True
  frame2 = cv2.imread('Prueba6.jpg',1)
  if(ret): #Si no hay fallo en capturar el frame
      
      Ang_rot = -1*cv2.getTrackbarPos('Rot(-d)', 'frame')      
      centro =(int(ancho/2),int(alto/2))
      matriz_rot = cv2.getRotationMatrix2D(center = centro, angle = Ang_rot, scale = 1)

      #rota la imagen
      #frame = frame2.shape
      frame = cv2.warpAffine(src=frame2, M = matriz_rot,dsize=(ancho,alto))
        
      # Convert BGR to HSV
      hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
     
      # Threshold the HSV image to get only Green and Red colors
      mask3 = cv2.inRange(hsv, lower_blue, upper_blue)
      
      blue = cv2.bitwise_and(frame,frame, mask= mask3)
      
      h_min = cv2.getTrackbarPos("h_min", "Azul")
      s_min = cv2.getTrackbarPos("s_min", "Azul")
      v_min = cv2.getTrackbarPos("v_min", "Azul")
      lower_blue = np.array([h_min,s_min,v_min])
      
      h_max = cv2.getTrackbarPos("h_max", "Azul")
      s_max = cv2.getTrackbarPos("s_max", "Azul")
      v_max = cv2.getTrackbarPos("v_max", "Azul")
      upper_blue = np.array([h_max,s_max,v_max])
      
      if not calib :
        x_ini,y_ini = calibracion(frame)
        cv2.putText(frame,'Pulse "c" para calibrar ',position,font,fontScale,fontColor,thick)
      
      contornos2,_ = cv2.findContours(mask3, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
      for c in contornos2:
          area = cv2.contourArea(c)
          if area > 800: #dibuja contornos de objetos area > a 4000
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
                  cat_ady = y - y_ini #cateto adyacente
                  theta = np.arctan(cat_op/cat_ady) #devuelve el valor en radianes
                  theta = np.rad2deg(theta) #lo convierto en grados
                  theta = round(theta,2)
                  print("Ángulo de inclinación:",theta) 
                  #com_serial.write(str(theta).encode() + b'\r\n')
                  #cv2.line(frame,(x_ini,0),(x_ini,alto-1),(0,255,255),thickness=1) #dibuja una linea recta que pasa por el punto donde se calibró el "péndulo"
                  cv2.line(frame,(x_ini,y_ini),(x,y),(0,255,255),thickness=2) #dibuja una linea recta que va desde el punto de calibración hasta el punto donde se encuentra actualmente el "péndulo"
                  cv2.putText(frame, "Angulo:"+str(theta)+"Deg", position2, font, fontScale, fontColor,thick)
              
      
      
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
      
      cv2.putText(frame, "T_min(ms):"+str(tiempo_frame_min), position5, font, fontScale*0.5, fontColor,thick-1)
      cv2.putText(frame, "T_max(ms):"+str(tiempo_frame_max), position6, font, fontScale*0.5, fontColor,thick-1)
      cv2.putText(frame, "T_frame(ms):"+str(tiempo_frame), position4, font, fontScale*0.5, fontColor,thick-1)
      
      if elap > 1:
          elap_viejo = 0
          fps = int(cuadros/elap)
          cuadros = 0
          tiempo_frame_min = 1000
          tiempo_frame_max = 0
          ciclo_ini = cv2.getTickCount()
          
      cv2.putText(frame, "FPS:"+str(fps), position3, font, fontScale, fontColor,thick)      
      cv2.imshow('frame',frame)
      cv2.imshow('Azul',blue)
     
      k = cv2.waitKey(1); 0xFF
      # si pulsa q se rompe el ciclo
      if k == ord("q"):
        break
      if k == ord("c"):
          print("Posición inical calibrada")
          calib = 1
          cv2.destroyWindow('Mask')
          cv2.destroyWindow('Hough')
          cv2.destroyWindow('Rectas elegidas para el centro')
          
          
        
        
  else:
       print("Error en la cámara :c")
       
cv2.destroyAllWindows()
#com_serial.close()