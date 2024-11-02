%% Se crea este script de prueba para calcular el controlador PD para el brazo del servo
% PD con LGR, por qué PD y no PI? Porque si, para probar. El PI es más
% "complicado". La ventaja del PD es que es más rápido, mientras que el PI es más estable

clc, clear all, close all
format long
%PD modificado 
%Utilizo la forma completa del controlador PD

% modificado -> C(z) = K (Z-alfa)/(Z)
% completa   -> C(z) = K (Z-alfa)/(Z-beta)

%----Datos
Ts = 1/60; %Por 60 FPS de la cámara
psi = 0.9; %No estoy seguro qué valor es el que conviene, o cómo saber cuál debería elegir
%wd = 100; %Acá igual
wd = 2 * pi * 50.0;
wn = wd/sqrt(1-psi^2);

%%
%----Planta
% salida angulo (posicion)
% Referencia: Fadali-Visioli pag 202 y Quanser
k=1.53 %Rescatado de los documentos de la materia. Hay que comprobarlo con el experimento
tau=0.025
Gs=tf([k],[tau 1 0])
Gz = c2d(Gs,Ts);
Gz = zpk(Gz)

%%
%----Polos deseados
z1 = exp(-psi*wn*Ts + j*wn*Ts*sqrt(1-psi^2))
% z2 = exp(-psi*wn*Ts - j*wn*Ts*sqrt(1-psi^2))
%----Grafico en lazo cerrado y sin G(z), para ver por dónde pasan los polos
%deseados
rlocus(Gz)
title("LGR sin controlador")
hold on
plot(z1,'bd')
%plot(z2,'bd')
%----Obtengo polos y ceros de Gz, con sus fases 
ceros_Gz = zero(Gz);
polos_Gz = pole(Gz);
fi_cero_Gz = angle(z1-ceros_Gz);
fi_polo1_Gz = angle(z1-polos_Gz(1));
fi_polo2_Gz = angle(z1-polos_Gz(2));
%deficiencia_angular = pi - angle(evalfr(Gz,z1))
%----fase y parte real de los valores del controlador
%% -----------------------------
%En caso que no se utilice la versión modificada
a = polos_Gz(2); %Anule uno de los polos de la planta
fi_a = angle(z1-a);
fi_beta = angle(evalfr(Gz,z1)) + fi_a -pi;
b = real(z1)- (imag(z1)/tan(fi_beta));
Dz = tf([1 -a],[1 -b],Ts)
%Ds = d2c(Dz)
%----------------------------
%% ------Calculo de los parametros del PD modificado
% b = 0;
% fi_beta = angle(z1-b)
% fi_alfa = -angle(evalfr(Gz,z1)) + fi_beta + pi;
% a = real(z1) - (imag(z1)/tan(fi_alfa));
% %----Creo el controlador
% Dz = tf([1 -a],[1 -b],Ts)
%%
%----Función de transferencia de lazo abierto
GLA = series(Dz,Gz);
%----Grafico para verificar si pasa por el LGR
figure,rlocus(GLA)
title("LGR con controlador")
hold on
plot(z1,'bd')
%plot(z2,'bd')
%----finalmente, obtener el valor de ganancia K
K = 1/abs(evalfr(GLA,z1))

%Extraigo los valores de las constantes del PD
%Dz_k = series(K,Dz) 
Dz_k = series(1,Dz) 
Dz_k = zpk(Dz_k)
D = pid(Dz_k)
%%
%----Respuesta al escalón y acción del controlador
n = 20;
r = ones(1,n);
nn = 1:n;
GLA_K = series(K,GLA); 
GLC = feedback(GLA_K,1);
escalon = lsim(GLC,r);

figure
plot (nn,escalon,'.')
hold on
plot(nn,r,'.')
grid on
legend("Respuesta al escalón","Escalón")
title("Respuesta al escalón")

figure
step(GLC)
title(['Wd = ',num2str(wd), ' psi = ',num2str(psi)])