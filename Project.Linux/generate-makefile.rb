class MakefileSchema
  def schema
  <<-MKFILE    
EXECUTABLE = LPP

SOURCES = Main.cpp\
          %SOURCES%

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
MKFILE
  end
end

class MakefileSources
  def create
    Dir.glob(File.join("../Classes/**", "*.cpp"))
  end
end

class MakefileReplacer
  def replace(schema, file_list)
    schema.gsub('%SOURCES%', file_list.join(" \\\n          "))
  end
end

schema = MakefileSchema.new
sources = MakefileSources.new
replacer = MakefileReplacer.new

puts replacer.replace(schema.schema, sources.create)
