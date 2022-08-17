EXE = 3d_model_viewer
BUILD_DIR = ../build
IMGUI_DIR = ./imgui
IMGUI_FILEBROWSER_DIR = ./imgui-filebrowser
DIRS = . ./utils/ ./shader/ ./loader/ ./includes/

SOURCES = main.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
SOURCES += ./shader/shader.cpp
SOURCES += ./loader/loader.cpp
SOURCES += ./utils/utils.cpp

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

%.o:utils/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)

$(EXE): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CXX) -o $(BUILD_DIR)/$@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: install
install: all
	install -m 557 $(BUILD_DIR)/$(EXE) ~/Desktop

.PHONY: uninstall
uninstall:
	rm -rf ~/Desktop/$(EXE)

.PHONY: dvi
dvi: $(DIRS)
	mkdir -p ../docs
	doxygen Doxyfile

.PHONY: dist
dist: $(DIRS) Makefile main.cpp
	mkdir -p ../dist
	tar cvzf ../dist/3d_model_viewer_1.0.tgz *

.PHONY: tests
tests:
	$(MAKE) -f test.mk 

gcov_report:
	$(MAKE) -f test.mk gcov_report

clean:
	rm -f  $(OBJS) imgui.ini
	$(MAKE) -f test.mk clean

fclean: clean
	rm -rf $(BUILD_DIR)
	rm -rf ../dist
	rm -rf ../docs
