#include "format_guard.hpp"

#include <istream>

src::FormatGuard::FormatGuard(std::basic_ios< char >& stream):
  stream_(stream),
  fill_(stream.fill()),
  precision_(stream.precision()),
  width_(stream.width()),
  flags_(stream.flags())
{}

src::FormatGuard::~FormatGuard()
{
  stream_.fill(fill_);
  stream_.precision(precision_);
  stream_.width(width_);
  stream_.flags(flags_);
}

std::istream& src::operator>>(std::istream& in, Demand&& value)
{
	std::istream::sentry sentry(in);
	if (!sentry)
	{
		return in;
	}

	char c = '\0';
	if (!(in >> c) || (c != value.expected))
	{
		in.setstate(std::ios::failbit);
	}
	return in;
}
