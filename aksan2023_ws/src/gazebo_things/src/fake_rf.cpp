#include <gazebo_things/fake_rf.h>

rangefinder::rangefinder(ros::NodeHandle* nh): nh_(*nh), real_pose_(std::vector<double>(3, 0)) {
    
    sub_ = nh_.subscribe("/gazebo_things/real_pose", 1, &rangefinder::callback, this);

    nh_.getParam("rf_depan", rf_depan_);
    nh_.getParam("rf_bawah", rf_bawah_);

     //RF SAMPING
    nh_.getParam("rf_kanan", rf_kanan_);
    nh_.getParam("rf_kiri", rf_kiri_);
    nh_.getParam("kanan_topic", kanan_topic_);
    nh_.getParam("kiri_topic", kiri_topic_);    

    //Test
    nh_.getParam("test_rf", test_rf_);
    nh_.getParam("rf_atas", rf_atas_);

    nh_.getParam("tembok_x", tembok_x_);
    nh_.getParam("depan_topic", depan_topic_);
    nh_.getParam("bawah_topic", bawah_topic_);
    //Test
    nh_.getParam("test_topic", test_topic_);
    nh_.getParam("atas_topic", atas_topic_);

    if (rf_depan_)
        rf_depan_pub_ = nh_.advertise<sensor_msgs::Range>(
            depan_topic_, 1, true);
    if (rf_bawah_)
        rf_bawah_pub_ = nh_.advertise<sensor_msgs::Range>(
            bawah_topic_, 1, true);
    //test advertise
    if (test_rf_)
        test_pub_ = nh_.advertise<sensor_msgs::Range>(
            test_topic_, 1, true);    
    if (rf_atas_)
        atas_pub_ = nh_.advertise<sensor_msgs::Range>(
            atas_topic_, 1, true); 
    //RF SAMPING ADVERTISE
    if (rf_kanan_)
        kanan_pub_ = nh_.advertise<sensor_msgs::Range>(
            kanan_topic_, 1, true);
    if (rf_kiri_)
        kiri_pub_ = nh_.advertise<sensor_msgs::Range>(
            kiri_topic_, 1, true);
}

void rangefinder::callback(const geometry_msgs::Pose &msg) {
    real_pose_.at(0) = msg.position.x;
    real_pose_.at(1) = msg.position.y;
    real_pose_.at(2) = msg.position.z;
}

void rangefinder::publishOnce() {
    sensor_msgs::Range range_depan, range_bawah, range_atas, range_kanan, range_kiri;
    range_depan.range = tembok_x_ - real_pose_.at(0);
    range_bawah.range = real_pose_.at(2);
    range_atas.range = 6.0 - real_pose_.at(2);
    range_kanan.range = 1.25 - (-1 * real_pose_.at(1));
    range_kiri.range =1.25 - real_pose_.at(1);
    

    if (rf_depan_)
        rf_depan_pub_.publish(range_depan);
    if (rf_bawah_)
        rf_bawah_pub_.publish(range_bawah);
        
        //Test Publish
    if (test_rf_)
        test_pub_.publish(range_bawah);
    if (rf_atas_)
        atas_pub_.publish(range_atas);
        
     //RF SAMPING PUBLISH
    if (rf_kanan_)
        kanan_pub_.publish(range_kanan);
    if (rf_kiri_)
        kiri_pub_.publish(range_kiri);        
                   
}