// Copyright Daniel Wallin 2007. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_DISTRIBUTED_ADJLIST_SERIALIZATION_070925_HPP
#define BOOST_GRAPH_DISTRIBUTED_ADJLIST_SERIALIZATION_070925_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

# include <boost/assert.hpp>
# include <boost/lexical_cast.hpp>
# include <boost/foreach.hpp>
# include <boost/filesystem/path.hpp>
# include <boost/filesystem/operations.hpp>
# include <cctype>
# include <fstream>

namespace boost {

namespace detail { namespace parallel
{

  // Wraps a local descriptor, making it serializable.
  template <class Local>
  struct serializable_local_descriptor
  {
      serializable_local_descriptor()
      {}

      serializable_local_descriptor(Local local)
        : local(local)
      {}

      operator Local const&() const
      {
          return local;
      }

      bool operator==(serializable_local_descriptor const& other) const
      {
          return local == other.local;
      }

      bool operator<(serializable_local_descriptor const& other) const
      {
          return local < other.local;
      }

      template <class Archive>
      void serialize(Archive& ar, const unsigned int /*version*/)
      {
          ar & unsafe_serialize(local);
      }

      Local local;
  };

  template <class Vertex, class Properties>
  struct pending_edge
  {
      pending_edge(
          Vertex source, Vertex target
        , Properties properties, void* property_ptr
      )
        : source(source)
        , target(target)
        , properties(properties)
        , property_ptr(property_ptr)
      {}

      Vertex source;
      Vertex target;
      Properties properties;
      void* property_ptr;
  };

  inline bool is_digit(char c)
  {
      return std::isdigit(c) != 0;
  }

  inline std::vector<int> 
      available_process_files(std::string const& filename)
      {
          if (!filesystem::exists(filename))
              return std::vector<int>();

          std::vector<int> result;

          for (filesystem::directory_iterator i(filename), end; i != end; ++i)
          {
              if (!filesystem::is_regular(*i))
                  boost::throw_exception(std::runtime_error("directory contains non-regular entries"));

              std::string process_name = i->path().filename().string();
              for (std::string::size_type i = 0; i < process_name.size(); ++i)
                if (!is_digit(process_name[i]))
                  boost::throw_exception(std::runtime_error("directory contains files with invalid names"));

              result.push_back(boost::lexical_cast<int>(process_name));
          }

          return result;
      }

  template <class Archive, class Tag, class T, class Base>
  void maybe_load_properties(
      Archive& ar, char const* name, property<Tag, T, Base>& properties)
  {
      ar >> serialization::make_nvp(name, get_property_value(properties, Tag()));
      maybe_load_properties(ar, name, static_cast<Base&>(properties));
  }

  template <class Archive>
  void maybe_load_properties(
      Archive&, char const*, no_property&)
  {}

  template <class Archive, typename Bundle>
  void maybe_load_properties(
      Archive& ar, char const* name, Bundle& bundle)
  {
    ar >> serialization::make_nvp(name, bundle);
    no_property prop;
    maybe_load_properties(ar, name, prop);
  }






  template <class Graph, class Archive, class VertexListS>
  struct graph_loader
  {
      typedef typename Graph::vertex_descriptor vertex_descriptor;
      typedef typename Graph::local_vertex_descriptor local_vertex_descriptor;
      typedef typename Graph::vertex_property_type vertex_property_type;
      typedef typename Graph::edge_descriptor edge_descriptor;
      typedef typename Graph::local_edge_descriptor local_edge_descriptor;
      typedef typename Graph::edge_property_type edge_property_type;
      typedef typename Graph::process_group_type process_group_type;
      typedef typename process_group_type::process_id_type process_id_type;
      typedef typename Graph::directed_selector directed_selector;
      typedef typename mpl::if_<
          is_same<VertexListS, defaultS>, vecS, VertexListS
      >::type vertex_list_selector;
      typedef pending_edge<vertex_descriptor, edge_property_type> 
          pending_edge_type; 
      typedef serializable_local_descriptor<local_vertex_descriptor>
          serializable_vertex_descriptor;

