#include <iostream>
#include <vector>
#include <unordered_map>
#include <string> 

std::string get_name(){
	std::string fullName;
	std::cout << "Please type the person's name that you would like to add." << std::endl;
	std::cin.ignore();
	std::getline(std::cin, fullName);
	return fullName;
}

std::string get_party(){
	std::string party;
	int userChoice = -1;
	while(userChoice != 1 && userChoice != 2){
		std::cout << "Please select a party." << std::endl;
		std::cout << "1. Liberals" << std::endl;
		std::cout << "2. Labor" << std::endl;
		std::cin >> userChoice;
		if(userChoice == 1){ party = "Liberal"; }
		if(userChoice == 2){ party = "Labor"; }
		if(userChoice != 1 && userChoice != 2){ std::cout << "Please pick a valid option." << std::endl; }
	}
	return party;
}

int get_postcode(std::vector<int> validPostcodes){
	int postcode;
	int userChoice = -1;
	while(userChoice < 0 || userChoice > validPostcodes.size()){ 
		std::cout << "Please select the postcode which this candidate represents." << std::endl;
		for(int i = 0; i != validPostcodes.size(); i++){
			std::cout << i << ". " << validPostcodes.at(i) << std::endl;
		}
		std::cin >> userChoice;
		if(userChoice >= 0 && userChoice <= validPostcodes.size()){ postcode = validPostcodes.at(userChoice); }
		else{ std::cout << "Please pick a valid option." << std::endl; }
	}
	return postcode;
}


std::unordered_map<std::string, std::string> add_candidate(std::vector<int> validPostcodes){
	std::unordered_map<std::string, std::string> candidateDetails;
	candidateDetails["Full Name"] = get_name();
	candidateDetails["Party"] = get_party();
	candidateDetails["Postcode"] = get_postcode(validPostcodes);
	return candidateDetails;
}

std::unordered_map<std::string, std::string> add_voter(std::vector<int> validPostcodes, int id){
	std::unordered_map<std::string, std::string> voterDetails;
	voterDetails["ID"] = std::to_string(id);
	std::cout << voterDetails["ID"] << std::endl;
	voterDetails["Full Name"] = get_name();
	voterDetails["Postcode"] = get_postcode(validPostcodes);
	// TODO: voterDetails["Has Voted"] = "false";
	return voterDetails;
}

int add_postcode(){
	int postcode = -1;
	while(postcode < 1000 || postcode > 9999){
		std::cout << "Please type in a postcode." << std::endl;
		std::cin >> postcode;
		if(postcode < 1000 || postcode > 9999){
			std::cout << "That is not a valid postcode." << std::endl;
		}
	}
	return postcode;
}

bool set_vote(std::string postcode, std::vector<std::unordered_map<std::string, std::string>> candidates){
	std::vector<std::unordered_map<std::string, std::string>> relevantCandidates;
	
	for(auto itr = candidates.begin(); itr != candidates.end(); ++itr){ 
		std::unordered_map<std::string, std::string> candidate;
		candidate = *itr;
		if(candidate.find("Postcode")->second == postcode){
			relevantCandidates.push_back(candidate);
		}
	}
	
	int userChoice = -1;
	int indexNo;
	std::cout << "Please type the number of the candidate that you would like to vote for." << std::endl;
	while(userChoice < 0 || userChoice > relevantCandidates.size()){
		indexNo = 0;
		for(auto itr = relevantCandidates.begin(); itr != relevantCandidates.end(); ++itr){ 
			std::cout << indexNo << ". " << (*itr).find("Full Name")->second << ", party: " << (*itr).find("Party")->second << std::endl;
			indexNo++;
		}
		std::cin >> userChoice;
		if(userChoice > -1 && userChoice < (relevantCandidates.size() + 1)){ 
			if(relevantCandidates[userChoice].find("Party")->second == "Liberal"){ return true; }
			else { return false; }
		}
		std::cout << "Invalid selection. Please type the number of a valid candidate." << std::endl;
	}
}

bool retrieve_voter(std::vector<std::unordered_map<std::string, std::string>> voters, std::vector<std::unordered_map<std::string, std::string>> candidates){
	int sentinel = 0;
	std::string inputId;
	std::string voterName = "Not defined.";
	std::string voterPostcode = "0000";
	while(sentinel != 9999){
		std::cout << "Please type your ID." << std::endl;
		std::cin >> inputId;

		for(auto itr = voters.begin(); itr != voters.end(); ++itr){ 
			std::unordered_map<std::string, std::string> voter;
			voter = *itr;
			if(voter.find("ID")->second == inputId){
				voterName = voter.find("Full Name")->second;
				voterPostcode = voter.find("Postcode")->second;
				break;
			}
		}

		if(voterPostcode == "0000"){ std::cout << "This is not a valid ID." << std::endl; }
		else { break; }
	}
	
	return set_vote(voterPostcode, candidates);
}

