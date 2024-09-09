import launch
import launch_ros.actions

def generate_launch_description():
    return launch.LaunchDescription([
        launch_ros.actions.Node(
            package='py_pkg',
            executable='talker_py',
            name='talker_py',
            )
        ])
