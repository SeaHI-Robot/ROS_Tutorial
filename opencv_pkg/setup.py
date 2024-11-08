from setuptools import find_packages, setup

package_name = 'opencv_pkg'

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
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "camera_publisher = opencv_pkg.camera_publisher:main",
            "camera_subscriber = opencv_pkg.camera_subscriber:main",
        ],
    },
)
