CXX=clang++
EXE = 3d_model_viewer
IMGUI_DIR = ./imgui
IMGUI_FILEBROWSER_DIR = ./imgui-filebrowser

SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SOURCES += ./shader/shader.cpp
SOURCES += ./laoder/loader.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

CXXFLAGS = -std=c++17 -pedantic -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -I$(IMGUI_FILEBROWSER_DIR)  -I./includes
CXXFLAGS += -g -Wall -Wformat 
CXXFLAGS += $(shell pkg-config --cflags glfw3 glew glm)
LIBS = $(shell pkg-config --libs glfw3 glew glm) 

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux) 
	LIBS += -lGL 
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:shader/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:loader/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXE) 
