#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>

namespace gazebo
{
  class Plugin : public WorldPlugin
  {
  private:
    rclcpp::Node::SharedPtr node;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher;
    event::ConnectionPtr updateConnection;
   
    physics::WorldPtr world;
    double valor1 = 0.0;
    double valor2 = 0.0;
    double valor3 = 0.0;

  public:
    Plugin() : WorldPlugin() {}

    void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
    {
      // Inicializa o ROS2
      if (!rclcpp::ok())
      {
        rclcpp::init(0, nullptr);
      }
      node = rclcpp::Node::make_shared("plugin");

      // Criar o publisher
      publisher = node->create_publisher<std_msgs::msg::Float64MultiArray>("/valores", 10);

      // Lê os valores do SDF
      if (_sdf->HasElement("valor1"))
        valor1 = _sdf->Get<double>("valor1");

      if (_sdf->HasElement("valor2"))
        valor2 = _sdf->Get<double>("valor2");

      if (_sdf->HasElement("valor3"))
        valor3 = _sdf->Get<double>("valor3");

      // Conecta a função de update no loop do Gazebo
      updateConnection = event::Events::ConnectWorldUpdateBegin(
          std::bind(&Plugin::OnUpdate, this));
    }

    void OnUpdate()
    {
      // Publica os valores no tópico ROS2
      std_msgs::msg::Float64MultiArray msg;
      msg.data = {valor1, valor2, valor3};

      publisher->publish(msg);
    }
  };

  GZ_REGISTER_WORLD_PLUGIN(Plugin)
}
