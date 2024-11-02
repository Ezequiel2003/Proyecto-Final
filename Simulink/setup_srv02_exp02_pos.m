%% SETUP_SRV02_EXP02_POS
%
% Sets the necessary parameters to run the SRV02 Experiment #2: Position
% Control laboratory using the "s_srv02_pos" and "q_srv02_pos" Simulink 
% diagrams.
% 
% Copyright (C) 2010 Quanser Consulting Inc.
%
%clear all;
%
%% SRV02 Configuration
% External Gear Configuration: set to 'HIGH' or 'LOW'
EXT_GEAR_CONFIG = 'HIGH';
% Encoder Type: set to 'E' or 'EHR'
ENCODER_TYPE = 'E';
% Is SRV02 equipped with Tachometer? (i.e. option T): set to 'YES' or 'NO'
TACH_OPTION = 'YES';

% Type of Load: set to 'NONE', 'DISC', or 'BAR'
LOAD_TYPE = 'NONE';     %Configurada en NONE para planta ball and beam  
% LOAD_TYPE = 'DISC'; 

% Amplifier Gain: set VoltPAQ amplifier gain to 1
K_AMP = 1;
% Power Amplifier Type: set to 'VoltPAQ', 'UPM_1503', 'UPM_2405', or 'Q3'
AMP_TYPE = 'VoltPAQ';
% Digital-to-Analog Maximum Voltage (V)
VMAX_DAC = 10;
%
%% Lab Configuration
% Type of controller: set it to 'AUTO', 'MANUAL'
% CONTROL_TYPE = 'AUTO_PIV';   
% CONTROL_TYPE = 'AUTO_PV';   
CONTROL_TYPE = 'MANUAL';            % Se aplica para la planta ball and beam
%
%% Control specifications
if strcmp(AMP_TYPE,'Q3')
    % Peak time (s)
    tp = 0.2;
    % Percentage overshoot (%)    
    PO = 5.0; % 5.0
    % Slope of ramp reference (rad/s)
    R0 = 2*pi/3 / (1/0.8/2);
    % Integral time to find integral gain (s)
    ti = 0.5;
else
    % Peak time (s)
    tp = 0.20;
    % Percentage overshoot (%)
    PO = 5.0;
    % Slope of ramp reference (rad/s)
    R0 = 2*pi/3 / (1/0.8/2);
    % Integral time to find integral gain (s)
    ti = 1.0;
end
%
%% SRV02 System Parameters
% Set Model Variables Accordingly to the USER-DEFINED SRV02 System Configuration
% Also Calculate the SRV02 Model Parameters and 
% Write them to the MATLAB Workspace (to be used in Simulink diagrams)
[ Rm, kt, km, Kg, eta_g, Beq, Jm, Jeq, eta_m, K_POT, K_TACH, K_ENC, VMAX_AMP, IMAX_AMP ] = config_srv02( EXT_GEAR_CONFIG, ENCODER_TYPE, TACH_OPTION, AMP_TYPE, LOAD_TYPE );
%
%% Filter Parameters
% High-pass filter in PD control used to compute velocity
% Cutoff frequency (rad/s)
wcf = 2 * pi * 140.0;
%wcf = 2 * pi * 50.0;
% Damping ratio
zetaf = 0.9;
% Encoder high-pass filter used to compute velocity
% Cutoff frequency (rad/s)
wcf_e = 2 * pi * 140.0;
%wcf_e = 2 * pi * 50.0;
% Damping ratio
zetaf_e = 0.9;
%
%% Calculate PIV Control Gains: Introducir los valores de kp, kv y ki manualmente

if strcmp ( CONTROL_TYPE , 'MANUAL' )
    % Load model parameters based on SRV02 configuration.
    [K,tau] = d_model_param(Rm, kt, km, Kg, eta_g, Beq, Jeq, eta_m, AMP_TYPE);
    % PIV control gains 
    %kp = 7.8173; %Completar aqui el kp segun las especificaciones de
    %diseño. Original
    kp = 2;
    
    %kv = -0.1564; %Completar aqui el Kv segun las especificaciones de diseño. Original
    kv = -0.01564;
    
    %ki = 38.9; %original
    ki = 15;
    %Completar aqui el kp segun las especificaciones de diseño
    %Completar aqui el Kv segun las especificaciones de diseño
    
    
elseif strcmp ( CONTROL_TYPE , 'AUTO_PV' )
    % Load model parameters based on SRV02 configuration.
    [K,tau] = d_model_param(Rm, kt, km, Kg, eta_g, Beq, Jeq, eta_m, AMP_TYPE);
    % Calculate PV control gains given specifications.
    [ kp, kv ] = d_pv_design( K, tau, PO, tp, AMP_TYPE  );
    % Integral gain (V/rad/s)
    ki = 0; 
elseif strcmp ( CONTROL_TYPE , 'AUTO_PIV' )
    % Load model parameters based on SRV02 configuration.
    [K,tau] = d_model_param(Rm, kt, km, Kg, eta_g, Beq, Jeq, eta_m, AMP_TYPE);
    % Calculate PV control gains given specifications.
    [ kp, kv ] = d_pv_design( K, tau, PO, tp, AMP_TYPE );
    % Ramp steady-state error when using PV control.
    [ e_ss ] = d_e_ss_ramp_pv (R0, kp, kv, K); 
    % Calculate integral gain
    if strcmp(AMP_TYPE,'Q3')
        [ ki ] = d_i_design( IMAX_AMP, kp, e_ss, ti); 
    else
        [ ki ] = d_i_design( VMAX_DAC, kp, e_ss, ti); 
    end
end
%
%% Display
if strcmp(AMP_TYPE,'Q3')
    disp( ' ' );
    disp( 'SRV02 model parameters: ' );
    disp( [ '   K = ' num2str( K, 3 ) ' rad/s^2/A' ] );
    disp( 'Specifications: ' );
    disp( [ '   tp = ' num2str( tp, 3 ) ' s' ] );
    disp( [ '   PO = ' num2str( PO, 3 ) ' %' ] );
    disp( 'Calculated PV control gains: ' );
    disp( [ '   kp = ' num2str( kp, 3 ) ' A/rad' ] );
    disp( [ '   kv = ' num2str( kv, 3 ) ' A.s/rad' ] );
    disp( 'Integral control gain for triangle tracking: ' );
    disp( [ '   ki = ' num2str( ki, 3 ) ' A/rad/s' ] );
else
    disp( ' ' );
    disp( 'SRV02 model parameters: ' );
    disp( [ '   K = ' num2str( K, 3 ) ' rad/s/V' ] );
    disp( [ '   tau = ' num2str( tau, 3 ) ' s' ] );
    disp( 'Specifications: ' );
    disp( [ '   tp = ' num2str( tp, 3 ) ' s' ] );
    disp( [ '   PO = ' num2str( PO, 3 ) ' %' ] );
    disp( 'Calculated PV control gains: ' );
    disp( [ '   kp = ' num2str( kp, 3 ) ' V/rad' ] );
    disp( [ '   kv = ' num2str( kv, 3 ) ' V.s/rad' ] );
    disp( 'Integral control gain for triangle tracking: ' );
    disp( [ '   ki = ' num2str( ki, 3 ) ' V/rad/s' ] );
end