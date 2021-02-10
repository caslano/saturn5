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
Mrce0MOIKJhLXzs1o3NS203FTyFxp124IWXs8PfycUrW/lGszbgEN4RM88No15fWh2wcMK1I4eFhxf+TCGa7Q3KjlZGEvfXk+OtrM6JQEQ7KbiT4C60zievraxe1Ch7EDOhEnZzArq9Dpi8LLvQQgiAN4fQBR4Wb5y0jPmuJHQRdCRCIqpcUnJZ1m6VziIsO3eHvcB3W/oC66i2/+HT17iTqPRz77WpmNU9BTMSBi7KWPLhR5tXLsTRr5axZwbUjvllK8Cy0ZraGk5w0Nbi3C7C4IgYBCxkEzue01WQUEbVtKMu+ihqxFkrTT/LgCas+T1h1dclfvCa8lEzQOw3bRsZzZ2lhfIUFUkswnfxvKz0F1NzWbcKp4idA3VDymG1FQkli5Gflb6K0RNZKeg/PVfzodD6HFFj/U/XT6+r5cXfoDkzbeYKA9JVO1WCrLBcguyLxoKSSe1O5WMg6qHWS2eqgkCWy+95LgxiUnqIAjqZCAS6JTqO3gC4MCF60miym7VSUgtUx0nM420H+E9Dx2MmVRamNqkDBeJyCjGUn8fPwg+crC4+2XkbxhqrhTJlUK78WtUTdkC5K7KT0aXj5pk9DaKbwk9tOG4F0IAqUUYFCkBaS4dLQ4bah8zGYtL25oXCyMT+S60k3fw+p
*/