//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef VSET_VSET_BUFFER_PERSISTENT_FILE_AD_WRITE_FILE_HPP
#define VSET_VSET_BUFFER_PERSISTENT_FILE_AD_WRITE_FILE_HPP

#include <vset/buffer/tags.hpp>
#include <vset/buffer/persistent/tags.hpp>

#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include <errno.h>

namespace vset { namespace buffer { namespace persistent{ namespace file{

struct ad_write_file
{
  template<typename T>
  void operator()( T& t, const char* data, size_t size, size_t offset )
  {
    if ( -1 == ::pwrite( t.get_aspect().template get<_descriptor_>(), data, size, offset) )
    {
      throw std::runtime_error(strerror(errno));
    }
  }
};

}}}}

#endif
