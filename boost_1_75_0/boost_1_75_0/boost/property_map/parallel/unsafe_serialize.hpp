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
CWOCdZaw2ydgCUnv4RctjmgMmlEug57wZ9CCa7c0hUuvmRn0YrAfg/7CTWH2NT8GXa43hScqx6COc5xBo88i7T10nTNo1+tCVU1h3eucQX3XiEF/LmUMutDAoGHBxopWyKDeq2ayOnrIyKDbDzEGPaE3hXsXGU3huI+UkO/RQ/8NyH+v3NIUHrliBtLlbwrv46Zw3RU/IIOCqg7kpN85kAPPYOt7rnIgs65W2RTef5UDed9VArLe74GAVNehVgrIrX+Zgaxz0Ahk0EEjkARctXfAFDKWwn1DR7rhghgUrCG+KItvqWawgAhMX6EKzWC8X4WmHTCbwWcPMDM4icxgGc4oATM4FrcqzSE7eOEGVA9Yi9ahFqlWL4hZvR/3M6sXFMjq/fmrZslKePIXntzHk0U8ufFXIeC+A8nM7t10aHYvjuxeSap0Au0euhFgr9LRshExI0Erlm+Ncr0sSBeFAdor1R1zqdHJ7G2gj4w/CuYiFdpMdCQ2zOyBXctdnVJbn70b+b5FTqnA2zfcZ49VRm5xG+oUb3qtkrvDsE5Kz/Lyk6xYmulIg0BQVlyg6GinW9oi9WM75mDl5d0zQLHoKKkiBereaI16OhKdAurLdtlFM8nLyNDiKUxOaZdD6i9Qt/QOn73WXyjd88jDK6K+bp/9NbqCz2XbLKhVQ60ZJQm+IhCiiUNw34WBqbm+zIdw84XTr1EpbrY0Oy8z
*/