% Find desired poles
% Location of dominant poles along real-axis
sigma = zeta*wn;
% Location of dominant poles along img axis (damped natural freqency)
wd = wn*sqrt(1-zeta^2);
% Desired poles (-30 and -40 are given)
DP = [-sigma+j*wd, -sigma-j*wd, p3, p4];    
%
%% Find Tranformation Matrix W
% Characteristic equation: s^4 + a_4*s^3 + a_3*s^2 + a_2*s + a_1
% inverted pendulum characteristic equation: s^4 + 11.6*s^3 - 117.3*s^2 - 408.3*s
a = poly(A)
% 
% Companion matrices (Ac, Bc)
Ac = [  0 1 0 0;
        0 0 1 0;
        0 0 0 1;
        -a(5) -a(4) -a(3) -a(2)];
%
Bc = [0; 0; 0; 1];
%
% Controllability
T = ctrb(A,B);
% Controllability of companion matrices
Tc = ctrb(Ac,Bc);
%
% Transformation matrices
W = T*inv(Tc);
%
%% Find Gain
% Desired polynomial from desired poles in vector "DP" (found in
% setup_rotpen.m)
a_des = poly(DP);
% Companion control gains
k1c = a_des(5) - a(5);
k2c = a_des(4) - a(4);
k3c = a_des(3) - a(3);
k4c = a_des(2) - a(2);
% Companion state-feedback control gain
Kc = [k1c k2c k3c k4c]
% The students would enter the gain manually from their pre-lab as
% Kc = [ 19200 8286 1725 64 ];
% Convert back from companion form
K_manual = Kc*inv(W)
%
%% Closed-loop System Poles
% Find poles of closed-loop system. 
% Verify that they are the same as the desired poles.
cls_poles = eig(A-B*K_manual)
%%
