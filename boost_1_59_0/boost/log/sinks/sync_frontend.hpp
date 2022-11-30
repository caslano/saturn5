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

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1(z, n, data)\
    template< typename T0 >\
    explicit synchronous_sink(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :\
        base_type(false),\
        m_pBackend(boost::make_shared< sink_backend_type >(arg0)) {}

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N(z, n, data)\
    template< BOOST_PP_ENUM_PARAMS_Z(z, n, typename T) >\
    explicit synchronous_sink(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, T, const& arg)) :\
        base_type(false),\
        m_pBackend(boost::make_shared< sink_backend_type >(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))) {}

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL(z, n, data)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1, BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N)(z, n, data)

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
    void consume(record_view const& rec) BOOST_OVERRIDE
    {
        base_type::feed_record(rec, m_BackendMutex, *m_pBackend);
    }

    /*!
     * The method attempts to pass logging record to the backend
     */
    bool try_consume(record_view const& rec) BOOST_OVERRIDE
    {
        return base_type::try_feed_record(rec, m_BackendMutex, *m_pBackend);
    }

    /*!
     * The method performs flushing of any internal buffers that may hold log records. The method
     * may take considerable time to complete and may block both the calling thread and threads
     * attempting to put new records into the sink while this call is in progress.
     */
    void flush() BOOST_OVERRIDE
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