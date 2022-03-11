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