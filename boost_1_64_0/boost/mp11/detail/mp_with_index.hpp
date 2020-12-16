#ifndef BOOST_MP11_DETAIL_MP_WITH_INDEX_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_WITH_INDEX_HPP_INCLUDED

//  Copyright 2017 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/integral.hpp>
#include <boost/mp11/detail/config.hpp>
#include <type_traits>
#include <utility>
#include <cassert>

#if defined( BOOST_MP11_HAS_CXX14_CONSTEXPR )
# define BOOST_MP11_CONSTEXPR14 constexpr
#else
# define BOOST_MP11_CONSTEXPR14
#endif

#if defined( __GNUC__ ) || defined( __clang__ )
# define BOOST_MP11_UNREACHABLE_DEFAULT default: __builtin_unreachable();
#elif defined( _MSC_VER )
# define BOOST_MP11_UNREACHABLE_DEFAULT default: __assume(false);
#else
# define BOOST_MP11_UNREACHABLE_DEFAULT
#endif

namespace boost
{
namespace mp11
{

namespace detail
{

template<std::size_t N> struct mp_with_index_impl_
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        case 7: return std::forward<F>(f)( mp_size_t<K+7>() );
        case 8: return std::forward<F>(f)( mp_size_t<K+8>() );
        case 9: return std::forward<F>(f)( mp_size_t<K+9>() );
        case 10: return std::forward<F>(f)( mp_size_t<K+10>() );
        case 11: return std::forward<F>(f)( mp_size_t<K+11>() );
        case 12: return std::forward<F>(f)( mp_size_t<K+12>() );
        case 13: return std::forward<F>(f)( mp_size_t<K+13>() );
        case 14: return std::forward<F>(f)( mp_size_t<K+14>() );
        case 15: return std::forward<F>(f)( mp_size_t<K+15>() );
        }

        return mp_with_index_impl_<N-16>::template call<K+16>( i-16, std::forward<F>(f) );
    }
};

template<> struct mp_with_index_impl_<0>
{
};

template<> struct mp_with_index_impl_<1>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t /*i*/, F && f )
    {
        return std::forward<F>(f)( mp_size_t<K+0>() );
    }
};

template<> struct mp_with_index_impl_<2>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        }
    }
};

template<> struct mp_with_index_impl_<3>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        }
    }
};

template<> struct mp_with_index_impl_<4>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        }
    }
};

template<> struct mp_with_index_impl_<5>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        }
    }
};

template<> struct mp_with_index_impl_<6>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        }
    }
};

template<> struct mp_with_index_impl_<7>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        }
    }
};

template<> struct mp_with_index_impl_<8>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        case 7: return std::forward<F>(f)( mp_size_t<K+7>() );
        }
    }
};

template<> struct mp_with_index_impl_<9>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        case 7: return std::forward<F>(f)( mp_size_t<K+7>() );
        case 8: return std::forward<F>(f)( mp_size_t<K+8>() );
        }
    }
};

template<> struct mp_with_index_impl_<10>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        case 7: return std::forward<F>(f)( mp_size_t<K+7>() );
        case 8: return std::forward<F>(f)( mp_size_t<K+8>() );
        case 9: return std::forward<F>(f)( mp_size_t<K+9>() );
        }
    }
};

template<> struct mp_with_index_impl_<11>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        case 7: return std::forward<F>(f)( mp_size_t<K+7>() );
        case 8: return std::forward<F>(f)( mp_size_t<K+8>() );
        case 9: return std::forward<F>(f)( mp_size_t<K+9>() );
        case 10: return std::forward<F>(f)( mp_size_t<K+10>() );
        }
    }
};

template<> struct mp_with_index_impl_<12>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        case 7: return std::forward<F>(f)( mp_size_t<K+7>() );
        case 8: return std::forward<F>(f)( mp_size_t<K+8>() );
        case 9: return std::forward<F>(f)( mp_size_t<K+9>() );
        case 10: return std::forward<F>(f)( mp_size_t<K+10>() );
        case 11: return std::forward<F>(f)( mp_size_t<K+11>() );
        }
    }
};

