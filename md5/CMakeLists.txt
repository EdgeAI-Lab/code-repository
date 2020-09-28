cmake_minimum_required(VERSION 3.10.2)

project(MD5 VERSION 0.1.0)

include_directories(.)

aux_source_directory(. SRC)

add_executable(MD5 ${SRC})
