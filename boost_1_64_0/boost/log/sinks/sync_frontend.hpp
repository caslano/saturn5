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
dJ+Pgp1Vl7gr7KPuJ6n/YbAXHAF7wzy9LtTrMXo9Xq8/h409nf/Q+aDJsAmmjsqHa/BXEy6Eh8PF8Bh4IxwEl8AceJO2o1u0Ha3Ucl8DL4W3w9l6vRCuhYvg3fBOeA/cADfA++B98CG4Eb4IH4fvwifgF3r9PXwKhs4JfBrWgs/CFvDPsJte94YvwEHwRngm3AXHwFfhDPgGvBzuhvPg9fBavdZzEvUdVd739zsnsW5A95ZA2VsCm8EGsA08FPYIhYEnwCZwGGwKJ8EW8Gp4BFwGW8M7YBv4B3gk3AiztH+1h6/CLvBT2A2GMncMrAGPhYfA42Bz2AdmwRNgV/V3DDwRDoQnwRz4O5gHB8Cx8BQ4EZ4Kp8Mh2j832fE8dartuI6+m5nQtbbjKbAZnAqPgFfp3oALYFd4Ieyu9j3gNHiqXp8Gp2t7ngFL4UUqny6BV6v7IjgX3qThboWXwhV6fTucCe/S6/d/5tzAM+YlmmLMHMw6zE7Ml/MS/6fPE/xn9ejrXJPo1KVfPCux3Pr0Ta9JrLBOfVfCDMFMxizGbMHswSTPTzTdMcMxF88/qFd/8Hfw9//++030/8cXlpT+Ct//C+n5pzO3mb45NJSWWLOLs9t1a686/M91ZT0+1i275LwJukcgg7Dzotzbt++oYevjti3WzRf2UNzNQ1HunTpr2MWtGf/EuvnCNiTs7ij3Dl0j6TbCbefDMW6+sI1xz3rE796pfTsN2wS32bFuGjYT9+cpj1JxZ4/CKM7XiS4y6ydpi8MPt+/309jlh9v0++no8KO3av30dfiRW9KzHD/KNFbv88tA9DcJKmFaM2Dau6hMv780SyMJrSPJjf28zqpft/SMoDsNszheGhRMBdPYHCeN5LhpULAVTKNxgjuNxvHSoGIqeh8Xx0kjK24aVGw50+gcqXM9G24xdd8MXgQfbsq7mU1DomdtSCrb/80iWc/axnrWueJ3fCCydjT3BlnvtudTnSXuJYF8ViDmYtZjHjctmB8Z51qr17Q9pz5xvriNCpxq0sxMVjpXYep4x3hO/e3FsesiIwsLxua79bYXO9ci7NlO2eI+LnCmqcs8X7JZg2E+13Oti9i47BmUE7L9+ho7rg+5H2b1Be6S68b2/MLP5LqO1SdpKNezvRYmQNrniN7TFsq9qdhf42WaytHnzmk6KyQftxNvfeq7ASH72PW8P4jbjZTT1bhr2Jjv8IwTP+8yx/uS1PXjpFkidgWBsnvL4d7K9CiKxH1Y4ERTT74wdSOmhtfN85VFQYlP9zlb2srRJoF/4sd++6asvM4O+VH3pt3s+YxSjzv0uzyT2ojObna+2u9Re92jkTNhwhRb3lUlvqDVHTlKrptQupXst3+qmpy8PNjcHEcewr+RUt4bxGdzyvNkSn0k7fga7jUTf6nq7zLxNzPUz/DbhhXTdDOOvzPwU1v93Ct+jjGVcGtCPKm4panbOnELiF262j2vdmmanwTMHLGbTk4GUv6kr/ajxf5l04iUrzCHcPZAFYmrtrpvFPd0saujdhvELih29dTuRZ9dqvHErreUVSr56J8yG4vdVZnvzKQPBWa8ntS4sugap6rbtxG3zIsOD9mrzqScV7ovTYycG7aC69WNmC/F77NqdmK+1fW3Xqa839qM0qX4mbU4kQW6Bhy9xtZcn53DHc9O3xAnFFbaX6hN1tU2iZ20PdojdrTHGHnbr5beR2g+Fe5TeTvjxv3kLQ++GHmr/f5u8fumlbfH3yzy1p6xeYO4fxQlb5t6d7tkrabrlrVLxe3twOnU9iXI2Tsxe73XXGvQxFN+Wat+neu+6XCluL8WOIV+NZ2QKzH3myPNh+Z1p7z130MLkQ8=
*/