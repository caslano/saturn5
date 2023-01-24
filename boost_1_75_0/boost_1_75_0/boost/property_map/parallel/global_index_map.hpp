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
xChTTwUi3SxxP+RHnc/EmpcK17DucT8IkW1KaFI4nuSJaYUA2RWcTFEdbM9WJEI+FkPoJRQhX1LWJ8A2zogLQDjeQsrkwMCPsnmjTuYOCUWlMlu/bIyhVycKCpoJcv5ScjvZHY2s0xDNSLTRg9CkfALS0TcKzJwz/OGqpiqjSz2jp/ojMBknO1B6Z1cwg01hWhxYpzadK0Aj/4Ljadrsm1Z2RM34Opv2Z6YS/PMiP7uYgaJpMTM/Gr3lj+rx/YHU91SOv7D22OhPco2/Tzxya/EyS9Bih9FsvyPodurWl9Nz9EX/BRcs6NN6YH8QFwRbbrsQ5XHJtWClq+hOpasodzb3amrg7z4klgLVVIYqyfOgjQxwMQR4L7h3AOvpBr+7PnN7flQ0P5k0P9mbZiE+lJjqDzWp/sN3qHMlJhYYVD/9ulH1kyuj+r4GFU+UON4ggJCtCPYTskXc29nQwE/1RwdXXvWn1+DC9qgVhW1+FBe2l6N08yMqofoDo7iw9YhSVf90EAlbgxrlq34yV/3T9c2q3/aaUfWbXWOqn8yAab1BU/00+cetiurnXa206j9Zv+IBMVf9AKh08vds7uaezV31/VT/suXWqv9nNY7GvmCa/9dAN/+vvm4ArBKqX1xfN/+vvqr6E5gz46lWgeoPt5tV/4srRtV/9wpT/WTW7MvXGZU7GVU/GfdTew5UP/pbpcsnrtSme4cFzX79
*/