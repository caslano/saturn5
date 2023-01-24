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
/hGbZJyC4wi9+0B6Ixc/zRLO9tK+Q2vnhr3u+8bmStmXhVR3dX9vp7Vtf7V3dPUoyMrexrNdh4tDGcsGXbXIHL1VsKVi8FQ4lMp1GhVRKpiccwHdwL5VZ0NTN7sG1DQ61vlsPxfAZ9HfWm75LagbETvfjvamUS3coCDariDZjuaDX9gOKINcQA/YCRLmnN7Eses5kV5LbJXhCgteUCZblxHXfW+ztL3E8VhrM4qwj8YIaF22WHn2UbT6apaKf/K4vro+v7p+gh763LJKpq7V5eR4NBW0nM0sdrHhLKL60YjGUSzob6ORnNUaFurQCAMzPjGSkNN6pENB4VAnw8pes2JRtG73DA2hM1GwkZPuQL/YCt9F9aSe0nxKol+yZSZBGW3B/ol6XeFn0YoDNaobkPSUuICcxxGGt/JxevdF6lqnb2x4xXvSh43DoO4v/zObduqXldcaMx8ohQkHMbod0PSsSu1QvGfPd37+VnbK16bIx6DnDh8Kcnfv6J3/OoCfv7f7xSEl4BVMupPbQev16esPPgOm26c8FnVMaM7ATtY8G1bypyzgLWxN9uIchMijWtwroQAqCNe1HsDEma6GhGTJh4jtMw0TZ5brRZmlVmk8WV2+tlXy/P1Z77vky0syQsv+Vx8XUXwga4Dux4H+Fh0XLqa8BR06GUFJoQueKlquygEWP2QUckjTtLziNrvuk5AehF/Mj0L4KOL8
*/