#include <gazebo_things/t265.h>
#include <gazebo_things/fake_rf.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "gazebo_sensors");
    ros::NodeHandle nh("~");

    if (!nh.hasParam("link_name"))
        nh.setParam("link_name", "iris_demo::realsense_biasa::base_link");
    if (!nh.hasParam("frame_name"))
        nh.setParam("frame_name", "rs_link");
    if (!nh.hasParam("noise")) {
        ROS_WARN("noise param not found! using 'false'!");
        nh.setParam("noise", false);
    }
    if (!nh.hasParam("noise_max"))
        nh.setParam("noise_max", 0.2);
    if (!nh.hasParam("scale_max"))
        nh.setParam("scale_max", 0.1);
    if (!nh.hasParam("noise_z_max")) {
        double noise_max;
        nh.getParam("noise_max", noise_max);
        nh.setParam("noise_z_max", noise_max);
    }
    if (!nh.hasParam("scale_z_max")) {
        double scale_max;
        nh.getParam("scale_max", scale_max);
        nh.setParam("scale_z_max", scale_max);
    }

    t265 fisheye(&nh);

    if (!nh.hasParam("rf_depan"))
        nh.setParam("rf_depan", false);
    if (!nh.hasParam("rf_bawah"))
        nh.setParam("rf_bawah", false);

    //RF SAMPING
    if (!nh.hasParam("rf_kanan"))
        nh.setParam("rf_kanan", false);
    if (!nh.hasParam("rf_kiri"))
        nh.setParam("rf_kiri", false);
                
    if (!nh.hasParam("tembok_y"))
        nh.setParam("tembok_y", 10.0);
        
    if (!nh.hasParam("bawah_topic"))
        nh.setParam("bawah_topic", "/gazebo_things/rf_bawah");
    if (!nh.hasParam("depan_topic"))
        nh.setParam("depan_topic", "/gazebo_things/rf_depan");

        //Test TOpic
    if (!nh.hasParam("test_topic"))
        nh.setParam("test_topic", "/mavros/distance_sensor/rangefinder_pub");
    if (!nh.hasParam("atas_topic"))
        nh.setParam("atas_topic", "/gazebo_things/rf_atas");

    //RF SAMPING TOPIC
    if (!nh.hasParam("kanan_topic"))
        nh.setParam("kanan_topic", "/gazebo_things/rf_kanan");
    if (!nh.hasParam("kiri_topic"))
        nh.setParam("kiri_topic", "/gazebo_things/rf_kiri");        

    rangefinder fake_rf(&nh);

    ros::Rate rate(50);
    while (ros::ok()) {
        ros::spinOnce();
        fisheye.publishOnce();
        // fisheye.sendBroadcast();
        fake_rf.publishOnce();
        rate.sleep();
    }

    return 0;   // should never reach here
}
