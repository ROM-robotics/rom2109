from setuptools import find_packages, setup

package_name = 'rom2109_simple_commander'

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
    maintainer='mr_robot',
    maintainer_email='server01.psa1981@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'go_lite_tot = rom2109_simple_commander.go_lite_tot:main',
            'talker = rom2109_simple_commander.publisher_member_function:main',
        ],
    },
)
