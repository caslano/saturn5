/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sources/features.hpp
 * \author Andrey Semashev
 * \date   17.07.2009
 *
 * The header contains definition of a features list class template.
 */

#ifndef BOOST_LOG_SOURCES_FEATURES_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_FEATURES_HPP_INCLUDED_

#include <boost/mpl/lambda.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

//! The macro defines the maximum number of features that can be specified for a logger
#ifndef BOOST_LOG_FEATURES_LIMIT
#define BOOST_LOG_FEATURES_LIMIT 10
#endif // BOOST_LOG_FEATURES_LIMIT

#endif

#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

#if defined(BOOST_LOG_DOXYGEN_PASS) || !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

/*!
 * \brief A type sequence of logger features
 *
 * This class template can be used to specify logger features in a \c basic_composite_logger instantiation.
 */
template< typename... FeaturesT >
struct features
{
};

namespace aux {

//! The metafunction produces the inherited features hierarchy with \c RootT as the ultimate base type
template< typename RootT, typename FeaturesT >
struct inherit_features;

template< typename RootT, typename FeatureT0, typename... FeaturesT >
struct inherit_features< RootT, features< FeatureT0, FeaturesT... > >
{
    typedef typename mpl::lambda<
        FeatureT0
    >::type::BOOST_NESTED_TEMPLATE apply<
        typename inherit_features<
            RootT,
            features< FeaturesT... >
        >::type
    >::type type;
};

template< typename RootT, typename FeatureT0 >
struct inherit_features< RootT, features< FeatureT0 > >
{
    typedef typename mpl::lambda<
        FeatureT0
    >::type::BOOST_NESTED_TEMPLATE apply<
        RootT
    >::type type;
};

template< typename RootT >
struct inherit_features< RootT, features< > >
{
    typedef RootT type;
};

} // namespace aux

#else

//! A type sequence of logger features
template< BOOST_PP_ENUM_BINARY_PARAMS(BOOST_LOG_FEATURES_LIMIT, typename FeatureT, = void BOOST_PP_INTERCEPT) >
struct features
{
};

namespace aux {

template< typename RootT, typename FeaturesT >
struct inherit_features;

template< typename RootT, BOOST_PP_ENUM_PARAMS(BOOST_LOG_FEATURES_LIMIT, typename FeatureT) >
struct inherit_features< RootT, features< BOOST_PP_ENUM_PARAMS(BOOST_LOG_FEATURES_LIMIT, FeatureT) > >
{
    typedef typename mpl::lambda<
        FeatureT0
    >::type::BOOST_NESTED_TEMPLATE apply<
        typename inherit_features<
            RootT,
            features< BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_LOG_FEATURES_LIMIT, FeatureT) >
        >::type
    >::type type;
};

template< typename RootT, typename FeatureT0 >
struct inherit_features< RootT, features< FeatureT0, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_LOG_FEATURES_LIMIT, void BOOST_PP_INTERCEPT) > >
{
    typedef typename mpl::lambda<
        FeatureT0
    >::type::BOOST_NESTED_TEMPLATE apply<
        RootT
    >::type type;
};

template< typename RootT >
struct inherit_features< RootT, features< BOOST_PP_ENUM_PARAMS(BOOST_LOG_FEATURES_LIMIT, void BOOST_PP_INTERCEPT) > >
{
    typedef RootT type;
};

} // namespace aux

#endif

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_FEATURES_HPP_INCLUDED_

/* features.hpp
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
*/