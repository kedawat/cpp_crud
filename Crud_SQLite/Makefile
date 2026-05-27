cxx = g++
CFLAGS = -I C:/msys64/ucrt64/include
LDFLAGS = -L C:/msys64/ucrt64/lib -lsqlite3

main: main.cpp UserManager.cpp
	$(cxx) $(CFLAGS) -o main main.cpp UserManager.cpp $(LDFLAGS)

clean:
	del /f main.exe 2>nul || true