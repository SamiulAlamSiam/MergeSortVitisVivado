set SynModuleInfo {
  {SRCNAME mergeSort_Pipeline_VITIS_LOOP_22_3 MODELNAME mergeSort_Pipeline_VITIS_LOOP_22_3 RTLNAME group3_mergeSort_Pipeline_VITIS_LOOP_22_3
    SUBMODULES {
      {MODELNAME group3_flow_control_loop_pipe_sequential_init RTLNAME group3_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME group3_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME mergeSort_Pipeline_VITIS_LOOP_29_4 MODELNAME mergeSort_Pipeline_VITIS_LOOP_29_4 RTLNAME group3_mergeSort_Pipeline_VITIS_LOOP_29_4}
  {SRCNAME mergeSort_Pipeline_VITIS_LOOP_31_5 MODELNAME mergeSort_Pipeline_VITIS_LOOP_31_5 RTLNAME group3_mergeSort_Pipeline_VITIS_LOOP_31_5}
  {SRCNAME mergeSort_Pipeline_VITIS_LOOP_39_6 MODELNAME mergeSort_Pipeline_VITIS_LOOP_39_6 RTLNAME group3_mergeSort_Pipeline_VITIS_LOOP_39_6}
  {SRCNAME mergeSort_Pipeline_VITIS_LOOP_42_7 MODELNAME mergeSort_Pipeline_VITIS_LOOP_42_7 RTLNAME group3_mergeSort_Pipeline_VITIS_LOOP_42_7}
  {SRCNAME mergeSort MODELNAME mergeSort RTLNAME group3_mergeSort
    SUBMODULES {
      {MODELNAME group3_mergeSort_temp_RAM_AUTO_1R1W RTLNAME group3_mergeSort_temp_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME group3 MODELNAME group3 RTLNAME group3 IS_TOP 1
    SUBMODULES {
      {MODELNAME group3_control_s_axi RTLNAME group3_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
