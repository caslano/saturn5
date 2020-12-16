// Copyright (C) 2004-2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_PARALLEL_GRAPHVIZ_HPP
#define BOOST_GRAPH_PARALLEL_GRAPHVIZ_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/distributed/concepts.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_same.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <boost/graph/parallel/container_traits.hpp>
#include <boost/graph/parallel/process_group.hpp>
#include <boost/property_map/parallel/global_index_map.hpp>

namespace boost {

template<typename Graph>
struct graph_id_writer
{
  explicit graph_id_writer(const Graph& g) : g(g) { }

  void operator()(std::ostream& out)
  {
    out << "    label=\"p" << process_id(g.process_group()) << "\";\n";
  }

 private:
  const Graph& g;
};

template<typename NumberMap>
struct paint_by_number_writer
{
  explicit paint_by_number_writer(NumberMap number) : number(number) { }

  template<typename Descriptor>
  void operator()(std::ostream& out, Descriptor k)
  {
    static const char* color_names[] = {
      "blue",
      "brown",
      "cyan",
      "darkgreen",
      "darkorchid",
      "darksalmon",
      "darkviolet",
      "deeppink",
      "gold3",
      "green",
      "magenta",
      "navy",
      "red",
      "yellow",
      "palegreen",
      "gray65",
      "gray21",
      "bisque2",
      "greenyellow",
      "indianred4",
      "lightblue2",
      "mediumspringgreen",
      "orangered",
      "orange"
    };
    const int colors = sizeof(color_names) / sizeof(color_names[0]);
    if (get(number, k) < colors) {
      out << " [ style=\"filled\", fillcolor=\"" << color_names[get(number, k)]
          << "\" ]";
    } else {
      out << " [ label=\"(" << get(number, k) << ")\" ]";
    }
  }

 private:
  NumberMap number;
};

template<typename NumberMap>
inline paint_by_number_writer<NumberMap>
paint_by_number(NumberMap number)
{ return paint_by_number_writer<NumberMap>(number); }

template<typename Graph, typename VertexPropertiesWriter, 
         typename EdgePropertiesWriter, typename GraphPropertiesWriter>
void 
write_graphviz(std::ostream& out,
               const Graph& g, 
               VertexPropertiesWriter vpw,
               EdgePropertiesWriter epw,
               GraphPropertiesWriter gpw
               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  typedef typename graph_traits<Graph>::directed_category directed_category;
  typedef typename boost::graph::parallel::process_group_type<Graph>::type 
    process_group_type;
  typedef typename property_map<Graph, vertex_index_t>::const_type
    VertexIndexMap;
  typedef typename property_map<Graph, vertex_global_t>::const_type
    VertexGlobalMap;

  static const bool is_undirected
    = (is_base_and_derived<undirected_tag, directed_category>::value
       || is_same<undirected_tag, directed_category>::value);
  static const char* graph_kind = is_undirected? "graph" : "digraph";
  static const char* edge_kind = is_undirected? "--" : "->";

  using boost::graph::parallel::process_group;
  process_group_type pg = process_group(g);

  parallel::global_index_map<VertexIndexMap, VertexGlobalMap> 
    global_index(pg, num_vertices(g), get(vertex_index, g),
                 get(vertex_global, g));

  std::ostringstream local_graph_out;

  local_graph_out << "  subgraph cluster_" << process_id(pg) << " {\n";
  gpw(local_graph_out);

  typename graph_traits<Graph>::vertex_iterator vi, vi_end;
  for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {

    int global_idx = get(global_index, *vi);
    local_graph_out << "    n" << global_idx;
    vpw(local_graph_out, *vi);
    local_graph_out << ";\n";
  }
  local_graph_out << "  }\n\n";

  
  typename graph_traits<Graph>::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    int source_idx = get(global_index, source(*ei, g));
    int target_idx = get(global_index, target(*ei, g));
    local_graph_out << "  n" << source_idx << " " << edge_kind << " n" 
                    << target_idx;
    epw(local_graph_out, *ei);
    local_graph_out << ";\n";
  }

