/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   basic_sink_backend.hpp
 * \author Andrey Semashev
 * \date   04.11.2007
 *
 * The header contains implementation of base classes for sink backends.
 */

#ifndef BOOST_LOG_SINKS_BASIC_SINK_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_BASIC_SINK_BACKEND_HPP_INCLUDED_

#include <string>
#include <boost/type_traits/is_same.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * \brief Base class for a logging sink backend
 *
 * The \c basic_sink_backend class template defines a number of types that
 * all sink backends are required to define. All sink backends have to derive from the class.
 */
template< typename FrontendRequirementsT >
struct basic_sink_backend
{
    //! Frontend requirements tag
    typedef FrontendRequirementsT frontend_requirements;

    BOOST_DEFAULTED_FUNCTION(basic_sink_backend(), {})

    BOOST_DELETED_FUNCTION(basic_sink_backend(basic_sink_backend const&))
    BOOST_DELETED_FUNCTION(basic_sink_backend& operator= (basic_sink_backend const&))
};

/*!
 * \brief A base class for a logging sink backend with message formatting support
 *
 * The \c basic_formatted_sink_backend class template indicates to the frontend that
 * the backend requires logging record formatting.
 *
 * The class allows to request encoding conversion in case if the sink backend
 * requires the formatted string in some particular encoding (e.g. if underlying API
 * supports only narrow or wide characters). In order to perform conversion one
 * should specify the desired final character type in the \c TargetCharT template
 * parameter.
 */
template<
    typename CharT,
    typename FrontendRequirementsT = synchronized_feeding
>
struct basic_formatted_sink_backend :
    public basic_sink_backend<
        typename combine_requirements< FrontendRequirementsT, formatted_records >::type
    >
{
private:
    typedef basic_sink_backend<
        typename combine_requirements< FrontendRequirementsT, formatted_records >::type
    > base_type;

public:
    //! Character type
    typedef CharT char_type;
    //! Formatted string type
    typedef std::basic_string< char_type > string_type;
    //! Frontend requirements
    typedef typename base_type::frontend_requirements frontend_requirements;
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_BASIC_SINK_BACKEND_HPP_INCLUDED_

/* basic_sink_backend.hpp
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
*/