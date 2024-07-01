
(cl:in-package :asdf)

(defsystem "uav_msgs-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :sensor_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "CameraInfoExtended" :depends-on ("_package_CameraInfoExtended"))
    (:file "_package_CameraInfoExtended" :depends-on ("_package"))
    (:file "DzPosition" :depends-on ("_package_DzPosition"))
    (:file "_package_DzPosition" :depends-on ("_package"))
    (:file "LidarsReadings" :depends-on ("_package_LidarsReadings"))
    (:file "_package_LidarsReadings" :depends-on ("_package"))
    (:file "MissionParams" :depends-on ("_package_MissionParams"))
    (:file "_package_MissionParams" :depends-on ("_package"))
    (:file "PayloadPosition" :depends-on ("_package_PayloadPosition"))
    (:file "_package_PayloadPosition" :depends-on ("_package"))
    (:file "PayloadROI" :depends-on ("_package_PayloadROI"))
    (:file "_package_PayloadROI" :depends-on ("_package"))
    (:file "PrecLand" :depends-on ("_package_PrecLand"))
    (:file "_package_PrecLand" :depends-on ("_package"))
    (:file "PrecLoit" :depends-on ("_package_PrecLoit"))
    (:file "_package_PrecLoit" :depends-on ("_package"))
    (:file "ReadQR" :depends-on ("_package_ReadQR"))
    (:file "_package_ReadQR" :depends-on ("_package"))
  ))