// Copyright 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_PARALLEL_GLOBAL_INDEX_MAP_HPP
#define BOOST_PARALLEL_GLOBAL_INDEX_MAP_HPP

#include <boost/property_map/property_map.hpp>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace boost { namespace parallel {

template<typename IndexMap, typename GlobalMap>
class global_index_map
{
public:
  typedef typename property_traits<IndexMap>::key_type key_type;
  typedef typename property_traits<IndexMap>::value_type value_type;
  typedef value_type reference;
  typedef readable_property_map_tag category;

  template<typename ProcessGroup>
  global_index_map(ProcessGroup pg, value_type num_local_indices, 
                   IndexMap index_map, GlobalMap global)
    : index_map(index_map), global(global)
  {
    typedef typename ProcessGroup::process_id_type process_id_type;
    starting_index.reset(new std::vector<value_type>(num_processes(pg) + 1));
    send(pg, 0, 0, num_local_indices);
    synchronize(pg);
    
    // Populate starting_index in all processes
    if (process_id(pg) == 0) {
      (*starting_index)[0] = 0;
      for (process_id_type src = 0; src < num_processes(pg); ++src) {
        value_type n;
        receive(pg, src, 0, n);
        (*starting_index)[src + 1] = (*starting_index)[src] + n;
      }
      for (process_id_type dest = 1; dest < num_processes(pg); ++dest)
        send(pg, dest, 1, &starting_index->front(), num_processes(pg));
      synchronize(pg);
    } else {
      synchronize(pg);
      receive(pg, 0, 1, &starting_index->front(), num_processes(pg));
    }
  }

  friend inline value_type 
  get(const global_index_map& gim, const key_type& x)
  {
    using boost::get;
    return (*gim.starting_index)[get(gim.global, x).first]
           + get(gim.index_map, x);
  }

private:
  shared_ptr<std::vector<value_type> > starting_index;
  IndexMap index_map;
  GlobalMap global;
};

} } // end namespace boost::parallel

#endif // BOOST_PARALLEL_GLOBAL_INDEX_MAP_HPP

/* global_index_map.hpp
BZADCXxU2Qu/rLQp9tNFR/JHFZ6kslqCuQPMxQv0KTI9/TJb7iFVQ0fjY/gGHKbd8+64NX755dL2Oi1o96Rgozcf5VImV/ZZ3W3YN9Ha+iB791uBk46nru43pk2ZqQYTr3xCvsmgDry/sxDT1OqAovkqYCsmQDxzvUII8Th7Btu/HvwPqCjYN/xIBHMOS4FNnPoT480ILC169hIlII1r9n9U/GqrP4oI+5y3ulvnhFWHfn5poePkOnm/HhQcsUoz+rj1677RKd5Ky3fkMjT9OV131uwxM4iQjw461i/z9T/x1zHw9A4j9QZ+333/8kB3FORBdZYAwjiA45LkgXKKC6G+Vd9EJTZhNfwlha9KTSW5VM9FpXjlBD8bxVI748nRI2Os8YS69DLhzbvbKkON+bwhpfTu1TPIhUUdgnU7+hTjNTqZQxD9vraXM2g3VAM2TEOwTiufwfr5AWthhUUr0ITFYNkme7Mh0pZiarH996pOKGVla6xd8WxXIl2WFE1aXCdmOC76EJ/0MODKb6XCF1saV6brtIxfUl7D7k4nx8Ihb9eVOV44w78wbw==
*/