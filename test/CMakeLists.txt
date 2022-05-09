
# ============================================= GENERATION DES EXECUTABLES =============================================
file( GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c )

# pour chaque TEST
foreach( source ${SRCS} )
    # Transform absolute path in relative path
    string( REPLACE ".c" "" source_name ${source} )
    string( REPLACE ${CMAKE_CURRENT_SOURCE_DIR}/ "" source_name ${source_name} )

    # on créé l'executable
    add_executable( ${source_name} ${source} )

    # on link les librairies
    target_link_libraries( ${source_name} TSP )
    target_compile_options( ${source_name} PUBLIC -g)

    # test
    add_test(${source_name} ${source_name})

endforeach( source ${SRCS} )