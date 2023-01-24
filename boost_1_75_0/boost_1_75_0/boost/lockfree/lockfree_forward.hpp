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
PhxpO6ndA2OddM+N2U0edKg3CvnwnQTG+DIibpd/lCepuJXyvlBUuQQ4vVedQKl9vw9EW+FWRoN88Alim5UBATSGp+co55wgFs8f1CD6BvkeiNOx+jnsc6n2CN7RXUrbBd153bk3FPzFfPpuTD+GUEznU+dabvjsLVBVJ9IY968EBp8M7q2JixHcnj11BKkc5O/PcoymNk3I9Io/d5M6KMtGYwgV78XUf7iCoD7qbGQJDL7OOX46A7QKmJCepkuUnCNaEFohv2G+BZCsTIPE75WwzdC8frvUS0wJVyBnePti3tb3W5eEOb0n64I+CuxbOXKprRXhKC3XZWRSU2I9iSQROrlHNm1zHkJFiXx55ihPKS8xNXctub2PSaCifNI31tnIylCnXUzEbrKMWJ1Yb/7z6j3KsPbR4cfOeFLPxhsZ2a39gtelmbuZ5YDyVA2y9I/Z45WlElCiH5fZ9HZQK/JBLWi3Zk4fTDkrooM8KxxCWar3BfMVxuC7fTBNWZ4M9Gd8cDm2h7ReacfbVYC2adR9F29FESaWU0YoG/oEJRY9ux9hIddm/FCdv1FBsSz05QcjjDkQobd56QpT48/j0seL1r+d+43zPz2gX7zvfDsRjO+usNzEHzFzSYKB3XhsHilD1h1veJG3o1+dDjo/wdpv+p55VmB8o8BEW/USNegFRnf4K8n1oeXhQ3byJaneCxYaB5SetHe9xrv5
*/