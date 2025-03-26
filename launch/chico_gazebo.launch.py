import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, SetLaunchConfiguration
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    gazebo_model_path = '/home/gabriel/chico_ws/src/chico_gz/models'
    
    world_file = os.path.join(
        get_package_share_directory('chico_gz'), 'worlds', 'river_1.sdf'
    )

    return LaunchDescription([
        SetLaunchConfiguration(
            name='gazebo_model_path',
            value=gazebo_model_path
        ),
        ExecuteProcess(
            additional_env={'GAZEBO_MODEL_PATH': LaunchConfiguration('gazebo_model_path')},
            cmd=['gazebo', '--verbose', world_file],
            output='screen',
        ),
    ])
