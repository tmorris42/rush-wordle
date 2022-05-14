#include "guess.hpp"

Guess::Guess(): guess(), _grade() {}

Guess::Guess(std::string const & guess): guess(guess), _grade(guess.size()) {}

Guess::Guess(Guess const & src) {
	*this = src;
}

Guess & Guess::operator=(Guess const & rhs) {
	if (this != &rhs) {
		this->guess = rhs.guess;
		this->_grade = rhs._grade;
	}
	return (*this);
}

Guess::~Guess() {}

void	Guess::show_grade() const {
	std::string::const_iterator guess_it = this->guess.begin();
	std::vector<int>::const_iterator grade_it = this->_grade.begin();

	std::map<int, std::string> colors;
	colors[CORRECT] = GREEN;
	colors[PRESENT] = YELLOW;
	colors[INCORRECT] = RESET;

	while (guess_it != this->guess.end() && grade_it != this->_grade.end()) {
		std::cout << colors[*grade_it] << *guess_it << " ";
		++guess_it;
		++grade_it;
	}
	std::cout << RESET << std::endl;
}

bool	Guess::grade_guess(std::string const & answer) {
	std::map<char, int> letters;
	std::vector<int> grade(answer.size());
	bool solved = true;

	if (answer.size() != this->guess.size())
		throw std::invalid_argument("Guess is not the right length");

	for (int i = 0; i < answer.size(); ++i) {
		if (letters.count(answer[i]))
			letters[answer[i]] += 1;
		else
			letters[answer[i]] = 1;
	}

	for (int i = 0; i < answer.length(); ++i) {
		if (this->guess[i] == answer[i]) {
			grade[i] = CORRECT;
			letters[this->guess[i]] -= 1;
		} else {
			solved = false;
		}
	}

	for (int i = 0; i < answer.length(); ++i) {
		if (grade[i] == 0 && letters[this->guess[i]] > 0) {
			grade[i] = PRESENT;
			letters[this->guess[i]] -= 1;
		}
	}

	if (grade.size() != this->guess.size())
		throw new std::runtime_error("Grading failed");

	this->_grade = grade;
	return (solved);
}

