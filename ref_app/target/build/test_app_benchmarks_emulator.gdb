
# Connect to the target (e.g., OpenOCD or another GDB server)
target remote localhost:9999
monitor reset halt

load

# Set a breakpoint at the specified location
break app_benchmark_crc.cpp:136

# Start or continue program execution
continue

# Query the value of a variable
print app_benchmark_standalone_result

# Format and write the value to a file
shell printf "Benchmark result: 0x%X\n" $1

# Delete (all) breakpoint(s)
delete

quit
