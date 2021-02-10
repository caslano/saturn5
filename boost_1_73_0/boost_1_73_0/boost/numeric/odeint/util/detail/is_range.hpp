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
mUkmRGwoUqqWcCDeShibA1mHshmObTiboliHtPgaQsJa6IQ0aXpCWuiM8oS0/j39hLRGm56Q3m7uVmRUPyGtU1ZOPxUyrDXJzkcVLVXnoy2ejqr6Vpdjm6ejLZyNtnMyurrJLK9q0+8xy9bLtY6fi56cKS6dxjUPd3n1LFbutuqlUxV9dp1BR1++5VWnX97wUtNXbngp2HOQfeUCk4I92P3K5SVl7wFyF6XmwNgdZOh9cOjVOzkK7n1w6OX7OKrO9wHy8l0c5dD7ALULD53nd3A01BhnoN/F+zfF/VZPmeb7yyfsL3iPKS+cqoHgvisvnKoFQNv1yLbHeqO4cKre/zCQ4sKpblC2qihDsVRHiFhUF07VegkGUl04VSsoRLz1C6dqTQXD1C6caubIVl/nIFY6O8Ow0tvcXnfD8lReOFUrcWSdKC6cqrU5sk7qF07Vah2GqV04VYvX2rjlIFYGLsOwMnLc2tBxW2PXssHrpgbvYIe9uLmLbv5IZjcv5EsR6Qsasvrv9OTsiA2F951WXOKGETeQQln6HZkxCr2Q9wKh9xzcVC7NJbKol9Cdnu/4QVcsTdLW54ZmnWDXiZ31O27Q64aeK9Rcj2jpcWi36/gh73Sd0Pc8AmoRuRWHpAjaimNCEacX+h2hjkIx
*/