#include <vset/vtree/vtree.hpp>
#include <vset/vtree/strategy.hpp>
#include <stx/btree_multimap.h>
#include <fas/xtime.hpp>
#include <iostream>

#include <vset/multiset.hpp>
#include <vset/allocators/allocator.hpp>
#include <fas/xtime.hpp>
#include <iostream>

#include "config.hpp"
using namespace vset;

template <int _innerslots, int _leafslots>
struct btree_traits_speed
{
  static const bool selfverify = false;
  static const bool debug = false;
  static const int leafslots = _innerslots;
  static const int innerslots = _leafslots;
};

struct ad_container
{
  template<typename K, typename V, typename C>
  struct apply
  {
    typedef stx::btree_multimap<K, V, C, struct btree_traits_speed<8, 512> > type;
  };
};

struct aspect: fas::aspect< fas::type_list_n<
  fas::advice< vset::vtree::_container_, ad_container >,
  vtree::strategy::vtree_fsb_inmem<int, std::less<int>, 512>
>::type >{};

typedef vtree::vtree< aspect > storage_type;

int main()
{
  storage_type stg;

  fas::nanospan minspan(fas::nanospan::xmax, fas::nanospan::xmax);
  fas::nanospan start = fas::process_nanotime();
  for (int i = 0; i < MAX_COUNT; ++i)
  {
    stg.insert( rand() );
  }
  fas::nanospan finish = fas::process_nanotime();

  std::cout << "init time: " << (finish - start).to_double() << std::endl;
  std::cout << "init rate: " << fas::rate(finish - start)*MAX_COUNT << std::endl;

  start = fas::process_nanotime();
  fas::nanospan start2 = start;
  for (int i=0; i < MAX_COUNT; ++i)
  {
    stg.find( rand() );
    if ( i % MIN_COUNT == 0)
    {
      finish = fas::process_nanotime();
      fas::nanospan tmp = finish - start2;
      if (i != 0 && tmp < minspan)
      {
        minspan = tmp;
      }

      if ( SHOW_PROCESS )
      {
        std::cout << "find time (" << i << "):" << (finish - start).to_double() << std::endl;
        std::cout << "find rate (" << i << "):" <<fas::rate(finish - start)*MAX_COUNT << std::endl;
        std::cout << "find time (" << MIN_COUNT << "):" << (tmp).to_double() << std::endl;
        std::cout << "find rate (" << MIN_COUNT << "):" <<fas::rate(tmp)*MAX_COUNT << std::endl;
      }
      start2 = fas::process_nanotime();
    }

  }
  finish = fas::process_nanotime();

  std::cout << "---------------------------------" << std::endl;
  std::cout << "final find time (" << MAX_COUNT << "):" << (finish - start).to_double() << std::endl;
  std::cout << "final find rate (" << MAX_COUNT << "):" <<fas::rate(finish - start)*MAX_COUNT << std::endl;
  std::cout << "min find time (" << MIN_COUNT << "):" << (minspan).to_double() << std::endl;
  std::cout << "min find rate (" << MIN_COUNT << "):" <<fas::rate(minspan)*MIN_COUNT << std::endl;
  std::cout << "DONE" << std::endl;

  std::cin.get();
  return 0;
}
