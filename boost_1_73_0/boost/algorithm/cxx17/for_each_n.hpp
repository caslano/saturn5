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
l3IjQcG9wyR/MtZVRXhcWbn8Yb190olHsyzK8E+mCPrZVLlNpsAIn7QpfkQ4dTGhC8/N6OijKaEklrv0ijJ6kyV/USaw6eLdJVUQbYM501HadXdJviEdfxD6Ao5KU65gXvYF25Kl5izWvBP1+fLYqPZ3NHX82vFjNkM4jCdnEldpTXNuPKp/MVH982fdUU0Aqp3fOA+eF8fw7GHi2XmFIJkAJDvHCIaBkcTOI9jlxbCbSewu
*/