#include <bits/stdc++.h>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "smkm_interfaces/msg/gamepad.hpp"

class MoveCommand : public rclcpp::Node
{
private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::Subscription<smkm_interfaces::msg::Gamepad>::SharedPtr subscriber_;

public:
    MoveCommand() : Node("move_command")
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("move_command", 1);
        subscriber_ = this->create_subscription<smkm_interfaces::msg::Gamepad>("f310_gamepad", 1, [this](const smkm_interfaces::msg::Gamepad::SharedPtr msg){
            geometry_msgs::msg::Twist move_command;
            move_command.linear.x = msg->l_stick_up * 100;
            // move_command.linear.y = msg.l_stick_left * 100;
            move_command.angular.z = msg->l_stick_left * 100;
    
            publisher_->publish(move_command);
        });
    }
};

int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MoveCommand>();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}