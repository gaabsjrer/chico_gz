#include <gazebo/gui/gui.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/common/common.hh>
#include <gazebo/gazebo.hh>

namespace gazebo
{
  class MeuPluginControle : public GUIPlugin
  {
  private:
    transport::NodePtr node;
    transport::PublisherPtr pub;
    double valor1 = 10.5;
    double valor2 = 20.0;
    double valor3 = 30.7;

  public:
    MeuPluginControle() : GUIPlugin()
    {
      // Criar interface GUI no Gazebo
      this->setStyleSheet("background-color: white; padding: 10px;");
      QVBoxLayout *mainLayout = new QVBoxLayout();

      QLabel *label1 = new QLabel("Valor 1:");
      QSlider *slider1 = new QSlider(Qt::Horizontal);
      slider1->setRange(0, 100);
      slider1->setValue(valor1);
      connect(slider1, &QSlider::valueChanged, this, &MeuPluginControle::SetValor1);

      QLabel *label2 = new QLabel("Valor 2:");
      QSlider *slider2 = new QSlider(Qt::Horizontal);
      slider2->setRange(0, 100);
      slider2->setValue(valor2);
      connect(slider2, &QSlider::valueChanged, this, &MeuPluginControle::SetValor2);

      QLabel *label3 = new QLabel("Valor 3:");
      QSlider *slider3 = new QSlider(Qt::Horizontal);
      slider3->setRange(0, 100);
      slider3->setValue(valor3);
      connect(slider3, &QSlider::valueChanged, this, &MeuPluginControle::SetValor3);

      mainLayout->addWidget(label1);
      mainLayout->addWidget(slider1);
      mainLayout->addWidget(label2);
      mainLayout->addWidget(slider2);
      mainLayout->addWidget(label3);
      mainLayout->addWidget(slider3);
      this->setLayout(mainLayout);
    }

    void SetValor1(int v)
    {
      valor1 = v;
      PublishValores();
    }

    void SetValor2(int v)
    {
      valor2 = v;
      PublishValores();
    }

    void SetValor3(int v)
    {
      valor3 = v;
      PublishValores();
    }

    void PublishValores()
    {
      sdf::SDF sdf;
      sdf.SetFromString("<sdf version='1.6'><world name='default'>"
                        "<valor1>" + std::to_string(valor1) + "</valor1>"
                        "<valor2>" + std::to_string(valor2) + "</valor2>"
                        "<valor3>" + std::to_string(valor3) + "</valor3>"
                        "</world></sdf>");

      transport::PublisherPtr pub = node->Advertise<gazebo::msgs::WorldControl>("/gazebo/world_control");
      gazebo::msgs::WorldControl msg;
      msg.set_step(true);
      pub->Publish(msg);
    }
  };

  GZ_REGISTER_GUI_PLUGIN(MeuPluginControle)
}
