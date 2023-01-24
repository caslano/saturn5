/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  partition_copy.hpp
/// \brief Copy a subset of a sequence to a new sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_PARTITION_COPY_HPP
#define BOOST_ALGORITHM_PARTITION_COPY_HPP

#include <utility>  // for std::pair

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn partition_copy ( InputIterator first, InputIterator last,
///     OutputIterator1 out_true, OutputIterator2 out_false, UnaryPredicate p )
/// \brief Copies the elements that satisfy the predicate p from the range [first, last) 
///     to the range beginning at d_first_true, and
///     copies the elements that do not satisfy p to the range beginning at d_first_false.
///
/// 
/// \param first     The start of the input sequence
/// \param last      One past the end of the input sequence
/// \param out_true  An output iterator to write the elements that satisfy the predicate into
/// \param out_false An output iterator to write the elements that do not satisfy the predicate into
/// \param p         A predicate for dividing the elements of the input sequence.
///
/// \note            This function is part of the C++2011 standard library.
template <typename InputIterator, 
        typename OutputIterator1, typename OutputIterator2, typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR std::pair<OutputIterator1, OutputIterator2>
partition_copy ( InputIterator first, InputIterator last,
        OutputIterator1 out_true, OutputIterator2 out_false, UnaryPredicate p )
{
    for ( ; first != last; ++first )
        if ( p (*first))
            *out_true++ = *first;
        else
            *out_false++ = *first;
    return std::pair<OutputIterator1, OutputIterator2> ( out_true, out_false );
}

/// \fn partition_copy ( const Range &r, 
///     OutputIterator1 out_true, OutputIterator2 out_false, UnaryPredicate p )
/// 
/// \param r         The input range
/// \param out_true  An output iterator to write the elements that satisfy the predicate into
/// \param out_false An output iterator to write the elements that do not satisfy the predicate into
/// \param p         A predicate for dividing the elements of the input sequence.
///
template <typename Range, typename OutputIterator1, typename OutputIterator2, 
            typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR std::pair<OutputIterator1, OutputIterator2>
partition_copy ( const Range &r, OutputIterator1 out_true, OutputIterator2 out_false, 
                                UnaryPredicate p )
{
    return boost::algorithm::partition_copy 
                      (boost::begin(r), boost::end(r), out_true, out_false, p );
}

}} // namespace boost and algorithm

#endif  // BOOST_ALGORITHM_PARTITION_COPY_HPP

/* partition_copy.hpp
6zq4qLocykF00v+KbLSN8MRAsIVzfep9xTzRM1GJtybN/MTSefqmvLqOAdBcERL/Q1zn2DmLHzGhd9ZyvQvZxV5Whi8jxBdwY+Es092KDipAhwTVdFagIU0oKH1iSvzYZ3YKWejCTFGBxNGgIie20yr6og6GUCENDi3SXT0sLL2NIwllEDWsspIQ4k+N/abXWjvmxF+hfLr06fWWn2JjJ/RZ8kvvE/xxbBwr6l39gt3N9wX64SmlI+/Ntjd2Ilzzc868V0PTXfmArjfJwoqGQtR/0xWtJkk/a1ViYZa5umFl9zz5nIVe1ovdmgxnF9PwSi1KqDlVTWyL4Z1A67mfUa/6qiAnc+khVq5LJFEGQ4Gw8A3DxDY8qtfO1W3i03kOvxFIKl5+W4SAAzgigIJeXE8yNWpa7bWVhs/yHfwi81ZNQrL0kCMKrwchD/ikUM3jF6Uq9vU8kjxSxb9j+1n8YuAItmpc9tB0UIO2Hw+xcyAsHKQbs25q7jTFRaZvcv+GV5iKC7T6pRJ8s3fAsP55kf1wjYYbxAm+KJux8A/9QZRzoUPSVVBlWEOZry8sEiEDfsGjCej/ELMlo/Y5WUy5D58xrVGFD/LXg0xIweJMWSDpL4/PcNXWLgew3+certZCxxojASMg5tXsCuQ3/XJRTu1r9O18UA+da/1yT5M7+uOB5dsceXtvyU0wJAKkS0//IWEl3eRsr5x3Hd85
*/