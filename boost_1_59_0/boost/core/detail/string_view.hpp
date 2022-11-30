#ifndef BOOST_CORE_STRING_VIEW_HPP_INCLUDED
#define BOOST_CORE_STRING_VIEW_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// boost::core::basic_string_view<Ch>
//
// Copyright 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/enable_if.hpp>
#include <boost/core/is_same.hpp>
#include <boost/assert.hpp>
#include <boost/assert/source_location.hpp>
#include <boost/throw_exception.hpp>
#include <boost/config.hpp>
#include <string>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <cstddef>
#include <cstring>
#include <climits>
#include <iosfwd>
#include <ios>
#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
# include <string_view>
#endif
#if !defined(BOOST_NO_CXX20_HDR_CONCEPTS) // std::common_reference_with
# include <type_traits>
#endif

namespace boost
{

template<class Ch, class Tr> class basic_string_view;

namespace core
{
namespace detail
{

template<class Ch> struct sv_to_uchar
{
    typedef Ch type;
};

template<> struct sv_to_uchar<char>
{
    typedef unsigned char type;
};

#if defined(__GNUC__) && __GNUC__ * 100 + __GNUC_MINOR__ >= 406
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wtype-limits"
#endif

template<class Ch> BOOST_CXX14_CONSTEXPR std::size_t find_first_of( Ch const* p_, std::size_t n_, Ch const* s, std::size_t pos, std::size_t n ) BOOST_NOEXCEPT
{
    typedef typename sv_to_uchar<Ch>::type UCh;

    unsigned char table[ 256 ] = {};

    bool use_table = true;

    for( std::size_t j = 0; j < n; ++j )
    {
        UCh ch = s[ j ];

        if( ch >= 0 && ch < 256 )
        {
            table[ ch ] = 1;
        }
        else
        {
            use_table = false;
            break;
        }
    }

    if( use_table )
    {
        for( std::size_t i = pos; i < n_; ++i )
        {
            UCh ch = p_[ i ];
            if( ch >= 0 && ch < 256 && table[ ch ] ) return i;
        }
    }
    else if( n >= 16 )
    {
        for( std::size_t i = pos; i < n_; ++i )
        {
            Ch ch = p_[ i ];
            if( std::char_traits<Ch>::find( s, n, ch ) != 0 ) return i;
        }
    }
    else
    {
        for( std::size_t i = pos; i < n_; ++i )
        {
            Ch ch = p_[ i ];

            for( std::size_t j = 0; j < n; ++j )
            {
                if( s[ j ] == ch ) return i;
            }
        }
    }

    return static_cast<std::size_t>( -1 );
}

template<class Ch> BOOST_CXX14_CONSTEXPR std::size_t find_last_of( Ch const* p_, Ch const* s, std::size_t pos, std::size_t n ) BOOST_NOEXCEPT
{
    typedef typename sv_to_uchar<Ch>::type UCh;

    unsigned char table[ 256 ] = {};

    bool use_table = true;

    for( std::size_t j = 0; j < n; ++j )
    {
        UCh ch = s[ j ];

        if( ch >= 0 && ch < 256 )
        {
            table[ ch ] = 1;
        }
        else
        {
            use_table = false;
            break;
        }
    }

    std::size_t const npos = static_cast< std::size_t >( -1 );

    std::size_t i = pos;

    if( use_table )
    {
        do
        {
            UCh ch = p_[ i ];

            if( ch >= 0 && ch < 256 && table[ ch ] ) return i;

            --i;
        }
        while( i != npos );
    }
    else if( n >= 16 )
    {
        do
        {
            Ch ch = p_[ i ];

            if( std::char_traits<Ch>::find( s, n, ch ) != 0 ) return i;

            --i;
        }
        while( i != npos );
    }
    else
    {
        do
        {
            Ch ch = p_[ i ];

            for( std::size_t j = 0; j < n; ++j )
            {
                if( s[ j ] == ch ) return i;
            }

            --i;
        }
        while( i != npos );
    }

    return npos;
}

template<class Ch> BOOST_CXX14_CONSTEXPR std::size_t find_first_not_of( Ch const* p_, std::size_t n_, Ch const* s, std::size_t pos, std::size_t n ) BOOST_NOEXCEPT
{
    typedef typename sv_to_uchar<Ch>::type UCh;

    unsigned char table[ 256 ] = {};

    bool use_table = true;

    for( std::size_t j = 0; j < n; ++j )
    {
        UCh ch = s[ j ];

        if( ch >= 0 && ch < 256 )
        {
            table[ ch ] = 1;
        }
        else
        {
            use_table = false;
            break;
        }
    }

    if( use_table )
    {
        for( std::size_t i = pos; i < n_; ++i )
        {
            UCh ch = p_[ i ];
            if( !( ch >= 0 && ch < 256 && table[ ch ] ) ) return i;
        }
    }
    else if( n >= 16 )
    {
        for( std::size_t i = pos; i < n_; ++i )
        {
            Ch ch = p_[ i ];
            if( std::char_traits<Ch>::find( s, n, ch ) == 0 ) return i;
        }
    }
    else
    {
        for( std::size_t i = pos; i < n_; ++i )
        {
            Ch ch = p_[ i ];

            bool r = false;

            for( std::size_t j = 0; j < n; ++j )
            {
                if( s[ j ] == ch )
                {
                    r = true;
                    break;
                }
            }

            if( !r ) return i;
        }
    }

    return static_cast<std::size_t>( -1 );
}

template<class Ch> BOOST_CXX14_CONSTEXPR std::size_t find_last_not_of( Ch const* p_, Ch const* s, std::size_t pos, std::size_t n ) BOOST_NOEXCEPT
{
    typedef typename sv_to_uchar<Ch>::type UCh;

    unsigned char table[ 256 ] = {};

    bool use_table = true;

    for( std::size_t j = 0; j < n; ++j )
    {
        UCh ch = s[ j ];

        if( ch >= 0 && ch < 256 )
        {
            table[ ch ] = 1;
        }
        else
        {
            use_table = false;
            break;
        }
    }

    std::size_t const npos = static_cast< std::size_t >( -1 );

    std::size_t i = pos;

    if( use_table )
    {
        do
        {
            UCh ch = p_[ i ];

            if( !( ch >= 0 && ch < 256 && table[ ch ] ) ) return i;

            --i;
        }
        while( i != npos );
    }
    else if( n >= 16 )
    {
        do
        {
            Ch ch = p_[ i ];

            if( std::char_traits<Ch>::find( s, n, ch ) == 0 ) return i;

            --i;
        }
        while( i != npos );
    }
    else
    {
        do
        {
            Ch ch = p_[ i ];

            bool r = false;

            for( std::size_t j = 0; j < n; ++j )
            {
                if( s[ j ] == ch )
                {
                    r = true;
                    break;
                }
            }

            if( !r ) return i;

            --i;
        }
        while( i != npos );
    }

    return npos;
}

#if defined(__GNUC__) && __GNUC__ * 100 + __GNUC_MINOR__ >= 406
# pragma GCC diagnostic pop
#endif

} // namespace detail

template<class Ch> class basic_string_view
{
private:

    Ch const* p_;
    std::size_t n_;

public:

    // types

    typedef std::char_traits<Ch> traits_type;
    typedef Ch value_type;
    typedef Ch* pointer;
    typedef Ch const* const_pointer;
    typedef Ch& reference;
    typedef Ch const& const_reference;
    typedef Ch const* const_iterator;
    typedef const_iterator iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef const_reverse_iterator reverse_iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    // npos

    BOOST_STATIC_CONSTEXPR size_type npos = static_cast<size_type>( -1 );

public:

    // construction and assignment

    BOOST_CONSTEXPR basic_string_view() BOOST_NOEXCEPT: p_(), n_()
    {
    }

    BOOST_CONSTEXPR basic_string_view( Ch const* str ) BOOST_NOEXCEPT: p_( str ), n_( traits_type::length( str ) )
    {
    }

    BOOST_CONSTEXPR basic_string_view( Ch const* str, size_type len ) BOOST_NOEXCEPT: p_( str ), n_( len )
    {
    }

    template<class End> BOOST_CXX14_CONSTEXPR basic_string_view( Ch const* begin, End end,
        typename boost::enable_if<is_same<End, Ch const*> >::type* = 0 ) BOOST_NOEXCEPT: p_( begin ), n_( end - begin )
    {
        BOOST_ASSERT( end - begin >= 0 );
    }

    template<class A> basic_string_view( std::basic_string<Ch, std::char_traits<Ch>, A> const& str ) BOOST_NOEXCEPT: p_( str.data() ), n_( str.size() )
    {
    }

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)

