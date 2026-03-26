from ros2env.api import get_all_env_list
from ros2env.api import set_ros_env
from ros2env.verb import VerbExtension


class SetVerb(VerbExtension):
    """Set ROS environment variables."""

    def add_arguments(self, parser, cli_name):
        parser.add_argument("env_name", help="Name of the environment variable")
        parser.add_argument("value", help="Value of the environment variable")

    def main(self, *, args):
        if args.env_name or args.value:
            message = set_ros_env(args.env_name, args.value)
            print("[Changed ROS environment variable]:")
            print(message)
        message = get_all_env_list()
        print("\n[Current ROS environment variable]:")
        print(message)
