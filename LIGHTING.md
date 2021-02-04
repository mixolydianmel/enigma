# Lighting
> All the stuff I have to do for lighting right now

## Graphics
+ Directional
+ Multiple lights
+ Shadow mapping
+ Point shadows

## Backend
+ Scene light management
+ Better shader selection
+ Light object (not just a cube)

## Scene Light Management
+ Renderer has a vector of lights?
    + Somewhere in the scene there should be a lights vector
    + On render, vector gets passed to the shader (somehow)
    + Shader takes into account each light in scene?
        + Check other projects to make sure this is best approach
+ Make sure chosen approach is extensible
    + Works with shadows, performance, etc.
+ Works with multiple types of lights

## Organization
+ Redocument engine
+ Create a wiki?
+ Use something (trello,tasque,etc.) to organize TODO lists
