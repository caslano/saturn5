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
bO8cpG5w+PeAujNo4+mu4829zMexIbB97jlMWG1ssMaufSxdRRjb2nAGbU11Hk/XvtxzoubY4Db/GZ2m0G3WOVF4x7ZJ25BK3h9K3sBiQrwbfAZtT9e2/1DiAvfnnmvtjTMf85aA9utcK6w2t1jj2T7WompsZ8sZtDPedYxlH7aN/GpvaBt5s+1zKNv50DbRk3Z4ic+KfqlP5fFnKza/Vz8xafNh4s227e23lTbbXIe2wTfbwoeyAT97NvJiA2c9C9LrS77HZQMnvt+9cARMgCNhCjwfpsEL4FQ4Gl4Ox8BZcDy8El4Il8GLYAW8GFZp+kk42X5Ow750/+qvQMIA3f9A2BUOgskwEw6DQ6D9TV0tp4uU4/52Zi7JPi6DneFyh1696nU26E1QvWwYDSc69BpC7w8l/ea27m+zQ6+xDb31qlepelUOvaY29Haq3l2q93mHXnMbelepXo7qzXPotbShV6x6K1VvlUPvRBt6u1TvftV7oFWPTKH1PqV621XvdocNZ6zqFRvGby8dP7E6fuN1/PbW8ZsIs2ASHA+T4QSYDrNhHzgbpsEC2A8WafpJON767QLjdP9RyEjdf57WOx92hwUwFhaq/mrrdwBcIPncviYna/0/ApPgVJgKp8EL4HQ4Fs7WdsyEV0BEzr8r4XxN1/oynw5d35u1vlu1vrdofW916E9uQ/9a1a9V/Q2qf51DP78N/XtU/4uqf6/qNzj069rQX6j6i1R/seovceg3tKG/RvXXqn6p6q9z6De1ob9H9b+i+ntV/2GHfksb+jtU/w7Vv1P1P6O29LGPte/7GU7708OI2pmqbWmwz89jPuZgFxhgC3onkqC2nsf4v2h+sL/OkYjlpzNKbS+3GL5XofaUgfaTtt/N7MUOX5tmP5tq60i+EH40l6q/zArsDLchu5EXkONIwraunmwkH6lDdiOHkHeQ2E/xzVBkIbIJ2YU8gxxDYrejtz1itxgJkRAJkfCfHs7J+n9pSeHZ8P+f7omRtZCKa3zz3qLilQU1pdV5+jO+vEjsAwooe5T+/q/w6u9+a56LHPY980mzfv8XllTLsw7Lzz/vz5t/96uO1/Zj8XqSJ+zf9eKDX8vW5xOutf2eqtQDeZf6NVn1E9dzlfrAzfoGX5v1RDf8521Nae17PsG+tR0hn7fZfV+qa+uP6VrCAWQ3bWux2yYmC/Sn1aZKe+3gl5Jnn/rZUR1KwkOZ+1mMfUykrYQS9d9C6Ecav/Qu5Xj18NU3gd99FJ7Xm36mgOYkt9wd69wOzwaip6tfKnXb6pMS8UnUR+rB+5xZ7mPfxbBu/lfyNPez+kfMDorLVpWUFYd57Jv7ffDj6VwHzNf18v6qlI783Xfs3HXjeWPAueOwqzkmeZON9aQc+9n3X8WHJp6FpLhWnzNHJU+cYdwa9fHcpPVR/T9Lnm5G30gt7ewn+/x1PEtnv8RpvTU+xoq36+PqV3lm53H8jjkP+Qf9Gpvu6teK9avM/RoPUyRvpqlftRxa3dov9vFISA/Rn0a99bbeYEnrYehHk94qW28saaSY/P+h98H7v6e7/9l29vt62Y61t1e51gB4KCIhQXfSGznK/STH2f95el/RmwpZ7Gt+ofg7WSD3oHt3EBMddA+y/foskjK7ntbXkfOakE/D/Ptr5fuMjwpX/YprdenWce0sMo0H9ALvBSVFtSGeyWteu61Le5/+/ua+/hUF3BPYV0D73jPYPvyT9tW52lfKNa+aYx3efbnuDMaS8361XH+ydrf6Xr+HW2/XDbMHx1hYkXH6/nG2/Wg3PedRlmfF6jijwVl+65iTa9uI3r689i3A9uszsL9P535jf1Ce29+U2iwmWTaLkt4=
*/