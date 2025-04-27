cmake_minimum_required(VERSION 3.16)

project(exercicio2 LANGUAGES C)

add_executable(exercicio2 main.c)

include(GNUInstallDirs)
install(TARGETS exercicio2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
