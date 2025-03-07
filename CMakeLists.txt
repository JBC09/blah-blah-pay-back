cmake_minimum_required(VERSION 3.30)
project(src/payment)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

find_package(unofficial-mysql-connector-cpp CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)

add_executable(payment main.cpp
        src/auth/customJwt.cpp
        src/database/database.cpp
        src/database/database.h
        src/auth/customJwt.h
        src/database/mysql.cpp
        src/database/mysql.h
        src/database/databaseManager.cpp
        src/database/databaseManager.h)


target_link_libraries(payment PRIVATE jwt-cpp::jwt-cpp)
