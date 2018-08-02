#include "hitlist.hpp"
#include "hitlist/compare.hpp"
#include <utility>
#include <iostream>
#include <list>
#include <set>

hitlist h;

typedef std::list<std::string> arg_list;

namespace{
  
const std::string generate_file = "generate.txt";

template<typename T>
T extract_param( arg_list& args )
{
  if ( args.empty() )
    return T();
  long value = std::atol(args.front().c_str() );
  args.pop_front();
  return static_cast<T>(value);
}

void help()
{
  
}

void generate( arg_list& arg)
{
  int hits_total = extract_param<int>(arg);
  int users = extract_param<int>(arg);
  int interval = extract_param<int>(arg);
  std::set<hit, cmp_by_src> hits;
  
  while( hits.size() <  static_cast<size_t>(hits_total) )
  {
    hits.insert( hit::make( 
      static_cast<uint32_t>(rand()%users), 
      static_cast<uint32_t>(rand()%users), 
      static_cast<time_t>(rand()%interval)
    ));
  }
}

void initialize()
{
  
}


}
int main(int argc, char* argv[])
{
  arg_list argl(argv + 1, argv + argc);
  while ( !argl.empty() )
  {
    std::string name = argl.front();
    argl.pop_front();
    if ( name == "help" )
    {
      
    }
    else if (name == "generate")
    {
      generate(argl);
      
    }
    else if (name == "initialize")
    {
      
    }
  }
  return 1;
}
