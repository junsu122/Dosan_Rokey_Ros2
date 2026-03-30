from setuptools import setup

package_name = 'lane_detect'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='sjs',
    maintainer_email='wordok38@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
    'console_scripts': [
        'publisher_node = lane_detect.publisher_node:main',
        'subscriber_node = lane_detect.subscriber_node:main',
    ],
},
)
