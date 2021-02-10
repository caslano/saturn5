//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_GLOBAL_SUITES_HPP
#define BOOST_BEAST_UNIT_TEST_GLOBAL_SUITES_HPP

#include <boost/beast/_experimental/unit_test/suite_list.hpp>

namespace boost {
namespace beast {
namespace unit_test {

namespace detail {

/// Holds test suites registered during static initialization.
inline
suite_list&
global_suites()
{
    static suite_list s;
    return s;
}

template<class Suite>
struct insert_suite
{
    insert_suite(char const* name, char const* module,
        char const* library, bool manual)
    {
        global_suites().insert<Suite>(
            name, module, library, manual);
    }
};

} // detail

/// Holds test suites registered during static initialization.
inline
suite_list const&
global_suites()
{
    return detail::global_suites();
}

} // unit_test
} // beast
} // boost

#endif

/* global_suites.hpp
IG5E9rryB90gu6D/IM/uwpyZZCfQd7kKSMQcMbqdExzPOfvoXamuCvIzRMzQNdeNbEjWtL1YAZnXhykAq1YviHFNMKKqMXu5xh44JHjq2k7cHUO2iic+rTlGdK+PuWHRMn1zcAY1iHcHhSfu2JgmyPq3bI4vTRgSeFRSJJPVo1mlrFw7k4+xnC4tK8RjmiDjw/HEy8s14uZ0Oy+6V+/eRH+/PT/tvfDK+pP1U6fv22Onst8IadAtyNTKuunXRItnxzRHhkSlMTxohhbeBqchCewDvIhh03iyfl77i1GjphO9hmg9w0sfG4tV2uv4fQBZbXo3GNChDGk8Go0mDSWkrBEf0Li/1e473/OESOZGbiJrHOva9txp7KMTLzV/XYT3jvPM+4vfaqZWozbTqhnda+WK0o9XC96DbS1YPuPuxSXZvbm84s1hqM0v/IfEX/Y9oKPTD8sgplMMLpuihLAaVGhUGyCeYieSycBj/HkS3JTb2GfifhulW9hxv+7xaQk0xTFPenYRJVhLHgIe3Fgo7mrMXcxkv6HcSs7ucBzQlXStog17U5+e7VcaDygIgv6E3FQF3ZzXw1gYJ7wh22dJfdbLe121SGGpUWyGOGxzmktuUdyuWF2rZ+Tl03CI/eQixwBDANDArtBd9cwM
*/