from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='f310_gamepad',
            # namespace='f310_gamepad',
            executable='f310_gamepad',
            # name='f310_gamepad',
        ),
        Node(
            package='joy',
            # namespace='joy',
            executable='joy_node',
            # name='joy_node',
        ),
        Node(
            package='robot_command',
            # namespace='robot_command',
            executable='move_command',
            # name='move_command',
            remappings=[
            ('/move_command', '/cmd_vel'),
            ]
        ),
    ])