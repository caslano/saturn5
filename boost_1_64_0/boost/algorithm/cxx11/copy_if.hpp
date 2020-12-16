/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  copy_if.hpp
/// \brief Copy a subset of a sequence to a new sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_COPY_IF_HPP
#define BOOST_ALGORITHM_COPY_IF_HPP

#include <utility>    // for std::pair, std::make_pair

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn copy_if ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
/// \brief Copies all the elements from the input range that satisfy the
/// predicate to the output range.
/// \return The updated output iterator
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
/// \note           This function is part of the C++2011 standard library.
template<typename InputIterator, typename OutputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR OutputIterator copy_if ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
{
    for ( ; first != last; ++first )
        if (p(*first))
            *result++ = *first;
    return result;
}

/// \fn copy_if ( const Range &r, OutputIterator result, Predicate p )
/// \brief Copies all the elements from the input range that satisfy the
/// predicate to the output range.
/// \return The updated output iterator
/// 
/// \param r        The input range
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename Range, typename OutputIterator, typename Predicate>
BOOST_CXX14_CONSTEXPR OutputIterator copy_if ( const Range &r, OutputIterator result, Predicate p )
{
    return boost::algorithm::copy_if (boost::begin (r), boost::end(r), result, p);
}


/// \fn copy_while ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that
///     satisfy the predicate to the output range.
/// \return The updated input and output iterators
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename InputIterator, typename OutputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR std::pair<InputIterator, OutputIterator>
copy_while ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
{
    for ( ; first != last && p(*first); ++first )
        *result++ = *first;
    return std::make_pair(first, result);
}

/// \fn copy_while ( const Range &r, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that
///     satisfy the predicate to the output range.
/// \return The updated input and output iterators
/// 
/// \param r        The input range
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename Range, typename OutputIterator, typename Predicate>
BOOST_CXX14_CONSTEXPR std::pair<typename boost::range_iterator<const Range>::type, OutputIterator> 
copy_while ( const Range &r, OutputIterator result, Predicate p )
{
    return boost::algorithm::copy_while (boost::begin (r), boost::end(r), result, p);
}


/// \fn copy_until ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that do not
///     satisfy the predicate to the output range.
/// \return The updated output iterator
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename InputIterator, typename OutputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR std::pair<InputIterator, OutputIterator>
copy_until ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
{
    for ( ; first != last && !p(*first); ++first )
        *result++ = *first;
    return std::make_pair(first, result);
}

/// \fn copy_until ( const Range &r, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that do not
///     satisfy the predicate to the output range.
/// \return The updated output iterator
/// 
/// \param r        The input range
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename Range, typename OutputIterator, typename Predicate>
BOOST_CXX14_CONSTEXPR std::pair<typename boost::range_iterator<const Range>::type, OutputIterator> 
copy_until ( const Range &r, OutputIterator result, Predicate p )
{
    return boost::algorithm::copy_until (boost::begin (r), boost::end(r), result, p);
}

}} // namespace boost and algorithm

#endif  // BOOST_ALGORITHM_COPY_IF_HPP

/* copy_if.hpp
pJUvn9kHkLZo5XF3+Ls8+8bAeriKPuSS8wg+VH0zvPk0zgQ0E+V7axVakrcqkBPeFVpstEfBYl/DPIdBsjCNH9IKnztswxM6TF03AcabgrdkusR5W+DfUpjKoZbXTFtCTlVfIGxi9S1+9ln181BILQov/weU5kXIeapuWoK2QIjNTlYlrK5Cm2g+qLfwfJj6n8d1j8zvnploTbUfPps6VQYml+J3vzT5XSfzuw3JOfeQxe+wcQJWR5NrolgEE/uxsfALHNTYvdTbhUUBTGU0bfJPhXsNNSPYkWBvOO70/AIHOd5gRNDSysTP8cqsTNSFla2oCp+5HPsvoEls4lzErCt5au3Jm/55fEvcX5Vcw33tcusGK7GMA35glGYUudFXU0SDVETQfYiGtIUzG7uwoApvZeRNhYVIxE8JdDKnwioGhfjqtUQsiIakN2nXDdbGgXzl0+v62vmgWinteqbOUJq9CCgHg+qkQ06X/dmRAcaWoQkXyZfZCMbneeEYPLLTAvST37lk0tdlFn2NmWDR1wVPp8vTZ0362gf66i1Pq4i+2iz6EqK0Oh/PJUAM21yhwrTTyu2jpKvImZKurouiwnVYEJ3P9IspE2L28OL1VUu00r2b7heIJJt7Sle0w5UmyTJdum78k5CuLFjTPXMPXJ+k0ms+bSrtJV9BsMKHfcml1ng8/VTaeGC+t/AgtNN4rLdswDu1tPH4gek1OVVh8Vp9Eq0rSnhSJq4dw6dQ2m+3JYdEuHrDdCUkL7IClSK3D7mJkqUusO1TNbHdWQHMuT3MfOoYk1AgYDEDCh/7oyODM6Xj2LtHo3chj2JXFw/TsMYuJXdezBrYYfzwsA1R7d6tgdjkv2MuYNfn5vmVsLNk43+uHPiCw0XbQc82+ITn4AFOtUiV4BWeiTf4fssRxUbpNuTAR86SiSx2ZJE4C6pQMjlLJmXhxzJJhp85stg5i4QsEmdBzfQxQpaeCrvKR/WmAFXsxA36hZvojBL2joegEvY+7rQloEZ3QkBppR6SUFtZQpFwwogkierXk4S7N03mz6SASvIHUKQIjTzkKxZFFvz6KBLI5BDw5mSipKPNs4hDTBQcwhIVivdNpjMQEiiFXAuywC46VBY+fq2X8Emc/xzNUZc3WUHs8k6uAd4KEEGcUzAJ1KeScog2k+Km9KuM80mE8088lSFf0m0ErkvSb0jkG92s3qfLl2ss+dJDtOyCaOHDF4TDiDg3bCoeJSxaEud9mW5e2SMwNAYOCBrYJSTMWcTAvAfB9YSCmn6/rI/cwXvLm1dJwAA7IzBrv9iZkjDidEIS1E8mYcCAelxN1H6xeZZoVlmGhaQd0wek7qxNv1lI0VVfmg+MhOs/G90P/gUvZLy+//emyCnTl05nbjfWB3vLOeQkPVDseDXpzbC1+ALDKowGEkpvd9hBX1dBYZiEtW5F4msDqRifmutQwu90QlTjkwZk4isO7yScJ9H6eTektzhch6pP0Q/QV7C0m+eTvaBvjYXhDlv1tiiDQr4egKtXhzgB3gwf8/qko/5hP4SoUWyI3DvWnKpz7rSJ+/qFtroPKbN5/wzDrtLF9vQBJvzlysJNGAY3CjOiV2SSXXS5+/44HsJL0DG2aArS5E2H6Jiy6SdBAQE2x1QkTi3AYjLM2cTZ8D76M1Nt9HS3K/4uzoWTNVR86cvveHDzA/xKRxPlhjB+Z2NrTjWaMQbsWDrQU1orR7JpGC8dWGHUh99xm9VUt3Y44O83byCgS8Lww5OEBq1ofGvSHCPDhQbvZz+vhc88Lf6Qc5La9a4WG19BPCr+gVO5tT7j74bBtADlU4uadl2MYrp+Q36Di6hGnOelM5/v54uz+yU=
*/