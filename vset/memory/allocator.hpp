#ifndef MANAGED_ALLOCATOR_HPP
#define MANAGED_ALLOCATOR_HPP

#include <limits>
#include <cassert>

namespace vset { namespace memory{

// TODO: привести к спецификации c++11
template<typename Memory >
struct allocator
{
  typedef Memory memory_type;
  typedef typename memory_type::value_type value_type;
  typedef typename memory_type::pointer pointer;
  typedef typename memory_type::const_pointer const_pointer;
  
  typedef typename memory_type::reference       reference;
  typedef typename memory_type::const_reference const_reference;
  typedef typename memory_type::size_type size_type;
  typedef typename memory_type::difference_type difference_type;

  allocator()
    : _memory()
  {
  }
  
  allocator(const memory_type& m)
    : _memory(m)
  {
  }

  template <typename U>
  struct rebind {
    typedef std::allocator<U> other;
  };

  pointer address(reference value ) const
  {
    return static_cast<char*>(&value) - _memory.data();
  }

  const_pointer address (const_reference value) const
  {
    return static_cast<char*>(&value) - _memory.data();
  }
  
  size_type max_size () const
  {
    return 1;
  }

  pointer allocate (size_type num, void *  hint = 0)
  {
    return _memory.allocate(num, hint);
  }

  void construct (pointer p, const_reference value)
  {
    *p = value;
  }

  void destroy (pointer p)
  {
    p->~T();
  }

  void deallocate (pointer p, size_type num)
  {
    _memory.deallocate(p, num);
  }

  const memory_type memory() const
  {
    return _memory;
  }

  memory_type memory()
  {
    return _memory;
  }
  
private:
  memory_type _memory;
};

}}

#endif
