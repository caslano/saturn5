//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) that equals \p value.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline InputIterator find(InputIterator first,
                          InputIterator last,
                          const T &value,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::find_if(
                   first,
                   last,
                   _1 == value,
                   queue
               );
    }
    else {
        return ::boost::compute::find_if(
                   first,
                   last,
                   all(_1 == value),
                   queue
               );
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_HPP

/* find.hpp
xTRmoYAXleAsPQj+Azt9dge2nslSyAURCS+5SQpWwHvwz/vwgNW76Pd/8cEXfGEN4dfw/CLs7y08kLImwvfC6R0Mo4db7yTeO/jkVmDrZnc4wbITq0FY48FRDoVUG6BEiAWhX7TDnD4NR+NpPPXCa/iZl1TUKYMri9EoMf/ohWVmd/3B4+SeStw+lUJHyHIJPmSCLHXg7Bu7AsNJmmyjgl/s72aKsb29bH9PsWNXtb+Nekjram/3ICw99qXgd39veLy5nQ4m8XgWj4aeE1pWl7ThSaovGvVBqBEb29bzLD4+bed9d56NG0plia2Uptw6XwI3no261k7cpEJp0YZ/7ASNg+mVerugWCUIZc5WWl2uuWa2je0kwjYpifDakm3z06HnxZmbQ7Ytas2R823JM4UtWdTC8EpYVKQvdRrfGqzxPIuaC9PkjiG9xgojYj9IscLewGniEs5ZMw1fCXzNAWNoA4ttCNAkY27InUBDbglOlqJASBs6fcWXwEo3+jp2wODo1bKw0TRz7HkpywiepYvrsGaAxUZ9YU1qHGmOAEQoyBf3rE5luZ+d50VC7IyIWtYFK83uKLY4CLjCjkl3aqikK4RuTlcpaaTZVJhgJpthtsTpX+5V1cEVxFDHrmaXXhiPwV9JRD07aoSO
*/