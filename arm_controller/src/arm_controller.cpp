#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>



void jointStateCallback(const sensor_msgs::JointState::ConstPtr& joint_state) {
   
   ROS_INFO("\nReceived joint positions:");
    for (size_t i = 0; i < joint_state->position.size(); i++) {
        ROS_INFO("Joint %zu: %f", i, joint_state->position[i]);
    }
}
   
 int main(int argc, char** argv) {
    ros::init(argc, argv, "arm_controller");
    ros::NodeHandle nh;
    ros::Rate loop_rate(10);

    // Create a publisher to send joint position commands
    ros::Publisher joint0_pub = nh.advertise<std_msgs::Float64>("/arm/joint0_position_controller/command", 1);
  

    // Create a subscriber to receive joint state information
    ros::Subscriber joint_state_sub = nh.subscribe("joint_states", 10, jointStateCallback);

    // Implement any necessary control logic
    while (ros::ok())
  {

   // Genera un comando per l'articolazione di base (j0) per far girare il braccio in senso orario
    std_msgs::Float64 joint0_command;
    joint0_command.data = 500.0; // Ad esempio, imposta un valore negativo per far girare l'articolazione in senso orario

    // Pubblica il comando
    joint0_pub.publish(joint0_command);

    // Attendi il tempo necessario per mantenere la frequenza desiderata
    
    loop_rate.sleep();
  }


    ros::spin();

    return 0;
}
