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
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
*/