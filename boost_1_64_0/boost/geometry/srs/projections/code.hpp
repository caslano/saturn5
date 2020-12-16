// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_CODE_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CODE_HPP


#include <algorithm>

#include <boost/geometry/srs/projections/dpar.hpp>


namespace boost { namespace geometry { namespace projections
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

    struct code_element
    {
        int code;
        srs::dpar::parameters<> parameters;
    };

    struct code_element_less
    {
        inline bool operator()(code_element const& l, code_element const& r) const
        {
            return l.code < r.code;
        }
    };

    template<typename RandIt>
    inline RandIt binary_find_code_element(RandIt first, RandIt last, int code)
    {
        code_element_less comp;
        code_element value;
        value.code = code;
        first = std::lower_bound(first, last, value, comp);
        return first != last && !comp(value, *first) ? first : last;
    }

}
#endif // DOXYGEN_NO_DETAIL


}}} // namespace boost::geometry::projections

#endif

/* code.hpp
xC7NOemK7i1ilyx+mfkTxC7NWco5vBXOa8mWHzx5FT1fld4fmNkbRi5B7JLduK3/B7GT8X203ulfrsLGSubctIsL4iPjPX92tW8XPA+S8fqljmu/HOeSZH7vTBwRHxmPz7udX3vEV019vjzZmHcZ4pNsTuSSe4iPjM/5Y7OXHfatNK50p2E3UFvJ/vL/gbpHkfH6+b+fh3MigYznLKr2xtk4d8lKMOsw9NUI9G51dV6G9nHbgXOJjM9Z2C/1J/YmGV/Li4grM7E3heGZ76An6kdmx/v64tRTqB9ZMWb7ry6dhfpJZu9qeRb1I3Nk9nHNgMOIr4b6esUGTxqO+pHxObsMGFoD9ZPs58Ivo7E3yfj1ingvN8UzA5k1s7EPYjJRPzJe23rPQhJQP8k6pj42vq+Q8V7q92qW8dytqb5e31mr5yB2Mj6n8/G2R1BbyXxjT3/B8xIZv96E/ZteI3ayksyqFFkQgHuqZMPKOw/B2UNWnFnbNyHpiE+yQvfv38H+q6XO9RyTzqtRP8luV/mC3vUj4/X78nH7C8QgWdRp02TUT7K/bxT+gWc+yX6kxiTimY+Mx7C/5vUz6E/J3uSf9FmYwVMdg6vyA8/lPmQOzNz6mU3G/iMrxq3/eBvsP2lcuaE3nmL/kZVmVuLj3SLic8wEZlZKXmV7D/Pccz6vkkG2OM/v9/5C9O9jAsorwsy98Dlfjnmf+HBQmJ5Mx2zpvlvPhbmSmeWYR46NLpNxUpgHWQE2LmF32B5hPpK9y4z2FuYnrWWGZVUvYQH0T/nY9Rxrf7UVFiSN+zo9cpuwkdK4Bp/rbxEWSmbHxsXdvG0nLILMipn//c1lhEWRWTN7NmTfR2HxZLbM7q8eFyAsmawgs67z/j1eWDpZUT6uUv83qJG3ug5RR7YMRI3IeOzPy947hhqR8evtOvloujBPsvwsLz9spviiRmQ2bNzCxMBTwjqTufB+GWfI3UfDgsPI7HM/i7VW+tS5+O27jbBIb5xZOXa3anQ9YfHZczIr0e3lbGEZZAWY1fdtphem1FNbbHg+f2HW9RBfjiWWvFVBmJ4sL7OFVxuPE2YgK8Lm9Cplt12YD5kVs4Fn1nXD14HI3HMtO+i7aW/GCltMluSQs/9ybM6VZ+uFxXbGZ5U59rlFan5h8WTWbM4B899dFZZMZs/MOTChnrAMsnxszuRhk82FZUrW0KpYQWFKF7VZvbWzEGZOlpeZzaNqbYTpyMyY1W20OVSYvWQFLGZVEuYkXe97/NROwlwku9MmorMwDzJzFnunpp6BwnzILJkVnlBzGGokjatzbGumsADpeqsb3HkirA9Zfma2dY9+FzZYGjduzJWGwkZK9qKQL3I2kcyUmX3boq+EhUrXe7n30w9hYVI+kx6++Ik+k8ZNjXC9LixCWstYf1dbYZFSXrautTgqLFqy9pvTFqN3peuN1JfqKuyMdL26XQZECUuUYi/h+/WpsCTJ2kW9fy7shnQ9l2726M8Uyextam0VliqtxWFIAPbKa+l6M8qvTROWIdlfD9cMFvZJul7VIjOXCsuSxs20GH9ImNJVbefM6uqEmZLxdYa29HAQppPGNTP7gHxaS3YyMgo9YS/N6X1mywNhTpLVS/auIsyFjMeX9bFvP2HuZGY89ufTsP+qS5bQ8Dh6yUuyirfOVBPWWIohdfKwM8J8pXEBVZd+FOYnWYHNGROFdSbjvXtreRWcS0FkOmaNV8X3FzZWso0Fj7wVFkZmwcwmfc6/hUVI5nup41lhm6T4mvdPiRUWJdVhfpnCK4RFS+OC87RvLeyAFLvvx7c3hMWT8XMw6LL9F2GJ0rgv8+v2FXZDsoZFB2D/pUg2Ot/W+cI=
*/