  if (process_id(pg) == 0) {
    out << graph_kind << " g {\n";
    out << local_graph_out.str();

    synchronize(pg);
    for (int i = 1; i < num_processes(pg); ++i) {
      int len;
      receive(pg, i, 0, len);
      char* data = new char [len+1];
      data[len] = 0;
      receive(pg, i, 1, data, len);
      out << std::endl << data;
      delete [] data;
    }
    out << "}\n";
  } else {
    std::string result_str = local_graph_out.str();
    const char* data = result_str.c_str();

    int len = result_str.length();
    send(pg, 0, 0, len);
    send(pg, 0, 1, data, len);
    synchronize(pg);
  }
  synchronize(pg);
  synchronize(pg);
  synchronize(pg);
}

template<typename Graph, typename VertexPropertiesWriter, 
         typename EdgePropertiesWriter>
inline void 
write_graphviz(std::ostream& out,
               const Graph& g, 
               VertexPropertiesWriter vpw,
               EdgePropertiesWriter epw
               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  write_graphviz(out, g, vpw, epw, graph_id_writer<Graph>(g));
}

template<typename Graph, typename VertexPropertiesWriter>
inline void 
write_graphviz(std::ostream& out,
               const Graph& g, 
               VertexPropertiesWriter vpw
               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  write_graphviz(out, g, vpw, default_writer());
}

template<typename Graph>
inline void 
write_graphviz(std::ostream& out, const Graph& g
               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  write_graphviz(out, g, default_writer());
}

template<typename Graph, typename VertexPropertiesWriter, 
         typename EdgePropertiesWriter, typename GraphPropertiesWriter>
void 
write_graphviz(const std::string& filename,
               const Graph& g, 
               VertexPropertiesWriter vpw,
               EdgePropertiesWriter epw,
               GraphPropertiesWriter gpw
               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  if (process_id(g.process_group()) == 0) {
    std::ofstream out(filename.c_str());
    write_graphviz(out, g, vpw, epw, gpw);
  } else {
    write_graphviz(std::cout, g, vpw, epw, gpw);
  }
}

template<typename Graph, typename VertexPropertiesWriter, 
         typename EdgePropertiesWriter>
void 
write_graphviz(const std::string& filename,
               const Graph& g, 
               VertexPropertiesWriter vpw,
               EdgePropertiesWriter epw
               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  if (process_id(g.process_group()) == 0) {
    std::ofstream out(filename.c_str());
    write_graphviz(out, g, vpw, epw);
  } else {
    write_graphviz(std::cout, g, vpw, epw);
  }
}

template<typename Graph, typename VertexPropertiesWriter>
void 
write_graphviz(const std::string& filename,
               const Graph& g, 
               VertexPropertiesWriter vpw
               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  if (process_id(g.process_group()) == 0) {
    std::ofstream out(filename.c_str());
    write_graphviz(out, g, vpw);
  } else {
    write_graphviz(std::cout, g, vpw);
  }
}

template<typename Graph>
void 
write_graphviz(const std::string& filename, const Graph& g
               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  if (process_id(g.process_group()) == 0) {
    std::ofstream out(filename.c_str());
    write_graphviz(out, g);
  } else {
    write_graphviz(std::cout, g);
  }
}

template<typename Graph>
void
write_graphviz(std::ostream& out, const Graph& g,
               const dynamic_properties& dp, 
               const std::string& node_id = "node_id"
               BOOST_GRAPH_ENABLE_IF_MODELS_PARM(Graph,distributed_graph_tag))
{
  write_graphviz
    (out, g,
     /*vertex_writer=*/dynamic_vertex_properties_writer(dp, node_id),
     /*edge_writer=*/dynamic_properties_writer(dp));
}

} // end namespace boost

#endif // BOOST_GRAPH_PARALLEL_GRAPHVIZ_HPP

