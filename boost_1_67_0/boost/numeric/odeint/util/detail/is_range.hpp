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