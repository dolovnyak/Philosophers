cmake_minimum_required(VERSION 3.17)
project(Philosophers C)

set(CMAKE_C_STANDARD 99)

include_directories(philo_one/includes)
add_executable(Philosophers
        philo_one/srcs/main.c
        philo_one/srcs/logging.c
        philo_one/srcs/fill_configuration_from_args.c
        philo_one/srcs/utilities/string_len.c
        philo_one/srcs/utilities/is_number.c
        philo_one/srcs/utilities/string_to_int.c
        )

#set_target_properties(${PROJECT_NAME}
#        PROPERTIES
#        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
#        )