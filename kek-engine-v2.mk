##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=kek-engine-v2
ConfigurationName      :=Debug
WorkspacePath          :=/home/kek-Engine_v2
ProjectPath            :=/home/kek-Engine_v2
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=04/03/17
CodeLitePath           :=/root/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=./Bin/$(ProjectName)_D
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="kek-engine-v2.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -rdynamic -L ../bullet/src/BulletSoftBody -L ../bullet/src/BulletDynamics -L ../bullet/src/BulletCollision -L ../bullet/src/LinearMath -L ../SDL2_image/.libs -Wl,-Bstatic -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lSDL2_image -Wl,-Bdynamic -lSDL2 -lGL -lm -lstdc++
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)./SDL2/include $(IncludeSwitch)./glm/glm $(IncludeSwitch)./glm/glm/gtc $(IncludeSwitch)./glm/glm/gtx $(IncludeSwitch)./SDL2_image $(IncludeSwitch)./bullet/src 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -std=c++14 -std=c++11 -std=c99 $(Preprocessors)
CFLAGS   :=  -g -O0 -std=c++14 -std=c++11 -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Animation.cpp$(ObjectSuffix) $(IntermediateDirectory)/Collision_coarse.cpp$(ObjectSuffix) $(IntermediateDirectory)/Collision_fine.cpp$(ObjectSuffix) $(IntermediateDirectory)/Component.cpp$(ObjectSuffix) $(IntermediateDirectory)/Contact.cpp$(ObjectSuffix) $(IntermediateDirectory)/Event.cpp$(ObjectSuffix) $(IntermediateDirectory)/EventHandler.cpp$(ObjectSuffix) $(IntermediateDirectory)/EventSubscriber.cpp$(ObjectSuffix) $(IntermediateDirectory)/ForceGenerator.cpp$(ObjectSuffix) $(IntermediateDirectory)/GameObject.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/glew.c$(ObjectSuffix) $(IntermediateDirectory)/InputManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/Light.cpp$(ObjectSuffix) $(IntermediateDirectory)/Links.cpp$(ObjectSuffix) $(IntermediateDirectory)/Main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Mesh.cpp$(ObjectSuffix) $(IntermediateDirectory)/Obj2.cpp$(ObjectSuffix) $(IntermediateDirectory)/ParticleSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/Physics.cpp$(ObjectSuffix) $(IntermediateDirectory)/Scene.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/ShaderManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/TorqueGenerator.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Animation.cpp$(ObjectSuffix): Animation.cpp $(IntermediateDirectory)/Animation.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Animation.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Animation.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Animation.cpp$(DependSuffix): Animation.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Animation.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Animation.cpp$(DependSuffix) -MM Animation.cpp

$(IntermediateDirectory)/Animation.cpp$(PreprocessSuffix): Animation.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Animation.cpp$(PreprocessSuffix) Animation.cpp

$(IntermediateDirectory)/Collision_coarse.cpp$(ObjectSuffix): Collision_coarse.cpp $(IntermediateDirectory)/Collision_coarse.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Collision_coarse.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Collision_coarse.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Collision_coarse.cpp$(DependSuffix): Collision_coarse.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Collision_coarse.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Collision_coarse.cpp$(DependSuffix) -MM Collision_coarse.cpp

$(IntermediateDirectory)/Collision_coarse.cpp$(PreprocessSuffix): Collision_coarse.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Collision_coarse.cpp$(PreprocessSuffix) Collision_coarse.cpp

$(IntermediateDirectory)/Collision_fine.cpp$(ObjectSuffix): Collision_fine.cpp $(IntermediateDirectory)/Collision_fine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Collision_fine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Collision_fine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Collision_fine.cpp$(DependSuffix): Collision_fine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Collision_fine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Collision_fine.cpp$(DependSuffix) -MM Collision_fine.cpp

$(IntermediateDirectory)/Collision_fine.cpp$(PreprocessSuffix): Collision_fine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Collision_fine.cpp$(PreprocessSuffix) Collision_fine.cpp

$(IntermediateDirectory)/Component.cpp$(ObjectSuffix): Component.cpp $(IntermediateDirectory)/Component.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Component.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Component.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Component.cpp$(DependSuffix): Component.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Component.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Component.cpp$(DependSuffix) -MM Component.cpp

$(IntermediateDirectory)/Component.cpp$(PreprocessSuffix): Component.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Component.cpp$(PreprocessSuffix) Component.cpp

