file(GLOB_RECURSE DOC_FILES
    CONFIGURE_DEPENDS
    docs/*.md
    mkdocs.yml
)

set(SITE_DIR ${CMAKE_CURRENT_BINARY_DIR}/site)

add_custom_command(
    OUTPUT ${SITE_DIR}/index.html
    COMMAND mkdocs build --site-dir ${SITE_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${DOC_FILES}
)

add_custom_target(docs ALL
    DEPENDS ${SITE_DIR}/index.html
)

add_custom_target(docs-deploy
    DEPENDS docs
    COMMAND mkdocs gh-deploy --force
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)