from setuptools import find_packages
from setuptools import setup

setup(
    name='bin_interfaces',
    version='0.0.0',
    packages=find_packages(
        include=('bin_interfaces', 'bin_interfaces.*')),
)
