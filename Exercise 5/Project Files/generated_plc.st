PROGRAM Exercise5
  VAR
    Left_Hand AT %QX0.0 : BOOL;
    Right_Hand AT %QX0.1 : BOOL;
    Guard_Front AT %QX0.2 : BOOL;
    Guard_Left AT %QX0.3 : BOOL;
    Guard_Right AT %QX0.4 : BOOL;
    E_Stop AT %QX0.5 : BOOL;
    Mode_Switch AT %QX1.0 : BOOL;
    Key_Switch AT %QX1.1 : BOOL;
    Stroke_Sensor AT %QX1.2 : BOOL;
    Pressure_Pump AT %QX1.3 : BOOL;
    Press_Ram_Full AT %QX1.4 : BOOL;
    Press_Ram_Slow AT %QX1.5 : BOOL;
    Safety_OK AT %QX1.6 : BOOL;
    Fault_Light AT %QX1.7 : BOOL;
    Pump_Run_Light AT %QX2.0 : BOOL;
    Jam_Fault_Light AT %QX2.1 : BOOL;
    Stabilization_Done AT %MX0.0 : BOOL;
    Prev_Mode AT %MX0.1 : BOOL;
    Mode_Changed AT %MX0.2 : BOOL;
    Both_Hands AT %MX0.3 : BOOL;
  END_VAR
  VAR
    TON0 : TON;
    TON1 : TON;
  END_VAR

  Pressure_Pump := NOT(Fault_Light) AND E_Stop;
  Pump_Run_Light := NOT(Fault_Light) AND E_Stop;
  TON0(IN := Pressure_Pump, PT := T#5s);
  Stabilization_Done := TON0.Q;
  IF NOT(Guard_Right) AND NOT(Guard_Left) AND NOT(Guard_Front) AND Right_Hand AND Left_Hand AND E_Stop THEN
    Fault_Light := FALSE; (*reset*)
  END_IF;
  IF Mode_Changed OR NOT(E_Stop) OR (Guard_Front OR Guard_Left OR Guard_Right) AND Pump_Run_Light AND Mode_Switch THEN
    Fault_Light := TRUE; (*set*)
  END_IF;
  TON1(IN := NOT(Stroke_Sensor) AND (Press_Ram_Full OR Press_Ram_Slow), PT := T#4s);
  IF TON1.Q THEN
    Jam_Fault_Light := TRUE; (*set*)
  END_IF;
  IF NOT(Right_Hand) AND NOT(Left_Hand) AND E_Stop THEN
    Jam_Fault_Light := FALSE; (*reset*)
  END_IF;
  Press_Ram_Full := NOT(Press_Ram_Slow) AND NOT(Jam_Fault_Light) AND NOT(Fault_Light) AND Pump_Run_Light AND Right_Hand AND Left_Hand AND Stabilization_Done AND NOT(Guard_Right) AND NOT(Guard_Left) AND NOT(Guard_Front) AND E_Stop AND Mode_Switch;
  Press_Ram_Slow := NOT(Press_Ram_Full) AND NOT(Jam_Fault_Light) AND NOT(Fault_Light) AND Pump_Run_Light AND Right_Hand AND Left_Hand AND Stabilization_Done AND Key_Switch AND E_Stop AND NOT(Mode_Switch);
  Safety_OK := NOT(Fault_Light) AND Pump_Run_Light AND Stabilization_Done AND NOT(Guard_Right) AND NOT(Guard_Left) AND NOT(Guard_Front) AND E_Stop AND Mode_Switch OR NOT(Fault_Light) AND Pump_Run_Light AND Stabilization_Done AND Key_Switch AND E_Stop AND NOT(Mode_Switch);
  Mode_Changed := NOT(Prev_Mode) AND Mode_Switch OR Prev_Mode AND NOT(Mode_Switch);
  Prev_Mode := Mode_Switch;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Exercise5;
  END_RESOURCE
END_CONFIGURATION
