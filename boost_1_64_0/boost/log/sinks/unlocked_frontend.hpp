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
/2GN1P2+EOt+X4h139BdubWO1Z3Z14+i3X9MPaxJaXof/4vWhbuc50TW76vG6L7q5NGksdJdzmU1JaXLaoPWD829mB3F7aXORfYyJqzQyhh3wec/LGVsC6/crKF3Frt1cmu5pdzxG3rfwq19rVDj2ij2sa61wvyCmrxyswfTXeyryUWY9M9kCuORCO2f4Z7Y8Aj+j4mMDA9rHxkZmxwR3D/9beM93Nek0GbiQllXDK1t6NmQkPvptEp7P+2qA0We9tMlTt03Wvdb2s+QRsbpH1bqOjv/9keNbqQd7Q+xHeGu0fH3t5UB46+tfeE/9H143JrxdwF9aUcr//jbKeTxd3DaqR5/6+oxzlKPSVWmHgO/DRTVUB5rfzr6Kks9nmTMnVKl+7XyzLXWI2GGVo8N3ZXb6kvd6Viq5fkRdTAo6VSPpeUBZZbtGzB1zSkC9RTqOI18q6XMtMjcZWba5E3i/jtOe9mpbERG0VJm/n2qbWIXZy1D/AWPqWbcfkjsdjprbf3AGme52f9+QuxWME6OtPUL4zfBvW+ZJ0Vhwjgobi4ghP5mz3jKSswo5V7UZWuVpUSeSVRh58C63RAX+tm4yM85HrrPQZ7XxpHfSt1zq9L56IaVQXtuIeyz4afRfbbbsWt0n834te+z3Yldo/ts4je0+QnuTrrHdoXYl9qem/g9+R7bZrEvscq+bBe7+Y3trzG2hr6/9tbKz7+/Fspz0d029uv3WIfq+DlEn4Nx1e62UbOyOngOpeXZSdz1QW/t/4QT2pgZVx3amBlXHfozTt3qGeO6usj8F4yt+sxqtIyfiLO/D+YGlvGqgkbmGQurQ3sfzA2xrHOrQ3snwF2j85FV1U2/D+ZWhz5nxa2ZjzxLm+wT1/z3wUEhyK03r25D60+++cm91fZ5ZprKO4zWus/S98GDwXV/krnJL8XtYKn/Po3U/cEQ6/5giHV/sDq08fZgUB+jDngvP9V9zP4uOEjLeE97R34zde9xho5haea8RUUFpWwt2wxxM8VJ5d+B9rIlHEtZBJet1V2R6S+DxG4Mafc6KfZ5C/5DH9vUrasvnLTtT226zMuDyryo0bn48hp/W/9y5TQue9GD+Zw7Hvrtoa+/fPvtx3eGb01cP6hFTuN/UU7DN/YvhR1UTmOpf80QFqo+SvZ35WfuDU2FXWAPlQ/oDrNUP1r1k1Q/WfUFqvfLS+zTeCZY5CX6aTz9NZ5M2BUOhChnEDxDzc/Ufc/xotd9bLM+I383uHf6Cg3/KtgOboLxqp8Ir4FT4bVwLrxO5Seuh0vhNrgSbocXwR3wEngT3AivhptU7y/X/ZqePEu5Vmp6qmASrIWdYA0crvoRqh+n+vGqX6J6LVfedxuXQ7lQ47lI47kUJsP1sC/cIPWIudbjJXCM6o/DF8y7G/nR8OV9T8PfhTsfb4Nt4O1abz+EKfBOmAnvgRNd3zN4CE6D34a58DswDz4C8+GjsBA+puX+BKyGT2t5PwNv0PB3whfgLo33Nng/fFTlH55S8+Owyv8+AldqfmJURsnR+xW88BxtJ3M0H/NgLzhf62UhHAUXabtf7JJvWAELYRUs0niz/fNmOFTjjUAN13iXaz2VaPsv03JcAYeoXtsVc7rG++twDWeEhpOl/XUUzFL9aNVPUv1k1Reo3t+uDmo8oy3tKlvjGavxTNL0joc94AQ4RM2HwokaP3oNX5+1cKYl/LYafgeYDjvDDJgI+8MkOFTNh8FOcAbs3CLHcMrkGEKVYWiu/MJW5BPuQx1AHUG1viXaGYDKRZWhNqN2o569pUWOoeXX8juVvy9l/7+stOBU7P93dmJlvfBZhAnDHF+4OKnNkwvw/HZntAuwk8s=
*/