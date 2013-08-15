EXECUTABLE = LPP

SOURCES = Main.cpp          ../Classes/Option.cpp \
          ../Classes/Hero.cpp \
          ../Classes/Joystick.cpp \
          ../Classes/MainMenuScene.cpp \
          ../Classes/ContactListener.cpp \
          ../Classes/GLES-Render.cpp \
          ../Classes/Npc.cpp \
          ../Classes/GameWorldScene.cpp \
          ../Classes/NameWorldScene.cpp \
          ../Classes/AppDelegate.cpp \
          ../Classes/MainMenuSceneLoader.cpp \
          ../Classes/PhysicsWorldScene.cpp

COCOS_ROOT = /usr/include/cocos2dx
INCLUDES = -I.. -I../Classes -I$(COCOS_ROOT)/external/Box2D -I$(COCOS_ROOT)/external -I$(COCOS_ROOT)/extensions -I$(COCOS_ROOT)/external/chipmunk/include/chipmunk -I$(COCOS_ROOT)/extensions/GUI/CCEditBox -I$(COCOS_ROOT)/extensions/GUI/CCControlExtension -I$(COCOS_ROOT)/scripting/lua/cocos2dx_support/ -I$(COCOS_ROOT)/scripting/lua/lua -I$(COCOS_ROOT)/CocosDenshion/include

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d -lbox2d -lcocosdenshion -llua -lextension
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
