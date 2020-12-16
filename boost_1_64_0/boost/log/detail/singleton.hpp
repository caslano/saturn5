/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   singleton.hpp
 * \author Andrey Semashev
 * \date   20.04.2008
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_SINGLETON_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_SINGLETON_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/once_block.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! A base class for singletons, constructed on-demand
template< typename DerivedT, typename StorageT = DerivedT >
class lazy_singleton
{
public:
    BOOST_DEFAULTED_FUNCTION(lazy_singleton(), {})

    //! Returns the singleton instance
    static StorageT& get()
    {
        BOOST_LOG_ONCE_BLOCK()
        {
            DerivedT::init_instance();
        }
        return get_instance();
    }

    //! Initializes the singleton instance
    static void init_instance()
    {
        get_instance();
    }

    BOOST_DELETED_FUNCTION(lazy_singleton(lazy_singleton const&))
    BOOST_DELETED_FUNCTION(lazy_singleton& operator= (lazy_singleton const&))

protected:
    //! Returns the singleton instance (not thread-safe)
    static StorageT& get_instance()
    {
        static StorageT instance;
        return instance;
    }
};

//! A base class for singletons, constructed on namespace scope initialization stage
template< typename DerivedT, typename StorageT = DerivedT >
class singleton :
    public lazy_singleton< DerivedT, StorageT >
{
public:
    static StorageT& instance;
};

template< typename DerivedT, typename StorageT >
StorageT& singleton< DerivedT, StorageT >::instance =
    lazy_singleton< DerivedT, StorageT >::get();

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_SINGLETON_HPP_INCLUDED_

/* singleton.hpp
J9dBnJBrSdS2ifWSVqHl0+29suUio/7C6PRD5Pwlxq41SPxTsZy0snz7rV8rssVWoP4a+H3GADn/oLVZ1zfXEFL+4jpqg9PcZ7C0+tQZGZeVdH39v5z0UfosskESZs8Z1K26PGghT1+T+cCEcX1endj2wTenxHuanB3d6nHffamf0Zm6/h7UjVFBr6FdDebDDDgc1oJPwNp6PLYO/A7WhSfhuTBW7zudBBvCAtgI9oSZsA/MgsNhDhwP87TO1Aw+Ac+Hz8GWp6nDzI3oMJEjckSOyBE5Ikfk+C8+zpr+P2jwGdH/VxDXtxfPEa3/f2vxYg8/gg3R/7e8ZfR/ss0JNgKEsQFUgs/81RvvQ0cbAGk62wD0ON9eOf++0V8/eCvYBvCUpD2VtC8yNoAtIvurquZsAyDP07MBBJRR2wAYDFV+/f+gnH/TlHEffkf93zmtbBWgrx+W86+YtA7ptBx0f6e0ciQtPQZ7XM5vNmkd0Wk56PmkVbJd4pScX2vsEifE39+qoVqIXSItIL00nZ6jXULrvEnSRo+Ysk1/W9sldJ+Jk/OLrMfV36W8GQHpZ0j6p2eXSJH05lhVKO34EuwSNSVcO1UfiW/+RBeRDaCsUWqWilcNrGpmjPg2Kfc5Zmy3QMKWc7RT3M85wlp5jDGvVx2NnaKhpNGH+6Grk51C2mq9xL3H2CmU1mF9+faR872scPaCBDnfwdh9POK/ldpoZ+wFFUS2JKy9wJLzy6yhVo6ej++7/jhjJ1iZoceyz5KdIDnITsB9qWUV/LJsnyzVL8vxydIcbAkZpbAl7D6DtoTbxZbw0pW9rp7edO7Av69YNUZ1Sfj17NgSnvfdS/p5n6mfLSsD9jdqDTNgP1gdToG14QZYB74H68IoK9iGUA02gHVgQ1gPZsKOMAv2h9lwOMyFo2ETOB3mwbmwOVwKW8CtsBV8A7Y+TdvC6ohtIXJEjsgROSJH5Igc/+bjLOj/Q+TvfledEf3/qYD9/6br+f+PxfPuC5fAPk14d3tZ9H9fviMH6X3Sxwfp7Xos9w35pt553P/lEL11bOC82ovk/EHn8XsdN1nrKOwDPvb6AaMyHXX38OGzAu0ThRJmSrzjeP3LxefbjzHl3CTXeI5qpK85c5vXPyu2izqs5lqH1Rv2YZXgPqwKog6r6Z7Danv0CZUSmyLh5Xt8STsxfp/VRVV1dVF93V3U/VFdmCbbRVWK6aK6kdLiuMsD8h6vCnTenbfKt9GxzC5WT+A6WvPVIdyd9nxVxzVfbcMNcs9Xrqj56s+4tp75ah9uavR8VTVmvtoQc7+6S+uCvSWtXbEutJjLsJkspyZ/ZeZjgeVGYy5UX6AlNrIL1XTbrV6HVV1uNcxVqLbDeHehGux2qyfgL26PGhDVVD0S5VaHogpVG49H3ekpVPs9blUnulBNiXarbbBajFsNiumk/hITrWJjC9Wg2Nig/cHr6GvsL/V7MaViXj89pyKsAc+DTWnd2bre86X8leIoP61xm3oIrkJTv8CyGVWfpT6G/4A32ey5as9SaS5b1XfNUhvgq7A3H4sOdc9SJ2FM1Cy1MMpWy2Cex1YdPLPUe/AzOD4anSJ6lqoQY6uaMbPUs3BrzDzVK9ZWV8cuUfO1rWGAlKd3XBRlvQ5N6AEYZ9VXLajP5fADmG/XVxOpzy9gDerxDld9tQbWdtdX3anPrfC4O0oNjKqvFlCftqe+yqYeH4ZvwTbR9dUo6vMTWJb6nBLTUK2nPmvG1lddY6PVjthb1B/iYoydooOUKXAf9mGqkbZLXCz9cGp8gdWFNu5Cu3ZRbvphO/rhtOgu6gX6oh3XRdXT9T1P0ooroZ8fM98abJc2jApca2A=
*/