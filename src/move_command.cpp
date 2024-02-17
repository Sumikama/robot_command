#include <bits/stdc++.h>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "smkm_interfaces/msg/gamepad.hpp"

int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("move_command");
    auto publisher = node->create_publisher<geometry_msgs::msg::Twist>("move_command", 1);
    geometry_msgs::msg::Twist move_command;
    auto subscriber = node->create_subscription<smkm_interfaces::msg::Gamepad>("f310_gamepad", 1, [&](const smkm_interfaces::msg::Gamepad& msg){
        move_command.linear.x = msg.l_stick_up * 100;
        // move_command.linear.y = msg.l_stick_left * 100;
        move_command.angular.z = msg.l_stick_left * 100;

        publisher->publish(move_command);
    });

    rclcpp::spin(node);
    // node = nullptr;
    rclcpp::shutdown();
    return 0;
}