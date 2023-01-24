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
0fIzzHjdVubjXDNQ+uiTRCYZxZyye5hEdRFvC1KadMbxvARLOpyP35Vy6gxlZ8/3YV4WzZqXBQnN+mrFoCvMy6KU1YiPnSsuUuc6wQ8Wk8IltRDrG8NlCffqyp88JhyRKYPdcNp1GHEDbikip3MD5teIxIqoIxJUz+UCbPWXc3DagWb3hB6nx8Sfsvo+n8N4XOhonE8eh8N5L58JD1jYmnLOV7dBcsX6dLDVkqTar7pb3+/LHIbF+zBbvFkBWrxDF9KcD7lLW7yLvtUXb/Nd+uI9PAuTBk5sVab30pShFiYUoEN0pR8P0cbTdIjO8kmLSlFMcath3LdoCuic652BM1AqB1r9bUA7Qn3nVNUojtADrXOY4T7CBfM0p7dp/6ylzRXNqJGetKSdCW6VLpIEpPHcESbYWyMYXUwiUWlzB5NQ7vOBDMFfO5hz9nX8wSf8mjKYXT8YSOU7DTbGgNLPeCCVrbGndDQq0nkvF8DZcpRPT2MOx0k4PRKbnqcW0PT85KfpWTlLA1TDv9n0ZKr2SQVmDdPcNFNjXGRODa0uNJLj5Eebq81Ww3ycreua2WyJMFvIlNwqdjRbfSOzdY9f68RLrZhEl2ZL5LPVbJwt9W5m5r1PwGwAL8/SF2JLtmGkz7KR/nk+jXQwG+kfZ2qNfPe1PtK5s/SR5s3Akw4WYq8UgbGhC7Ww6p0B8ZRq4iR9KImqveRu3FQvreFr
*/