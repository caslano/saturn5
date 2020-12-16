/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/intptr.hpp
 *
 * This header defines (u)intptr_t types.
 */

#ifndef BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_

#include <boost/cstdint.hpp>
#if defined(BOOST_HAS_INTPTR_T)
#include <cstddef>
#endif
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_HAS_INTPTR_T)
using boost::uintptr_t;
using boost::intptr_t;
#else
typedef std::size_t uintptr_t;
typedef std::ptrdiff_t intptr_t;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_INTPTR_HPP_INCLUDED_

/* intptr.hpp
93yPPOcKnQ9V3jUP/1nkVofPv560hyPO3wuqLq+oq3f7Kn5fZIdw/xYweRR68jiix/9dPyflsoZ6My7CNvafHYQtjH6n2uKvv7NC+tvsOed6dfWxGLp6ANKHEXPYczHOrwe959eIc667zTnvmrmR7arrR8wcaNrMjBfage20g8eO8SAKGFp7fCgcDM90zq27jP536B6yTX6i8VH9bJveB2Ncd6r8Oeb7orcl/mbAf5xMlXPBuyLzRkCvOzWPiuh7TuRr4IuyPyGo151G3uce1HyP9IbIvBsI1ev3Es+OPJfuCutZM9t6k980se3U5qJLnCZz+2r/qaSZFB4vnnx22+5rTulTsxa2+ZZFz+1u3/3p8B+75fpav23h7HK/E1/HNxe1ch1f7D7Pa77zIr6hUX3T72+XSH5DAwEsxc615+l3uVyNPMB2zm4Z7vLUVa2qcH0ndETSfkmOm2POJxTX810Pemrq4/5+5JuS/h3bHMMzly1DZoHIlAS031Um/M1Kmez/tOw/OMrZX0khwn3RLO3Tz5y3vyPxF/lSbbXOUeG6Ot/rfNiNNqG89zvfhiSsa0rtkpQcPJGPaoYne+YS/zmnFTrfkHwa2UxZk1T98BOcc2kigW2kxLeB3gcs6tN2XVVLvnWE5YQVhHoC+wnyt8xdpXb7595cOzx3NdrR596NdvR81mT7z2fb7OjnI4wB7/MRypUuOs24YHv0uJCy6HncPYfNg8WR12vm+i7HnMdD36adnD5Q+o775e5t8QrpN+e4/12/jP72xHF/jSE772axn17+Qbqd3DD57JV7Zox7ctcTK/93/DL6220fu7/GY/XL6Fr/U+YfZ/xOVhvrfPO8lHYkNHrWP7xR19u7CQ6FN8N3YLN5ZsdxNV063KLp+rIpG/aDo2F/OBEOgJNhLjwLDoSz4SB4IRwDL4dD4BI4FC6DebAeDoMr4HC4Go6AV8GR8Go4Cl6n+Zj6aTlTfOqXySaHPWBX2NPYYuvzHH2e1ui2xVab70nwIXga3AOnwodhhdp4b1Ab703wEfgN+F34DPwefB5+H74BfwATOMZ+OAg+CvPgj+Ao+GMt13Oh+3C4UsslzxW0XLBxMPwZLIAH4MnwF9reT2t7PwMvhb+Ca+Gz8Br4PNwGX4DN8NdwJzyo5f4tfAm+Al+Gv4d/gK/BRJt8YFf4B9gD/hEOh3+C58I34WfgW/BS+GdYDt8x66fqfaneRzd61k/9vNr8b4Oj4O1wBrwbzoI74Ry4Cy6E2+Em3f8FtYm/D94D98EvwLfgF826m3oPIH3MRs+6mxP0+JPgqfBkeAacDBfBQlgLp8AmOFW/MZim+Weba0hkg5I/Y4E6Qktt1OfBizS/i7X8l8BbYAn8GiyDj8PL4FNwgfZPhfbHQvgPeDnsT96VcDKsgtPgYngeXALnw6VwFayFct6GW2AdvE3jf4dXQUttzsvhdXAx3Agb4HK4Ba6At8JV8ABcDd+Ga+Cf4dXwfXgNdO4Xrof1cf+v/xH/r9h//8/5gMWGPL4O58fkCzbtykRrNGE2oYbQRGghHCAcuTJul/5Rfv+99/+Lq+o+Jv9/TXm8f9Nn1+/qe2emGmsg7AmHOu8xt7qfXdeU1dZVxHpuo7IFxgfJwFud+Pt2jOc2Kj/WvGfuL/J77IDdZHzs3HFbm0+VLGuQHLdvtuTDTZ4+wzT5jDL37H0kH1vu2Z8cIOsNVtS63qFky/4PzTtE0ps1C94aJvJlbl8duVKGVa7nNpqG/9y+RwZnyL26czBqGV5jLVOPl4LMK9LaK83zy56y7z3b8Ruxjz2ltHt6juPvo/HbXn8fWSpzAzKfa/Nj0SsttXFD6LnB/EwJIhs=
*/