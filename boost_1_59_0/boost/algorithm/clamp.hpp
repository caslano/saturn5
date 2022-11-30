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
7NStlsunj3SxGlLyHY3lXOz5wvtrfQMxWrnxB3WwJTOyQdBxzmHg0qP/GqOWv3lp1zlYYhUvU40xr2KvZ7VJQExqGcqTSub8TiMtneHkMKiUDAyMcYeQMLTno8SimhKqqzfB545dNRHdMvFliDZhsd3iVyoRb1SyGLepezjvs72/jsJjLrqlH2UdNdlUQ7uF71+KMmmq0/6qUxGbxGaU1bpQx8qJxDtXwQsFFzgJsZBNGiF0+KWgreILybQ6uPIGd9AX1+9E5e0RRKD6YkgkkxqfDOgRwso0ISqyEHIYxWFII4Gm9TaEvXrnpEaJVAut5BC7Los6YOJwnjamYBImtRwUOmSQtqYqEiYqiwS05kAt6v+RITUnEygNk9xm4xlumGQGOrADc1BNZ3CiWQ5/KltUEI2jX3HqQAC3KPB/UrQ1uH59/RrO2rSxabAqUNVZ5uv52vbQ/MB//rqG6t5MaEOpmy89t+f7yj035jRaeadd1PaQpYPys9djnk9DtGTqbMxi/KzfYvJoQqEiq5dCA6NeOgWBA1vFXJgZV3fXaE/md52qLMtySKKwnc8InAZkGZqKdGAw940eXQ1RLjpwqfYtqNdO8ePjTfTZ1fauPTYzTM7dIfZi6xc1+9jIZziVdGYl9aQ8GEWDOC7jyhcT/NVfyo1PhWxtM14FLqarZu4rowaVI2vzIioO70B3FS/d3I/JWd1XONfUzWnM6dUusOy0yqOUHGen0ajkBWrN4krpbi5ftxf1Qk1GwzqffXXNGu26g1l2WlUZxsYSHtWgY2GVVbsmblWf5S7cNcMe8vauLfGzqTQBRSV8CbcytyI1A8qkZNbr4UYCO7FVpNRsjXEFhdPBsNJ7i2PrYO0wX9CG0lhzRoSfRmCQCiZgUDHmYLN4lZyNpxC7D3K4PV5CNjL9xdbmqFnUI5SlpKgKXs00Gw9y6l59k+WutGTWkuo83gU02e5qxUn26sffXNR5VlVSPs5YKUsvfU6Ad5QylufDUluLCQld5i4SL6xTAml385OlSe5810VVpmvuawf0uvZlvKmXRMX4Y7xSoweJEwuZU1vjKhxxkFiAp/mDJU5JTl2UytDxVDEyCSpirARrlM2oQtrqDmeltdVy7Ia1VMSMhoWgchuLlh2ODi+FzGKbEkjkT8IZs/C+fCV3TEXcKitW9V/7HKoanhGWiZ4U3BV4QrowQ9Ta+yu/6Kv6NlIhjxiDQ+4oeYvUy2MGYMXbdkfMoft5eV8/Qfz2Eiv+7cOlHP+pKh0LCxMbGyvr/ymc96cyFk5mJlY2Fq7/A1U6Zs5/Dedx/Vs4j+N/wnmswpwiXBxiHOyi4qJsEsIswuKsXMKcbCzif7woE6eEABEfizgHCwcLJxe7BPefckwSwtyiwmLMzBzCrJxcHCwSbP8hnMfJ8r8D520BQEDTACBgjH+2XwAQCGQAyBcqAAh0JgAExhIAApsHAIHzAYCwvwNAOKr+I2iPmZWbm/O/EbXHxkzEyv1vqD1JZ0e3r39BVX9jtBhl/8WpMqo5Gzu4fP0L3zP1/Jcv+VtJAYF/5vz+Xun/OefHxvGfSdadp0x9R2WG+51LdBlPSjTThM/rXv0lnoskdsDcMRhJpylv41GwMuk5Sewu6te0zPkRZ2z3lCHfscs3hBjkt2yZVx3HnZ0x+N2hLT9YBikxK5wdFRllyBjO0hLIyDmhGgVYWFMC/2jMn4x9oz9QouTH0SDUd3EkosxC+gxciohGf+oWyx/y27WkmLSw9bhdCW7boIfQ77Ol/ZQBNZ89OfuqXuHu5fo1+2jGFvMkfX3MFV6wv8VjRzOWwPbOUPcpuZMyXmP6R4LOU4aSsITOYBPacACYm0ui8yKNGQQxeRY2iPnvRaVSMm7dkSqLUiuTMDffpWshLdSBmZnexZF3YVt50OEMY524LGQO9xNXdy6bNc/Z/ne3Estc/dLDa8sc0ytXxm9bTmSbQZRmKDhlhp577fIAsd/psYuKPNqXavpoq+WqpUhlKSy6Wys8cX0Ka1Q/vhhnLOKij9okTfb8VuY6ZoPJzvF1z84ZYoLh1b088OQ3VfyMy/B3m7/iuHY7EKQT3rtBIRBoodq7KXRXAy/zG9jgtQtmNUCValrjSEtEBjN160+HQfkxONgy86mVerkzUVjjeQfhuHdz11LE4IehRfPho1hgjfreOP/b3Lbj/gMG+tog5L81R/hnl5XoX2jAP7ts/wPuk7Zn/ztN8Z+BhnLasioqOrTCztbGdvJq/xY05Pg/AA05/6tBQzYW1r9zP2zM/4P7YeVmVJU3drH9O5bw/xIERAmg/icICPsv6vCf2ThwMAjIvzggEiQACDgoCDjY/zoFAgoGDoGMAolKzMIs7PSvwLjbrSn/v5cL0lvkgFWooB/O5FW1GTSkEmawxYUoVU8FymeXNZnUJBOlsccGzZWPOVNMzq/WaY6iqbca3PGvznFoPVbLP1FVOHceeTeV2NVd6mVeKWvse08/2sqtmG62cm5PWrIGAABgie0zle0e9PYX84uZvzFJO318s1I2Y83XWm0d3UsaN5la8U/3zoDVd7YMG2O63k3sJdehw5eGhObv1BFNYb95mlIcm5cX29PQ3hmP5cQrOZgXKit8m383rf8qPfaXMaE3rvteZa573sxevT8oKH/dxfmvNQ0I/yvhSjZ2zn8nmv6LAgjnXwLoHyII/E+YQIB9+Re4EvTPPsQ/nP0rgpBR0FiMUYmZhZWdSP45hp7f/npH/HmFqDQl7+Top+WjVZlzWaaZH8nTSk8iOJ91OlvPWmRTWM9aJgC/JSAjwzc3XvNE35DaV/EpFLxFvOoKotPUDMem/ubQxTq2MxLKujLqRcZMeGhO/5otvjVLaGudBj2v/05aaG2ZBpOi6S+73RssJ2vLTF850FxLpPBNLPMbefSXJEfwOjsc+cbEwYZ8e5uyHe7H3KlwkdUF1T6XS8FchJSqgpLkg7rc4iulfDMxE13tSHsL8qZAUJcJezyiW2lTUl3JL3yzhjNVmaXyB4kfYTbEwxNi3Lg/w8n/jVE0MZCm7AAXiwecO/gy5lvDJFK5gsd7D4waWP8rQUVWdqb/PiH21xgF8s+sIhgIKPhfYxTRnwgDBQWBAPnHMQoZhRkMnJhE2Djwn6Praea6AfgnV6ZbZKNxjJPSJq5S/JcV1KlZl8QTeU7q7WbrNKRxlWpU7k9SzyU2qKosuaiqzDWYzDeeNZpGvegwD/oyftntysbHB3xB4gPmorcKOorloo8qrs1gf92n7nYUb/Oj/PLsh3H8lEW6/2RYsuvz9eaNTusXACAUeMgb4tg+s07qu/l9B/fiTilf6c+vlWAeSYhxNjPFS7fHmLH/2+//T2jJ/7/2Ozvzf6N+x/kbpw3yT9g24O/cNvlfHQ8CBvYPY8ufoQUZnJkVRdnpz+VJWAXtX/X+LcWLquPRrbTAj+aPOD7HYo6PEHq127OEbJvSXLOYT8AC3yt5wGK5b7ytKp9dsE76nhnsgmI9xEnpCui96uSwq+USOsNevsCvMg986Pte2VZjcIgO5yuIDpWrv7yRhrAsgiwlvzYEHTdd1idAA0afQZY/7LeMLPU+fExyquooPrSE07iBsgqN0PCcJAq79VNChWJfWCzOP9biwo9QJv/e+d0wf4F65OKBm1F+iZbsMbX/Z7V6P5x7TqumAdY7u3N5C7Z/oBQ1FKk8ntRC6a5ElSAMDpsVB90SWTuYyYSzbO3fdrGUA7Ew9jD6Mfo1eoaxQUjVqctT5V0pyrXZpzPKzIx6Q4hh1Xu7vxXQbG91KPNzcaah4VQTJuNUYz3lLXwdGkQ7Dd//awM9DfOjwoAWRwr/9+KS9f+Ly/8vLv8bxiXb/2tAP+t/n7j8d4B+yP8toH86o18DAMAsd5P6QtanBQAYlC0QESVBGwFAvErVAoLkyAMAECfZKn/7pOC/19zs/1vNLW/s6mpOpPtn9vjXfab/ncaXdDb2/HdudPzP9mdm5v4Pm//bqqkRFkRhgElPlY21LR2jrRXJ2J8gNrGRtc/wsLL+zk7oF9p2P3dqKopDAdS5QVHTwsVjMVcwj0cDCSUXd9C50C8uW2kDR7N4gWE6QjcrtjhBuorpRkcM/ulh7RlAFridgGFhbITMyZZqjCtPW2j0BADMwGHB/Yf3Iv/vZrz/dWoHXP/P1A44/63aASvLf652YDPwl9pBHq8Vtz6cwqwKVUgPkzlR9Md0I9RXO3J2ObtCruj1LhzL4QJQU4JL311iNwdD3UuUckWEksKQ4NtUawRY3L4cicP8ymmepAsZ6Nkql4Kye9GANsh78t9Z3wb7R8JyCIR8a8nd/Qb6p1pRN+iZDaxJcmsDSkBkg+m85q71FUNoTIcWoy5nvdAgHwcecaArKseqgqBTD37C1z2QCusPs2kZmuEQOX4+L0jcBz8v0O3cQJDpo8VNTQ9rbuwnSQW2aBmwHkd4SzYwyXb6RKyfLg57rjqii4rlOyB+AEw0HBL+bb9z/XsCBxz/S+CAnYP5HwUOmDn+l8ABKwv7vyNwwMHB/rdTRCxMTEx/q+yfFA64/1nh4F+F2P+NwgHLn0r/rnDAxfUfKxwwc/9DIHD/W/0xdm5upv+pcMDNxM7+n8lgnL9DuaJJzjHBePzgI0XiLkQXIYnIy9a3B8CtLtiMcGMxcXwhEyIiqwRAUuL1clFmMU9iUSLHMCNwWX4dgIbjgrLby/ribWthK9mPI+i3efl+8Tzljygkr/5453qvpvnn9UgXgiKSEW8ekoQdPKQY4+f6HFMXf0tPjF9NyN9Vk26doycrNXRL7Pi7EqIYdurdVdJQyl9C6uFEO/qEr8XNx1GQGGyKXCyDyXsnC4Ix+yv/elynbMTTe9YoeUO312FRVQic93ekZk8HT+sVb0bfByxi0jQR38DW+Jn1pZMvRbhEG24XQW1zfrzkTkizl0i7/qX1XhrUI9yP7iKT+rDHj5jJOc21z1+cGInj6IJvcspnIfYfO4nW4Y7ZQ9hsW2vbmh3eTHldRQxWxYaLRTEXkxnHfT2AHCKUBBRi/olal+UJC674yLK2MpYoU5Xk7ClmfVkZN8/A5NZ9VtvhjtHZNhpnnOQC1KFBviJW4kjwhB3ulKMibGthlko0ILVSpgTcbDIbJb1wEAxyXrJbOBca+Xg+doLQb6XLCGhRviu5m66AR7FEaZ2JjCYjYm0LQ8bGmrTlJfUHtyZffV0NbeZwux/6yuoyzctLlLTlNCfDLg/3KVGrJzI3Yb6+mDCpiRsP96jxZuTPo11+3XkdlUFvJoaf5YFrycua0BnWLVA16yVYelWL0pL7bCpom+tt5dUVF2001bZhpzRrS2b8Gac2203YxzJeyILYQiZm4OlCJQksKtInw9hAH2fo1rB1uQsylKbRaqnmdA5Fk2O69rSyWexZtK+aA0s9vIBFCW3NnsyzBxV7qN0N6awV7khdu4BDQEskpdNa64jXqgBER95Hs6PRC6tP9AFA325TXpgFToc/Eak1d31KgR3zJIRHKaa4T0UktCKkAlq1YJSLhCopZaQopV6NO7hRY1Jjkvg8+Tb5VkrSvNUZ+bhIL39djm8UZJ9yVvcy/xC1xiAPE6n7o+qDnpothzWHEmRPfE8cZdQqdSYjhHXVopE8+Av6oTaOeDuTYBxskrTkbJzYCBPLdzly1hE+FdHURBdhZ8340xGc+lS2+Amg9A3oivAmufewJdOLP3H4TyF4T9adm/cbsBtSDj+lTZO9cKCk/TqRI8QbQClu5Qnk2QlXkErQ+M9hyr8Ok8JdqcZ7IckI2u9BAS3t3vLeKmMJE3MbnILf+JL9lPxAVBCFjzHt3wLeEmMJkw2br0VvaDkc4g1DZxFHaoTLQWQcW67BbhD+1Nnt8KdOTrt1om7oYtxZMpY0uhDm7rPuxGHdh8wtxu7YRE8o8gZU8lsGmQP+bZfuN4HRQ7DksXCqNH2qtA2qhDglEu8/pkzyqkRCuIbyDE5+Qy0DZE0ePqRKYFQiMVxFeYYhv2GXAeImD/slD7dQJVx+iJNUDNs4c3peEZLf8MsAATJAqOThOKqEXCUSwT9VQJDf0NqMO1Klbymz+OeZfTSyHzAmTwknTxEnjxknjyEnS5FQIzOxNYuhZSRH9CWiKP8iRxaXkhFDTkJRLioSQ+OmRhaXlhFT/oRC8fzeIbFJ3C5MshWfO2yYrCw/86f43Z8ypNTI5H+2YmkVEhlVWRIZiz++oUgs+UA6kor+TxkdCvKCxnqygkYFGTHrpOSIWY4yZpn2IrPkB+kRKny6WGUeiv1CV5FnV4lns3w95ypOdT6qNLtkWcxkWYTRYlsVhk/TSJ9TKTJE8ll48ll88lkw8llU8kRH2SJMmSJOmSJEmSJGmSIA+W4TuUmBmA8VsqBMERI5ilAkuH1kiBKJcbKUYLKU//wPEKp0VLtY7IhE7JBEapERscREkDGFKvc11ml1JlSsIpgSAIRF8HeyOLSADhMztHS7DvjULi1sWj3zjuD5hd8KmThQnpckbk3XBErk7q2PCW2rTz0llc6EJG7sV9aIrGaEKEEfWMIUCdhGC6fD2mahdWM7jWs7dwn91nH91jX91rn9x6bhc5TUCr/98iBpB+Mf6VU0cbdW1KCBvnHz/jYzpQrRAi46d61zBYxZGL7HjUe0peKGvPQvv61nQErFBbnoX2asZxQVoo3O5gQaEbmYzrW9RbQRxuoOTa7WWd6aMZWglCD8Attbel53gqFNu9fmkcJxTpT68Wx+yUdeXUxI616ht68qfpgJ3je8DzC6HxueJ3Zrr/b5BVHS2beGNb62Vw7Hbi/xSTXHtxi9vYGQDuVVlYU/FPnxxCPk09JXv7AqLcFz3FeK8qcVLLvnVbeU4SPct4l27ig5ribvp+Cc0Udb5Pa5pfhe2pfO8yI0zZVwSdVAW49sNuXW6jhTN+g4Vekf8GumL47bzNE88O0oOaN7b5Udg4W/TOe7c887hL8M5z9wzRuEr1qqsjxN2EdCedUgQseDwPmAucNeea8ceMF6I8ts9PWoGlUQv0dlt2d0grdWrAwp6Ofm0Zm5Y7eD3pnDt+PKVJs/osbyDxOQyWuD6SqyrEg0R7JZZq5oXD21nmO3gFflFw0/vLLQOxLmdMI7rA9dBPNwCntO5hgpBtR8yRiqBuFGdkdtH1kU/eEm5FGJDr2s7U7anuBqwtmQKW350xR3ZFZdnzz4TvK+NM8Pkud38f5s6LgO/VeHhkOc8Htwzl/GS1DkT0sqlA7WAin1RXYVoa44rXFQnhiXk7eehA43AMG03CnGbdonGT/s7izD/pp9zquFN3c/zu60rSHCbcTr+zfjDyr/IMGJ3MOaK/w3+a6kv2AVwtupZ8433Q/8z8BPMndM70jKiOCBCC263wO/uNTwKL6jDEUmDZTtUu/KOX3nMqzEsB0c3D3e1d5luda79rkWcQr9pdIh1iHXIdIh0yGhR27AuEm1SVeNsRThEWU7+DoI6ZT0FPFL3UdunUKAtouqi6aLoYu6i7SL8QLlMSo3yjByK0owojvCPwJqMGSAXHu2uESFtSx0XsKG0S3s8UFqRQWzrCKZ0i3NS6azSEAlEJgEUxw/b4hDJl5kYp3BJkqTZnMP/0Lh29ALNzId
*/