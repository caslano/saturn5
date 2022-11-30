/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   from_settings.hpp
 * \author Andrey Semashev
 * \date   11.10.2009
 *
 * The header contains definition of facilities that allows to initialize the library from
 * settings.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_FROM_SETTINGS_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_FROM_SETTINGS_HPP_INCLUDED_

#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/log/detail/setup_config.hpp>
#include <boost/log/sinks/sink.hpp>
#include <boost/log/utility/setup/settings.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The function initializes the logging library from a settings container
 *
 * \param setts Library settings container
 *
 * \b Throws: An <tt>std::exception</tt>-based exception if the provided settings are not valid.
 */
template< typename CharT >
BOOST_LOG_SETUP_API void init_from_settings(basic_settings_section< CharT > const& setts);


/*!
 * Sink factory base interface
 */
template< typename CharT >
struct sink_factory
{
    //! Character type
    typedef CharT char_type;
    //! String type
    typedef std::basic_string< char_type > string_type;
    //! Settings section type
    typedef basic_settings_section< char_type > settings_section;

    /*!
     * Default constructor
     */
    BOOST_DEFAULTED_FUNCTION(sink_factory(), {})

    /*!
     * Virtual destructor
     */
    virtual ~sink_factory() {}

    /*!
     * The function creates a formatter for the specified attribute.
     *
     * \param settings Sink parameters
     */
    virtual shared_ptr< sinks::sink > create_sink(settings_section const& settings) = 0;

    BOOST_DELETED_FUNCTION(sink_factory(sink_factory const&))
    BOOST_DELETED_FUNCTION(sink_factory& operator= (sink_factory const&))
};

/*!
 * \brief The function registers a factory for a custom sink
 *
 * The function registers a factory for a sink. The factory will be called to create sink
 * instance when the parser discovers the specified sink type in the settings file. The
 * factory must accept a map of parameters [parameter name -> parameter value] that it
 * may use to initialize the sink. The factory must return a non-NULL pointer to the
 * constructed sink instance.
 *
 * \param sink_name The custom sink name. Must point to a zero-terminated sequence of characters,
 *                  must not be NULL.
 * \param factory Pointer to the custom sink factory. Must not be NULL.
 */
template< typename CharT >
BOOST_LOG_SETUP_API void register_sink_factory(const char* sink_name, shared_ptr< sink_factory< CharT > > const& factory);

/*!
 * \brief The function registers a factory for a custom sink
 *
 * The function registers a factory for a sink. The factory will be called to create sink
 * instance when the parser discovers the specified sink type in the settings file. The
 * factory must accept a map of parameters [parameter name -> parameter value] that it
 * may use to initialize the sink. The factory must return a non-NULL pointer to the
 * constructed sink instance.
 *
 * \param sink_name The custom sink name
 * \param factory Pointer to the custom sink factory. Must not be NULL.
 */
template< typename CharT >
inline void register_sink_factory(std::string const& sink_name, shared_ptr< sink_factory< CharT > > const& factory)
{
    register_sink_factory(sink_name.c_str(), factory);
}

/*!
 * \brief The function registers a factory for a custom sink
 *
 * The function registers a factory for a sink. The factory will be called to create sink
 * instance when the parser discovers the specified sink type in the settings file. The
 * factory must accept a map of parameters [parameter name -> parameter value] that it
 * may use to initialize the sink. The factory must return a non-NULL pointer to the
 * constructed sink instance.
 *
 * \param sink_name The custom sink name. Must point to a zero-terminated sequence of characters,
 *                  must not be NULL.
 * \param factory Pointer to the custom sink factory. Must not be NULL.
 */
template< typename FactoryT >
inline typename boost::enable_if_c<
    is_base_and_derived< sink_factory< typename FactoryT::char_type >, FactoryT >::value
>::type register_sink_factory(const char* sink_name, shared_ptr< FactoryT > const& factory)
{
    typedef sink_factory< typename FactoryT::char_type > factory_base;
    register_sink_factory(sink_name, boost::static_pointer_cast< factory_base >(factory));
}

/*!
 * \brief The function registers a factory for a custom sink
 *
 * The function registers a factory for a sink. The factory will be called to create sink
 * instance when the parser discovers the specified sink type in the settings file. The
 * factory must accept a map of parameters [parameter name -> parameter value] that it
 * may use to initialize the sink. The factory must return a non-NULL pointer to the
 * constructed sink instance.
 *
 * \param sink_name The custom sink name
 * \param factory Pointer to the custom sink factory. Must not be NULL.
 */
template< typename FactoryT >
inline typename boost::enable_if_c<
    is_base_and_derived< sink_factory< typename FactoryT::char_type >, FactoryT >::value
>::type register_sink_factory(std::string const& sink_name, shared_ptr< FactoryT > const& factory)
{
    typedef sink_factory< typename FactoryT::char_type > factory_base;
    register_sink_factory(sink_name.c_str(), boost::static_pointer_cast< factory_base >(factory));
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_FROM_SETTINGS_HPP_INCLUDED_

/* from_settings.hpp
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
*/