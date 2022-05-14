#include <iostream>
#include <fstream>
#include <stdexcept>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

#include "constants.hpp"
#include "guess.hpp"

std::set<std::string> load_dict(std::string const & path) {
	std::ifstream infile(path);
	std::set<std::string> dict;
	std::string line;

	while (std::getline(infile, line)) {
		if (line.length() != 5) {
			throw std::invalid_argument("Invalid word in dictionary: " + line);
		}
		transform(line.begin(), line.end(), line.begin(), toupper);
		dict.insert(line);
	}
	return (dict);
}

Guess	get_guess(std::set<std::string> const & dict) {
	std::string guess;
	std::cout << "Guess a word: ";
	std::cin >> guess;
	transform(guess.begin(), guess.end(), guess.begin(), toupper);
	return (guess);
}

void	print_guesses(std::vector<Guess> const & guesses) {
	std::vector<Guess>::const_iterator it = guesses.begin();
	std::vector<Guess>::const_iterator ite = guesses.end();
	
	int i = 0;
	while (it != ite) {
		std::cout << "\t\t";
		it->show_grade();
		++it;
		++i;
	}
	while (i < 6) {
		std::cout << "\t\t_ _ _ _ _" << std::endl;
		++i;
	}
}

int	main() {
	std::set<std::string> dict;
	std::vector<Guess> guesses;
	try {
		dict = load_dict("words.txt");
		std::cout << "Dictionary Loaded (" << dict.size() << " words)" << std::endl;
	} catch (std::exception & e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}

	std::string answer = "goats";
	transform(answer.begin(), answer.end(), answer.begin(), toupper);

	int guess_count = 0;
	bool solved = false;
	while (!solved && guesses.size() < 6) {
		print_guesses(guesses);
		Guess guess = get_guess(dict);
		if (dict.count(guess.guess)) {
			solved = guess.grade_guess(answer);				
			guesses.push_back(guess);
		} else {
			std::cout << "Invalid Guess: [" << guess.guess << "]" << std::endl;
		}
	}

	print_guesses(guesses);
	if (solved)
		std::cout << GREEN << "Congratulations!" << YELLOW << " You found the word in " << GREEN << guesses.size() << YELLOW << " guess(es)" << RESET << std::endl;
	else
		std::cout << RED << "Better luck next time!" << RESET << std::endl;
	
	return (0);
}
