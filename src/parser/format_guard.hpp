#ifndef FORMAT_GUARD_HPP
#define FORMAT_GUARD_HPP

#include <ios>

namespace src
{
	class FormatGuard
	{
	public:
		FormatGuard(std::basic_ios< char >& stream);
		~FormatGuard();
	private:
		std::basic_ios< char >& stream_;
		char fill_;
		std::streamsize precision_;
		std::streamsize width_;
		std::basic_ios< char >::fmtflags flags_;
	};

	struct Demand
	{
		char expected = '\0';
	};
	std::istream& operator>>(std::istream& in, Demand&& value);
}

#endif
