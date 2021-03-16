/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  for_each_n.hpp
/// \brief Apply a functor to the elements of a sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_FOR_EACH_N_HPP
#define BOOST_ALGORITHM_FOR_EACH_N_HPP

#include <utility>      // for std::pair

#include <boost/config.hpp>

namespace boost { namespace algorithm {

/// \fn for_each_n(InputIterator first, Size n, Function f);
/// \return first + n
///
/// \param first    The start of the first range.
/// \param n        One past the end of the first range.
/// \param f        A functor to apply to the elements of the sequence
/// \note           If f returns a result, the result is ignored.
template<class InputIterator, class Size, class Function>
InputIterator for_each_n(InputIterator first, Size n, Function f)
{
    for ( ; n > 0; --n, ++first )
        f(*first);

    return first;
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_FOR_EACH_N_HPP

/* for_each_n.hpp
AFr3L0/bf2+aK8A6bVRPLUCuo4cbjk21W7GTmIqm16777RWR1rC1mwYGZOFRqRU+b6yXzSN8gG/7zdOuig2CrFEUnkLl/EneAYN5rfgC6yylgTlANUfL3nYaIGqo8BH+zxDayA2o2nbzyilG7xwId928owC+UIFRHp92M5vrWYqCzRAOtiKs2ObbS75fndtEVdzgmilKIAv2zRjYikCJRwThc3e1Dz9Z2BAVgrimQQ4K9x5QZhjZ6Ms6M+PmcgA=
*/