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
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
*/