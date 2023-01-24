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
u/1D6ct50WMyxuvzkQ4QKAz2g2IizkRsUbLzW+xSUOHpgMguR4MPS6SoF0cl3v0Facvt4PhSLU9SxAJhOR7TeMk0exOFzWlnpjdzb4pkoEYkZOHcO8bI2xeRWU2EtaNuV+K6NUfj7e262TDoQzLwIMunsrZSc2a24V92oc31vjnzZPl9+vhZUQaEtj+iiqDFkDxGU3Z4iccmsLPeo0N45mmyEKAMg4BwdYw3/Bj1c325tpp2E/hslhSjPzp6zTnKP+RhiXTVwLiaQcdHEQr355FgvzyHZ91HEHwy+1w330X+rCHQa6njVux+/c6vjD1yBW84dsJjTYm9gRxq/cuocZ7mooIigLPgWfZ+IHyzSuDR9kOdx8e/ARz79XNhQMqzrD+SYfYbLa0ti8lB3ve1azy5vFEiKicVaDeIZWDJFKXaX8PkHzPH9QGvC+PLLLgK7jH59viFZWLYmjDBvg2yAv4FQ+Xo1lrrICeIFU7AdOqlEGqc/kBuf59P8+09yAd7SucxUDNaMNC8svAQlHwWbtOsn2c7+2kWpt/GKL5d74B3Of7GwKkIQgjt74JQmttQdrofvxA5hZoFOkzclj+fbdwS63razTMwe5fgtLfxJvyHxJ0jYpuVdtZOpefkUXxBPLh5MAJjG3z33QpVB3EJJ5vvtuKnAh/puH1qXhcET9eEp+S2Jjhro8qRILeUMWRcdW6ROiOo9iNEauCR
*/