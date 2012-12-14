//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef VSET_VSET_BUFFER_PERSISTENT_BASIC_AD_FILE_SIZE_HPP
#define VSET_VSET_BUFFER_PERSISTENT_BASIC_AD_FILE_SIZE_HPP

#include <vset/buffer/tags.hpp>
#include <vset/buffer/persistent/tags.hpp>
#include <sys/stat.h>
#include <string.h>
#include <stdexcept>
#include <errno.h>


namespace vset { namespace buffer { namespace persistent{

struct ad_file_size
{
  template<typename T>
  size_t operator()( T& t )
  {
    struct stat sb;
    memset(&sb, 0, sizeof(sb));

    if ( -1 == stat( t.get_aspect().template get<_file_name_>().c_str(), &sb) )
      throw std::domain_error(strerror(errno));
    std::cout << "ad_file_size: " << sb.st_size << " name:" << t.get_aspect().template get<_file_name_>() << std::endl;
    return sb.st_size;
  }
};

}}}

#endif
