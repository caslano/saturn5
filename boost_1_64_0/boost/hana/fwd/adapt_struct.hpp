/*!
@file
Documents the `BOOST_HANA_ADAPT_STRUCT` macro.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADAPT_STRUCT_HPP
#define BOOST_HANA_FWD_ADAPT_STRUCT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note:
    // The weird definition as a variable seems to exploit a glitch in Doxygen
    // which makes the macro appear in the related objects of Struct (as we
    // want it to).

    //! Defines a model of `Struct` with the given members.
    //! @ingroup group-Struct
    //!
    //! Using this macro at _global scope_ will define a model of the `Struct`
    //! concept for the given type. This can be used to easily adapt existing
    //! user-defined types in a ad-hoc manner. Unlike the
    //! `BOOST_HANA_DEFINE_STRUCT` macro, this macro does not
    //! require the types of the members to be specified.
    //!
    //! @note
    //! This macro only works if the tag of the user-defined type `T` is `T`
    //! itself. This is the case unless you specifically asked for something
    //! different; see `tag_of`'s documentation.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adapt_struct.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto BOOST_HANA_ADAPT_STRUCT(...) = ;
    #define BOOST_HANA_ADAPT_STRUCT(Name, ...) see documentation
#else
    // defined in <boost/hana/adapt_struct.hpp>
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ADAPT_STRUCT_HPP

/* adapt_struct.hpp
VEtLQlYhvPzuU4T9hsUyFnXGkSjUUB/e7x7AHhwBPwZ7vBvvaQ5IcPvRAqk/UMHyM7/40r6vUt0ub0T87iHxgBUajabr8A8Rtazb3Jbvp5XaupvvP5qhP1cgvh8oqdx4n2i1Th38lE8IB9budxjk/qNSLhjV5Y7xfTIjacRCj+PKd41U2Qc8cg9rCezC+dg4BWOgqSY0P8dIOC+hpzmwP0z4/vwQ96UT+pqrsF0rC+u4QN0K4gxz5cMf49dq8iofJHdvhz2IR70tk9fDTOD5IWV75+J87g0/B9YzF0EdZqYVqpqRpxCT08X5VUn8Q5W4jllh+TAUqxC+bctX8Xc5WbfPYT5QOXt+FPGcuQKPUVO8RuIvwVzvUF7AuwzfJ9/h9zKwIX62ELjE+6HzpvyewkJl/R3xt0cITPumleOcR9gBBM0SavP+hcVVfQ3f1zJMQRN5b0Gk/6mrQAV+aOYOZ2ci4bOp9URcK9hO/S2vVEb271Hwli4EW+gMNs79VxLcvC3nVUPRebPQmxVSdkVjpa4Wwl9M4HUl4X63EfgnscFGH1AXDgTjD7NXKrOUuLjwxHfScb7vGWLEfrMXv2fq9CvKZoaJaRsX4jP4LUyacj7PRz8wEvZTdYEAVLqJRLlzI0YOQm+LnglUN8Uf4cV+m6Xszt3EP8xV9yd+vearHeAn7NQo0VmhBJaYx/dMXNstz2J/DHJEXxNi0kHuI56dny2kMYgj+NwM7+o5FlKhYOQjVOZL8Cp0rxBlqOFJk5vych5k4b8aYsr7NexzPEpjOXyfPCae7MD5h8zn2jJ+efEnluL9FQ+FC79SNr+7UrNNeP/MobWHmEOTrkJ45Ga/vcT+ZRo7gDhpLzDvlZh2zP5e7TDxI2P8u3mJJ7fiPppsx/ckwp5+JC7WN4WNXsh5ahB4vZH3erOVKnqG9xETuS9bqGzrWoFhYcrmm4E9U5z3489FN4GfBtnur9TvIurlup8mko8fMcnBvK3nAIjhNcb1DLXbmiOy2X1lG80Rq/1rVWaJhyqnpcDUC9wf75jfUQK9OSfXcZg3Yd4OvhCo81HA/JyabFiJ+GUB7I9w7MsqfO/yUmKsSRTwBRtfSFgrgvIlXvO+BAYLCfBE2wmcmST267eYiKSMk/q7QNjJacRXISnWRbJU4LvolLo5CIoSj+LMuTxQqQu7Rfw7L/4Nrpgj78TKhWOzXH7VmHuc+b0uYMvdszMUf8RBpaaEEv9din9thWrUH8D3xHSmsxH+WIYzlu1yi+7nwJU9ZL/AZyLffTlPg4KVDZ6nHt1IQX9xVLb7bMlShc9jp+ZEf1mpbPgEdStgbw78u7zf2Mp5epz3epyTSXwZ5oXKPhlb6MtZ/GtOpnwfKjEiiF43jpR88YDLd8S0/2rs1eGsvyilxnhyv/GmzStA3X/prGrLXZSaTLTUdbFYHTblvS0brOYw7OlcFvBTtgWeNk9+58RhGevFRhMf4oL9tkxlBYiqJjGhI6E76Y9+xWdzTigxPlzRlg/5nqSRUqeyz5cA9HGwARxz92joBbPwzkjV9o7hvrzKe2AMnTe/lbo9mPh0N2P1dyXxZMLLOdFkCjfDv0ZXL/DTKu0ei0FtrKIuBEoNviq7z5Frvov3L07Ey3KIlUWwOfq96NqwNebTbvGdYjW1kM1ffu/rJtN9bYo643yL/i5Rqj2X3CSeJb/sjr+ErK21sPOIRrqz6aKGq6uDqDaLu9Yezt/2cf9acV9iN+6ZLs65d3EelFZZZB6BpEM5+D7FRPuNi/4YH5kZE5r+2VzZlL4Cs/aznsn6N+P828h5H85gE8Gaw1J2Oalsq60CpTjXnjDddTsKvGpAfDWXgB0/Xfc=
*/