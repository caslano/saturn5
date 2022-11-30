/*
 *                 Copyright Lingxi Li 2015.
 *              Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   text_ipc_message_queue_backend.hpp
 * \author Lingxi Li
 * \author Andrey Semashev
 * \date   14.10.2015
 *
 * The header contains implementation of a text interprocess message queue sink
 * backend along with implementation of a supporting interprocess message queue.
 */

#ifndef BOOST_LOG_SINKS_TEXT_IPC_MESSAGE_QUEUE_BACKEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_TEXT_IPC_MESSAGE_QUEUE_BACKEND_HPP_INCLUDED_

#include <limits>
#include <string>
#include <boost/cstdint.hpp>
#include <boost/move/core.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/exceptions.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_1(z, n, data)\
    template< typename T0 >\
    explicit text_ipc_message_queue_backend(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :\
        m_queue(arg0) {}

#define BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_N(z, n, data)\
    template< BOOST_PP_ENUM_PARAMS_Z(z, n, typename T) >\
    explicit text_ipc_message_queue_backend(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, T, const& arg)) :\
        m_queue(BOOST_PP_ENUM_PARAMS_Z(z, n, arg)) {}

#define BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL(z, n, data)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_1, BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_N)(z, n, data)

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief An implementation of a text interprocess message queue sink backend and
 *        a supporting interprocess message queue.
 *
 * The sink backend sends formatted log messages to an interprocess message queue
 * which can be extracted by a viewer process. Methods of this class are not
 * thread-safe, unless otherwise specified.
 */
template< typename QueueT >
class text_ipc_message_queue_backend :
    public basic_formatted_sink_backend< char, concurrent_feeding >
{
    //! Base type
    typedef basic_formatted_sink_backend< char, concurrent_feeding > base_type;

public:
    //! Character type
    typedef base_type::char_type char_type;
    //! String type to be used as a message text holder
    typedef base_type::string_type string_type;
    //! Interprocess message queue type
    typedef QueueT queue_type;

private:
    //! Interprocess queue
    queue_type m_queue;

public:
    /*!
     * Default constructor. The method constructs the backend using the default-constructed
     * interprocess message queue. The queue may need additional setup in order to be able
     * to send messages.
     */
    text_ipc_message_queue_backend() BOOST_NOEXCEPT
    {
    }

    /*!
     * Initializing constructor. The method constructs the backend using the provided
     * interprocess message queue. The constructor moves from the provided queue.
     */
    explicit text_ipc_message_queue_backend(BOOST_RV_REF(queue_type) queue) BOOST_NOEXCEPT :
        m_queue(static_cast< BOOST_RV_REF(queue_type) >(queue))
    {
    }

    /*!
     * Constructor that passes arbitrary named parameters to the interprocess queue constructor.
     * Refer to the queue documentation for the list of supported parameters.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_GEN(BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL, ~)
#else
    template< typename... Args >
    explicit text_ipc_message_queue_backend(Args&&... args);
#endif

    /*!
     * The method returns a reference to the managed \c queue_type object.
     *
     * \return A reference to the managed \c queue_type object.
     */
    queue_type& message_queue() BOOST_NOEXCEPT { return m_queue; }

    /*!
     * The method returns a constant reference to the managed \c queue_type object.
     *
     * \return A constant reference to the managed \c queue_type object.
     */
    queue_type const& message_queue() const BOOST_NOEXCEPT { return m_queue; }

    /*!
     * Tests whether the object is associated with any message queue. Only when the backend has
     * an associated message queue, will any message be sent.
     *
     * \return \c true if the object is associated with a message queue, and \c false otherwise.
     */
    bool is_open() const BOOST_NOEXCEPT { return m_queue.is_open(); }

    /*!
     * The method writes the message to the backend. Concurrent calls to this method
     * are allowed. Therefore, the backend may be used with unlocked frontend. <tt>stop_local()</tt>
     * can be used to have a blocked <tt>consume()</tt> call return and prevent future
     * calls to <tt>consume()</tt> from blocking.
     */
    void consume(record_view const&, string_type const& formatted_message)
    {
        if (m_queue.is_open())
        {
            typedef typename queue_type::size_type size_type;
            const string_type::size_type size = formatted_message.size();
            if (BOOST_UNLIKELY(size > static_cast< string_type::size_type >((std::numeric_limits< size_type >::max)())))
                BOOST_LOG_THROW_DESCR(limitation_error, "Message too long to send to an interprocess queue");
            m_queue.send(formatted_message.data(), static_cast< size_type >(size));
        }
    }
};

#undef BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_1
#undef BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL_N
#undef BOOST_LOG_IPC_BACKEND_CTOR_FORWARD_INTERNAL

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_TEXT_IPC_MESSAGE_QUEUE_BACKEND_HPP_INCLUDED_

/* text_ipc_message_queue_backend.hpp
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
*/