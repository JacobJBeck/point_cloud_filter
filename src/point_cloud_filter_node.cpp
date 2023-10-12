#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PointCloud<pcl::PointXYZI> PointCloud;

ros::Publisher pub;

void filter_cb(const PointCloud::ConstPtr &msg)
{
    PointCloud::Ptr filtered(new PointCloud);
    filtered->header.frame_id = "world";
    filtered->height = 1;

    for (const auto pt : msg->points)
    {
        if (pt.intensity < 0.7)
            filtered->points.push_back(pt);
    }

    filtered->width = filtered->points.size();

    pub.publish(filtered);
    ROS_INFO_STREAM("Input cloud size: " << msg->points.size()
        << ", output cloud size: " << filtered->points.size() << std::endl);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "point_cloud_filter");
    ros::NodeHandle nh;
    auto sub = nh.subscribe("raw_points", 1, filter_cb);
    pub = nh.advertise<PointCloud>("filtered_points", 1);
    ros::spin();
    return 0;
}