/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   syslog_backend.hpp
 * \author Andrey Semashev
 * \date   08.01.2008
 *
 * The header contains implementation of a Syslog sink backend along with its setup facilities.
 */

#ifndef BOOST_LOG_SINKS_SYSLOG_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_SYSLOG_BACKEND_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_WITHOUT_SYSLOG

#include <string>
#include <boost/log/detail/asio_fwd.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/syslog_constants.hpp>
#include <boost/log/sinks/attribute_mapping.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/keywords/facility.hpp>
#include <boost/log/keywords/use_impl.hpp>
#include <boost/log/keywords/ident.hpp>
#include <boost/log/keywords/ip_version.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! Supported IP protocol versions
enum ip_versions
{
    v4,
    v6
};

namespace syslog {

    //! The enumeration defined the possible implementation types for the syslog backend
    enum impl_types
    {
#ifdef BOOST_LOG_USE_NATIVE_SYSLOG
        native = 0                  //!< Use native syslog API
#ifndef BOOST_LOG_NO_ASIO
        ,
#endif
#endif
#ifndef BOOST_LOG_NO_ASIO
        udp_socket_based = 1        //!< Use UDP sockets, according to RFC3164
#endif
    };

    /*!
     * \brief Straightforward severity level mapping
     *
     * This type of mapping assumes that attribute with a particular name always
     * provides values that map directly onto the Syslog levels. The mapping
     * simply returns the extracted attribute value converted to the Syslog severity level.
     */
    template< typename AttributeValueT = int >
    class direct_severity_mapping :
        public basic_direct_mapping< level, AttributeValueT >
    {
        //! Base type
        typedef basic_direct_mapping< level, AttributeValueT > base_type;

    public:
        /*!
         * Constructor
         *
         * \param name Attribute name
         */
        explicit direct_severity_mapping(attribute_name const& name) :
            base_type(name, info)
        {
        }
    };

    /*!
     * \brief Customizable severity level mapping
     *
     * The class allows to setup a custom mapping between an attribute and Syslog severity levels.
     * The mapping should be initialized similarly to the standard \c map container, by using
     * indexing operator and assignment.
     */
    template< typename AttributeValueT = int >
    class custom_severity_mapping :
        public basic_custom_mapping< level, AttributeValueT >
    {
        //! Base type
        typedef basic_custom_mapping< level, AttributeValueT > base_type;

    public:
        /*!
         * Constructor
         *
         * \param name Attribute name
         */
        explicit custom_severity_mapping(attribute_name const& name) :
            base_type(name, info)
        {
        }
    };

} // namespace syslog

/*!
 * \brief An implementation of a syslog sink backend
 *
 * The backend provides support for the syslog protocol, defined in RFC3164.
 * The backend sends log records to a remote host via UDP. The host name can
 * be specified by calling the \c set_target_address method. By default log
 * records will be sent to localhost:514. The local address can be specified
 * as well, by calling the \c set_local_address method. By default syslog
 * packets will be sent from any local address available.
 *
 * It is safe to create several sink backends with the same local addresses -
 * the backends within the process will share the same socket. The same applies
 * to different processes that use the syslog backends to send records from
 * the same socket. However, it is not guaranteed to work if some third party
 * facility is using the socket.
 *
 * On systems with native syslog implementation it may be preferable to utilize
 * the POSIX syslog API instead of direct socket management in order to bypass
 * possible security limitations that may be in action. To do so one has to pass
 * the <tt>use_impl = native</tt> to the backend constructor. Note, however,
 * that in that case you will only have one chance to specify syslog facility and
 * process identification string - on the first native syslog backend construction.
 * Other native syslog backends will ignore these parameters.
 * Obviously, the \c set_local_address and \c set_target_address
 * methods have no effect for native backends. Using <tt>use_impl = native</tt>
 * on platforms with no native support for POSIX syslog API will have no effect.
 */
