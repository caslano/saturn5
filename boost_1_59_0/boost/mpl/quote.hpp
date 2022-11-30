
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_QUOTE_HPP_INCLUDED
#define BOOST_MPL_QUOTE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/void.hpp>
#   include <boost/mpl/aux_/has_type.hpp>
#endif

#include <boost/mpl/aux_/config/bcc.hpp>
#include <boost/mpl/aux_/config/ttp.hpp>

#if defined(BOOST_MPL_CFG_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
    && !defined(BOOST_MPL_CFG_BCC590_WORKAROUNDS)
#   define BOOST_MPL_CFG_NO_QUOTE_TEMPLATE
#endif

#if !defined(BOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS) \
    && defined(BOOST_MPL_CFG_NO_HAS_XXX)
#   define BOOST_MPL_CFG_NO_IMPLICIT_METAFUNCTIONS
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
 && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER quote.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   include <boost/mpl/limits/arity.hpp>
#   include <boost/mpl/aux_/preprocessor/params.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   include <boost/mpl/aux_/config/workaround.hpp>

#   include <boost/preprocessor/iterate.hpp>
#   include <boost/preprocessor/cat.hpp>

#if !defined(BOOST_MPL_CFG_NO_QUOTE_TEMPLATE)

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T, bool has_type_ >
struct quote_impl
// GCC has a problem with metafunction forwarding when T is a
// specialization of a template called 'type'.
# if BOOST_WORKAROUND(__GNUC__, BOOST_TESTED_AT(4)) \
    && BOOST_WORKAROUND(__GNUC_MINOR__, BOOST_TESTED_AT(0)) \
    && BOOST_WORKAROUND(__GNUC_PATCHLEVEL__, BOOST_TESTED_AT(2))
{
    typedef typename T::type type;
};
# else 
    : T
{
};
# endif 

template< typename T >
struct quote_impl<T,false>
{
    typedef T type;
};

#else // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

template< bool > struct quote_impl
{
    template< typename T > struct result_
        : T
    {
    };
};

template<> struct quote_impl<false>
{
    template< typename T > struct result_
    {
        typedef T type;
    };
};

#endif 

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <boost/mpl/quote.hpp>))
#include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_QUOTE_TEMPLATE

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_QUOTE_HPP_INCLUDED

///// iteration

#else
#define i_ BOOST_PP_FRAME_ITERATION(1)

template<
      template< BOOST_MPL_PP_PARAMS(i_, typename P) > class F
    , typename Tag = void_
    >
struct BOOST_PP_CAT(quote,i_)
{
    template< BOOST_MPL_PP_PARAMS(i_, typename U) > struct apply
#if defined(BOOST_MPL_CFG_BCC590_WORKAROUNDS)
    {
        typedef typename quote_impl<
              F< BOOST_MPL_PP_PARAMS(i_, U) >
            , aux::has_type< F< BOOST_MPL_PP_PARAMS(i_, U) > >::value
            >::type type;
    };
#elif !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
        : quote_impl<
              F< BOOST_MPL_PP_PARAMS(i_, U) >
            , aux::has_type< F< BOOST_MPL_PP_PARAMS(i_, U) > >::value
            >
    {
    };
#else
        : quote_impl< aux::has_type< F< BOOST_MPL_PP_PARAMS(i_, U) > >::value >
            ::template result_< F< BOOST_MPL_PP_PARAMS(i_, U) > >
    {
    };
#endif
};

#undef i_
#endif // BOOST_PP_IS_ITERATING

/* quote.hpp
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
*/