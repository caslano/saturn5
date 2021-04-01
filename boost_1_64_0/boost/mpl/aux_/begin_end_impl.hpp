
#ifndef BOOST_MPL_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_BEGIN_END_IMPL_HPP_INCLUDED

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

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/aux_/has_begin.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {


namespace aux { 

template< typename Sequence > 
struct begin_type 
{ 
    typedef typename Sequence::begin type; 
};
template< typename Sequence > 
struct end_type
{ 
    typedef typename Sequence::end type; 
};

}

// default implementation; conrete sequences might override it by 
// specializing either the 'begin_impl/end_impl' or the primary 
// 'begin/end' templates

template< typename Tag >
struct begin_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename eval_if<aux::has_begin<Sequence, true_>,
                                 aux::begin_type<Sequence>, void_>::type type;
    };
};

template< typename Tag >
struct end_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename eval_if<aux::has_begin<Sequence, true_>,
                                 aux::end_type<Sequence>, void_>::type type;
    };
};

// specialize 'begin_trait/end_trait' for two pre-defined tags

#   define AUX778076_IMPL_SPEC(name, tag, result) \
template<> \
struct name##_impl<tag> \
{ \
    template< typename Sequence > struct apply \
    { \
        typedef result type; \
    }; \
}; \
/**/

// a sequence with nested 'begin/end' typedefs; just query them
AUX778076_IMPL_SPEC(begin, nested_begin_end_tag, typename Sequence::begin)
AUX778076_IMPL_SPEC(end, nested_begin_end_tag, typename Sequence::end)

// if a type 'T' does not contain 'begin/end' or 'tag' members 
// and doesn't specialize either 'begin/end' or 'begin_impl/end_impl' 
// templates, then we end up here
AUX778076_IMPL_SPEC(begin, non_sequence_tag, void_)
AUX778076_IMPL_SPEC(end, non_sequence_tag, void_)
AUX778076_IMPL_SPEC(begin, na, void_)
AUX778076_IMPL_SPEC(end, na, void_)

#   undef AUX778076_IMPL_SPEC


BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(1,begin_impl)
BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(1,end_impl)

}}

#endif // BOOST_MPL_AUX_BEGIN_END_IMPL_HPP_INCLUDED

/* begin_end_impl.hpp
+52yujREBvRdhshds9kURgWad3oE8YlN0CBlh0jGsMJVVIGVb06z88w2FOuOj+n0aNU2hmtX7yxvIk3/0SoWp4WnIqK8KY+jOfr8tVM4TRQWYBY1G2sg3RnwB6pbhBjTX3nwNTgGxHQ5FRDMH7ct3qsN+WmDLd8WUIXK1CSEIjS4lEGqP9mYGD5SZ78N/BDCM9ND+V5uBN/26gG+5w9KgbUg7mVR8RRUcAjj0Ds/rx2QToTwrv7S+8Lhdy6xXKP3q8iyhLewauLq0wNGRT1Rs4R6NGoWG28PgwdoKxPfk27ILloINAE/qdYaV2Z/unosIDcDIsy3IOCvOk3V3PWcuo1sqjiPWqaLevW1ygdFtzu1p7LwP/0LJeVM8yZc/9r/X6Y+9CksA8KV+CbN1uCkQKnjoVfVH5O2ktUg+PPp58WPDPDFFB9py6FCtcHx+epVX4wxgHETG6oroKRUGnbvh35NUHTVOVg9zxzO2q9ZtJpLdGvkXtlHge5zcrCtGfblrQM8VLCxywyrE7tR4iaVpLV5uFqgh0F55oEvarIT2yERWleqnjb30cZG+A==
*/