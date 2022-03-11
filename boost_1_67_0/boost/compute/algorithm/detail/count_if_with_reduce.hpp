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