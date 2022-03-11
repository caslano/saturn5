/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

 Revision history:
   27 June 2009 mtc First version
   23 Oct  2010 mtc Added predicate version
   
*/

/// \file clamp.hpp
/// \brief Clamp algorithm
/// \author Marshall Clow
///
/// Suggested by olafvdspek in https://svn.boost.org/trac/boost/ticket/3215

#ifndef BOOST_ALGORITHM_CLAMP_HPP
#define BOOST_ALGORITHM_CLAMP_HPP

#include <functional>       //  For std::less
#include <iterator>         //  For std::iterator_traits
#include <cassert>

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/mpl/identity.hpp>      // for identity
#include <boost/utility/enable_if.hpp> // for boost::disable_if

namespace boost { namespace algorithm {

/// \fn clamp ( T const& val, 
///               typename boost::mpl::identity<T>::type const & lo, 
///               typename boost::mpl::identity<T>::type const & hi, Pred p )
/// \return the value "val" brought into the range [ lo, hi ]
///     using the comparison predicate p.
///     If p ( val, lo ) return lo.
///     If p ( hi, val ) return hi.
///     Otherwise, return the original value.
/// 
/// \param val   The value to be clamped
/// \param lo    The lower bound of the range to be clamped to
/// \param hi    The upper bound of the range to be clamped to
/// \param p     A predicate to use to compare the values.
///                 p ( a, b ) returns a boolean.
///
  template<typename T, typename Pred> 
  BOOST_CXX14_CONSTEXPR T const & clamp ( T const& val, 
    typename boost::mpl::identity<T>::type const & lo, 
    typename boost::mpl::identity<T>::type const & hi, Pred p )
  {
//    assert ( !p ( hi, lo ));    // Can't assert p ( lo, hi ) b/c they might be equal
    return p ( val, lo ) ? lo : p ( hi, val ) ? hi : val;
  } 


/// \fn clamp ( T const& val, 
///               typename boost::mpl::identity<T>::type const & lo, 
///               typename boost::mpl::identity<T>::type const & hi )
/// \return the value "val" brought into the range [ lo, hi ].
///     If the value is less than lo, return lo.
///     If the value is greater than "hi", return hi.
///     Otherwise, return the original value.
///
/// \param val   The value to be clamped
/// \param lo    The lower bound of the range to be clamped to
/// \param hi    The upper bound of the range to be clamped to
///
  template<typename T> 
  BOOST_CXX14_CONSTEXPR T const& clamp ( const T& val, 
    typename boost::mpl::identity<T>::type const & lo, 
    typename boost::mpl::identity<T>::type const & hi )
  {
    return boost::algorithm::clamp ( val, lo, hi, std::less<T>());
  } 

/// \fn clamp_range ( InputIterator first, InputIterator last, OutputIterator out, 
///       std::iterator_traits<InputIterator>::value_type const & lo, 
///       std::iterator_traits<InputIterator>::value_type const & hi )
/// \return clamp the sequence of values [first, last) into [ lo, hi ]
/// 
/// \param first The start of the range of values
/// \param last  One past the end of the range of input values
/// \param out   An output iterator to write the clamped values into
/// \param lo    The lower bound of the range to be clamped to
/// \param hi    The upper bound of the range to be clamped to
///
  template<typename InputIterator, typename OutputIterator> 
  BOOST_CXX14_CONSTEXPR OutputIterator clamp_range ( InputIterator first, InputIterator last, OutputIterator out,
    typename std::iterator_traits<InputIterator>::value_type const & lo, 
    typename std::iterator_traits<InputIterator>::value_type const & hi )
  {
  // this could also be written with bind and std::transform
    while ( first != last )
        *out++ = boost::algorithm::clamp ( *first++, lo, hi );
    return out;
  } 

/// \fn clamp_range ( const Range &r, OutputIterator out, 
///       typename std::iterator_traits<typename boost::range_iterator<const Range>::type>::value_type const & lo,
///       typename std::iterator_traits<typename boost::range_iterator<const Range>::type>::value_type const & hi )
/// \return clamp the sequence of values [first, last) into [ lo, hi ]
/// 
/// \param r     The range of values to be clamped
/// \param out   An output iterator to write the clamped values into
/// \param lo    The lower bound of the range to be clamped to
/// \param hi    The upper bound of the range to be clamped to
///
  template<typename Range, typename OutputIterator> 
  BOOST_CXX14_CONSTEXPR typename boost::disable_if_c<boost::is_same<Range, OutputIterator>::value, OutputIterator>::type
  clamp_range ( const Range &r, OutputIterator out,
    typename std::iterator_traits<typename boost::range_iterator<const Range>::type>::value_type const & lo, 
    typename std::iterator_traits<typename boost::range_iterator<const Range>::type>::value_type const & hi )
  {
    return boost::algorithm::clamp_range ( boost::begin ( r ), boost::end ( r ), out, lo, hi );
  } 


/// \fn clamp_range ( InputIterator first, InputIterator last, OutputIterator out, 
///       std::iterator_traits<InputIterator>::value_type const & lo, 
///       std::iterator_traits<InputIterator>::value_type const & hi, Pred p )
/// \return clamp the sequence of values [first, last) into [ lo, hi ]
///     using the comparison predicate p.
/// 
/// \param first The start of the range of values
/// \param last  One past the end of the range of input values
/// \param out   An output iterator to write the clamped values into
/// \param lo    The lower bound of the range to be clamped to
/// \param hi    The upper bound of the range to be clamped to
/// \param p     A predicate to use to compare the values.
///                 p ( a, b ) returns a boolean.

///
  template<typename InputIterator, typename OutputIterator, typename Pred> 
  BOOST_CXX14_CONSTEXPR OutputIterator clamp_range ( InputIterator first, InputIterator last, OutputIterator out,
    typename std::iterator_traits<InputIterator>::value_type const & lo, 
    typename std::iterator_traits<InputIterator>::value_type const & hi, Pred p )
  {
  // this could also be written with bind and std::transform
    while ( first != last )
        *out++ = boost::algorithm::clamp ( *first++, lo, hi, p );
    return out;
  } 

/// \fn clamp_range ( const Range &r, OutputIterator out, 
///       typename std::iterator_traits<typename boost::range_iterator<const Range>::type>::value_type const & lo,
///       typename std::iterator_traits<typename boost::range_iterator<const Range>::type>::value_type const & hi,
///       Pred p )
/// \return clamp the sequence of values [first, last) into [ lo, hi ]
///     using the comparison predicate p.
/// 
/// \param r     The range of values to be clamped
/// \param out   An output iterator to write the clamped values into
/// \param lo    The lower bound of the range to be clamped to
/// \param hi    The upper bound of the range to be clamped to
/// \param p     A predicate to use to compare the values.
///                 p ( a, b ) returns a boolean.
//
//  Disable this template if the first two parameters are the same type;
//  In that case, the user will get the two iterator version.
  template<typename Range, typename OutputIterator, typename Pred> 
  BOOST_CXX14_CONSTEXPR typename boost::disable_if_c<boost::is_same<Range, OutputIterator>::value, OutputIterator>::type
  clamp_range ( const Range &r, OutputIterator out,
    typename std::iterator_traits<typename boost::range_iterator<const Range>::type>::value_type const & lo, 
    typename std::iterator_traits<typename boost::range_iterator<const Range>::type>::value_type const & hi,
    Pred p )
  {
    return boost::algorithm::clamp_range ( boost::begin ( r ), boost::end ( r ), out, lo, hi, p );
  } 


}}

#endif // BOOST_ALGORITHM_CLAMP_HPP

/* clamp.hpp
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
*/