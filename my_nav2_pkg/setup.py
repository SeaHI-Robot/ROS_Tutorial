from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'my_nav2_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[pxy][yma]*'))),
        (os.path.join('share', package_name, 'maps'), glob(os.path.join('maps', '*'))),
        (os.path.join('share', package_name, 'params'), glob(os.path.join('params', '*.yaml'))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='SiyuanWang',
    maintainer_email='12012324@mail.sustech.edu.cn',
    description='EE211-24Fall-Lab-Session-Week08: SLAM & Navigation',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "nav_to_pose = my_nav2_pkg.nav_to_pose:main",
        ],
    },
)
