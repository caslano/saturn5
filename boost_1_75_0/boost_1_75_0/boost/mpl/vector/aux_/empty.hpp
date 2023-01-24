
#ifndef BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct empty_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : is_same<
              typename Vector::lower_bound_
            , typename Vector::upper_bound_
            >
    {
    };
};

#else

template<>
struct empty_impl< aux::vector_tag<0> >
{
    template< typename Vector > struct apply
        : true_
    {
    };
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct empty_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
Wu32qXoIHmRTJ/OF0xV6FjeLB/bYcTy1L4gXTvhHC7gFE56qD2FxpL/fNhgjBn/0SA0HJG/TGVZ/ijdBWOKM/qkDFEKnZX5qVoHCYEuHaXxyYDLnHBi7QvET88+wPhTF+rnUZeobBbZ7Z9ZrN7T10bYjyAqCDi/e11tF6N7y0ngYF1rHuO01F7SdeHg4tBRMpGjrpcgJvGEmXyjDoFX2C15tWo+GpCRZJpbMJ6Da119QjMD95qd16MyP9qA32LfXaryVaY0sTqtPtlJMc62J+B2OFxSk9BaBhONIZrcyrkkC9HNbzEUaKFO011/zaEbLJO6doJZZ+05KZ0Hd8wVWoy0sZ6iZGn8Er3OGIjSrRgeIC2jZIaKEJ7IrzPGkcY4JNF9Qdx/jq/7Ul76oHCSgvAabbNiu8xNcn/4lO4pX8zccIVGYn08I6W6rVo8eFmV4VpNWl52aqNQlb3je6uioZoIMDUItfpa8y15eaVteO+Ty14NKkFI0HXPkNcsze+pxd+MYYWxzftVsZGMIYQIIYgQTVNac1/1RPSofvISE2YnhngaEGRJAZjGDSUmoULdPTXnB/MfnEk0Ay5MXIzUok+Ljp3oRbtEI2SiRy8xd8ngvikX0zRqXIoC6wga6Xk303YJnloQ0GGBtCAiemol8Vi5aw0ZzpraZSU3tTnSFjl7M7LWqltSiu8Qxfp5ngqBH552I8tHRo8bpS9s/
*/