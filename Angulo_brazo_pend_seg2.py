import cv2
import numpy as np
import serial


#flags y variables de configuracion

#--------- Configuración puerto COM de datos de inclinación brazo

COM_brazo = 'COM3'

com_brazo = serial.Serial(COM_brazo,115200,8,stopbits=1)

com_brazo.close()
if(not(com_brazo.isOpen())): #si el puerto está cerrado, lo abre
    com_brazo.open()
#--------

#--------- Configuración puerto COM de datos de inclinación pendulo

COM_pend = 'COM7'

com_pend = serial.Serial(COM_pend,9600,8,stopbits=1)

com_pend.close()
if(not(com_pend.isOpen())): #si el puerto está cerrado, lo abre
    com_pend.open()
#--------


#-------- Configuración puerto COM de seguridad
COM_seg = 'COM5'

com_serial_seg = serial.Serial(COM_seg,115200,8,stopbits=1)

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
position = (int(ancho/2)-260,80)
position2 = (200,40)
position7 = (350,40)
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

#Configuraciones para las cámaras
cap_brazo = cv2.VideoCapture(1, cv2.CAP_DSHOW)#1
cap_brazo.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'UYVY'))
cap_brazo.set(cv2.CAP_PROP_FRAME_WIDTH, ancho)
cap_brazo.set(cv2.CAP_PROP_FRAME_HEIGHT,alto)
#cap_brazo.set(cv2.CAP_PROP_FPS,60)

cap_pend = cv2.VideoCapture(2, cv2.CAP_DSHOW)#2
cap_pend.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'UYVY'))
cap_pend.set(cv2.CAP_PROP_FRAME_HEIGHT,alto)
cap_pend.set(cv2.CAP_PROP_FRAME_WIDTH, ancho)
cap_pend.set(cv2.CAP_PROP_FPS,60)

class coordenadas_mask:
    def __init__(self):
    #iniciar atributos vacíos o con valores nulos
        self.x = (0,0) #(x1,x2)
        self.y = (0,0) #(y1,y2)
    def guardar(self,x,y):
        self.x = x    #(x1,x2)
        self.y = y    #(y1,y2)
        
