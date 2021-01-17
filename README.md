## BulletTime: the 1v1 Shooter Arena where your past actions matter.
## Themes and Mechanics
 - 1v1
 - Local Multiplayer
 - Everything is reversed! (maybe :p)

## Gameplay Overview
1v1 your friends in this fast-paced shooter arena where tactics and the past affect your next rounds. In 3 rounds of 10 seconds of combat, attempt to reduce you opponent to 0 health before they do, first person to do this or the person with the most health after 3 rounds wins the arena. But there's a twist, your previous round actions are saved and played back (as if time was reversed with your actions being replayed) but in ghost form. Be careful though, although the ghost can no longer be shot, their bullets are still dangerous. So make sure you are cautious with your movements to prevent getting yourself in a crossfire and be tactical with your shots to catch them off-guard.

## Game Inspiration
Our inspiration came from our love of FPS games. We play games such as R6, CS:GO, and wanted to build a unique shooter ourselves. The time loop aspect is inspired from our curiosity of how replay systems work, as well as providing an extra layer of tactical gameplay.

## How it was made
The game was built on the [HackersNest](https://github.com/UbisoftToronto/HackersNest) Engine/API provided by Ubisoft based on the SFML library.  On top of this we extending the features by adding custom components and our own game entities. 

## Challenges we ran into
The first challenge we ran into was our overall experience with making games. Some of us had zero experience what so ever while some of us have dabbled in game development or game engine development but never a finished game. We took this challenge as an opportunity to learn more about making games and as motivation to actually finish a game. Our inexperience led us to take a while to ramp up to using this engine as we slowly figured out how to implement our game idea.

One of the problems was the feature of building a replay/playback system of the players actions from the last round. This feature caused us a bulk of our issues as we had to figure out how to first save/track the player's previous actions, then play them back in the next round. We ran into issues with memory allocation and our game acting really weird.

Another challenge was working collaboratively especially since it was not in person and since we found out early on that game development is highly reliant on each of the different parts. We found early on that some of us were waiting on other to finish features because our's depended on them. We actually found it very useful to do pair-programming as it was more efficient than figuring out how to layout the tasks.

## Accomplishments
Our accomplishments include creating a working event recording/replay system, creating our own Entities and Components to supplement the initial engine provided, and creating a playable game at the end of it all. Not only did we learn about how important ECS is in the design of games, but how to extend it to our needs. Getting a event replay system going was super complicated however rewarding, since this is one of the area of game design that has always been mysterious. Overall, we are proud to have been able to finish a game and thank Ubisoft for providing the resources and API. 

## What's next for BulletTime
We actually found the game was a lot of fun and want to continue building it out. Due to the time crunch, we were unable to polish our game to the standard we wanted. So the first step would be to polish our game (game restarting when game is over, etc.) Next, we want to add features such as wall destruction, grenades, and various types of guns. 
