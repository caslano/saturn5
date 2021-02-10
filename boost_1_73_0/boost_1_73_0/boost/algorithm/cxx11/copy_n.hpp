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
fD5oNhq7X+DlSyVayOUEyolrVHu33kX2jbzo1Yp2t996fd51Rm9bw27HLj6i2kzYJZsiqgm2W87ry37nvFsp427ImHa7bZsVnLooNrlrmlwlkBXvfVnypbDsOBlVRs4eXV5cDIZj56zbGl8OuyMbTLPIgvxSOWLhrlbLRE14/jy3IycVEl4U0ko3siJdNyYnr1lzMRyMB+3B+ch+YEvhvRZ7ctmsnDbgy0tZBep9dzjCfaWMkqqlo6qgZY281JZTmrWTkjYnX5Gi87VWNP97zHCE0TsEa3r8ZYWbhU9wn5TcO7q7Z+Uku48sKNyvXF+PcgtZigmLsT9ig0Tvl1i4yEamONUAWVHkEe7LziJ8Ina5KjoVEcUvO+RN2YyOD08OX1jt96PSbLXmo2a/KN4s7XIhfLuK0FoMtqF0u4rSdon/I1K3q0htN307Wnk/N2saN1M1a7Om88xcae/rCfyyLDT2mDLcIx5Ttiohg1Aur94qJCpqaMOKLXozSx7TW0rpDESpQDZzjfI2qS0WVVi18io3yUJYtZ2EfsNZVJSj2UrmMzWpqBMEkWmHM4rMprWAm+st5ri6X+FGv7mfZAr6l3/9RJeSg1mpQG/5ld1MTaj7D1PjY616yDehiR+tzvqI/xDz6qNA09yUhBU8
*/