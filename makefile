name=sine_generator

ifndef target_device_version
target_device_version=26.1
endif

target_platform=arm64-apple-macos${target_device_version}

directory_sdk=${shell xcrun --sdk macosx${target_device_version} --show-sdk-path}

target_version_clic3=0
target_version_math_c=0

directory_include=include
directory_objects=objects
directory_output=output
directory_sources=sources

ifndef directory_clic3
directory_clic3=../clic3
endif
directory_clic3_include=${directory_clic3}/include
directory_clic3_library=${directory_clic3}/library/macos/release

ifndef directory_math_c
directory_math_c=../math_c
endif
directory_math_c_include=${directory_math_c}/include
directory_math_c_library=${directory_math_c}/library/macos/release

cc=clang
c_flags_platform=-target ${target_platform} -isysroot ${directory_sdk}
c_flags=${c_flags_platform} -O3 -I${directory_include} -I${directory_clic3_include} -I${directory_math_c_include}

files_sources=${wildcard ${directory_sources}/*.c}
files_objects=${patsubst ${directory_sources}/%.c,${directory_objects}/%.o,${files_sources}}

file_clic3_library=${directory_clic3_library}/clic3.${target_version_clic3}.dylib
file_math_c_library=${directory_math_c_library}/math_c.${target_version_math_c}.dylib

file_output=${directory_output}/${name}

files_libraries=${file_clic3_library} ${file_math_c_library}

${file_output}: ${files_objects}
	if [[ ! -d ${directory_output} ]]; then mkdir ${directory_output}; fi
	${cc} ${c_flags} ${files_libraries} ${files_objects} -o ${file_output}

${directory_objects}/%.o: ${directory_sources}/%.c
	if [[ ! -d ${directory_objects} ]]; then mkdir ${directory_objects}; fi
	${cc} ${c_flags} -c $< -o $@

clean: clean_objects clean_output

clean_objects:
	-rm -r ${directory_objects} 2>/dev/null

clean_output:
	-rm -r ${directory_output} 2>/dev/null
