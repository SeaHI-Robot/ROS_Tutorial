from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
    ld = LaunchDescription()
    ld.add_action(
        ComposableNodeContainer(
            name="a_component_node",
            namespace="",
            package="rclcpp_components",
            executable="component_container",
            composable_node_descriptions=[
                ComposableNode(
                    package="cpp_components_pkg",
                    plugin="ros2_components_learn::Talker",
                    name="talker_components",
                    extra_arguments=[{"use_intra_process_comms": True}],
                )
            ],
        )
    )
    return ld
