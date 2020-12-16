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
3rYNZIy7GJbn+YvMzyijYbEo2c4uyzUB2cycvwtKfmvZjuhJ2OWZ8hdkXcw385nfYWas3he3y3QdsU1mmmy2aI7ElNf7+b32mkY+c5Yt+3lrSv3gF2+q7UlPdzH6g0g2bTbHNFv7cqbbb7CPyPgCdJt6hqTrMY+k9fe9YYYY9I9pVjWeZho9r2tUUttVFdlWmxdvaf5hvGgrazvsv8hItd9jrLf/ovsH/FX222C3PlBi1bQ0fZrPePtRKeqVhkQ/YjLhPK4lyOfbjSDKVFNt+F/mFx5Lbaz9cMbaxKhOWyXamEtsJtzbg7ftbYw37R7XQvR+skPmtY4RI2lr3un02W3efy3j3q8B0+6yfLMnjk+z+ucLlvl92bSzn9YwRhj/ZpuWz/R6+t6vA+cw99v6G6tsbzMeVd/IMc9aT71lWkKMWFUHN5TtYybXqMoYK5n7rUYMPRL8qbefh6T8R+bPLMGtzIHUzx77pdRROq+kHOuZdGNg4TYRFqmnpe39TI1b32Qt5fvLGzZyYtR1/XxZ/wvCDpvtjac5OqzhSf0i14PUcnlGhg/x62dEmNPM8WasWp9PSz3+b8Y60JjFkXA98SFR3G2ZdZA6pZOXfdCaZquyjlHLJFi+c7Wfne0ix1hnTrdFmpWK1sEynlT2m+nsNz38x+j3356W+XsizDFPr0YWPtNruPS3cbTwGGa+bGwvehzTx590KgZrvaYvkuO4/v1wsqSLDO96DVOXDZD1VEO3Ae6TdCPbYNoAI2kDXKRucK/3aMWqem+4bJdfmqONW5Sx6juGd9mWOWpnjtDfd1aOI5WN2CLHyfJ+mX7FzCf9KxuBdtf6YYI05CML60s1L36hqca7AZ7Px8q5Lzqe3ezajetkg53X3x6fEmoP5bm6RaF+XIkrZvh8V64MF/eQur4X+fgiz2t7180BEdNIN1TX5PxYh43VtbU/0Z+0nQggiqkIJILEwggmKM9wVhQQIeT7E434OxSPhItyzS8Mi8u4LQNUlCDC1XRQXl/7s+m/i4SUi1DjiSRsKt2dccxWzwmVlOGd3l2UouwpeXamcPpLk07n7ygsQ0QTv5IuizHEMVl27s/45Hmkt4Vb+dFqWsopo7C8x/RtEq3fy+msWCKWqEjMVsOtQP6W6TwaXpiOcxnXMRW+n+MhX7XZwp6RupSaNJQeIXsVPs9j3vl5njRTnueR+/yzZV8yqgwdRTfi0kblPcOL3K+77nW/7ip5BV6urx71cn31pJfrq2d8XF+94OP66mUv11dv+ri+atiKXl8NtHm/vhpu8359Ndrm/fpqnM379dV4m/frqwm2or/DN7EV/R0+0Vb0Oipl5Vx6nIyXc3J977/367PJtqLXZ1Ns3q/Dptm8X4fNtvm+Dptj834dNtdW5P48fV/mZVnHcsjQ199pf+hnJ2R5GM7hnfUt24fh9syDPFtwI8/92YOghfrZA7f7AU+ONOTfVD/DqIrD8CBlshc7r/s6ez8u8tu8fmf+B1K2qp++X0DS9XQ7c62ku3u97hiP78vnNfycx8n+z8r1C/2Mc9clcn3MDKO/TH2fgQwzwOXaj2ypMs440u/I57X9nOdPbz5r3R+Y5jq8Oq/If07uBXLpl2DS0IyJHA/V8ewFKd9DxtfTZXj3flTc33kwScZZVc2HaayVdEmjGP8VPUdVfZfJvDaz9THambL89HDtvJ5vJKK33x7L4CaZxlZ+Hm0YvV52yXdl6vbWC/I9XTzbL7p85Wddr8k7lxltCN1H27BM1/Fflu9/uMj4C39D0/W5HIfqRLgf05L1cc3jOOCj/v+Z8uck7R73ROoyUtfPMe5c12cjdb3U68yfW72ebxStr3cb7nU=
*/