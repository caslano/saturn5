/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   id.hpp
 * \author Andrey Semashev
 * \date   08.01.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_ID_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ID_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Generic identifier class
template< typename DescriptorT >
class id
{
public:
    //! Native type of the process id
    typedef typename DescriptorT::native_type native_type;

private:
    native_type m_NativeID;

public:
    BOOST_CONSTEXPR id() BOOST_NOEXCEPT : m_NativeID(0) {}

    explicit id(native_type native) BOOST_NOEXCEPT : m_NativeID(native) {}

    native_type native_id() const BOOST_NOEXCEPT { return m_NativeID; }

    bool operator== (id const& that) const BOOST_NOEXCEPT
    {
        return (m_NativeID == that.m_NativeID);
    }
    bool operator!= (id const& that) const BOOST_NOEXCEPT
    {
        return (m_NativeID != that.m_NativeID);
    }
    bool operator< (id const& that) const BOOST_NOEXCEPT
    {
        return (m_NativeID < that.m_NativeID);
    }
    bool operator> (id const& that) const BOOST_NOEXCEPT
    {
        return (m_NativeID > that.m_NativeID);
    }
    bool operator<= (id const& that) const BOOST_NOEXCEPT
    {
        return (m_NativeID <= that.m_NativeID);
    }
    bool operator>= (id const& that) const BOOST_NOEXCEPT
    {
        return (m_NativeID >= that.m_NativeID);
    }
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ID_HPP_INCLUDED_

/* id.hpp
INenDnjLqXD57wCtXEfAdiWMr4sIDfEkB3OXWGAJ3X4PsxGHtx44wEfvn6uPx++fx3wOw3n/POHxrefyjx8/KlJeg2Jqv7PZ2+8Z2lJOmmGUoECFUmfIp/i0gbToKrsGeKLXK3zI2tsAFwDBbPI4FfOvOazN8CFqF+BppCJIFm+2YhEHjejMgcmSMn/lIkzBRZ5lp1MvNsDCN2BdUKcPBWp1cY5FV42+wQQ4SQJ22FQTu+N7aOyZA6DJp6CHrLyt79DWwtWbSXG7/1Z0FcWWeK4iHjjZaCXk2HaBjZYoO8XfutcmvbH04Kx71Rp2L1rdwZvDbTC9CEyVhJ2iZCM5Lh4o4Kh9VB0RU9oGMFxSaIWr9XTF/8w4Cj9dAJoliUCybRUCeROLdLYpXFB7q/Iqr6LR8alOlVu/EDOEwcybFzn3ijtTJgtmcbhkTp2gMqxq1UcSqVbqLTlak6cJh0dTTcAL595bZkuG5SARQW0BAVApm87BLuJWIwrZ6TkYaUfP0X8+eo6fj+nzcVnMQ9VFWFkZFfhWR9Ik9YKMW2DSnoazWcLTnDRJtkRLIHaCBDwiJoq3wp0IuOGNxzEKmzqfkKKmprBR1IoaiaC6CG21NusIy80hW3+AUj0tA34XeynXkJFmugZzZimOQXle
*/