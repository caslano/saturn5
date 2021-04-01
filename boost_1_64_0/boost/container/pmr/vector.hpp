//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_VECTOR_HPP
#define BOOST_CONTAINER_PMR_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using vector = boost::container::vector<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a vector
//! that uses a polymorphic allocator
template<class T>
struct vector_of
{
   typedef boost::container::vector
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_VECTOR_HPP

/* vector.hpp
1a/0XDaOnZIGXNuPJGy3XmVoaDqfJUhJZaJrl1EPD8Zt915ueawiAjRaLsKUT8DPNbw+wLV9IGzlg9PseL6Js1518ueKbXWHei3NXfVhZxuuXLH7t3ytKmkXBbz/eJbE+Yd4hmuFA+EhQDRE1lTK/9udKcMXBdXCFWc/BrJEfn01VOVuiJZ+1OtTq4ZgxWRXSjnyboCooeh1FV3CSHiIoYbMpRfKp3aFgYTZf8738sOxKN/mCV3sdYnUjX4FNtR6Sju6UsJjJXdJClc5Pg8dDXx29PQyoL5k/dgmOr73JKv8rcR2vYxl9ZtENU4buBNXGyecN02+yLRWfjY2Fah5nEu3FOIxaCuDPxVzFg4bZq57HBKofeofgiM8h/TgII7jT1BS0MHlOrcW5XHBkvgmO0vyJFE0lTwjC80KbJ1j9uS1WG+4sYmtC3LhgBULP0bP6J4VNu6kXZ8fdFQ2v5Kvzv5s4CbM26ZL/1j+H/M/1UTZG3DjbW9PdL3Or8sBuLeK9ArvRdT0e9YG8Zaf+lGoZ/bGe1ZJqEnfEBzsqW6r6onDZXYPSvE7UugcUg==
*/