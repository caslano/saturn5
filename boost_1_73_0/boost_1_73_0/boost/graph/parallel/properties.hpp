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
M9VcMSQm1sCknazi4bcT6x2pWzNeMvDYzPpjQ8/+ymNDlh2QNuRomXd4xVayt2Af3wHpGUSLk2J1GY7LipASuWXJz19pbtPXIE2XnHix0A6/WFS8wdogGUOPDhuRMMdHGJ7w2/N/voe2t7eJO8NgTnkrQV49/54Kpuhsb4/6e4fWeqE6LFNIIrQJrp05EeQCxJnn/vPzl+WnrKq8GycrFipcMzbK61kYfjTilXgCvRYGEsrW7WQiz0tQfDfj0O7UTJlTc2zqrz8ARYn9OJe9umRAurTSJbAaKoywYPt7sz3R7Zy+7jrDUVsZkp1XnQtYQtrPfvhebrh446ksAgTHITh5bhb58sMnK7XLhiGBNuQvBzB3J1ZtKWCLWqqxk2Vt9XEq9oshelXDTT1V0SwtYW5nx1YaRfKJS2lM2gcsEU9BGXNvLYNfg0RUE2P56AKB6zu555FV6JKM1LcDa+k6iIhgsXIuGrBCCj/CWeLhMwZCZsbmHujwHAKBwULS9gjwI2GHz5KnEy/QuPbVfQbUOsOaBolkSlVebtQ4WCA1O2mUagE2mDAQaaxPyLG8LBYklBCKfs1fhJ9N9uTyzAK92ruBw4MIGB6rJ/ZCoROYMpiCP6ouQPhP7X2pLoVzuljK2JNyJ7QDrNY8a2Cy
*/