$(IntermediateDirectory)/Contact.cpp$(ObjectSuffix): Contact.cpp $(IntermediateDirectory)/Contact.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Contact.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Contact.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Contact.cpp$(DependSuffix): Contact.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Contact.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Contact.cpp$(DependSuffix) -MM Contact.cpp

$(IntermediateDirectory)/Contact.cpp$(PreprocessSuffix): Contact.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Contact.cpp$(PreprocessSuffix) Contact.cpp

$(IntermediateDirectory)/Event.cpp$(ObjectSuffix): Event.cpp $(IntermediateDirectory)/Event.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Event.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Event.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Event.cpp$(DependSuffix): Event.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Event.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Event.cpp$(DependSuffix) -MM Event.cpp

$(IntermediateDirectory)/Event.cpp$(PreprocessSuffix): Event.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Event.cpp$(PreprocessSuffix) Event.cpp

$(IntermediateDirectory)/EventHandler.cpp$(ObjectSuffix): EventHandler.cpp $(IntermediateDirectory)/EventHandler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/EventHandler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/EventHandler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EventHandler.cpp$(DependSuffix): EventHandler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/EventHandler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/EventHandler.cpp$(DependSuffix) -MM EventHandler.cpp

$(IntermediateDirectory)/EventHandler.cpp$(PreprocessSuffix): EventHandler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/EventHandler.cpp$(PreprocessSuffix) EventHandler.cpp

$(IntermediateDirectory)/EventSubscriber.cpp$(ObjectSuffix): EventSubscriber.cpp $(IntermediateDirectory)/EventSubscriber.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/EventSubscriber.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/EventSubscriber.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/EventSubscriber.cpp$(DependSuffix): EventSubscriber.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/EventSubscriber.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/EventSubscriber.cpp$(DependSuffix) -MM EventSubscriber.cpp

$(IntermediateDirectory)/EventSubscriber.cpp$(PreprocessSuffix): EventSubscriber.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/EventSubscriber.cpp$(PreprocessSuffix) EventSubscriber.cpp

$(IntermediateDirectory)/ForceGenerator.cpp$(ObjectSuffix): ForceGenerator.cpp $(IntermediateDirectory)/ForceGenerator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/ForceGenerator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ForceGenerator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ForceGenerator.cpp$(DependSuffix): ForceGenerator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ForceGenerator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ForceGenerator.cpp$(DependSuffix) -MM ForceGenerator.cpp

$(IntermediateDirectory)/ForceGenerator.cpp$(PreprocessSuffix): ForceGenerator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ForceGenerator.cpp$(PreprocessSuffix) ForceGenerator.cpp

$(IntermediateDirectory)/GameObject.cpp$(ObjectSuffix): GameObject.cpp $(IntermediateDirectory)/GameObject.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/GameObject.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameObject.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameObject.cpp$(DependSuffix): GameObject.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameObject.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/GameObject.cpp$(DependSuffix) -MM GameObject.cpp

$(IntermediateDirectory)/GameObject.cpp$(PreprocessSuffix): GameObject.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameObject.cpp$(PreprocessSuffix) GameObject.cpp

$(IntermediateDirectory)/glew.c$(ObjectSuffix): glew.c $(IntermediateDirectory)/glew.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/kek-Engine_v2/glew.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/glew.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/glew.c$(DependSuffix): glew.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/glew.c$(ObjectSuffix) -MF$(IntermediateDirectory)/glew.c$(DependSuffix) -MM glew.c

$(IntermediateDirectory)/glew.c$(PreprocessSuffix): glew.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/glew.c$(PreprocessSuffix) glew.c

$(IntermediateDirectory)/InputManager.cpp$(ObjectSuffix): InputManager.cpp $(IntermediateDirectory)/InputManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/InputManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/InputManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/InputManager.cpp$(DependSuffix): InputManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/InputManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/InputManager.cpp$(DependSuffix) -MM InputManager.cpp

$(IntermediateDirectory)/InputManager.cpp$(PreprocessSuffix): InputManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/InputManager.cpp$(PreprocessSuffix) InputManager.cpp

$(IntermediateDirectory)/Light.cpp$(ObjectSuffix): Light.cpp $(IntermediateDirectory)/Light.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Light.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Light.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Light.cpp$(DependSuffix): Light.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Light.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Light.cpp$(DependSuffix) -MM Light.cpp

$(IntermediateDirectory)/Light.cpp$(PreprocessSuffix): Light.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Light.cpp$(PreprocessSuffix) Light.cpp

