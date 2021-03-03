cmake_minimum_required(VERSION 3.17)
project(Philosophers C)

set(CMAKE_C_STANDARD 99)

include_directories(includes)

SET(TARGET_NAME philo_one)

add_executable(${TARGET_NAME}
        srcs/main.c
        srcs/logging.c
        srcs/fill_configuration_from_args.c
        srcs/philosopher_live.c
        srcs/clean_all.c
        srcs/utilities/string_len.c
        srcs/utilities/is_number.c
        srcs/utilities/string_to_int.c
        srcs/utilities/timeval_into_size_t.c
        srcs/utilities/get_current_time.c
        srcs/utilities/ms_usleep.c
        srcs/utilities/mem_help.c
        srcs/utilities/size_t_to_string.c
        srcs/utilities/ft_strcpy.c
        srcs/utilities/numlen.c
        srcs/philosopher_utilities.c
        srcs/setup_philosophers.c)


set_target_properties(${TARGET_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )