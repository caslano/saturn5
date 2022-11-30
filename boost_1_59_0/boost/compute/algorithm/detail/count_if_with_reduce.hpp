//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_REDUCE_HPP

#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/iterator/transform_iterator.hpp>
#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Predicate, class Arg>
struct invoked_countable_predicate
{
    invoked_countable_predicate(Predicate p, Arg a)
        : predicate(p), arg(a)
    {
    }

    Predicate predicate;
    Arg arg;
};

template<class Predicate, class Arg>
inline meta_kernel& operator<<(meta_kernel &kernel,
                               const invoked_countable_predicate<Predicate, Arg> &expr)
{
    return kernel << "(" << expr.predicate(expr.arg) << " ? 1 : 0)";
}

// the countable_predicate wraps Predicate and converts its result from
// bool to ulong so that it can be used with reduce()
template<class Predicate>
struct countable_predicate
{
    typedef ulong_ result_type;

    countable_predicate(Predicate predicate)
        : m_predicate(predicate)
    {
    }

    template<class Arg>
    invoked_countable_predicate<Predicate, Arg> operator()(const Arg &arg) const
    {
        return invoked_countable_predicate<Predicate, Arg>(m_predicate, arg);
    }

    Predicate m_predicate;
};

// counts the number of elements matching predicate using reduce()
template<class InputIterator, class Predicate>
inline size_t count_if_with_reduce(InputIterator first,
                                   InputIterator last,
                                   Predicate predicate,
                                   command_queue &queue)
{
    countable_predicate<Predicate> reduce_predicate(predicate);

    ulong_ count = 0;
    ::boost::compute::reduce(
        ::boost::compute::make_transform_iterator(first, reduce_predicate),
        ::boost::compute::make_transform_iterator(last, reduce_predicate),
        &count,
        ::boost::compute::plus<ulong_>(),
        queue
    );

    return static_cast<size_t>(count);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COUNT_IF_WITH_REDUCE_HPP

/* count_if_with_reduce.hpp
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
*/