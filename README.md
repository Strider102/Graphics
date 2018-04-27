# Graphics

# Week of 1/29/18
![alt text](https://github.com/Strider102/Graphics/blob/master/images/Triangle%201.png) <br />
![alt text](https://github.com/Strider102/Graphics/blob/master/images/Triangle%202.png) <br />
	a. The theme is internet memes. <br />
	b. We plan on one main room now with potential to expand. <br />
	c. No ideas on floor and wall textures yet, but nothing that detracts too much from the art. <br />
	d. For now we are planning on having a ceiling, but depending on how lighting works out, we might change that. <br />
	e. For our sculpture, we will use Ugandan Knuckles. We should be able to find models online, but the character isn't too detailed so we could potentially do it on our own. <br />
	f. For the paintings, we will have some greatest hits of memes. These will be just like paintings hung on the wall with frames around them.

# Week of 2/12/18
![alt text](https://github.com/Strider102/Graphics/blob/master/images/blender_screenshot.png) <br />
[Access Blender File Here!](https://github.com/Strider102/Graphics/blob/master/Museum.blend)

# Week of 2/26/18
Attempts have been made to get an object loader working, but we are still learning more about the details that have not yet been implemented or tested.

# Week of 3/5/18
![alt text](https://github.com/Strider102/Graphics/blob/master/images/cube_rendering.png) <br />
![alt text](https://github.com/Strider102/Graphics/blob/master/images/pikachu_rendering.png) <br />
Our model loader has been successfully implemented. It swaps between 2 models, a cube and pikachu, when spacebar is pressed. Pikachu looks fine but the cube is so big it looks weird and we thought it wasn't working for the longest time. In general, code was also cleaned up a bit so main is not so cluttered.

# Week of 3/26/18
![alt text](https://github.com/Strider102/Graphics/blob/master/images/camera.png) <br />
Our museum is loading and we have a functioning camera that can move in all directions as well as movement in all directions.

# Week of 4/2/18
![alt text](https://github.com/Strider102/Graphics/blob/master/images/textures1.png) <br />
One color of our textures are loading on the walls and floors. Camera is fixed to include projection matrix.

# Week of 4/9/18
![alt text](https://github.com/Strider102/Graphics/blob/master/images/planet.png) <br />
Did some cleanup. Tried loading in an outside model to see if our texture issue was with the code or our model. The test model we found of a planet works and looks great. We are looking to resolve issues with our model now.

# Week of 4/23/18
![alt text](https://github.com/Strider102/Graphics/blob/master/images/museum.png) <br />
Added comments and picutre frames to the museum. We still have issues with our generated models showing more than one color of the texture. As seen before, other models work, but we are having issues with blender and cannot find out what is wrong. In the src folder is all code and the most recent assets as well as the executable for our code.

# Final Update!
![alt text](https://github.com/Strider102/Graphics/blob/master/images/pic1.png) <br />
![alt text](https://github.com/Strider102/Graphics/blob/master/images/pic2.png) <br />
![alt text](https://github.com/Strider102/Graphics/blob/master/images/pic3.png) <br />
![alt text](https://github.com/Strider102/Graphics/blob/master/images/pic4.png) <br />
![alt text](https://github.com/Strider102/Graphics/blob/master/images/statue.png) <br />
While fooling around with lighting in the fragment shader, textures all of a sudden started working! Now the player has a flashlight and can walk and look around the museum with fully functioning textures. <br />
<br />
And that's it. You can look at the blender file in all_assets/blender. A linux executable is in the src folder. Enjoy!
