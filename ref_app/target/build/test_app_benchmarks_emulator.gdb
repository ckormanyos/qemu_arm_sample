target remote localhost:9999

set confirm off

break main

run

print app_benchmark_standalone_result

continue
