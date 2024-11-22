
# Connect to the target (e.g., OpenOCD or another GDB server)
target remote localhost:9999

# Set a breakpoint at the specified location
break app_benchmark_get_standalone_result

# Start or continue program execution
continue

# Query the value of a variable
print app_benchmark_standalone_result

# Delete (all) breakpoints
delete

# Continue execution after the breakpoint (optional)
continue
