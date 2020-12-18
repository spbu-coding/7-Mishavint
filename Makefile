.PHONY: all clean check test
include CONFIG.cfg
BLD_OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/main_work.o
CC = gcc
LD = gcc
TARGET = $(BUILD_DIR)/$(NAME)
INP = $(wildcard $(TEST_DIR)/*.in)
LOG = $(INP:$(TEST_DIR)/%.in=$(BUILD_DIR)/%.log)
ERR = $(BUILD_DIR)/error_with_checks

all: $(TARGET) 

$(BLD_OBJS): $(BUILD_DIR)/%.o:	$(SOURCE_DIR)/%.c  | $(BUILD_DIR)
	$(CC) -c $< -o $@ 

$(TARGET): $(BLD_OBJS)| $(BUILD_DIR)
	$(LD) $^ -o $@

$(BUILD_DIR):	
	@mkdir -p $@

clean:	
	$(RM) $(BUILD_DIR)/$(NAME) $(BLD_OBJS) $(LOG) $(ERR)

check:	$(LOG) 
	@if [ -e $(ERR) ] ; then \
	printf "\n\nResults of checks are:\n" ; \
	cat $(ERR); \
		exit 1; \
	fi
	
$(LOG): $(BUILD_DIR)/%.log:	$(TEST_DIR)/%.in $(TARGET)
	@$(BUILD_DIR)/sorter $< >$@
	@if cmp -s $(TEST_DIR)/$*.out $@; then \
		echo Test $* has finished succesfully; \
	else \
		echo Test $* has failed; \
		printf "Test $* has failed\n" >> $(ERR); \
	fi
