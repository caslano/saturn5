//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP
#define BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/small_vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T, std::size_t N>
using small_vector = boost::container::small_vector<T, N, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a small_vector
//! that uses a polymorphic allocator
template<class T, std::size_t N>
struct small_vector_of
{
   typedef boost::container::small_vector
      < T, N, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_SMALL_VECTOR_HPP

/* small_vector.hpp
SxyjIdErIU2+BHfUmMtWwa7ZetipuYctKJzZXIHVZa2jLQT9sIslhvrEifopsUVGpV/vuGogHJlfKLGkpE0OjCUZd6d9JFJS4y55XuH4jshyef2fnfVbM3ycmo8olbi22nlM3WBJMHeDgZZWZloB2Q288HWninlrAzAiH/gmd/Iq4ZV+Z4lcwI8fdbCd2qxin4Qfo/WkfHyOcg7menBUK2nNDdV1NN3JcJ8JRGSpBxLReHc7svJ6dYm/cF3MVn9zosokmtnJKOSUijzhkFP/RrRphcNtF7k920JJ4hwQfGm/uVtDPwwMwFh5rNoHAOD2taI5sROu/yidxJiDQreQw7616tMlQayXqvYjT0++n0I1pB/Kk6aFvXk/9qh0Sp9yfL6fNAglvzl8dL0GNARE4Kuc9XaFBOvcl8KQKvDCY5cyf7fPh5n+FK/om6rjyBYJyyNHvfNF4s27ZJNZvK2N3QDszggyIveCmIypoQn3q8VHIOPZ1ntyx1ggRkfeJLud6FkOMfrKp213sF8SP10/M0wFzSaXcRNnVgFxHX9/bROCmKk/H/4n1uB4PQ==
*/