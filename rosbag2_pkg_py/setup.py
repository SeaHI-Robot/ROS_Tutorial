from setuptools import find_packages, setup

package_name = 'rosbag2_pkg_py'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='syw',
    maintainer_email='12012324@mail.sustech.edu.cn',
    description='TODO: Package description',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "bag_recorder = rosbag2_pkg_py.bag_recorder:main",
            "data_generator = rosbag2_pkg_py.data_generator:main",
            "data_generator_and_rate_control = rosbag2_pkg_py.data_generator_and_rate_control:main",
        ],
    },
)
