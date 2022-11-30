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
        if( i < N / 2 )
        {
            return mp_with_index_impl_<N/2>::template call<K>( i, std::forward<F>(f) );
        }
        else
        {
            return mp_with_index_impl_<N-N/2>::template call<K+N/2>( i - N/2, std::forward<F>(f) );
        }
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
pFmu22ttkccIf3pJuTH5kbZ4u8REAaRUr1PIVL+c2dw+//Sre3mxHdmQLluLe1hRj7vgXQ6UlZBESox6cGyk/JNIvl3HvTVafMOnFn0ctiEPZdvl63GyRbnTT65NFK5dFaOFTUnG6tNGHhZmD4M6iRnpxP4O4YpNE3cmoSnhzotWd7z10sw2B2rKJGkxuHHXOZltXSSwyo8PSfm1xJP2PNDtMhc0Ytv7g2gwZHNyS4kF/Wye21VvHDrQpqVodnQpa2kaFK50fKf0nm/5zLCE50IbeGt7D03WF3StLIoW6eElG4fEMbAVQeXLxZVK7cGGZSODKelSii1xlDdoWR386Q2+fp07nARfkjbMcJcN6ZZDypn7r6lQyuVdWYJSSsXr079iWrlkJYjN+HcqDksComLX5dyPiOiJ3oaoOwmB8ZfUqGNybncmOgOCW4dLZkNPdBc9pV/iu1QERB7wGFOF6pYidxNzn5IL+kBJNixE2eiC1jT8Cvk+I3FBrNit2B6nHfKJ2BkSZg2CgcTXk02Jet6xWfML3kCfliPtjDwZzyN+Gd01QioS7tx6Lw/HSMflLjPH+r7cKDl7tAzkf76PhpJJmn7mMvwr/NSxqKO+RGeH/zUliKnQxUcdzynMn9CstH6CfoQGw0d6qz0bJJrknPjzNMc+Vr8KRTCM98ge/oLO50RYc+hQ5w5mx5+GftRzAjiErlIQsueDW9LaKYvh5+PoqiFa6J9ioEx3e6ADtd/hBdI7TMQtn9FXV1xc5NwBST6z5cNsl6vnE+8q8Tdbcu2DNyyrcUdy+Yu01DscPb+vj14TH3YJIXnnwNu1QdiiRaNi306qM8C/w8CRZmBCjd+55IHyqQQyoVD49qYUGl51z6ya2F3Bz1iUJhnUoy0hQYcSqA61tKhhVX4b5CfyDy8nX1MCzVnG0Qjp66/2V9gnhbyjpkxIA5sdepwEi1oCGrtKvoc+jN4uxwBHRgjfiilETEz6Y5XXSi3fmphjonsrK527w7tQ5lJe52/P7MkPn0q28c8cAzcJWhd8HO+v1seXvtAQldnfqU3qu/PMDG316NqolEVmMEZkAvb4WlR28nIFmPdJsygoazczqHeR+DM6t5g5Oh/sbpM8Lr81q3f8bBNeflnZySvOJoXLTvI5X/ETftRR+Om6P++gfuzlz9gtzsKbpq2+uNyNiffzCCDFkhhUuwQSaCLfAS8twveohijicXdAkF6/9nE9sYlktbrlz+E3nyWRODKSYIEjkN4vsoREJO6hJBcndCks7zO58HIgQm46i57shavaJwTq9QOs19N/58tHMlKU6AW4wWACJfLdAsZ9Bs4SPjhNTB3QVcIRC0f+ILGSCLhGySZY0VF5qsN3Vi6YAj3Z1Ma/mWvDp1VOaL4YpQaNc9yw34im2doeHY3QiyaAi3bu+WAYgEOscrH5cPHlYU3w0RcHKwrfxAigqyuZO7z2A5SFqmeE38AVCJmweRurxMqx3Ee4HsW0Z9Nnrvwal5uDwvYrJEH2hoLF0w20BJBOF6Ll92raXdE5T5g+0ZYxtMggWS4Ng7myqWyyVAAkyCphnUs1gwXJcJZq1CGLKr6ISKXO+138KhrLzOPH51Tj756lq6gJY7p8kDPzE6LpO/FdTJ4q1JLL271zGdMmqw/jNDzV+cvaOM/34hmajuHMr6Ej1XGx1CbVgNwwCuJVrM914KkIRMtcpeOrxta0HryMeeLsUB2M9QlZHGNVDigzMBLGt37Nen69u+ETXPTZ2APx2Yg1jQywXN3+g90E24kkgnYYYW2jX0hBFe3lYMc22H0wQRiRmtGwdFbLypGQejPly0Pw5Up0O3QWtQGzy14ZA6G8yNGayeDzkTu/shISdHdQjhdxf0LetR7guNn25it5CGK/Ap5Ra4evCibz+v7QpAlpi5MeU92MTaOdOKPI8FZ3CWnPDqUCR8CDA4E8+0EbBnUkJy4L8UuxfM3D+XA157xPAXy1/DOYEk2Y/KGs1lOYd8S58mqK/eXcEeNads5HlZz9ujTrzAgnboExe3stAnfaVgvc00IZJZCQPmXeeubMxpL+OH1sh2D7A4SXGve75po7RAzik1zgmBKr8OLsbJv9y5R0/nHFVMVkNPdvkr1dxYVateWGhAduHV0n3RoZQhIJOvR2nRrtJPVzWyFymsugb1/zuyF31TIOUHzUkaria1MevfJYkdWLGjYJ38wUukW0wwLWYN5VAevWJlSx928y+lzjXCEJUVTEUp3VbbJUzsI6VxP375ws/oZlb5MqUXTuihUFanQKgeqTerF2PV5cTX2H9Xl7DKrQj8Ocg6X8JdBXN0m0I2I1h8we3B8OdRgpf94mRokzTrwNfMQIE/JOix67UJ+SALWLKBNXJbNF7Q1wfCo6s321XK6zZ+STxljlKeOo29yyqiXc9QRczSUqKDk580Y4c8cdnd1wPznqBnHxuFL8sdnoCb6KOl0JDKLxO76SLXH5y3Lvs0zmtur0rWow6/BFmmisNiTVo9m3vWi9Q53d2EobT+8UEvqh5Ll8e/2A5SPsk0lyEEq0JiW/pAidOF7bqrg/3NxellFlB3NjLk+LT9A3RxvMoDwaUa59zS2b29wy2VMYqQnoaXsPDBx6zKdrC4w+lNAZ3H0Jr3Lr+Ka+sc0Tqt3mVGKKiJdzZLnmMlgZGSt2uSURQ2MhvJCxVnVxuW5zNAmlyZfKyATOVL4LTdtECNDHT8IouTJTehsBYg/456QUfekPDjG/C3qIRHpmv/OOkzEejE0J+iekYNuHW3MXLg3L4axYHNOd1kqEChzZvXpe+pbgLhsxxTc1CJPEpKkxqD68GxgwEXWvc7/UD0KvYzDbTGWdT0OW3XiUggmjj0N3aHDZW4AbhZ/XfpbUH+opcOjAJ6rGQOsiYhyn6dBHQh3m0LaojSV4lCpOL57W75bh8cVPOWCTVotxdkikpYICUy9TW6dtRKXYd6FVV/JxzoYv0FfRNIdi9wUkjw/XCvA/5I5Cm1umDsOnrkQnmgt5EWvTjXJxayBOPywC/6Ut0YItkSUw4jYxlD0M1O4g1jnHPwTu/sr8mmh1oSN0bNhaVJgIyH5BPPwAfb0OV1uz2GXt+SzE0Fq3rqG9R3mQjlUdZ/PXUolb0J/BtlyhBqg4ckXC8fhgkSevdzIiMnxV8kaPHlzbNr/m4fLFcloR6bWvQXIZi3L0zY9kPlBLHb1mzCG4sfao3Ir8ysqBsQ1GdSZehgMvN4c8RCHZYCbiQCcd9epcqaGdhGRSQD58/p8tdhZfg35OYX8SNZMTlDqdgkI3tiQlesDDatUS868XAcDDTgTdywUCQ2jvJlResTCrxHofAXCIGSHonJ1fTu81vFz5ClB2V8hNjpBHoQYa7RWmr3JeM38n+JY+wDHwQzXsPsJP6L6DYiaGPKCsUCDDBOKOp/CfxQxHp4Q++TbltsMntXXc3UZ9D3IxENnK5eeNJRKnNXKyyOCF56sy8Inf37Y6dYPP3U87ntiFy2IfKvhqL0pCvmc+szIl5oF5aPKEtd2ynmeVokcyDEaZx/ntCQZtHpLB4OBrWyyAibuVy3drtt60WSqebVfxQHrm+AZgUrQ1QJuvqdZAtTZ0NrzqnO0qw9QL1MBQlj71RhZg/BJJ+kXPsJGtzVeG77802d0bNBhjTGllJQNcB/QoDi/qKIMI4ZQ6kt8bW7SXsbplRohxZhC+kI1YQeCiNg62cep1+YuQ6tvXVL39f8isRVAkKuPBHtgGs+aCYBiayKvNab7ym1PzO8PptIkfqpJxSdICVXmjy3m+sCeZx9Ropsm4aV25ws++sTbTwc3gcOWcbQrjsZi4X/MnGiw3YufGD7exKXAzspLyEh9am9QMa/iRcY4cBeFyfFbXN2Bhp0zbFsmS7v7F8JXrgxLAJDC4yrXiuKGAdSen1KUKn126gtmTquyJ8mO35nNeb7pNcpTe2Z8ZPadepy9Pj5cqa/BQx9MsIlK3J1gBTDTdJncklDmvn0Ngynamq5TWC3PXjpEftLzbWlw9gmg8HdpEjOw+rrm2HY0c6ycakOJotA06KWFB23wVdQI7FDojUAFe29mmkuTu+wMSuP7FDo0AR9RkamQ3WDGQValX0jmVXTkH3k4WaMs6b1hxpwrervvEuMD/jgPXOmahfQxujezxmn/SQuuIDEi0MSqUYxlh2LR4mz6LCs23489n0mWskyvO0dC2B1oSPIPwu7ti2W/VvnZF72NcaeWg45RkN5jfH0BFq1iQAO1Ljb3D0CMl9uYnDAX93S5B7J7LqDhuwUXyVJ8RO1Q3u6CvhsEanaLD1mX1WYO5kUGF/mhxcYiZ8enjV/5h6dV3fKawYiy/OoHN5Vaaaac25C5/LHW73T3yv02VzPBxuaf2Qlj98aM7JaN0/5d8v+D7edPlgWjs0Eoiv0FpZm7XO9fKtfJp80jlFbQAtcYgspnVIriy6iBkiuUSbF9TtCrWtoh7eacexk5hPipXF1Mgnm7VlYCFbOiLcuhKZvzQDynCRQBIW+kdMO73XtCvKsCRBjG9UTHLqkJOVXsKc/W8vg7AR0sBAxSGTlEiILW2R3uGxvtkcQ8saQkWGuwkOsD0SsPlIKN8O8HhkA+vP3+VwKGu2wiaMcdvT1613Yem5lCPdCAESn8ch/GrC0mX4l9UtBSxpT+8DHhUHxA7A7VOKBx+jUJNLynUJDX0OYqYGAh8vOWBtX5QYiK8gnTpcoAlu2WlvcBFzvFB66t0HgtTmg8vK11PZid/Mr1IY6s5I8WNaQRXPcMzTWK9qyzwl5y4t8mU8jyw2VylzcVrh7vLxCbJy8zdqr9KAh7zXvkE3t7d05OYli/8TGjwvYo/8OwBEGPmY7KuhgE8fRUcHca9gyx1NzP/7SNVFzPf5erZCK0qQuKgrgRmeBVfBDalpA8T0b/50KUX5BzI6RgS10jMkEGFvhoYttTUCPpOY0z+GsQ9pO6Y6X0FlaFIvM1NY8ZNTp9SyO35fkxI3ua+QC26ZaC4kBHJ6/nOpa3KMcN3LtMr8JZ3m2AnQHcAGsl+ArnIENcbLkM6MnD6cfRfAUyLyNGpvcjW5O+t/6+FIO2iAN87qJMfrZpA8zkwmgw1o0wKfXf64TXbGxCi0C/Xv+v2rY2u8gvcWTtau9pD1boKXktavpssJxubDOwsEVxlJiS+tnJRhdAZKeulocJL1CIjV+7JTy1HUy3KZDUuVfcff+cm+SqSDB95/fmJBwtiTnhia/JZQ08mKXJy7Knw4o8MsJIo6L9nPTeuFKPThY2vg0hMndC9Mx5+XTpnGill7bekod/inkIiq8xVwzWv91Vwjniw9XT31pKDAkrWDrsd8zlJxCJ8CICjrSKddOD05i8G26gJMdmqSWR+bOmz9/MCJJuZvVavRRtrSqwrjJE8kQadrHhHyAmNOPFo97gjAK8pZCg/IWtGKgTYTmBKeyGBVWKPvuAUbTncUq/H2XcVY1eyrFyts5J/BFzUjJEDIUOtFle0p/xHRkM/udsc0JTPpY56gYp4xzxfUMl5hetcV5DKMhjjmjUsgc/MpHlBEXPNtDNqQDGoEnlT/KoibUcC9bLaxU5WtqDsrYbNL6+CLU9vhl/BOuRJBZq2E6tj4ziozohf+sAPHfws0BANSRN5OQTS6KQLNelTNDjEcrwV7R2RGfnJBRV/WJrwYKMPH80DDe6YZyAhgnahRRtqta8fQmsLpbIHDUrk3QqWunlM6y6VTilMJ7bWLEJCTBd3/QSVLkqn/JhSftdjEDrI8abZXtMnI74Q9x6gl07rmZ399vcgwLBFKH9uDOWt8nawFnYVO9cdwPIhFQD5b+NlP3TSvbmHM15kHq/9SbNTLOCUWJzv2ID3CLc8CxgImk903NrcmU0Xkcg20O1bMUVt18cCFuQvkFclJ+cy8B0kJD82PHUwISpKExZH05Bl9hf6H6RuWxOxUtsU8pCHOZF3x4NPqDoI+pCrvmrnBdkyU+NxtfNGOehVIvb49Bs9BiBeGjPvVzDS/MtdMIPW4ZgtygvKpOgNi5MTS3ymxCZlo939CDZKxrleXHSMLfKXAilAqVJheSrEr+UaBRwaMCraHgFuLhSHcBF/PsnHyqw69BsJOoH9XnvWvaij+61g6FwP0xRllsPkY261JHPHSwObeXA/pYIOSViWvC8amlvhfNcixZWxizxT09bp/mchlVH1uoIWounz3N3AzaXJ7Y9pi0nTLGvnnpsF18Ab9o14jA8qgbNuiKKZhTJ2AbFGC0DJAEAQEAAAAAACAAAQAAAoALu7u7u7u7u7Xbjiwu7u4e5id91d3d3d3d3dRMCKaMCMAAAGAIIBMtfpkdRENgU2Ua2RaBGUnpRONE9aTs0H+RP6RPyRf6KMlHqkcCwR9BYNczrDBATQUDlBTrATTw2AlkDjBHEIBKCEABgAAAAAGQAImOtdvu+S+n0Lda0SL9rnOpzuE5msfPBarauo8xXlzIJ/PSXHHzZ1KlRgw2ASsZgY6Tlw0L3WExbepBH1mJP24OmMKPvG9lHS3imGx62XcHnDCzLQGibSZsKvPXJ3gfYq9PzZOCkK5UmKjqq88jYCUvaV9r2gOFQfiIwcMoYiXCaQKOXaJu90WN0UZBwz1BLQ1O+TeDAsfmp99S/3DIFETPVnCqlrEO+tYk/EwRKvYr2264Kp9qM6Dmo0E3i3lwajl7L52odnMKBWkzM6/4APqTVR9nkqL6vUqi492nT0UhbZ6iDRziY2rHlDgD+DOlk0AEqwuRIaOH7aCOKPD+N9J261zp4BuiHFByHdhT2VzEBeKMeRyMsv72J6kmA+F8vXPmxY+3G/OOoaW44i49fyHgeHX2C6JFSBHZHze93QuE0UfwWk30BhE5FPvM9IhtEiz01o58qiiL9Izl8oAKKeQad/snPsdio582aeEkibn0wIcLCOVtkArqhpnW9nVyKRpR8Vxl20RybL9PqC7OTMbxpCN0DorrIgVye99/smgs3V+3vqn03XkFxSKw0k0T4TtYkqDLolLznEpBWwP5tjcfQ/lR3E8/l61QGuIkwWaSF3esDS8PxNMM7mqBnpFNUG7HHTpY0NU1Kmpf6RagjuZ3l6dEs9qg9pkDw8kX+d1MMCkFEpuWwT4k8Fg0JmAhA7QLwjz+NQVZPe/IsLopTaslUXuVTIyyBY9q/Nmybdb/382Q/7+vYY592+B8YQHL76OHfbJTt39RuiAWhf23xFwazavuo1bJUhk7y0g7xbLjDXs2WcCR1/ZcEZR0eZTIUpMRjX5scKf+YjixdMJOGMIsgwDpfchkC+kFNYE2Vxa5Ho+oiOKtpXegWRj9RnnrU2HEuYXy2oihki+Zo8QxquF/bfdcemo78Xf/aglBDYVSiy5IeImaT1PqtwJMFhSoFYj8eFTCackH9QBvYs+3jbVfFx+uszJo8lCc6sH5nftiPSn9eicbrcx7YqnndFLrje/eraRW9aFts/Dy1y/c9W+dkSWiAL6LrKmUNzS9DLmO6edl+r7xTjz8aJJoNei0S5hRwb3Vhy85vvWizg36L4LvLvaDrRZNzp6I/831x2J+r3XG2yvuLYTtE2XIVCMGE3JLd2rWN7u2gKpZfJMrNnTo3MP3OrQ5LGqYGs
*/