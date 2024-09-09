import os
from glob import glob
from setuptools import find_packages, setup

package_name = 'py_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.py'))),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.xml'))),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.yaml')))
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='syw',
    maintainer_email='syw@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "talker_py = py_pkg.talker:main"
        ],
    },
)