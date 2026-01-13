# Emscripten build file

# Artifacts directory
BUILD_DIR=./build

# Compilers
CC=emcc
CPP=em++

# Default compiler flags
CFLAGS=-g0 -O3 -c

# PhysFS

# Compiler flags
CFLAGS_PHYSFS=\
	-I./physfs/src \
	-s USE_SDL=2 \
	-s EMULATE_FUNCTION_POINTER_CASTS=1 \
	-DPHYSFS_SUPPORTS_DEFAULT=0 \
	-DPHYSFS_SUPPORTS_ZIP=1

# Sources
SOURCES_PHYSFS=\
	physfs/src/physfs.c \
	physfs/src/physfs_archiver_7z.c \
	physfs/src/physfs_archiver_dir.c \
	physfs/src/physfs_archiver_grp.c \
	physfs/src/physfs_archiver_hog.c \
	physfs/src/physfs_archiver_iso9660.c \
	physfs/src/physfs_archiver_mvl.c \
	physfs/src/physfs_archiver_qpak.c \
	physfs/src/physfs_archiver_slb.c \
	physfs/src/physfs_archiver_unpacked.c \
	physfs/src/physfs_archiver_vdf.c \
	physfs/src/physfs_archiver_wad.c \
	physfs/src/physfs_archiver_zip.c \
	physfs/src/physfs_byteorder.c \
	physfs/src/physfs_platform_posix.c \
	physfs/src/physfs_platform_unix.c \
	physfs/src/physfs_platform_windows.c \
	physfs/src/physfs_unicode.c \
	physfs/src/physfsrwops.c

# Objects
OBJECTS_PHYSFS=$(SOURCES_PHYSFS:%=$(BUILD_DIR)/%.o)

# TinyXML2

# Compiler flags
CFLAGS_TINYXML2=\
	-I./tinyxml2

# Sources
SOURCES_TINYXML2=\
	tinyxml2/tinyxml2.cpp

# Objects
OBJECTS_TINYXML2=$(SOURCES_TINYXML2:%=$(BUILD_DIR)/%.o)

# C-Hashmap

# Compiler flags
CFLAGS_HASHMAP=\
	-I.

# Sources
SOURCES_HASHMAP=\
	c-hashmap/c-hashmap/map.c

# Objects
OBJECTS_HASHMAP=$(SOURCES_HASHMAP:%=$(BUILD_DIR)/%.o)

# LodePNG

# Compiler flags
CFLAGS_LODEPNG=\
	-I./lodepng

# Sources
SOURCES_LODEPNG=\
	lodepng/lodepng.cpp

# Objects
OBJECTS_LODEPNG=$(SOURCES_LODEPNG:%=$(BUILD_DIR)/%.o)

# SheenBidi

# Compiler flags
CFLAGS_SHEENBIDI=\
	-I./SheenBidi/Headers

# Sources
SOURCES_SHEENBIDI=\
	SheenBidi/Source/BidiChain.c \
	SheenBidi/Source/BidiTypeLookup.c \
	SheenBidi/Source/BracketQueue.c \
	SheenBidi/Source/GeneralCategoryLookup.c \
	SheenBidi/Source/IsolatingRun.c \
	SheenBidi/Source/LevelRun.c \
	SheenBidi/Source/Object.c \
	SheenBidi/Source/PairingLookup.c \
	SheenBidi/Source/RunQueue.c \
	SheenBidi/Source/SBAlgorithm.c \
	SheenBidi/Source/SBBase.c \
	SheenBidi/Source/SBCodepoint.c \
	SheenBidi/Source/SBCodepointSequence.c \
	SheenBidi/Source/SBLine.c \
	SheenBidi/Source/SBLog.c \
	SheenBidi/Source/SBMirrorLocator.c \
	SheenBidi/Source/SBParagraph.c \
	SheenBidi/Source/SBScriptLocator.c \
	SheenBidi/Source/ScriptLookup.c \
	SheenBidi/Source/ScriptStack.c \
	SheenBidi/Source/SheenBidi.c \
	SheenBidi/Source/StatusStack.c

# Objects
OBJECTS_SHEENBIDI=$(SOURCES_SHEENBIDI:%=$(BUILD_DIR)/%.o)

# FAudio

# Compiler flags
CFLAGS_FAUDIO=\
	-I./FAudio/include \
	-I./FAudio/src \
	-s USE_SDL=2

# Sources
SOURCES_FAUDIO=\
	FAudio/src/F3DAudio.c \
	FAudio/src/FACT.c \
	FAudio/src/FACT_internal.c \
	FAudio/src/FAPOBase.c \
	FAudio/src/FAPOFX.c \
	FAudio/src/FAPOFX_echo.c \
	FAudio/src/FAPOFX_eq.c \
	FAudio/src/FAPOFX_masteringlimiter.c \
	FAudio/src/FAPOFX_reverb.c \
	FAudio/src/FAudio.c \
	FAudio/src/FAudio_internal.c \
	FAudio/src/FAudio_internal_simd.c \
	FAudio/src/FAudio_operationset.c \
	FAudio/src/FAudio_platform_sdl2.c \
	FAudio/src/FAudioFX_reverb.c \
	FAudio/src/FAudioFX_volumemeter.c
# 	FAudio/src/XNA_Song.c

# Objects
OBJECTS_FAUDIO=$(SOURCES_FAUDIO:%=$(BUILD_DIR)/%.o)

# VVVVVV

# Compiler flags
CFLAGS_VVVVVV=\
	-I./physfs/src \
	-I./lodepng \
	-I./tinyxml2 \
	-I./c-hashmap \
	-I./SheenBidi/Headers \
	-I./FAudio/include \
	-I./FAudio/src \
	-I./src \
	-s USE_SDL=2 \
	-s USE_SDL_MIXER=2 \
	-s EMULATE_FUNCTION_POINTER_CASTS=1 \
	-s FETCH=1 \
	-DPHYSFS_SUPPORTS_DEFAULT=0 \
	-DPHYSFS_SUPPORTS_ZIP=1
