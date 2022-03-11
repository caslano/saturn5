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