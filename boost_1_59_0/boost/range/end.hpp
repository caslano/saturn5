// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_END_HPP
#define BOOST_RANGE_END_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/range/config.hpp>

#include <boost/range/detail/implementation_help.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/const_iterator.hpp>
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
        range_end( C& c )
        {
            //
            // If you get a compile-error here, it is most likely because
            // you have not implemented range_begin() properly in
            // the namespace of C
            //
            return c.end();
        }

        //////////////////////////////////////////////////////////////////////
        // pair
        //////////////////////////////////////////////////////////////////////

        template< typename Iterator >
        BOOST_CONSTEXPR inline Iterator range_end( const std::pair<Iterator,Iterator>& p )
        {
            return p.second;
        }

        template< typename Iterator >
        BOOST_CONSTEXPR inline Iterator range_end( std::pair<Iterator,Iterator>& p )
        {
            return p.second;
        }

        //////////////////////////////////////////////////////////////////////
        // array
        //////////////////////////////////////////////////////////////////////

        template< typename T, std::size_t sz >
        BOOST_CONSTEXPR inline const T* range_end( const T (&a)[sz] ) BOOST_NOEXCEPT
        {
            return range_detail::array_end<T,sz>( a );
        }

        template< typename T, std::size_t sz >
        BOOST_CONSTEXPR inline T* range_end( T (&a)[sz] ) BOOST_NOEXCEPT
        {
            return range_detail::array_end<T,sz>( a );
        }

#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
} // namespace 'range_detail'
#endif

namespace range_adl_barrier
{

template< class T >
#if !BOOST_WORKAROUND(BOOST_GCC, < 40700)
BOOST_CONSTEXPR
#endif
inline BOOST_DEDUCED_TYPENAME range_iterator<T>::type end( T& r )
{
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    using namespace range_detail;
#endif
    return range_end( r );
}

template< class T >
#if !BOOST_WORKAROUND(BOOST_GCC, < 40700)
BOOST_CONSTEXPR
#endif
inline BOOST_DEDUCED_TYPENAME range_iterator<const T>::type end( const T& r )
{
#if !BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
    using namespace range_detail;
#endif
    return range_end( r );
}

    } // namespace range_adl_barrier
} // namespace 'boost'

namespace boost
{
    namespace range_adl_barrier
    {
        template< class T >
        BOOST_CONSTEXPR inline BOOST_DEDUCED_TYPENAME range_iterator<const T>::type
        const_end( const T& r )
        {
            return boost::range_adl_barrier::end( r );
        }
    } // namespace range_adl_barrier
    using namespace range_adl_barrier;
} // namespace boost

#endif


/* end.hpp
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
*/