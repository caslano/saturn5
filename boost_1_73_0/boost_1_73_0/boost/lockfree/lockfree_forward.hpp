//  Copyright (C) 2008-2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_LOCKFREE_FORWARD_HPP_INCLUDED
#define BOOST_LOCKFREE_FORWARD_HPP_INCLUDED


#ifndef BOOST_DOXYGEN_INVOKED

#include <cstddef> // size_t

#include <boost/config.hpp>

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#include <boost/parameter/aux_/void.hpp>
#endif

namespace boost    {
namespace lockfree {

// policies
template <bool IsFixedSized>
struct fixed_sized;

template <size_t Size>
struct capacity;

template <class Alloc>
struct allocator;


// data structures

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_,
          class A2 = boost::parameter::void_>
#else
template <typename T, typename ...Options>
#endif
class queue;

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_,
          class A2 = boost::parameter::void_>
#else
template <typename T, typename ...Options>
#endif
class stack;

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T,
          class A0 = boost::parameter::void_,
          class A1 = boost::parameter::void_>
#else
template <typename T, typename ...Options>
#endif
class spsc_queue;

}
}

#endif // BOOST_DOXYGEN_INVOKED

#endif // BOOST_LOCKFREE_FORWARD_HPP_INCLUDED

/* lockfree_forward.hpp
iSEZpF7EJgOxECoWU1QkCpgXRW5+7/WCUseIvhdmgekF1fG78yKpT3KHIBLxCFleQJFBaWQHiLIDSRaqiJ5oEFzMy2mszLyzQoOq0rCXaTAyjkkW8ilpLGwJN848HSKDHBGrgh4mSw2pup9nyRoh2pGkRKVOURHaAYnCDM3cgTINpWZiPnmlwtmUDfyka1Z4Q8hSBAMH/RsY3hzAVBhlOvBuOHkzvp3Au/71dX80uYPxBfRHdyTs7XD0Gl2vUJkG+ZBraVC5BpXksZKh0/n9/nqtH1QaxGUo4aDIstg3sijz7vyg1dgw6IfCvw/ccoS2ieD89vrSfz286b+6HPiXw1f8fXw1GY5HSIQUKpUwGPE27f3tX10PR5OLVu+QnA5ZqSG7TyHXKi2itoduSAMKOANrqCikHjYAMdIgmlH40dbGjhTm0ehgy05iZmZDViKTUE7LGS4DQvskZW6TAJPisn8zgYoSURH2WZxNRQwLoRVHP59UMfAOROgq0n6EZ5I6EoHEyCg1PoIMRcxkKrUgWpaGYVJizavMC4cOuB/KIIZTGN1eXp4QqL9WyoJYWAlspqcliEI0JbwqFWY901mYGNOyCLo7hTDmhpAbWVDWBiKOd2tHW8+FDpu8t2mQpQupC0XnMFbSTuWxxMyp
*/