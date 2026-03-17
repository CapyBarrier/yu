file(GLOB_RECURSE DOC_FILES
    CONFIGURE_DEPENDS
    docs/*.md
    mkdocs.yml
)

set(SITE_DIR ${CMAKE_CURRENT_BINARY_DIR}/site)

add_custom_command(
    OUTPUT ${SITE_DIR}/index.html
    COMMAND mkdocs build
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${DOC_FILES}
)

add_custom_target(docs ALL
    DEPENDS ${SITE_DIR}/index.html
)