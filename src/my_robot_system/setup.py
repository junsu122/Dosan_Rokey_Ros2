from setuptools import find_packages, setup
import os
from glob import glob

package_name = "my_robot_system"

setup(
    name=package_name,
    version="0.0.0",
    packages=find_packages(exclude=["test"]),
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
        (os.path.join("share", package_name, "launch"), glob("launch/*.py")),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="i",
    maintainer_email="i@todo.todo",
    description="TODO: Package description",
    license="TODO: License declaration",
    # tests_require=["pytest"],
    
    entry_points={
        "console_scripts": [
            "sensor_node = my_robot_system.sensor_node:main",
            "manager_node = my_robot_system.manager_node:main",
            "cooler_service = my_robot_system.cooler_service:main",
            "switch_action_server = my_robot_system.switch_action_server:main",
        ],
    },
)
