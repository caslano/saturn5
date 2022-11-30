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
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
*/