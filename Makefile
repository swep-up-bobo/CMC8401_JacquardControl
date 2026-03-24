# ─── 跨平台 Makefile (macOS / Windows) ─────────────────
# 用法:
#   make          — 配置 + 编译
#   make run      — 编译并运行
#   make clean    — 清除 build 目录
#   make rebuild  — 清除后重新编译

APP_NAME  := CMC8401_JacquardControl
BUILD_DIR := build

# ─── 平台检测 ──────────────────────────────────────────
ifeq ($(OS),Windows_NT)
    PLATFORM  := windows
    # Windows 下使用 NMake 或 Ninja；优先 Ninja
    CMAKE_GEN := -G "MinGW Makefiles"
    EXE       := $(BUILD_DIR)/$(APP_NAME).exe
    RM_CMD    := if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
    MKDIR_CMD := if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RUN_CMD   := $(EXE)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        PLATFORM := macos
    else
        PLATFORM := linux
    endif
    CMAKE_GEN :=
    EXE       := $(BUILD_DIR)/$(APP_NAME)
    RM_CMD    := rm -rf $(BUILD_DIR)
    MKDIR_CMD := mkdir -p $(BUILD_DIR)
    RUN_CMD   := ./$(EXE)
endif

# ─── 默认目标: 配置 + 编译 ─────────────────────────────
.PHONY: all configure build run clean rebuild info

all: build

# CMake 配置（仅首次或 CMakeLists.txt 变更时需要）
configure:
	@echo ">>> [$(PLATFORM)] CMake configure ..."
	@$(MKDIR_CMD)
	cmake -S . -B $(BUILD_DIR) $(CMAKE_GEN)

# 编译（自动触发配置）
build: configure
	@echo ">>> [$(PLATFORM)] Building ..."
	cmake --build $(BUILD_DIR) --parallel

# 编译 + 运行
run: build
	@echo ">>> [$(PLATFORM)] Launching $(APP_NAME) ..."
	$(RUN_CMD)

# 清除
clean:
	@echo ">>> Cleaning build directory ..."
	$(RM_CMD)

# 重新编译
rebuild: clean all

# 打印平台信息
info:
	@echo "Platform : $(PLATFORM)"
	@echo "Generator: $(CMAKE_GEN)"
	@echo "Executable: $(EXE)"
