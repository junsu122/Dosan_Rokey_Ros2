from setuptools import find_packages, setup

package_name = 'my_cam_pubsub'

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
    maintainer='junsoo122',
    maintainer_email='junsoo122@naver.com',
    description='My first cam pub sub package',
    license='MIT',
    # tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'cam_pub = my_cam_pubsub.cam_pub:main',
            'cam_sub = my_cam_pubsub.cam_sub:main',
        ],
    },
)
