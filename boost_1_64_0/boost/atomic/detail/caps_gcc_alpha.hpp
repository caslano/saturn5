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
 * \file   atomic/detail/caps_gcc_alpha.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_ALPHA_HPP_INCLUDED_

/* caps_gcc_alpha.hpp
Y5ucOnJdZFOycbIgB25IjXbwf9XYM79EBChfOm4C876zw3FpxBEzrabTgCz5wLSgmCZSekysBC/9MLX1vBv6qa+TW3o/KIv/vILtnrLPD1DAO/SV6oMbCNuZt+nXL49otTbLdRPQBbGs8E/7E1rlzbKiPX+SZkUcD8Ly/IooYl/Z4aNr/zAunRfRdWvZdan7bUrs5Nbxe6IHb8xXtmoBvhqGjuko6tzGf03VMHH57IxU5/3W+lGXm1BYj5vd773S7Z3Jwg6nqiR9NrMLTKi7uwMZM4tfA+rZvHaNO+kbjRCfhoIy/+Tl9oFgktcgIT/FJO7wlSHU3Ln08Xh1svhiOsPxzkS+NvJJg3fKNdvgBj1kLP1qUc+l0UdBsFOzBUybZ8P53Xedl1oBL0gQ7UcDE2rIzt4ZtPApUbAfi5ha74PKTzK5S8uYk19LPfNraOhI2RJ3NWv89yT/BbxGUfc13satk/0QU4UxH6s3lulyKtBQAYrEvi4XeJ8nOIFksHBOXnurOTM1SmKoIKnBFmZHKKRLkBij5WGsM9yRF/BtjjOD6UQKH/702flTdg==
*/