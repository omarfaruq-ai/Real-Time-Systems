TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK


PROGRAM Exercise5
  VAR
    Left_Hand : BOOL;
    Right_Hand : BOOL;
    Guard_Front : BOOL;
    Guard_Left : BOOL;
    Guard_Right : BOOL;
    E_Stop : BOOL;
    Mode_Switch : BOOL;
    Key_Switch : BOOL;
    Stroke_Sensor : BOOL;
    Pressure_Pump : BOOL;
    Press_Ram_Full : BOOL;
    Press_Ram_Slow : BOOL;
    Safety_OK : BOOL;
    Fault_Light : BOOL;
    Pump_Run_Light : BOOL;
    Jam_Fault_Light : BOOL;
    Stabilization_Done : BOOL;
    Prev_Mode : BOOL;
    Mode_Changed : BOOL;
    Both_Hands : BOOL;
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
