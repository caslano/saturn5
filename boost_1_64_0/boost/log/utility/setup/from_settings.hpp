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
qSqdBdkQgHKWvtIaSt/AMHv61iDsBnv6pPic1vmGGkrf6TB1+ZUp0kelqY7SV1ZD6Zsfbk/fcwhbrkgfqNBp+ZXXUPoujrCn73mErbCnD7KmztNXUUPp2x6hLj/tI1v6RLbTafq0j2omfZNr2dP3AsLG2tJH+SWH6YutZvr0u0Y5TFgLkC4O+0eETbamj/LTusyT+2OmShf5LLJUuRlTs9WyVAxr5Fdj+nT5qPbin+j0bpgpv5RFYjotMkuSHuu3IIt3heQH5e5eQnpSK5VB4Tl+C1KZz/oI+34Hd1hLLGqda9Wo34bML94FN8u7LG1zcJQ93y8jnvzK+Q7w2yL8tAWzQ/JLbl866quR1/rMK94DN/091j7YLtqez1fcssOV8xngN6rY1H7fkXwKt1pusBp51Nsv3gE3eYclfwkx6nosrZy/AL9xpbZ6JLevu2fVyKO1HvmeSvX4tSKfr7q/5ZXzGeC3UvhZj9s7SFhhV+pXrUYe9XrEO+Am77Dkb3cde/5eB39F5fwF+q015e9tT/6EXan/sgbyh3fATd5hyd/auqr6Ax6slL8Av9XCb60/YbflT8JWP39Sf3yHOX/Lz7Pnbz34UyrnL8BvvfCzH27z5I/s6n6YUo086v0Q74Gb8R7L3e+wWPsabyV+pHryWXnBa3y/4xKd3e3uzfcUM2QSAzQA7YZbPt+jXFjL+nVIXCTC5YBOtHDLAOCKVky4JR28f+W7fBzKMAeqQ1Et6+tLFte3jHHi8RC4Pzlqyra83vG9Nu259b1bDvRc6kt2N3BZ6JqSMa4pXY+B6nQMVJY7UN2K/mSY2aik7RXzbid1Q3EfB21ToRuqAXVrXQC8GNiI8myNKc/WnDqSmgJv5m/K9XKPBH1SocsnhXK9HYHxwE4mvhLyRSr47iHffGAtyvfpfKV++H5FvgLyFZr4NvjhyybfRPJNMvGV+eGbQ75byXebia/cD99Y8o0j3w0mvgo/fEPIN5R815n4tI98811JvqvI19fEF2vns+siJN9lJjn0ZPK1ED6rHPqF5LuI8tgXU26yNXW1taEurktMcpCpjC9O4rPKQd7H+O4HRou/Rx79AbMcpR/+6eSfQf6Z5J9l4i/2w38L+XPIP5X8uSb+Uj/8t5P/DvLfSf55Jv4yP/xp5E8nfwb5J5j4K/zwDyf/CPKPJP8onZ/zE1/8V5N/IPmvIf+1Jv4UP/yXk78n+XuRv7e5/smfoOCPI389yuPGczxJIH8yKJ/8SeRnXJwPQd6O8nIJJ6K0FNDgE1XLzf0/yMnVlIxcdeXjKuuQSn0/zCYbNxN1tgS0FlQOCjsJmTjQQNBk0HzQatBO0GlQwsfQJQUaA5oDWg56A3QIpJ2CrqlTQfm54BN8gk/w+X9+fqbz/5wpE6pv/999bv+x6dy+iOfeCznnWQAq64D1xzv63o/t6MByT123WfKxhJ+HNMFVrY+Gcdr1gel2MH4U/4GKvSEr77uylzQxX7PeWzfC8E67TfeWbqsjcYfH/mEdpBY6bSRceQe5gWvYVUsCuiRcX2P/Za4D2+iB6E5CPuCGfFBHXLy8T9OQFvndir/fpB6hKwx/q+zCQJ6112VC6oDuxoXh4h3eOkTDKkibmJMxqdBaf/Z6Ip+lnoTRXi8S1tmend9yYfzck7To/GvASOpT51+pKU95+bNwvjezyC2UUjDLmi9d989aCR+vPidg2uth320wyvBr0KIk1GloHVve9bO99cITIftwOl8MIvs4DljH2f5c5bIQnVDMd78IW38U/X9lRr6lGyr74J4d3j6Yre6DiMe5Tj4Ja9HJl5NRMAnpp/6Tv4l/f7WNth02fXvCq/f1L8R/kF13nu0=
*/