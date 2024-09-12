# Spatial partitioning study - with OpenFrameworks

To run this project, first [Download OpenFrameworks source code](https://openframeworks.cc/download/). Then, move inside the `myApps` folder. You need this to have access to the OpenFrameworks header files.
```bash
cd openframeworks_version_####/apps/myApps/
git clone [URL]
```

# Backlog
- [ ] Oranize objects into scenes
- [ ] Create volume representing the domain of the environment
- [ ] subdivide the volume into a uniform grid of voxels, visualize them  


## Useful snipets
```C++
    stringstream ss;
    ss << "Spatial partitioning: " << '\n' << '\n';
    ss << "FPS: " << ofToString(ofGetFrameRate(),0) << '\n' ;
    ss << "Voxel Grid Resolution: " << voxelGridResolution << '\n' ;
    ofDrawBitmapStringHighlight(ss.str().c_str(), 20, 20);
```