class syslog_backend :
    public basic_formatted_sink_backend< char >
{
    //! Base type
    typedef basic_formatted_sink_backend< char > base_type;
    //! Implementation type
    struct implementation;

public:
    //! Character type
    typedef base_type::char_type char_type;
    //! String type that is used to pass message test
    typedef base_type::string_type string_type;

    //! Syslog severity level mapper type
    typedef boost::log::aux::light_function< syslog::level (record_view const&) > severity_mapper_type;

private:
    //! Pointer to the implementation
    implementation* m_pImpl;

public:
    /*!
     * Constructor. Creates a UDP socket-based backend with <tt>syslog::user</tt> facility code.
     * IPv4 protocol will be used.
     */
    BOOST_LOG_API syslog_backend();
    /*!
     * Constructor. Creates a sink backend with the specified named parameters.
     * The following named parameters are supported:
     *
     * \li \c facility - Specifies the facility code. If not specified, <tt>syslog::user</tt> will be used.
     * \li \c use_impl - Specifies the backend implementation. Can be one of:
     *                   \li \c native - Use the native syslog API, if available. If no native API
     *                                   is available, it is equivalent to \c udp_socket_based.
     *                   \li \c udp_socket_based - Use the UDP socket-based implementation, conforming to
     *                                             RFC3164 protocol specification. This is the default.
     * \li \c ip_version - Specifies IP protocol version to use, in case if socket-based implementation
     *                     is used. Can be either \c v4 (the default one) or \c v6.
     * \li \c ident - Process identification string. This parameter is only supported by native syslog implementation.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_CALL(syslog_backend, construct)
#else
    template< typename... ArgsT >
    explicit syslog_backend(ArgsT... const& args);
#endif

    /*!
     * Destructor
     */
    BOOST_LOG_API ~syslog_backend();

    /*!
     * The method installs the function object that maps application severity levels to syslog levels
     */
    BOOST_LOG_API void set_severity_mapper(severity_mapper_type const& mapper);

#if !defined(BOOST_LOG_NO_ASIO)

    /*!
     * The method sets the local host name which log records will be sent from. The host name
     * is resolved to obtain the final IP address.
     *
     * \note Does not have effect if the backend was constructed to use native syslog API
     *
     * \param addr The local address
     * \param port The local port number
     */
    BOOST_LOG_API void set_local_address(std::string const& addr, unsigned short port = 514);
    /*!
     * The method sets the local address which log records will be sent from.
     *
     * \note Does not have effect if the backend was constructed to use native syslog API
     *
     * \param addr The local address
     * \param port The local port number
     */
    BOOST_LOG_API void set_local_address(boost::asio::ip::address const& addr, unsigned short port = 514);

    /*!
     * The method sets the remote host name where log records will be sent to. The host name
     * is resolved to obtain the final IP address.
     *
     * \note Does not have effect if the backend was constructed to use native syslog API
     *
     * \param addr The remote host address
     * \param port The port number on the remote host
     */
    BOOST_LOG_API void set_target_address(std::string const& addr, unsigned short port = 514);
    /*!
     * The method sets the address of the remote host where log records will be sent to.
     *
     * \note Does not have effect if the backend was constructed to use native syslog API
     *
     * \param addr The remote host address
     * \param port The port number on the remote host
     */
    BOOST_LOG_API void set_target_address(boost::asio::ip::address const& addr, unsigned short port = 514);

#endif // !defined(BOOST_LOG_NO_ASIO)

    /*!
     * The method passes the formatted message to the syslog API or sends to a syslog server
     */
    BOOST_LOG_API void consume(record_view const& rec, string_type const& formatted_message);

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    //! The method creates the backend implementation
    template< typename ArgsT >
    void construct(ArgsT const& args)
    {
        construct(
            args[keywords::facility | syslog::user],
#if !defined(BOOST_LOG_NO_ASIO)
            args[keywords::use_impl | syslog::udp_socket_based],
#else
            args[keywords::use_impl | syslog::native],
#endif
            args[keywords::ip_version | v4],
            args[keywords::ident | std::string()]);
    }
    BOOST_LOG_API void construct(
        syslog::facility facility, syslog::impl_types use_impl, ip_versions ip_version, std::string const& ident);
#endif // BOOST_LOG_DOXYGEN_PASS
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_WITHOUT_SYSLOG

#endif // BOOST_LOG_SINKS_SYSLOG_BACKEND_HPP_INCLUDED_

/* syslog_backend.hpp
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
*/