/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unlocked_frontend.hpp
 * \author Andrey Semashev
 * \date   14.07.2009
 *
 * The header contains declaration of an unlocked sink frontend.
 */

#ifndef BOOST_LOG_SINKS_UNLOCKED_FRONTEND_HPP_INCLUDED_
#define BOOST_LOG_SINKS_UNLOCKED_FRONTEND_HPP_INCLUDED_

#include <boost/static_assert.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/detail/fake_mutex.hpp>
#include <boost/log/sinks/basic_sink_frontend.hpp>
#include <boost/log/sinks/frontend_requirements.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1(n, data)\
    template< typename T0 >\
    explicit unlocked_sink(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :\
        base_type(false),\
        m_pBackend(boost::make_shared< sink_backend_type >(arg0)) {}

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N(n, data)\
    template< BOOST_PP_ENUM_PARAMS(n, typename T) >\
    explicit unlocked_sink(BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& arg)) :\
        base_type(false),\
        m_pBackend(boost::make_shared< sink_backend_type >(BOOST_PP_ENUM_PARAMS(n, arg))) {}

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL(z, n, data)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1, BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N)(n, data)

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Non-blocking logging sink frontend
 *
 * The sink frontend does not perform thread synchronization and
 * simply passes logging records to the sink backend.
 */
template< typename SinkBackendT >
class unlocked_sink :
    public aux::make_sink_frontend_base< SinkBackendT >::type
{
    typedef typename aux::make_sink_frontend_base< SinkBackendT >::type base_type;

public:
    //! Sink implementation type
    typedef SinkBackendT sink_backend_type;
    //! \cond
    BOOST_STATIC_ASSERT_MSG((has_requirement< typename sink_backend_type::frontend_requirements, concurrent_feeding >::value), "Unlocked sink frontend is incompatible with the specified backend: thread synchronization requirements are not met");
    //! \endcond

    //! Type of pointer to the backend
    typedef shared_ptr< sink_backend_type > locked_backend_ptr;

private:
    //! Pointer to the backend
    const shared_ptr< sink_backend_type > m_pBackend;

public:
    /*!
     * Default constructor. Constructs the sink backend instance.
     * Requires the backend to be default-constructible.
     */
    unlocked_sink() :
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
    explicit unlocked_sink(shared_ptr< sink_backend_type > const& backend) :
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
    explicit unlocked_sink(Args&&... args);
#endif

    /*!
     * Locking accessor to the attached backend.
     *
     * \note Does not do any actual locking, provided only for interface consistency
     *       with other frontends.
     */
    locked_backend_ptr locked_backend()
    {
        return m_pBackend;
    }

    /*!
     * Passes the log record to the backend
     */
    void consume(record_view const& rec)
    {
        boost::log::aux::fake_mutex m;
        base_type::feed_record(rec, m, *m_pBackend);
    }

    /*!
     * The method performs flushing of any internal buffers that may hold log records. The method
     * may take considerable time to complete and may block both the calling thread and threads
     * attempting to put new records into the sink while this call is in progress.
     */
    void flush()
    {
        boost::log::aux::fake_mutex m;
        base_type::flush_backend(m, *m_pBackend);
    }
};

#undef BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1
#undef BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N
#undef BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_UNLOCKED_FRONTEND_HPP_INCLUDED_

/* unlocked_frontend.hpp
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
*/