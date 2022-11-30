/*
 [auto_generated]
 boost/numeric/odeint/util/detail/is_range.hpp

 [begin_description]
 is_range implementation. Taken from the boost::range library.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2013 Thorsten Ottosen



 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_DETAIL_IS_RANGE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_DETAIL_IS_RANGE_HPP_INCLUDED


#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <cstddef>
#include <boost/range/config.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/and.hpp>

namespace boost {
namespace numeric {
namespace odeint {



namespace range_detail
{
BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
    BOOST_MPL_HAS_XXX_TRAIT_DEF(const_iterator)
}

namespace detail
{

template< typename Range >
struct is_range : boost::mpl::and_<range_detail::has_iterator<Range>, range_detail::has_const_iterator<Range> >
{
};

//////////////////////////////////////////////////////////////////////////
// pair
//////////////////////////////////////////////////////////////////////////

template< typename iteratorT >
struct is_range< std::pair<iteratorT,iteratorT> > : boost::mpl::true_
{
};

template< typename iteratorT >
struct is_range< const std::pair<iteratorT,iteratorT> > : boost::mpl::true_
{
};

//////////////////////////////////////////////////////////////////////////
// array
//////////////////////////////////////////////////////////////////////////

template< typename elementT, std::size_t sz >
struct is_range< elementT[sz] > : boost::mpl::true_
{
};

template< typename elementT, std::size_t sz >
struct is_range< const elementT[sz] > : boost::mpl::true_
{
};

//////////////////////////////////////////////////////////////////////////
// string
//////////////////////////////////////////////////////////////////////////

template<>
struct is_range< char* > : boost::mpl::true_
{
};

template<>
struct is_range< wchar_t* > : boost::mpl::true_
{
};

template<>
struct is_range< const char* > : boost::mpl::true_
{
};

template<>
struct is_range< const wchar_t* > : boost::mpl::true_
{
};

template<>
struct is_range< char* const > : boost::mpl::true_
{
};

template<>
struct is_range< wchar_t* const > : boost::mpl::true_
{
};

template<>
struct is_range< const char* const > : boost::mpl::true_
{
};

template<>
struct is_range< const wchar_t* const > : boost::mpl::true_
{
};

} // namespace detail

} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_UTIL_DETAIL_IS_RANGE_HPP_INCLUDED

/* is_range.hpp
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
*/