// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_MUTABLE_ITERATOR_HPP
#define BOOST_RANGE_MUTABLE_ITERATOR_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/range/config.hpp>

#include <boost/range/range_fwd.hpp>
#include <boost/range/detail/extract_optional_type.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <cstddef>
#include <utility>

namespace boost
{

    //////////////////////////////////////////////////////////////////////////
    // default
    //////////////////////////////////////////////////////////////////////////
    
    namespace range_detail
    {

BOOST_RANGE_EXTRACT_OPTIONAL_TYPE( iterator )

template< typename C >
struct range_mutable_iterator
        : range_detail::extract_iterator<
            BOOST_DEDUCED_TYPENAME remove_reference<C>::type>
{};

//////////////////////////////////////////////////////////////////////////
// pair
//////////////////////////////////////////////////////////////////////////

template< typename Iterator >
struct range_mutable_iterator< std::pair<Iterator,Iterator> >
{
    typedef Iterator type;
};

//////////////////////////////////////////////////////////////////////////
// array
//////////////////////////////////////////////////////////////////////////

template< typename T, std::size_t sz >
struct range_mutable_iterator< T[sz] >
{
    typedef T* type;
};

    } // namespace range_detail

template<typename C, typename Enabler=void>
struct range_mutable_iterator
        : range_detail::range_mutable_iterator<
            BOOST_DEDUCED_TYPENAME remove_reference<C>::type
        >
{
};

} // namespace boost

#include <boost/range/detail/msvc_has_iterator_workaround.hpp>

#endif

/* mutable_iterator.hpp
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
*/