
#ifndef BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED
#define BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED

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

#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/has_begin.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/is_msvc_eti_arg.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

// agurt, 27/nov/02: have to use a simplistic 'sequence_tag' implementation
// on MSVC to avoid dreadful "internal structure overflow" error
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300) \
    || defined(BOOST_MPL_CFG_NO_HAS_XXX)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct sequence_tag
{
    typedef typename Sequence::tag type;
};

#elif BOOST_WORKAROUND(BOOST_MSVC, == 1300)

// agurt, 07/feb/03: workaround for what seems to be MSVC 7.0-specific ETI issue

namespace aux {

template< bool >
struct sequence_tag_impl
{
    template< typename Sequence > struct result_
    {
        typedef typename Sequence::tag type;
    };
};

template<>
struct sequence_tag_impl<false>
{
    template< typename Sequence > struct result_
    {
        typedef int type;
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct sequence_tag
    : aux::sequence_tag_impl< !aux::is_msvc_eti_arg<Sequence>::value >
        ::template result_<Sequence>
{
};

#else

namespace aux {

template< bool has_tag_, bool has_begin_ >
struct sequence_tag_impl
{
    // agurt 24/nov/02: MSVC 6.5 gets confused in 'sequence_tag_impl<true>' 
    // specialization below, if we name it 'result_' here
    template< typename Sequence > struct result2_;
};

#   define AUX_CLASS_SEQUENCE_TAG_SPEC(has_tag, has_begin, result_type) \
template<> struct sequence_tag_impl<has_tag,has_begin> \
{ \
    template< typename Sequence > struct result2_ \
    { \
        typedef result_type type; \
    }; \
}; \
/**/

AUX_CLASS_SEQUENCE_TAG_SPEC(true, true, typename Sequence::tag)
AUX_CLASS_SEQUENCE_TAG_SPEC(true, false, typename Sequence::tag)
AUX_CLASS_SEQUENCE_TAG_SPEC(false, true, nested_begin_end_tag)
AUX_CLASS_SEQUENCE_TAG_SPEC(false, false, non_sequence_tag)

#   undef AUX_CLASS_SEQUENCE_TAG_SPEC

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct sequence_tag
    : aux::sequence_tag_impl<
          ::boost::mpl::aux::has_tag<Sequence>::value
        , ::boost::mpl::aux::has_begin<Sequence>::value
        >::template result2_<Sequence>
{
};

#endif // BOOST_MSVC

BOOST_MPL_AUX_NA_SPEC(1, sequence_tag)

}}

#endif // BOOST_MPL_SEQUENCE_TAG_HPP_INCLUDED

/* sequence_tag.hpp
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
*/