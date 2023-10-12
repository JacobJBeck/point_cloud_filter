#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"

void filter_cb(const sensor_msgs::PointCloud2::ConstPtr &msg)
{
    ROS_INFO("Hit callback");
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "point_cloud_filter");
    ros::NodeHandle nh;
    auto sub = nh.subscribe("raw_points", 100, filter_cb);
    ros::spin();
    return 0;
}