/* graphviz.hpp
bkI7TZWKWZuweZi5Dv0D1kJY6Sx+LYRxscWshZCXP3l6oVkM4YzXQlgcfi0EnQePn3K+kA1K0wepXI9LXqzqn2eG39cv0fL7a2Ml6lj6NrGPclRkH7UU1Tt3x4uOinMrV/kgZ99rPRtu3QSNb6rR8X1d7HUch71j/KrTe02CV7bVjENHWSQwYP5CA3FP5EylrNo6Fv2wxPO3Upu49mNWf/pHsxy9XPloc9/hyI2IMTrLI8qIvjT3sSt6v9pXHueVjXPFWX1d1UXuc3CWkrR5NlLishzzrdHOdpbTNV/2+Jsr47NZEwsKraBx7E0VzH5AIt8YtK/gpMmzAuaHLCnnjX8bc107GL2WS+Xa7pAx36P4fU+u64FS4daLaCZpPyQrVk62ehsd/ntE/nFcS0rLx65FURq/5u1ak9dXi/1OO406Xpui60A+J+efFfGNVYM+n56Ohc4PXPXEzWHtk3NkxNXgHIsdHutex0zrPmcNK8fDCpSeaGth9HeO4vZa3KV50lnqnmkoq/jkFCPRa2heZO2M++U8Y11lGPve61ypcjSg46UMW3Gy6mZcqF6Ahr9LrmGBVU/1BEZIfJe4oqlRl5L2b8i7dY7B7EBIL5mrvFXZVYP8xC++Pi3l058fTHlMcgynX3qNtZcx+v3OSOtl51NG9/0+OccHcp/qyzqVbOGkZYC1L4rf01HL80C5Bylavh1WWqLX/gl1zzNm/8FvJP4tpYqda4CfSdAl13VDKTsfsrLHz5xo9CPSkkQv15Esdv+9fzniJivb5Xb/0emNJwt/kRLPmoBzSQUlF+T1I/W4+LnG9sMzqlvTWSl6vnvipew6nDI/gVkV1sP+OSxadl6XstPVVTVa11rV8r/fcQdVR3H1y27M49ZTUk4SVYe8tOpzNC/t9RcteT4vSK9kvCgb+vWO+lTw+vurmZtyOFaeOffHlPFGjhhHurOr0+fXrotqi19HULr7OFpaDzBbZApKvn/1LLZeiLje49+ns7b4m8W9sPMnJ0BXZYSk4Tm1Bz6XZj9Y6mb863PYPVnmeaGbgd08tzdHbrMSI7znPE6IF+Q6Xihlx5Fv9hkbThwr5P6TRrH783p3sXuE1lYdoiclztdKXcDz/QHX2oE5LzMwBzzbrQVxb3IfTFjJd/qUi1tX1uyD+g+Jb3upgPkuRjdll5T7PPy2N++fo/L8VTbr3CyWe1w2Np21dMo4ro32677MLu+7Tz2sKhqfXh/lrwqjQNU1n9+T8G1dldhpaDG90wconS86Iq3XHU/JOSqY5+LZiDutZZ5hEV3lnqRyPVEWVdUEyrfmzWm5x7XimAXkvM/5mqOZp1yE972So++VH8vIuSj57KsocnHQe73FzNWoKvFcGVDHT+JZs98TD8h7Yq6jAaMNKUHvibci7rDaeWIjGlrTI+pJfNsIfULy+KFSgev26m0w79BUCV+JWtNp5iJ9KuHuIpx5bvgabdXCsutS9hz1PWPVdU7NaEn7CXcE7+8rKM8DHbsdFV0rrSOuKKue3oeEsjI/hjp0AfvHdGQvq16M15XnfTGYcet4q5YzWp63XPv9bOYlJUv8i0oVmZdk6s4lkp4Y8Z+H/Am5hjcoX6a+NfprD0hZ6hT4Pi7IyCk0eZIp6WyJblS8xHcIHx9JfPeWKro28fscPShu7wakbXbQvn5Lk+SZ9ojd3LM9AfVSbs54stcb30JsMXKtqyT/zbtY3o72M7xenpHFVmLQM5zs3G19JfGs9Ja7WKkbAp6xqWf8Pitub9wUrbN3xMs3Fj5jaHlEMkbysOpYFndt03PzMrIkTYuxVZRru0ryqpFU3HwK6fuxguosd5H3vtwSkUcht/OWnAq4768=
*/