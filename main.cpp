#include <iostream>
#include <vector>
#include <unordered_map>
#include <string> 
#include "elec_functions.cpp"

int main(){
	std::vector<std::unordered_map<std::string, std::string>> candidates;
	std::vector<std::unordered_map<std::string, std::string>> voters;
	std::vector<int> postcodes;
	int liberalVotes = 0;
	int laborVotes = 0;
	int userChoice = 0;
	
	while(userChoice != 5){
		userChoice = 0;
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "1. Place a vote" << std::endl;
		std::cout << "2. Add a candidate" << std::endl;
		std::cout << "3. Add a voter" << std::endl;
		std::cout << "4. Add a postcode" << std::endl;
		std::cout << "5. Exit program" << std::endl;
		std::cin >> userChoice;
		
		if(userChoice == 1){ 
			if(retrieve_voter(voters, candidates) == true){
				liberalVotes++;
			}
			else{
				laborVotes++;
			}
			
			std::cout << "Votes for Liberal: " << liberalVotes << std::endl;
			std::cout << "Votes for Labor: " << laborVotes << std::endl;
		}
		
		if(userChoice == 2){ candidates.push_back(add_candidate(postcodes)); }
		if(userChoice == 3){ voters.push_back(add_voter(postcodes, (10000000 + voters.size()))); }
		if(userChoice == 4){ postcodes.push_back(add_postcode()); }
		if(userChoice < 1 || userChoice > 5){ std::cout << "Sorry, that is not a valid option." << std::endl; }
	}
		
	return 0; 	
}
