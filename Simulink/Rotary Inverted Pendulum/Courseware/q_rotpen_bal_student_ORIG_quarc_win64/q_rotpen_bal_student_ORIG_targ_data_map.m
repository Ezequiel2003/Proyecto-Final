  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 4;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (q_rotpen_bal_student_ORIG_P)
    ;%
      section.nData     = 41;
      section.data(41)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_P.ControlGain_Gain
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_OOStart
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 4;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_OOEnter
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 5;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_OOTerminate
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 6;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_OOExit
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 7;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AIHigh
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 8;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AILow
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 9;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOHigh
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 10;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOLow
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 11;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOInitial
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 12;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOFinal
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 13;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOWatchdog
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 14;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POFrequency
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 15;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POLeading
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 16;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POTrailing
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 17;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POInitial
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 18;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POFinal
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 19;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POWatchdog
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 20;
	
	  ;% q_rotpen_bal_student_ORIG_P.EncoderCalibrationradcount_Gain
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 21;
	
	  ;% q_rotpen_bal_student_ORIG_P.ModAnglerad_Value
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 22;
	
	  ;% q_rotpen_bal_student_ORIG_P.OffsetAnglerad_Value
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 23;
	
	  ;% q_rotpen_bal_student_ORIG_P.Constant_Value
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 24;
	
	  ;% q_rotpen_bal_student_ORIG_P.u0V_Value
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 25;
	
	  ;% q_rotpen_bal_student_ORIG_P.SignalGenerator_Amplitude
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 26;
	
	  ;% q_rotpen_bal_student_ORIG_P.SignalGenerator_Frequency
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 27;
	
	  ;% q_rotpen_bal_student_ORIG_P.Amplitudedeg_Gain
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 28;
	
	  ;% q_rotpen_bal_student_ORIG_P.Gain1_Gain
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 29;
	
	  ;% q_rotpen_bal_student_ORIG_P.ConverttoVectorState_Gain
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 30;
	
	  ;% q_rotpen_bal_student_ORIG_P.HPFtheta_dotrads_A
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 34;
	
	  ;% q_rotpen_bal_student_ORIG_P.HPFtheta_dotrads_C
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 35;
	
	  ;% q_rotpen_bal_student_ORIG_P.HPFtheta_dotrads_D
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 36;
	
	  ;% q_rotpen_bal_student_ORIG_P.HPFalpha_dotrads_A
	  section.data(32).logicalSrcIdx = 32;
	  section.data(32).dtTransOffset = 37;
	
	  ;% q_rotpen_bal_student_ORIG_P.HPFalpha_dotrads_C
	  section.data(33).logicalSrcIdx = 33;
	  section.data(33).dtTransOffset = 38;
	
	  ;% q_rotpen_bal_student_ORIG_P.HPFalpha_dotrads_D
	  section.data(34).logicalSrcIdx = 34;
	  section.data(34).dtTransOffset = 39;
	
	  ;% q_rotpen_bal_student_ORIG_P.DirectionConventionRightHandsys
	  section.data(35).logicalSrcIdx = 36;
	  section.data(35).dtTransOffset = 40;
	
	  ;% q_rotpen_bal_student_ORIG_P.AmplifierSaturationV_UpperSat
	  section.data(36).logicalSrcIdx = 37;
	  section.data(36).dtTransOffset = 41;
	
	  ;% q_rotpen_bal_student_ORIG_P.AmplifierSaturationV_LowerSat
	  section.data(37).logicalSrcIdx = 38;
	  section.data(37).dtTransOffset = 42;
	
	  ;% q_rotpen_bal_student_ORIG_P.InverseAmplifierGainVV_Gain
	  section.data(38).logicalSrcIdx = 39;
	  section.data(38).dtTransOffset = 43;
	
	  ;% q_rotpen_bal_student_ORIG_P.EnableVoltPAQX2X4_Value
	  section.data(39).logicalSrcIdx = 40;
	  section.data(39).dtTransOffset = 44;
	
	  ;% q_rotpen_bal_student_ORIG_P.Gain_Gain
	  section.data(40).logicalSrcIdx = 41;
	  section.data(40).dtTransOffset = 48;
	
	  ;% q_rotpen_bal_student_ORIG_P.Gain_Gain_n
	  section.data(41).logicalSrcIdx = 42;
	  section.data(41).dtTransOffset = 49;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 7;
      section.data(7)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_CKChannels
	  section.data(1).logicalSrcIdx = 43;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOWatchdog
	  section.data(2).logicalSrcIdx = 44;
	  section.data(2).dtTransOffset = 3;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_EIInitial
	  section.data(3).logicalSrcIdx = 45;
	  section.data(3).dtTransOffset = 4;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POModes
	  section.data(4).logicalSrcIdx = 46;
	  section.data(4).dtTransOffset = 5;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POConfiguration
	  section.data(5).logicalSrcIdx = 47;
	  section.data(5).dtTransOffset = 6;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POAlignment
	  section.data(6).logicalSrcIdx = 48;
	  section.data(6).dtTransOffset = 7;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POPolarity
	  section.data(7).logicalSrcIdx = 49;
	  section.data(7).dtTransOffset = 8;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AIChannels
	  section.data(1).logicalSrcIdx = 50;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOChannels
	  section.data(2).logicalSrcIdx = 51;
	  section.data(2).dtTransOffset = 8;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOChannels
	  section.data(3).logicalSrcIdx = 52;
	  section.data(3).dtTransOffset = 16;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_EIChannels
	  section.data(4).logicalSrcIdx = 53;
	  section.data(4).dtTransOffset = 24;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_EIQuadrature
	  section.data(5).logicalSrcIdx = 54;
	  section.data(5).dtTransOffset = 32;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POChannels
	  section.data(6).logicalSrcIdx = 55;
	  section.data(6).dtTransOffset = 33;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILReadEncoder_Channels
	  section.data(7).logicalSrcIdx = 56;
	  section.data(7).dtTransOffset = 41;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILWriteAnalog_Channels
	  section.data(8).logicalSrcIdx = 57;
	  section.data(8).dtTransOffset = 43;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILWriteDigital_Channels
	  section.data(9).logicalSrcIdx = 58;
	  section.data(9).dtTransOffset = 44;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(3) = section;
      clear section
      
      section.nData     = 38;
      section.data(38)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_Active
	  section.data(1).logicalSrcIdx = 59;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_CKPStart
	  section.data(2).logicalSrcIdx = 60;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_CKPEnter
	  section.data(3).logicalSrcIdx = 61;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_CKStart
	  section.data(4).logicalSrcIdx = 62;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_CKEnter
	  section.data(5).logicalSrcIdx = 63;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AIPStart
	  section.data(6).logicalSrcIdx = 64;
	  section.data(6).dtTransOffset = 5;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AIPEnter
	  section.data(7).logicalSrcIdx = 65;
	  section.data(7).dtTransOffset = 6;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOPStart
	  section.data(8).logicalSrcIdx = 66;
	  section.data(8).dtTransOffset = 7;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOPEnter
	  section.data(9).logicalSrcIdx = 67;
	  section.data(9).dtTransOffset = 8;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOStart
	  section.data(10).logicalSrcIdx = 68;
	  section.data(10).dtTransOffset = 9;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOEnter
	  section.data(11).logicalSrcIdx = 69;
	  section.data(11).dtTransOffset = 10;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOTerminate
	  section.data(12).logicalSrcIdx = 70;
	  section.data(12).dtTransOffset = 11;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOExit
	  section.data(13).logicalSrcIdx = 71;
	  section.data(13).dtTransOffset = 12;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_AOReset
	  section.data(14).logicalSrcIdx = 72;
	  section.data(14).dtTransOffset = 13;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOPStart
	  section.data(15).logicalSrcIdx = 73;
	  section.data(15).dtTransOffset = 14;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOPEnter
	  section.data(16).logicalSrcIdx = 74;
	  section.data(16).dtTransOffset = 15;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOStart
	  section.data(17).logicalSrcIdx = 75;
	  section.data(17).dtTransOffset = 16;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOEnter
	  section.data(18).logicalSrcIdx = 76;
	  section.data(18).dtTransOffset = 17;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOTerminate
	  section.data(19).logicalSrcIdx = 77;
	  section.data(19).dtTransOffset = 18;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOExit
	  section.data(20).logicalSrcIdx = 78;
	  section.data(20).dtTransOffset = 19;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOReset
	  section.data(21).logicalSrcIdx = 79;
	  section.data(21).dtTransOffset = 20;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_EIPStart
	  section.data(22).logicalSrcIdx = 80;
	  section.data(22).dtTransOffset = 21;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_EIPEnter
	  section.data(23).logicalSrcIdx = 81;
	  section.data(23).dtTransOffset = 22;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_EIStart
	  section.data(24).logicalSrcIdx = 82;
	  section.data(24).dtTransOffset = 23;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_EIEnter
	  section.data(25).logicalSrcIdx = 83;
	  section.data(25).dtTransOffset = 24;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POPStart
	  section.data(26).logicalSrcIdx = 84;
	  section.data(26).dtTransOffset = 25;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POPEnter
	  section.data(27).logicalSrcIdx = 85;
	  section.data(27).dtTransOffset = 26;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POStart
	  section.data(28).logicalSrcIdx = 86;
	  section.data(28).dtTransOffset = 27;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POEnter
	  section.data(29).logicalSrcIdx = 87;
	  section.data(29).dtTransOffset = 28;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POTerminate
	  section.data(30).logicalSrcIdx = 88;
	  section.data(30).dtTransOffset = 29;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POExit
	  section.data(31).logicalSrcIdx = 89;
	  section.data(31).dtTransOffset = 30;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_POReset
	  section.data(32).logicalSrcIdx = 90;
	  section.data(32).dtTransOffset = 31;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_OOReset
	  section.data(33).logicalSrcIdx = 91;
	  section.data(33).dtTransOffset = 32;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOInitial
	  section.data(34).logicalSrcIdx = 92;
	  section.data(34).dtTransOffset = 33;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILInitialize_DOFinal
	  section.data(35).logicalSrcIdx = 93;
	  section.data(35).dtTransOffset = 34;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILReadEncoder_Active
	  section.data(36).logicalSrcIdx = 94;
	  section.data(36).dtTransOffset = 35;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILWriteAnalog_Active
	  section.data(37).logicalSrcIdx = 95;
	  section.data(37).dtTransOffset = 36;
	
	  ;% q_rotpen_bal_student_ORIG_P.HILWriteDigital_Active
	  section.data(38).logicalSrcIdx = 96;
	  section.data(38).dtTransOffset = 37;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(4) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (q_rotpen_bal_student_ORIG_B)
    ;%
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_B.EncoderCalibrationradcount
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_rotpen_bal_student_ORIG_B.Sum
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 2;
	
	  ;% q_rotpen_bal_student_ORIG_B.EnableSwitch
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 3;
	
	  ;% q_rotpen_bal_student_ORIG_B.InverseAmplifierGainVV
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 4;
	
	  ;% q_rotpen_bal_student_ORIG_B.Gain
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 5;
	
	  ;% q_rotpen_bal_student_ORIG_B.Gain_a
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 6;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_B.Compare
	  section.data(1).logicalSrcIdx = 6;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 7;
    sectIdxOffset = 2;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (q_rotpen_bal_student_ORIG_DWork)
    ;%
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_AIMinimums
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_AIMaximums
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 8;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_AOMinimums
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 16;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_AOMaximums
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 24;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_AOVoltages
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 32;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_FilterFrequency
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 40;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_POSortedFreqs
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 48;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_POValues
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 56;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_Card
	  section.data(1).logicalSrcIdx = 8;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 6;
      section.data(6)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_DWork.HILReadEncoder_PWORK
	  section.data(1).logicalSrcIdx = 9;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILWriteAnalog_PWORK
	  section.data(2).logicalSrcIdx = 10;
	  section.data(2).dtTransOffset = 1;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILWriteDigital_PWORK
	  section.data(3).logicalSrcIdx = 11;
	  section.data(3).dtTransOffset = 2;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.alphadeg_PWORK.LoggedData
	  section.data(4).logicalSrcIdx = 12;
	  section.data(4).dtTransOffset = 3;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.thetadeg_PWORK.LoggedData
	  section.data(5).logicalSrcIdx = 13;
	  section.data(5).dtTransOffset = 4;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.VmV_PWORK.LoggedData
	  section.data(6).logicalSrcIdx = 14;
	  section.data(6).dtTransOffset = 5;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_ClockModes
	  section.data(1).logicalSrcIdx = 15;
	  section.data(1).dtTransOffset = 0;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_DOStates
	  section.data(2).logicalSrcIdx = 16;
	  section.data(2).dtTransOffset = 3;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_QuadratureModes
	  section.data(3).logicalSrcIdx = 17;
	  section.data(3).dtTransOffset = 11;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_InitialEICounts
	  section.data(4).logicalSrcIdx = 18;
	  section.data(4).dtTransOffset = 19;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_POModeValues
	  section.data(5).logicalSrcIdx = 19;
	  section.data(5).dtTransOffset = 27;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_POAlignValues
	  section.data(6).logicalSrcIdx = 20;
	  section.data(6).dtTransOffset = 35;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_POPolarityVals
	  section.data(7).logicalSrcIdx = 21;
	  section.data(7).dtTransOffset = 43;
	
	  ;% q_rotpen_bal_student_ORIG_DWork.HILReadEncoder_Buffer
	  section.data(8).logicalSrcIdx = 22;
	  section.data(8).dtTransOffset = 51;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_POSortedChans
	  section.data(1).logicalSrcIdx = 23;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_DWork.HILInitialize_DOBits
	  section.data(1).logicalSrcIdx = 24;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% q_rotpen_bal_student_ORIG_DWork.HILWriteDigital_Buffer
	  section.data(1).logicalSrcIdx = 25;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(7) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 2063351769;
  targMap.checksum1 = 4285674787;
  targMap.checksum2 = 3361206938;
  targMap.checksum3 = 3758241607;