      graph_loader(Graph& g, Archive& ar)
        : m_g(g)
        , m_ar(ar)
        , m_pg(g.process_group())
        , m_requested_vertices(num_processes(m_pg))
        , m_remote_vertices(num_processes(m_pg))
        , m_property_ptrs(num_processes(m_pg))
      {
          g.clear();
          load_prefix();
          load_vertices();
          load_edges();
          ar >> make_nvp("distribution", m_g.distribution());
      }

  private:
      struct pending_in_edge
      {
          pending_in_edge(
              vertex_descriptor u, vertex_descriptor v, void* property_ptr
          )
            : u(u)
            , v(v)
            , property_ptr(property_ptr)
          {}

          vertex_descriptor u;
          vertex_descriptor v;
          void* property_ptr;
      };

      bool is_root() const
      {
          return process_id(m_pg) == 0;
      }

      template <class T>
      serialization::nvp<T> const make_nvp(char const* name, T& value) const
      {
          return serialization::nvp<T>(name, value);
      }

      void load_prefix();
      void load_vertices();

      template <class Anything>
      void maybe_load_and_store_local_vertex(Anything);
      void maybe_load_and_store_local_vertex(vecS);

      void load_edges();
      void load_in_edges(bidirectionalS);
      void load_in_edges(directedS);
      void add_pending_in_edge(
          vertex_descriptor u, vertex_descriptor v, void* property_ptr, vecS);
      template <class Anything>
      void add_pending_in_edge(
          vertex_descriptor u, vertex_descriptor v, void* property_ptr, Anything);
      template <class Anything>
      void add_edge(
          vertex_descriptor u, vertex_descriptor v
        , edge_property_type const& property, void* property_ptr, Anything);
      void add_edge(
          vertex_descriptor u, vertex_descriptor v
        , edge_property_type const& property, void* property_ptr, vecS);
      void add_remote_vertex_request(
          vertex_descriptor u, vertex_descriptor v, directedS);
      void add_remote_vertex_request(
          vertex_descriptor u, vertex_descriptor v, bidirectionalS);
      void add_in_edge(
          edge_descriptor const&, void*, directedS);
      void add_in_edge(
          edge_descriptor const& edge, void* old_property_ptr, bidirectionalS);

      void resolve_remote_vertices(directedS);
      void resolve_remote_vertices(bidirectionalS);
      vertex_descriptor resolve_remote_vertex(vertex_descriptor u) const;
      vertex_descriptor resolve_remote_vertex(vertex_descriptor u, vecS) const;
      template <class Anything>
      vertex_descriptor resolve_remote_vertex(vertex_descriptor u, Anything) const;

      void resolve_property_ptrs();

      void commit_pending_edges(vecS);
      template <class Anything>
      void commit_pending_edges(Anything);
      void commit_pending_in_edges(directedS);
      void commit_pending_in_edges(bidirectionalS);

      void* maybe_load_property_ptr(directedS) { return 0; }
      void* maybe_load_property_ptr(bidirectionalS);

      Graph& m_g;
      Archive& m_ar;
      process_group_type m_pg;

      std::vector<process_id_type> m_id_mapping;

      // Maps local vertices as loaded from the archive to
      // the ones actually added to the graph. Only used 
      // when !vecS.
      std::map<local_vertex_descriptor, local_vertex_descriptor> m_local_vertices;

      // This is the list of remote vertex descriptors that we
      // are going to receive from other processes. This is
      // kept sorted so that we can determine the position of
      // the matching vertex descriptor in m_remote_vertices.
      std::vector<std::vector<serializable_vertex_descriptor> > m_requested_vertices;

      // This is the list of remote vertex descriptors that
      // we send and receive from other processes.
      std::vector<std::vector<serializable_vertex_descriptor> > m_remote_vertices;

