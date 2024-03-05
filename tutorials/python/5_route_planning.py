#=============================================================================
#     Copyright (C) 2021-2024 Wageningen University - All Rights Reserved
#                      Author: Gonzalo Mier
#                         BSD-3 License
#=============================================================================


import math
import fields2cover as f2c

rand = f2c.Random(42);
robot = f2c.Robot(2.0, 6.0);
field = rand.generateRandField(1e4, 5);
cells = field.getField();
const_hl = f2c.HG_Const_gen();
no_hl = const_hl.generateHeadlands(cells, 3.0 * robot.getWidth());
bf = f2c.SG_BruteForce();
swaths = bf.generateSwaths(math.pi, robot.getCovWidth(), no_hl.getGeometry(0));

print("####### Tutorial 5.1 Boustrophedon ######");
boustrophedon_sorter = f2c.RP_Boustrophedon();
swaths = boustrophedon_sorter.genSortedSwaths(swaths);

f2c.Visualizer.figure();
f2c.Visualizer.plot(cells);
f2c.Visualizer.plot(no_hl);
f2c.Visualizer.plot(swaths);
f2c.Visualizer.save("Tutorial_5_1_Boustrophedon_1.png");


for i in range(1, 4):
  f2c.Visualizer.figure();
  f2c.Visualizer.plot(cells);
  f2c.Visualizer.plot(no_hl);
  f2c.Visualizer.plot(boustrophedon_sorter.genSortedSwaths(swaths, i));
  f2c.Visualizer.save("Tutorial_5_1_Boustrophedon_" + str(i+1) + ".png");



print("####### Tutorial 5.2 Snake order ######");
snake_sorter = f2c.RP_Snake();
swaths = snake_sorter.genSortedSwaths(swaths);

f2c.Visualizer.figure();
f2c.Visualizer.plot(cells);
f2c.Visualizer.plot(no_hl);
f2c.Visualizer.plot(swaths);
f2c.Visualizer.save("Tutorial_5_2_Snake_1.png");

for i in range(1, 4):
  f2c.Visualizer.figure();
  f2c.Visualizer.plot(cells);
  f2c.Visualizer.plot(no_hl);
  f2c.Visualizer.plot(snake_sorter.genSortedSwaths(swaths, i));
  f2c.Visualizer.save("Tutorial_5_2_Snake_" + str(i+1) + ".png");

swaths = bf.generateSwaths(math.pi, robot.getCovWidth(), no_hl.getGeometry(0));
print("####### Tutorial 5.3 Spiral order ######");
spiral_sorter = f2c.RP_Spiral(6);
swaths = spiral_sorter.genSortedSwaths(swaths);

f2c.Visualizer.figure();
f2c.Visualizer.plot(cells);
f2c.Visualizer.plot(no_hl);
f2c.Visualizer.plot(swaths);
f2c.Visualizer.save("Tutorial_5_3_Spiral_1.png");

for i in range(1, 4):
  f2c.Visualizer.figure();
  f2c.Visualizer.plot(cells);
  f2c.Visualizer.plot(no_hl);
  f2c.Visualizer.plot(spiral_sorter.genSortedSwaths(swaths, i));
  f2c.Visualizer.save("Tutorial_5_3_Spiral_" + str(i+1) + ".png");


