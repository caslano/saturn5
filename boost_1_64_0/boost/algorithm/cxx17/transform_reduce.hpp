/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  transform_reduce.hpp
/// \brief Combine the (transformed) elements of a sequence (or two) into a single value.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP
#define BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator1, class InputIterator2, class T,
         class BinaryOperation1, class BinaryOperation2>
T transform_reduce(InputIterator1 first1, InputIterator1 last1,
                   InputIterator2 first2, T init,
                 BinaryOperation1 bOp1, BinaryOperation2 bOp2)
{
    for (; first1 != last1; ++first1, (void) ++first2)
        init = bOp1(init, bOp2(*first1, *first2));
    return init;
}

template<class InputIterator, class T,
         class BinaryOperation, class UnaryOperation>
T transform_reduce(InputIterator first, InputIterator last,
                   T init, BinaryOperation bOp, UnaryOperation uOp)
{
    for (; first != last; ++first)
        init = bOp(init, uOp(*first));
    return init;
}

template<class InputIterator1, class InputIterator2, class T>
T transform_reduce(InputIterator1 first1, InputIterator1 last1,
                   InputIterator2 first2, T init)
{
    return boost::algorithm::transform_reduce(first1, last1, first2, init,
                            std::plus<T>(), std::multiplies<T>());
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

/* transform_reduce.hpp
J6YpSZuzqB6jtRO+MMugSVSPNjw6HkWpOHN3rk8H+KYyFJ21mVHpAhwTnKE74ciZHokHMEsO+w28fHPFlS8TBJ/8EPaGvJa44piAmuK+isTOrvEa7hu1NMpYfv7OKdtiFGlY1e1ajwMIPh/pgR2JWieZckWuROgT7e5JRjMMwL9p3xNV7U0tCZVOGXtv2ovpY6eVKIoTicrcBWdMR2o+zwzJ7680Ewf9pNsSnDGckBIJq4MloDeJgIOeSGj99pA7KY1cT7WAjaTfbxQXZ2/tQtUuszHjk1jJwdBUH8SJz0GC7nVkh3eqfHW4ba0Z3Ods1kPl2yJMqt9PqOl6pbXpDt42xc8xCBc80zwIqkujOhIoNW/UgQTLlG5tLllrp8Lt0z/1gvl6Jw4Q0MWrmmrQsexIDQcmC0BQjlb8AyJ5WW/oW1GNUNDjpuaXg63eXbAh3tnYmECn9DxCkO9QLs5lU40FOq9ekxaYAb6lVP2dVoKs+rWsF4PEZXm3jUdMrhIkLOGobun7GoCmtqCXSgTowvzBBvMDqcOSYjTymLXI3YML60jVGlJF8ef2MQ==
*/