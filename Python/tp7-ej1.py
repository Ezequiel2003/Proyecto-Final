"""
Segmentar las siguientes imagenes utilizando umbralizacion
adaptativa con las opciones Adaptive Thresh Mean y Adaptive Thresh Gaussian,
para el calculo del umbral. Mostrar las imagenes resultantes y comentar las
mejoras obtenidas con respecto al metodo de umbralizado global.
En caso de no conseguir resultados, realizar un filtrado previo para acondicionar la imagen.
"""
import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread("Prueba1.jpg",0)
img2 = cv2.imread("Prueba2.jpg",0)

"""
▪ ADAPTIVE_THRESH_MEAN_C: el valor umbral es equivalente al valor medio de los 
    pixeles vecinos. 
▪ ADAPTIVE_THRESH_GAUSSIAN_C: el valor de umbral es la suma ponderada de los 
    valores de pixeles en la vecindad. Los pesos están dados por una función gaussiana. 
▪ Block Size: Tamaño del área de los vecinos ▪ C – Es una constante que se puede 
    restar del cálculo del umbral medio o ponderado.
"""

#------------------Umbralizacion global
# cv2.threshold(src, thresh, maxval, type)
#Umbral de 100 para las dos
#ese guion bajo es para que no me tire basura, en este caso son umbral y umbral2
umbral,global_img1 = cv2.threshold(img, 120, 255, cv2.THRESH_TOZERO)
umbral2,global_img2 = cv2.threshold(global_img1, 120, 255, cv2.THRESH_BINARY)

#global_img1 = np.uint8(global_img1)

plt.close('all')

#plt.subplot(221),plt.title('Transformada original'),plt.imshow(magnitudFFT,cmap='gray')

plt.subplot(221), plt.title('Original img1'), plt.imshow(img, cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(222), plt.title('Umbralizacion global a img1'), plt.imshow(global_img1, cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(223), plt.title('Original img2'), plt.imshow(img2,cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(224), plt.title('Umbralizacion global a img2'), plt.imshow(global_img2, cmap='gray')
plt.xticks([]),plt.yticks([])
plt.show()

#---------Adaptive Thresh Gaussian
#Blocksize = 11 y C = 3, C es un offset digamos
adapt_gauss_img1 = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY_INV, 11, 3)
adapt_gauss_img2 = cv2.adaptiveThreshold(img2, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 3)

plt.figure()
plt.subplot(221), plt.title('Original img1'), plt.imshow(img, cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(222), plt.title('Umbralizacion adaptativa gaussiana a img1'), plt.imshow(adapt_gauss_img1, cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(223), plt.title('Original img2'), plt.imshow(img2,cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(224), plt.title('Umbralizacion adaptativa gaussiana a img2'), plt.imshow(adapt_gauss_img2, cmap='gray')
plt.xticks([]),plt.yticks([])
plt.show()

#---------Adaptive Thresh mean
#Blocksize = 11 y C = 3, C es un offset digamos
adapt_mean_img1 = cv2.adaptiveThreshold(img, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY_INV, 11, 3)
adapt_mean_img2 = cv2.adaptiveThreshold(img2, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, 11, 3)

plt.figure()
plt.subplot(221), plt.title('Original img1'), plt.imshow(img, cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(222), plt.title('Umbralizacion adaptativa media a img1'), plt.imshow(adapt_mean_img1, cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(223), plt.title('Original img2'), plt.imshow(img2,cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(224), plt.title('Umbralizacion adaptativa media a img2'), plt.imshow(adapt_mean_img2, cmap='gray')
plt.xticks([]),plt.yticks([])
plt.show()


laplacian = cv2.Laplacian(global_img1,cv2.CV_64F)
sobel_diag = cv2.Laplacian(global_img2,cv2.CV_64F)

#Lo calculo con flotante, para que tenga mejor resultado y luego le saco
#el valor absoluto para representarlo con uint8

laplacian_8u = np.uint8(np.absolute(laplacian))
sobeldiag_8u = np.uint8(np.absolute(sobel_diag))


#plt.close('all')

plt.figure()
plt.subplot(221),plt.title("Original"), plt.imshow(img,cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(222),plt.title("Laplaciano"), plt.imshow(laplacian_8u,cmap='gray')
plt.xticks([]),plt.yticks([])
plt.subplot(223),plt.title("Sobel diag"), plt.imshow(sobeldiag_8u,cmap='gray')
plt.xticks([]),plt.yticks([])

"""
Se puede observar que con el umbral fijo, habrán partes del objeto que no se verán correctamente
debido a los cambios de iluminación y también muestra como objeto algunas sombras

mientras que las adaptativas distinguen el objeto, importante a destacar que para el caso de
la media, en la imagen de la T, también distingue como objeto, la sombra producida por este objeto
y el contorno es mucho más grueso

en cambio, para el gaussiano se distingue con bastante precision el objeto del fondo

"""