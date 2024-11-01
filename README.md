# Obstacle Detection and Avoidance in Boids using Ray-Voxel Intersection
<div style="display: flex; justify-content: space-around;">
    <img src="images/many random without.gif" alt="Without Avoidance" width="45%">
    <img src="images/many random with.gif" alt="With Avoidance" width="45%">
</div>

> Without (left) and with (right) obstacle avoidance using a rotation operator

### Project Overview
Prototype an obstacle Detection and Avoidance algorithm using ray-voxel intersection for boids in the OpenGL-based 
library OpenFrameworks in C++, to imform the future implementation of a more robust solution in Unity using compute shaders.

# Build instructions for XCode on Mac
1. To run this project, first [Download OpenFrameworks source code](https://openframeworks.cc/download/). 
2. Then, move inside the `myApps` folder inside the OpenFrameworks folder. You need this to have access to the OpenFrameworks header files. 
```bash
cd openframeworks_version_####/apps/myApps/
```
3. Only inside you can now clone the repo:
```bash
git clone https://github.com/DavidGiraldoCode/t-spatial_partitioning.git
```
4. Open the XCode project

### Learning Objectives
- Develop efficient spatial data structures for collision avoidance.
- Implement ray-voxel intersection test for obstacle detection

### Key Sections
- [Session Notes](session_notes.md): Detailed breakdowns of what is implemented, code explanations, and self-quizzes to reinforce understanding.
- [Technical Challenges](technical_challenges.md): List of problems encountered and solutions; documented repeated issues, solutions, knowledge gaps, and relevant resources.
- [Review and Reflection](review.md): Summaries, progress reflections, future work, and lingering questions.
- [DevLogs and GIFs](DEVLOGS.md): GIF of the progress (soon to be migrated to session Notes).

<img width="400" alt="image" src="https://github.com/user-attachments/assets/be9ddd61-9139-45b6-bcb7-84c8cb9f3665">
<img width="400" alt="image" src="https://github.com/user-attachments/assets/963b99a4-e775-4128-b00f-f8a33ffb47a5">

