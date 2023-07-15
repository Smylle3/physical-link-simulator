# Variáveis
CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC_DIR = src
HEADER_DIR = headers
OBJ_DIR = obj
EXECUTABLE = $(OBJ_DIR)/simulador.exe

# Obter lista de arquivos .cpp na pasta SRC_DIR
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Obter lista de arquivos .o baseados na lista de arquivos .cpp, excluindo o executável
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Targets
.PHONY: compile exec run clean

compile: $(EXECUTABLE)

exec: compile
	$(EXECUTABLE)

run: compile exec

# Compilar arquivo Simulador.cpp em arquivo objeto Simulador.o
$(OBJ_DIR)/Simulador.o: $(SRC_DIR)/Simulador.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(HEADER_DIR)

# Compilar arquivo CamadaEnlace.cpp em arquivo objeto CamadaEnlace.o
$(OBJ_DIR)/CamadaEnlace.o: $(SRC_DIR)/CamadaEnlace.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(HEADER_DIR)

# Compilar arquivo CamadaFisica.cpp em arquivo objeto CamadaFisica.o
$(OBJ_DIR)/CamadaFisica.o: $(SRC_DIR)/CamadaFisica.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I $(HEADER_DIR)

# Link dos arquivos objeto para gerar o executável
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	del $(OBJ_DIR)\simulador.exe
	del $(OBJ_DIR)\CamadaEnlace.o
	del $(OBJ_DIR)\CamadaFisica.o
	del $(OBJ_DIR)\Simulador.o
	@echo Arquivos limpos!