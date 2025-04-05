# LoadAnimation Component

The LoadAnimation component provides animated loading indicators for the OLED display with the ability to execute a function in parallel with the animation.

## Features

- Multiple animation presets (Progress Bar, Circle Sweep, Dot Sequence)
- Function execution during animation
- Minimum animation duration of 1 second
- Automatic adaptation to display size and orientation
- Smooth transitions

## Usage

### Basic Usage
```cpp
LoadAnimation* loader = new LoadAnimation(1, LOAD_ANIM_PROGRESS_BAR);
displayManager.addComponent(loader);
```

### Usage with Function Execution
```cpp
LoadAnimation* loader = new LoadAnimation(1, LOAD_ANIM_CIRCLE_SWEEP);
loader->execute([]() {
    // Your code here
    return 0; // Return next component ID
});
displayManager.addComponent(loader);
```

## Methods

### Constructor
```cpp
LoadAnimation(unsigned int id, LoadAnimationPresets preset)
```
Creates a new loading animation with the specified ID and preset.

### execute
```cpp
void execute(std::function<unsigned int()> execute)
```
Sets a function to be executed in parallel with the animation. The function will be executed once and should return the ID of the next component to display.

### nextComponent
```cpp
void nextComponent(unsigned int nextComponent)
```
Sets the ID of the next component to display after the animation completes.

## Animation Presets

### Progress Bar
A horizontal progress bar that fills from left to right.

### Circle Sweep
A circle with dots that rotate around the center.

### Dot Sequence
Three dots that animate in sequence.

## Examples

### Basic Loading Animation
```cpp
void setup() {
    LoadAnimation* loader = new LoadAnimation(1, LOAD_ANIM_PROGRESS_BAR);
    displayManager.addComponent(loader);
}
```

### Loading Animation with Function Execution
```cpp
void setup() {
    LoadAnimation* loader = new LoadAnimation(1, LOAD_ANIM_CIRCLE_SWEEP);
    loader->execute([]() {
        // Simulate some work
        delay(2000);
        return 2; // Return next component ID
    });
    displayManager.addComponent(loader);
}
```

### Multiple Loaders with Different Presets
```cpp
void setup() {
    LoadAnimation* loader1 = new LoadAnimation(1, LOAD_ANIM_PROGRESS_BAR);
    LoadAnimation* loader2 = new LoadAnimation(2, LOAD_ANIM_CIRCLE_SWEEP);
    LoadAnimation* loader3 = new LoadAnimation(3, LOAD_ANIM_DOT_SEQUENCE);
    
    displayManager.addComponent(loader1);
    displayManager.addComponent(loader2);
    displayManager.addComponent(loader3);
}
```

## Best Practices

1. **Function Execution**
   - Keep the executed function as short as possible
   - Return the correct next component ID
   - Handle errors appropriately

2. **Animation Selection**
   - Choose the preset that best matches your use case
   - Consider the display size and orientation
   - Test different presets for optimal performance

3. **Performance**
   - Avoid long delays in the executed function
   - Use appropriate animation presets for your needs
   - Monitor memory usage with multiple animations

4. **User Experience**
   - Ensure smooth transitions between components
   - Provide visual feedback during loading
   - Consider using different presets for different contexts 