include(ExternalProject)

# The dependency has no CMake build files, so download and build it as an
# external Makefile project. Pinning a tag makes the firmware build repeatable.
set(SCPI_SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/scpi-parser-src")
set(SCPI_BUILD_DIR "${SCPI_SOURCE_DIR}/libscpi")
set(SCPI_ARCHIVE "${SCPI_BUILD_DIR}/dist/libscpi.a")

find_program(SCPI_MAKE_EXECUTABLE NAMES make gmake REQUIRED)

ExternalProject_Add(scpi-parser-build
    GIT_REPOSITORY https://github.com/j123b567/scpi-parser.git
    GIT_TAG v2.3
    SOURCE_DIR "${SCPI_SOURCE_DIR}"
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE TRUE
    # The upstream Makefile's "static" target creates libscpi.a. Run it from
    # libscpi because that is where the Makefile and its source files live.
    # CMake's compiler variables are passed as environment variables because
    # the Makefile reads CC, AR, and RANLIB rather than CMake target settings.
    # CFLAGS combines the toolchain's common flags with the active
    # configuration flags (for example, -Og -g3 for Debug).
    BUILD_COMMAND
        ${CMAKE_COMMAND} -E env
        "CC=${CMAKE_C_COMPILER}"
        "AR=${CMAKE_AR}"
        "RANLIB=${CMAKE_RANLIB}"
        "CFLAGS=${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_${CMAKE_BUILD_TYPE}}"
        ${SCPI_MAKE_EXECUTABLE}
        -C "${SCPI_BUILD_DIR}"
        static
    BUILD_BYPRODUCTS "${SCPI_ARCHIVE}"
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)

# ExternalProject_Add creates a build-step target, not a linkable library.
# The source tree is downloaded at build time, so its include directory does
# not exist during CMake generation. Pass it as an interface compiler option
# rather than an INTERFACE_INCLUDE_DIRECTORIES entry, which CMake validates
# immediately for imported targets.
add_library(scpi-parser STATIC IMPORTED GLOBAL)
set_target_properties(scpi-parser PROPERTIES
    IMPORTED_LOCATION "${SCPI_ARCHIVE}"
    INTERFACE_COMPILE_OPTIONS "-I${SCPI_BUILD_DIR}/inc"
)
add_dependencies(scpi-parser scpi-parser-build)
