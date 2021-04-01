//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EQUAL_HPP
#define BOOST_COMPUTE_ALGORITHM_EQUAL_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/mismatch.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the range [\p first1, \p last1) and the range
/// beginning at \p first2 are equal.
///
/// Space complexity: \Omega(1)
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,
                  InputIterator1 last1,
                  InputIterator2 first2,
                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    return ::boost::compute::mismatch(first1,
                                      last1,
                                      first2,
                                      queue).first == last1;
}

/// \overload
template<class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1,
                  InputIterator1 last1,
                  InputIterator2 first2,
                  InputIterator2 last2,
                  command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    if(std::distance(first1, last1) != std::distance(first2, last2)){
        return false;
    }

    return ::boost::compute::equal(first1, last1, first2, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EQUAL_HPP

/* equal.hpp
/6NjV2fUiG7M91Dr6X+rZRup60qwQi6QxbMf4h881c0fYfj9go0fWKPKTdCCq+B2NySYvPIrVTUC2FBMv6/8zRBEtl5mZHtVQpNcOny2js4mtyiHOO3R1OTbyhCsk4UcOUfix6ZI9FRiZcSdaMzmvBVuh70ZsmIzramxVIzRrTvVdLhDecAy/XHS/c2ACpqwveVPvIyZZrCh7Ws3enJOucvLl7Y4WbLVVduk2tnlKleufKNKMPvJ+spY4WPbsLSHhx4lMefaAqOYym8JynLzurYdYFv+YRR29XuoqaBxXkSQ36dy9LDxcFfVMlhTaBB/H+K67w4iTXm+n480JngkNR3Kw6qaPDyt2fPxojIkfsAjHij4C73BX+/iwcP7q/ryBZlYfdlosqGzjj46AmXOjBnZkVdYocq2t5cZdI6gcZiIE1DzwfIdG7T/DeLaCndhqozfduekUF7hSmCltsgY9LW2R25K2IUq4StA04aKv6eB44gdkmjIgb3Rbt3gVcXxvaGXNkHfSLavLRoMETayj4igeTm2XZVBX54I32YiyQfKU4UP32So7NJJ9w==
*/