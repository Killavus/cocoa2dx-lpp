LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/ContactListener.cpp \
                   ../../Classes/GameWorldScene.cpp \
                   ../../Classes/GLES-Render.cpp \
                   ../../Classes/Hero.cpp \
                   ../../Classes/Joystick.cpp \
                   ../../Classes/MainMenuScene.cpp \
                   ../../Classes/MainMenuSceneLoader.cpp \
                   ../../Classes/Npc.cpp \
                   ../../Classes/Option.cpp \
                   ../../Classes/PhysicsWorldScene.cpp \
                   ../../Classes/NameWorldScene.cpp
                                  
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../../extensions \
					$(LOCAL_PATH)/../../../extensions/GUI/CCEditBox \
					$(LOCAL_PATH)/../../../external/Box2D
    

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static box2d_static cocos_extension_static cocos_lua_static

            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions) \
$(call import-module,external/Box2D)
$(call import-module,scripting/lua/proj.android)


