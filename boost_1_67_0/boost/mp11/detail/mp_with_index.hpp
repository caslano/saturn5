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
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
*/