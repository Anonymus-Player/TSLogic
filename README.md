# The-Spell-Logic (TSLogic)

This is the framework used in The Spell engine that I'm working on

# Features:

  - Very detailed in code documentation
  - Animantion Support
  - A very crude Player (for now it can only move)
  - Enemies support with 2 type of them:
    - A basic enemy which it just moves randomly
    - An intelligent enemy which it can fallow you and it can avoid obstcales
    - Because of how enemy is designed you can exrend it by inhereting from the base class
  - JSON support of map scrippting, there is documentation of how it need to written
  - A texture resource manager
  - A collision reaction engine (which it works well, but it needs improvement)
  - Tile map support for making huge maps
  - Barriers support
  - Levels support
  - Layers support
  
# Preview:

  If you want to see how it runs there is an example folder with a CMake file where you can see how it runs
  
# Videos: 
  https://www.youtube.com/watch?v=NQQcAoYNp0Y
  https://www.youtube.com/watch?v=Mn78pblibPY

# Build instructions:
  
  ```sh
  git clone https://github.com/Anonymus-Player/TSLogic.git
  cd TSLogic
  cd Examples
  mkdir build
  cd build
  cmake ..
  make -j
  ./TSLogicTest
  ```
