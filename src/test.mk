CXX 			:= 		clang++

GCOV_FLAGS  	:= 		--coverage -fprofile-instr-generate -fcoverage-mapping
ASAN			:=		-g -fsanitize=address
CFLAGS			:=		-std=c++11 -Wall -Werror -Wextra  #$(ASAN)
CFLAGS 			+= 		$(shell pkg-config --cflags gtest glm glew glfw3)
LDFLAGS 		:= 		$(shell pkg-config --libs gtest glm glew glfw3) 

TARGET			:= 		test
TARGET_LIB 		:= 		s21_3d_model_viewer.a

MODULES			:= 		$(shell find . -type d | grep -E "utils|loader")
TEST_MODULES	:= 		$(shell find . -type d | grep -E "tests")

SRC				:= 		$(notdir $(shell find $(MODULES) -maxdepth 1 -name "*.cpp"))
INC				:=		$(shell find $(MODULES) -maxdepth 1 -name "*.hpp")
OBJS			:=		$(SRC:%.cpp=%.o)
OBJS_DIR		:= 		./objs

TEST_SRC		:= 		$(notdir $(shell find $(TEST_MODULES) -maxdepth 1 -name "*.cpp"))
TEST_INC		:= 		$(shell find $(TEST_MODULES) -maxdepth 1 -name "*.hpp")
TEST_OBJS		:=		$(TEST_SRC:%.cpp=%.o)

vpath %.cpp 	$(MODULES) : $(TEST_MODULES)
vpath %.o 	$(OBJS_DIR)	

all				: $(TARGET) 

$(TARGET)		: $(TARGET_LIB) $(TEST_OBJS)
					$(CXX) --coverage -fprofile-instr-generate  -o $@  $(addprefix $(OBJS_DIR)/, $(TEST_OBJS)) $(TARGET_LIB) $(LDFLAGS) 
					./test
				
%.o 			: %.cpp $(INC) $(OBJS_DIR)
					$(CXX) $(GCOV_FLAGS) $(CFLAGS) -o $(addprefix $(OBJS_DIR)/, $@) -c $<
$(OBJS_DIR) 	:
				mkdir -p $(OBJS_DIR)

$(TARGET_LIB)	: $(OBJS)
					ar -vrcs $(TARGET_LIB) $(addprefix $(OBJS_DIR)/, $(OBJS))
					ranlib $(TARGET_LIB)
	

gcov_report: $(TARGET)
	llvm-profdata merge -sparse default.profraw -o default.profdata
	llvm-cov show ./test -instr-profile=default.profdata utils/utils.cpp loader/loader.cpp  -use-color --format=html > coverage.html
	open coverage.html


debug			:
					$(info TARGET = $(TARGET))
					$(info MODULES = $(MODULES))
					$(info SRC = $(SRC))
					$(info INC = $(INC))
					$(info OBJS = $(OBJS))
					$(info TARGET_LIB = $(TARGET_LIB))
					$(info TEST_MODULES = $(TEST_MODULES))
					$(info TEST_SRC = $(TEST_SRC))
					$(info TEST_INC = $(TEST_INC))
					$(info TEST_OBJS = $(TEST_OBJS))

clean			:
					rm -rf $(OBJS_DIR)
					rm -rf $(TARGET_LIB)
					rm -rf $(TARGET)
					rm -rf coverage*
					rm -rf default.*

re: clean $(TARGET)

.PHONY: tests test all gcov_report re clean debug 
