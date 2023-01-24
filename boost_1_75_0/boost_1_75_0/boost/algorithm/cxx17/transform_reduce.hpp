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
tzAlHr7/zHfR3XbW+BfWsRQH65xWBQcqK/oQ87hg8xtGMxRVrV1PV7f7fZ/4LXJbkut5GrDU0SizAV0MSAI8sIqgtH+Hn+RXJarL+mzy2t/xwiAFPJcOFAXxMIJM/YYhQRF2xVg8+rW2eb+Iuj4KMnz7fM4FmVbz6utv7X+fF9y66MxeZ3CLCe16wE/XG2OReQcl0j6HFjA989k+P1fK8x8hyRu8zb9r3xiGfBzJ1emmp7BZP9aKmPyhfiPUM73B1ImdOqrHh0NeE9Cec7vZlgKd0CrOf5YePkViWys0DvSxE/pyXMMyouwZjNBJ/sq70FcmG5tk+bnPupL/AzmL2org8GP9knBq8wdD2EmUkiwhP4WC9GnCgme/0ysOgr4zqC+kyEfRiZDMi67rrdrrOSGebEU35M6bvtiOttrhtUd6DtUwrpvBSfXXby655MVPfbg4KW5s8QzH49wPah8v/qzWyoCkP0TVX7yjdXMi9wjEv9Oc9zTQ0yuJGAqtzEzsSFJaJHxmKwvKNWjvrN1j5ie3PY5mmrsy/AP63vg493Lu263NWRRbD0hIdaHsC0fgFP9gxib+BWHbVUOZokE30lE4mF3qzlW1TRJ1SbSZt5dHVRBzXols2xo1N+ykrMDdBbsqyNFcQxm7Qf1rM2mvObYISUOi1PlvLBHcbS6Vjh+lGxrB8tR677ZNSrMZrRmCHKmClaXu6Avcg1AP
*/