      // ...
      std::vector<pending_edge_type> m_pending_edges;

      // The pending in-edges that will be added in the commit step, after
      // the remote vertex descriptors has been resolved. Only used
      // when bidirectionalS and !vecS.
      std::vector<pending_in_edge> m_pending_in_edges;

      std::vector<std::vector<unsafe_pair<void*,void*> > > m_property_ptrs;
  };

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::load_prefix()
  {
      typename process_group_type::process_size_type num_processes_;
      m_ar >> make_nvp("num_processes", num_processes_);

      if (num_processes_ != num_processes(m_pg))
          boost::throw_exception(std::runtime_error("number of processes mismatch"));

      process_id_type old_id;
      m_ar >> make_nvp("id", old_id);

      std::vector<typename Graph::distribution_type::size_type> mapping;
      m_ar >> make_nvp("mapping", mapping);

      // Fetch all the old id's from the other processes.
      std::vector<process_id_type> old_ids;
      all_gather(m_pg, &old_id, &old_id+1, old_ids);

      m_id_mapping.resize(num_processes(m_pg), -1);

      for (process_id_type i = 0; i < num_processes(m_pg); ++i)
      {
# ifdef PBGL_SERIALIZE_DEBUG
          if (is_root())
              std::cout << i << " used to be " << old_ids[i] << "\n"; 
# endif
          BOOST_ASSERT(m_id_mapping[old_ids[i]] == -1);
          m_id_mapping[old_ids[i]] = i;
      }

      std::vector<typename Graph::distribution_type::size_type> new_mapping(
          mapping.size());

      for (int i = 0; i < num_processes(m_pg); ++i)
      {
          new_mapping[mapping[old_ids[i]]] = i;
      }

      m_g.distribution().assign_mapping(
          new_mapping.begin(), new_mapping.end());
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::load_vertices()
  {
      int V;
      m_ar >> BOOST_SERIALIZATION_NVP(V); 

# ifdef PBGL_SERIALIZE_DEBUG
      if (is_root())
          std::cout << "Loading vertices\n";
# endif

      for (int i = 0; i < V; ++i)
      {
          maybe_load_and_store_local_vertex(vertex_list_selector());
      }
  }

  template <class Graph, class Archive, class VertexListS>
  template <class Anything>
  void graph_loader<Graph, Archive, VertexListS>::maybe_load_and_store_local_vertex(Anything)
  {
      // Load the original vertex descriptor
      local_vertex_descriptor local;
      m_ar >> make_nvp("local", unsafe_serialize(local)); 

      // Load the properties
      vertex_property_type property;
      detail::parallel::maybe_load_properties(m_ar, "vertex_property",
                          property);

      // Add the vertex
      vertex_descriptor v(process_id(m_pg), add_vertex(property, m_g.base()));

      if (m_g.on_add_vertex)
        m_g.on_add_vertex(v, m_g);

      // Create the mapping from the "old" local descriptor to the new
      // local descriptor.
      m_local_vertices[local] = v.local;
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::maybe_load_and_store_local_vertex(vecS)
  {
      // Load the properties
      vertex_property_type property;
      detail::parallel::maybe_load_properties(m_ar, "vertex_property",
                          property);

      // Add the vertex
      vertex_descriptor v(process_id(m_pg), 
                          add_vertex(m_g.build_vertex_property(property), 
                                     m_g.base()));

      if (m_g.on_add_vertex)
        m_g.on_add_vertex(v, m_g);
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::load_edges()
  {
      int E;
      m_ar >> BOOST_SERIALIZATION_NVP(E);

# ifdef PBGL_SERIALIZE_DEBUG
      if (is_root())
          std::cout << "Loading edges\n";
# endif

      for (int i = 0; i < E; ++i)
      {
          local_vertex_descriptor local_src;
          process_id_type target_owner;
          local_vertex_descriptor local_tgt;

          m_ar >> make_nvp("source", unsafe_serialize(local_src)); 
          m_ar >> make_nvp("target_owner", target_owner); 
          m_ar >> make_nvp("target", unsafe_serialize(local_tgt)); 

          process_id_type new_src_owner = process_id(m_pg);
          process_id_type new_tgt_owner = m_id_mapping[target_owner];

          vertex_descriptor source(new_src_owner, local_src);
          vertex_descriptor target(new_tgt_owner, local_tgt);

          edge_property_type properties;
          detail::parallel::maybe_load_properties(m_ar, "edge_property", properties);

          void* property_ptr = maybe_load_property_ptr(directed_selector());
          add_edge(source, target, properties, property_ptr, vertex_list_selector());
      }

      load_in_edges(directed_selector());
      commit_pending_edges(vertex_list_selector());
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::load_in_edges(bidirectionalS)
  {
      std::size_t I;
      m_ar >> BOOST_SERIALIZATION_NVP(I);

# ifdef PBGL_SERIALIZE_DEBUG
      if (is_root())
          std::cout << "Loading in-edges\n";
# endif

      for (int i = 0; i < I; ++i)
      {
          process_id_type src_owner;
          local_vertex_descriptor local_src;
          local_vertex_descriptor local_target;
          void* property_ptr;

          m_ar >> make_nvp("src_owner", src_owner);
          m_ar >> make_nvp("source", unsafe_serialize(local_src));
          m_ar >> make_nvp("target", unsafe_serialize(local_target));
          m_ar >> make_nvp("property_ptr", unsafe_serialize(property_ptr));

          src_owner = m_id_mapping[src_owner];

          vertex_descriptor u(src_owner, local_src);
          vertex_descriptor v(process_id(m_pg), local_target);

          add_pending_in_edge(u, v, property_ptr, vertex_list_selector());
      }
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::load_in_edges(directedS)
  {}

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::add_pending_in_edge(
      vertex_descriptor u, vertex_descriptor v, void* property_ptr, vecS)
  {
      m_pending_in_edges.push_back(pending_in_edge(u,v,property_ptr));
  }

  template <class Graph, class Archive, class VertexListS>
  template <class Anything>
  void graph_loader<Graph, Archive, VertexListS>::add_pending_in_edge(
      vertex_descriptor u, vertex_descriptor v, void* property_ptr, Anything)
  {
      // u and v represent the out-edge here, meaning v is local
      // to us, and u is always remote.
      m_pending_in_edges.push_back(pending_in_edge(u,v,property_ptr));
      add_remote_vertex_request(v, u, bidirectionalS());
  }

  template <class Graph, class Archive, class VertexListS> 
  template <class Anything>
  void graph_loader<Graph, Archive, VertexListS>::add_edge(
      vertex_descriptor u, vertex_descriptor v
    , edge_property_type const& property, void* property_ptr, Anything)
  {
      m_pending_edges.push_back(pending_edge_type(u, v, property, property_ptr));
      add_remote_vertex_request(u, v, directed_selector());
  }

  template <class Graph, class Archive, class VertexListS> 
  void graph_loader<Graph, Archive, VertexListS>::add_remote_vertex_request(
      vertex_descriptor u, vertex_descriptor v, directedS)
  {
      // We have to request the remote vertex.
      m_requested_vertices[owner(v)].push_back(local(v));
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::add_remote_vertex_request(
      vertex_descriptor u, vertex_descriptor v, bidirectionalS)
  {
      // If the edge spans to another process, we know
      // that that process has a matching in-edge, so
      // we can just send our vertex. No requests
      // necessary.
      if (owner(v) != m_g.processor())
      {
          m_remote_vertices[owner(v)].push_back(local(u));
          m_requested_vertices[owner(v)].push_back(local(v));
      }
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::add_edge(
      vertex_descriptor u, vertex_descriptor v
    , edge_property_type const& property, void* property_ptr, vecS)
  {
      std::pair<local_edge_descriptor, bool> inserted = 
          detail::parallel::add_local_edge(
              local(u), local(v)
            , m_g.build_edge_property(property), m_g.base());
      BOOST_ASSERT(inserted.second);
      put(edge_target_processor_id, m_g.base(), inserted.first, owner(v));

      edge_descriptor e(owner(u), owner(v), true, inserted.first);

      if (inserted.second && m_g.on_add_edge)
        m_g.on_add_edge(e, m_g);

      add_in_edge(e, property_ptr, directed_selector());
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::add_in_edge(
      edge_descriptor const&, void*, directedS)
  {}

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::add_in_edge(
      edge_descriptor const& edge, void* old_property_ptr, bidirectionalS)
  {
      if (owner(target(edge, m_g)) == m_g.processor())
      {
          detail::parallel::stored_in_edge<local_edge_descriptor>
              e(m_g.processor(), local(edge));
          boost::graph_detail::push(get(
              vertex_in_edges, m_g.base())[local(target(edge, m_g))], e);
      }
      else
      {
          // We send the (old,new) property pointer pair to
          // the remote process. This could be optimized to
          // only send the new one -- the ordering can be
          // made implicit because the old pointer value is
          // stored on the remote process.
          //
          // Doing that is a little bit more complicated, but
          // in case it turns out it's important we can do it.
          void* property_ptr = local(edge).get_property();
          m_property_ptrs[owner(target(edge, m_g))].push_back(
              unsafe_pair<void*,void*>(old_property_ptr, property_ptr));
      }
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::resolve_property_ptrs()
  {
# ifdef PBGL_SERIALIZE_DEBUG
      if (is_root())
          std::cout << "Resolving property pointers\n";
# endif

      for (int i = 0; i < num_processes(m_pg); ++i)
      {
          std::sort(
              m_property_ptrs[i].begin(), m_property_ptrs[i].end());
      }

      boost::parallel::inplace_all_to_all(m_pg, m_property_ptrs);
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::resolve_remote_vertices(directedS)
  {
      for (int i = 0; i < num_processes(m_pg); ++i)
      {
          std::sort(m_requested_vertices[i].begin(), m_requested_vertices[i].end());
      }

      boost::parallel::inplace_all_to_all(
          m_pg, m_requested_vertices, m_remote_vertices);

      for (int i = 0; i < num_processes(m_pg); ++i)
      {
          BOOST_FOREACH(serializable_vertex_descriptor& u, m_remote_vertices[i])
          {
              u = m_local_vertices[u];
          }
      }

      boost::parallel::inplace_all_to_all(m_pg, m_remote_vertices);
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::resolve_remote_vertices(bidirectionalS)
  {
# ifdef PBGL_SERIALIZE_DEBUG
      if (is_root())
          std::cout << "Resolving remote vertices\n";
# endif

      for (int i = 0; i < num_processes(m_pg); ++i)
      {
          std::sort(m_requested_vertices[i].begin(), m_requested_vertices[i].end());
          std::sort(m_remote_vertices[i].begin(), m_remote_vertices[i].end());

          BOOST_FOREACH(serializable_vertex_descriptor& u, m_remote_vertices[i])
          {
              u = m_local_vertices[u];
          }
      }

      boost::parallel::inplace_all_to_all(m_pg, m_remote_vertices);

      for (int i = 0; i < num_processes(m_pg); ++i)
          BOOST_ASSERT(m_remote_vertices[i].size() == m_requested_vertices[i].size());
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::commit_pending_edges(vecS)
  {
      commit_pending_in_edges(directed_selector());
  }

  template <class Graph, class Archive, class VertexListS>
  template <class Anything>
  void graph_loader<Graph, Archive, VertexListS>::commit_pending_edges(Anything)
  {
      resolve_remote_vertices(directed_selector());

      BOOST_FOREACH(pending_edge_type const& e, m_pending_edges)
      {
          vertex_descriptor u = resolve_remote_vertex(e.source);
          vertex_descriptor v = resolve_remote_vertex(e.target);
          add_edge(u, v, e.properties, e.property_ptr, vecS());
      }

      commit_pending_in_edges(directed_selector());
  }

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::commit_pending_in_edges(directedS)
  {}

  template <class Graph, class Archive, class VertexListS>
  void graph_loader<Graph, Archive, VertexListS>::commit_pending_in_edges(bidirectionalS)
  {
      resolve_property_ptrs();

      BOOST_FOREACH(pending_in_edge const& e, m_pending_in_edges)
      {
          vertex_descriptor u = resolve_remote_vertex(e.u, vertex_list_selector());
          vertex_descriptor v = resolve_remote_vertex(e.v, vertex_list_selector());

          typedef detail::parallel::stored_in_edge<local_edge_descriptor> stored_edge;

          std::vector<unsafe_pair<void*,void*> >::iterator i = std::lower_bound(
              m_property_ptrs[owner(u)].begin()
            , m_property_ptrs[owner(u)].end()
            , unsafe_pair<void*,void*>(e.property_ptr, 0)
          );

          if (i == m_property_ptrs[owner(u)].end()
              || i->first != e.property_ptr)
          {
              BOOST_ASSERT(false);
          }

          local_edge_descriptor local_edge(local(u), local(v), i->second);
          stored_edge edge(owner(u), local_edge);
          boost::graph_detail::push(
              get(vertex_in_edges, m_g.base())[local(v)], edge);
      }
  }

  template <class Graph, class Archive, class VertexListS>
  typename graph_loader<Graph, Archive, VertexListS>::vertex_descriptor 
  graph_loader<Graph, Archive, VertexListS>::resolve_remote_vertex(
      vertex_descriptor u) const
  {
      if (owner(u) == process_id(m_pg))
      { 
          return vertex_descriptor(
              process_id(m_pg), m_local_vertices.find(local(u))->second);
      }

      typename std::vector<serializable_vertex_descriptor>::const_iterator 
          i = std::lower_bound(
              m_requested_vertices[owner(u)].begin()
            , m_requested_vertices[owner(u)].end()
            , serializable_vertex_descriptor(local(u))
          );

      if (i == m_requested_vertices[owner(u)].end()
          || *i != local(u))
      {
          BOOST_ASSERT(false);
      }

      local_vertex_descriptor local =
          m_remote_vertices[owner(u)][m_requested_vertices[owner(u)].end() - i];
      return vertex_descriptor(owner(u), local);
  }

  template <class Graph, class Archive, class VertexListS>
  typename graph_loader<Graph, Archive, VertexListS>::vertex_descriptor 
  graph_loader<Graph, Archive, VertexListS>::resolve_remote_vertex(
      vertex_descriptor u, vecS) const
  {
      return u;
  }

  template <class Graph, class Archive, class VertexListS>
  template <class Anything>
  typename graph_loader<Graph, Archive, VertexListS>::vertex_descriptor 
  graph_loader<Graph, Archive, VertexListS>::resolve_remote_vertex(
      vertex_descriptor u, Anything) const
  {
      return resolve_remote_vertex(u);
  }

  template <class Graph, class Archive, class VertexListS>
  void* 
  graph_loader<Graph, Archive, VertexListS>::maybe_load_property_ptr(bidirectionalS)
  {
      void* ptr;
      m_ar >> make_nvp("property_ptr", unsafe_serialize(ptr));
      return ptr;
  }

template <class Archive, class D>
void maybe_save_local_descriptor(Archive& ar, D const&, vecS)
{}

template <class Archive, class D, class NotVecS>
void maybe_save_local_descriptor(Archive& ar, D const& d, NotVecS)
{
    ar << serialization::make_nvp(
        "local", unsafe_serialize(const_cast<D&>(d)));
}

template <class Archive>
void maybe_save_properties(
    Archive&, char const*, no_property const&)
{}

template <class Archive, class Tag, class T, class Base>
void maybe_save_properties(
    Archive& ar, char const* name, property<Tag, T, Base> const& properties)
{
    ar & serialization::make_nvp(name, get_property_value(properties, Tag()));
    maybe_save_properties(ar, name, static_cast<Base const&>(properties));
}

template <class Archive, class Graph>
void save_in_edges(Archive& ar, Graph const& g, directedS)
{}

// We need to save the edges in the base edge
// list, and the in_edges that are stored in the
// vertex_in_edges vertex property.
template <class Archive, class Graph>
void save_in_edges(Archive& ar, Graph const& g, bidirectionalS)
{
    typedef typename Graph::process_group_type
        process_group_type;
    typedef typename process_group_type::process_id_type
        process_id_type;
    typedef typename graph_traits<
        Graph>::vertex_descriptor vertex_descriptor;
    typedef typename vertex_descriptor::local_descriptor_type 
        local_vertex_descriptor;
    typedef typename graph_traits<
        Graph>::edge_descriptor edge_descriptor;

    process_id_type id = g.processor();

    std::vector<edge_descriptor> saved_in_edges;

    BGL_FORALL_VERTICES_T(v, g, Graph) 
    {
        BOOST_FOREACH(edge_descriptor const& e, in_edges(v, g))
        {
            // Only save the in_edges that isn't owned by this process.
            if (owner(e) == id)
                continue;

            saved_in_edges.push_back(e);
        }
    }

    std::size_t I = saved_in_edges.size();
    ar << BOOST_SERIALIZATION_NVP(I);

    BOOST_FOREACH(edge_descriptor const& e, saved_in_edges)
    {
        process_id_type src_owner = owner(source(e,g));
        local_vertex_descriptor local_src = local(source(e,g));
        local_vertex_descriptor local_target = local(target(e,g));
        void* property_ptr = local(e).get_property();

        using serialization::make_nvp;

        ar << make_nvp("src_owner", src_owner);
        ar << make_nvp("source", unsafe_serialize(local_src));
        ar << make_nvp("target", unsafe_serialize(local_target));
        ar << make_nvp("property_ptr", unsafe_serialize(property_ptr));
    }
}

template <class Archive, class Edge>
void maybe_save_property_ptr(Archive&, Edge const&, directedS)
{}

template <class Archive, class Edge>
void maybe_save_property_ptr(Archive& ar, Edge const& e, bidirectionalS)
{
    void* ptr = local(e).get_property();
    ar << serialization::make_nvp("property_ptr", unsafe_serialize(ptr));
}

template <class Archive, class Graph, class DirectedS>
void save_edges(Archive& ar, Graph const& g, DirectedS)
{
    typedef typename Graph::process_group_type
        process_group_type;
    typedef typename process_group_type::process_id_type
        process_id_type;
    typedef typename graph_traits<
        Graph>::vertex_descriptor vertex_descriptor;

    typedef typename Graph::edge_property_type edge_property_type;

    int E = num_edges(g);
    ar << BOOST_SERIALIZATION_NVP(E);

    // For *directed* graphs, we can just save
    // the edge list and be done.
    //
    // For *bidirectional* graphs, we need to also
    // save the "vertex_in_edges" property map,
    // because it might contain in-edges that
    // are not locally owned.
    BGL_FORALL_EDGES_T(e, g, Graph) 
    {
        vertex_descriptor src(source(e, g));
        vertex_descriptor tgt(target(e, g));

        typename vertex_descriptor::local_descriptor_type
            local_u(local(src));
        typename vertex_descriptor::local_descriptor_type
            local_v(local(tgt));

        process_id_type target_owner = owner(tgt);

        using serialization::make_nvp;

        ar << make_nvp("source", unsafe_serialize(local_u)); 
        ar << make_nvp("target_owner", target_owner); 
        ar << make_nvp("target", unsafe_serialize(local_v)); 

        maybe_save_properties(
            ar, "edge_property"
          , static_cast<edge_property_type const&>(get(edge_all_t(), g, e))
        );

        maybe_save_property_ptr(ar, e, DirectedS());
    }

    save_in_edges(ar, g, DirectedS());
}

}} // namespace detail::parallel

template <PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template <class IStreamConstructibleArchive>
void PBGL_DISTRIB_ADJLIST_TYPE::load(std::string const& filename)
{
    process_group_type pg = process_group();
    process_id_type id = process_id(pg);

    synchronize(pg);

    std::vector<int> disk_files = detail::parallel::available_process_files(filename);
    std::sort(disk_files.begin(), disk_files.end());

    // Negotiate which process gets which file. Serialized.
    std::vector<int> consumed_files;
    int picked_file = -1;

    if (id > 0)
        receive_oob(pg, id-1, 0, consumed_files);

    std::sort(consumed_files.begin(), consumed_files.end());
    std::vector<int> available_files;
    std::set_difference(
        disk_files.begin(), disk_files.end()
      , consumed_files.begin(), consumed_files.end()
      , std::back_inserter(available_files)
    );

    if (available_files.empty())
        boost::throw_exception(std::runtime_error("no file available"));

    // back() used for debug purposes. Making sure the
    // ranks are shuffled.
    picked_file = available_files.back();

# ifdef PBGL_SERIALIZE_DEBUG
    std::cout << id << " picked " << picked_file << "\n";
# endif

    consumed_files.push_back(picked_file);

    if (id < num_processes(pg) - 1)
        send_oob(pg, id+1, 0, consumed_files);

    std::string local_filename = filename + "/" + 
        lexical_cast<std::string>(picked_file);

    std::ifstream in(local_filename.c_str(), std::ios_base::binary);
    IStreamConstructibleArchive ar(in);

    detail::parallel::graph_loader<
        graph_type, IStreamConstructibleArchive, InVertexListS
    > loader(*this, ar);

# ifdef PBGL_SERIALIZE_DEBUG
    std::cout << "Process " << id << " done loading.\n";
# endif

    synchronize(pg);
}

template <PBGL_DISTRIB_ADJLIST_TEMPLATE_PARMS>
template <class OStreamConstructibleArchive>
void PBGL_DISTRIB_ADJLIST_TYPE::save(std::string const& filename) const
{
    typedef typename config_type::VertexListS vertex_list_selector;

    process_group_type pg = process_group();
    process_id_type id = process_id(pg);

    if (filesystem::exists(filename) && !filesystem::is_directory(filename))
        boost::throw_exception(std::runtime_error("entry exists, but is not a directory"));

    filesystem::remove_all(filename);
    filesystem::create_directory(filename);

    synchronize(pg);

    std::string local_filename = filename + "/" + 
        lexical_cast<std::string>(id);

    std::ofstream out(local_filename.c_str(), std::ios_base::binary);
    OStreamConstructibleArchive ar(out);

    using serialization::make_nvp;

    typename process_group_type::process_size_type num_processes_ = num_processes(pg);
    ar << make_nvp("num_processes", num_processes_);
    ar << BOOST_SERIALIZATION_NVP(id);
    ar << make_nvp("mapping", this->distribution().mapping());

    int V = num_vertices(*this);
    ar << BOOST_SERIALIZATION_NVP(V);

    BGL_FORALL_VERTICES_T(v, *this, graph_type)
    {
        local_vertex_descriptor local_descriptor(local(v));
        detail::parallel::maybe_save_local_descriptor(
            ar, local_descriptor, vertex_list_selector());
        detail::parallel::maybe_save_properties(
            ar, "vertex_property"
          , static_cast<vertex_property_type const&>(get(vertex_all_t(), *this, v))
        );
    }

    detail::parallel::save_edges(ar, *this, directed_selector());

    ar << make_nvp("distribution", this->distribution());
}

} // namespace boost

#endif // BOOST_GRAPH_DISTRIBUTED_ADJLIST_SERIALIZATION_070925_HPP


/* serialization.hpp
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
*/