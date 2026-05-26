# Plan: Install g++ via MinGW-w64 (winget) on Windows

Install MinGW-w64 directly via winget, add to PATH, and set up VS Code for C++ development.

## Steps

### Phase 1: Install MinGW-w64
1. Run in PowerShell (as admin):
   ```
   winget install -e --id MingW-w64.MingW-w64
   ```

### Phase 2: Add to Windows PATH
2. Add the MinGW-w64 `bin` folder to your system PATH (typically `C:\mingw64\bin`)
   - Search "Environment Variables" in Windows → Edit system PATH → Add: `C:\mingw64\bin`
3. **Restart VS Code** (or open a new terminal)
4. Verify: `g++ --version`

### Phase 3: VS Code Extensions
5. Install the following VS Code extensions:
   - **C/C++** (`ms-vscode.cpptools`) — IntelliSense, debugging, code browsing
   - **C/C++ Extension Pack** (`ms-vscode.cpptools-extension-pack`) — includes CMake Tools and other helpers
   - **Code Runner** (`formulahendry.code-runner`) — quick run with a single click/shortcut

### Phase 4: Compile and Run
6. Compile and run in the Crud folder:
   - `g++ -o main.exe main.cpp`
   - `.\main.exe`

## Verification
1. `g++ --version` → shows GCC version info
2. `g++ -o main.exe main.cpp` → produces `main.exe`
3. `.\main.exe` → prints "Hello, World!"
