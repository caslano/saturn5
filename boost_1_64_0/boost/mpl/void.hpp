
#ifndef BOOST_MPL_VOID_HPP_INCLUDED
#define BOOST_MPL_VOID_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/void_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

//  [JDG Feb-4-2003] made void_ a complete type to allow it to be
//  instantiated so that it can be passed in as an object that can be
//  used to select an overloaded function. Possible use includes signaling
//  a zero arity functor evaluation call.
struct void_ { typedef void_ type; };

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

namespace boost { namespace mpl {

template< typename T >
struct is_void_
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_void_<void_>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template< typename T >
struct is_not_void_
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

template<>
struct is_not_void_<void_>
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

BOOST_MPL_AUX_NA_SPEC(1, is_void_)
BOOST_MPL_AUX_NA_SPEC(1, is_not_void_)

}}

#endif // BOOST_MPL_VOID_HPP_INCLUDED

/* void.hpp
frNRzj48Qh9hUsWOMXZ90N4XcJlD1yuyvHfjgWJLXPS5WgfMzLSaQ1mHWPi5CU4u7bE4+elakhB9/rHrIsa/S66vF++tTLy9lKQQLgkKaXKg/Bo8XSLuVS8e0E741DMSOM5NEYMIP8NpXDRPXizp9aL9siw8iYbdqF6lau+q2G9N12JK7fyNAQRLg2Ble38MtdevqtYgDRGGeZS7Yrg77GV1Sg68fBh4POl52Eo43KZRmmP018fy9MCNtEPGblPHcpC80ecxDQxuVOWn+G7jRoXEPDnUPKUaYE77mxhC8MhbQrOpHqNW0LekR80vOAoTUIGPlM2nefBw9oWx6GVNBG+1hKNju51oyd8QGoAN4ZMcAOlEO5xL8y78ZqLdtWhXbCtaROVv+0oqQdzc0l6gpzrS5tCOsm6X5Qs80DnziyH7UakNFeMyl+oyMh56KNpjR4lJFis4s8s+OxDh2QSeleFuwV9R7OE9VcvAvtdEeXs81tirT/bwwPW0aMuAtv3hibBRGgtAXkF51sz1sXajXc0VWvtl3eixrqfjCdSgcwA3VfSfGKZwV5UR3sQsxxbQMbth81HAYEf2sc7/TnHfZOtzLP3HVZqYEDuaP4nMG6hIjuVo/0PCHawDguE/uCl1zGbpP8Tuv3sq/RdH9t/+cPr/4fcx+2/7eQr9f/hJ5PjfPbT+czD+30t80k5iixEcmSov3zsNKAZqG9ulMo5LconR306tuYj92sytXMuAksVBZqctIaFpCZ4zNcjuDEhnmS/qr6UqZpGHNnXYC598HugN12hy6rdp1pHczycgr2R/2VBqh8YeEQ+3jror60pTwK3fm6ZPBPS9K13wWWtWOMPvH4H2Z+L7sYWcyTqm/hO9v/Wsb3E1mvUmQkIRBkkpi7zHj4Yk+gHP/E7Sb+vXYzdYHhhJHaoh7I8gDd7efSAVYZr9fVH4O94v7DH8RuBvwos+8AJsOB/8RI3zIV/whZspTOajrU5O+sr6KIrRDDsbKfmKIff4naLi0qkgRZteX7758GyC9fxU7ZDz89Ab9vnh4WSrU6iP2AfPHGhIxTWXnp9e1H4APaD+JUAR2uE0erlBz3/PN6XfidcUMHUEAZxQ1w3MmNac6AwZV1lcmJUtWVmBGmOv4iLNGe4sWT50PJih7g/AnBss5fp3U7vPtyR4L9SuSs5vnPBMbH7j139M/h6Z8we0H5ee7ADCwAN8oiSDfqICn2lc7RDq0zQ9U33Y9YXfbPOxxbp+Iv+3H7H8eTq7id9iSJrTGzjBGEkEALVIJ4L4KNjqXv3cCpxI2fBNOJMp/9veVXRdmUQKfHB+v8NOq5adHOjJFW9SFUdwxUAvpONsvv6qejKcAqdetULtqoqUxOnmSftYtlcT6IsaQMGVXOOo+rvl+OdErspggO2I88QoIDAUPUPW2EWNrz5wmhxB7Yf7iMNoG3e9cscyIjBcTdssHv3Id3j0I6yxrH8FNQOnIwkaZ6s4CXJM2I9UyViv5uwnAZRStUfp7x7nBs60ZvRqbiCluzeVD/affvXyPvTh+SO4wfNWyVOVsPwxardSjelPyc2azL7o2t9CnyuCnj/VyTd3iINWTyOSgS/6cBPqgkNuckkvlYTF6NCXFUIjY8vFlDq9g/wSHE0r1STYg/7mBM+kv8HgKeFiyuyRRpnD6ctH9GXaafRlh/hycrg/wSOM+LVZcfh4SjlG0LPt6Mt48cVHX0aqR0wRfWFN+WURvvkmCzPwAKJ4mZctUl79xhMJzfHqT5/uF3+DwsFPk2A7+tsq2Co8gP4NBtvNLKsF+B3CJ9KKz3zfQT+Emnc7mDWzWUZY6A/MfM/hhqv/w8G7h/tR+FivOIc=
*/