// Copyright (C) 2006 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine

// This file contains the "unsafe_serialize" routine, which transforms
// types they may not be serializable (such as void*) into
// serializable equivalents.
#ifndef BOOST_PROPERTY_MAP_UNSAFE_SERIALIZE_HPP
#define BOOST_PROPERTY_MAP_UNSAFE_SERIALIZE_HPP

#include <boost/mpi/datatype.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <utility>

BOOST_IS_BITWISE_SERIALIZABLE(void*)
namespace boost { namespace mpi {
    template<> struct is_mpi_datatype<void*> : mpl::true_ { };
} } // end namespace boost::mpi

namespace boost {
  typedef mpl::if_c<(sizeof(int) == sizeof(void*)), 
                    int, 
                    mpl::if_c<(sizeof(long) == sizeof(void*)),
                              long,
                              mpl::if_c<(sizeof(void*) <= sizeof(boost::intmax_t)),
                                        boost::intmax_t,
                                        void>::type
                              >::type
                    >::type ptr_serialize_type;

  BOOST_STATIC_ASSERT ((!boost::is_void<ptr_serialize_type>::value));
    
  template<typename T> inline T& unsafe_serialize(T& x) { return x; }

  inline ptr_serialize_type& unsafe_serialize(void*& x)
  { return reinterpret_cast<ptr_serialize_type&>(x); }

  // Force Boost.MPI to serialize a void* like a ptr_serialize_type
  namespace mpi {
    template<> inline MPI_Datatype get_mpi_datatype<void*>(void* const& x)
    {
      return get_mpi_datatype<ptr_serialize_type>();
    }
  }

  template<typename T, typename U>
  struct unsafe_pair
  {
    unsafe_pair() { }
    unsafe_pair(const T& t, const U& u) : first(t), second(u) { }
    unsafe_pair(const std::pair<T, U>& p) : first(p.first), second(p.second) { }
    T first;
    U second;

    template<typename Archiver>
    void serialize(Archiver& ar, const unsigned /*version*/)
    {
      ar & unsafe_serialize(first) & unsafe_serialize(second);
    }
  };

  template<typename T, typename U>
  bool operator<(unsafe_pair<T,U> const& x, unsafe_pair<T,U> const& y)
  {
    return std::make_pair(x.first, x.second) < 
      std::make_pair(y.first, y.second);  
  }

} // end namespace boost

#endif // BOOST_PROPERTY_MAP_UNSAFE_SERIALIZE_HPP

/* unsafe_serialize.hpp
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
*/