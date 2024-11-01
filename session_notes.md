# Session notes (Oldest first )
---
## 💻 Session 2024-10-29: An Obstacle Avoidance Equation

### Objective: Study and understand an equation for obstacle avoidance.

I found a simple and "stable" equation for dodging behavior proposed by Ma and Chou (2024). Their paper addresses stability issues in multi-agent simulations (MAS) and proposes an equation to solve the minima problem. They created a *Rotation Operator* vector that pulls the agent away from the obstacle center based on the angle between the agent's velocity vector and the agent-to-obstacle vector.

Using this approach, the objective is to enable an agent to dodge an obstacle directly in front.

> ### What's the Minima Problem?
> When an agent in a simulation cannot resolve conflicting forces (e.g., collision avoidance, target following, obstacle avoidance) in a direction that would allow it to exit from a concave shape, it may get trapped or stop. This often happens in navigation simulations when the agents lack prior environmental knowledge, meaning a pathfinding algorithm is not feasible.


### Breaking Down the Rotation Operator

#### Variables:
- **Obstacle Center**: Position of the obstacle.
- **Agent Position**: Current position of the agent.
- **Agent Velocity**: Agent's directional movement vector.
- **Critical Radius**: Distance threshold to initiate avoidance behavior.

#### Steps:
1. **Distance Check**: Validate if the agent-to-obstacle distance is equal to or less than the Critical radius.
2. **Angle Comparison**:

Compare the angle between the agent's velocity (a) and agent-to-obstacle (ao) to determine if the obstacle is to the left and to the right. And here, I simplified the proposed method. The original compares the absolute rotation, and if it is greater than PI, computes the two different equations with arctan2 to determine whether the agent should turn to the left (obstacle to the right ) or to the right (obstacle to the left).

![alt text](images/origital_angle_check.png)

