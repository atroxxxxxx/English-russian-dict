#include "parser.hpp"

#include <iostream>

bool src::Context::eol()
{
  while (input.peek() != '\n')
  {
    wchar_t c = '\0';
    input.get(c);
    if (!std::isspace(c))
    {
      return false;
    }
  }
  return true;
}
