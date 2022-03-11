/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sync_frontend.hpp
 * \author Andrey Semashev
 * \date   14.07.2009
 *
 * The header contains implementation of synchronous sink frontend.
 */

#ifndef BOOST_LOG_SINKS_SYNC_FRONTEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_SYNC_FRONTEND_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_LOG_NO_THREADS)
#error Boost.Log: Synchronous sink frontend is only supported in multithreaded environment
#endif

#include <boost/static_assert.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/log/detail/locking_ptr.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/sinks/basic_sink_frontend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1(n, data)\
    template< typename T0 >\
    explicit synchronous_sink(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :\
        base_type(false),\
        m_pBackend(boost::make_shared< sink_backend_type >(arg0)) {}

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N(n, data)\
    template< BOOST_PP_ENUM_PARAMS(n, typename T) >\
    explicit synchronous_sink(BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& arg)) :\
        base_type(false),\
        m_pBackend(boost::make_shared< sink_backend_type >(BOOST_PP_ENUM_PARAMS(n, arg))) {}

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL(z, n, data)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1, BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N)(n, data)

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Synchronous logging sink frontend
 *
 * The sink frontend serializes threads before passing logging records to the backend
 */
template< typename SinkBackendT >
class synchronous_sink :
    public aux::make_sink_frontend_base< SinkBackendT >::type
{
    typedef typename aux::make_sink_frontend_base< SinkBackendT >::type base_type;

private:
    //! Synchronization mutex type
    typedef boost::recursive_mutex backend_mutex_type;

public:
    //! Sink implementation type
    typedef SinkBackendT sink_backend_type;
    //! \cond
    BOOST_STATIC_ASSERT_MSG((has_requirement< typename sink_backend_type::frontend_requirements, synchronized_feeding >::value), "Synchronous sink frontend is incompatible with the specified backend: thread synchronization requirements are not met");
    //! \endcond

#ifndef BOOST_LOG_DOXYGEN_PASS

    //! A pointer type that locks the backend until it's destroyed
    typedef boost::log::aux::locking_ptr< sink_backend_type, backend_mutex_type > locked_backend_ptr;

#else // BOOST_LOG_DOXYGEN_PASS

    //! A pointer type that locks the backend until it's destroyed
    typedef implementation_defined locked_backend_ptr;

#endif // BOOST_LOG_DOXYGEN_PASS

private:
    //! Synchronization mutex
    backend_mutex_type m_BackendMutex;
    //! Pointer to the backend
    const shared_ptr< sink_backend_type > m_pBackend;

public:
    /*!
     * Default constructor. Constructs the sink backend instance.
     * Requires the backend to be default-constructible.
     */
    synchronous_sink() :
        base_type(false),
        m_pBackend(boost::make_shared< sink_backend_type >())
    {
    }
    /*!
     * Constructor attaches user-constructed backend instance
     *
     * \param backend Pointer to the backend instance
     *
     * \pre \a backend is not \c NULL.
     */
    explicit synchronous_sink(shared_ptr< sink_backend_type > const& backend) :
        base_type(false),
        m_pBackend(backend)
    {
    }

    /*!
     * Constructor that passes arbitrary named parameters to the interprocess sink backend constructor.
     * Refer to the backend documentation for the list of supported parameters.
     */
#ifndef BOOST_LOG_DOXYGEN_PASS
    BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_GEN(BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL, ~)
#else
    template< typename... Args >
    explicit synchronous_sink(Args&&... args);
#endif

    /*!
     * Locking accessor to the attached backend
     */
    locked_backend_ptr locked_backend()
    {
        return locked_backend_ptr(m_pBackend, m_BackendMutex);
    }

    /*!
     * Passes the log record to the backend
     */
    void consume(record_view const& rec)
    {
        base_type::feed_record(rec, m_BackendMutex, *m_pBackend);
    }

    /*!
     * The method attempts to pass logging record to the backend
     */
    bool try_consume(record_view const& rec)
    {
        return base_type::try_feed_record(rec, m_BackendMutex, *m_pBackend);
    }

    /*!
     * The method performs flushing of any internal buffers that may hold log records. The method
     * may take considerable time to complete and may block both the calling thread and threads
     * attempting to put new records into the sink while this call is in progress.
     */
    void flush()
    {
        base_type::flush_backend(m_BackendMutex, *m_pBackend);
    }
};

#undef BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1
#undef BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N
#undef BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_SYNC_FRONTEND_HPP_INCLUDED_

/* sync_frontend.hpp
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
*/