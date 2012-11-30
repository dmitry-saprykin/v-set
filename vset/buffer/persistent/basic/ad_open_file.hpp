//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef VSET_VSET_BUFFER_PERSISTENT_BASIC_AD_OPEN_FILE_HPP
#define VSET_VSET_BUFFER_PERSISTENT_BASIC_AD_OPEN_FILE_HPP

#include <vset/buffer/tags.hpp>
#include <vset/buffer/persistent/tags.hpp>

#include <fcntl.h>

namespace vset { namespace buffer { namespace persistent{

struct ad_open_file
{
  template<typename T>
  void operator()( T& t )
  {
    if ( t.get_aspect().template get<_descriptor_>() != -1 )
      t.get_aspect().template get<_close_file_>();

    t.get_aspect().template get<_descriptor_>() =
      ::open( t.get_aspect().template get<_file_name_>().c_str(), O_RDWR /*| O_APPEND*/ | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
  }
};

}}}

#endif
