//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/testing.hpp>
#include <vset/memory/manager.hpp>
#include <vset/memory/provider.hpp>
#include <vset/memory/allocator.hpp>
#include <vset/memory/fsb/aspect.hpp>
#include <vset/buffer/persistent/filesync/aspect.hpp>

#define MAX_TEST 777 

const size_t CAPACITY = (777/64)*64 + (777%64!=0)*64;

typedef char value_type;

template<typename T, typename Alloc>
void test_char_init(T& t, Alloc& allocator)
{
  using namespace fas::testing;
  typedef typename Alloc::pointer pointer;

  for (int i=0; i < MAX_TEST; ++i)
  {
    value_type* ch = allocator.allocate(1);
    t << is_true<assert>( ch != 0 ) << "i=" << i << " " << FAS_TESTING_FILE_LINE;
    t << stop;
    *ch = '0' + i%10;
  }

  pointer beg = allocator.begin();
  pointer end = allocator.end();

  int i=0;
  for ( ; beg != end; ++beg, ++i)
  {
    t << equal< assert, value_type > ( *beg, '0' + i%10 ) << char(*beg) << "!=" << char('0' + i%10) << " " << FAS_TESTING_FILE_LINE;
  }
}

template<typename T, typename Alloc>
void test_char_test(T& t, const Alloc& allocator)
{
  using namespace fas::testing;
  typedef typename Alloc::const_pointer const_pointer;
  const_pointer beg = allocator.begin();
  const_pointer end = allocator.end();
  int i=0;
  for ( ; beg != end; ++beg, ++i)
  {
    t << equal< assert, value_type > ( *beg, '0' + i%10 ) << char(*beg) << "!=" << char('0' + i%10) << " " << FAS_TESTING_FILE_LINE;
  }
  t << equal< assert, int > ( i, MAX_TEST) << i << "!=" << MAX_TEST << " " << FAS_TESTING_FILE_LINE;

  t << equal< assert, int > ( i, allocator.count() ) << FAS_TESTING_FILE_LINE;
  t << equal< assert, int > ( CAPACITY, allocator.capacity() ) << FAS_TESTING_FILE_LINE;

  beg = allocator.begin();
  const_pointer beg1 = beg;
  ++beg1;
  --beg1;
  
  t << equal< assert > ( beg, beg1 ) << FAS_TESTING_FILE_LINE;
  t << equal< assert > ( *beg, *beg1 ) << FAS_TESTING_FILE_LINE;
  
  i = MAX_TEST - 1;
  beg = allocator.begin();
  end = allocator.end();
  
  for ( --end; beg!=end;--end, --i)
  {
    if ( i < 0 )
    {
      t << is_true< assert>(false, "Iterator is out of range!!!");
      break;
    }

    t << equal< assert, value_type > ( *end, '0' + i%10 ) << char(*end) << "!=" << char('0' + i%10) << " " << FAS_TESTING_FILE_LINE;
  }
}

UNIT(test_unit, "")
{
  using namespace fas::testing;
  typedef vset::memory::manager< vset::memory::strategy::fsb_mmap<char> > allocator_type;
  
  allocator_type allocator;
  allocator.buffer().open("allocator.bin");
  allocator.buffer().truncate(0);

  test_char_init(t, allocator);
  test_char_test(t, allocator);

  allocator.buffer().sync();
  allocator.buffer().close();
  allocator.buffer().open("allocator.bin");

  test_char_test(t, allocator);

  allocator_type allocator2;
  allocator2.buffer().open("allocator.bin");

  test_char_test(t, allocator);

  allocator2.buffer().close();
  allocator.buffer().close();

  t << nothing();
}

UNIT(test_allocator, "")
{
  using namespace fas::testing;
  using namespace vset;

  typedef memory::manager< vset::memory::strategy::fsb_mmap<char> > manager;
  typedef memory::allocator< memory::provider< manager > > allocator;

  manager m;
  allocator a(&m);
  a.memory().buffer().open("allocator2.bin");
  a.memory().buffer().clear();
  *(a.allocate(1))='X';
  a.memory().buffer().sync();
  a.memory().buffer().close();
  t << nothing();
}

BEGIN_SUITE(basic_suite, "")
  ADD_UNIT(test_unit)
  ADD_UNIT(test_allocator)
END_SUITE(basic_suite)
