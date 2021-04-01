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
54w0qqysmLsGA65kZ/G7AkruBC38e5KQBb+wXhqelSco8WWP3oI2D7lH5zSjdRN1ffqKGT6bRxAUFFxFrJua9EJrqQfJozQk6j3PEw7gUyDeD1Co5SYYClIwjNOqXSc0SCvFoN0gXkSSXIzFaHbJZZ/BwlXUri8y7gaW6i7y+rbmkXnuJ4P9rlC8ksR4d6/tz7+sIAjINpjDWEBcqCNx9U/PAqC5uobrXcQo9hWM7AGinzRlInBrnYJDRu8M6C0KEkwOgCuj/asL17CpldwcvYHqyvxxdvgp1DA9czlPQsGnqBv3U4Ad2nwGfCkkPxL63g1if9pmjVqC7Gku8lxHOVbrFRBikcFjIKTiqL+9Hxi4YEojberSBxmQsa7mqa2tQDK5rkGrKsNEoeAaLAy8xIrUrv3sBdcvUVFh7v++I9GUhCIocJzfy11NAf3DzzHLw5j2BwVOdu7jLaXQDb9Kr6W2sZF8vj+uoIC0k1dY9mKfsGx5ebZW/U9r+0sKiGRQYpnWqiKZbDkpa4+2sgkztr0R3QcUt9nlju8WKMMfWk1vq0z/G4uXEUQrqw==
*/