    basic_string_view( std::basic_string_view<Ch, std::char_traits<Ch> > const& str ) BOOST_NOEXCEPT: p_( str.data() ), n_( str.size() )
    {
    }

#endif

    template<class Ch2> basic_string_view( boost::basic_string_view<Ch2, std::char_traits<Ch2> > const& str,
        typename boost::enable_if<is_same<Ch, Ch2> >::type* = 0 ) BOOST_NOEXCEPT: p_( str.data() ), n_( str.size() )
    {
    }

    // BOOST_CONSTEXPR basic_string_view& operator=( basic_string_view const& ) BOOST_NOEXCEPT & = default;

    // conversions

    template<class A> operator std::basic_string<Ch, std::char_traits<Ch>, A>() const
    {
        return std::basic_string<Ch, std::char_traits<Ch>, A>( data(), size() );
    }

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)

    template<class Ch2, class En = typename boost::enable_if<is_same<Ch2, Ch> >::type>
    operator std::basic_string_view<Ch2>() const BOOST_NOEXCEPT
    {
        return std::basic_string_view<Ch>( data(), size() );
    }

#endif

    template<class Ch2> operator boost::basic_string_view<Ch2,
        typename boost::enable_if<boost::core::is_same<Ch2, Ch>, std::char_traits<Ch> >::type> () const BOOST_NOEXCEPT
    {
        return boost::basic_string_view< Ch, std::char_traits<Ch> >( data(), size() );
    }

    // iterator support

    BOOST_CONSTEXPR const_iterator begin() const BOOST_NOEXCEPT
    {
        return p_;
    }

    BOOST_CONSTEXPR const_iterator end() const BOOST_NOEXCEPT
    {
        return p_ + n_;
    }

    BOOST_CONSTEXPR const_iterator cbegin() const BOOST_NOEXCEPT
    {
        return p_;
    }

    BOOST_CONSTEXPR const_iterator cend() const BOOST_NOEXCEPT
    {
        return p_ + n_;
    }

    BOOST_CONSTEXPR const_reverse_iterator rbegin() const BOOST_NOEXCEPT
    {
        return const_reverse_iterator( end() );
    }

    BOOST_CONSTEXPR const_reverse_iterator rend() const BOOST_NOEXCEPT
    {
        return const_reverse_iterator( begin() );
    }

    BOOST_CONSTEXPR const_reverse_iterator crbegin() const BOOST_NOEXCEPT
    {
        return const_reverse_iterator( end() );
    }

    BOOST_CONSTEXPR const_reverse_iterator crend() const BOOST_NOEXCEPT
    {
        return const_reverse_iterator( begin() );
    }

    // capacity

    BOOST_CONSTEXPR size_type size() const BOOST_NOEXCEPT
    {
        return n_;
    }

    BOOST_CONSTEXPR size_type length() const BOOST_NOEXCEPT
    {
        return n_;
    }

    BOOST_CONSTEXPR size_type max_size() const BOOST_NOEXCEPT
    {
        return npos / sizeof( Ch );
    }

    BOOST_CONSTEXPR bool empty() const BOOST_NOEXCEPT
    {
        return n_ == 0;
    }

    // element access

