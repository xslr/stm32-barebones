cmake_minimum_required(VERSION 3.8) # always first, 3.8 is a pretty low bar

set(CMAKE_BUILD_TYPE RelWithDebInfo)

# Add stm32-cmake's custom modules the the search path. This is
# where the author implemented the find package logic and more
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/third_party/stm32-cmake/cmake/stm32_gcc.cmake)

# declare a project, there must be at least one of these and it should
# come before any target based commands
project(stm32-blinky C CXX ASM)

# Sets a variable to true. Must be used internally for stm32-cmake
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# Finds the listed components. Hard error if they are not found
# according to the readme this depends on some variables
# that you should have set via command line
find_package(CMSIS COMPONENTS STM32F4 REQUIRED)
find_package(HAL COMPONENTS STM32F4 REQUIRED)
find_package(FreeRTOS COMPONENTS ARM_CM4F REQUIRED)

# create a target called `stm32-blinky-f4` using blinky.c
# listing the header is nice an explicit but unnecessary
add_executable(stm32-blinky-f4
  src/blinky.c
  src/stm32f4xx_it.c
  src/stm32f4xx_it.h
  src/stm32f4xx_hal_conf.h)

target_include_directories(stm32-blinky-f4
  PRIVATE src)

# Here is the magic, assuming the find_package commands succeeded
# targets for each module you asked for is creates
# you link your target against these targets which gives you everything
# you need to compile and link against those targets
target_link_libraries(stm32-blinky-f4
  HAL::STM32::F4::RCC
  HAL::STM32::F4::GPIO
  HAL::STM32::F4::CORTEX
  CMSIS::STM32::F407VG
  STM32::NoSys
)

# create a target called `stm32-freertos-f4` using freertos.c
# listing the header is nice an explicit but unnecessary

add_executable(stm32-freertos.elf
  src/stm32f4_freertos.c

  #src/stm32f4xx_it.c
  #src/stm32f4xx_it.h

  src/FreeRTOSConfig.h
  src/stm32f4xx_hal_conf.h)

target_include_directories(stm32-freertos.elf
  PRIVATE src)

target_link_libraries(stm32-freertos.elf PRIVATE
  FreeRTOS::Timers
  FreeRTOS::Heap::1
  FreeRTOS::ARM_CM4F
  HAL::STM32::F4::RCC
  HAL::STM32::F4::GPIO
  HAL::STM32::F4::CORTEX
  CMSIS::STM32::F407VG
  STM32::NoSys
  )
