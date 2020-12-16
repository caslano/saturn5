/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keyword_fwd.hpp
 * \author Andrey Semashev
 * \date   29.01.2012
 *
 * The header contains attribute keyword forward declaration.
 */

#ifndef BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace phoenix {

template< typename >
struct actor;

} // namespace phoenix

#endif // BOOST_LOG_DOXYGEN_PASS

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * \brief This class implements an expression template keyword
 */
template< typename DescriptorT, template< typename > class ActorT = phoenix::actor >
struct attribute_keyword;

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_EXPRESSIONS_KEYWORD_FWD_HPP_INCLUDED_

/* keyword_fwd.hpp
SF6IvaMNuq/q1+FQeD08Dt4E8+FGWARvgIvhjfBMvU/45J2OtepYcB7sjSTwt38f0E7wN3AgfApOgE/DKfB3cCZ8AS6EL8LT4D64DL4Cz4Wvwhr4R1gLX4PXwNfhdfAN+F34JtwG34L3wL/AnfAA/Dl8Bz4N/wbbe+grYSb8O+wL34V58D04Cr4PZ8J/wGL4GSyHn8Nz4SF4PvwEXqzXpZw9/jFJ0qD5MgQ5S/Nlku4DNx32hTPgQDgTjoSz4Bx4ElwIV2v+nwxXwTnwajgXXqf3vwFPgd+CC+Ct8DR4G1wEv6/nzfBM+AhcDB+Dp8Mn4BnwGb3/DjwbvgfPgR4PdQgOg0vhOHgaLNTzIj2fB8vgOep+A1wFr4W18DZYB++CDfAeuBruhCvgLlgBH4TnwmfgefBZWAmfg1XwJfX3rtQfHQeCL2k9z0Se1Hq+SfdpvAV2g9+BfeEW2B/eDgfDrXAEvAOOgnfDsfAerafb4Tz4Y7gI3gsXwx1wJbwProI/gVfDR+Fm+Et4O3wMboX3a33dBX8AH4S/hA/BvfAR+KK6fxeSpzp2gR+tTwORKZ6AHr0HngR7wXnwOLgAFsBT4Ri4CE6ES+E0uAzOgKXwZLgClsMKWAXPgw2wCr4Ja+AHcBX8GNbCT2Ed9NjlCdvB1bA7PB/mwDVwALwEjoeXwomw0Y4HXAtnwHVwEbwCLoZXwWq4HtbBa+AaeC1cB6+D18Im2AS/AW+EN8Gb4Gy4Dd4A74M3wgfkvu776NHvdR2DyIP9kQLN13jd97E9TIdemAs7wjzYCc6Ax8DZcIK22zR4DjxW++UecLWeXw6HwStgOtwAM+BG2BveDPvAb8MB8DtwILwXDoYPwBPg0xrOy+rvDTgK/g2O1nYxBh7SeH0E82EcaRsOE+AQmAL7QsQqhMfB8XAkPBFyTfyPh0nwVJgMT9Pr2v70+40+16X9dXesd+kAe0PEynbYu+sPB8Pj4RA4GQ6FM/T+LMg9yd98/V0YDi+FBfAKdXclHAVvgqPhHXAM/B4cCx+E4+Av1f1j8ET4PJwIX4aT4dswYDdPv7X0PXf3Yezm7YnS3f4o3bVE6c6acXh3u8WO3tFZ71Iz7l+35iW23iW23uX/ab1L40PJ1mZkJ7IHOYB4m5OtfkgRsgRpRDYjO5G9zbF1L7EjdsSO2BE7YkfsiB2x47/j+FL0/zEbdLT0/zNyAvv/MY4px0DEgwxA3rPn9ApkvsthWcln0K+TsZek+13pHPX74j7HfZ6vQOfAdc+zGTyoC3HwepPNXFduZ+d+Z22z9eezqxRuU6lJ9d9v0PmBjcjduM0eEZY2Y5Bu6YXFFaU6x1obSKfRB+kvfq9j7M7jmlbC1rTKPL7alSJI9zk/417n9I17VZFxX98wImz/QKNLkCv3LmdsMtF1f7GucJq4WYmmR3ujozVartVanbiaRTnZ446f8inX1S6nuCRvUoI3rtKbFO+qr6ru+5Hf3Wz3SZne+LTwveyi1SuodZRn16D1DYG8zArWLQjkWYgdxfVaafrqg/ogn9rz6mF1gOIvKS0uLSsvaaisLy6nteA0rL67zrWPCMzxdpZEldeU1K8w+/v8Re63N3pu78p5R5M/mTmt73XlUtfFTtUbEhZje6nBtgJXqAGt55E45DnkM/ymjnRNd5vSSxjO9PKX+Hat38atqau1Zc69KnvK/V9J/a+RsiqrKllaiVE3yrTOMnnYKO566TmakXKeKnV1A/52t2M8VvSr4lJSUmaxpWSXhBDbhRIHOj6OYFuk/SSsh/06WBLeAcLLssNLbXzY9Ekhes3Hcr8HckuaxRXfM3q6lGWSi/7V4/JMElvqWrY6h6/7MGo=
*/