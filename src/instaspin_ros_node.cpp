#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Float32.h"

#include "instaspin_serial.h"

#include <sstream>

std::string port;
int motor_id;
int baud;

std::stringstream motor_id_ss;
InstaspinSerial instaspin("/dev/ttyUSB0", 115200);

void run_identify_callback(const std_msgs::Bool::ConstPtr msg);
void enable_speed_control_callback(const std_msgs::Bool::ConstPtr msg);
void speed_ref_callback(const std_msgs::Float32::ConstPtr msg);
void max_acceleration_callback(const std_msgs::Float32::ConstPtr msg);

int main(int argc, char **argv)
{
    ros::init(argc, &argv[0], "instaspin");
    ros::NodeHandle n("~");

    n.param("motor_id", motor_id, 0);
    n.param("port", port, (std::string)"/dev/ttyUSB0");
    n.param("baud", baud, 395000);

    if(motor_id == 0){
        ROS_ERROR("Motor ID is not set! Abort");
        return -1;
    }
    motor_id_ss<<motor_id;

    ros::Subscriber run_identify_sub = n.subscribe("motor"+motor_id_ss.str()+"/flag/run", 100, run_identify_callback);
    ros::Subscriber enable_speed_control_sub = n.subscribe("motor"+motor_id_ss.str()+"/flag/enableSpeedControl", 100, enable_speed_control_callback);
    ros::Subscriber speed_ref_sub = n.subscribe("motor"+motor_id_ss.str()+"/speedRef", 100, speed_ref_callback);
    ros::Subscriber max_acceleration_sub = n.subscribe("motor"+motor_id_ss.str()+"/maxAcceleration", 100, max_acceleration_callback);

    instaspin.open();

    ros::spin();
}


void run_identify_callback(const std_msgs::Bool::ConstPtr msg){
    instaspin.setValue((uint8_t)0, (uint8_t)TYPE_BOOL, (void*)(&(msg->data)));
}

void enable_speed_control_callback(const std_msgs::Bool::ConstPtr msg){
    if(msg->data){

    }
    else{

    }
}

void speed_ref_callback(const std_msgs::Float32::ConstPtr msg){
    instaspin.setValue((uint8_t)2, (uint8_t)TYPE_QVALUE, (void*)(&(msg->data)));
}

void max_acceleration_callback(const std_msgs::Float32::ConstPtr msg){

}

