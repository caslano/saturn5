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