//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP

#include <iterator>

#include <boost/compute/algorithm/sort_by_key.hpp>
#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class Iterator, class Transform, class Compare>
inline void sort_by_transform(Iterator first,
                              Iterator last,
                              Transform transform,
                              Compare compare,
                              command_queue &queue = system::default_queue())
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    typedef typename boost::compute::result_of<Transform(value_type)>::type key_type;

    size_t n = detail::iterator_range_size(first, last);
    if(n < 2){
        return;
    }

    const context &context = queue.get_context();

    ::boost::compute::vector<key_type> keys(n, context);

    ::boost::compute::transform(
        first,
        last,
        keys.begin(),
        transform,
        queue
    );

    ::boost::compute::sort_by_key(
        keys.begin(),
        keys.end(),
        first,
        compare,
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_SORT_BY_TRANSFORM_HPP

/* sort_by_transform.hpp
4B+R9giOw1Wkn1utcmwtyWDhRmUt0mC0eqLFFGKKDdz6N/j19ozBfzNzu+8THJEvrT3YP5N81xl34nJVJADAZqu50K7gbTaLvrBvb8wwiGCZ8eR4hPdaGUx3gYjJQ7pnqYUno8qFfejD3kWVnrXofTka5PCHAn898pZqoAPo8eNTiJHX4viHKXCychGJdo8JbOpOdjs2HIgbiHMJf+HNp43dDt3xbLiZuPurKaMtdB8zbO7BiFoL0RYYXBI3Y+KSSQLZLxbuYMRvEbiylmHKiUremDY29lk6aLUQERP1o2+TGbQxztMfI5mXka2NApkgiXSb+Z8Etmtg1EW3nXe+brVH+8kl9PThtR3A2oIJZokq+h/nT5ZB5ev8OOe3nx3V9K72Ut0M2NbAralaZjkxGFsL2PXNRE8Q6BYEFINLA1c/mrzCFGHVZu50Rl5EGyl2LUZrTxOustcSCUSg4aKW6t4Q/NAM9vEKW06Da1TapcpbDdchW4avUcceMn+QNaEo4vwhWb9PZYNesNW3gq7nlq+Fp8iiA87UKxc8sWPAgYHDf8AKOBjNt6KZdQ==
*/