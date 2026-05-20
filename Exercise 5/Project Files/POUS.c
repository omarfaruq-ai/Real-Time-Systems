void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void EXERCISE5_init__(EXERCISE5 *data__, BOOL retain) {
  __INIT_VAR(data__->LEFT_HAND,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RIGHT_HAND,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->GUARD_FRONT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->GUARD_LEFT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->GUARD_RIGHT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->E_STOP,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MODE_SWITCH,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->KEY_SWITCH,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->STROKE_SENSOR,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PRESSURE_PUMP,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PRESS_RAM_FULL,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PRESS_RAM_SLOW,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SAFETY_OK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->FAULT_LIGHT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PUMP_RUN_LIGHT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->JAM_FAULT_LIGHT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->STABILIZATION_DONE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->PREV_MODE,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MODE_CHANGED,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->BOTH_HANDS,__BOOL_LITERAL(FALSE),retain)
  TON_init__(&data__->TON0,retain);
  TON_init__(&data__->TON1,retain);
}

// Code part
void EXERCISE5_body__(EXERCISE5 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,PRESSURE_PUMP,,(!(__GET_VAR(data__->FAULT_LIGHT,)) && __GET_VAR(data__->E_STOP,)));
  __SET_VAR(data__->,PUMP_RUN_LIGHT,,(!(__GET_VAR(data__->FAULT_LIGHT,)) && __GET_VAR(data__->E_STOP,)));
  __SET_VAR(data__->TON0.,IN,,__GET_VAR(data__->PRESSURE_PUMP,));
  __SET_VAR(data__->TON0.,PT,,__time_to_timespec(1, 0, 5, 0, 0, 0));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->,STABILIZATION_DONE,,__GET_VAR(data__->TON0.Q,));
  if ((((((!(__GET_VAR(data__->GUARD_RIGHT,)) && !(__GET_VAR(data__->GUARD_LEFT,))) && !(__GET_VAR(data__->GUARD_FRONT,))) && __GET_VAR(data__->RIGHT_HAND,)) && __GET_VAR(data__->LEFT_HAND,)) && __GET_VAR(data__->E_STOP,))) {
    __SET_VAR(data__->,FAULT_LIGHT,,__BOOL_LITERAL(FALSE));
  };
  if (((__GET_VAR(data__->MODE_CHANGED,) || !(__GET_VAR(data__->E_STOP,))) || ((((__GET_VAR(data__->GUARD_FRONT,) || __GET_VAR(data__->GUARD_LEFT,)) || __GET_VAR(data__->GUARD_RIGHT,)) && __GET_VAR(data__->PUMP_RUN_LIGHT,)) && __GET_VAR(data__->MODE_SWITCH,)))) {
    __SET_VAR(data__->,FAULT_LIGHT,,__BOOL_LITERAL(TRUE));
  };
  __SET_VAR(data__->TON1.,IN,,(!(__GET_VAR(data__->STROKE_SENSOR,)) && (__GET_VAR(data__->PRESS_RAM_FULL,) || __GET_VAR(data__->PRESS_RAM_SLOW,))));
  __SET_VAR(data__->TON1.,PT,,__time_to_timespec(1, 0, 4, 0, 0, 0));
  TON_body__(&data__->TON1);
  if (__GET_VAR(data__->TON1.Q,)) {
    __SET_VAR(data__->,JAM_FAULT_LIGHT,,__BOOL_LITERAL(TRUE));
  };
  if (((!(__GET_VAR(data__->RIGHT_HAND,)) && !(__GET_VAR(data__->LEFT_HAND,))) && __GET_VAR(data__->E_STOP,))) {
    __SET_VAR(data__->,JAM_FAULT_LIGHT,,__BOOL_LITERAL(FALSE));
  };
  __SET_VAR(data__->,PRESS_RAM_FULL,,(((((((((((!(__GET_VAR(data__->PRESS_RAM_SLOW,)) && !(__GET_VAR(data__->JAM_FAULT_LIGHT,))) && !(__GET_VAR(data__->FAULT_LIGHT,))) && __GET_VAR(data__->PUMP_RUN_LIGHT,)) && __GET_VAR(data__->RIGHT_HAND,)) && __GET_VAR(data__->LEFT_HAND,)) && __GET_VAR(data__->STABILIZATION_DONE,)) && !(__GET_VAR(data__->GUARD_RIGHT,))) && !(__GET_VAR(data__->GUARD_LEFT,))) && !(__GET_VAR(data__->GUARD_FRONT,))) && __GET_VAR(data__->E_STOP,)) && __GET_VAR(data__->MODE_SWITCH,)));
  __SET_VAR(data__->,PRESS_RAM_SLOW,,(((((((((!(__GET_VAR(data__->PRESS_RAM_FULL,)) && !(__GET_VAR(data__->JAM_FAULT_LIGHT,))) && !(__GET_VAR(data__->FAULT_LIGHT,))) && __GET_VAR(data__->PUMP_RUN_LIGHT,)) && __GET_VAR(data__->RIGHT_HAND,)) && __GET_VAR(data__->LEFT_HAND,)) && __GET_VAR(data__->STABILIZATION_DONE,)) && __GET_VAR(data__->KEY_SWITCH,)) && __GET_VAR(data__->E_STOP,)) && !(__GET_VAR(data__->MODE_SWITCH,))));
  __SET_VAR(data__->,SAFETY_OK,,((((((((!(__GET_VAR(data__->FAULT_LIGHT,)) && __GET_VAR(data__->PUMP_RUN_LIGHT,)) && __GET_VAR(data__->STABILIZATION_DONE,)) && !(__GET_VAR(data__->GUARD_RIGHT,))) && !(__GET_VAR(data__->GUARD_LEFT,))) && !(__GET_VAR(data__->GUARD_FRONT,))) && __GET_VAR(data__->E_STOP,)) && __GET_VAR(data__->MODE_SWITCH,)) || (((((!(__GET_VAR(data__->FAULT_LIGHT,)) && __GET_VAR(data__->PUMP_RUN_LIGHT,)) && __GET_VAR(data__->STABILIZATION_DONE,)) && __GET_VAR(data__->KEY_SWITCH,)) && __GET_VAR(data__->E_STOP,)) && !(__GET_VAR(data__->MODE_SWITCH,)))));
  __SET_VAR(data__->,MODE_CHANGED,,((!(__GET_VAR(data__->PREV_MODE,)) && __GET_VAR(data__->MODE_SWITCH,)) || (__GET_VAR(data__->PREV_MODE,) && !(__GET_VAR(data__->MODE_SWITCH,)))));
  __SET_VAR(data__->,PREV_MODE,,__GET_VAR(data__->MODE_SWITCH,));

  goto __end;

__end:
  return;
} // EXERCISE5_body__() 





