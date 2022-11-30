// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_BEGIN_HPP
#define BOOST_RANGE_BEGIN_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/range/config.hpp>

#include <boost/range/iterator.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

namespace boost
{

#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
namespace range_detail
{
#endif

    //////////////////////////////////////////////////////////////////////
    // primary template
    //////////////////////////////////////////////////////////////////////

    template< typename C >
    BOOST_CONSTEXPR inline BOOST_DEDUCED_TYPENAME range_iterator<C>::type
    range_begin( C& c )
    {
        //
        // If you get a compile-error here, it is most likely because
        // you have not implemented range_begin() properly in
        // the namespace of C
        //
        return c.begin();
    }

    //////////////////////////////////////////////////////////////////////
    // pair
    //////////////////////////////////////////////////////////////////////

    template< typename Iterator >
    BOOST_CONSTEXPR inline Iterator range_begin( const std::pair<Iterator,Iterator>& p )
    {
        return p.first;
    }

    template< typename Iterator >
    BOOST_CONSTEXPR inline Iterator range_begin( std::pair<Iterator,Iterator>& p )
    {
        return p.first;
    }

    //////////////////////////////////////////////////////////////////////
    // array
    //////////////////////////////////////////////////////////////////////

    //
    // May this be discarded? Or is it needed for bad compilers?
    //
    template< typename T, std::size_t sz >
    BOOST_CONSTEXPR inline const T* range_begin( const T (&a)[sz] ) BOOST_NOEXCEPT
    {
        return a;
    }

    template< typename T, std::size_t sz >
    BOOST_CONSTEXPR inline T* range_begin( T (&a)[sz] ) BOOST_NOEXCEPT
    {
        return a;
    }


#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
} // namespace 'range_detail'
#endif

// Use a ADL namespace barrier to avoid ambiguity with other unqualified
// calls. This is particularly important with C++0x encouraging
// unqualified calls to begin/end.
namespace range_adl_barrier
{

template< class T >
#if !BOOST_WORKAROUND(BOOST_GCC, < 40700)
BOOST_CONSTEXPR
#endif
inline BOOST_DEDUCED_TYPENAME range_iterator<T>::type begin( T& r )
{
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    using namespace range_detail;
#endif
    return range_begin( r );
}

template< class T >
#if !BOOST_WORKAROUND(BOOST_GCC, < 40700)
BOOST_CONSTEXPR
#endif
inline BOOST_DEDUCED_TYPENAME range_iterator<const T>::type begin( const T& r )
{
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    using namespace range_detail;
#endif
    return range_begin( r );
}

    } // namespace range_adl_barrier
} // namespace boost

namespace boost
{
    namespace range_adl_barrier
    {
        template< class T >
        inline BOOST_DEDUCED_TYPENAME range_iterator<const T>::type
        const_begin( const T& r )
        {
            return boost::range_adl_barrier::begin( r );
        }
    } // namespace range_adl_barrier

    using namespace range_adl_barrier;
} // namespace boost

#endif


/* begin.hpp
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
*/