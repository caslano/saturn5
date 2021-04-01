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
nmGWPaRV0q0FzrraVPvKBKxRk+zgmN/kjC8Dv+p/oDZVzwMJIzI9fZ3qkVy2wddfJVYGXN+00TCRryLdABk938cbIGxyorI51VIQ2RlWzTYwjAg+LstA2el7Q31lw818zsvzCLBbRw/edqkf8crmLtV+hNBFLiEDrlBAl0pEtEyAvQDE+nSOpUdJJOmEJm+MfkhI3N7LNR2kNs0SMfZYv/AYb7oMrHCbNb79OKic8A4rGHRLfMIgzLBnzrCVevWUJ4whaKX1pO9xvv9Q5wf62fSVR/sb3c8K43wmSKXwtGquJFgiFO45G4D6boW+R9tPffTulr64+x3ujsjuHshQIQBPWwYWYKKZlHZ6V1Y/YI5QYeDDlbeQrJ+vl37LbGnLPZ551Fx0iVjkfTNOEH5aGHxLnVyGD6UZhxMD/+sKmYe2hA/7V3W3s28Q1Pwakz6spVm4GU8HEBQ2BYVcBQ1PM1/WwaLzT87ekt7aIR8CCJVgKKdaNEsZCz8JXNI57dUDazg8smrNWzO+17zLggrx2A2goETxL4onsIdE0vNb4Mk3B2DeFRUnfUhMig==
*/