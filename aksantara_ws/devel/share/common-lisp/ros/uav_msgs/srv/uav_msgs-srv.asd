
(cl:in-package :asdf)

(defsystem "uav_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "DetectObject" :depends-on ("_package_DetectObject"))
    (:file "_package_DetectObject" :depends-on ("_package"))
    (:file "DetectQR" :depends-on ("_package_DetectQR"))
    (:file "_package_DetectQR" :depends-on ("_package"))
    (:file "PilotOverride" :depends-on ("_package_PilotOverride"))
    (:file "_package_PilotOverride" :depends-on ("_package"))
    (:file "SetCurrent" :depends-on ("_package_SetCurrent"))
    (:file "_package_SetCurrent" :depends-on ("_package"))
  ))