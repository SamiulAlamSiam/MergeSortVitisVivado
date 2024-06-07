# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: E:\USN_Education\VitisCode\MergeSort\vitis\MergeSortApplication_system\_ide\scripts\systemdebugger_mergesortapplication_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source E:\USN_Education\VitisCode\MergeSort\vitis\MergeSortApplication_system\_ide\scripts\systemdebugger_mergesortapplication_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zybo 210279652014A" && level==0 && jtag_device_ctx=="jsn-Zybo-210279652014A-13722093-0"}
fpga -file E:/USN_Education/VitisCode/MergeSort/vitis/MergeSortApplication/_ide/bitstream/merge_sort_design_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw E:/USN_Education/VitisCode/MergeSort/vitis/Merge_Sort_Platform/export/Merge_Sort_Platform/hw/merge_sort_design_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source E:/USN_Education/VitisCode/MergeSort/vitis/MergeSortApplication/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow E:/USN_Education/VitisCode/MergeSort/vitis/MergeSortApplication/Debug/MergeSortApplication.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
