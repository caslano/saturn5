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
L4R/hOvhUbgZvgevVvdb4fvob4TH4C74Z3gY/hX+CX4A/wr/Bv8GP4JhHtoojIZ/hwnwE9gBfgqT4IewCwwnnhwYAc+GkXAmPI79ufAvMF/NtX3pPR6MZZb21Qd3PvaFCbAf9NdDlfrraKmH7uqvB2wNe8IYmAFjYXpdOOJoq4ZzhaN9B1Wr4ZyHOy9cqv7zYU9YAPvActgPFsGhsBhOhMvgZLgczoKlcCk8H14Ky+DlsNzkR+9bgP0t+XmScvPAp7Rd7Nd28QzsB78P/d+u3aDhnG35du2PiM8Dfwqj4EEtj1/BNvBlmAgPwR7wF3Aw/BkcrvrR8FU4Af4STlX//vjf1PgXWOL/tt4p+wiMgo/DdvAJmAqfhBnwe3Aw3A+HwqfhmaofC5+B4+H34Xz4LDwO3/SfzYf3avydUIc0/iu0XVwNfebbYXe4A2bCh+Ao+E24GN4JC9S8EN4Fi+HdsAzeAyvgvXAdvA9+Bd4PN6i7q+CD8BoN5zr4ALxB9dvgXniz6m+B18Bdqr8NXgvvUf1x+Ig5Ly7n78194vdpPseE0V/hNDgITtfxdQYcCefDc+BCWAYXQeYG6DGHPv1auBhuhXlwD8yH+2EhfBUWw2NwOWxNOkphGlwBs2A5zIWVsARW6/h30NGzv/BXWk9JUo8qp6ztvBomwxrYFW6HabBWx711sApeDGvhV+AauB6ugxvgJfASuBFeCjfBy+BN8Ap4P9wMH4ZXwcfgFvg9eAP8AdwGD8CvwYOajlfgKviq6rX969lT6tDS/hdoPz4XRsHzYCwsgW1gHiyBS2EZLNB8FMLLYJGmv0TH9+Vwi+qP+2jORGKn8UejztP4n9f+94L2vx/BOHgAng5/DMfBn8B58BXtXy/B8+DP4DI194/f+zS+WMv4/Wt9Hr6mz9PXob+c9qu/IZZyIg3ibzxsDSfANnA6bAsnwvZwEkxW805wMkyBObCnmqfDKTBT9cclPj27Bzpb7vB+jvKU8tL6eQG2gz+GcfCHMAG+CBPVPAkegJ1U76+PNI1nlKU+Xtfx6Lf6nHoLRsMj+rx5G7aH78BU+C7sCw/DQaofqe799VGl8bWx1MderY/7YSx8wDWv2eAvD8vzZ4/6uxsmwntgkuo7qV7D0XNi5NsSzjc0nFthV7gLdlN9qurN/FHDybSEc4eGsxsOgN+EA1U/WPVaHpyHarw8btJwdmp53Kz+WntIv/qr1PlZCuoT9TdQ62cY7AKHw5lwJJwNF8J5ap4Hs+AKeBq8CJ6pz4ez4JVwDNyi/q6HY+HX4Dgd/8fDd+Bk+D7MgR/AKdDxMM7DNnA67ABnwK5wJkyBubA7nAoz4Hw4Gy6Ac+FCuBBOgMVwIlyh5sd99W/Ob9BHtRwTULdoefxR2/H7UNYNtR3/Q8vpOEyCf4Hp8AQcCP8KM9XdEPgBHAE/gWPhp3Cy2ufAj+AM+DHMVXfF6m6FujsOsdMzG8jOa3pboSZoet/U8eVtHT8O6/jwjs43/gCHwXfhaar3j1sHNdxKy7h1u4Z7B4yGd+p4dbfOc/bA4aofofrJqs9Rfb7qC1RfoXqNn7MGjc/vFmn818EYuBUmwOt1fnUrTIM3wIGqHwR3aHpuguPUfDy8BU5V/XFIGjl7EFiukagzNP73NP4/aXn+WcvzuJbnMS1P9GYeE1dsnlcN5jFrtH9eoM+PdTABXqjjzkUwDV4Me8Ov6HxnPRwBN8Az4CVwPLwU5sDL4Sx4hc6DroZz4Ca4EG6GS+BVsFDti+BGuEz1x+FWIwtPWjX97Xzu/PNdr853db79KJTnic63H4dd4RM6rj8Jh8LvwcnqTspc2/vTcAl8BubDH8Aq+Dxcre513EM=
*/