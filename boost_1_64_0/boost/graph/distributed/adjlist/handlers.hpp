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
m+MOaRs3VzzdM71c77qNDdguz6aeLVhaPp9rweHe5ZRj9nsG/zbewXzEO5gU3sGE12ttlPiPVYjo9/LzR+dKEw7b4H1R+osMmuZq5pyV1/JwvB+lblPrnLmuwuTwurNZEmdORS9x9s+Q/sCMP70yPsuOr6B+jJM1IMh2STm9U1GvldPXWa5MCpa9Zy17f2DpT+kGK+l6WyN96RLuwHW50ztULm6yvPPkeLhf1faGOaQ2ybm+qphh7qEXTs0rytU3Uvv+4pfyrBl+vtbvxfo53MzS262W0j+eob5gR9jWjiSJuyFh9krcL1UMr9/x6PU7vfU9atMWOXeam2tyluMSp4ob65rire/Y4GttfZVU1VHBv1kd9LPXcaCFGhzorDYHklnXkMjzRh01ILW1tTqthtqbRp+px+1XSpoe8NZVM7xlou5l5F+P3e8XnTgVvNYm6+twitTbaJdbDXGJvMQ1uMDqnhJen/OT5GlNxPO+9Ox6cGGvvyov9TBA+3kbJuUeKptdHK8kbeISKZuU0Hqg4slFofrdp8cBCzP1vZ5XZ1PzJptrpI1cz02Mbffb5b5QR9XQbX+7pHF3xb94KqjvEx5XVyTy9dq3Vz2RFKfeTXo/ufTzv0Oe/0mbxD9J0tag4mnWOZlnGqc8I3mtFKzRPasczElMN3sU22NEGSLq+yrzVKWtv+DAVjJvyVPpzys4+jry1AOONDMWKJS87MDs3Tb9LpdvelJn6U6n2uB40DFUddB2n9dKPn+smMLY5hATVX/EJQecqn6qWzVL7ayu57n0LtwrvC04mO5R7ZiEuBDDeTdnHnT1lrgj3yfk8D6hrvsffZeQIWkKxzcqdaG1Kn5CQkX36daDvRUsUSnjuvJsVVWVfDcp++CasbV1rzyPcpZByQuSv3aWeC6VOGeid4f4T1Sw38kUF0beF9Kfie5bWz1j9wVHOD5EwreP6J+nTR85IX9U5BrFURImyx7fi7+mytTxnEBnnMTTOLL9FOVPzSseX1hg2s9Q6ddvpfeszdySqsxN9uo9obFnLP3rD1awRe2gnTitJLXNaqBa6rWYg6U9fOTdTpjjDlYIubzqO3eCVZkVcQNxt/Bu/muY4jmmkhLy1a0JPom7kLBP3yXtq+J+ro2NCR7eyF1n7Us8EgivXf1Y0pUnay6rqTo6TeFr5Xn66EPB7wmcr7XqF5dj1k7fu4vjzMAMMNszQ84VDmO509TFjrWOXg65HwTtRUr5VKAPKV331Lwp6z2b0CMlvfW18YHku563OqvJ73Zscex2V1KTGNstiqugduH85LtBfLzqHl+fb7W56gLy+JgnXr2JQemyCfGqbcIi5fSml3qvod816/cav1CiLqu69Yol7YrUrRa9n+WeKPtFht7nS3+VodP2gtwfhnjOYk1qP545ztLX7p1SBt+mJaqj7ri4d+K/5Rk2x79QbfHfZPVLqeq4KM2prmAMtT6tnHqD3xml7i8VHdxT9Lg4+j1QI/pquhn5myjyjamJaoBrgquF+/6Eao7PEne47vU3s44GxqjhKbWsa1PLUp+EQZM/c78mLmIsSkpJ3u6qRJ77mr5/OmOtW7mON1gXJ/a2jvhWW7HWZWYSZTUppwsj3onKoMrUZwd97YTLf2jE9XeM43kSvmVFu+8vkI4/8nvVK/eF+vqWv/vb2A1Wyfcc9nMJL33k9mWnsdaj9nOI7PWvn+urICujzzlBZD4V9Uw3WV4Ime9oi7ROxJpysw79cunjXyN85LhpdeI29aTXa54tZpo03fa4vt9xbHJovGv2+BjE8Tfk+Gzzfu568W9mT4PlVsR9tFRZrhe9iSXGNBecdkxj13uxvMiWePS71JslntY=
*/