My simplification (considering a 2D avoidance) is as follows:

   - Normalize both vectors: $$\left(A\right)$$ (agent's velocity) and $$\left(O-A\right)$$ (agent-to-obstacle).
   - Ignore the Z component (UP) since this is a 2D rotation.
   - Compute a simplified cross-product to obtain the sign, indicating left or right orientation.
$$C_{ross}=\left(D_{irectionX}\ \cdot a_{toObstacleY}\ \right)-\left(D_{irectionY}\cdot a_{toObstacleX}\right)$$
3. With the orientation, create the rotation vector that is orthogonal to the object-to-agent (oa) vector by reflecting the component of "oa."

$$V_{rotationLeft}\ =\ \left(\left(x_{iy}\ -\ x_{ly}\right),\ -\left(x_{ix}\ -\ x_{lx}\right)\right)$$
$$V_{rotationRigth}\ =\ \left(-\left(x_{iy}\ -\ x_{ly}\right),\ \left(x_{ix}\ -\ x_{lx}\right)\right)$$
$$V_{rotation} = \begin{cases} 
      V_{rotationLeft} & \text{if } C_{ross} < 0 \\
      V_{rotationRigth} & \text{if } C_{ross} \geq 0 
   \end{cases}$$

4. Now that we have the direction to turn, we compute three things:
- Radial attenuation: This is an inverse relationship between the agent's position and the resulting value. It helps dampen the force of the rotation if the agent moves away from the obstacle.
- 
$$k_{radialAttenuation}=\left(\left(\frac{1}{r_{o}}\right)-\left(\frac{1}{r_{critical}}\right)\right)$$

- Rotation Velocity and Proximity Damping: This increases the force of the velocity the closer the agent gets and gives a smooth transition.

$$\frac{1}{\left(r_{o}^{2}\cdot V_{rotMagnitud}\right)}$$

- Amplitude coefficient This is a user-defined value that increases the force of the rotation operator.

$$K_{amplitud}=8$$

4. Lastly, Ma and Chou's Rotation Operator equation looks like this:

$$R_{operator}=K_{amplitud}\cdot\frac{1}{\left(r_{o}^{2}\cdot V_{rotMagnitud}\right)}\cdot k_{radialAttenuation}\cdot V_{rotation}$$

![alt text](images/rotation_operator.gif)

[Play this it in DESMOS](https://www.desmos.com/calculator/qc0rr7hacq)

### Next Steps
- **Implement in Code**: Outline steps for adding the rotation operator.
- **Voxel-based Setup Compatibility**: Assess how this fits with a voxel-based obstacle detection setup.

[1] X. Ma and T. Chou, "Practical time-varying formation cooperative control for high-order nonlinear multi-agent systems avoiding spatial resource conflict via safety constraints," *International Journal of Robust and Nonlinear Control*, vol. n/a, no. n/a, doi: 10.1002/rnc.7600.

---

## 💻 Session 2024-10-30: Rotation Operator Brute Force Implementation

### Objective
**Make a Boid move forward while dodging an obstacle in front using Ma and Chou's Rotation Operator.**

1. Initialized the boid within a voxel, moving forward.
2. Set up a hard-coded intersection point as the obstacle.

### Findings
- The Boid successfully avoided obstacles, but turns were minimal; adjusting the amplitude coefficient had a significant effect.
```C++
float amplitudCoefficient = 80000.0f; 
```
- Functionality verified from both left and right obstacle positioning.
- Computing the simplified Cross yield very small number, consider adding a threshold since we only care about the sign
```C++
// Simple Cross product, taking Y as Up vector, with contribution zero.
float obstacleLocation = (velocity.normalize().x * boidToObstacle.normalize().z)
                        - (velocity.normalize().z * boidToObstacle.normalize().x);

const float overflowThreshold = 99.0f;

if(obstacleLocation < -overflowThreshold)
    obstacleLocation = -overflowThreshold;
else if(obstacleLocation > overflowThreshold)
    obstacleLocation = overflowThreshold;
```
- Lastly, just add the vectors
```C++
ofVec3f rotatorOperator = amplitudCoefficient * velocityAndProximityDamping * radialAttenuation * rotatorVelocity;
acceleration += rotatorOperator;
velocity += acceleration;

 if(velocity.length() > MAX_SPEED)
        velocity = velocity.normalize() * MAX_SPEED;

position += velocity * ofGetLastFrameTime();
```

![alt text](images/boid_avoidance_rotation_operator.gif)

### Next Steps
- **Dynamic Obstacle Positioning**: Test how the rotation operator functions with real-time updates in obstacle positions.
- **Multiple Obstacles**: Experiment with handling multiple obstacles simultaneously.
- **New Obstacle Detection**: Determine if the agent should track several obstacles in the critical zone, similar to neighbor tracking.

---

## 💻 Session 2024-10-31: Rotation Operator when Detecting Obstacle with a Ray

**Objective:** Make the boid use the rotation operator when a ray-sensed obstacle is detected.
- What happens when the intersection point starts changing position?
- Would the rotation operator work with multiple obstacles being tracked?

**Pseudocode:** Update the reference of one obstacle, the current intersection point.
```C++
1 if obstacle detected, update obstacle position to avoid
2 when the ray stops detecting obstacle, keep the last obstacle reference
3 while distance obstacle-boid <= critical radius
4   Apply rotation operator
5 if distance obstacle-boid > critical radius
6   set rotation operator to zero
```

Results:

When reaching the last obstacle and leaving the bounding volume, the boid disappears. This was due to not updating the boid-to-obstacle distance, so the distance was zero, and the force shot the boid out instantly.
Some cases:

Noticed the boid jumps when deciding the direction. The algorithm works by comparing the velocity and boid-to-obstacle angle. Since the ray returns a point along the ray, taking that point as the obstacle yields a zero angle, causing the boid to guess which side the obstacle is on. We need the center of the voxel.
Noticed the orientation of the turn has changed.

Case 1: In-line obstacles
![alt text](images/in_line.gif)

IMPORTANT consideration is to reflect the Cross product to account for the -Z axis.

Case 2: A wall obstacle
![alt text](images/fails_wall_case.gif)

It fails miserably when multiple obstacles are close (size by size) and have distinct centers. The voxel grid model would have to support subgroups of obstacles to distinguish between a large obstacle consisting of multiple voxels sharing the same center. This is still useful as the first part of the algorithm helps understand the shortest escape path, but during the avoidance protocol, the boid will have to check surrounding areas to fly free.

Case 2: Zig-zag obstacles
![alt text](images/zig_zag.gif)
Sparsed obstacle are an easy task for the rotation operator.

Case 4: In-line on x-axis
![alt text](<images/in-line horizontal.gif>)
As with the wall, obstacles close to each other are troublesome. It fails again because the ray is push to the voxel on the side, but the voxel center is further outwards, making the operator steer the boid to the other side again.

*Multiple boids, n = 20*

- Case 1: sparsed obstacle field
![alt text](images/cross_sparse_obstacle_field.gif)
In a flock, sparsed obstacle are also easy

- Case 3: Comparisson, Random obstacles with and without rotation operator
<div style="display: flex; justify-content: space-around;">
    <img src="images/many_random_without.gif" alt="Without Avoidance" width="45%">
    <img src="images/many_random_with.gif" alt="With Avoidance" width="45%">
</div>
One can see that without (left) the operator, there are more collission (red voxels), than when the operator is present (right). There still the need for a another heuristic to handle this scenatio propertly.

Conclusion:
- Tracking juts one obstacle is unrealistic and does not mimic the behaviour of real agents. It might be better to follow C. W. Reynolds, “Steering Behaviors For Autonomous Characters” original method, or evaluate how the operator con complemente Raynolds's mehtod.
- The operator ALONE simply does not work if there are obstacle verry close to each other. Theres is the need for a more complex logic.
- It does offers a smooth way to deal with small discrite obstacles, but if the voxel grid is too dense, meaning the vobstacle voxel are smaller, it might be overkill. It work well when the obstacle is comparatively similar to the size of the boid.

Next Setps:
- Track multiple obstacles
- Add Reynolds methods
- Fix original boids behaviour, and add follow target behaviour