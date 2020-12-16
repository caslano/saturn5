/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/start_thread.hpp
 * \author Andrey Semashev
 * \date   14.07.2009
 *
 * The header contains the \c start_thread keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows enable/disable spawning a dedicated thread in the asynchronous sink frontend
BOOST_PARAMETER_KEYWORD(tag, start_thread)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_START_THREAD_HPP_INCLUDED_

/* start_thread.hpp
AycCXwdOAv4CnAyMwfp8NXBkdKDeTgIWAy8B7gd8EVgC/ALYF3h8TKDergP2Az4MLANuAx4AjI0N1NtAYH/gGOAA4ArgQcAHgIOAHwMHAwfHBerrbOBhwOuBQ4E7gMOAZfGB+hoFHA5cChwBvB84EvgNcBTQ34S/nwEcDbwQOBZ4N7Ac+BpwHLBJQqC+9gVWAkcCq4DTgeOB1wMnAFcDJwK3AycBmyUG6qsMWA08CTgdeAFwBvByYC1wFXAWcKAUv7tXv+44fPMf7l64DXCb4WKPx53ocKVw2O9Pa0CXwd0Lx/vyQ/bjD4VbCPcg77t32m9/PdyDcJvgtsNhXz3vpQ/ZR4/985CHW9XEj33z4fvlea+8wz75rXDYD6/2v5fA8T302Ntefz/7wpA97LyuFbZffQ2ctU997PHuepdLLrnkkksuueSSS3tq/X/q+HGFXcwNAH96/X9RDnRVXv+HPkj0Jumt2IsKHAXbR0mBWv8PpIyDB5QfyNj36tu/a9qqsxlmvdN+Z45POp4b2PAr1t/I/2FprT+MoGefugM7k+Keg7h7833IWMMh3tMiFZrcaaKr8133BWqPPsLwXoMJtUc7fl8gTH4o7XWYUXF0VeXM6qpAXj9CXitJ5m6V17H07Hc4I+BU7omzqioCcX2JuKrJ/1ZprbPcY5YJZYnnMn6JZ4R2PD9gj7uW4q6ZOYXr9D3EfRX5z1b53ExxNVPfET6B/M+WV4qPKP40W/xpHL+1f+KsXAGqJLnNIXtLa9Qd3ktJvlZK6REjZaLtXMOsfPt31M8huTKsk2G/L69vbQjw5CjxCvO4ffGM9qU8ICyoWn2vO4r8E2URNObbxEA+84HVIOKPRL8bYvv29ozyWVVCfUt3b5JZSP4x+wq0Xu1EsHntmveKkswA3iPA9+kXUJ5Q//PBhyyeQJzXJ0QLJS9J3lYGapfXUXdPURyHKvulybuXeImqnwj0E/vd6keTf6z6Lu8seh6gvoVfS88LpCZ6SjOdTYjzNuJNkrZ2yBO2szVzyf8ieQ/XOcpiL4e6x/o8PgfSoYH7hdmGqs58iF1/rx5+4PHv0v6Ncfz+wFe/P/7GOMfBvyPwqN/WmjzV/xOpj6LPgldpylC9o53xTO38j7DF7nxIgn/Dxmt7fdp8+jv3zR9zzEmFNz3w37bF3ma9V3jMmQNsCne1unsmeG9vX2Artr3mAE8H7gW8EZgLfJxtttvYZruDbbY+xNsBGA/sCDwQ2Al4ODCfv/lZAJwM7GLbT30O23JvBvYC3g0sBnZogA3NtZEhb3DHuTYyl1xyySWX/ie0Z/R/Pvi/G879X2A79/8Yf3DnPQOxMA7DZGlzq6D+XzGuQmn/Ybq/0un6t6b9SPos8aIWz/pF8xyTlyctnevANqRzsa6LXbS55nO2Oi/9K8XRnXU0nFol/65O9gTkz9mekALdJxY4fa/AvQHRkB4mFqp9jJuJP1pYebyC8vS6OnN/LPnPEpglKT25GZXjUiNdK9ec8p6q8tqRbSHK38kmgbxHtkmkm/lXMsuNmeI1ea+2QbyuL1RxxNrLr+wUk7H86/AdRKe6Yt0yCWltNvf7UB2crJVq2Uo3LCFef220rW7iqB6uMvbWjuQ2VuV0sk8g3fBzHuhFnG6a8j9HO0ZslMruEBYOOhuodmINl2078muzBSj9uIz6jl/pw0dRXj+DnnC3asdFVKYJspV4iPuY1eeKWEaK20nmWWngxr0kbosqimuy8ZocqqWAtxV5CMi9K59BP2kiF9lsHXOmTs9HP2Q9fRzJddSuFUOxG+tRkcR2n8XE76X9LLM5LJczD/XDYS/OCeyV7i8e1qxyHUb5Ha3fIs7TLLs=
*/