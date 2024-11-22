target remote localhost:9999

set confirm off

break app_benchmark_get_standalone_result

continue

print app_benchmark_standalone_result

continue
