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
NAJa00XhAhqwMBkOoX+bTEiQf84OZZEJJKVWEFIro/Bwh0uaC2+G/0SxPO/k6zzI4TNQSwMECgAAAAgALWdKUvQYlxoOBQAAaA0AACwACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF9tdWx0aV9zZXRvcHQuM1VUBQABtkgkYK1WUW/bNhB+16+4eQ9tBlVumg5bt6KY4qi1UEc2JKWdBwMCLVERV1oURCqugf74HikpTmK5yUMdxLJ4d993dzze0VmN4Lef9rEcDQePfhLzn+AHn73Rohb/01QNGyTJN2j/0HCFzydQjWFv9S05gSdZfYPnxirpuN7q30nyBLqVdlJ/jbXxKtE/caW17OwnotrV7LpQ8HxyAqdv3vwJL+DVy1enNlyQklEOkaLlmtbXNrzNzMo/Bfn61ZH0nQ1UAeHOPcC4YBKkyNWW1BTwN2cpLSXNgEjIqExrtsYXVoIqKOSMU5jMF0s/+GDDtmBp0eHsRAOyEA3PoCA3FGqaUnbTwlSkViByRED8jEmFmI1ionSQnoKi9UZ2MNoJwqUAckMYJ2ukIwoKpSr513icNjXHSMaZSOU47VPhFGrzIKolerMhOxCVAiWgkdQGrW/DRmQs109MES5WzZozWdh7t5CwzMaiBkk5
*/