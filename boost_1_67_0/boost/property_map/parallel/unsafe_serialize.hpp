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