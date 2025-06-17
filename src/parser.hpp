#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <limits>
#include <string>

#include "map.hpp"
#include "set.hpp"
#include "dict.hpp"

namespace src
{
  struct Context
  {
    using dict_type = Dictionary;
    std::istream& input;
    std::ostream& output;
    std::ostream& error;
	  dict_type& dict;
    bool eol();
  };
  template< class Processor >
  class Parser
  {
  public:
    using processor = Processor;
    using call_signature = bool(processor::*)(Context&);
    using num_call_signature = bool(processor::*)(Context&, size_t);
    using map_type = src::Map< std::string, call_signature >;

    Context context;

    template< class P = processor, class M = map_type >
    Parser(P&& proc, Context context, M&& comands):
      context(context),
      proccessor_(std::forward< P >(proc)),
      comands_(std::forward< M >(comands)),
      needNumCall_(false)
    {}
    bool run()
    {
      if (needNumCall_)
      {
        size_t num = 0;
        if ((((context.input >> std::ws).peek() != '-') && (context.input >> num)))
        {
          if (!(proccessor_.*numCall_)(context, num))
          {
            parseAsError();
          }
          return context.input.good();
        }
        context.input.clear(context.input.rdstate() & ~std::ios::failbit);
      }
      std::string command;
      if (context.input >> command)
      {
        typename map_type::iterator current = comands_.find(command);
        if (current != comands_.end())
        {
          if ((proccessor_.*(current->second))(context))
          {
            return context.input.good();
          }
        }
        parseAsError();
      }
      return context.input.good();
    }
    bool regiserNumCall(num_call_signature numCall)
    {
      if (!needNumCall_)
      {
        needNumCall_ = true;
        numCall_ = numCall;
        return true;
      }
      return false;
    }
    void parseAsError()
    {
      context.input.clear(context.input.rdstate() & ~std::ios::failbit);
      context.input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      context.output << "<INVALID COMMAND\\FORMAT>\n";
    }
  private:
    processor proccessor_;
    map_type comands_;
    bool needNumCall_;
    num_call_signature numCall_;
  };
}

#endif
