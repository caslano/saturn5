//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_STD_FWD_HPP
#define BOOST_CONTAINER_DETAIL_STD_FWD_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//////////////////////////////////////////////////////////////////////////////
//                        Standard predeclarations
//////////////////////////////////////////////////////////////////////////////

#include <boost/move/detail/std_ns_begin.hpp>
BOOST_MOVE_STD_NS_BEG

template<class T>
class allocator;

template<class T>
struct less;

template<class T>
struct equal_to;

template<class T1, class T2>
struct pair;

template<class T>
struct char_traits;

struct input_iterator_tag;
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;

template<class Container>
class insert_iterator;

struct allocator_arg_t;

struct piecewise_construct_t;

BOOST_MOVE_STD_NS_END
#include <boost/move/detail/std_ns_end.hpp>

#endif //#ifndef BOOST_CONTAINER_DETAIL_STD_FWD_HPP

/* std_fwd.hpp
yyz77fNaYDGXUZ/MrslN64f5yXzM+pLejYWFyCxm5l1ssEki55KF9mewsLC5v5XHwfKFZT5y0VJYqbCRp31yBKxa9JLqWVYOaxAWM+C3a2Gtwqa1rhkN6xL1Ni5s2QNzTYpeLrHXFV0E85PxuL5FT26HJZDxekd+/aMFSyHzM7utsOMKWETEHbh3OOKWfDKs9yPdeWPNeocVKlasWKkwcw4GK3c0l6uS2VHujIX8/ku1o+3bV8uW59G03V5csP1lWAuZzcwcq2BdZBaM73vI+pU4e3J0vcVxH98GCwpb9fxzL8EmCZsY+a0XFiHjvZx/+N4HYfnCzLMmsBKyAB9DdccL+y07t5YMy8xyL5xlju+wejI/sxG5U66CtStxnYp1k3mZmXtWsH4RZ87nYTFTos2sW5hXMVsxv6PlZMUyO8ad9d9vfsHiyfzMzLviYZMUyyLzMWPfUHMVsbiBtI4+yfwmDKsSNmfj9+thTWQ2s7YLD7oV1iHs9Kd2b4D1kfmYLX7H3gGzp9JcYnbvQH8xLE7Y2nfvHA9LJMMy+wsZ/45RsmKTFEsj88LE3xHCZDazX5uOGw/LF3b61MvPhpUKW3nK8tth1cJmXP9MLayRzGI2enzSSlibiLuuafUPsB6Zc2D6jzBPanTO2tFnTYD5yTww8feOWBG3fPfgEliIzM9s1s7ww7B0EXfVpfVzYVmpzushV7F8xQpTnddfqTK+cjEG85wirF6xdjIbJv7G0Cvsj9Xje2Hey2l7YDb88n9cDYsjs5j9mVO9BJYo4pa2fXskLJ2M1/sl3LIEli1y3rr9vRNhhSLupmOPWAkrF/U2HXLLHlidyDl2YtldsGYyp/XQTua0HjpFvSEPN/0Mc10RbXErA1fA/GS8F/PtX1iQzGYWaEpfDEsROWtGrjoMFhY5Nw5IvR+WJ3KWZFzghZWInMXH5rlh1SKn+T0mrEFYx9Pv+mCtot6Kw/LnwbqFnfbrl9fAYqZFW8G/ls2E+cl4vTuaT0mCBYXtum9gOSyZzM8se3PJ2bAwmYeZOabCsmBsveNvPbmsTx/9rScyYEkKrNjEMTP3X2ClIi4wrfl2WLWw4gGnnA1rFDnNdSOsWRjvs5XMy2xfZ9/fYJ0ibk9fxRpYt+jly3XvPQaLSYu2Sz47aDfMT2Yxu/rRa7bCgmQemPjbWUjEmXsssEkizpyHwNKUuAiZFyb+xpen5CxwNLpHzewEcV+xhNmJdI+MW5liFYpVKVajWJ1iDYo1cRP3RlsUayPzM3v09aItsD6yWGalq166ARa40rGXhXFkmGd+um9jvu8LSxLWNadvPSydzGL2xcHP3A7LIvMwM9s7LFfEmec7YEWi3rQX3/4IViFs3zcn3wOrEznNNxBgzWReZuY33bB2Mh+zts+u/QLWJ+z80aFTYfb06Hrd27YvhcWRybG7sP9kdpL8XYliSYqlKJaqWLpimdzEuVSEzMeM/0apkMxmdsYJ+56FlSv1KoXx74tW85ziXKqRzMvM7HtgrcoY2hXrJPMze/rT+WfAYq6KtrnLEutgsWS8zxvWnDVwv81zJZKh3slRY1+Qk8zsFLrXZXqBTVIsjczLzIwdFhZmzrNgucLMe6JghWQ2s7SJridg5cL6jv/g37BaxZoV61SsXzE73dniFUtWLEOxXMWKnW1mJRmWdYDuZ51Ud+42WK0ws/5gjWQeZma9w5rJLGbmXhDuWXWwuMF0z8rse2BdwkxOWA83cY+sTzHX1dFm5jXMo5ilmE+xgGJxigUVCzGTyyVJsRTFUpV66YplKhZR6mU7Gl2TkGGenUr3I3ccXNwKK1KsTNiWrnXdsCrF6oTxfXKTYm0YAyz00/k=
*/