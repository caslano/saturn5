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
I/cNLEfN/NLTzD3MKjUx3YC1Sddvta/HSarAxpG+JAzEuqX/qbkQdn+hbTMeUoUa3WtmS/VFeAaZpD5rf4CGgRKcr9TophxHakd7OVA4+CO1hPZGttyoYj+BrSrfTbx48G3PZpsXPVU/3WMh9wA4RBX5du5zrxhWLq3fKlW+JLCL9FYPWYST7lTQtDZf0pYAIPpzmIrryNiswZfj87je183ypA6n11aND+F+baTwuA5MZI5Bet35PIcmzI0U7YfIc1Dbc+NTJlh3XIVY7RGSEcRBWZekk3zLQuYhhNT+S/dkdL/PngXmPOrJEztfUqTLEduJTsy9TFKXNKLXKmpVisBEn/oUwXDIV70+4ReaYe9cn20BHuOgxVrNJntndDyHDPvQXKqMwpRhX4NgWH8CgfCW74FwsYbiIMJtfqySy8xZcxQ1V75akazIo252LvDQWb4Cyg2BCYNK+3HSbxesfPKCOjNOPK9FBYZCPi6nvFld+GhUkiX4Mcg+9ctBRDqpzqxZt1JI8wiuT8iOAbwliUeFtY1FBd0Azbkvpwdh6S1JuvATzHt7tn7K5sgMG+9ylHNxZOsT+5ijkCV2cCb23FOUbgaR4r5MUnCw+kpt3ncszFM768GzA4H9Sydy/QXFQcp0KRJGt3Y743/m
*/