template<> struct mp_with_index_impl_<13>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        case 7: return std::forward<F>(f)( mp_size_t<K+7>() );
        case 8: return std::forward<F>(f)( mp_size_t<K+8>() );
        case 9: return std::forward<F>(f)( mp_size_t<K+9>() );
        case 10: return std::forward<F>(f)( mp_size_t<K+10>() );
        case 11: return std::forward<F>(f)( mp_size_t<K+11>() );
        case 12: return std::forward<F>(f)( mp_size_t<K+12>() );
        }
    }
};

template<> struct mp_with_index_impl_<14>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        case 7: return std::forward<F>(f)( mp_size_t<K+7>() );
        case 8: return std::forward<F>(f)( mp_size_t<K+8>() );
        case 9: return std::forward<F>(f)( mp_size_t<K+9>() );
        case 10: return std::forward<F>(f)( mp_size_t<K+10>() );
        case 11: return std::forward<F>(f)( mp_size_t<K+11>() );
        case 12: return std::forward<F>(f)( mp_size_t<K+12>() );
        case 13: return std::forward<F>(f)( mp_size_t<K+13>() );
        }
    }
};

template<> struct mp_with_index_impl_<15>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        case 7: return std::forward<F>(f)( mp_size_t<K+7>() );
        case 8: return std::forward<F>(f)( mp_size_t<K+8>() );
        case 9: return std::forward<F>(f)( mp_size_t<K+9>() );
        case 10: return std::forward<F>(f)( mp_size_t<K+10>() );
        case 11: return std::forward<F>(f)( mp_size_t<K+11>() );
        case 12: return std::forward<F>(f)( mp_size_t<K+12>() );
        case 13: return std::forward<F>(f)( mp_size_t<K+13>() );
        case 14: return std::forward<F>(f)( mp_size_t<K+14>() );
        }
    }
};

template<> struct mp_with_index_impl_<16>
{
    template<std::size_t K, class F> static BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) call( std::size_t i, F && f )
    {
        switch( i )
        {
        BOOST_MP11_UNREACHABLE_DEFAULT
        case 0: return std::forward<F>(f)( mp_size_t<K+0>() );
        case 1: return std::forward<F>(f)( mp_size_t<K+1>() );
        case 2: return std::forward<F>(f)( mp_size_t<K+2>() );
        case 3: return std::forward<F>(f)( mp_size_t<K+3>() );
        case 4: return std::forward<F>(f)( mp_size_t<K+4>() );
        case 5: return std::forward<F>(f)( mp_size_t<K+5>() );
        case 6: return std::forward<F>(f)( mp_size_t<K+6>() );
        case 7: return std::forward<F>(f)( mp_size_t<K+7>() );
        case 8: return std::forward<F>(f)( mp_size_t<K+8>() );
        case 9: return std::forward<F>(f)( mp_size_t<K+9>() );
        case 10: return std::forward<F>(f)( mp_size_t<K+10>() );
        case 11: return std::forward<F>(f)( mp_size_t<K+11>() );
        case 12: return std::forward<F>(f)( mp_size_t<K+12>() );
        case 13: return std::forward<F>(f)( mp_size_t<K+13>() );
        case 14: return std::forward<F>(f)( mp_size_t<K+14>() );
        case 15: return std::forward<F>(f)( mp_size_t<K+15>() );
        }
    }
};

} // namespace detail

template<std::size_t N, class F> inline BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) mp_with_index( std::size_t i, F && f )
{
    assert( i < N );
    return detail::mp_with_index_impl_<N>::template call<0>( i, std::forward<F>(f) );
}

template<class N, class F> inline BOOST_MP11_CONSTEXPR14 decltype(std::declval<F>()(std::declval<mp_size_t<0>>())) mp_with_index( std::size_t i, F && f )
{
    return mp_with_index<std::size_t{N::value}>( i, std::forward<F>(f) );
}

#undef BOOST_MP11_CONSTEXPR14
#undef BOOST_MP11_UNREACHABLE_DEFAULT

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_WITH_INDEX_HPP_INCLUDED

