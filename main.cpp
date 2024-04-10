#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>

//random number generator
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char *argv[]){
	
	if(argc == 1){

		//check for args
		std::cout << "arguments not provided" << "\n";

	}	
	else if(argc == 2){

		//check for args
		std::cout << "num doors opened by host, num simulations not provided" << "\n";

	}
	else if(argc == 3){

		//check for args
		std::cout << "num simulations not provided" << "\n";

	}
	else if(argc == 4){

		//num doors
		int num_doors = 0;
		try{
			num_doors = std::stoi(argv[1]);

			if(num_doors <= 0){

				//strictly positive values allowed
				std::cout << "only positive values allowed" <<  "\n";
				return 0;

			}
		}
		catch(const std::invalid_argument& e){

			//check invalid args
			std::cout << "invalid argument " << e.what() << "\n";
			return 0;

		}
		catch(const std::out_of_range& e){

			//check out of range
			std::cout << "out of range " << e.what() << "\n";
			return 0;

		}

		//num doors opened by host
		int num_doors_opened_by_host = 0;
		try{
			num_doors_opened_by_host = std::stoi(argv[2]);

			if(num_doors_opened_by_host <= 0){

				//strictly positive values allowed
				std::cout << "strictly positive values allowed" << "\n";
				return 0;

			}
		}
		catch(const std::invalid_argument& e){

			//check invalid args
			std::cout << "invalid argument " << e.what() << "\n";
			return 0;

		}
		catch(const std::out_of_range& e){

			//check out of range 
			std::cout << "out of range " << e.what() << "\n";
			return 0;

		}

		//num simulations
		int num_simulations = 0;
		try{
			num_simulations = std::stoi(argv[3]);

			if(num_simulations <= 0){

				//strictly positive values allowed
				std::cout << "strictly positive values allowed" << "\n";
				return 0;

			}
		}
		catch(const std::invalid_argument& e){

			//check invalid args
			std::cout << "invalid argument " << e.what() << "\n";
			return 0;

		}
		catch(const std::out_of_range& e){

			//check out of range
			std::cout << "out of range " << e.what() << "\n";
			return 0;

		}

		if(num_doors_opened_by_host + 2 > num_doors){

			//check if possible to open doors
			std::cout << "it is not possible to open the doors specified" << "\n";
			return 0;

		}

		//total num of itrs
		int total_itrs = num_simulations;

		//count itrs in which switch results in winning
		int switch_itrs = 0;

		//count itrs in which sticking results in winning
		int stick_itrs = 0;

 		//SIMULATION FOR STICKING:
 		//we need not simulate opening of doors because it won't effect the
 		//probability at all
		for(int i = 0; i < total_itrs; i++){

			//first assign a prize position
			int prize_position = rng() % num_doors;

			//then assign contestant door position
			int contestant_door_position = rng() % num_doors;

			//check for first chairs
			if(prize_position == contestant_door_position){
				stick_itrs++;
			}

		}

		//SIMULATION FOR SWITCHING:
		//here firstly if we get same position for prize and contestant position
		//it is useless to switch
		//if not then we may get to prize after switching
		//in the simulation if we have diff positions for prize and contestant
		//we can then reorder the doors such that
		//last door is participant door (n-1)
		//next last p doors i.e (n-p-1, n-2) are opened by host
		//0 door is prize
		//hence to select the door for opening it is 
		for(int i = 0; i < total_itrs; i++){

			//first assign contestant position
			int contestant_position = rng() % num_doors;

			//second assign prize position
			int prize_position = rng() % num_doors;

			if(contestant_position != prize_position){

				//selection of prize
				int prize_select_position = rng() % (num_doors - num_doors_opened_by_host - 1);

				if(prize_select_position == 0){
					switch_itrs++;
				}
			}

		}

 		//output
		std::cout << "--- output ---" << "\n";
		std::cout << "switching : " << ((float)switch_itrs / total_itrs) * 100 << "\n";
		std::cout << "sticking : " <<  ((float)stick_itrs / total_itrs) * 100 << "\n";

	}
	else{

		//more args provided
		std::cout << "more than 4 arguments provided" << "\n";	

	}

	//i think that bonus code will be same because the probability 
	//implementation has the same logic as this
	//i tried to implement efficiently..
	//i know it is possible to implement in brute force manner
	//directly selecting positions and making vectors
	//which takes space and time complexity
	
	return 0;
}