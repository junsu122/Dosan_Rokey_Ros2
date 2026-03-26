from ros2env.api import get_all_env_list
from ros2env.api import get_dds_env_list
from ros2env.api import get_ros_env_list
from ros2env.verb import VerbExtension


class ListVerb(VerbExtension):

    def add_arguments(self, parser, cli_name):
        parser.add_argument(
            "-a",
            "--all",
            action="store_true",
            help="Display all environment variables.",
        )
        parser.add_argument(
            "-r",
            "--ros-env",
            action="store_true",
            help="Display the ROS environment variables.",
        )
        parser.add_argument(
            "-d",
            "--dds-env",
            action="store_true",
            help="Display the DDS environment variables.",
        )

    def main(self, *, args):
        if args.ros_env:
            message = get_ros_env_list()
        elif args.dds_env:
            message = get_dds_env_list()
        else:
            message = get_all_env_list()
        print(message)
