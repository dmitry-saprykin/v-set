//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef VSET_VSET_MEMORY_FSB_OFFSET_PROVIDER_HPP
#define VSET_VSET_MEMORY_FSB_OFFSET_PROVIDER_HPP

#include <vset/memory/fsb/tags.hpp>
#include <cassert>
#include <stdexcept>

namespace vset { namespace memory{ namespace fsb{

template<typename T>
class offset_provider
{
public:

  typedef typename T::aspect::template advice_cast<_value_type_>::type value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  
  offset_provider()
    : _offset(0)
  {}
  
  offset_provider(T* offset)
    : _offset(offset)
  {}

  const value_type* get(size_t offset) const
  {
    assert(_offset!=0);
    return _offset->get_aspect().template get<_get_by_offset_>()(*_offset, offset);
  }

  value_type* get(size_t offset)
  {
    assert(_offset!=0);
    return _offset->get_aspect().template get<_get_by_offset_>()(*_offset, offset);
  }

  size_t offset(value_type* p) const
  {
    assert(_offset!=0);
    return _offset->get_aspect().template get<_offset_by_ptr_>()(*_offset, p);
  }

  size_t next(size_t offset, size_t count = 1) const
  {
    assert(_offset!=0);
    return _offset->get_aspect().template get<_next_offset_>()(*_offset, offset, count);
  }

  size_t pred(size_t offset, size_t count = 1) const
  {
    assert(_offset!=0);
    throw std::domain_error("offset_provider::pred not impl");
  }

  bool operator == (const offset_provider<T> right) const
  {
    return _offset==right._offset;
  }

private:
  T *_offset;
};


}}}

#endif
