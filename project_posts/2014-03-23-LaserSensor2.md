Finally we converted all switches to laser range sensors as planned.

It was great challenge because we could spend only two days for that.


## Challange of Laser Range Sensor

The point of the laser sensor is that it returns value not with grid array style data but angle and distance with fan shaped area.

The first thing we had to do is convert fan shaped data to grid shaped data. This part is not so difficult just sin / cos issue.

Second and difficult part is detecting foot area from blob grid arary point with blob detection.

At first we used OpenCV for blob detection. 



## Obstacles

However we found two problems.

One is that what we need is just blob position but detecting moment and location of step impacts.

Another problem is speed. Open CV image processing was not fast as we desired.

Therefore we descided to make our own region finder program.


## Result

However we found two problems.

One is that what we need is just blob position but detecting moment and location of step impacts.

Another problem is speed. Open CV image processing was not fast as we desired.

Therefore we descided to make our own region finder program.




## The hardest challange is over!

Now we will start video making for our presentation.


![Exhibition Sketch](../project_images/sketches/sketch_035.png?raw=true "Example Image")




