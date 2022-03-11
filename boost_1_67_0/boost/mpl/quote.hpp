
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