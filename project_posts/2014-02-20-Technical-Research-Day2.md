#Technical Research / Hardware

Technical Research again! While I study openFrameworks and C++. I also need to consider device thing.

To make interactive floor. I planned four approach. Each one have pros and cons.

#Idea A: Pressure Sensor Matrix

![Floor Sketch](../project_images/sketches/sketch_017_plan_a.png?raw=true "Example Image")

First and theoretically best idea is making sensor grid matrix. In this case pressure sensor.

This seems best if I just see positive side. Of Course there are also risks. Technical difficulty and cost!

- **PRO:** Very accurate!
- **PRO:** Can get pressure velocity! Not just on and off.
- **CON:** Seems Very Expensive.
- **CON:** Using analogue sensor is technically difficult.
	
	
	
#Idea B: Kinect and Open CV

![Floor Sketch](../project_images/sketches/sketch_018_plan_b.png?raw=true "Example Image")

An alternative idea is using Kinnects. Its easy and cheap, but not so accurate I think.

	- **PRO:** Cheap! Just 2 to 3 kinnects.
	- **PRO:** I can use powerful existing library like Open CV.
	- **PRO:** Easy to test. Setup is just kinnect and projector.
	- **CON:** Not so accurate because What I need is not position but detecting foot step.
	- **CON:** Multiple human's shadow prevent detecting.
	
	
#Idea C: Projection from down stairs.

![Floor Sketch](../project_images/sketches/sketch_019_plan_c.png?raw=true "Example Image")

Third idea is an another image recognition. By making big floor structure with openCV and projector.

I use infrared LED to detect human's shadow from under the floor.

Technically its accurate, but quite expensive and difficult.

	- **PRO:** Very accurate.
	- **PRO:** Just open CV! Most of technical issue is just software side.
	- **CON:** I need massive structure. It must be hard and really expensive!
	- **CON:** I have to think about safety, because it must be little bit higher place.
	- **CON:** I need huge space for prototyping.
	

#Idea D: Kinect and Open CV

![Floor Sketch](../project_images/sketches/sketch_020_plan_d.png?raw=true "Example Image")

Handy version of Plan A. Instead of sensor matrix, It just uses switch matrix. Its cheaper!!

	- **PRO:** Very accurate I hope.
	- **PRO:** Not so expensive.
	- **CON:** Too many switches, making them seems to be bit tough.



As far as I compare those ideas. Plan B and Plan D seem to be possible idea. Plan A and Plan C seems nice but quite expensive and I do not have enough time.

I gonna try Idea B and Idea D for prototyping. If I win the competition, I also may be test plan A and plan C as well.
