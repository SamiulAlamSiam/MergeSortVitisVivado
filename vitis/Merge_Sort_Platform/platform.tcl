# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct E:\USN_Education\VitisCode\MergeSort\vitis\Merge_Sort_Platform\platform.tcl
# 
# OR launch xsct and run below command.
# source E:\USN_Education\VitisCode\MergeSort\vitis\Merge_Sort_Platform\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {Merge_Sort_Platform}\
-hw {E:\USN_Education\Embeded System\VDHL Code\My Code\mergesort\Merge_Sort_VIVADO\merge_sort_design_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -out {E:/USN_Education/VitisCode/MergeSort/vitis}

platform write
platform generate -domains 
platform active {Merge_Sort_Platform}
platform generate
platform clean
platform generate -domains standalone_domain,zynq_fsbl 
platform active {Merge_Sort_Platform}
platform generate -domains 
