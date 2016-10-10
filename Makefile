
# ========= define =========
BUILD_DIR = build
HEADER_DIR = include
SRC_DIR = src
TEST_DIR = tests
SAMPLE_DIR = samples

# ========= files =========
SRCS = $(wildcard $(SRC_DIR)/*/*.cpp)
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp $(TEST_DIR)/*/*.cpp)
TEST_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(TEST_SRCS))

SAMPLE_SRCS = $(wildcard $(SAMPLE_DIR)/*.cpp)

DEPEND_FILES = $(patsubst %.cpp, $(BUILD_DIR)/%.d, $(SRCS))
DEPEND_FILES += $(patsubst %.cpp, $(BUILD_DIR)/%.d, $(TEST_SRCS))
DEPEND_FILES += $(patsubst %.cpp, $(BUILD_DIR)/%.d, $(SAMPLE_SRCS))

# ========= flags =========
CPPFLAGS = -I$(HEADER_DIR) -I$(SRC_DIR) -Wall -ggdb -std=c++11
LDFLAGS = -lpthread -lm
ARFLAGS =

CC = gcc
CXX = g++
AR = ar
RM = rm
CP = cp

# ========== rules =========
$(BUILD_DIR)/%.o : %.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CPPFLAGS) $<

$(BUILD_DIR)/%.o : %.cc
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $(CPPFLAGS) $<

$(BUILD_DIR)/%.o : %.cpp
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $(CPPFLAGS) $<

$(BUILD_DIR)/%.d : %.c
	@set -e; mkdir -p $(@D); $(RM) -f $@; \
	$(CC) -MM $(CPPFLAGS) $< |	sed '1s,^,$@ $(@D)/,' > $@

$(BUILD_DIR)/%.d : %.cc
	@set -e; mkdir -p $(@D); $(RM) -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< |	sed '1s,^,$@ $(@D)/,' > $@

$(BUILD_DIR)/%.d : %.cpp
	@set -e; mkdir -p $(@D); $(RM) -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< |	sed '1s,^,$@ $(@D)/,' > $@


# ========= targets =========
all :
	@echo "need to add dependents for all"

test : $(BUILD_DIR)/test.out
	@$(BUILD_DIR)/test.out

$(BUILD_DIR)/libtarget.a : $(OBJS)
	$(AR) crvs $(ARFLAGS) $@ $^

$(BUILD_DIR)/test.out : $(TEST_OBJS) $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) -lgtest -lgtest_main






clean :
	$(RM) -r $(BUILD_DIR)

-include $(DEPEND_FILES)

init-project:init-lib-project
init-app-project:
	@mkdir -p src tests docs scripts
init-lib-project:
	@mkdir -p src tests include samples docs scripts
