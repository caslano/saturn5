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

template<class InputIterator, class OutputIterator,
         class BinaryOperation, class UnaryOperation, class T>
OutputIterator transform_inclusive_scan(InputIterator first, InputIterator last,
                                        OutputIterator result,
                                        BinaryOperation bOp, UnaryOperation uOp,
                                        T init)
{
    for (; first != last; ++first, (void) ++result) {
        init = bOp(init, uOp(*first));
        *result = init;
        }

    return result;
}

template<class InputIterator, class OutputIterator,
         class BinaryOperation, class UnaryOperation>
OutputIterator transform_inclusive_scan(InputIterator first, InputIterator last,
                                        OutputIterator result,
                                        BinaryOperation bOp, UnaryOperation uOp)
{
    if (first != last) {
        typename std::iterator_traits<InputIterator>::value_type init = uOp(*first);
        *result++ = init;
        if (++first != last)
            return boost::algorithm::transform_inclusive_scan
                                              (first, last, result, bOp, uOp, init);
        }

    return result;
}


}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

/* transform_inclusive_scan.hpp
CpOy3s1O3Qc4L/wAbsxjGxp1wKPszIg+9v7CP7G45M+x/7GbcDxfmywe/mi1gYDGINoGcw6X9LRPoDFv5H2u4Z6CqLZrfjeYZZHIxHEIMjEKEJ0hovsQNmH2OPMXoFnxQ5NBOK7RBttUNAk6AIEaRCJK8nHtfx8xh4ondKVi7kZ/qW+Mh0bbENcwo7L7ObkeORgKnPWoWqFjD8j3oCYoc0D6RW1Tv9d6f2OECHAx5gOycCORLC/QDUn/pw+HJG2zyKBGJUMIHIHWnQNHmhfMRTar836fTLAolyYieCePBDeCVFKIObmLq+IgM9IOs0WVroKSrsrVDBt4N9Eu5qmrdzFTjGZtmwv1gm44WO4W8sCUPjnbLVt0t9xxkOdiwEv/e3iH3SZGINdh1QN/mUw8BbuhPq/c7IiZ638Kbhygq2l2MM5ut+bj6KQeSKUBw71gEV9G9n0z2QSBC0/YEvI0a5oqIb6VE++j6PpjzPm5aY2dzLsJbZyC2F4KBMfSQ3VHjsAQNF6FsWXIijWVhNOtnHVakTZfRRDPVYmLVIG/48IVupwZy19/gXveYA==
*/