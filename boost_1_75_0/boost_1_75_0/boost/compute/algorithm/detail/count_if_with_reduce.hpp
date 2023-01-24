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
e0o7Us2m/eeH04XnBsfSl5Sdk7L/mVCl3no9Urxgar3HYEza34neKuM309EiJQQ0za6L227vtqL91gvibtwvhxDzKPkBMx1rfboBbbjojiPWp8E1c8kR4T6yVxMZCrw0N8UQvIEv/7P440pAOX94RZM/vLhRT6bgDRc0+Ljt3o1syUei9mgWxsQ9hMgTeom+aKB8zg/RtfJKf9yL8tNM3wsDne7DGhbx5AxZEs/OQBwPbZotpMvZCeeEg2Yp4LgeVymYJiKh63+9kf8AetsNjumrVBNcJk8iNy/eo4csyCu5aZR5/wKReDON+Z4xp+UDotwU+sbIYwDxguIE8eI5dhG4D/8ZG2o3YsVqd+aCeoORFZSEHwv96G/WW/7QR4cQGxYqMilWRnsU091GPzScX2MsnxT923k2RqMAyF7n0dKFLW88n5ZYuFLNOp+WqFJmAW4s78c0HtRy794YOQLqZPRHJsGBehDYtCsN3si0A8SvYXFCf6TgUyxYqFWhgQvWclhofioQvDxoELBQGGS4IBXYsCsNmLEiBX4wzkvC7THiXfp6YWxPxPbDDFbnFUWAzxvNep1XqtaDWRqCefWeA4Z6D9ZPxHQzB7zhSet9EX+TL+L5VIrMOIoegzpIi0tWNRmC5nqTUR1fsuqAAb0Hb280UJUVf6NS35cQHDjtOY2YJCniOSrP+JQ6wEyuVYiXvWJ4CaiaZtRrY96x
*/