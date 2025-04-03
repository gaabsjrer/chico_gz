import os

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    pkg_share = FindPackageShare(package='laser_rahcm_simulation').find('laser_rahcm_simulation')
    worlds_dir = os.path.join(pkg_share, 'worlds')
    default_world = 'river.sdf'
    
    world_gazebo_arg = DeclareLaunchArgument(
        name="world", 
        default_value=default_world, 
        description="Name of the Gazebo world file located in the worlds directory"
    )
    
    world_gazebo_path = PathJoinSubstitution([worlds_dir, LaunchConfiguration("world")])
    
    world_models_path = os.path.join(pkg_share, 'models')
    install_dir = FindPackageShare(package='laser_rahcm_simulation').find('laser_rahcm_simulation')

    os.environ['GAZEBO_MODEL_PATH'] = world_models_path
    os.environ['GAZEBO_PLUGIN_PATH'] = os.environ.get('GAZEBO_PLUGIN_PATH', '') + ':' + install_dir + '/lib'

    print("GAZEBO MODEL PATH==", os.environ["GAZEBO_MODEL_PATH"])
    print("GAZEBO PLUGIN PATH==", os.environ["GAZEBO_PLUGIN_PATH"])

    gazebo_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(FindPackageShare("gazebo_ros").find("gazebo_ros"), "launch", "gazebo.launch.py")
        ]),
        launch_arguments={"world": world_gazebo_path}.items(),
    )

    return LaunchDescription([
        world_gazebo_arg,
        gazebo_launch,
    ])
