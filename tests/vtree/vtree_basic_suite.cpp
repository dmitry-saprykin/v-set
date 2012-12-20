//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/testing.hpp>
#include <vset/vtree/vtree.hpp>
#include <vset/vtree/aspect/aspect.hpp>

UNIT(vtree_create_filesync, "")
{
  using namespace fas::testing;
  using namespace vset;

  typedef vtree::vtree< vtree::aspect<char, std::less<char>, 3> > int_vtree;
  int_vtree tree;
  tree.get_allocator().memory().buffer().open("vtree.bin");
  
  int_vtree::iterator lower = tree.lower_bound('B');
  int_vtree::iterator upper = tree.upper_bound('B');
  std::cout<< std::endl;
  std::cout<< "[";
  for ( ; lower!=upper; ++lower, std::cout << ",")
    std::cout<< *lower;
  std::cout<< "]" << std::endl;

  
  for (int i = 0; i < 5 ; ++i)
    tree.insert('A'+i%10);
  

  std::cout<< std::endl;
  int_vtree::iterator itr = tree.begin();
  for (; itr != tree.end(); ++itr)
    std::cout<< *itr << " ";
  std::cout<< std::endl;

  tree.get_allocator().memory().buffer().sync();
  t << message("tree size: ") << tree.get_container().size();
  tree.get_allocator().memory().buffer().close();
  t << nothing();
}

BEGIN_SUITE(vtree_basic_suite, "")
  ADD_UNIT(vtree_create_filesync)
END_SUITE(vtree_basic_suite)
