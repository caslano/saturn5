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
i14Gx/fy4snUX6V7nIDvm4g+elXZdT8SOHz3eQi51dB1LxI4fEt5AHlvhZgfNt5xR3srlffJyrd2hCljYOsV8YrPg672pT10L9TLcE2TwRvbbpfuySJ/3DGBr7nRyoSa0Pz5L3FfF/G2pKNe40aWuQTFVrCdAO70CODu+IeIC9m3HY8+mV4mOTLk+Y1CmbaPk+THGgo45/lIM/GlQH60sLh/3krH5zjlC9pwZZXuQyNuWhx4rE8Lr3NomYHfOhV4tV+KF8sN/Omx4GHjqC7pWRmBjzsffXn38pD0tJy419OcAduDbemh5RQtRHgpEU/G5vJLqstcIo6XEDh8Z3kIacsP4njpgJOz9q7YK8GxcxqcY3RSGTFBec3t4WkHWwlx8Q3k4eTHN3kdQssA/ObBwOftCMXzcgDfPBFt2JjdBc/KgvtsaZBJyjGfhp5acBxf732wN9Rm0sdwLewMYegQ0S5djIE0bedh3LXsCUINzOb7yES01+jLmVyVWPxgz3X/FNgC/lwZ9vREwjjwNcDWL8r1u6HlclHJ4XtGoi2O/xH2tw1+dz1Tn4VNTODPMNvJqBO8zGa3W7BtOiHDHD3iK7bXVo7DRhzLVNtNTrdfpDeI1Bxh61fBBF/U4fdOgo4zqa7Wy5cax2n8tCmwzznxomDWaCrW6czlqrm640JesQlZ99tWYdfeYgEsMZPKyYTpTYK5NoOdScdaMr6z
*/