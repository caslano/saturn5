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
RNVcWynnc0UHrAQTunDRm94XLooIFGLrKRYXDWpHbAUX5aswXwuwDgjt77VEmczHeq2CPir8U/jkl1Lj+wNCLw+SsqejLVvFE+3ZimsWnWxxTeGZh9kTTtd+bUwvNh9hHP0MQV/p7C6mYpge2UnDPJnGYz764veq9MU0h3hoMQbREwnUF62NE8BJWYlOb8bMqjUU1d4GZgVmoc/7gkZl+Rm4/eeduTsRhw0HuuXLbbttho+tsVn+ZmaKouGxKrGVP4CtbNHP4Pybal899J9x/tXDPKk/Hd1bVZopCrgvQSm0s/nml5JUjRwXvaMnzTeRQbmRnpb8HGwaGH+B+VhfnEpjoAi7QbeK64+2YwTMRRL9nE/Q1vHZKTxs6h09u+zEzjj/k0IUrC9Yqb+DRtF/jpUvuW5J6gVcNPjvi2pR1lhpv/4/iKd/hNKPNdO/pZnpw5n03pkPS7n/vOP7wxBu3/5LSqBO2RT6JnPmWLTZj2gNA/sGZKo76YyYbIX9PS9AmK71JZI4S07glCZSMBqAD+y0Tf87RDZI2Z8iIq5NooNK8IOZbdF6ZumNMkm95mePBvr7VN/qQ9BWNfyfdY+fn45tbHs+W2H7/t7Wtt/H277fmNLO+a/t+9DP2jn/tX3//dttv3/pjX9vOLGd81/b943b26Z/1vZ9ut72+32274nt1K/C9v2WXe3U3/b9w7fafh9k+57VsvzFRG9t9QmdkkJ/9+PdpvLu8XwdHCjErU7x6r/D1GDd9zenV0cKq6GvneXJrMpco9Q6luA0RSi8vfXaXR7Ok6+UWqVfxTmvpVX+JLzK5Re2BVuJ9GOH/IXOB7OUCYJ6oKBWaFrfjQz0V3ZZ9TojoB3Jt8TX6b9vZg57LF3leIFT/HD9EXVDnHFjaxrJmO48Vvi2xXOwby6mUikHPSe14Yc/62ZdfHoFJhFxLFeO9VFRQsVA+E/GyH6qJBPDcBxB/3oDQMQGpQc0SVsv0gv2NCXxrVzBKZCSXeAmM5Ol16Um0BZLRZTDqaVwmkNedRv0n2lq55MCLApjeQRcGYwct/PE9ARtHevDWvr3ylBfj1jFUVDAd1U0LSVVAEPvtXF00ucxVPJFJPKcwPCpOBoZ6kuLVfTE4Qb09SNjYiZwCMTeZd/2bew/Mk16w8S1P6JS296BttUvbbCII7e2OMPFp8pvIA665rzEBnwOCAHwkwj+9ZNa7R3U8GW51pScX1uqJhysX9V2/b9mmOXVT3RZOvUjMCyz9U/o25RxkLAkrRyRyV4glBfOo1RLeaU+SlZeT/C31fpJVOL1RN5X7t59MNcQoDwWqb6TbvN/of8G3WBo5JmkRMOXVCr06SgDsqVLVK/iVw+tdcNu0GQ2F//UTB5k/RDhVclLsw8mApCpuvUeX/KQ7Gk0J7DZM0BVNiNfjuceODQqbof/mXUL5NIZYuhmb4JNbRrnbPoMGp0o2Q7Iq4RZoDBzuq453Q7/SzPyvDCX23Tt0hjqpt+1mXpoZDZ0ez9Jxi2ICQ7j1sOePFD+aASPeXv3ITjxtevXyf7fLMSNuQG69G4liqJPPEEu5mnYQ51x8w+MpqZmLzZ6YjGzoVh5L9ytky1yPqxNb/yae2+thjAAOJXVk8VdLWQb/cMrUg1+s446CAfl5VNDO5LKzwp97ShPi5shYWPiDWqpgMkm0zRzn5Lt0xL5Rqsl63mb24+By+iCUz9U444klcLZXupk2OzoP9/NQGmG5/NgOJUrcIh2Tvb+fsRtvy87CesG87JsNZfKrC88xhCLFKw0lqCdtlhLe067kKK/5Cb7/Mig9+f3TFBYV1GpmovvKEKQdWyXnZ2ZgBMcKHDhAFI9TR+zwWKGQ4g=
*/