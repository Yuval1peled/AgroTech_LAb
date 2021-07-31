# AgroTech_LAb
### Liron Grossmann & Yuval Peled

![WhatsApp Image 2021-07-20 at 08 55 09](https://user-images.githubusercontent.com/81626067/126270377-5971ea56-3db7-4403-9472-26bc5154443f.jpeg)


This project's goal was to encourage us to come up with ideas and solutions to build our system. We were given an abstract idea of what this project will include and had to brainstorm as a group and develop a plan that included what parts we need for each level of this project, how to connect them, and how to write a code that will run smoothly.  

We were asked to come up with an irrigation system comprised of three main parts. Each one is more elaborated than the last: the first will water its plant based on time, the second will include a sensor that will read the moisture levels in its soil and water it accordingly. Lastly, the third part of our system will weigh the plant and its soil and will water it deducting the plant's added weight.

For the two of us, who do not major in soil and water science major or plant science, this project was very hard as we do not have preliminary knowledge that might help us understand how the type of system is supposed to build work. Nevertheless, we dived head deep into the development of our project.

To start, we have built our three-valve system (description provided in the following folder) that was connected to our relay module that would eventually help us control each valve separately. As we went along, we learned basic skills like soldering wires and components together and immensely enjoyed the process. With these parts and our new skills, we started working on our basic code, which we later modified and expanded upon to accommodate the rest of our systems' parts.

![WhatsApp Image 2021-07-31 at 11 47 46](https://user-images.githubusercontent.com/81626067/127742469-0379a053-66fd-45d5-a72d-26d289c01f92.jpeg)
![WhatsApp Image 2021-07-31 at 11 47 46 (1)](https://user-images.githubusercontent.com/81626067/127742471-17a94425-a787-4932-837e-d8674355ac2d.jpeg)

With this project's base done, we moved on to tackle the more challenging aspects of the system: connecting the soil humidity sensor, weight module and connecting the project as a whole to our Thingspeak servers.

![WhatsApp Image 2021-07-31 at 11 47 47](https://user-images.githubusercontent.com/81626067/127742493-f380a49a-aa2f-4db6-ab86-a7f0caf21cd3.jpeg)
![WhatsApp Image 2021-07-31 at 11 49 34](https://user-images.githubusercontent.com/81626067/127742494-b8c2fc1e-5305-4730-b409-a4b4f86142cd.jpeg)

## The Code:

After few weeks of building our hardware and developing our project, we started gathering pre-existing codes to run each system component. As most parts are widely available most of them came with basic coding that runs with those parts. Moreover, some of the Arduino libraries needed to run those parts came with example codes that we modified to fit our needs.

As we wrote before, to keep things simple, clean, and efficient, we wrote the code for each part of our system individually, all based on those pre-existing codes. We started with the code for our valve and relays, making them open and close based on our commends. Then we connected to one of these valves the soil humidity sensor and merged the code for these two components together.

Afterward, we connected our weight sensor to a valve. At this point, we had to calibrate the sensor to give us a reading that corallites to a known weight measurement. That was done manually with physical weights. We collected the data and created an equation to give us a reading we can understand and include in our project's code.

Now that we had all our parts and code running separately, we began the task of combining the codes into one. We also integrated a code we were given to connect our project to the internet and the Thingspeak server. As our Thingspeak account is free, it can only get a reading once every 15 seconds, which is not as accurate as we would like. So in our final code, we considered that and worked around this limitation. Another modification we did is connecting our system's code to an online clock that would help us run it all remotely. With this combined (And working) code, we could go on and assemble the project in a greenhouse and start collecting data. The complete code is attached above.

## Our Hypothesis:

Due to lack of time, we could not collect enough data to analyze our system readings and collected data. Instead, we would like to share our thoughts and hypotheses:

We assume that we will detect an exponential decrease in our readings in the planter with the humidity sensor. The soil water content will go down until we reach the threshold that we set in our code. At this point, our sensor reading will trigger the valve to open, allowing water to rehydrate the soil. A drastic spike will accompany this in the reading we will receive. Another factor to take into consideration is the rising temperature throughout the day. We can assume that approaching midday, the rate of water loss from our soil will increase exponentially. 

![WhatsApp Image 2021-07-31 at 13 22 14](https://user-images.githubusercontent.com/81626067/127742421-02048b8d-f888-4e51-b336-151c2dcdc356.jpeg)

As for our weight sensor, we can assume that the data we would receive would look similar to the humidity sensor. We should see an exponential decrease in our planters' weight throughout the day as the water evaporates through the plant and the exposed soil. Similarly, we have set a trigger weight that will open our water valve to water the plant for a set amount of time. After that, the valve closes, and we will see a spike in our data. To account for our plants growing wight in this system, we set the weight scale to be reset at midnight every day.

![WhatsApp Image 2021-07-31 at 13 22 15](https://user-images.githubusercontent.com/81626067/127742431-6365cf0e-a0bc-4953-84a1-16ef8e3cc903.jpeg)