$(IntermediateDirectory)/Links.cpp$(ObjectSuffix): Links.cpp $(IntermediateDirectory)/Links.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Links.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Links.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Links.cpp$(DependSuffix): Links.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Links.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Links.cpp$(DependSuffix) -MM Links.cpp

$(IntermediateDirectory)/Links.cpp$(PreprocessSuffix): Links.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Links.cpp$(PreprocessSuffix) Links.cpp

$(IntermediateDirectory)/Main.cpp$(ObjectSuffix): Main.cpp $(IntermediateDirectory)/Main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Main.cpp$(DependSuffix): Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Main.cpp$(DependSuffix) -MM Main.cpp

$(IntermediateDirectory)/Main.cpp$(PreprocessSuffix): Main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Main.cpp$(PreprocessSuffix) Main.cpp

$(IntermediateDirectory)/Mesh.cpp$(ObjectSuffix): Mesh.cpp $(IntermediateDirectory)/Mesh.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Mesh.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Mesh.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Mesh.cpp$(DependSuffix): Mesh.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Mesh.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Mesh.cpp$(DependSuffix) -MM Mesh.cpp

$(IntermediateDirectory)/Mesh.cpp$(PreprocessSuffix): Mesh.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Mesh.cpp$(PreprocessSuffix) Mesh.cpp

$(IntermediateDirectory)/Obj2.cpp$(ObjectSuffix): Obj2.cpp $(IntermediateDirectory)/Obj2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Obj2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Obj2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Obj2.cpp$(DependSuffix): Obj2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Obj2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Obj2.cpp$(DependSuffix) -MM Obj2.cpp

$(IntermediateDirectory)/Obj2.cpp$(PreprocessSuffix): Obj2.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Obj2.cpp$(PreprocessSuffix) Obj2.cpp

$(IntermediateDirectory)/ParticleSystem.cpp$(ObjectSuffix): ParticleSystem.cpp $(IntermediateDirectory)/ParticleSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/ParticleSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ParticleSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ParticleSystem.cpp$(DependSuffix): ParticleSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ParticleSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ParticleSystem.cpp$(DependSuffix) -MM ParticleSystem.cpp

$(IntermediateDirectory)/ParticleSystem.cpp$(PreprocessSuffix): ParticleSystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ParticleSystem.cpp$(PreprocessSuffix) ParticleSystem.cpp

$(IntermediateDirectory)/Physics.cpp$(ObjectSuffix): Physics.cpp $(IntermediateDirectory)/Physics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Physics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Physics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Physics.cpp$(DependSuffix): Physics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Physics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Physics.cpp$(DependSuffix) -MM Physics.cpp

$(IntermediateDirectory)/Physics.cpp$(PreprocessSuffix): Physics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Physics.cpp$(PreprocessSuffix) Physics.cpp

$(IntermediateDirectory)/Scene.cpp$(ObjectSuffix): Scene.cpp $(IntermediateDirectory)/Scene.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/Scene.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Scene.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Scene.cpp$(DependSuffix): Scene.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Scene.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Scene.cpp$(DependSuffix) -MM Scene.cpp

$(IntermediateDirectory)/Scene.cpp$(PreprocessSuffix): Scene.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Scene.cpp$(PreprocessSuffix) Scene.cpp

$(IntermediateDirectory)/ShaderManager.cpp$(ObjectSuffix): ShaderManager.cpp $(IntermediateDirectory)/ShaderManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/ShaderManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ShaderManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ShaderManager.cpp$(DependSuffix): ShaderManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ShaderManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ShaderManager.cpp$(DependSuffix) -MM ShaderManager.cpp

$(IntermediateDirectory)/ShaderManager.cpp$(PreprocessSuffix): ShaderManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ShaderManager.cpp$(PreprocessSuffix) ShaderManager.cpp

$(IntermediateDirectory)/TorqueGenerator.cpp$(ObjectSuffix): TorqueGenerator.cpp $(IntermediateDirectory)/TorqueGenerator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kek-Engine_v2/TorqueGenerator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TorqueGenerator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TorqueGenerator.cpp$(DependSuffix): TorqueGenerator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TorqueGenerator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TorqueGenerator.cpp$(DependSuffix) -MM TorqueGenerator.cpp

$(IntermediateDirectory)/TorqueGenerator.cpp$(PreprocessSuffix): TorqueGenerator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TorqueGenerator.cpp$(PreprocessSuffix) TorqueGenerator.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


