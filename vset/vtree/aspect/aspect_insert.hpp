//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef VSET_VTREE_ASPECT_ASPECT_INSERT_HPP
#define VSET_VTREE_ASPECT_ASPECT_INSERT_HPP

#include <vset/vtree/aspect/tags.hpp>
#include <vset/vtree/aspect/ad_node_for_insert.hpp>
#include <vset/vtree/aspect/ad_multimap_insert.hpp>
#include <vset/vtree/aspect/ad_create_node.hpp>
#include <vset/vtree/aspect/ad_lower_node.hpp>
#include <vset/vtree/aspect/ad_upper_node.hpp>
#include <vset/vtree/aspect/ad_split_node.hpp>
#include <vset/vtree/aspect/ad_insert_value.hpp>
#include <vset/vtree/aspect/ad_update_node_key.hpp>
#include <vset/vtree/aspect/ad_first_proper_node.hpp>

#include <vset/vtree/aspect/ad_lower_bound.hpp>
#include <vset/vtree/aspect/ad_upper_bound.hpp>


namespace vset{ namespace vtree{

struct aspect_insert: fas::aspect< fas::type_list_n<
  fas::advice< _node_for_insert_, ad_node_for_insert>,
  fas::advice< _insert_to_container_, ad_multimap_insert>,
  fas::advice< _create_node_, ad_create_node>,
  fas::advice< _lower_node_, ad_lower_node>,
  fas::advice< _upper_node_, ad_upper_node>,
  fas::advice< _split_node_, ad_split_node>,
  fas::advice< _insert_value_, ad_insert_value>,
  fas::advice< _update_node_key_, ad_update_node_key>,
  fas::advice< _first_proper_node_, ad_first_proper_node>,
  fas::advice< _lower_bound_, ad_lower_bound>,
  fas::advice< _upper_bound_, ad_upper_bound>
>::type > {};

}}

#endif
