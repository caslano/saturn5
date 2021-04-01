/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_cast.hpp
 * \author Andrey Semashev
 * \date   06.08.2010
 *
 * The header contains utilities for casting between attribute factories.
 */

#ifndef BOOST_LOG_ATTRIBUTES_ATTRIBUTE_CAST_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_ATTRIBUTE_CAST_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

/*!
 * The class holds a reference to the attribute factory implementation being casted
 */
class cast_source
{
private:
    attribute::impl* m_pImpl;

public:
    /*!
     * Initializing constructor. Creates a source that refers to the specified factory implementation.
     */
    explicit cast_source(attribute::impl* p) : m_pImpl(p)
    {
    }

    /*!
     * The function attempts to cast the aggregated pointer to the implementation to the specified type.
     *
     * \return The converted pointer or \c NULL, if the conversion fails.
     */
    template< typename T >
    T* as() const { return dynamic_cast< T* >(m_pImpl); }
};

} // namespace attributes

/*!
 * The function casts one attribute factory to another
 */
template< typename T >
inline T attribute_cast(attribute const& attr)
{
    return T(attributes::cast_source(attr.get_impl()));
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_ATTRIBUTE_CAST_HPP_INCLUDED_

/* attribute_cast.hpp
klF63ZiyTpcD2q69ff+NWy5axs0zKP7sjqQDrSnBcHM0X8ohX5Qt3PbOZrmLCHkjoE3exnIvhClW0yAPHQYNstZT1T/TiFOnxhZIUMEW8MCOEUrUQC8s3ngueMKMUBzRNQhcYzv+MfcdbfDhnnlQKVAfJ0z93z/9MstegXk8cbY9ORQC2atqjgpMNNsEey69joHTHerugaGyACpzerbWeRFtfzTdLAnjo88/9Ax/JvToGBWzhU7DsZrbZH9M/QZlV0hsTKzcfDvtQGLsn5VxzCXKqGtLo10W05949Zvf+FE6wcjl07vx9p4XxakQuypHZxyT14AAqlQ2LXjorP1DJNfYRFdfGcln9JfedNpU/LtJBnyMCofFmn1DXL/xdPU9k+9bKuePtVJO2iokcNhzJsbFbTA7ICeRLqn1r2jRekfVGaETqjRQN3TdLAH2wnE+IjNPD7piqWWwiEVh/2iiFCPlh6aVsf2/e8XuFl5US8AZ8sDZri865zXkSFjlAsY/xkWn2tI4g2zynHuVlHws8QqyOAvdONNO26XLX78xCYC0UhRGSbrQ6DLSOA==
*/