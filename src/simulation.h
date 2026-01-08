/*
***** class Simulation

private ig_runtime = 24*60*60 //ig=ingame, 24*60*60 means each simulation represents 24hrs
private ig_sec_per_tick = 10

private tt: Image
private tm: Image
private dir: Image
private mph: Image

private cm: Image

private agents: [Agent, ...]


public create(tt, tm, dir, mph, ig_runtime, ig_sec_per_tick) -> Simulation
    * tt,tm,dir,mph
    * set_connectivity_matrix() -> keep as image
    * populate_agents()

private set_connectivity_matrix() -> void

private populate_agents() -> void


***** class Agent:

private position: Vector2i //cell position
private targets: [Vector2i]
private destination: Vector2i

//inventory
car: Car

//state
private exists: bool


public create() -> Agent

public create_random() -> Agent
* specifiy probabilites of certian things

public get_exists() -> bool
public get_


***** class Car

private owner: Agent
private exists: bool
private contents: [Agent]
private position: Vector2i
private targets: [Vector2i]



start -> walk -> destination
start -> walk -> target car -> enter car -> drive -> target parking -> exit car -> walk -> destination


known: start cell and end cell
Determine path sequence: walk or drive
* check walking connectivity:
    * walk eta: Euclidean distance between start cell and end cell times average walking speed along the path
* check drigin connectivityL
    * place a parking reservation (look for closest parking spot, not reserved, connected)
    * drive eta: walk eta to car, car euclidean to parking (where?), walk euclidean to destination
* path sequence = 0, 1 (WALK, DRIVE)
* Generate a lower resolutuon path using A* world is 512 x 512 (between what and what??)
* Generate a higher resolution path using A* of max size of 512 at a time
* add to the higher resolution path every 64 
* HOW TO MOVE FORWARD ALONG THE PATH. WHAT DO I WANT TO STORE?


***** ParkingManager
2D matrix of parking spots
given a spot, and a connectivity group id, find neasest not reserved parking space (exit condition to avoid a full search)

***** ParkingSpot
* 
* contents
* reserved for car...


position is a vector2
destination and targets are cells













*/
























/*
    TIME: ticks, Ig time, RL time

    class Simulation
    public ig_runtime = 24*60*60 //in game runtime = 24 hours (ie every 4min rl simulation represents 24 hours ig)
    public ig_sec_per_tick = 10

    private tt Image
    private tm Image
    private dir Image
    private mph Image

    private cm: image


    public create(tt, tm, dir, mph) -> Simulation
        * tt, tm, dir, mph
        * set_connectivity_matrix()
        * set_agents_start_position()
        * set_cars_start_position()
        * paths and stuff (1. Path Sequence (walk, car, park, walk or walk), 2. parking reservations, 3. high level path (4. lower level path 1st one each gets generate at runtime)

    private set_connectivity_matrix()
        * cm
    private set_agents_start_position()
    private set_cars_start_position()

    public get_total_ticks() -> int
    public step(by_ticks: integer)


    Data Structures
    * if it gets written to the screen via a visaul shader it should be packed into a img/tex

    I want to show the path for a particular agent but I dont need to show all agents paths simultainously.


    I need a function to generate a path sequence for a agent (agent position, car position, target_position)
    -> path sequence is a packed 8 bit integer 

    I navigate to a car, enter the car, then the car navigates agent to parking space, agent exits the car, and continues (importatnt so logic can be generalized for trains...)


    Agent Object: (col, row), position, target_position, Owned_Car, inside_car when a modification to position occurs, look in col,row in hte image an make the modification
    Car Object: position, target_position, Contained_Agents, reserved_parking_spot_id

    Agent.step -> move
    Car.step -> move

    Agent.create() (give it a rowwise id)
    Agent.assign targe


    position
    cars position
    target position
    reserved parking position
    inside of car
    path sequence: walk only or (walk, drive, walk)
    high level path: 8x8 blocks

    Agent wants to navigate to car as its sub target, then (uses the sequence)

    path_sequence: [8bit integers, ...]
    * walk = [00000000]
    * walk,drive,walk = [00000000 00000001 00000000]





    Person: has a position, want to go to a destination, may go to several targets to get to destination
    
    * position
    * destination
    * target
    * car
    * in_car
    * path_sequence
    * lr_path_to_target: [32 bit ints] (lr = low resolution)
    * path (higher rsolution)

    Car: has a position, is at a parking space and want to get to another parking space (how to pick which pakring space)
    * position
    * 
    * reserved parkign space
    * No Target or desitnation, must take a target from an Agent
    * contained_agents: [Agent]

    Parking: 
    * which spots are going to have people and from what times will they be filled. 
    



    CM
    Generate 64 x 64 agents and 70% have a car
    * give them a starting position for person and car
    * give them a destination
    * give person a path_sequence and a parking spot
    * Now I have enough





*/
