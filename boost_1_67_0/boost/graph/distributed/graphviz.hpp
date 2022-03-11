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