#	-DMAKEANDPLAY

# Linker flags
LDFLAGS_VVVVVV=\
	-s TOTAL_MEMORY=512MB \
	--preload-file ./data@/ \
	--use-preload-cache \
	-s USE_SDL=2 \
	-s USE_SDL_MIXER=2 \
	-s EMULATE_FUNCTION_POINTER_CASTS=1 \
	-s TOTAL_STACK=128MB \
	-s USE_OGG=1 \
	-s USE_VORBIS=1 \
	-s FETCH=1

# Sources
SOURCES_VVVVVV=\
	src/BinaryBlob.cpp \
	src/BlockV.cpp \
	src/ButtonGlyphs.cpp \
	src/CustomLevels.cpp \
	src/CWrappers.cpp \
	src/DeferCallbacks.c \
	src/Editor.cpp \
	src/Ent.cpp \
	src/Entity.cpp \
	src/FileSystemUtils.cpp \
	src/Finalclass.cpp \
	src/Font.cpp \
	src/FontBidi.cpp \
	src/Game.cpp \
	src/GlitchrunnerMode.c \
	src/GOGNetwork.c \
	src/Graphics.cpp \
	src/GraphicsResources.cpp \
	src/GraphicsUtil.cpp \
	src/IMERender.cpp \
	src/Input.cpp \
	src/InterimVersion.out.c \
	src/KeyPoll.cpp \
	src/Labclass.cpp \
	src/LevelDebugger.cpp \
	src/Localization.cpp \
	src/LocalizationMaint.cpp \
	src/LocalizationStorage.cpp \
	src/lodepng_wrapper.c \
	src/Logic.cpp \
	src/Map.cpp \
	src/Music.cpp \
	src/Network.c \
	src/Otherlevel.cpp \
	src/preloader.cpp \
	src/Render.cpp \
	src/RenderFixed.cpp \
	src/RoomnameTranslator.cpp \
	src/Screen.cpp \
	src/Script.cpp \
	src/Scripts.cpp \
	src/Spacestation2.cpp \
	src/TerminalScripts.cpp \
	src/Textbook.c \
	src/Textbox.cpp \
	src/ThirdPartyDeps.c \
	src/Tower.cpp \
	src/UtilityClass.cpp \
	src/UTF8.c \
	src/VFormat.c \
	src/Vlogging.c \
	src/WarpClass.cpp \
	src/XMLUtils.cpp \
	src/Xoshiro.c \
	src/main.cpp

# Objects
OBJECTS_VVVVVV=$(SOURCES_VVVVVV:%=$(BUILD_DIR)/%.o)

# All objects
# ALL_OBJECTS=$(OBJECTS_VVVVVV) $(OBJECTS_PHYSFS) $(OBJECTS_TINYXML2) $(OBJECTS_HASHMAP) $(OBJECTS_LODEPNG) $(OBJECTS_SHEENBIDI) $(OBJECTS_FAUDIO)
ALL_OBJECTS=$(OBJECTS_VVVVVV) $(OBJECTS_PHYSFS) $(OBJECTS_TINYXML2) $(OBJECTS_HASHMAP) $(OBJECTS_SHEENBIDI) $(OBJECTS_FAUDIO)

index.html: $(ALL_OBJECTS)
	$(CPP) $(LDFLAGS_VVVVVV) $(ALL_OBJECTS) -o $(BUILD_DIR)/index.html --shell-file ./shell.html

$(BUILD_DIR)/physfs/src/%.c.o: physfs/src/%.c
	@mkdir -p $(BUILD_DIR)/physfs/src
	$(CC) $(CFLAGS) $(CFLAGS_PHYSFS) $< -o $@

$(BUILD_DIR)/tinyxml2/%.cpp.o: tinyxml2/%.cpp
	@mkdir -p $(BUILD_DIR)/tinyxml2
	$(CPP) $(CFLAGS) $(CFLAGS_TINYXML2) $< -o $@

$(BUILD_DIR)/c-hashmap/c-hashmap/%.c.o: c-hashmap/c-hashmap/%.c
	@mkdir -p $(BUILD_DIR)/c-hashmap/c-hashmap
	$(CC) $(CFLAGS) $(CFLAGS_HASHMAP) $< -o $@

$(BUILD_DIR)/lodepng/%.cpp.o: lodepng/%.cpp
	@mkdir -p $(BUILD_DIR)/lodepng
	$(CPP) $(CFLAGS) $(CFLAGS_LODEPNG) $< -o $@

$(BUILD_DIR)/SheenBidi/Source/%.c.o: SheenBidi/Source/%.c
	@mkdir -p $(BUILD_DIR)/SheenBidi/Source
	$(CC) $(CFLAGS) $(CFLAGS_SHEENBIDI) $< -o $@

$(BUILD_DIR)/FAudio/src/%.c.o: FAudio/src/%.c
	@mkdir -p $(BUILD_DIR)/FAudio/src
	$(CC) $(CFLAGS) $(CFLAGS_FAUDIO) $< -o $@

$(BUILD_DIR)/src/%.cpp.o: src/%.cpp
	@mkdir -p $(BUILD_DIR)/src
	$(CPP) $(CFLAGS) $(CFLAGS_VVVVVV) $< -o $@

$(BUILD_DIR)/src/%.c.o: src/%.c
	@mkdir -p $(BUILD_DIR)/src
	$(CC) $(CFLAGS) $(CFLAGS_VVVVVV) $< -o $@

clean:
	rm -rf $(BUILD_DIR)