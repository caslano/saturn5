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
43QjJ87io2ERagjrFjH6fjGHomvuMb1o3lt1NGMhbuNrZ2zeGfPv/e+Z99G0OuHy+bKNhVV+SqqrxDXRdysINZYE2Xl7E/uRVp/VcXDq+8WKEnSl2X61qJ94AM/D1uwKqaZRCLwGCBQGqo3m36QxyLEZtHr4kiISm3Bu+wxmh/RokXNwFu0CrD9EpL2Wius2srGM7e+WzzVvE2zOUV2qXbeit9PTGtLuRjcuh9DTAJwkAQ+y2DonSdF0kcIf2S3qsPJxArV2Ki4AB+xFo+VKtOniP/efPYVJUt0o8DohH9M9cncmSohwY8gPUjotwdtrXzTzmtNra/96F34Roceofq8znlK80dxUHLc4S/53dpw7GWlx2r+ZCWbYQHHgpy6lEXBMJtRsvrUOt3ifP51fecA3roJTCJ6fY4dzSWRJTJDirnM7G5tibvT0kuYBpOapSWxeS/gZnyTjiSaGO0P+GBaH7CQAnGKjzdHA2bwut2Hw/uHuG6dooMxHq+HwiUxIo+wFkzZ3J0mqIxq3+U/lvb0cnX/iICwDBtX2ICb1mkD/YCy1PBc08CFP9l0gL4W01bVMOwH6xR82VUxLYCdnK5Pdf/SASt2L+ROLzNHdS0FRvbMZ64o6Q7r2tP0pRH6bggH3Pv4eM7xcCVTK+gPY2D1yN+8TUIxY4lfK96LZWUw+Vgru2hDobhTsxcC0jNwOgj8FEduzJcWQVGpV
*/