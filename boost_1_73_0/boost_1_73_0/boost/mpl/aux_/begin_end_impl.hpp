
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
XtadhSl/TFbihHy1wkVQlSkWMRGFIZRGZKgZKsGVk2Y4XBC7+/76bnRx09+ler65vh0xYixmeHzhfeXL08yIZ2KeLaiP2TIv9F7vxih9znM4DEqBgeze3Z5i1bNCjqlUmNKomNI62ygLX5zk1L8sFRKxNkCwYheC5aXsIxEyr8WQZ04YLzK+TJE2LFusXUyFdmFQZ53mBqbO6UTjtXDwQO1xOTd2gvforA9P2NgJPqAiRG8m6BylH1lhux/Pb+8urn/ZCd6gIpW4/JK93Al2KOKVC1+Orb+ux38i5h6Kbo56iVK6NZ2AFJ4nAnKEAOkVOsc2pSaWuN1lh6jWExTVUhsHqpqOkS1J8kqUJTUYapQzsiRH7WFg2SXHer/CTs2kSPuNl4zh4pOxePKpd/T5yfJclJaRqm0gejbaG2ystAip+BbAktvIj0Pbh/Ecs7sTIMv/h1Ff53xJXGeDOOtSHAkL5mqzzsKsu20mjPFmMNUprlLY4Xqc9aHEoGhk7f3tDNlfTQeG46/RaPxLFEzW+mAmsLf9ya+7Y79uhL3vCtT+dhj/FW07tgd8Ym9+G2/b8XdN4ROOgwjnwWfCr7PVHW40G378+AUG8OIFyAz29vDjhz+A/b7GZ/vw/DksNzCn2jC5tTbjRuHS/mbL
*/