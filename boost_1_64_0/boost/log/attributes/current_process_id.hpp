/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   current_process_id.hpp
 * \author Andrey Semashev
 * \date   12.09.2009
 *
 * The header contains implementation of a current process id attribute
 */

#ifndef BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_ID_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_ID_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/process_id.hpp>
#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Process identifier type used by the library
typedef boost::log::aux::process::id process_id;

namespace attributes {

/*!
 * \brief A class of an attribute that holds the current process identifier
 */
class current_process_id :
    public constant< process_id >
{
    typedef constant< process_id > base_type;

public:
    /*!
     * Constructor. Initializes the attribute with the current process identifier.
     */
    current_process_id() : base_type(boost::log::aux::this_process::get_id()) {}
    /*!
     * Constructor for casting support
     */
    explicit current_process_id(cast_source const& source) :
        base_type(source)
    {
    }
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_CURRENT_PROCESS_ID_HPP_INCLUDED_

/* current_process_id.hpp
X+vS6/vULwKJjmf+G6XWXVnX16Zkc55bruwrmRJuYJ+WzaXTeitx77KsmctzXFclenqd32I/1tN61u2bcYiUOMieZFlvlud1lvUZuSdtIp40RmJI4x5PGlNYwOhOnV9p2+Nn2kRPr51lzd/48dBpfZjoYqb3iroX+Fr2ib6kdAL1+uPDsT9dfnnWguUikRJP67kk4XLoxg/m3B5ehQfNNeLuPEzPSvHKRns+6jV6L1ZT++Wcz2BwyNcq4i5EufvItY87/ipq/77oE6MuPM3xOp/BOd/1uuDnlV9HHMvB6vZAgjpr0Nzmo912Um7vcjqzUbt1WgutzztTOp+7XnUF+fyGZQ0VxmmXaU8g/DLG5eRO1/uMtir7ZZRPOX2+7JxozFjB6bCGWruboNxVdVXiFLUocTdTmQ12tcS3ROOUPrsuSpmfcRU5C13yvpWyf8lxbfVFp7XVsuZ6EHW3ipyV/jr1d4m5UAQx6/Ld8HY5Q31/uFsmxBbyGcSyVpq/i56xHv4T1X3POZjUAcxUHVBmFx3WUV92WEfd0nOej7Qb6o5mX/7Lj5C9e3IaoZlfrTF3yf5yh/YhbmT/gT5v/vr7Yzx5YPofKf5b9/yeL+tW7ooEy3O8dujWifLEcRz7Tr3Pkg6R+PpY6y1uXRa9NKc+UutV8a5nKamWtbEJSqe50dBBL03pyT56pVefMSxEr5klj5QsrX39s+PCvPIpVeqJ5zrNK89CZXo9WvJsFDIEvS2ROs+ysmdbMk3GzZG45oTDLB9ji7h3WeqDeZKf4xp5dG1n8dn2ee5X9r0MdcInUoM8CZY8KYh17+3/DPlD7PX37njqkBn/SIl/FWv+SDyt+1YPSR7VFY/qSN3P1nk0JTMnh+mJVzb51xbwwzpvIE3+j4O2dqC/n3Kuomib63GFo9CtE+qJr+mGDwVPnyxlWXwccWcfh7IB5UMf6rEnlK7GJPZ+jtNuxc623jx1+oTWhXV9WEVV17Ev5ziOWd0HBon7eMNx3LLHk7eX5uZbPRaMVfaTLPYTsS8c02cr+9563foxde0e39qpnE2dTNz1PCZd2ZfXY4n4760fL+OhU/gSvypi7w7vXnKins84lqlYsjh+KXH0zDUsYdjjqffMW3U849yHBJ6E7mVexi6r7d4TO4O/832Y38Pfy5E4CmemcL70XeWK7btCAc9/K8o7evYJveb+u8GAQfEJhpjtKDSL95itKTRr7TG7u9AszmOWrM1atzM8YYRqM6UXhllXbdbG0m/oNif9hh5vs4vuRZC6LmNwYJCYxRfuW3K7lXog/rVTYahy1Pt9tVm8mPnp9orNrXUuXBDGf5Y1fKOlX7uox/ScDHb3Z+bOVoO7X/0Zbm3z/4xxyjG/elInA6Q/r8T/McgNSDukB2LuRTtP//UEcVth7kXDY9s8Qe1H+7F9pCftw8T1fuln9iK9GtEfV5e0p09ktpDDl9jU3atK+8KG6ttAmdb9NvOV/sPUAedvTuCf7pM+r6nmkXzMvHBOsEzZbzCyZG9T+8oy1yTG1n2DR5VeqN5H79V2LfdWzyu9CL0H0HN20zECW0ne3Yuskv0393naox/jpZn2SNJu/R6CGddIHVeH+ma799ojN+esRTAqw13QzPOxNbzzPGOq7zyPgllKf3BArBHklOfin8spP5X+Oe95PcEV5t+GWoXn4J8VvYgYLCzf9o+Aj8eYel/Itcv4k3LHuUm6XGZNT2X6RyboupKj4rUuMBrfpX1I+LKPTeJwQektD6hJ6QxlJbUnzAdUGMMkrp4wg5zigN86DnoMNOf3+1S8R7sK608ucXTnSwH2hW7N4hC3Ev6HNU23J+zhyRxCnyml9R+p4R4=
*/