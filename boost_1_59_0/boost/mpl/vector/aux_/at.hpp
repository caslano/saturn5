
#ifndef BOOST_MPL_VECTOR_AUX_AT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_AT_HPP_INCLUDED

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

#include <boost/mpl/at_fwd.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template< typename Vector, long n_ >
struct v_at_impl
{
    typedef long_< (Vector::lower_bound_::value + n_) > index_;
    typedef __typeof__( Vector::item_(index_()) ) type;
};


template< typename Vector, long n_ >
struct v_at
    : aux::wrapped_type< typename v_at_impl<Vector,n_>::type >
{
};

template<>
struct at_impl< aux::vector_tag >
{
    template< typename Vector, typename N > struct apply
        : v_at<
              Vector
            , BOOST_MPL_AUX_VALUE_WKND(N)::value
            >
    {
    };
};

#else

#   if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)

template< typename Vector, BOOST_MPL_AUX_NTTP_DECL(long, n_) > struct v_at;

template< BOOST_MPL_AUX_NTTP_DECL(long, n_) >
struct at_impl< aux::vector_tag<n_> >
{
    template< typename Vector, typename N > struct apply
#if !defined(BOOST_BORLANDC)
        : v_at<
              Vector
            , BOOST_MPL_AUX_VALUE_WKND(N)::value
            >
    {
#else
    {
        typedef typename v_at<
              Vector
            , BOOST_MPL_AUX_VALUE_WKND(N)::value
            >::type type;
#endif
    };
};

#   else

namespace aux {

template< BOOST_MPL_AUX_NTTP_DECL(long, n_) > struct v_at_impl
{
    template< typename V > struct result_;
};

// to work around ETI, etc.
template<> struct v_at_impl<-1>
{
    template< typename V > struct result_
    {
        typedef void_ type;
    };
};

} // namespace aux

template< typename T, BOOST_MPL_AUX_NTTP_DECL(long, n_) >
struct v_at
    : aux::v_at_impl<n_>::template result_<T>
{
};

#   endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_AT_HPP_INCLUDED

/* at.hpp
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
*/