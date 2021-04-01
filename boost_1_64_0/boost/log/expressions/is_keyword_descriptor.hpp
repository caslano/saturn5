/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   is_keyword_descriptor.hpp
 * \author Andrey Semashev
 * \date   14.07.2012
 *
 * The header contains attribute keyword descriptor detection trait.
 */

#ifndef BOOST_LOG_EXPRESSIONS_IS_KEYWORD_DESCRIPTOR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_IS_KEYWORD_DESCRIPTOR_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Base class for keyword descriptors. All keyword descriptors must derive from this class to support the \c is_keyword_descriptor trait.
 */
struct keyword_descriptor
{
#ifndef BOOST_LOG_DOXYGEN_PASS
    typedef void _is_boost_log_keyword_descriptor;
#endif // BOOST_LOG_DOXYGEN_PASS
};

/*!
 * The metafunction detects if the type \c T is a keyword descriptor
 */
template< typename T, typename VoidT = void >
struct is_keyword_descriptor :
    public mpl::false_
{
};

#ifndef BOOST_LOG_DOXYGEN_PASS
template< typename T >
struct is_keyword_descriptor< T, typename T::_is_boost_log_keyword_descriptor > :
    public mpl::true_
{
};
#endif

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_IS_KEYWORD_DESCRIPTOR_HPP_INCLUDED_

/* is_keyword_descriptor.hpp
PFAGsYiODy6sn7/EOMSeZMjqzm3aDYNxjjrnPliPVjFM8bnWB/slqljzQktvdfyJLc//c9TZAHD5/96HG7wQM3IlWj2ol+52FO2FcjXVjb6JFop7aD4mVTncjGDT1gSFm+/sbROwALX5RhffQXD5jrC8sv83XuogRxGEYX3DhDiokBZi0V4ttT30hguiPKSlhVGwsXxBeJqnoZp+3M8mOost9lZzJGGsm3MkfTvMhToTKQMYDLaCf5C4QcXAMil++qI4SH0o4DMEKp1V3x9wwpaCS1Cv1x2oj+/zePsnlB91RJUKtvmTrK/5giejgpj/Lt+cSVbmak1EissLFbwZYkhxZPPVXmcvus5yduQYbjV7Xqq0FFFej/+znbjFBRfS9SukzgkN5ZYPAPd56fJuREz7bu0XGaQ5AAfXK2u5XcBinmF7jEcLdHI6G+h4YR6hHoAUtl3ui+GD03UIrKjkQXtmWlLaHrN4Z7I6rmLtWLlmeeYnPglZK24C4PzsTOREluAu681mxZVcXhc+pZ5z10brV5MmPVIt7pJkJNgnyVaDUW1b6wyC/YqEGg==
*/