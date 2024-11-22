
# Connect to the target (e.g., OpenOCD or another GDB server)
target remote localhost:9999
monitor halt

load

# Set a breakpoint at the specified location
break app_benchmark_crc.cpp:136

# Start or continue program execution
continue

# Format and print the value of a variable
printf "0x%X\n", app_benchmark_standalone_result

# Delete (all) breakpoint(s)
delete

quit
