# SPDX-License-Identifier: Apache-2.0

set(CONF_FILE prj.conf)

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hts221)

#FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE src/main.c
                ${CMAKE_CURRENT_SOURCE_DIR}/../../oslib/scu_drivers/scu_sensors/temp_humidity_sensor.c
                ${CMAKE_CURRENT_SOURCE_DIR}/../../oslib/scu_drivers/scu_sensors/motion_sensor.c
                ${CMAKE_CURRENT_SOURCE_DIR}/../../oslib/scu_drivers/scu_sensors/air_quality_sensor.c
                ${CMAKE_CURRENT_SOURCE_DIR}/../../oslib/scu_drivers/scu_sensors/temp_pressure_sensor.c)
include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../oslib/scu_drivers/scu_sensors/)
