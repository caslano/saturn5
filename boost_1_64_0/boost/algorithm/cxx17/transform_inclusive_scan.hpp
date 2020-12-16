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
kdjh0jTjSvbomOu2R8E0I1K80pM9qLpmww2S5mwroqxNF/eNU0O2VKpvrrUZottJxbMqtqL+BRmmjZ1lLvoGJHPUCHZPGW133560obSMxhU5WLNMOf471TIlOxJG4PaSd5JeQwFnSc5uJ4Zbkv0p3Q2W5HyNmG/OEter+P9N/P+urcRVRfF6U0URREZp+s1P6jQYJqehB09DPqYh251tFStwzq4+aiJrzINiWE+vH9N+pNnd2S9pBjBOd867TPtOd/abTnRnpYEKjHqVZunT0fIuvgkq+cSrWvQqxQMcJGM7NP9DpIHK1Ejv7T/nymSDmvyhTH5VTa5eScmuHgia8jDhcmEGfAnfMap2z5vF0U6yxSS0KJ7sofXb9UB1YxMDusshAT0rATVHAEOzAdDqrqnzuFY73QvM1bNkk/lqybtkyVtRMo5KXn8zSi53lsxNt5XMTRWvJ2lx19Hsn8LIrh4T4Z6XgAB9ayj6NxmGpRvYhZwDy3KsL0thNT70eF811RzKHPowtVGjbHSc1ujo5nUIHtPc4/HoDWf4Nnx9vYbzfRpegu8ywNg8b4CxmtspLoHa2q9eotZktBmtxS4dqMUVZ31a3HC1T4trjf4tPmHUWgwSPI7WPG0DBTUrPBFteby8phlasCQCx25gH/fTBMkKeoON/9yiDYCDSDlhjEhHRcx1ck1zeJmzdzuBfk4l51O7OweAR0n0E2s6ylIdZSmkZm/Npjjwn/HTcDkvodpWuEBZKQITnWKp8DGjxEcK3li6XS7BP3LkpDzCV1w5byLpAJJkbBmiKXG3zHkXOVWcs1PmvCkmyJyviUJ8KYNpkKhCbGaPTgSJQ9BWMQp9bu+xwDL7xO2ufNE0QWK0K56x0tWI18IViQ/MamMVxRvyQMkL4pOq7Cq+gO1lU7JfAniMb6tnl53gd/B42Ez/PR/L5JY5dKv/KG71nxTv4daYGIiikrHClMt3v2OwLoWLqvBdMhdXPzQLfiJONeFL4ETZj1vHSL6ajOL4DZuvfU3Y5uuznIyD+WYqMqEV+X58hRkhin/KSXNVy6ef8frcFnFqHftLjtfndSanHqPUqPEE/z1kRJKNXOUItpEr47hn5F83bkIF+01+mcIjomWlwUscyErHzJRkpdIi0xpUx5+V80L1q7/4N7mg/U/9cbw81cFhVji9/2LTNrNOT+gx83KRQ/6Qe/CJVSR8/Axf5U7OXhAHcuglSLAGUYj9CB/P5Eqh4mqyHx4kt7FwNrR08TY2YLb4pAtYTJGMJRLnLHklaRo1gxDgy4Yw+5qZnlN02LKsEX4oA1NJzCXjCo98QoIBf+WQgK8gwKNd7iEQEwYsEUUEOEkCThDHenCHGlGHFKH16WW1aju9T5AwZotBVJW4P0gqPSG/8dLTGrcs81TY0lNdR8jS8PthIMKyxpbV37Z1h2f1MaDfd8FirJPcm3IBGtL3X/Ah8iEbcOxxWzHkDrLnzBWRjaTb8F8AxaYg4Dz5A++UedcOQWcxUrIGzYUnlnpIK+ofayCabQqJvqYLW0Vm3ShteUmKxPFuG/oAIYhEr2RIQijMjDdiAnOFlrC/IwuohgQkdRSnNbCukQFE5MSvplHITpyMR0wZkqYe5JUnwj48lAmbUES6RCCo4QWdxf8NfxcbH1W1f7R67VEGNAvy/p1P/ucJgfkRPvlzGgWx/8z05h9KDGL/6ZO/clgI9kqpfP7JDJSnH0+SfL9/dz95OsIusX0xC5JTNXl6fGeWp7MhTzu98nQPphQ8zMz4ZCN8qqLfk4ClDhRjxOo/Wpex/zL08srYIZwncnn8/YKM/2p1/Nf7j3+gep5gap+mjz+Fx39nvfHTeEBSz6I=
*/