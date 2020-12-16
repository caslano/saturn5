/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_ppc.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_ppc.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(BOOST_ATOMIC_DETAIL_PPC_HAS_LDARX_STDCX)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_PPC_HPP_INCLUDED_

/* caps_gcc_ppc.hpp
Y+YLZmr7993PWBmyT9GfT434wsCnltt1LPMCySHmBTKD9l9nYNbWzAtInot5njk74cvXyJzBv2POYLGeM7ii7bKlLU9b9njPvZtv//mm9dX/G3MGeb42Qdo/yj/7DrX8bn1lOuQyN3OM+TvCYthZxv5dYB3sCj+EZK2Wq50PfwYL4I2wEO6F3aDbRZrAeHgCbAy7w0zYG7aAfWA72A+Ww/5wMiyGN8MT4R1wEHwTlsD9cIjtj/wcCjvBYXAqHA6r4Ui4EZ4Ed8KT4UewDH4G+8Fcj/d+BfA0uCsyZ/FfOWfxeGS+InJFrsgVuSJX5PpJrp98/F9oq1nTJncv+lHW/9flKnO+e6p0D163v9sC74PKPhNdKeP/wgn6xsw+6OjoMbljnO44/y9+TjBj9i+1fr3V2DlGF/cjjPsSrR+L3jPD1m8UPV8OP0evXesxfqpvPuHs2um+e043YYzRbg7SMcfXlOkVU+dVVeBGzqz01OFOsWQeQPzs12Gcin6Ttl+itL25b57yx7vy3IopOjx9rri1dn+hDq8U//20++iA741zD/O98d2SZrXR5gyvDisfDtFhnWqlSly+1v5WWzuIjy+8/KDw9sj5/7w0nYParFjMSF+uavM986Y6/ForxXI7ZCCcW+BLw1Q4UbuJNecVYrX+Tn1mK0POmf5Km+3nHuWcY4mGOk+4qsz+/QTtZrFjj8TcSedWKHPWrLm2P0/bb+ysCL220jveH6TnSbjkPrsp0Un6XPoMMX9am4/QZmlS557XZoO1f9+3aXZos8fZl52OWztcHYDJ0+Z2mGImz8S9TqbUNdN2PKsOJ/h5U/U9sHOEJXIoTTlRlBPF5SsXB3SeJZj5qO+0PsPItkzT91gt+sByJ/mUL+HpdEjS7tfLOVErOP5GdsJKOTM/8SgyMMtEBqaccTDzML5voG9yzsHIvEwdTNX+pC6K+S5I/cPc1L8g2ZneOoSZLr+12kzqgpzNpzxrGZy40elKGUFPGXHM/WSi7tdzElcO/HrUFQMO1netX3Xg9lG/vMg7pq/z1RVp02TNn1TzXmz1XNQLtoX9YDt4PcyCK+Fx8EHYXtbvc+FBmAcPww6ynt8ZNoJd4XB4PDwVFsBpsBDWwCK4APaEv4C94K9gX3gf7AcTCfcVxmn7UYci47XIFbkiV+SKXJErckWu//jrXzP+n/Kjjf/XOsb/9XKOspWLvi+Mh4fpxyefbcb/U451/O/101+PI09HP0rrH7JacKoNN5hZKlH3zZupMHMCEkYfs6dghNbXW6HmAGTNWvycYE1EpkdzWbOu0WYPWuNVCaaNOVdaEmaOgDG/CSPfzAkUa/2HVvAcgG89fpq232C9gA/HuF/CYZTH+L7Gpyd1l6kq1jqrGs4DyNzHYO3uj5ZzzI9fM+afbz+vOfdgMsPcu2eQ+0WB8wFGls4p2s1e60Vc7QgxJ5AqcwL3a3fvYf+kmRf4uTaLs4rUbYHjfzlvUart91la/pu2m2LON2RM13MkZs7hC63PJF7o+TV4uszJcHJ0B+ah5gjwp68X9H2+ZAx3jzH3oA6d7RsPP0qcdfqbckAZ4J+J1xTlOP/wkb53UoNxd6rE/VIdxptIQ3jWpM812uyvjLPvM/LqVuaijkFenT2+LQsx3i4PMd6eGGa8PT3MeLsmxHh7vnO8Lf4XmTMapiyJ//Dj7k/0uLvz02/+Ysp56+eveXNvWrtT7/+zd9x9yJQ/3ZboqyXqY8d5+eNga1gK28DJsC2cIePwOTAbroQ5cKtjPJ4HX4UdocVNusBEGX+nwnyYBQthrqyx94BFcAA8AQ6FPWA17Akvgb3gDTIe3w77wz/AE+EbcCB8Hw6Cf4I=
*/