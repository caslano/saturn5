/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sink.hpp
 * \author Andrey Semashev
 * \date   22.04.2007
 *
 * The header contains an interface declaration for all sinks. This interface is used by the
 * logging core to feed log records to sinks.
 */

#ifndef BOOST_LOG_SINKS_SINK_HPP_INCLUDED_
#define BOOST_LOG_SINKS_SINK_HPP_INCLUDED_

#include <string>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

//! A base class for a logging sink frontend
class BOOST_LOG_NO_VTABLE sink
{
public:
    //! An exception handler type
    typedef boost::log::aux::light_function< void () > exception_handler_type;

private:
    //! The flag indicates that the sink passes log records across thread boundaries
    const bool m_cross_thread;

public:
    /*!
     * Default constructor
     */
    explicit sink(bool cross_thread) : m_cross_thread(cross_thread)
    {
    }

    /*!
     * Virtual destructor
     */
    virtual ~sink() {}

    /*!
     * The method returns \c true if no filter is set or the attribute values pass the filter
     *
     * \param attributes A set of attribute values of a logging record
     */
    virtual bool will_consume(attribute_value_set const& attributes) = 0;

    /*!
     * The method puts logging record to the sink
     *
     * \param rec Logging record to consume
     */
    virtual void consume(record_view const& rec) = 0;

    /*!
     * The method attempts to put logging record to the sink. The method may be used by the
     * core in order to determine the most efficient order of sinks to feed records to in
     * case of heavy contention. Sink implementations may implement try/backoff logic in
     * order to improve overall logging throughput.
     *
     * \param rec Logging record to consume
     * \return \c true, if the record was consumed, \c false, if not.
     */
    virtual bool try_consume(record_view const& rec)
    {
        consume(rec);
        return true;
    }

    /*!
     * The method performs flushing of any internal buffers that may hold log records. The method
     * may take considerable time to complete and may block both the calling thread and threads
     * attempting to put new records into the sink while this call is in progress.
     */
    virtual void flush() = 0;

    /*!
     * The method indicates that the sink passes log records between different threads. This information is
     * needed by the logging core to detach log records from all thread-specific resources before passing it
     * to the sink.
     */
    bool is_cross_thread() const BOOST_NOEXCEPT { return m_cross_thread; }

    BOOST_DELETED_FUNCTION(sink(sink const&))
    BOOST_DELETED_FUNCTION(sink& operator= (sink const&))
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_SINK_HPP_INCLUDED_

/* sink.hpp
f/2muNeyz51zHxBdJDvGXS/XVV11rXG79zx8JG7t9ZrZkQdj20V+wdjSHCvfhko6z6ss8sxjEr7YO8yc6KWWtaWcyRKsbD/KRvE3xdtksli3TDBjvUQr9x5WtwzCF0t43gVLmDamjs4vmmDHt9/jN5xeadzx7Y/izswfd9tQ2+5esTuWVEeYSeYk9ADamjrUapqNo6RwKocbFo6TI3asrnyW3GtT0R7kyaL2PCnEfp1JJa4ppjXUeELtR3McebYUid8ruOuhJpM+U8X2GZGFGCsT7XdCq/6MHKQOyvoM1+F2anJG5RSON//EWW1NErCT9qbv7NqPNugkSWhtPWQxPcRQP5I2MmN/QShTNX69u2L7bjRjs7yfuWSfxufF1RdOkLBV3P3mwf3OeZXBibMfWL/useYJkk66e6yp4Z3Pfr3HdeJ+uHOcacPa5/V55LMs7Ivivtq+Fyc9JPPBto+8Lu7Hx56lat9/HxD3Qi/eOHWbuL9Upksr9zqNOx1Ffdk82X6+U/wP9PWzYulo9hufEv5kiS/dxjfWHIJdWZjzNIzO9YqfZmVjX7ku5plyqhlA30h1fO9zQsPYcbDYyRj4yMZ2LIEROx0bl68fkeeo8YSUufMbfcXlGBOH2l3FxsSRs9iGNDTyW6Njjrswteln8yQ/M84vLB3P+av+fnW+ydR6vVn83GDSqclWoTlfYr7cVOHckQT3OtJD5dMNxl/se1074/t+7p/FvcCE9m4NIcQ5ppKrz9l4Un3x6JyFq4/hP3b9aowdR30gbv1Nd1ONNbfKrn5GeHcfzdR+tlDcV9EKmeXHDMAsxtyCca19+OObJfHJvJP4beDz28DnN7JH6VDa5Ok6N/I5Jvx3efTJ/W3v/Fh96Nh3MV1jiJof980L+c8aG+M8uxc7uZdZITu5v/+Mc7uSngjFs2/KaX+9sm7XgVOyFnyxu/EZrQ6e2/XffG7XbaF5PzgY8zmm2K5Fyzq6uFXHSOPVb+aFOBhWVd3eOno+VBrMg/Xg2bCFXrdUnd8seCbspTq/x/vOk5rt6bqmrj1Phm31jKjIeVdJvm8kFsFn9byod+AE+CHcorrFJXqu00T4LZyk5xhN0fOcpqpu6DTYFP4ettZvKLaHM1VX9CLVdbwUjoWXwal6LtSF8Ao4E14J58G5cD68Ci6D16rO8SL4KFwM/6rnTL0Bb4RvwyXwYz1n6u+qo5kQoH5gGlwF68PV8HB4F+wG18AeUHQ04b3wNBgKXwA3wQnwAXgpfBBeATfDa+FDcAl8BN4Kt9jzvWTtKu65YI9rO3gCZsAnNdxLnq5l6NpSKFxXzA6tx2dUd3g7rK06w/Xhn2B7+GfVHW7ucd4afIHrE+Bf9Jyol2Ae3AWLYchfKXxF6+NVrY/XVBf3dbgI7oY3qvtt8G34PHwPvgrfh3vU/nv4JvxR4w8EeNaF2g38SOvhE9gEfgrbwM+0HvbCE+CX8Az4NRwDv4WT4XdwBtwHL4E/abkb0tkEPfgnWAnugpXhW7Aq/BusDkMVkQRTYE14GEyFvWFteAKsCwfAQ2AODIUbCRvA8bAhnAQbwemwMbwUNoHz4GHwetgMLofNoeq86xyt5G0/nXfKUOr3fdgQfgDbwY9Vl/Zv8Fz4herOfgVnwq/hHPgtvAp+p7qzJoDObAjwARiEj8BKUNKET4PK8CVYE+6GyfADmAI/gtXhV+r+vboneOKu96XzgXCU4776eGH5czLsqLrHPWB/eIrqII+Fg+FFcKjm/0y4Fg6DW2A2/AQWwH2SVlhnfTRMgufCFBhyz4CheDrAYtgDToAnwhJ4EhwHT1X34epeIO4qVyNzSzqHNjnmG6stPf2WLmwMO/g=
*/