/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  equal.hpp
/// \brief Test ranges to if they are equal
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_EQUAL_HPP
#define BOOST_ALGORITHM_EQUAL_HPP

#include <iterator>

#include <boost/config.hpp>

namespace boost { namespace algorithm {

namespace detail {

    template <class T1, class T2>
    struct eq {
        BOOST_CONSTEXPR bool operator () ( const T1& v1, const T2& v2 ) const { return v1 == v2 ;}
        };
    
    template <class RandomAccessIterator1, class RandomAccessIterator2, class BinaryPredicate>
    BOOST_CXX14_CONSTEXPR
    bool equal ( RandomAccessIterator1 first1, RandomAccessIterator1 last1, 
                 RandomAccessIterator2 first2, RandomAccessIterator2 last2, BinaryPredicate pred,
                 std::random_access_iterator_tag, std::random_access_iterator_tag )
    {
    //  Random-access iterators let is check the sizes in constant time
        if ( std::distance ( first1, last1 ) != std::distance ( first2, last2 ))
            return false;

    //  std::equal
        for (; first1 != last1; ++first1, ++first2)
            if (!pred(*first1, *first2))
                return false;
        return true;
    }

    template <class InputIterator1, class InputIterator2, class BinaryPredicate>
    BOOST_CXX14_CONSTEXPR
    bool equal ( InputIterator1 first1, InputIterator1 last1, 
                 InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred,
                 std::input_iterator_tag, std::input_iterator_tag )
    {
    for (; first1 != last1 && first2 != last2; ++first1, ++first2 )
        if ( !pred(*first1, *first2 ))
            return false;

    return first1 == last1 && first2 == last2;
    }
}

/// \fn equal ( InputIterator1 first1, InputIterator1 last1, 
///             InputIterator2 first2, InputIterator2 last2,
///             BinaryPredicate pred )
/// \return true if all elements in the two ranges are equal
/// 
/// \param first1    The start of the first range.
/// \param last1     One past the end of the first range.
/// \param first2    The start of the second range.
/// \param last2     One past the end of the second range.
/// \param pred      A predicate for comparing the elements of the ranges
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
BOOST_CXX14_CONSTEXPR
bool equal ( InputIterator1 first1, InputIterator1 last1, 
             InputIterator2 first2, InputIterator2 last2, BinaryPredicate pred )
{
    return boost::algorithm::detail::equal ( 
        first1, last1, first2, last2, pred,
        typename std::iterator_traits<InputIterator1>::iterator_category (),
        typename std::iterator_traits<InputIterator2>::iterator_category ());
}

/// \fn equal ( InputIterator1 first1, InputIterator1 last1, 
///             InputIterator2 first2, InputIterator2 last2 )
/// \return true if all elements in the two ranges are equal
/// 
/// \param first1    The start of the first range.
/// \param last1     One past the end of the first range.
/// \param first2    The start of the second range.
/// \param last2     One past the end of the second range.
template <class InputIterator1, class InputIterator2>
BOOST_CXX14_CONSTEXPR
bool equal ( InputIterator1 first1, InputIterator1 last1, 
             InputIterator2 first2, InputIterator2 last2 )
{
    return boost::algorithm::detail::equal (
        first1, last1, first2, last2,
        boost::algorithm::detail::eq<
            typename std::iterator_traits<InputIterator1>::value_type,
            typename std::iterator_traits<InputIterator2>::value_type> (),
        typename std::iterator_traits<InputIterator1>::iterator_category (),
        typename std::iterator_traits<InputIterator2>::iterator_category ());
}

//  There are already range-based versions of these.

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_EQUAL_HPP

/* equal.hpp
B9hPwxUpNC7ebt5Jsd6pVuVhsa8/A6M7GYsaSo5GSeVP+9hMjbYsVVxiu/InhiysJX6IJOUavON5MT1fgeeWrKRP0V5F/PzU+fm6DdypZI9LGo1VScb5+bLHo5+fi/KlRvkkC5W3GuVve/ynz9/TNdPiyzfo2qIenUMe12m7x55zk2c7qfuOspEcb6KV1GeoI6d2IPsgZMo1ylesP6imoe8p2gGkzo9hYq9/MVlgxbt3p0/qrGz+qw4O1Seu5cTJUizNhD30ZPVamkaKGQeJjYZl6qlbBYOfcFuvXa+3tV8no60usBdoUPugOU85kEq3joS7QuoIavdAanc2Vk5uNwFOcXC7v92tGavwbpgaEA+2LFu9iUYTXNSERdiHEfbYOWGUuHdGiI3KtsURvdNFWf6YYMQrjOJjteKnPMu19a/akAf687LuRCrbsyLpWSRhRX8Qf0x8GehpXuHv738iK7xm/1TF9WMmjkDlu5YkC2u2j7DrjFzPzBkxwSjvbrJOi5Fka4ZVDugZkfltJTk3NkOK9cTjwZohWSPsI9vL/WKljFzkw8YRD8iPWP8Evoyk9FQL8l9Y/nkt5MeF5b/2lxbs/ypD+ea3muevC8vf8EIL8m9Y/qIW8kvD8jFJwvKJvl5JNgXD3qe93PR997Km70ci4Mcvbfq+fknT97yId+/iiPyXIuqn+iLav47xJ3ljuUYre8siaUUvn7C8WflSvXzy169o5XvizKp1+je+98BiDX5SWRT4c436b9Dht4DRtU7/7+r1Jy3T4O3R6l+nwyd/tFSDnxit/sfeNfDX27tiTmv9NZ7GM6L9xvfcenl1d7T2G9/b9KIGnzsnWvuDev1P6fDPRKt/XVCvv6Pev3vvj9b+oDHeev2XR6v/lqBBX3r9s+9vlb6IfiPa3/x7W3ZFa//aZt+zR2vPurV6/T/o9U/cFa39Rv3upfr4l0Zrv1F/Rx3eFq3+S0P16/gPjlZ/XKh+HX75zijwOwJ6/TP09taXtDYeIwASjGi/KE/yozH+O6O13/ieMX6zS6K136h/jQ7/6QfR2m/Uf5vev+mttievBf7n17/X3Zj/0b73mN+YL8/p418crf1+g34X6uP/QbT2h+o3xr84Wvv9zebH8h3Rxv8dsR/E+OmyQfuaKPCLDPiPdPz3bYkC7zHgH3hBg18ZDd7ZHJ+iaPCpBvwaHZ+ro8F/8bZRvz5eZ0eDf92An6HDN7wXBb70bQMfHT4QDX6IAZ+kj9fD0eDPDeH/vAb/x2jwB9/S4Z/S8bk4Gvw6A96t12+OBv+YDh/il1s3R6N/A/7rZzT4Z6PBX2rAd1ykwd8ZDT5Oh4+7Tae3btHgd6zR4ZMWaPCNm6LRvwFvjG91NHjPmmb4zIsG7zTgjf4ZFw0+NVS/jn92NPgvVuvwy3R4azT411cb+OjwuzZGo38D3qDPxdHgh6w28H9Wg58aDf5cA36Tjo8rGvzBCh1+hl5/WjT4dQZ8d53elA3R6N+A7/i0Bl8eDf4WA96t86uyluGhUgw2t6/V7UHFWeIZojaKMFLQwLvV/IJ6KAZ8wwNq6rH4DmxIsHYxa2PakQ4rh1y/+PpPr4MhRyWf0rks2CUDjDa84xQTlk9SuFVM0ZReuWZWej2+hJRer0HplaisXAQ1zp7SQ1P7sXNqUUsGzhPd+IvvrfFTHdO6UvFBbNc0C5WhRq4pX9SkTOBa2MbFhxzStp0ZhuhQRjR3el330Efy9I8AdljYR0byR+4N+4iyWHykjfiIvIOKmJ/mIqG2FYi2rV6sty1B2fE8FWAjFHGgO0Zc3fxlrwroP9HjE/Uu58EVgZKUz982VG49XbJVUVn7mUWqmotdiAk=
*/