def encontrar_puntob(img2,p_ini,flag_cal,tipo): #frame,flag calibración y el tipo, o sea si es brazo o péndulo
    """
    Encuentra la ubicación del punto blanco, según si está en estado de calibración o en modo de funcionamiento normal.
    En el modo de calibración, se utilizan máscaras seleccionadas desde barras deslizantes para ubicar la posición de las mismas.
    Luego, según la calibración sigue el punto blanco de interés. Y si lo pierde, activa un flag de seguridad para detener el movimiento.
    
    Métodos utilizados:
        *Calibración: Transformada circular de Hough, con una previa umbralización normal.
        *Modo normal: Obtener el contorno con el modo más sencillo para ubicar el centro del punto de interés. Además, se utiliza para obtener el área
        así de esta forma, saber cuando se pierde y haya detectado otra cosa que no sea el punto seguido.
    
    Parameters
    ----------
    img2: Matriz de 3 dimensiones, ya que es una copia del frame en color.
    flag_cal: Parámetro de entrada que le hace saber si ya está calibrado o no
    tipo: Indica a qué se hace referencia, si al brazo o al péndulo. Según 0 y 1.
    
    Returns
    -------
    Devuelve una tupla con el punto de referencia encontrado, el punto blanco actual y la seguridad
    """



    #global x1,x2,y1,y2 #guardo la última vez en donde estuvo el punto blanco
    img = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    mask = np.zeros(img.shape[:2], np.uint8)
    p_ref = (0,0)
    p_blanco = (0,0)
    seg = 0
    
    
    
    
    if not(flag_cal): #Cuando no está calibrado
        
        if(not (tipo)): #Si se trata del brazo
            #Obtener las posiciones actuales de los 3 Trackbars
            x_ini_mask = cv2.getTrackbarPos('X_i_brazo', 'Mask_brazo')
            x_fin_mask = cv2.getTrackbarPos('X_f_brazo', 'Mask_brazo')
            y_ini_mask = cv2.getTrackbarPos('Y_i_brazo', 'Mask_brazo')
            y_fin_mask = cv2.getTrackbarPos('Y_f_brazo', 'Mask_brazo')
            desplazamiento_mask = cv2.getTrackbarPos('Copia Desplazada', 'Mask_brazo')
            c = y_fin_mask+desplazamiento_mask
            d = (2*y_fin_mask) + desplazamiento_mask - y_ini_mask
            mask_brazo.guardar((x_ini_mask,x_fin_mask),(c,d)) #Guarda en la instancia "mask_brazo" las posiciones de las máscaras
        else: #si se trata del péndulo
            #Obtener las posiciones actuales de los 3 Trackbars
            x_ini_mask = cv2.getTrackbarPos('X_i_pend', 'Mask_pend')
            x_fin_mask = cv2.getTrackbarPos('X_f_pend', 'Mask_pend')
            y_ini_mask = cv2.getTrackbarPos('Y_i_pend', 'Mask_pend')
            y_fin_mask = cv2.getTrackbarPos('Y_f_pend', 'Mask_pend')
            desplazamiento_mask_y = -1*cv2.getTrackbarPos('Copia Y', 'Mask_pend')
            desplazamiento_mask_x = cv2.getTrackbarPos('Copia X', 'Mask_pend')
            a = x_ini_mask + desplazamiento_mask_x 
            b = x_fin_mask + desplazamiento_mask_x
            c = y_fin_mask+desplazamiento_mask_y
            d = (2*y_fin_mask) + desplazamiento_mask_y - y_ini_mask
            mask_pend.guardar((x_ini_mask,x_fin_mask),(c,d)) #Guarda en la instancia "mask_pend" las posiciones de las máscaras
            print("a,b",a,b)
        #a = y_fin_mask+desplazamiento_mask
        #b = (2*y_fin_mask) + desplazamiento_mask - y_ini_mask
        
        x1 = x_ini_mask
        x2 = x_fin_mask
        y1 = c
        y2 = d
        
        #print("x1,x,2:",x1,x2)
        #print("y1,y,2:",y1,y2)
        
        
        mask[y_ini_mask:y_fin_mask,x_ini_mask:x_fin_mask] = 255
        if (tipo):
            mask[c:d,a:b] = 255
        elif (tipo == 0): 
            mask[c:d,x_ini_mask:x_fin_mask] = 255
        
        img = cv2.bitwise_and(mask, img)
        #img = cv2.bitwise_and(mask2, img)
        
        #binarización OTSU
        #_,binarizado = cv2.threshold(img, 0,255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)
        _,binarizado = cv2.threshold(img,75,255,cv2.THRESH_BINARY)
        
        
        #Dilatación para agrandar los puntos blancos
        kernel = np.ones((5,5),np.uint8)
                
        #if(tipo or not tipo):binarizado = cv2.dilate(binarizado, kernel, iterations = 1)
        #img = cv2.GaussianBlur(img,(9,9),0)
        
        #circulos = cv2.HoughCircles(binarizado, cv2.HOUGH_GRADIENT, dp = 2, minDist=1, param1=90,param2=70,minRadius=10,maxRadius=40)
        print('\n')
        #print(circulos)
        #print(len(circulos[0,:]))
        if not tipo: #si es para el brazo
            _,binarizado = cv2.threshold(img,75,255,cv2.THRESH_BINARY)
        
        
            #Dilatación para agrandar los puntos blancos
            kernel = np.ones((5,5),np.uint8)
                
            #if(tipo or not tipo):binarizado = cv2.dilate(binarizado, kernel, iterations = 1)
            circulos = cv2.HoughCircles(binarizado, cv2.HOUGH_GRADIENT, dp = 2, minDist=50, param1=90,param2=7, minRadius=1,maxRadius=7)
            if circulos is not(None):
                
                circulos = np.uint16(np.around(circulos))
                
                binarizado = cv2.cvtColor(binarizado,cv2.COLOR_GRAY2BGR)
                if(len(circulos[0,:]) == 2):
                    #print(circulos[0,0,0:2],circulos[0,1,0:2])
                    
                    if(not(tipo)): #Si tipo = 0, entonces se calibra para el brazo
                        print("Calibracion para brazo")    
                        if(circulos[0,0,1] < circulos[0,1,1]): #Si el primer elemento encontrado es el punto de referencia
                            p_ref = circulos[0,0,0],circulos[0,0,1]        
                            p_blanco = circulos[0,1,0],circulos[0,1,1]
                        else: #si el primer elemento encontrado es el punto blanco
                            p_blanco = circulos[0,0,0],circulos[0,0,1]        
                            p_ref = circulos[0,1,0],circulos[0,1,1]
                    else: #Se calibra para el péndulo
                        print("Calibracion para pendulo")  
                        
                        if(circulos[0,0,1] > circulos[0,1,1]): #Si el primer elemento encontrado es el punto de referencia
                            p_ref = circulos[0,0,0],circulos[0,0,1]        
                            p_blanco = circulos[0,1,0],circulos[0,1,1]
                        else: #si el primer elemento encontrado es el punto blanco
                            p_blanco = circulos[0,0,0],circulos[0,0,1]        
                            p_ref = circulos[0,1,0],circulos[0,1,1]
                            
                    
                    for i in circulos[0,:]:
                      # draw the outer circle
                      cv2.circle(binarizado,(i[0],i[1]),i[2],(0,255,0),2)
                      cv2.circle(img2,(i[0],i[1]),i[2],(0,255,0),2)
                      # draw the center of the circle
                      cv2.circle(binarizado,(i[0],i[1]),2,(0,0,255),3)
                      cv2.circle(img2,(i[0],i[1]),2,(0,0,255),3)
        else: #si es para el péndulo
            umbral,binarizado = cv2.threshold(img, 50,255, cv2.THRESH_BINARY) #original
            contornos,_ = cv2.findContours(binarizado, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
            binarizado = cv2.cvtColor(binarizado,cv2.COLOR_GRAY2BGR)
        
            for c in contornos:
                
                area = cv2.contourArea(c)
                print("area:",area)
                #print("tipo:",tipo)
                
                
                if(area <= 45 and area >= 34):
                    M = cv2.moments(c)
                    # if (M["m00"]==0): M["m00"]=1 #si el m00 es cero lo iguala a 1 para no dividir por 0
                    x = int(M["m10"]/M["m00"])
                    y = int(M['m01']/M['m00'])
                    p_ref = (x,y)
                    #print("Punto blanco:",p_blanco)
                    cv2.circle(img2, (x,y), 3, (0,255,0), -1)
                    cv2.circle(binarizado, (x,y), 3, (0,255,0), -1)
                    contorno = cv2.convexHull(c) #dibuja contorno aplicando cerco Convexo
                    cv2.drawContours(img2, [contorno], 0, (255,0,0), 3)
                    cv2.drawContours(binarizado, [contorno], 0, (255,0,0), 3)
        
                if(area <= 24 and area >= 17):
                    M = cv2.moments(c)
                    # if (M["m00"]==0): M["m00"]=1 #si el m00 es cero lo iguala a 1 para no dividir por 0
                    x = int(M["m10"]/M["m00"])
                    y = int(M['m01']/M['m00'])
                    p_blanco = (x,y)
                    #print("Punto blanco:",p_blanco)
                    cv2.circle(img2, (x,y), 3, (0,255,0), -1)
                    cv2.circle(binarizado, (x,y), 3, (0,255,0), -1)
                    contorno = cv2.convexHull(c) #dibuja contorno aplicando cerco Convexo
                    cv2.drawContours(img2, [contorno], 0, (255,0,0), 3)
                    cv2.drawContours(binarizado, [contorno], 0, (255,0,0), 3)
        cv2.imshow('img', img)
            
        
    #dst2 = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 3)
    #cv2.imshow()
    else:
        
        print("\n")
        
        #Esta invocación es para usar los valores guardados para ubicar la posición de la máscara
        
        x1,x2 = mask_brazo.x if tipo == 0 else mask_pend.x #Si es para brazo o para péndulo
        y1,y2 = mask_brazo.y if tipo == 0 else mask_pend.y #Si es para brazo o para péndulo
       
        
    
        
        mask[y1:y2,x1:x2] = 255
        img = cv2.bitwise_and(mask, img)
        
        #binarización OTSU
        #_,binarizado = cv2.threshold(img, 0,255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)
        
        if(not tipo): #si es para el brazo
            _,binarizado = cv2.threshold(img, 130,255, cv2.THRESH_BINARY)
        else: #si es para el péndulo
            #umbral,binarizado = cv2.threshold(img, 0,255, cv2.THRESH_BINARY+cv2.THRESH_OTSU)
            umbral,binarizado = cv2.threshold(img, 50,255, cv2.THRESH_BINARY) #original
            
        
        #Dilatación para agrandar los puntos blancos
        kernel = np.ones((5,5),np.uint8)
        #binarizado = cv2.dilate(binarizado, kernel, iterations = 1)
        #img = cv2.GaussianBlur(img,(9,9),0)
        
        #----------------Búsqueda del punto blanco con contorno y momentos
        
        contornos,_ = cv2.findContours(binarizado, cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        binarizado = cv2.cvtColor(binarizado,cv2.COLOR_GRAY2BGR)
        
        for c in contornos:
            
            area = cv2.contourArea(c)
            #print("area:",area)
            #print("tipo:",tipo)
            
            
            if(area <= 35 and area > 0):
                seg = 1
                M = cv2.moments(c)
                # if (M["m00"]==0): M["m00"]=1 #si el m00 es cero lo iguala a 1 para no dividir por 0
                x = int(M["m10"]/M["m00"])
                y = int(M['m01']/M['m00'])
                p_blanco = (x,y)
                #print("Punto blanco:",p_blanco)
                cv2.circle(img2, (x,y), 3, (0,255,0), -1)
                cv2.circle(binarizado, (x,y), 3, (0,255,0), -1)
                contorno = cv2.convexHull(c) #dibuja contorno aplicando cerco Convexo
                cv2.drawContours(img2, [contorno], 0, (255,0,0), 3)
                cv2.drawContours(binarizado, [contorno], 0, (255,0,0), 3)
            else:
                #seg = 0
                #if tipo == 1:
                    #print("area:",area)
                    #print("umbral",umbral)
                p_blanco = p_ini
                cv2.circle(img2, (p_blanco), 3, (0,255,0), -1)
                cv2.circle(binarizado, (p_blanco), 3, (0,255,0), -1)
        #---------------
        
        #------------ seguir el punto blanco
        if(seg):
            tolerancia = 10
            x1 = p_blanco[0] - int(tolerancia*1.5) if tipo == 0 else p_blanco[0] - int(tolerancia*2.5)
            x2 = p_blanco[0] + int(tolerancia*1.5) if tipo == 0 else p_blanco[0] + int(tolerancia*2.5)
            y1 = p_blanco[1] - int(tolerancia*0.75) if tipo == 0 else p_blanco[1] - int(tolerancia*0.9)
            y2 = p_blanco[1] + int(tolerancia*1.5) if tipo == 0 else p_blanco[1] + int(tolerancia*1.75)
            
        else:
            tolerancia = 10
            x1 = p_ini[0] - int(tolerancia/2)
            x2 = p_ini[0] + int(tolerancia/2)
            y1 = p_ini[1] - tolerancia
            y2 = p_ini[1] + tolerancia
        
        #Esto es para guardar la nueva posición de la máscara
        mask_brazo.guardar((x1,x2), (y1,y2)) if tipo == 0 else mask_pend.guardar((x1,x2), (y1,y2))
        
        #if tipo == 1: cv2.imshow('img',img)
        
        #if(not(tipo)): mask_brazo.guardar((x1,x2), (y1,y2)) #Si es para el brazo
        #else: mask_pend.guardar((x1,x2), (y1,y2)) #Si es para el péndulo
        
        
    ventana = 'Mask_brazo' if tipo == 0 else 'Mask_pend'
    
    
    if(flag_cal):
        cv2.circle(mask, p_blanco, 3, (0,255,0), -1)
        #mask =cv2.cvtColor(mask,cv2.COLOR_GRAY2BGR)
        #img2 = cv2.bitwise_or(mask,img2)
        #cv2.imshow('copia',img2)
        
    #print("Ventana",ventana)    
    #cv2.imshow('binarizado', binarizado)
    cv2.imshow(ventana, mask)
    
    return p_ref,p_blanco,seg   #retorna el punto de referencia, es decir el superior para calibración, punto blanco actual, y seguridad    


def calcular_cat(p_blanco,p_ref,p_ini,redondeo):
    """
    Calcula los valores de cat_op y cat_ady basados en los parámetros proporcionados y calcula el ángulo en radianes y grados.

    Parameters
    ----------
    p_blanco : Tupla (x, y) del punto blanco (float, float)..
    p_ref : Tupla (x, y) del punto de referencia (float, float).
    p_ini : Tupla (x, y) del punto inicial (float, float).
    redondeo : Número de decimales para redondear el ángulo (int).

    Returns
    -------
    Una tupla con los valores del ángulo en radianes y grados redondeados.
    """
    # Calcula cat_ady basado en la diferencia en la coordenada y
    cat_ady = abs(int(p_blanco[1]) - int(p_ref[1]))
    
    # Inicializa cat_op
    #cat_op = 0

    # Lógica para calcular cat_op
    """
    if p_ini[0] < p_ref[0]: #Si el punto inicial está a la izquierda del centro de la imagen respecto al punto de referencia
        if p_ini[0] <= p_blanco[0] and p_blanco[0] < p_ref[0]: #Si el punto blanco que buscamos está entre el punto inicial y la mitad de imagen
            cat_op = (int(p_ref[0]) - int(p_ini[0])) - (int(p_ref[0]) - int(p_blanco[0]))
        elif p_blanco[0] >= p_ref[0]: #Si el punto blanco pasa la mitad derecha de la imagen
            cat_op = (int(p_ref[0]) - int(p_ini[0])) + (int(p_blanco[0]) - int(p_ref[0]))
        else: #Si el punto blanco está en la mitad izquierda de la imagen
            cat_op = (int(p_ref[0]) - int(p_blanco[0])) - (int(p_ref[0]) - int(p_ini[0]))
            cat_op *= -1
    else: #O sea si p_ini[0] >= p_ref[0] quiere decir si el punto inicial está a la derecha del centro de la imagen respecto al punto de referencia
        if p_ini[0] >= p_blanco[0] and p_blanco[0] > p_ref[0]: #Si el punto blanco que buscamos está entre el punto inicial y la mitad de imagen
            cat_op = (int(p_ini[0]) - int(p_ref[0])) - (int(p_blanco[0]) - int(p_ref[0]))
            cat_op *= -1
        elif p_blanco[0] >= p_ini[0]: #Si el punto blanco pasa la mitad derecha de la imagen y el punto inicial
            cat_op = (int(p_blanco[0]) - int(p_ref[0])) - (int(p_ini[0]) - int(p_ref[0]))
        else: #Si el punto blanco está en la mitad izquierda de la imagen
            cat_op = (int(p_blanco[0]) - int(p_ref[0])) + (int(p_ini[0]) - int(p_ref[0]))
    """
    #Lo que está comentado en comillas es como estaba antes, hay que probar en la facu este cambio cuando se vayan a hacer capturas        
    
    
    cat_op = int(p_blanco[0]) - int (p_ini[0]) #Si el punto blanco está a la derecha del punto inicial, es positivo, sino negativo
    
    # Calcula el ángulo en radianes y grados
    ang = np.arctan2(cat_op, cat_ady) # arctan2 maneja correctamente los cuadrantes
    ang_d = np.rad2deg(ang) # convierte a grados

    # Redondea los resultados
    ang = round(ang, redondeo)
    ang_d = round(ang_d, redondeo)

    return ang, ang_d



#Crea una función que no hace nada
def nada(x):
     pass




#--------Barras deslizantes
cv2.destroyAllWindows()
#Crear una ventana llamada canny
#cv2.namedWindow('Controles - Canny')
#cv2.resizeWindow('Controles - Canny', ancho,alto)

cv2.namedWindow('Mask_brazo')
cv2.resizeWindow('Mask_brazo', ancho,alto)
cv2.namedWindow('Mask_pend')
cv2.resizeWindow('Mask_pend', ancho,alto)


cv2.createTrackbar('X_i_brazo', 'Mask_brazo', 227, ancho, nada)
cv2.createTrackbar('X_f_brazo', 'Mask_brazo', 235, ancho, nada)#252
cv2.createTrackbar('Y_i_brazo', 'Mask_brazo', 239, alto, nada)#38
cv2.createTrackbar('Y_f_brazo', 'Mask_brazo', 253, alto, nada)#60
cv2.createTrackbar('Copia Desplazada', 'Mask_brazo', 114, alto, nada)#128


cv2.createTrackbar('X_i_pend', 'Mask_pend', 302, ancho, nada)
cv2.createTrackbar('X_f_pend', 'Mask_pend', 309, ancho, nada)#252
cv2.createTrackbar('Y_i_pend', 'Mask_pend', 369, alto, nada)#38
cv2.createTrackbar('Y_f_pend', 'Mask_pend', 380, alto, nada)#60
cv2.createTrackbar('Copia Y', 'Mask_pend', 338, alto, nada)#128
cv2.createTrackbar('Copia X', 'Mask_pend', 0, alto, nada)

#cv2.destroyWindow('Mask_pend')

#cv2.namedWindow("frame_brazo")
#cv2.namedWindow("frame_pend")
#cv2.createTrackbar('Rot(-d)', 'frame',0,90,nada)

#-------- Fin barras deslizantes

ciclo_ini = cv2.getTickCount()
f_anterior = np.zeros([360,640,3], np.uint8) #Cambiar por los valores correspondientes (480,640)

mask_pend = coordenadas_mask()
mask_brazo = coordenadas_mask()


while(1):
   
  # Take each frame
  ret, frame_brazo = cap_brazo.read() #COMENTADO SOLAMENTE PARA PRUEBA CON IMÁGENES ESTÁTICAS
  ret2, frame_pend = cap_pend.read() #COMENTADO SOLAMENTE PARA PRUEBA CON IMÁGENES ESTÁTICAS
  
  frame_brazo = cv2.rotate(frame_brazo, cv2.ROTATE_90_CLOCKWISE)
  #frame2 = cv2.imread('3-9-24/Pendulo_1.JPG',1)
  #frame2 = cv2.imread('monedas_4x8.jpg',1)
  if(ret and ret2): #Si no hay fallo en capturar el frame
      
      if calib < 2 :
        com_serial_seg.write(str(0).encode() + b'\r\n')
        
        #La idea es que vayan apareciendo las ventanas de calibración de los correspondientes ejes. Pero uno a la vez. Una vez que todos estén calibrados, se procede al modo "automático".
        
        if(calib == 0):  
            
            p_ref_brazo,p_ini_brazo,_ = encontrar_puntob(frame_brazo,(0,0),flag_cal=0,tipo= 0) 
            #Tipo en 1 es péndulo, en 0 es brazo
            print("Punto de referencia brazo: ",p_ref_brazo)
            print("Punto inicial brazo: ",p_ini_brazo)
            cv2.putText(frame_brazo,'Pulse "c" para calibrar ',position,font,fontScale,fontColor,thick) #Comentado únicamente para imágenes estáticas
            cv2.imshow('frame_brazo', frame_brazo)
            
        if(calib == 1):
            
            if(cv2.getWindowProperty('frame_brazo', cv2.WND_PROP_VISIBLE) >= 1):
                cv2.destroyWindow('frame_brazo')
                cv2.destroyWindow('Mask_brazo')
                
            p_ref_pend,p_ini_pend,_ = encontrar_puntob(frame_pend,(0,0),flag_cal=0,tipo= 1) 
            #Tipo en 1 es péndulo, en 0 es brazo
            print("Punto de referencia: ",p_ref_pend)
            print("Punto inicial: ",p_ini_pend)
            cv2.putText(frame_pend,'Pulse "c" para calibrar ',position,font,fontScale,fontColor,thick) #Comentado únicamente para imágenes estáticas
            cv2.imshow('frame_pend', frame_pend)
        
        
      else:
#         Comentar cuando no se utilicen imágenes estáticas
          """
          frame = frame2.shape
          Ang_rot = 1*cv2.getTrackbarPos('Rot(-d)', 'frame')      
          centro = p_ref
#          #print("Centro de rotacion: ",centro)
          matriz_rot = cv2.getRotationMatrix2D(center = centro, angle = Ang_rot, scale = 1)
          frame = cv2.warpAffine(src=frame2, M = matriz_rot,dsize=(frame2.shape[1],frame2.shape[0]))
          """
                   
          
          _,p_blanco_brazo,seg_brazo = encontrar_puntob(frame_brazo,p_ini_brazo,flag_cal=1,tipo = 0)
          #Si ya está calibrado, devuelve la posición del punto blanco del brazo
          
          _,p_blanco_pend,seg_pend = encontrar_puntob(frame_pend,p_ini_pend,flag_cal=1,tipo = 1)
          #Si ya está calibrado, devuelve la posición del punto blanco del péndulo
          
          
          #Imprime las líneas y busca los puntos blancos
          if(seg_brazo):cv2.line(frame_brazo, p_ref_brazo, p_blanco_brazo, (0,255,255),2)
          cv2.line(frame_brazo, p_ref_brazo, p_ini_brazo, (0,255,255),2)
          
          #Imprime las líneas y busca los puntos blancos
          if(seg_pend):cv2.line(frame_pend, p_ref_pend, p_blanco_pend, (0,255,255),2)
          cv2.line(frame_pend, p_ref_pend, p_ini_pend, (0,255,255),2)
          
          #print("\n")
          #print("p_ini_brazo",p_ini_brazo)
          #print("p_ref_brazo",p_ref_brazo)
          
          #Calcula el ángulo de inclinación del brazo
          theta,theta_d = calcular_cat(p_blanco_brazo, p_ref_brazo, p_ini_brazo, redondeo = 2)
          
          #Calcula el ángulo de inclinación del péndulo
          alfa,alfa_d = calcular_cat(p_blanco_pend, p_ref_pend, p_ini_pend, redondeo = 2)
                   
          print("Ángulo de inclinación brazo (rad):",theta)
          print("Ángulo de inclinación brazo (deg):",theta_d)
          #com_brazo.write(str(theta).encode() + b'\r\n')
          
          #print("Ángulo de inclinación pendulo (rad):",alfa)
          #print("Ángulo de inclinación pendulo (deg):",alfa_d)
          #com_pend.write(str(alfa).encode() + b'\r\n')
              
          if(not seg_brazo or not seg_pend): 
              flag_seg = 0 #Cuando no hay "seguridad", envía constantemente el 0, para asegurarse que no funcione el motor
              com_serial_seg.write(str(seg_brazo*seg_pend).encode() + b'\r\n')
              com_brazo.write(str(0).encode() + b'\r\n')
              com_pend.write(str(0).encode() + b'\r\n')
              falla = "Brazo" if seg_brazo == 0 else "Pendulo"
              print("FALLA DE SEGURIDAD en ",falla)
                  
          else:
              if(flag_seg):
                  com_brazo.write(str(theta).encode() + b'\r\n') 
                  com_pend.write(str(alfa).encode() + b'\r\n')
              
          #Si no hay seguridad, es decir que perdió el punto blanco, entonces envía un cero para detener el uso del motor.
          #Pero en cambio si seg es 1, entonces manda habilitar el uso del motor.
              
          
         
          #cv2.putText(frame, "Angulo:"+str(theta)+"Deg", position2, font, fontScale, fontColor,thick)
          cv2.putText(frame_brazo, "Angulo:"+str(theta)+"Rad", position2, font, fontScale, fontColor,thick) #Comentado para sacar capturas
          cv2.putText(frame_pend, "Angulo:"+str(alfa_d)+"Deg", position7, font, fontScale, fontColor,thick) #Comentado para sacar capturas
          
          
         
          #cv2.imshow('frame_brazo',frame_brazo) #COMENTAR CUANDO NO SE USEN IMÁGENES ESTÁTICAS
      #rota la imagen
      
      
        
          ciclos_trans = cv2.getTickCount() - ciclo_ini #Diferencia entre ciclo transcurrido y ciclo inicial hasta que se procesó el frame
          frec = cv2.getTickFrequency()
          elap = ciclos_trans/frec
          
          elap_viejo = elap
          cuadros+=1 #aumento la cuenta de la cantidad de cuadros  
          
          #cv2.putText(frame, "T_min(ms):"+str(tiempo_frame_min), position5, font, fontScale*0.5, fontColor,thick-1)
          #cv2.putText(frame, "T_max(ms):"+str(tiempo_frame_max), position6, font, fontScale*0.5, fontColor,thick-1)
          #cv2.putText(frame, "T_frame(ms):"+str(tiempo_frame), position4, font, fontScale*0.5, fontColor,thick-1)
          
          #print("seg: ",seg_brazo)
          #print("flag_seg: ",flag_seg)
          
          if elap > 1:
              elap_viejo = 0
              fps = int(cuadros/elap)
              cuadros = 0
              tiempo_frame_min = 1000
              tiempo_frame_max = 0
              
              if(seg_brazo and flag_seg):
                  com_serial_seg.write(str(seg_brazo*seg_pend).encode() + b'\r\n')
                  print("seguridad: ",seg_brazo*seg_pend)
              ciclo_ini = cv2.getTickCount()
              
          
          
          cv2.putText(frame_brazo, "FPS:"+str(fps), position3, font, fontScale, fontColor,thick)      #comentado para sacar capturas
          cv2.putText(frame_pend, "FPS:"+str(fps), position3, font, fontScale, fontColor,thick)      #comentado para sacar capturas
          cv2.imshow('frame_brazo',frame_brazo) # COMENTADO ÚNICAMENTE PARA IMÁGENES ESTÁTICAS
          cv2.imshow('frame_pend',frame_pend) # COMENTADO ÚNICAMENTE PARA IMÁGENES ESTÁTICAS
          
          
          #cv2.imshow('frame2',frame2) # comentar cuando no se usen imágenes estáticas
      
     
      k = cv2.waitKey(1); 0xFF
      # si pulsa q se rompe el ciclo
      if k == ord("q"):
        com_brazo.write(str(0).encode() + b'\r\n')
        com_pend.write(str(0).encode() + b'\r\n')
        com_serial_seg.write(str(0).encode() + b'\r\n')
        break
      if k == ord("c"):
          calib += 1
          if(calib == 2):
              print("Posición inical calibrada")
              flag_seg = 1
              cv2.destroyAllWindows()
              #cv2.destroyWindow('img')
      if k == ord("r") and not flag_seg:
          flag_seg = 1
          com_serial_seg.write(str(seg_brazo*seg_pend).encode() + b'\r\n')
          print("Reset")
        
  else:
       print("Error en la o las cámaras :c")
       com_serial_seg.write(str(0).encode() + b'\r\n')
       break
       
cv2.destroyAllWindows()
com_brazo.close()
com_pend.close()
com_serial_seg.close()