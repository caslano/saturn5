/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2012 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_windows.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_WINDOWS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_WINDOWS_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_WINDOWS_HPP_INCLUDED_

/* caps_windows.hpp
qR76p+Nt3z8l+vqPWOtL2n6+RvR9fGLvN/Se3a9Fo+Tdcj/s7LW/pSB7iK/u7VJg6XclmGS7dZ7rrXt5SE2FibDSscdEsfqbrf6ce0ycq2tLljr2CukFl8FcWAonwOVwqspnqRzc62Kvhr9Iw3fudXGOujtovr3ItxxxN5zfD0JbrXacJz4CXgbPhBvgDLgNzte9ZJbC7fAzcAe8GX4Z7oI3wm/Dr8AfwpvgM3AnfAF+Db4Ib4FvwFvhMbgHeojLt+BpcC/Mg/fAQvhtWA6/AxvgvXAjfAjugfvhXvgwfBD+CD4Pb4Vvwx/DD+BPYDb39zF4BvwpHAafhOXwKVgPn4Fb4fPwbvgS/DF8Bb4Ifwdfga/BN+AfoF0g3oYD4Y/gdPgenA2PweXwn/A26KHBvB964Y+hDz4G4+DzMAF+CJNgKverHWwPk+FR2UNL+63a37bv5wI7H/XbZSbu8mF3OEDlQSoPg7lwlMrjVJ4Mx8LpcBysgONhNZwAm+AU+EV4LnwALoO/g+XwdbgCvgMvgH+DK2GKhx4n7AmrYV9YAwfCejgMNsLzoB+Wwo2wGm6C6+Bn4GZ4BbwSfgFugzvgHvgV+E14E7wP3gwfhbfB5+Dt8Bi8A34I74RJ5NU3YXt4D8yB34bd4XdgAfwePBPug2Ph/XAJfASWwR/B9fDH8Ab4E7gT/hR+Hz4JfwGfhofgszCB+/oczIa/gMPhITgb/hrOhS/D5fBFuAr+Bjao+Rr4Ctyk7q+G98Ed8A/wDfgGfBf+Cb4P/wwHx9GWweHwr3ACfBfOge/BufAYXASPw/PgB3A9/BBeA/8B74PtWKr2FHwL+dfQg/wB9EIf5dEH42E87AMT4ECYCLVd1L4X97xZu4iMdQdYBXvAC7VdrIbj4EWwHDbAC2EjrFNZ22vtP3HtKO31F4mHzWthPLxO45WH3q/+fOrP63hGfEn97VD3RcG+Aeyi7uPgAHWfijt5V4LpsD3MUjnof6/67xrFfyf1nw0zYGfYSWX1r+++vMtF8Z/mCfhrDzvBDrCLykfh65a+u+o7Lf4lHofV/yl6/R5wEOwJB8M5sBj2hpNhHiyB/eBSmA+rYH+4Bg6Cl8KBcAMsgNfAoXAbHAlvgmfCb8LRcB8cBx+GxfBROB4+DSfB1+AU+Gc4DR6H0+Hf4QxIm2nNhumQ+Gq50HdRfY/db4WXi2xNb44jvw+24oym6sJ4azN6J/pe9EH0y+jj6Kwh7EmDnoZeid6C3o3ePyT+U3m205Eh8R/tfCfMeSj9R893Yk+lj/WMp9bul3SiM54O1IWf87T+4bioZz2xB1LUs56yyOMCdAl6LXobeg/6IPpVtDUs3jodPQm9FL122KdvbnocuuHjG/+vr6u+ePCQgmHmx8lYA2CPQ1+Qa5m9V3kmi7pev1FeiX40n3a9QPrFJXrp0ilVtWXV+o1jf374976zPMRF3K/SPnPQfw/H952asnJ1P8PYdzdjZk+K3IjsGMdwfGN+XOyHqcyXxcG6776OE68kTVXoxMyWv3UG++mkQ7816rcT822IuEbsUVuiHx6XaX6dBx/Bf/3g8Hw6S8fUo+UT+aLufSLPRW4U+VwZy41Lt+w8rLzY5JO656p9GUd4FXm7l/cJ0pnqK/A1pUxMmZRSkeD19UH3Z+C8f397TCFb3e7F7Spxu3Fbanw7y2n3hLG70LYKs3vd2E1qZhfnU7u4zqmJKQG71n4fjczvdEiaMSPNEfk9VKv7EXRv5QH8FwwJz++F9RUMScTMb3U/xIzNlYt8P328VCuU51W19aE8Vz8FZjxnucgP0k/McHwzrq6sdYyHnSdufsi+ntkSTokJZ2BkmTZ7ip8j9o8=
*/