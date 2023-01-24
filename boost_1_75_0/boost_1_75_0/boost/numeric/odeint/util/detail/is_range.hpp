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
xFnvKkcARAqgsYEyDeS2diiwgkkh4ndIMLcDMLcD2fx3Ng58fBuVBi7pM/lHrzPtL8cFBd13gfeXdoH1V/IFo79etWknAyTor9lO/Ar3jwpUJkF5XhTYZkpDTP+9YMFfDpk/CPxVHP9sE/9zNnfCeXEwzjsI3ozEXpYXJW4zT70x+deKey9k/iZwH+a4T5i4k2y4X5WkI+Qxgmfdu+7a3y34O0Hmp3/n+DP/zvD3/buB/zGbd+EOSTpDPnLiPW3XfaoV92zI/FngXshxLzdx37X1+3Mu6QPQcX+o7oet+E9D5t8C/0WO/5qJv5etb5Jovw+5Z7+nX7Tg7guZhy9y3IUXGe5hFw3cy2390p/2+5dOPPfedV9oxb8KMm8K/C9y/FtN/DNs+MdLUHco8h51P2/FfQ0yHS5x3OgSwx1/ycDtsuFe74K6/3C/F14SciDFPwIy0wR+5vRIpMglu+THujse4yHOtuu8Rse5EYC/QDpxidPi4QYt3neJ0eL3zNr3sZl3TrvkD4Aoj3fSjdx71Z98Zal/ImQe/IrXP/UrVv+eXxklfGYvQZK+oKcT7uI22xHRcT8OwG8hrfyKt+PXtVF+u898Ze8lhyQfgerPZt1/z/oftNb/KGS+FfVv4vW/ZNZ/ga3+M2j9z+JruO1xSP1a4O4FwIOQxn/N67/QqP/gr7n962ujFIetlOddrCFJPziPlnxtacdzkNn5
*/