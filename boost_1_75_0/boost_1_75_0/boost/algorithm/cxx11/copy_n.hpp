/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  copy_n.hpp
/// \brief Copy n items from one sequence to another
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_COPY_N_HPP
#define BOOST_ALGORITHM_COPY_N_HPP

#include <boost/config.hpp>

namespace boost { namespace algorithm {

/// \fn copy_n ( InputIterator first, Size n, OutputIterator result )
/// \brief Copies exactly n (n > 0) elements from the range starting at first to
///     the range starting at result.
/// \return         The updated output iterator
/// 
/// \param first    The start of the input sequence
/// \param n        The number of elements to copy
/// \param result   An output iterator to write the results into
/// \note           This function is part of the C++2011 standard library.
template <typename InputIterator, typename Size, typename OutputIterator>
BOOST_CXX14_CONSTEXPR OutputIterator copy_n ( InputIterator first, Size n, OutputIterator result )
{
    for ( ; n > 0; --n, ++first, ++result )
        *result = *first;
    return result;
}
}} // namespace boost and algorithm

#endif  // BOOST_ALGORITHM_COPY_IF_HPP

/* copy_n.hpp
oOvhlOvhOAhaNxxdzNgdOc3t2OK2a3QHVuLMJTW4fC8CXHK7I49WA5Qgz5CPoFPFLUEKyU2Lsa9p0d4EtLCvv1R5HWO0eVUs/lvYw+sr7CacxywtUH+PbmZt+Vu3Dw/tTReA6QAtxD6WsEeuWlrJmU3odACk/LWB2yEYfYv8q8GAPBeKJcB+PUWq/XrPVV6UIy87Pgw+1uevTaV0f6UuCZL209r56jo8R9DLfVJOn9d+UtLGBcH2op2zbDFtQTsGrIa6vCF7Q3q1LpAwsy1KP5QZBkgUMS3chbQqx9J08hWWjyySK7RaCds0NmfWX00esgr0yEiNYi/+Z2mVfZkqoM8arsfNlsf5ldp/FPYsonz/6vEg/667jv7z07T7FO71fnTEcGIch4JA7sKXQE6lT572Qcn1SD4wgqrNedx9WJGZ0tSmM8lEzFgIzrfVk3eyhhpaLMk+cdVVa050wzz36humbrM+LU8yenr8Fc3sevddQnce5dVsHYBSCEishrL5TzIMjTKMBS9/5zgrQa9rsjU2TFdVGFgSn86gwqovX0PS0JHkLZ+yY2BErKa7zJTcsigZ95Nf6YLhpvSje9dJeRIkjUg12+hiRDnbrstpXTcRA3B2DE64IF1VaW5pxsRoPjtrcUzaMMzW+fYhls0C7UyuBmw/Dz8sO8WqMTDjooMiRexHHBi50cGAgePj/pPh3m1E1KypgMfVQKf2
*/