<html>
    <p align="center">
        <img src="https://www.42porto.com/wp-content/uploads/2024/08/42-Porto-Horizontal.png" alt="Pipex Image" />
    </p>
    <h1 align="center">Philosophers</h1>
    <p align="center">
        <img src="https://github.com/user-attachments/assets/4363c36a-9ff3-4e40-b9b5-ea31b6db625b" width="300" alt="Image" />
    </p>
</html>

## Summary
<html>
    <p>
        <b>Philosophers</b> is a project from 42 School that aims to teach how to creat programs with threads.<br>
		<b>What was the problem that was presented?</b><br>
		The project involves a table with X number of philosophers who will perform certain actions, and the goal is to keep them alive for as long as possible. Each philosopher will perform the actions of eating, sleeping, and thinking. The first two parameters (time to eat and time to sleep) are defined as arguments when calling the function, while the time to think will be defined by the project owner.<br>
		To eat, each philosopher needs two forks. Each philosopher has only one fork, and they will need two to eat, so they need to take the other fork from another philosopher. After eating, if the philosopher is still alive, they should sleep for the duration specified in the arguments.<br>
		The simulation ends when one philosopher dies, or if the optional parameter <number of meals> is provided, when all the philosophers have eaten the required number of meals.
	</p>
</html>

## Thread
<html>
    <p>Thread is a sequence of instructions that can be executed independently by a computer's CPU. Threads are the smallest unit of processing that can be scheduled by an operating system. They allow for concurrent execution of code, which can improve the performance of applications, especially on multi-core processors.
	</p>
</html>

## Mutex
<html>
    <p>A mutex, short for "mutual exclusion," is a synchronization primitive used in concurrent programming to manage access to shared resources. It is designed to prevent multiple threads from simultaneously accessing a resource, which can lead to race conditions and inconsistent data.<br>
	In this project, each fork will be represented by a mutex. Additionally, other variables, such as meal->m_finished (marks meal as finished), also need to be protected by a mutex to prevent different threads from reading and writing to it simultaneously.
	</p>
</html>

## Parameters
<html>
    <ol>
        <li><b>Number of philosophers - </b>The number of philosohers which will be on the simulation</li>
		<li><b>Time to die - </b>The time (in milliseconds) that a philosopher has to live.Starts counting right after the last meal is eaten.</li>
		<li><b>Time to eat - </b>The time (in milliseconds) it takes for a philosopher to eat.</li>
		<li><b>Time to sleep - </b>The time (in milliseconds) that a philosopher sleeps.</li>
		<li><b>Number of meals(optional) - </b>The number of meals each phisolosopher sould eat.</li>
	 </ol>
</html>

## Code Phases
### Parsing
<html>
    <ol>
		<li> Check if the number of parameters is correct. The program should have 4 or 5 parameters depending on whether the number of meals is included.</li>
		<li> Implement the <b>atol( )</b>(string to long integer) function for each of the parameters, ensuring that the input consists only of numbers and that they are positive. This is important because there cannot be negative values for philosophers, meals, or time. We are using atol because we will be working with milliseconds, and the time values may exceed the range of a standard integer. This approach allows us to compare these values without needing to perform type casting.</li>
	</ol>
</html>

### Simulation start
<html>
    <ol>
		<li>In the case of a single philosopher, the simulation will start, but since the philosopher has only one fork, they will die once the time to die has elapsed. For this we call <b>one_philo( )</b>.</li>
		<li>In the case of multiple philosophers, we call <b>init_philo( )</b> to allocate memory for the arrays we use: the array of mutex forks, the array of other mutexes (defined by the enum), and the array for philosophers. After that, we initialize each philosopher, providing them with all the variables they will need to access during the simulation. To avoid <b>data races</b> (which occur when multiple threads access the same memory location concurrently), we assign each philosopher their own time to sleep, time to die, and other relevant variables. The only variable they will need to check from the main structure is whether the simulation has finished. In this loop, we will assign the forks that each philosopher will use. Each philosopher's right fork will be the one matching their ID number, while the left fork will be their ID plus one, except for the last philosopher, who will have the left fork as the first philosopher's fork. This arrangement is designed to prevent <b>deadlock</b> (a situation where two or more processes are unable to proceed because each is waiting for the other to release a resource).
		</li>
		<li><b>init_threads( )</b> - We call this function to initialize each thread (which represents one philosopher), to initialize the mutex array, and to initialize the supervisor/monitoring thread (which will be responsible for checking if any philosopher has died and if the required number of meals has already been accomplished). The <b>pthread_mutex_init( )</b> function receives the address of a mutex, just as pthread_create( )</b> receives the address of the thread, the function to be executed, and the structure for each philosopher.
		</li>
		<li> After all threads are created we call <b>init_eat_time( )</b> to give each philosopher the starting simulation time.
	</ol>
</html>

## Code Setup
<html>
    <p>    
    <b>Step 1:</b> Clone the repository
    </p>
</html>
 
    git clone https://github.com/Hugofslopes/philosophers

<html>
    <p>
    <b>Step 2:</b> Open the terminal on the repo folder and write
    </p>
</html>

   cd /philol; make

<html>
    <p>
    <b>Step 3:</b> Execute
    </p>
</html>

    ./philo <number of philosophers> <time to die> <time to eat> (optional): <number of meals>

<html>
    <p>
    <b>Step 4:</b> Run tests<br>
	</p>
</html>

	./philo 1 800 200 200

	./philo 5 800 200 200

    ./philo 5 800 200 200 7

	./philo 4 410 200 200

	./philo 4 310 200 100

	./philo 4 400 200 200

	./philo 5 400 200 200

	./philo 2 410 200 200

	./philo 2 400 200 200

	./philo 5 800 200 200 10 | grep "is eating" | awk '{print $2}' | sort | uniq -c
## Improvements