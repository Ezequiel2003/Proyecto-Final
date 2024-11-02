import cv2
import numpy as np
import time
from matplotlib import pyplot as plt

#--------Variables auxiliares
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

alto = 480
ancho = 640


cont_45 = 0
cont_135 = 0
#-----------------------



def nothing(x):
     pass

cv2.destroyAllWindows()
#Crear una ventana llamada canny
cv2.namedWindow('Controles - Canny')
cv2.resizeWindow('Controles - Canny', ancho,alto)

cv2.namedWindow('Hough')
cv2.resizeWindow('Hough', ancho,alto)

cv2.namedWindow('Mask')
cv2.resizeWindow('Mask', ancho,alto)

#Crear las barras para los valores inferiores y superiores
cv2.createTrackbar('lower', 'Controles - Canny', 255, 255, nothing)
cv2.createTrackbar('upper', 'Controles - Canny', 255, 255, nothing)

cv2.createTrackbar('Thresh', 'Hough', 102, 255, nothing)
cv2.createTrackbar('Recta 45d', 'Hough', 0, 20, nothing) #Se puede elegir hasta 10 rectas
cv2.createTrackbar('Recta 135d', 'Hough', 0, 20, nothing) #Se puede elegir hasta 10 rectas
cv2.createTrackbar('Rotacion', 'Hough',0,90,nothing)

cv2.createTrackbar('Hab', 'Mask', 0, 1, nothing)
cv2.createTrackbar('X_ini', 'Mask', 211, ancho, nothing)
cv2.createTrackbar('X_final', 'Mask', 400, ancho, nothing)
cv2.createTrackbar('Y_ini', 'Mask', 70, alto, nothing)
cv2.createTrackbar('Y_final', 'Mask', 252, alto, nothing)





while True:
    pass
    img2 = cv2.imread('Prueba5.jpg',1)
    img = cv2.cvtColor(img2, cv2.COLOR_BGR2GRAY)
    mask = np.zeros(img.shape[:2], np.uint8)
    
    #Obtener las posiciones actuales de los 3 Trackbars
    x_ini_mask = cv2.getTrackbarPos('X_ini', 'Mask')
    x_fin_mask = cv2.getTrackbarPos('X_final', 'Mask')
    y_ini_mask = cv2.getTrackbarPos('Y_ini', 'Mask')
    y_fin_mask = cv2.getTrackbarPos('Y_final', 'Mask')
    hab_mask = cv2.getTrackbarPos('Hab', 'Mask')
    low = cv2.getTrackbarPos('lower', 'Controles - Canny')
    up = cv2.getTrackbarPos('upper', 'Controles - Canny')
    
    threshold = cv2.getTrackbarPos('Thresh', 'Hough')
    Ang_rot = -1*cv2.getTrackbarPos('Rotacion', 'Hough')
    
    
    centro =(int(ancho/2),int(alto/2))

    #Generar la matriz rotada
    #Nota: rota en contra de las agujas del reloj
    matriz_rot = cv2.getRotationMatrix2D(center = centro, angle = Ang_rot, scale = 1)

    #rota la imagen
    img = cv2.warpAffine(src=img, M = matriz_rot,dsize=(ancho,alto))
    img2 = cv2.warpAffine(src=img2, M = matriz_rot,dsize=(ancho,alto))
    
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
    
    A_45 = np.array([[],[],[]],dtype=np.uint8)
    A_135 = np.array([[],[],[]],dtype=np.uint8)
    
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
        
        print("Lines:",len(lines))
        for i in range(0, len(lines)):
            print("\n")
            print("i",i)
            rho = lines[i][0][0] #saca de la matriz "lines" el valor de rho y tita
            print("rho:",rho)
            theta = lines[i][0][1]
            theta_d = 180*theta/np.pi
            print("theta:", theta)
            print("theta_d:", theta_d)
            
            theta_tol = 3 #ángulo de tolerancia para que sea considerada como recta de interés
            theta_tol2 = 3
            
            if(abs(theta_d -45) <= theta_tol) :
                cont_45 += 1
                print("theta_d válido:", theta_d)
                
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
                print("theta_d válido:", theta_d)
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
                
                
                
        print("\n") 
        
        
        
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
            print("Coordenadas intersección ({},{}) \n".format(x_ini,y_ini))
            
            cv2.circle(img2, (x_ini,y_ini), 5, (0,0,255),-1)
            cv2.line(img2, (x_ini,0), (x_ini,alto), (0,255,255), 1, cv2.LINE_AA)    
                
        
           
        
    cv2.imshow('Ima_Original',img2)
    cv2.imshow('Mask', mask)
    cv2.imshow('Controles - Canny',edges)
    cv2.imshow('Rectas elegidasa para el centro',cedges2)
    cv2.imshow('Hough',cedges)
    
    #Si se presiona "ESC", se cierra la imagen, sino sigue trabajando
    k = cv2.waitKey(1) & 0xFF
    if(k == ord('q')):
        break

#cv2.waitKey(0)
cv2.destroyAllWindows()
