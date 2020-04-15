# MyMachine
<p align="center">
<img src="./img/dinoGame.gif" height="300">
<img src="./img/textEditor.gif" height="300">
</p>

TODO

# Installation
```
sudo apt-get install ncurses-dev
git clone https://github.com/Brenocq/MyMachine.git
cd MyMachine/assembler
make
cd ../simulator
make
```

# Files
<p align="center">
<img src="./img/basmEx.png" height="400">
 ----->
<img src="./img/bbinEx.png" height="400">
</p>
TODO

# Assembler
<p align="center">
<img src="./img/assembler.png" height="400">
</p>
TODO

# Simulator
<p align="center">
<img src="./img/simulator.png" height="400">
</p>
TODO

# Examples

### Text editor
```
cd MyMachine
./assembler/bin/assembler examples/textEditor/textEditor.basm
./simulator/bin/simulator examples/textEditor/textEditor.bbin
```
TODO
### Dinosaur
```
cd MyMachine
./assembler/bin/assembler examples/dinosaur/dinosaur.basm
./simulator/bin/simulator examples/dinosaur/dinosaur.bbin
```
TODO

# The Machine
TODO
### Architecture
TODO
### Registers

| Name |  Description  |
| ---  | ------------------- |
|  pc  |  Program counter |
|  ra  |  Return register |
| rand |  Random register |
| time |  Time register |
|input |  Input register |
| zero |  Ground register |
|  ra  |  Return register |
|  t0  |  Temporary register |
|  t1  |  Temporary register |
|  t2  |  Temporary register |
|  t3  |  Temporary register |
|  t4  |  Temporary register |
|  t5  |  Temporary register |
|  t6  |  Temporary register |
|  t7  |  Temporary register |
|  a0  |  Argument register |
|  a1  |  Argument register |
|  a2  |  Argument register |
|  a3  |  Argument register |
|  v0  |  Function result |
|  v1  |  Function result |
|  v2  |  Function result |
|  v3  |  Function result |
|  s0  |  Saved temporary |
|  s1  |  Saved temporary |
|  s2  |  Saved temporary |
|  s3  |  Saved temporary |
|  s4  |  Saved temporary |
|  s5  |  Saved temporary |
|  s6  |  Saved temporary |
|  s7  |  Saved temporary |

### Commands
TODO

# License
TODO
