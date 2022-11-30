// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_CONST_ITERATOR_HPP
#define BOOST_RANGE_CONST_ITERATOR_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/range/config.hpp>

#include <boost/range/range_fwd.hpp>
#include <boost/range/detail/extract_optional_type.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <cstddef>
#include <utility>

namespace boost
{
    //////////////////////////////////////////////////////////////////////////
    // default
    //////////////////////////////////////////////////////////////////////////
    
    namespace range_detail
    {

BOOST_RANGE_EXTRACT_OPTIONAL_TYPE( const_iterator )

template< typename C >
struct range_const_iterator_helper
        : extract_const_iterator<C>
{};

//////////////////////////////////////////////////////////////////////////
// pair
//////////////////////////////////////////////////////////////////////////

template< typename Iterator >
struct range_const_iterator_helper<std::pair<Iterator,Iterator> >
{
    typedef Iterator type;
};

//////////////////////////////////////////////////////////////////////////
// array
//////////////////////////////////////////////////////////////////////////

template< typename T, std::size_t sz >
struct range_const_iterator_helper< T[sz] >
{
    typedef const T* type;
};

    } // namespace range_detail

template<typename C, typename Enabler=void>
struct range_const_iterator
        : range_detail::range_const_iterator_helper<
            BOOST_DEDUCED_TYPENAME remove_reference<C>::type
        >
{
};

} // namespace boost


#endif

/* const_iterator.hpp
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
*/