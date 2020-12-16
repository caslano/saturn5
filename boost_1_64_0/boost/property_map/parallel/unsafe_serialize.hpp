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
2m9saPFxmvbba1yPzpfS9hHmHY/QDl/nO5Jpv7W0c28V847JzHe/xPau0T+16wq3FLET2vGur9H+nqI91XCdvJ15YQT1HKRdNTNO0v5nm7TrEMzP0hjHfsd2U+gf+3k+TKZfMZ5MmsLfdkjm/LyF/vwX+k8a48gvaJdLaB/X5LO6jeeBR6XMPqKXdjcxzqyVdmzt/C1nI8/bfw3neEpZ8RL7XWMQef/IPPcb9Pc2aa+f69xzP2b+vkORcezm+P2Y86PjOoP+vegv3L+G+nP9ndkp5ZaPMz9+lHFrC/PK4zwPr2Qe/DeOQzj1mMr85P2Mb8t10u5Vyr9PJ+3GMr/4GvPcr/J8HqXFPb4L3G7g9Sv6dYWUuhpFPn+c4/ku5nunqd+XGLf/ztP9QFk9bXEAv3dmLg3lVYQoCiEMTQylUoNRgyiKwtBgEI0aGjWU6imKorx69OhV1FMUoiiZ/lBPURJCT6N6GqRS0b9R07yz1u/ze62111nTvff3O2efvb/7u/c+93dPxst+8UzqnvizdZXKS5vCo5JKcfsmdkBPk/p75nvLVPS+V/CrVtbrOgUl4v1e+pI/5TQRb88Xf2Z6nX8nN+Fdv8K/TvK+Ouz0GfGsBzt723VS6jcjzPc09awqcf9+fPlO9jID/mTiFePk/Sfbz4/Ma3Rcv0tE1ztPfW4wHvoYfmV/U8Vwbrt4cgV+m8GuXk2PriMvq3dhNDbuqZ7YRvyRB05azS6WibP4fOZYdYjZ7LeVfT+ciMY35cXjjAej15eehe8fYKcr8ZVHotfLBtNDL/v1rPj3k7x5gTz+Nryqr3j2CZyrwGdHJKJ9bAi3LoOv3/Kz16Mx972M6HV1tJId6ni/JfyWKn/4yXXa8adn/BbmP6LXs35PRHpfBf9Ow9/asMdH6T/dfc7HB26JXi9/xTPx78aP+3pWdl287p3o9YZHyvvVr9cl4dOb6guN+cXneNxD+J64X9ASP1rMLp+A+5+y//nqWEfz0yz5YUv2fRU/H40vDKAn+zSxkp4ek38eIf/9jr8czS92qDfAnRE/evY+/Ct7HL8/W95/Or/xmxPLb4zGibPgo7yg4NNobPgVXG8Fh7+Un7zOT5pErzdgvznGzj+YB9wYd6J4upnfq98UZ9C7uLJ8Fh6ANxZc4f/PUJeYnC4/hWNz2as41joNnt4mvu8Rr47F39Vnx7HXkmCPUZ7K39vJgweIl/y8bFY0JtlnLj6Sei4aC+VJu5viU+y78AZ+8LT4/i6c+hv+cyK9z0p69nu6fA1/WKV+tS/6O1Xhmf3qw4PZ1Vb8OeuxaCzpIF+lt7KG+FdGQj0bz5JnFaqb1nstGqvXwxX6zK2Kxsb8eHddel+NB22QZ8i/yg8lo3Xy16WN8JqbzNvrU8eys8b87rC8DN7No4+8yXAA72xY17oXmuef/OwGvAf+lrWKf3POvLra1zVwr6f7H4N3nIG3s4euTdnV867zhXpgh2is7iDOqNPUGR2Nec/hP67b9Xw87Xj4kYN37hNfDtBnC3lACX/jJ51niB83q1d0Yj94Te8C/P18++t6Ex7FK9rT15horGyD/5+O710KJ0/Cz8bIg3bY/7f5Uyd4UIdf/tf/26/lbeHsbP50F37yR/R60Rx6P+z6X0avN7w+en1mjjyrofopey88hEeeiw+38f6V/Phn/qXOXHFAP2SD/od+V8Gf6Xgwfz4R/twjrt2mfvA5e+2LV9Fb1gD4MTjuB5gPvx72L7/1kwm/J8nTatP7jfYF7udfw09ftA/N+IH6WDk+nDeO38kHlooPuT3wkj7yrk0+r46ZfQT7TciHfkyL1q9OUVxLXfhd9X35Q+bP9KWOUOjvBVc=
*/