set moduleName mergeSort_Pipeline_VITIS_LOOP_22_3
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set C_modelName {mergeSort_Pipeline_VITIS_LOOP_22_3}
set C_modelType { void 0 }
set C_modelArgList {
	{ k int 32 regular  }
	{ sext_ln22_3 int 33 regular  }
	{ l1_2_cast2 int 32 regular  }
	{ sext_ln22 int 32 regular  }
	{ l1_2 int 32 regular  }
	{ h1 int 32 regular  }
	{ icmp_ln22 int 1 regular  }
	{ temp int 32 regular {array 30 { 0 3 } 0 1 }  }
	{ arr_0 int 32 regular  }
	{ phi_ln22_out int 32 regular {pointer 1}  }
	{ phi_ln22_1_out int 32 regular {pointer 1}  }
	{ indvars_iv1_out int 64 regular {pointer 1}  }
	{ k_1_out int 32 regular {pointer 1}  }
	{ i_1_out int 32 regular {pointer 1}  }
	{ icmp_ln22_1_out int 1 regular {pointer 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "k", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sext_ln22_3", "interface" : "wire", "bitwidth" : 33, "direction" : "READONLY"} , 
 	{ "Name" : "l1_2_cast2", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sext_ln22", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "l1_2", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "h1", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "icmp_ln22", "interface" : "wire", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "temp", "interface" : "memory", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "arr_0", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "phi_ln22_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "phi_ln22_1_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "indvars_iv1_out", "interface" : "wire", "bitwidth" : 64, "direction" : "WRITEONLY"} , 
 	{ "Name" : "k_1_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "i_1_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "icmp_ln22_1_out", "interface" : "wire", "bitwidth" : 1, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 30
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ k sc_in sc_lv 32 signal 0 } 
	{ sext_ln22_3 sc_in sc_lv 33 signal 1 } 
	{ l1_2_cast2 sc_in sc_lv 32 signal 2 } 
	{ sext_ln22 sc_in sc_lv 32 signal 3 } 
	{ l1_2 sc_in sc_lv 32 signal 4 } 
	{ h1 sc_in sc_lv 32 signal 5 } 
	{ icmp_ln22 sc_in sc_lv 1 signal 6 } 
	{ temp_address0 sc_out sc_lv 5 signal 7 } 
	{ temp_ce0 sc_out sc_logic 1 signal 7 } 
	{ temp_we0 sc_out sc_logic 1 signal 7 } 
	{ temp_d0 sc_out sc_lv 32 signal 7 } 
	{ arr_0 sc_in sc_lv 32 signal 8 } 
	{ phi_ln22_out sc_out sc_lv 32 signal 9 } 
	{ phi_ln22_out_ap_vld sc_out sc_logic 1 outvld 9 } 
	{ phi_ln22_1_out sc_out sc_lv 32 signal 10 } 
	{ phi_ln22_1_out_ap_vld sc_out sc_logic 1 outvld 10 } 
	{ indvars_iv1_out sc_out sc_lv 64 signal 11 } 
	{ indvars_iv1_out_ap_vld sc_out sc_logic 1 outvld 11 } 
	{ k_1_out sc_out sc_lv 32 signal 12 } 
	{ k_1_out_ap_vld sc_out sc_logic 1 outvld 12 } 
	{ i_1_out sc_out sc_lv 32 signal 13 } 
	{ i_1_out_ap_vld sc_out sc_logic 1 outvld 13 } 
	{ icmp_ln22_1_out sc_out sc_lv 1 signal 14 } 
	{ icmp_ln22_1_out_ap_vld sc_out sc_logic 1 outvld 14 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "k", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k", "role": "default" }} , 
 	{ "name": "sext_ln22_3", "direction": "in", "datatype": "sc_lv", "bitwidth":33, "type": "signal", "bundle":{"name": "sext_ln22_3", "role": "default" }} , 
 	{ "name": "l1_2_cast2", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "l1_2_cast2", "role": "default" }} , 
 	{ "name": "sext_ln22", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sext_ln22", "role": "default" }} , 
 	{ "name": "l1_2", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "l1_2", "role": "default" }} , 
 	{ "name": "h1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "h1", "role": "default" }} , 
 	{ "name": "icmp_ln22", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "icmp_ln22", "role": "default" }} , 
 	{ "name": "temp_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":5, "type": "signal", "bundle":{"name": "temp", "role": "address0" }} , 
 	{ "name": "temp_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "temp", "role": "ce0" }} , 
 	{ "name": "temp_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "temp", "role": "we0" }} , 
 	{ "name": "temp_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "temp", "role": "d0" }} , 
 	{ "name": "arr_0", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "arr_0", "role": "default" }} , 
 	{ "name": "phi_ln22_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "phi_ln22_out", "role": "default" }} , 
 	{ "name": "phi_ln22_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "phi_ln22_out", "role": "ap_vld" }} , 
 	{ "name": "phi_ln22_1_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "phi_ln22_1_out", "role": "default" }} , 
 	{ "name": "phi_ln22_1_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "phi_ln22_1_out", "role": "ap_vld" }} , 
 	{ "name": "indvars_iv1_out", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "indvars_iv1_out", "role": "default" }} , 
 	{ "name": "indvars_iv1_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "indvars_iv1_out", "role": "ap_vld" }} , 
 	{ "name": "k_1_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "k_1_out", "role": "default" }} , 
 	{ "name": "k_1_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "k_1_out", "role": "ap_vld" }} , 
 	{ "name": "i_1_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "i_1_out", "role": "default" }} , 
 	{ "name": "i_1_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "i_1_out", "role": "ap_vld" }} , 
 	{ "name": "icmp_ln22_1_out", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "icmp_ln22_1_out", "role": "default" }} , 
 	{ "name": "icmp_ln22_1_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "icmp_ln22_1_out", "role": "ap_vld" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1"],
		"CDFG" : "mergeSort_Pipeline_VITIS_LOOP_22_3",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "-1", "EstimateLatencyMax" : "-1",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "k", "Type" : "None", "Direction" : "I"},
			{"Name" : "sext_ln22_3", "Type" : "None", "Direction" : "I"},
			{"Name" : "l1_2_cast2", "Type" : "None", "Direction" : "I"},
			{"Name" : "sext_ln22", "Type" : "None", "Direction" : "I"},
			{"Name" : "l1_2", "Type" : "None", "Direction" : "I"},
			{"Name" : "h1", "Type" : "None", "Direction" : "I"},
			{"Name" : "icmp_ln22", "Type" : "None", "Direction" : "I"},
			{"Name" : "temp", "Type" : "Memory", "Direction" : "O"},
			{"Name" : "arr_0", "Type" : "None", "Direction" : "I"},
			{"Name" : "phi_ln22_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "phi_ln22_1_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "indvars_iv1_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "k_1_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "i_1_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "icmp_ln22_1_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_22_3", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter1", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter1", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter1", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	mergeSort_Pipeline_VITIS_LOOP_22_3 {
		k {Type I LastRead 0 FirstWrite -1}
		sext_ln22_3 {Type I LastRead 0 FirstWrite -1}
		l1_2_cast2 {Type I LastRead 0 FirstWrite -1}
		sext_ln22 {Type I LastRead 0 FirstWrite -1}
		l1_2 {Type I LastRead 0 FirstWrite -1}
		h1 {Type I LastRead 0 FirstWrite -1}
		icmp_ln22 {Type I LastRead 0 FirstWrite -1}
		temp {Type O LastRead -1 FirstWrite 1}
		arr_0 {Type I LastRead 0 FirstWrite -1}
		phi_ln22_out {Type O LastRead -1 FirstWrite 1}
		phi_ln22_1_out {Type O LastRead -1 FirstWrite 1}
		indvars_iv1_out {Type O LastRead -1 FirstWrite 1}
		k_1_out {Type O LastRead -1 FirstWrite 1}
		i_1_out {Type O LastRead -1 FirstWrite 1}
		icmp_ln22_1_out {Type O LastRead -1 FirstWrite 1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "-1", "Max" : "-1"}
	, {"Name" : "Interval", "Min" : "-1", "Max" : "-1"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	k { ap_none {  { k in_data 0 32 } } }
	sext_ln22_3 { ap_none {  { sext_ln22_3 in_data 0 33 } } }
	l1_2_cast2 { ap_none {  { l1_2_cast2 in_data 0 32 } } }
	sext_ln22 { ap_none {  { sext_ln22 in_data 0 32 } } }
	l1_2 { ap_none {  { l1_2 in_data 0 32 } } }
	h1 { ap_none {  { h1 in_data 0 32 } } }
	icmp_ln22 { ap_none {  { icmp_ln22 in_data 0 1 } } }
	temp { ap_memory {  { temp_address0 mem_address 1 5 }  { temp_ce0 mem_ce 1 1 }  { temp_we0 mem_we 1 1 }  { temp_d0 mem_din 1 32 } } }
	arr_0 { ap_none {  { arr_0 in_data 0 32 } } }
	phi_ln22_out { ap_vld {  { phi_ln22_out out_data 1 32 }  { phi_ln22_out_ap_vld out_vld 1 1 } } }
	phi_ln22_1_out { ap_vld {  { phi_ln22_1_out out_data 1 32 }  { phi_ln22_1_out_ap_vld out_vld 1 1 } } }
	indvars_iv1_out { ap_vld {  { indvars_iv1_out out_data 1 64 }  { indvars_iv1_out_ap_vld out_vld 1 1 } } }
	k_1_out { ap_vld {  { k_1_out out_data 1 32 }  { k_1_out_ap_vld out_vld 1 1 } } }
	i_1_out { ap_vld {  { i_1_out out_data 1 32 }  { i_1_out_ap_vld out_vld 1 1 } } }
	icmp_ln22_1_out { ap_vld {  { icmp_ln22_1_out out_data 1 1 }  { icmp_ln22_1_out_ap_vld out_vld 1 1 } } }
}
