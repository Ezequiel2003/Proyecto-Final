import colorsys
import numpy as np
import cv2 as cv2

lower_blue = np.array([30,50,35]) #hsv

bgr = np.uint8([[[60,190,210]]])
hsv = cv2.cvtColor(bgr,cv2.COLOR_BGR2HSV)
 
print ("hsv",hsv)

#hsv2 = np.array([[[35, 50, 20]]],np.uint8)
bgr_out = cv2.cvtColor(hsv,cv2.COLOR_HSV2BGR)
print ("bgr_out",bgr_out)



#----Prueba de conversión rápida
#entrada
(r,g,b) = (210,190,60)
#normalizo
(r,g,b) = (r/255,g/255,b/255)
#convierto a hsv 
(h,s,v) = colorsys.rgb_to_hsv(r, g, b)
#expandir a rango hsv
(h,s,v) = (int(h*179),int(s*255),int(v*255))
lala = np.array([h,s,v]) 
print("lala",lala)


imagen = cv2.imread("Prueba.png",1)
cv2.imshow("imagen", imagen)
k = cv2.waitKey(1); 0xFF
# si pulsa q se rompe el ciclo
if k == ord("q"):
    cv2.destroyAllWindows()
