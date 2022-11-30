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

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1(z, n, data)\
    template< typename T0 >\
    explicit unlocked_sink(T0 const& arg0, typename boost::log::aux::enable_if_named_parameters< T0, boost::log::aux::sfinae_dummy >::type = boost::log::aux::sfinae_dummy()) :\
        base_type(false),\
        m_pBackend(boost::make_shared< sink_backend_type >(arg0)) {}

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N(z, n, data)\
    template< BOOST_PP_ENUM_PARAMS_Z(z, n, typename T) >\
    explicit unlocked_sink(BOOST_PP_ENUM_BINARY_PARAMS_Z(z, n, T, const& arg)) :\
        base_type(false),\
        m_pBackend(boost::make_shared< sink_backend_type >(BOOST_PP_ENUM_PARAMS_Z(z, n, arg))) {}

#define BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL(z, n, data)\
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_1, BOOST_LOG_SINK_CTOR_FORWARD_INTERNAL_N)(z, n, data)

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