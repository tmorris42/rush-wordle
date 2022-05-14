#ifndef GUESS_HPP
# define GUESS_HPP

# include <string>
# include <vector>
# include <map>
# include <iostream>

# include "constants.hpp"

class Guess {
	public:
	std::string guess;

	Guess();
	Guess(std::string const & guess);
	Guess(Guess const & src);
	Guess & operator=(Guess const & rhs);
	~Guess();

	void	show_grade(void) const;
	bool	grade_guess(std::string const & answer);

	private:
	std::vector<int>	_grade;
};

#endif
