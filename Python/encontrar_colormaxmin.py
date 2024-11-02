import cv2
import numpy as np
import colorsys
 
"""
bgr = np.uint8([[[60,190,210]]])
hsv = cv2.cvtColor(bgr,cv2.COLOR_BGR2HSV)
print ("hsv",hsv)
"""
"""Con este código, busco la forma de obtener los colores RGB con el mouse
   click izquierdo: Valor BGR mínimo
   click derecho: Valor BGR máximo

ref: https://www.youtube.com/watch?v=7fgUnqe2x78
"""

lower_blue = np.array([30,50,35]) 
upper_blue = np.array([120,210,230])


alto = 480
ancho = 640
cap = cv2.VideoCapture(2, cv2.CAP_DSHOW) #fuerza a que se utilice esa cámara
cap.set(cv2.CAP_PROP_FRAME_WIDTH, ancho)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,alto)
cap.set(cv2.CAP_PROP_FPS,60)

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
    
    elif event == cv2.EVENT_LBUTTONDOWN:
        h_min = cv2.getTrackbarPos("h_min", "barra")
        s_min = cv2.getTrackbarPos("s_min", "barra")
        v_min = cv2.getTrackbarPos("v_min", "barra")
        print("Valor mínimo calibrado")
        print("(h,s,v) -> (",h_min,",",s_min,",",v_min,")")
        print("\n") 
        lower_blue = np.array([h_min,s_min,v_min]) 
        
    elif event == cv2.EVENT_RBUTTONDOWN:
        h_max = cv2.getTrackbarPos("h_max", "barra")
        s_max = cv2.getTrackbarPos("s_max", "barra")
        v_max = cv2.getTrackbarPos("v_max", "barra")
        print("Valor máximo calibrado")
        print("(h,s,v) -> (",h_max,",",s_max,",",v_max,")")
        print("\n") 
        upper_blue = np.array([h_max,s_max,v_max]) 
        
    """
    if event == cv2.EVENT_LBUTTONDOWN:
        b_min = frame[y,x,0]
        g_min = frame[y,x,1]
        r_min = frame[y,x,2]
        #entrada
        (r,g,b) = (r_min,g_min,b_min)
        #normalizo
        (r,g,b) = (r/255,g/255,b/255)
        #convierto a hsv 
        (h,s,v) = colorsys.rgb_to_hsv(r, g, b)
        #expandir a rango hsv
        (h,s,v) = (int(h*179),int(s*255),int(v*255))
        lower_blue = np.array([h,s,v]) 
        
        print("Valor azul mínimo:")
        print("(x,y) -> ","(",x,",",y,")")
        print("(b,g,r) -> (",b_min,",",g_min,",",r_min,")")
        print("(h,s,v) -> (",h,",",s,",",v,")")
        print("\n")
        
    elif event == cv2.EVENT_RBUTTONDOWN:
        b_max = frame[y,x,0]
        g_max = frame[y,x,1]
        r_max = frame[y,x,2]
        #entrada
        (r,g,b) = (r_max,g_max,b_max)
        #normalizo
        (r,g,b) = (r/255,g/255,b/255)
        #convierto a hsv 
        (h,s,v) = colorsys.rgb_to_hsv(r, g, b)
        #expandir a rango hsv
        (h,s,v) = (int(h*179),int(s*255),int(v*255))
        upper_blue = np.array([h,s,v]) 
        
        print("Valor azul máximo:")
        print("(x,y) -> ","(",x,",",y,")")
        print("(b,g,r) -> (",b_max,",",g_max,",",r_max,")")
        print("(h,s,v) -> (",h,",",s,",",v,")")
        print("\n")
    """
cv2.namedWindow("frame")
cv2.setMouseCallback("frame",Mouse)
"""
cv2.namedWindow("barra")
cv2.createTrackbar("h_min","barra",30,179,nada)
cv2.createTrackbar("s_min","barra",50,254,nada)
cv2.createTrackbar("v_min","barra",35,254,nada)

cv2.createTrackbar("h_max","barra",120,179,nada)
cv2.createTrackbar("s_max","barra",210,254,nada)
cv2.createTrackbar("v_max","barra",230,254,nada)
"""

while(1):
   
  # Take each frame
  ret, frame = cap.read()
  
  if(ret):
      cv2.imshow('frame',frame)
      k = cv2.waitKey(1); 0xFF
      # si pulsa q se rompe el ciclo
      if k == ord("q"):
        break
  else:
      print("Eror con la cámara")
      img = cv2.imread("gatito.jpg")
      cv2.imshow('gatito',img)
      k = cv2.waitKey(1); 0xFF
      if k == ord("q"):
        break
  
cap.release() 
cv2.destroyAllWindows()