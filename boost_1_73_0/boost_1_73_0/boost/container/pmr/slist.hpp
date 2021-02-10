//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SLIST_HPP
#define BOOST_CONTAINER_PMR_SLIST_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/slist.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using slist = boost::container::slist<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a slist
//! that uses a polymorphic allocator
template<class T>
struct slist_of
{
   typedef boost::container::slist
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_VECTOR_HPP

/* slist.hpp
cdNBjTv2TufhSMP1XvQ1xC5Q23i7dGxoXQPjClbIQd7mmp9cOK2eAqst7PJPFbZE6SHF6q3xxNLNWv4CjRxnuWnuLqRTfz5JnHA+mZiN6SxKolE0iZ2zJJn24r7ZHf/lf5hOxibnwz1rAgH5xhQIe69EQprpw7I1LqXCmULZJfquKnC10D7Sc+hgREYl3fljyoHJxl5hynMejl17TjK5fexU0n9JqoC167QiGXaqfFRKiRZvHsMFbb0TRRL8v44lASZZNH3nEwrkVSasRnOMSx3JnhIZk6WG+g16ZqdvNLTAaTAZwx5vlV4YNRS650K62uqE9XZ+gPumyVTl9o2FsmfVnj2DHzAElq8bu4NyQ5tTD37p9+GT8b9sBLpQ9qRCLIEymkRTH5sYh9BPcrlkKG70Ed5oYCmlvg00QUyn4Yghukz6ED1Hh0veENYzFSTFPnpBsjXCuJuV+xXKRlBFLNXQliFCh2IC1tXbtZ+ppKmqboKLWZCMbdehvR1i7zax/efPj8FQjuDlYL0zMoIonNYGyLRSGp3rpH12Hjk6GYeLY+ez4zycBmZxbwrsutK7S1X07mn6Np5nOW/vDRD/ox9M/PfBJEgWjl8U9ua2g9MIzMbJfBbCR38yHzszE4a02BgeEsJUyk5TXVTZ
*/