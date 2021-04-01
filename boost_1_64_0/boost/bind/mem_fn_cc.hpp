//
//  bind/mem_fn_cc.hpp - support for different calling conventions
//
//  Do not include this header directly.
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/mem_fn.html for documentation.
//

template<class R, class T> _mfi::BOOST_MEM_FN_NAME(mf0)<R, T> mem_fn(R (BOOST_MEM_FN_CC T::*f) () BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf0)<R, T>(f);
}

template<class R, class T> _mfi::BOOST_MEM_FN_NAME(cmf0)<R, T> mem_fn(R (BOOST_MEM_FN_CC T::*f) () const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf0)<R, T>(f);
}

template<class R, class T, class A1> _mfi::BOOST_MEM_FN_NAME(mf1)<R, T, A1> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf1)<R, T, A1>(f);
}

template<class R, class T, class A1> _mfi::BOOST_MEM_FN_NAME(cmf1)<R, T, A1> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf1)<R, T, A1>(f);
}

template<class R, class T, class A1, class A2> _mfi::BOOST_MEM_FN_NAME(mf2)<R, T, A1, A2> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf2)<R, T, A1, A2>(f);
}

template<class R, class T, class A1, class A2> _mfi::BOOST_MEM_FN_NAME(cmf2)<R, T, A1, A2> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf2)<R, T, A1, A2>(f);
}

template<class R, class T, class A1, class A2, class A3> _mfi::BOOST_MEM_FN_NAME(mf3)<R, T, A1, A2, A3> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf3)<R, T, A1, A2, A3>(f);
}

template<class R, class T, class A1, class A2, class A3> _mfi::BOOST_MEM_FN_NAME(cmf3)<R, T, A1, A2, A3> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf3)<R, T, A1, A2, A3>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4> _mfi::BOOST_MEM_FN_NAME(mf4)<R, T, A1, A2, A3, A4> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf4)<R, T, A1, A2, A3, A4>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4> _mfi::BOOST_MEM_FN_NAME(cmf4)<R, T, A1, A2, A3, A4> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf4)<R, T, A1, A2, A3, A4>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5> _mfi::BOOST_MEM_FN_NAME(mf5)<R, T, A1, A2, A3, A4, A5> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf5)<R, T, A1, A2, A3, A4, A5>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5> _mfi::BOOST_MEM_FN_NAME(cmf5)<R, T, A1, A2, A3, A4, A5> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf5)<R, T, A1, A2, A3, A4, A5>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> _mfi::BOOST_MEM_FN_NAME(mf6)<R, T, A1, A2, A3, A4, A5, A6> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf6)<R, T, A1, A2, A3, A4, A5, A6>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6> _mfi::BOOST_MEM_FN_NAME(cmf6)<R, T, A1, A2, A3, A4, A5, A6> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf6)<R, T, A1, A2, A3, A4, A5, A6>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> _mfi::BOOST_MEM_FN_NAME(mf7)<R, T, A1, A2, A3, A4, A5, A6, A7> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf7)<R, T, A1, A2, A3, A4, A5, A6, A7>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7> _mfi::BOOST_MEM_FN_NAME(cmf7)<R, T, A1, A2, A3, A4, A5, A6, A7> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf7)<R, T, A1, A2, A3, A4, A5, A6, A7>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> _mfi::BOOST_MEM_FN_NAME(mf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7, A8) BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(mf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8>(f);
}

template<class R, class T, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> _mfi::BOOST_MEM_FN_NAME(cmf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8> mem_fn(R (BOOST_MEM_FN_CC T::*f) (A1, A2, A3, A4, A5, A6, A7, A8) const BOOST_MEM_FN_NOEXCEPT)
{
    return _mfi::BOOST_MEM_FN_NAME(cmf8)<R, T, A1, A2, A3, A4, A5, A6, A7, A8>(f);
}

/* mem_fn_cc.hpp
93dB2zA7894hHibKtMWjmK6JW4UPQBwTU2yDq5j8/dzkD5VYjSkNxn0GG7mlQCrI6amTQwSjBFwrqY6EieqHiHzfzar1DUm+YnX/OQ74VCY1H5maWIIHcEzLMpAAH9lhojucWKk5rga11V4aPPdl1BhymkMz7oz4/Dexg6ai0J5f6bT0A/tjt84ujmVQgKi8elu1gV5oZLLFPksDAp1cvZcw8EgEnnWX9VRp3Bm2UKpZIMGRxwKmxJbONCcDsIyYr4d1NZRt5hbYyjYtgRYRLuIPyM8KVSOAE1fEeXuh3zJKanDN2ecZ41LkAqJE1BECpOFzw/5l/Waa3Xbs/XY49vTW1SlzLI+wvmvwjtPcsFwSxCklg9keJ479a/y/9UmWV8TD9d7+5gpoR2kO8q4vjLhFBzHuJk7/bJdbO4QxotNB5czEjcfNVQy6cd6TdVeaWO0rsgR7RybxHBjQi8rVc+3vMdhsNtinqw7XyduUWDRbPgFgnK4LumOvlnd1j9JgOxF4m5hG+q6ohqdEM0rN+ZhZVZYIeS8e5x2QSvFe2jvPgiFVLwM1PKsIzA==
*/