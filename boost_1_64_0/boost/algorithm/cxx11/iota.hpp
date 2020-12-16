/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  iota.hpp
/// \brief Generate an increasing series
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_IOTA_HPP
#define BOOST_ALGORITHM_IOTA_HPP

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn iota ( ForwardIterator first, ForwardIterator last, T value )
/// \brief Generates an increasing sequence of values, and stores them in [first, last)
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param value    The initial value of the sequence to be generated
/// \note           This function is part of the C++2011 standard library.
template <typename ForwardIterator, typename T>
BOOST_CXX14_CONSTEXPR void iota ( ForwardIterator first, ForwardIterator last, T value )
{
    for ( ; first != last; ++first, ++value )
        *first = value;
}

/// \fn iota ( Range &r, T value )
/// \brief Generates an increasing sequence of values, and stores them in the input Range.
/// 
/// \param r        The input range
/// \param value    The initial value of the sequence to be generated
///
template <typename Range, typename T>
BOOST_CXX14_CONSTEXPR void iota ( Range &r, T value )
{
    boost::algorithm::iota (boost::begin(r), boost::end(r), value);
}


/// \fn iota_n ( OutputIterator out, T value, std::size_t n )
/// \brief Generates an increasing sequence of values, and stores them in the input Range.
/// 
/// \param out      An output iterator to write the results into
/// \param value    The initial value of the sequence to be generated
/// \param n        The number of items to write
///
template <typename OutputIterator, typename T>
BOOST_CXX14_CONSTEXPR OutputIterator iota_n ( OutputIterator out, T value, std::size_t n )
{
    for ( ; n > 0; --n, ++value )
        *out++ = value;

    return out;
}

}}

#endif  // BOOST_ALGORITHM_IOTA_HPP

/* iota.hpp
qkzUMUy0I+1BUkVAr2cYxCb2z+hBjeV3cbvcTOIv33ZkmLBxZHqCjp0ulgXOLpyt+CmjH4KHzVyE4TIBWWEaWCUmWFp05iR2Arf8M7BW6R2khDxjOl5/5V//R6fnZfNM/znnmJRxiQ86zHtfd5FFD4zGDqveRHmRPxN5HjoTAfprxGgm4pk7zbAFxxR/tvkLafH3obS4+4ELjvaAL3jcnhGFxK7w7sO7D+8VeK/A+zi8j8P7JLxPwu9U/E51e77FJr9+Uf7x3D+f3+bQD749Ib49Ib49J77RDwXwtWtRsDX0Gw8qFjF3TcyYHlT00dgAW4Ms4JF20hu/5spIXL9rB0z6oyZSZAFnWlxWDTYHjpg8fiIO6kF9tifCD5n3Gx5f/Fv8HXU/JilvRFSCyOeT8V/mJCfwVFiBwHB3UJCiEDvlwNwKNI+Onf1FsoxUwx+lMGP67XQnZj0m7XRz/wtzCW/Veyl08xNYjFBPybluIc/fy+EH/qA4Q3UxbIEPP5F0/zdqMZUmku1fzAGN4sRitDFbVOxpX17YvoVnNjS13e4H19Fk28jnG/VletM/uLsauKiqLD7DgAwCzlhg1PpBrZWFKcXWoujG05kcdCj78CtL3ShXs9KUKTVTCUhmX1PW1mZZm1mWpqW2fSBazTgJ+JWomZp9qNX2iFqhUlGzt/9z7ntvhgEmtdov/Anv3Xvufefee+6555577jm5hyrNnnYt8Y9O7TT+MQ0TWfAPcjEiPiy/p/GPxYJ/jMMcXWDwjzTBPzYxOwP/2ITCPOMYnFJd6jArF+G6uALgh9k8GDXQsOdZNpPPZ5lLUAa0GBKKmPFN4WVAos/TSkPNur8nkMRxEtjNbIPdCFQvNhPmY4jdaPgSD1HPyLcc4gynXDXQ1/GgiXiP5WPckP7ejfn0TCJf+WG00ZO5gKK/Lhqc3/7ZaupX6eiTO5uXTgMjNEtHyTtxnMFpJhGn6dbLcIbwv+KIpQV6n3ehTu9zZv6i9L4iMRq92/8d9H5R4qnRu6DWTXAMq6/e1nBCjyBZJigQiUGGrc8CzCEvtovhc4ASrD+f3gf5On5/pS8JNM+LR75ls7Lc2jq9Z805eXrPvux/kN71eDorz9fJfME9TeQyFzvP4+WLNIJZRehxcdb2MHUDmZFmPawPfSYKQEBe68Yz5BZJyC3Uq91YlGFqVuGOtXiuuBqDjgMks73ieWLISbDpPxWuurC4N9ruPo3ueCaz44udylvfNAh9uiHOBH93sjF5Np34/tmI/3xemNYna5t+erYb9uCKrZQC7b5ICVVXsCE8lu/utyTRa2YcuxpwLVEer2tQYcw1nGdbJs92kDzuI2SziZfvymxKGI5miii8nfO8d8G56cw0dTuFd87O913h8ivxBIhL7xVEd+N3zSHcEvANKXPUMGS5CNTFmXnyzOGAh4oZ4Brkp1AaZo62aflXQoOPaTPNHglW3gQMKPtcGMap6QCPBPU1B00HaGYLoDcJUPHdqzPx4Vz/V/E4DQLwNkCO/5DAuCblMgGL2SU6NVbINeFaln/D2ckJ6+eGCuPkiV2ZSMTNINy3vAnUgbHvkUdbmdSzCiDQPVzboGv//+CWwZjc0BPS5CAnh/IHXB2dB8RhzQEMWyGfIZU/Lohq501JLPfG9tYDYeTShtTFJ5BshE1mxSfVK7lDrh1K9wxnUwNe+a3OAp6+W79nWJ8Hvx5sat6A2djONudOM+1XJJ6btjkFfNIp+UlmzV8B4xrNY9BGR1n+AhR/1utcMtbrfLnMuVzZW0SHS1eAlpzL6SKEb8heFKqZbTXbujkXjLXNctaENvWkze7qL3N+qnaw2fPhx+He5bAtIdZT/OU=
*/