    BOOST_CXX14_CONSTEXPR const_reference operator[]( size_type pos ) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT( pos < size() );
        return p_[ pos ];
    }

    BOOST_CXX14_CONSTEXPR const_reference at( size_type pos ) const
    {
        if( pos >= size() )
        {
            boost::throw_exception( std::out_of_range( "basic_string_view::at" ), BOOST_CURRENT_LOCATION );
        }

        return p_[ pos ];
    }

    BOOST_CXX14_CONSTEXPR const_reference front() const BOOST_NOEXCEPT
    {
        BOOST_ASSERT( !empty() );
        return p_[ 0 ];
    }

    BOOST_CXX14_CONSTEXPR const_reference back() const BOOST_NOEXCEPT
    {
        BOOST_ASSERT( !empty() );
        return p_[ n_ - 1 ];
    }

    BOOST_CONSTEXPR const_pointer data() const BOOST_NOEXCEPT
    {
        return p_;
    }

    // modifiers

    BOOST_CXX14_CONSTEXPR void remove_prefix( size_type n ) BOOST_NOEXCEPT
    {
        BOOST_ASSERT( n <= size() );

        p_ += n;
        n_ -= n;
    }

    BOOST_CXX14_CONSTEXPR void remove_suffix( size_type n ) BOOST_NOEXCEPT
    {
        BOOST_ASSERT( n <= size() );

        n_ -= n;
    }

    BOOST_CXX14_CONSTEXPR void swap( basic_string_view& s ) BOOST_NOEXCEPT
    {
        std::swap( p_, s.p_ );
        std::swap( n_, s.n_ );
    }

    // string operations

    BOOST_CXX14_CONSTEXPR size_type copy( Ch* s, size_type n, size_type pos = 0 ) const
    {
        if( pos > size() )
        {
            boost::throw_exception( std::out_of_range( "basic_string_view::copy" ), BOOST_CURRENT_LOCATION );
        }

        std::size_t rlen = (std::min)( n, size() - pos );

        traits_type::copy( s, data() + pos, rlen );

        return rlen;
    }

    BOOST_CXX14_CONSTEXPR basic_string_view substr( size_type pos = 0, size_type n = npos ) const
    {
        if( pos > size() )
        {
            boost::throw_exception( std::out_of_range( "basic_string_view::substr" ), BOOST_CURRENT_LOCATION );
        }

        std::size_t rlen = (std::min)( n, size() - pos );

        return basic_string_view( data() + pos, rlen );
    }

    // compare

    BOOST_CXX14_CONSTEXPR int compare( basic_string_view str ) const BOOST_NOEXCEPT
    {
        std::size_t rlen = (std::min)( size(), str.size() );

        int cmp = traits_type::compare( data(), str.data(), rlen );

        if( cmp != 0 ) return cmp;

        if( size() == str.size() ) return 0;
        
        return size() < str.size()? -1: +1;
    }

    BOOST_CONSTEXPR int compare( size_type pos1, size_type n1, basic_string_view str ) const
    {
        return substr( pos1, n1 ).compare( str );
    }

    BOOST_CONSTEXPR int compare( size_type pos1, size_type n1, basic_string_view str, size_type pos2, size_type n2 ) const
    {
        return substr( pos1, n1 ).compare( str.substr( pos2, n2 ) );
    }

    BOOST_CONSTEXPR int compare( Ch const* s ) const BOOST_NOEXCEPT
    {
        return compare( basic_string_view( s ) );
    }

    BOOST_CONSTEXPR int compare( size_type pos1, size_type n1, Ch const* s ) const
    {
        return substr( pos1, n1 ).compare( basic_string_view( s ) );
    }

    BOOST_CONSTEXPR int compare( size_type pos1, size_type n1, Ch const* s, size_type n2 ) const
    {
        return substr( pos1, n1 ).compare( basic_string_view( s, n2 ) );
    }

    // starts_with

    BOOST_CONSTEXPR bool starts_with( basic_string_view x ) const BOOST_NOEXCEPT
    {
        return size() >= x.size() && traits_type::compare( data(), x.data(), x.size() ) == 0;
    }

    BOOST_CONSTEXPR bool starts_with( Ch x ) const BOOST_NOEXCEPT
    {
        return !empty() && front() == x;
    }

    BOOST_CONSTEXPR bool starts_with( Ch const* x ) const BOOST_NOEXCEPT
    {
        return starts_with( basic_string_view( x ) );
    }

    // ends_with

    BOOST_CONSTEXPR bool ends_with( basic_string_view x ) const BOOST_NOEXCEPT
    {
        return size() >= x.size() && traits_type::compare( data() + size() - x.size(), x.data(), x.size() ) == 0;
    }

    BOOST_CONSTEXPR bool ends_with( Ch x ) const BOOST_NOEXCEPT
    {
        return !empty() && back() == x;
    }

    BOOST_CONSTEXPR bool ends_with( Ch const* x ) const BOOST_NOEXCEPT
    {
        return ends_with( basic_string_view( x ) );
    }

    // find

    BOOST_CONSTEXPR size_type find( basic_string_view str, size_type pos = 0 ) const BOOST_NOEXCEPT
    {
        return find( str.data(), pos, str.size() );
    }

    BOOST_CXX14_CONSTEXPR size_type find( Ch c, size_type pos = 0 ) const BOOST_NOEXCEPT
    {
        if( pos >= size() ) return npos;

        Ch const* r = traits_type::find( data() + pos, size() - pos, c );

        return r? r - data(): npos;
    }

    BOOST_CXX14_CONSTEXPR size_type find( Ch const* s, size_type pos, size_type n ) const BOOST_NOEXCEPT
    {
        if( n == 1 ) return find( s[0], pos );

        if( pos + n > size() ) return npos;
        if( n == 0 ) return pos;

        Ch const* p = data() + pos;
        Ch const* last = data() + size() - n + 1;

        for( ;; )
        {
            p = traits_type::find( p, last - p, s[0] );

            if( p == 0 ) break;

            if( traits_type::compare( p + 1, s + 1, n - 1 ) == 0 ) return p - data();

            ++p;
        }

        return npos;
    }

    BOOST_CONSTEXPR size_type find( Ch const* s, size_type pos = 0 ) const BOOST_NOEXCEPT
    {
        return find( s, pos, traits_type::length( s ) );
    }

    // rfind

    BOOST_CONSTEXPR size_type rfind( basic_string_view str, size_type pos = npos ) const BOOST_NOEXCEPT
    {
        return rfind( str.data(), pos, str.size() );
    }

    BOOST_CXX14_CONSTEXPR size_type rfind( Ch c, size_type pos = npos ) const BOOST_NOEXCEPT
    {
        size_type n = size();

        if( n == 0 )
        {
            return npos;
        }

        if( pos > n - 1 )
        {
            pos = n - 1;
        }

        do
        {
            if( p_[ pos ] == c ) return pos;
            --pos;
        }
        while( pos != npos );

        return npos;
    }

    BOOST_CXX14_CONSTEXPR size_type rfind( Ch const* s, size_type pos, size_type n ) const BOOST_NOEXCEPT
    {
        if( n > size() ) return npos;

        if( pos > size() - n )
        {
            pos = size() - n;
        }

        if( n == 0 ) return pos;

        for( ;; )
        {
            size_type xpos = rfind( s[0], pos );

            if( xpos == npos ) return npos;

            if( traits_type::compare( data() + xpos, s, n ) == 0 ) return xpos;

            if( xpos == 0 ) return npos;

            pos = xpos - 1;
        }
    }

    BOOST_CONSTEXPR size_type rfind( Ch const* s, size_type pos = npos ) const BOOST_NOEXCEPT
    {
        return rfind( s, pos, traits_type::length( s ) );
    }

    // find_first_of

    BOOST_CXX14_CONSTEXPR size_type find_first_of( basic_string_view str, size_type pos = 0 ) const BOOST_NOEXCEPT
    {
        return find_first_of( str.data(), pos, str.size() );
    }

    BOOST_CONSTEXPR size_type find_first_of( Ch c, size_type pos = 0 ) const BOOST_NOEXCEPT
    {
        return find( c, pos );
    }

    BOOST_CXX14_CONSTEXPR size_type find_first_of( Ch const* s, size_type pos, size_type n ) const BOOST_NOEXCEPT
    {
        if( n == 0 || pos >= size() ) return npos;
        if( n == 1 ) return find( s[0], pos );

        return detail::find_first_of( data(), size(), s, pos, n );
    }

    BOOST_CXX14_CONSTEXPR size_type find_first_of( Ch const* s, size_type pos = 0 ) const BOOST_NOEXCEPT
    {
        return find_first_of( s, pos, traits_type::length( s ) );
    }

    // find_last_of

    BOOST_CXX14_CONSTEXPR size_type find_last_of( basic_string_view str, size_type pos = npos ) const BOOST_NOEXCEPT
    {
        return find_last_of( str.data(), pos, str.size() );
    }

    BOOST_CONSTEXPR size_type find_last_of( Ch c, size_type pos = npos ) const BOOST_NOEXCEPT
    {
        return rfind( c, pos );
    }

    BOOST_CXX14_CONSTEXPR size_type find_last_of( Ch const* s, size_type pos, size_type n ) const BOOST_NOEXCEPT
    {
        if( n == 1 )
        {
            return rfind( s[0], pos );
        }

        size_type m = size();

        if( m == 0 )
        {
            return npos;
        }

        if( pos > m - 1 )
        {
            pos = m - 1;
        }

        return detail::find_last_of( data(), s, pos, n );
    }

    BOOST_CXX14_CONSTEXPR size_type find_last_of( Ch const* s, size_type pos = npos ) const BOOST_NOEXCEPT
    {
        return find_last_of( s, pos, traits_type::length( s ) );
    }

    // find_first_not_of

    BOOST_CXX14_CONSTEXPR size_type find_first_not_of( basic_string_view str, size_type pos = 0 ) const BOOST_NOEXCEPT
    {
        return find_first_not_of( str.data(), pos, str.size() );
    }

    BOOST_CXX14_CONSTEXPR size_type find_first_not_of( Ch c, size_type pos = 0 ) const BOOST_NOEXCEPT
    {
        for( std::size_t i = pos; i < n_; ++i )
        {
            if( p_[ i ] != c ) return i;
        }

        return npos;
    }

    BOOST_CXX14_CONSTEXPR size_type find_first_not_of( Ch const* s, size_type pos, size_type n ) const BOOST_NOEXCEPT
    {
        if( pos >= size() ) return npos;
        if( n == 1 ) return find_first_not_of( s[0], pos );

        return detail::find_first_not_of( data(), size(), s, pos, n );
    }

    BOOST_CXX14_CONSTEXPR size_type find_first_not_of( Ch const* s, size_type pos = 0 ) const BOOST_NOEXCEPT
    {
        return find_first_not_of( s, pos, traits_type::length( s ) );
    }

    // find_last_not_of

    BOOST_CXX14_CONSTEXPR size_type find_last_not_of( basic_string_view str, size_type pos = npos ) const BOOST_NOEXCEPT
    {
        return find_last_not_of( str.data(), pos, str.size() );
    }

    BOOST_CXX14_CONSTEXPR size_type find_last_not_of( Ch c, size_type pos = npos ) const BOOST_NOEXCEPT
    {
        size_type m = size();

        if( m == 0 )
        {
            return npos;
        }

        if( pos > m - 1 )
        {
            pos = m - 1;
        }

        do
        {
            if( p_[ pos ] != c ) return pos;
            --pos;
        }
        while( pos != npos );

        return npos;
    }

    BOOST_CXX14_CONSTEXPR size_type find_last_not_of( Ch const* s, size_type pos, size_type n ) const BOOST_NOEXCEPT
    {
        if( n == 1 )
        {
            return find_last_not_of( s[0], pos );
        }

        size_type m = size();

        if( m == 0 )
        {
            return npos;
        }

        if( pos > m - 1 )
        {
            pos = m - 1;
        }

        return detail::find_last_not_of( data(), s, pos, n );
    }

    BOOST_CXX14_CONSTEXPR size_type find_last_not_of( Ch const* s, size_type pos = npos ) const BOOST_NOEXCEPT
    {
        return find_last_not_of( s, pos, traits_type::length( s ) );
    }

    // contains

    BOOST_CONSTEXPR bool contains( basic_string_view sv ) const BOOST_NOEXCEPT
    {
        return find( sv ) != npos;
    }

    BOOST_CXX14_CONSTEXPR bool contains( Ch c ) const BOOST_NOEXCEPT
    {
        Ch const* p = data();
        size_type n = size();

        if( n >= 16 )
        {
            return traits_type::find( p, n, c ) != 0;
        }
        else
        {
            for( size_type i = 0; i < n; ++i )
            {
                if( p[ i ] == c ) return true;
            }

            return false;
        }
    }

    BOOST_CONSTEXPR bool contains( Ch const* s ) const BOOST_NOEXCEPT
    {
        return find( s ) != npos;
    }

    // relational operators

    BOOST_CXX14_CONSTEXPR friend bool operator==( basic_string_view sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.size() == sv2.size() && traits_type::compare( sv1.data(), sv2.data(), sv1.size() ) == 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator!=( basic_string_view sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return !( sv1 == sv2 );
    }

    BOOST_CXX14_CONSTEXPR friend bool operator<( basic_string_view sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) < 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator<=( basic_string_view sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) <= 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator>( basic_string_view sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) > 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator>=( basic_string_view sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) >= 0;
    }

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)

    // "sufficient number of additional overloads"

    // against std::string_view

    BOOST_CXX14_CONSTEXPR friend bool operator==( basic_string_view sv1, std::basic_string_view<Ch> sv2 ) BOOST_NOEXCEPT
    {
        return sv1.size() == sv2.size() && traits_type::compare( sv1.data(), sv2.data(), sv1.size() ) == 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator==( std::basic_string_view<Ch> sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.size() == sv2.size() && traits_type::compare( sv1.data(), sv2.data(), sv1.size() ) == 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator!=( basic_string_view sv1, std::basic_string_view<Ch> sv2 ) BOOST_NOEXCEPT
    {
        return !( sv1 == sv2 );
    }

    BOOST_CXX14_CONSTEXPR friend bool operator!=( std::basic_string_view<Ch> sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return !( sv1 == sv2 );
    }

    BOOST_CXX14_CONSTEXPR friend bool operator<( basic_string_view sv1, std::basic_string_view<Ch> sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) < 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator<( std::basic_string_view<Ch> sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) < 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator<=( basic_string_view sv1, std::basic_string_view<Ch> sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) <= 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator<=( std::basic_string_view<Ch> sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) <= 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator>( basic_string_view sv1, std::basic_string_view<Ch> sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) > 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator>( std::basic_string_view<Ch> sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) > 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator>=( basic_string_view sv1, std::basic_string_view<Ch> sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) >= 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator>=( std::basic_string_view<Ch> sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) >= 0;
    }

    // against Ch const*

    BOOST_CXX14_CONSTEXPR friend bool operator==( basic_string_view sv1, Ch const* sv2 ) BOOST_NOEXCEPT
    {
        return sv1 == basic_string_view( sv2 );
    }

    BOOST_CXX14_CONSTEXPR friend bool operator==( Ch const* sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return basic_string_view( sv1 ) == sv2;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator!=( basic_string_view sv1, Ch const* sv2 ) BOOST_NOEXCEPT
    {
        return !( sv1 == sv2 );
    }

    BOOST_CXX14_CONSTEXPR friend bool operator!=( Ch const* sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return !( sv1 == sv2 );
    }

    BOOST_CXX14_CONSTEXPR friend bool operator<( basic_string_view sv1, Ch const* sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) < 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator<( Ch const* sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv2.compare( sv1 ) > 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator<=( basic_string_view sv1, Ch const* sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) <= 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator<=( Ch const* sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv2.compare( sv1 ) >= 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator>( basic_string_view sv1, Ch const* sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) > 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator>( Ch const* sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv2.compare( sv1 ) < 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator>=( basic_string_view sv1, Ch const* sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) >= 0;
    }

    BOOST_CXX14_CONSTEXPR friend bool operator>=( Ch const* sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv2.compare( sv1 ) <= 0;
    }

    // against std::string

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator==( basic_string_view sv1, std::basic_string<Ch, std::char_traits<Ch>, A> const& sv2 ) BOOST_NOEXCEPT
    {
        return sv1.size() == sv2.size() && traits_type::compare( sv1.data(), sv2.data(), sv1.size() ) == 0;
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator==( std::basic_string<Ch, std::char_traits<Ch>, A> const& sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv1.size() == sv2.size() && traits_type::compare( sv1.data(), sv2.data(), sv1.size() ) == 0;
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator!=( basic_string_view sv1, std::basic_string<Ch, std::char_traits<Ch>, A> const& sv2 ) BOOST_NOEXCEPT
    {
        return !( sv1 == sv2 );
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator!=( std::basic_string<Ch, std::char_traits<Ch>, A> const& sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return !( sv1 == sv2 );
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator<( basic_string_view sv1, std::basic_string<Ch, std::char_traits<Ch>, A> const& sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) < 0;
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator<( std::basic_string<Ch, std::char_traits<Ch>, A> const& sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv2.compare( sv1 ) > 0;
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator<=( basic_string_view sv1, std::basic_string<Ch, std::char_traits<Ch>, A> const& sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) <= 0;
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator<=( std::basic_string<Ch, std::char_traits<Ch>, A> const& sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv2.compare( sv1 ) >= 0;
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator>( basic_string_view sv1, std::basic_string<Ch, std::char_traits<Ch>, A> const& sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) > 0;
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator>( std::basic_string<Ch, std::char_traits<Ch>, A> const& sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv2.compare( sv1 ) < 0;
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator>=( basic_string_view sv1, std::basic_string<Ch, std::char_traits<Ch>, A> const& sv2 ) BOOST_NOEXCEPT
    {
        return sv1.compare( sv2 ) >= 0;
    }

    template<class A> BOOST_CXX14_CONSTEXPR friend bool operator>=( std::basic_string<Ch, std::char_traits<Ch>, A> const& sv1, basic_string_view sv2 ) BOOST_NOEXCEPT
    {
        return sv2.compare( sv1 ) <= 0;
    }

#endif
};

// stream inserter

template<class Ch> std::basic_ostream<Ch>& operator<<( std::basic_ostream<Ch>& os, basic_string_view<Ch> str )
{
    Ch const* p = str.data();
    std::streamsize n = str.size();

    std::streamsize m = os.width();

    if( n >= m )
    {
        os.write( p, n );
    }
    else if( ( os.flags() & std::ios_base::adjustfield ) == std::ios_base::left )
    {
        os.write( p, n );

        os.width( m - n );
        os << "";
    }
    else
    {
        os.width( m - n );
        os << "";

        os.write( p, n );
    }

    os.width( 0 );
    return os;
}

#if defined(BOOST_NO_CXX17_INLINE_VARIABLES)
template<class Ch> BOOST_CONSTEXPR_OR_CONST std::size_t basic_string_view<Ch>::npos;
#endif

// typedef names

typedef basic_string_view<char> string_view;
typedef basic_string_view<wchar_t> wstring_view;

#if !defined(BOOST_NO_CXX11_CHAR16_T)
typedef basic_string_view<char16_t> u16string_view;
#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)
typedef basic_string_view<char32_t> u32string_view;
#endif

#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L
typedef basic_string_view<char8_t> u8string_view;
#endif

} // namespace core
} // namespace boost

// std::common_reference support
// needed for iterators that have reference=string_view and value_type=std::string

#if !defined(BOOST_NO_CXX20_HDR_CONCEPTS)

template<class Ch, class A, template<class> class Q1, template<class> class Q2>
struct std::basic_common_reference<
    boost::core::basic_string_view<Ch>,
    std::basic_string<Ch, std::char_traits<Ch>, A>,
    Q1, Q2>
{
    using type = boost::core::basic_string_view<Ch>;
};

template<class Ch, class A, template<class> class Q1, template<class> class Q2>
struct std::basic_common_reference<
    std::basic_string<Ch, std::char_traits<Ch>, A>,
    boost::core::basic_string_view<Ch>,
    Q1, Q2>
{
    using type = boost::core::basic_string_view<Ch>;
};

#endif

#endif  // #ifndef BOOST_CORE_STRING_VIEW_HPP_INCLUDED

/* string_view.hpp
fYQmWAA7mWvtjWu4Sqcv0UEyda9H+lzxuGWbiZHConlEgGVs+9m4UAUq4BE7jvt998aosJLrEZgeZ4jbXwS5BlhQJp08VvFbC7o599fIGtMe1bYRvnCDV1lsl14GZifg65juEeBu4uweznYS7H3BawQ0sSEAemyjS3xG/aaNu9GxMSFbVwOJkxcGBIhWa5pQhPp00Exg1Bj+pdjBHmXFFbdQr12nC2goItpukBm7lEMqi7oeFF+3/dYHnYJvjK/0aHwjTey1ce/MVy5PX7vAKcrGIjGO0RHlYa1qOkOm25p5PgbYzxXtBMb08bNpoaWemofi/fF2VRBsqF5Wd5NBSQ1zNaaRn3AsQJXoy3NWVBGAQ4eRg1ZQsEzzqI9PNSxQUwd3wfvxh/WoEASkC5EotJSnbV5jhw7YKCAaa7RIj3fqQ6UUfiBqaVoaCJRXQtLS+Ijata3NLyy03gLShS9kwKDCqYCyL79VtVyMC1XPA9spfw6EGcZxMwmYkW3ifUyMWi5yiVMznc/k1J4sK4u8SWqDiGHofHBtHEFEMiK2kpB0lYQkTVgAejdpVNCpWmeXYSdlc/djnXk4ZrdUMKHrgVagvnr6VT+AGQFQY/X32pxFKQEmP/EZurLLtxwdUcxZpFJYVjkQzKZOE2wyhcMQlNI5ABOod8J+pypDHQkUKGeLgqkvsgPN0EYPj0g2h7qo4ibFXpPkysKrjl/C50I25x9FNnyev/BdLRiDrTYNLXDAbuqQTVikWHwUm+5y1pZtbZcHcsT1cAkIZ8qkE+823yEP0evCee/cS2svDIiXI377SJKx0ap/6IpArfC4CUACuLNw0yvzRMhwB+32I6B00AbrcGMmYLE4QPu+8RQXyKWIlT45dnmxrxhhkfMaaTGbyv0Gr6kAt9kEus5tXHh3xvjwbJfEtbFzAMdRJfGhPhTKY1FktFo8lZqhd64WCnt8gyRu2yO0QngP997W7nkHQ8Ry9t8DEZbqw0rD9YIIqUWajJcixLVhK1C+69sOFWTMNrQA0oh1wIQRoUhRcrjtjewYhMhpbmgnHnSvhnvK71VG11tdwhiNTnBhYrdaYBGp+XiRCKMDHL76x242zrjuhPQQjuUYT2oDkgtY5H2aI2ElW2yM17OV630Km1OKfOx/qCEeUEOZ390KJZ8VvYyOZ1CkDl3OwU8DlcZ2dP1cbopHIkFgJ1pU+Do6bXqniryKP+kugm+Y2fPruBuSYvN4W37ualfp9O8gUUsgIt4k9V7888s1ID/74h9L3QwOV9XzSk+xpRNR9Zsh4DjyGyItGT6EonRCSk16Tf3Es5H82+QM6zMVW98EhkcQXctin0FufD8k26sdrIUgmL5poH78DAKfQ6A6P+aXd0KNd7bRAkyw7Gb5vF+yN0ItbqNFkh20Jx0tGpHo9lJkmbRGJfpA2XluXk/uZ7fV52Y+YhR1K+9aiLwHL7tqO4/zGJkFOMSnaRtmePhADCJTEmLzkGv97jkJDnCdeWOuaZm7Ec7ZbpcB2l6uDo8X9wxV5mAhL9JtFVLwN5dBF+mxTnUigWKxtOcjRQfYzUJu/Z52UDaPH7TDIJQaKI5Vn6ybMfYRCfYkLls8gBIfB8Kq2l60KNrEkFqH+mvkMvw0Aw8yg+E9NJFaw2frFyevXOZnA7vuh+RbIxHik3hSpD2HjbnOEgf4E92DB07DwGbCB8LRV3tZvM2dkJI9dDjGLRsQ74pbHL5zw8EuqHWruLz5JlO0u1wkHQ70DFrEGC/hiXl7FO61avHWYEfmwxXlvHwIIonkwUbPmJ6xoO0CSTOVK/n/HEeyJrhb/9MXpaDVYfCuwT9ODk0Rsgmeeqectiy8GFPI4bca61yKvsW++Yp2zN0KfzxczqWn93qpO2qlvtl57IvUNvd8PLs6XmosvIo36ga3TQaLXjXly3nv+UJ1wtN55f5jiJQioDfOkjp38qMS6xY6rA16eJeTSgIOtE5FklcTYbmeY42G63aH2o4+rhp/tQajxMOJRVX4jBy0kkOBt2xTOYJ8x3AnP1IGCGfOV8jZIrtKdF7BEPVut5zpsDou+EC4qbLSKsGtn7AgHMq5ctMhZxHkZ6mUhn/hlj3nrEfLmlg4x9E50mXRcWuyDGq/cTsWDI0wjf++JRDDsJ8XFmHkb2FhOYC+pbLryrf8GK51Izx5FrM49gnvbLNZb+PoGDRyheiLfx+OnodsYfiFPSF9hIqv2WQZ1vwPzoTVF0Lecu4yOY9Jp+09iA5eeX0+Csut6etPOrbxs56J/LNdQLznj2QmuZaPNiz/2x2GC7D30/xmM8sXXWx0cmBusenE/YINL7SuytzX9wQj2UIDWc5b9gmRj5r8ykI+2WAAl6qzPNvG9DU4v5zocReGLRL9ca81djw9tzx8COjC5pUKS+7qtFdcnNHjq/z6H7nFxVG4uxRYMl46xBo4Wy/sWvIFVSd7Be0ePOsce6Ux6kb7w7QDwndR0YEJQOWdk9eDfiL2LD5xnPe0eb8/QSzFwkaaS23fqvbmwxkUE6VMWehMMbyTPWU6lkqtTbeignmmD6mBf0VXbyJtZp6dt9MD64BtukI/prK0JuNr5APwnnwTOg9Pa77m3sziaNqfp40l5WRlrbdMWeXE8Mr1dsZesNGDH4Umuqjm6c9r8Wcsi+Lk2Ujb70W6FIhg3Rv6kwcGR8UtZp+NpgL7eAjZphbK16KVhgLbT7NVaXFrSy9tfbtNTasA8R2HYnR8R2e88Nxy1B65b2/Bgv6yab5skj7bmdHFpwrcCPS8iYdaDaQc3xPPv9NKQzbuSg/t0aXFi2w+IK/gI9bmHASbV+pu+sdV/siwhUw5Ij+dB5hNloeDxMYNrmVSdbgyqkMGSoTZ0cRX4cAFohsbgZqNzAqQDMSJiuMQC5IUsXAbxUcDtLb5wLRXdVGprvDF9rMyqhqYBDll0xKi9ICEGeOEVKYMnYLEKpN3VDzY4Y2cZw7PJiVE3Z7jjaSfj8w2D0ZB/MMf0c48R4rP3A3ngCPxIw9j2cEDVJqmMvqD9icMl5P2MQH+UrM/TqqWNq+pV9jfcLNry4xPZ98i027EPjWnWFpbOpGLNDkrsj7UV0UdSTq0kRQlpf1UwIOtFC1j+HYniT58VEqycnsLVeCPQnqywkBmgLvI47ZMxpSSKRv1UJjG6MW2Kd70JZkdmvsxmzW/hJ76sHwRdJaSpmNPqOu9eHCY7wp7n/mNYy2d9+JUgx5AtjiI499jJc3VmZABtAXuR/6Iru3cZr6vHGeMSfI7Tb3rs/XogD4evmI76KSt6dimf0QVdQw8DTjyFhzhYHkWqbAi9dKowPOqFk7+ZRgTTUgRn7yq+awHQSfkQ5f4z01LNOj76e3S+iZL6640imec1UefmarncnHc6VfGaxyOsOEfRQrEQG6oGFOeH3gs/fYAItIGezFtkQKoit+Hs69Eegah2ZIKqWJp307MY87iXUV0yL1T+GWD+gtQMlp6cITXy6Kk0umQsQ9hoJJG1Vc3T994FgC6l5WruhlBf1tVGR5UsHd9fbLFc+dGyb3NLBFdycVvUVaCWBBc9BT+4GxBHjwh7ykkV3S94L51kcZeRzZq0UFp180r3YmswNbbtC9ubgtVEe+731hcwTpqeqbKVpdGb6+fT5uLy7p/EVcmkRYx/EUH+Zjj4bEbwuxPDnT8MlPUgVbpS9CZBunATtZeZfm4dqH9inj2LHbtsVGosI3GebSSCDsZyHNaeaZHT5TLLS54ZsPbccLLnMGj3ElP0QOJP4Av5F12JWjIBvYm2mMJbcmcxE3bGxxm6A6iDdMyBf9yvJOIduQmWPdKi1whXyZYzWmZ9xIZXSPfPl7PsZ/0ehQLli9QrwO+IH9gHIrlGyNcgWMwiLRn1dF1MqgjZs8dCtoOaLS1+G4m7kkZOsyG2nl81yPXR4+krIztTvdekdufQ1uA64xtNA3ILqaiNeHJwj+x0eGeiNac5Ktxy/ohXRU9Sxz6MzsyEtxT81cljPZkwP0rglLoz9IbTf3dtE+xVc+f5mYadCVqLeVFh8g0GVp0R/531W2jDtRhn38a4x9F6wSDW03zDu3PVy8O+yitHYYpvt2XHiDVHUvkEyu8+LmdMG9H+tKdNou3mW10TIML8TPnUyoo5sLP9PLqtJXNQxGl1k8oOc806pYX+Lkuj95rHcjJTG836FnhdwpuMruGnT+RtZyQ/WPEED+tK1mTh1lkxsCcHAAALP/TN7ED9XfmYHvG9j392T5e86NXSQcsyCg7+LQ92dRvF4nmQzvQ0z+dx0b77T6f3jYohTRqFbkvwH9rlwSVrP8pGqjw09yEvs1AT+s11Gpet2xgQDHl78w0ZLTo2glQDAQsceIkNp+Cq37r2NEpQb/H7oD56joub+dCegV0KdZe/rm92HDbiDTQbfjLPf1sewPWP8YBU+vLEtI8AvnVtftZLlYkzBBJaTduVjx0sEWTqcxcRbFHeR0vJxxBhR027nmkI3GztDb3ccqSRV9fQb/03vgeMOmDAxcb5is99f7uHWBx0TyQRKFhYkuNM3u4E5PXdWFR+kOXYCspGuDlJhGd9TdTRiHNCP3mjdNcK/wcmTOxetRTdhCZKhpj5SXcoVUmFcEsOsKd8k8ddTpBczbNeftnWe6/QvKXb5uKOcf13y/kjpanWcdBfITF/mwOPr1F8UOMBawFcXP9BSZ0bEC3nvXObPkD2mvyAXuyCViDKaXBpskhd2roymEC0xhkHzovQlmYyQ1xptzZv5SOGujDGEX370m45IykDEcvMgNLYRpufYccEoL9zt+bVmBh978f/h0VJ95/qEENBHgChNg39h/z8l8e76tzbaMpyTNY7nYdF9w886QB5bT7y4ogFIVPVJNyvFdb1r+SyNKTnlAIBwlx8nSeN/36skAfRQ22Swm4X6Rn5k4Xvej8lUWfDhrH1m2/mijLn0UHl0zHom4IfRBlF1M6YWpHjeHrp5K0+kcGLDul/xBH0TmPNFORnN+JOjSWNhZupufskL9Sa07l0rCeGL0sbqhpyUKGXBS9JVrZ5JmMxXoqOiJ8ei12fhpYQj+TrdSmgA5GZ1ZHYt0EAl7iskI5Es1CFKhMJdBbq1wIIlRHZUxBNy6UltCYyyPisUiXrrtarhmt4L+sjtqkyRxN2IBVH7AZ70ghv9h2Qxu6uXXLdsjy0lDY4rh/88nOM4gWR4t4C3A++BMyB+hMJ8k4zc7USleyfLfe8Vna878DLPVdM6P1Rs9LTat1VWoQukcB7fRbFyNV/m1bALOEsy+GpWBXfgP1BtQXrY3Fbhr0yabZKnyv69i/v1eHZ2cKRvMSalXEkhi/qpAm9JZ9eHusO9iwbTz3qUdXVzIaWBjvOi/f9Oaf7kbF4lvTVFKzOIjiUGneA1XDv7yM2D8csrXW2ap1DlZmME8NQdKP76lVTvPZ4YEKhRUedSoG0E1yA+nxYTzcbjuX7nTXeMG1ZmDjsVGvkfjKoZNFbDb073fmWBsPSEeni6gfU6lgVMrsjQMI9aWezMC5VmKWGS+QOlbP0qtm7nowkO3E0UXZb3SE9LJZwuOdX/WWK5KSej/Hab6ATzyLlgQvaWrufmZz0BZkaYBkOTC/BASVwAXtCpNsX8XKBfH8S2nqNsFgS8DPOPIyJr1wfM8tcY09eEwFM2x9EJJo5KI1ldhzjkUZZ7W6SPXl0BihxtNos+M5ozESfjDdINuOnqQ9axuUA3popiQW5lKbyA13y0IgYwCz2F37zwsn12E6raW3Gq5eHDWSL/kn/uAwjNKdKw+zJZJ8g/cP4Ygo/1HiA3Hscxp4/GDpz1CP2FeMR/G87+cUeWY40fF4daczm3+mZ81smcLVzOPtvwxO+qt61Hj/lnPNDsWiyRWiChEfVRNQq6hDJchi/8oQJwKEl6SWJFJveWkdf7Cn5k30UtnH+nNP9aA2Qqt1pY2gIMBsWuVhjn6NCgMqCcut9fHVkuryl8RENltyWHkD5Y1TV+U/7sIYtfd8le0JxZJQ3iJTvObszNE2jRgf5K3XSFBblvo6gmD0K5r3XmzkV3hZ5u+aP95tuwMp1xdCUOSrz5moxpipQ1jK6x5kZpfAt6btUA4eNXX0688oarXi5cx68PvwiNUZ9YgtuhxmnRdZ1Z+esF/N+kX5L4jG4mCrpYjVu9DbNz31jcOfIJSXEvS04oSLxH+mKMWnyN7Cb5bXyfy1LR220V2pps/Ac0qzFZQQ27ManzBnYi1OLTvVvlBGczCFe9FnpJY6nU/Vd8LwnFq6+YlcHw5IJV+yusIgZOeO5bQtnt32J3blPW7oVoy6bCGjGr2yPQR41p6hbi460IOkL9V6pI09K+K28s6qGZ5RjY2AbqJ7yZhMO/tQItaGKdbMuSU/5I3cPKMZvcnerIwduc6Wcg2uQUsvlVMZSU7pECrZIOd/4kjCkYmY3DojwSF5dl8pBImG340qYvXMncgN6FVR6Wya/zGDhZNK7UZsoS7Omw4bX9kh7NijIBXiEWch1DyxDFMMQIZcY/PhGWSzx12f9a/hgrcees//FNX5ME6ExlPcWvm8DH5hbgqlqhvJ4ue9uR22OZc/7Uv4qjAOtFwN0V4xJmQrNGdVuOOfLEMZPI3y9jFpM6D1QIrB7rkR2eq2E4qGzIGT4EXFIOxl6hulzbqiBBtv3HwnkVmBS2tBgkDVNG3dIiKeBLlwr1i2sn4bcXVmX2D0aS9keLsySuFivg7PxKlPssVqidGHNUr4hnRQDt4enzhey3kgaZHKMmUIdq/AoMvnwJ/yOCEmnZxP5wSHwKkju41Ra7XnVsxQh0vevnT+jW7TPT60zJ0bZx/153Ell+B6n0eBsMwjL//wArej9RhMjL5FS7yTv6NYSioeYOTxVtLX0qZuJoRkOs0Qm4UoWzOv20y7gFIvf1XMO1mf8lxO5l5YiR9VRfRJEmHFdPeVsXcQqUxWy839VKuXp/Hp+dZcQ47Ff9oO0yA7o7LH2LZ/JnHHbB8qdCUO4gYfeZzmGlihs8x9VwQnWYjrEOW17cBB0qXZI53GN8Q8/pih4AzY5Wrb0NM09I2o/COUdeqW7Ec4sif5aL/f+FmD7Yge6rl581D+njPrY9yqUs8x1l57OsmcJM+rD4+NocBh11ccyhPzta1FyaYq9OF4cP6yBqD6E68T4rl+IX6Cv1AilWuOYL4rtfTuI6q9IA6KvESk34phCDOUIbz/xdGm8xB98NqAc0tIYrzS1sWzwIy7HpPJ3MPSr0tzEzGmQzf96cNV1GlPFMIlu/0VbOjmT/8CZPUdMPsDar8MPT+NbuTpxMRzLCpOlkQMgIjLFIAgiQu8CASlEJUlh5xgHAvYCURrGWQ1mXmfk7n9D9Gk/msf3b4Mw7csyOUUdkXhLE1hrULh7U5haAk9I42h+cDO/sczYR1RqQZxwpAHuwziawli4AGC+AHb4/h4mBHJLQYonJZFyRrRuUwixRoC3AeFmycCFnHIAv2pl4cpJKQ3I2iyhZlIA/jeizMBBzEaOVblsOugwzUVUtoRGdibD28KIhryKiqGJ9blJdWyN5LgljCzf09w6bZsICav3HP2UdXsmIOlAzkjE3Xgh49qbo/zLyJhPXx5N8pug8SLSmazCw4B
*/