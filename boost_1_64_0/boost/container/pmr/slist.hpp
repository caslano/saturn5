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
H0nwMnIza7bI+EFx+lwHPDYOzu9umMaXWB9ibFhH3AY6XoQmO59yMKX8oZBwLSomflDA+Cr4HoCBYKWyOUSu0q0LR04hbbraa7gN7WS+VoRUaL76lt0MzQEePEaGF7+F8+c3imNGgGHHnWtH3mjJNlsh1AZZlhwV/8WrceWEjHpSfnOSNAODaPQsi9cVENzvsUqZPoGGjS4RJu1XM7FgF7xfYSpQFMSFJPX+tm3CPRXQsgFmKqf0pNxGs9ahySTLLBPN+FknIm6H3b/1EGgZJdprR2aX5fM6WGT7jbLB7n9fceM+oPbRLj70j+FFI3KAL3ZFNUVLn4376xVCv500R737yHondm1fSw74R7EJO3219tAAI8l+AWE4OLx8VXCsoX2PFNpxnlg0BHXdapOi+hwduFh1tpCIyg/EcWvIbg9LExMypKKpHwkH4rLt3TDMGoRTHwuy+qPdJ36w4QAIMYUxtCZ8sK81pdUSDfhjhToxmCxiqbh1LZkipjYRzRvYkEuGNA0bvRfNdOIk4PA4u2Q7JFPfP0vnB/IBIR6SFuiJLqUI844wmNIkEQ==
*/