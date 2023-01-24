// Copyright (C) 2007 Douglas Gregor 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file contains code for the distributed adjacency list's
// message handlers. It should not be included directly by users.

#ifndef BOOST_GRAPH_DISTRIBUTED_ADJLIST_HANDLERS_HPP
#define BOOST_GRAPH_DISTRIBUTED_ADJLIST_HANDLERS_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/parallel/simple_trigger.hpp>
#include <boost/graph/parallel/detail/untracked_pair.hpp>

namespace boost { 

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
void
PBGL_DISTRIB_ADJLIST_TYPE::
setup_triggers()
{
  using boost::graph::parallel::simple_trigger;

  simple_trigger(process_group_, msg_add_vertex_with_property, this,
                 &adjacency_list::handle_add_vertex_with_property);
  simple_trigger(process_group_, msg_add_vertex_with_property_and_reply, this,
                 &adjacency_list::handle_add_vertex_with_property_and_reply);
  simple_trigger(process_group_, msg_add_edge, this, 
                 &adjacency_list::handle_add_edge);
  simple_trigger(process_group_, msg_add_edge_with_reply, this, 
                 &adjacency_list::handle_add_edge_with_reply);
  simple_trigger(process_group_, msg_add_edge_with_property, this,
                 &adjacency_list::handle_add_edge_with_property);
  simple_trigger(process_group_,  msg_add_edge_with_property_and_reply, this,
                 &adjacency_list::handle_add_edge_with_property_and_reply);
  simple_trigger(process_group_, msg_nonlocal_edge, this,
                 &adjacency_list::handle_nonlocal_edge);
  simple_trigger(process_group_, msg_remove_edge, this,
                 &adjacency_list::handle_remove_edge);
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
void 
PBGL_DISTRIB_ADJLIST_TYPE::
handle_add_vertex_with_property(int source, int tag, 
                                const vertex_property_type& data, 
                                trigger_receive_context)
{
  vertex_descriptor v(this->processor(), 
                      add_vertex(this->build_vertex_property(data), 
                                 this->base()));
  if (on_add_vertex)
    on_add_vertex(v, *this);
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
typename PBGL_DISTRIB_ADJLIST_TYPE::local_vertex_descriptor
PBGL_DISTRIB_ADJLIST_TYPE::
handle_add_vertex_with_property_and_reply(int source, int tag, 
                                          const vertex_property_type& data, 
                                          trigger_receive_context)
{
  // Try to find a vertex with this name
  local_vertex_descriptor local_v
    = add_vertex(this->build_vertex_property(data), this->base());

  vertex_descriptor v(processor(), local_v);
  if (on_add_vertex)
    on_add_vertex(v, *this);

  return local_v;
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
void 
PBGL_DISTRIB_ADJLIST_TYPE::
handle_add_edge(int source, int tag, const msg_add_edge_data& data,
                trigger_receive_context)
{
  add_edge(vertex_descriptor(processor(), data.source), 
           data.target, *this);
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
boost::parallel::detail::untracked_pair<typename PBGL_DISTRIB_ADJLIST_TYPE::edge_descriptor, bool>
PBGL_DISTRIB_ADJLIST_TYPE::
handle_add_edge_with_reply(int source, int tag, const msg_add_edge_data& data,
                           trigger_receive_context)
{
  std::pair<typename PBGL_DISTRIB_ADJLIST_TYPE::edge_descriptor, bool> p = 
    add_edge(vertex_descriptor(processor(), data.source),data.target, *this);
  return p;
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
void 
PBGL_DISTRIB_ADJLIST_TYPE::
handle_add_edge_with_property(int source, int tag, 
                              const msg_add_edge_with_property_data& data,
                              trigger_receive_context)
{
  add_edge(vertex_descriptor(processor(), data.source), 
           data.target, data.get_property(), *this);
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
boost::parallel::detail::untracked_pair<typename PBGL_DISTRIB_ADJLIST_TYPE::edge_descriptor, bool>
PBGL_DISTRIB_ADJLIST_TYPE::
handle_add_edge_with_property_and_reply
  (int source, int tag, 
   const msg_add_edge_with_property_data& data,
   trigger_receive_context)
{
  std::pair<typename PBGL_DISTRIB_ADJLIST_TYPE::edge_descriptor, bool> p = 
    add_edge(vertex_descriptor(processor(), data.source), 
                  data.target, data.get_property(), *this);
  return p;
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
void 
PBGL_DISTRIB_ADJLIST_TYPE::
handle_nonlocal_edge(int source, int tag, 
                     const msg_nonlocal_edge_data& data,
                     trigger_receive_context)
{
  add_remote_edge(data, source, directed_selector());
}

template<PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
void 
PBGL_DISTRIB_ADJLIST_TYPE::
handle_remove_edge(int source, int tag, 
                   const msg_remove_edge_data& data,
                   trigger_receive_context)
{
  remove_local_edge(data, source, directed_selector());
}

} 

#endif // BOOST_GRAPH_DISTRIBUTED_ADJLIST_HANDLERS_HPP


/* handlers.hpp
zMnmPGg9t/nfzNvNh81fmzvN/TCjRFqmWhQWgyXOMtuywrLa8rDFbdkIuvaRxWO5jO3ZwDC5uOhhQ9ib2MmgbXp2JruAzWefZN9g32M/ZnWKexTvKj5UHFecUnQrpnM43j7IreXc3OPcM9wLoGF/BR17B8bgZu4Id4L7Ambj89xljuFDeDm0wx28HubhTH4Nvx507WmQxn/n/8Lv4HfB7PUhaN0noHVf8138Bf4yL1KOVI5TTgX90yvvhBHvbpjblisfUq5TPq/coXxPeVTZpfyXklWpVU+rnle9Dpr4peob1Rr1Y+q/qd9XHwY9/Fo9RnOTZormDk0CzEFFoI1VmtWaFzWdmh9AIyu1h0AP27RfaDu032l7tBe0/aCV43W36dbqHgeN/KcuXK/WG/Rz9Mv1bv1z+imGWMMCw7uG0zA7zDDONCYb04yPwryeZlpt2mX63jTaPAPavBpGug+gzb8xT7Qss7xl6cF2bWWYFmjX6WwZ+wEbrihVvK8YUJi5R7hW7ma+DGovUWqUZcoXlK1KMdSnVLUZRu5TqnOqizB2i9Vh6onqyerfq/+o1qkt6lnq2TCf3wUj+r3q+9WPq19Wb1e/pd6l3qNuVn+kboXR50uY6X9U/6TuU4/WTNBoNbGaeM1izUpNnWYLjEYNMB61a3o04TAfT9XGapNBj3O15aDJddot2u3QKm3QEpG6aN00nRIsuXhdCszU
*/