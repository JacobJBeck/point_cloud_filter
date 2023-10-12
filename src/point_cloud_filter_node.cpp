#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PointCloud<pcl::PointXYZI> PointCloud;

void filter_cb(const PointCloud::ConstPtr &msg)
{
    ROS_INFO("Hit callback");
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "point_cloud_filter");
    ros::NodeHandle nh;
    auto sub = nh.subscribe("raw_points", 1, filter_cb);
    ros::spin();
    return 0;
}