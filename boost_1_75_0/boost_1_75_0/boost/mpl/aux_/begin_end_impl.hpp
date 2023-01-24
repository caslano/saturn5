
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
kqCju6D71Uxdiq/ROD4oEFcvv1tDRzHHcEe7YvMZmEg2RnebWECvviNjVXprypyUoRhx677GU/qRNpUiapY7XT6eNCXqWOXL7RdDaj4NjQ7bCQqg6/gfTQw0HZxiZji6abaxVh9FAySBzjjHmamcd0sf3BT543a9e2Xt9hVdPicAqWRzqKcJSef4BFPlj+VY+EzjrRk4+zJytgs4GUm5FEWdSsYzlsQCrHSbGOoV0jLko2qHv7B54gNkbgdTxoXhrSeWFGKRNE+06XIGFXKcozbMFr+m2fbbnTB/Jr1vvNxIEKigjUidcvQJjchoPVWUBVZZEirzlRcUEM68nRSfoe3IkLZ8adn1liZffCC3xT4jmJrpOBzq1Zuj3S9Zkt2N/MxFpVKq+ICCSz+bliZLQdl4IEMsE3dFt0jFNaOB6RihIqz/p90E3e0n1lqNT3PeP0pFLa9ngs1KoN5wamOfF2Sp5XdLYHH/xy6q4WWjcmQZv4U/IOlkd0aVE7GlrAOjqiNbc7emo9lz7VqqHrJNPLaM529ojzjNjm8nc89D4nORtOI8nt9QcgbVz5KcqAl3WoS+irc3FY1BSU+v/bw88TFnZ77kSapQjA2yko3Ycmb0D60d6Wq2OSTEodJubYJ7C3ZeVfYuA5gjnysoNjq7jYFiQrCNohGBqyMLP99Qri0cRu7CO5vjrjzy3d3c8KdZuvxQFPclAJhQOm/g
*/