/* mp_with_index.hpp
1QkAF1pKF39YsIpQIzOdqu7gqiUTEopoBCMnRsNr+W6U9XNjaB+CIc1Qi99uUjgyOozlHvVAhcwHBRrKoQ5/Vdxf1UMoGelzYGnFjJV9Od9HImp9ITELJdqtJNH2ghlFrbMHIQ+rH++g0wuDL7/ZZPvzwE470p7PTazJmnPlrmqy/j0/df/dZbyfRV7wnjvAfm4KuPbzwitc+3m+7Gdi6NcfM8h+XhJQ+/nLvJ/vnM/7eR8VC8jgIR4aEaxVE5NyxPf/cc5H3sukL6T+12D/e7Q4oYMpD286VVMePu63+eNPX6+OL46dIifvhBoPnpJzLj+WX3lQcHuf61ecNB2WHqcd8xwPiXRMvN8Rjje9DUhqFgECUBMoozRHdb7oH/yeShY/7qEKWOwqrVGY4vc+/b6DqjQhiLSuFgx4kaEof64zMzWcXniRHW1fSVCjj1FnVfdAbZqqgpv721SV4XrIAL1TibdrJ9Bn4/HljbjZNsoVEtsOF1mAxtQ6PMfg7TV+Veq3PdGADf6XOwJshrX9MAXGn7wihPRxYsc5CoxXvFgJQXfnKTRSzqHoW9pJ5/e9+sjJ5Yi5LRMjnC65Ha+b6Ddwbx6tAPq8Vw0ctkSSz1otw3E8IkTf5LyRYp0+cLQ6OC2lWizVxGTt0PwfrB3EktyZkJb4Fq6do3YQiqOO9NKx4A8Pl+VWBFTo8JLl3wAsSIXvc1LG15zj7ONram7lffyLswkqth+Sfol1aPwoJanXQDsqpYnPDyjlNFgnDOj1hzoHsjUXOW3VSVvncVvJMY7wftTFOnvKO4PWz6GT/2dt0j7KT+H/C134/4wB8H+Zz43/L9k5/p8yCP4f71P4f6mN/88cDP8/foSD/z/ly8H/p+4W/M/9/wL2P+3ws2dfrfjtKw5xYexrYFnxoU5nL5uhHHKEQg+flVTWZGVJ1iOBi0apZPk2xfNkgedp21rWvKUkFli5AjrW1luKrN4ISlrWtrUUkwxO2mwWt2G5IpQEjTvaEqHmzSWxUAslbgkWP5dT0oSSxVwpfOrcjKLgSNTT01UsWEXgjjbLaO6F+pdw/XyIRUkr2qwgJoWWcO1m8YtYzoyF8ci0bWtABzlY3K6VhGLFXCO8d27B6fFEjRWJvwMGYTaWPsJ5KQ3dL87nkdbvgqlkLl22cdrZxjUH29s4/aGn/CP9lPxzfu5+6Zw7wH7Z4XfLPxfudL/cNXmQ/eLX+KWoLf/MG2y//OkKZ78MzeGXfjpzt+wXtn89j/o/EKM0yuZPqk9QjFKynnaS/0rFJY0ud0mxJ+aeu8HmYfXu2NP1MwSmpbk93nqISHvUyonluyzX9vO/mP95Oa/hzjxULlQPT4NXOffcDqyjvko88ZuPXYRd28yq+FtgKY8TfoswAulZFxwn0Q0AG0yIpOomkObPRBvaTNvmAj8oKtk611ihqY1SeJtsKrk62WxnHx3DzwYoCnfAj9VyH/4qpEHHZxrN/3xd3oUZabPGkrLLbNoMjR8frdoEajNwZou0x8Lt4LMXXi8M0oYZo3qcddPWCwO5KTq7oIc4T8QM7VHIAB8rqtptbtSP6VQcdhHIe9F5w3pAtKpw6izAIlBSfRkCXyiP/rGQP4aaewtjs5f0sKqTwtiH2ix/zte2Lf6KSBeldbdZY0BzB0urLTGkeXNhbF5LD4vfbb1DKsJdJOh2tyX2rkBNXwes0LatQ5u3FMZmrOyJhrsxbfPQChSFu7DirXtW4CWFHdSo4WrU0BoNVYQ7pN0SV7slWrsjtHZHutodqbU7XGt3lKvdUVq7xVq7pa52S7V2g1q7+7ja3Udrt0Brd6ze6FitUZ802gpSS10pVqrSQ7npvro9KX0=
*/