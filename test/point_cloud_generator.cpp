#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

typedef pcl::PointCloud<pcl::PointXYZI> PointCloud;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "point_cloud_generator");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<PointCloud>("raw_points", 1);

    PointCloud::Ptr msg(new PointCloud);
    msg->header.frame_id = "world";
    msg->height = msg->width = 1;

    pcl::PointXYZI pt;
    pt.x = 1.0;
    pt.y = 2.0;
    pt.z = 3.0;
    pt.intensity = 0.5;

    msg->points.push_back(pt);

    ros::Rate loop_rate(4);
    while (nh.ok())
    {
        pcl_conversions::toPCL(ros::Time::now(), msg->header.stamp);
        pub.publish(*msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}