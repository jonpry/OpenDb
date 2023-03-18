import inspect
import os
import sys
from pathlib import Path

import cmake_build_extension
import setuptools

init_py = inspect.cleandoc(
    """
from .odb_py import *
    """
)

# Extra options passed to the CI/CD pipeline that uses cibuildwheel
CIBW_CMAKE_OPTIONS = []
if "CIBUILDWHEEL" in os.environ and os.environ["CIBUILDWHEEL"] == "1":

    # The manylinux variant runs in Debian Stretch and it uses lib64 folder
    if sys.platform == "linux":
        CIBW_CMAKE_OPTIONS += ["-DCMAKE_INSTALL_LIBDIR=lib"]

    # Eigen is not found when installed with vcpkg because we don't pass the toolchain.
    # Passing directly the right folder as workaround. This is meant to work just in CI.
    if os.name == "nt":
        CIBW_CMAKE_OPTIONS += [
            "-DEigen3_DIR:PATH=C:/vcpkg/packages/eigen3_x64-windows/share/eigen3",
        ]

# This example is compliant with PEP517 and PEP518. It uses the setup.cfg file to store
# most of the package metadata. However, build extensions are not supported and must be
# configured in the setup.py.
setuptools.setup(
    # The resulting "mymath" archive contains two packages: mymath_swig and mymath_pybind.
    # This approach separates the two bindings types, typically just one of them is used.
    ext_modules=[
        cmake_build_extension.CMakeExtension(
            # This could be anything you like, it is used to create build folders
            name="SwigBindings",
            # Name of the resulting package name (import mymath_swig)
            install_prefix="opendbpy",
            # Writes the content to the top-level __init__.py
            write_top_level_init=init_py,
            # Selects the folder where the main CMakeLists.txt is stored
            # (it could be a subfolder)
            source_dir=str(Path(__file__).parent.absolute()),
            cmake_configure_options=[
                # This option points CMake to the right Python interpreter, and helps
                # the logic of FindPython3.cmake to find the active version
                f"-DPython3_ROOT_DIR={Path(sys.prefix)}",
                "-DCALL_FROM_SETUP_PY:BOOL=ON",
                "-DBUILD_SHARED_LIBS:BOOL=OFF",
                # Select the bindings implementation
                "-DEXAMPLE_WITH_SWIG:BOOL=ON",
                "-DEXAMPLE_WITH_PYBIND11:BOOL=OFF",
            ]
            + CIBW_CMAKE_OPTIONS,
        ),
    ],
    cmdclass=dict(
        # Enable the CMakeExtension entries defined above
        build_ext=cmake_build_extension.BuildExtension,
        # If the setup.py or setup.cfg are in a subfolder wrt the main CMakeLists.txt,
        # you can use the following custom command to create the source distribution.
        # sdist=cmake_build_extension.GitSdistFolder
    ),
)
