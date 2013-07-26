class MakefileSchema
  def schema
  <<-MKFILE    
EXECUTABLE = LPP

INCLUDES = -I.. -I../Classes

SOURCES = %SOURCES%

COCOS_ROOT = /usr/include/cocos2dx
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d
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
    Dir.glob(File.join("../**", "*.cpp"))
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
