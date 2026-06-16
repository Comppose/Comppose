# Creates C assets file from files in given directory
# https://stackoverflow.com/questions/11813271/embed-assets-eg-shader-code-images-into-executable-library-with-cmake/11814544#11814544
function(create_assets dir output)

    # Then create
    file(WRITE ${output} "")

    # Collect input files
    file(GLOB bins ${dir}/*)

    # Iterate through input files
    foreach(bin ${bins})
        # Get short filename
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
        # Read hex data from file
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        # Append data to output file
        file(APPEND ${output} "const unsigned char ${filename}[] = {${filedata}};\nconst unsigned ${filename}_size = sizeof(${filename});\n")
    endforeach()
endfunction()

create_assets("${CMAKE_CURRENT_SOURCE_DIR}/font" "${CMAKE_CURRENT_SOURCE_DIR}/include/assets/font.h")

add_library(assets INTERFACE)
target_include_directories(
    assets
    INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
    $<INSTALL_INTERFACE:include>)
