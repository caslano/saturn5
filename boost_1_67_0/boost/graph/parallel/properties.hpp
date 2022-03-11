// Copyright 2004 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

#ifndef BOOST_GRAPH_PARALLEL_PROPERTIES_HPP
#define BOOST_GRAPH_PARALLEL_PROPERTIES_HPP

#ifndef BOOST_GRAPH_USE_MPI
#error "Parallel BGL files should not be included unless <boost/graph/use_mpi.hpp> has been included"
#endif

#include <boost/graph/properties.hpp>
#include <boost/property_map/parallel/distributed_property_map.hpp>

namespace boost {
  /***************************************************************************
   * Property map reduction operations
   ***************************************************************************/
  /**
   * Metafunction that produces a reduction operation for the given
   * property. The default behavior merely forwards to @ref
   * basic_reduce, but it is expected that this class template will be
   * specified for important properties.
   */
  template<typename Property>
  struct property_reduce
  {
    template<typename Value>
    class apply : public parallel::basic_reduce<Value> {};
  };

  /**
   * Reduction of vertex colors can only darken, not lighten, the
   * color. Black cannot turn black, grey can only turn black, and
   * white can be changed to either color. The default color is white.
   */ 
  template<> 
  struct property_reduce<vertex_color_t>
  {
    template<typename Color>
    class apply
    {
      typedef color_traits<Color> traits;
      
    public:
      BOOST_STATIC_CONSTANT(bool, non_default_resolver = true);

      template<typename Key>
      Color operator()(const Key&) const { return traits::white(); }
      
      template<typename Key>
      Color operator()(const Key&, Color local, Color remote) const {
        if (local == traits::white()) return remote;
        else if (remote == traits::black()) return remote;
        else return local;
      }
    };
  };

  /**
   * Reduction of a distance always takes the shorter distance. The
   * default distance value is the maximum value for the data type.
   */
  template<> 
  struct property_reduce<vertex_distance_t>
  {
    template<typename T>
    class apply
    {
    public:
      BOOST_STATIC_CONSTANT(bool, non_default_resolver = true);

      template<typename Key>
      T operator()(const Key&) const { return (std::numeric_limits<T>::max)(); }

      template<typename Key>
      T operator()(const Key&, T x, T y) const { return x < y? x : y; }
    };
  };

  template<> 
  struct property_reduce<vertex_predecessor_t>
  {
    template<typename T>
    class apply
    {
    public:
      BOOST_STATIC_CONSTANT(bool, non_default_resolver = true);

      template<typename Key>
      T operator()(Key key) const { return key; }
      template<typename Key>
      T operator()(Key key, T, T y) const { return y; }
    };
  };

  template<typename Property, typename PropertyMap>
  inline void set_property_map_role(Property p, PropertyMap pm)
  {
    typedef typename property_traits<PropertyMap>::value_type value_type;
    typedef property_reduce<Property> property_red;
    typedef typename property_red::template apply<value_type> reduce;

    pm.set_reduce(reduce());
  }

} // end namespace boost
#endif // BOOST_GRAPH_PARALLEL_PROPERTIES_HPP

/* properties.hpp
+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
*/