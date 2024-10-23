# Devlogs
- 2024-10-23 The boid starts a simple avoidance protocol by steering to the right
Note that while turning to avoid, the other forces are still influencing the boid's trajectory. This must be constrained in some way
so the obstacle avoidance protocol can have more dominance over the boid's flight routine. The next step is to first evaluate a clear escape route and then steer the boid in that direction. Also, add the destination force so it can correct its path back to the target.
<img width="480" alt="image" src="/images/avoidance_to_rigth.gif"></br>
- 2024-10-15 Enabled the ray intersection at the head of the boid
<img width="480" alt="image" src="https://github.com/user-attachments/assets/be9ddd61-9139-45b6-bcb7-84c8cb9f3665"></br>
- 2024-10-11 Implemented Ray-AxisAlignPlane intersection for XYZ on a user-controlled ray. The ray leaves and enters the bounding volume while keeping the intersections
<img width="400" alt="image" src="https://github.com/user-attachments/assets/df9e1d7f-5021-4748-a7f1-6b0ae5ba68b7">
<img width="400" alt="image" src="https://github.com/user-attachments/assets/6c7df04e-a9f7-4cd7-aa70-b4b079645729">
<p> Here can be seen how the ray leaves and enters the volume, and the intersections persist </p>
<img width="400" alt="image" src="https://github.com/user-attachments/assets/963b99a4-e775-4128-b00f-f8a33ffb47a5">
<img width="400" alt="image" src="https://github.com/user-attachments/assets/20f541cd-1a97-49e1-aa68-4ff947e63779">

- 2024-10-01 Implemented boids algorithm in naïve form in $O(n^2)$ with obstacle avoidance as a steering force
![boids_obstacles_floor_GIF](https://github.com/user-attachments/assets/ba46988c-e8d3-4a20-8dcd-78e4a7d64d3f)
- 2024-09-30 Implemented a Ray-AxisAlignPlane Intersection Test, and fill intersected voxels with red
![intersection_test_xyz_axis_GIF](https://github.com/user-attachments/assets/3c6cbbee-2706-4c11-a69f-5b1927b4bdb6)
- 2024-09-24 Organize scene for better visualization. Added visual feedback when detecting collisions with random allocated obstacles
![grid_obstacles_collisions_color_feedback_GIF](https://github.com/user-attachments/assets/ae475cd1-a9c2-4972-b114-fe9c2d6424f1)
- 2024-09-14 Implemented algorithm to determine the presence of a point in a voxel domain in $O(1)$
![GIF_particles_updating_voxels](https://github.com/user-attachments/assets/3a2bf8c8-9ad3-441f-be52-a968e9f43556)

- Built the sparse voxel volume and set a boid to query the space.
- <img width="800" alt="image" src="https://github.com/user-attachments/assets/72566f1e-3199-469a-a185-27807ba22981">
