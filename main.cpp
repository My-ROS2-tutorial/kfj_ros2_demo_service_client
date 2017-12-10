/*
 * ROS2 demo service client for adding two integers.
 *
 * Refer to https://github.com/ros2/examples/blob/master/rclcpp/minimal_client/main.cpp
 */

#include<chrono>
#include<cinttypes>
#include<memory>

#include<kfj_ros2_demo_service_interface/srv/add_two_ints.hpp>
#include<rclcpp/rclcpp.hpp>

const static char* g_service_name = "add_two_ints";
/**
 * Class for sending two integers to the server and reading the sum back.
 */
class DemoClient
{
public:
    DemoClient()
    {
        m_node = std::make_shared<rclcpp::Node>("DemoClient");
    }

    int add_two_ints(int a_, int b_)
    {
        using AddTwoInts = kfj_ros2_demo_service_interface::srv::AddTwoInts;
        auto client = m_node->create_client<AddTwoInts>(g_service_name);
        while (!client->wait_for_service(std::chrono::seconds(1)))
        {
            if (!rclcpp::ok())
            {
                printf("Interruption occurred while searching for the server\n");
                return -1;
            }
            printf("Searching for the server...\n");
        }
        auto request = std::make_shared<AddTwoInts::Request>();
        request->a = a_;
        request->b = b_;
        auto result_future = client->async_send_request(request);
        if (rclcpp::spin_until_future_complete(m_node, result_future)
                != rclcpp::executor::FutureReturnCode::SUCCESS)
        {
            printf("Failed to get the response from the server\n");
            return -1;
        }

        return result_future.get()->sum;
    }
private:
    rclcpp::Node::SharedPtr m_node;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    DemoClient demo;
    int a = 3;
    int b = 5;
    auto c = demo.add_two_ints(a, b);
    printf("%d + %d = %d\n", a, b, c);

    rclcpp::shutdown();

    return 0;
}

