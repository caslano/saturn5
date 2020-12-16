//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_MPL_VECTOR_TO_TUPLE_HPP
#define BOOST_COMPUTE_DETAIL_MPL_VECTOR_TO_TUPLE_HPP

#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/boost_tuple.hpp>
#include <boost/preprocessor/repetition.hpp>

#include <boost/compute/config.hpp>

namespace boost {
namespace compute {
namespace detail {

namespace mpl = boost::mpl;

template<class Vector, size_t N>
struct mpl_vector_to_tuple_impl;

#define BOOST_COMPUTE_PRINT_ELEM(z, n, unused)                                 \
    typename mpl::at_c<Vector, n>::type

#define BOOST_COMPUTE_VEC2TUP(z, n, unused)                                    \
template<class Vector>                                                         \
struct mpl_vector_to_tuple_impl<Vector, n>                                     \
{                                                                              \
    typedef typename                                                           \
        boost::tuple<                                                          \
            BOOST_PP_ENUM(n, BOOST_COMPUTE_PRINT_ELEM, ~)                      \
        > type;                                                                \
};

BOOST_PP_REPEAT_FROM_TO(1, BOOST_COMPUTE_MAX_ARITY, BOOST_COMPUTE_VEC2TUP, ~)

#undef BOOST_COMPUTE_VEC2TUP
#undef BOOST_COMPUTE_PRINT_ELEM

// meta-function which converts a mpl::vector to a boost::tuple
template<class Vector>
struct mpl_vector_to_tuple
{
    typedef typename
        mpl_vector_to_tuple_impl<
            Vector,
            mpl::size<Vector>::value
        >::type type;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_MPL_VECTOR_TO_TUPLE_HPP

/* mpl_vector_to_tuple.hpp
/qZcskuRNsG3zBmHtJiSGBgP+5Q5JvZt58jSYEbqO/okT5spS9/VJ4c0mZIeOkeBDqHvmS8yNJiQ/r57OKRD6AfuYZ8qA6LHYiBDlTHJH1pDlDkm+iN5JEedMYkfi5MDmkxZHqlHgS7BT+SGLYr0ifzUPHNAh9DPxMQeVUYkxtqmQI/Iz9UhR4sFK7+wNilzTOKX6pCnS3jiuU6WJnNWfqUf6sxY+bV5o8qI5G/kiwJ9olP9kqXJnJXfqkONCenfGR9H9In8Xh1ytJizMhMrFUYk/yBPlBgS+6N1zQEdIn8yJ+RoMWNlrg1K9An92fjI0GDK0l/cQ4Vj4n+VE4r0iS6scQ5oEf6bNsjQYErq72KjxJD4P9QhT5cgsDc3+9SZsnwu7wlRZUzq3N7fosSA+Hm8Z0KWGhPiIe/BkKHBglMntEuDEUsnve9DgQ4Lls/rPSeKdAnC3jNimyO6LFg6n/ebKNAldH5xs80RXeYsXcB7R9QYkYx4z4hDuoQvqB671BiRupD3wSjSJXJh7xWxRZ4mY2JRY2KHKseEL+JeslQZELqoMbBFgTYzUhcTCznqjIjF5I09yvQJXVx9tijQZkbqEuqTo86I2CXVZ48yfUJx9dmiQJsZqUupT446I2KXVp89yvQJXUZ9tigwIJEwd5QZs3RZOaTOnLXLyQE1JiQv736KDIkl5Y59jtm4glwTvqL+ydJkzsqVtE2VMamUtjiiT/TK3tfjgDbBVfTPPnWmLF3V2qDMMYm0PinQI3I180aGKjOSV9cPZSbEr2GdU2RIaMl6ZYMqoWuKlUPqjIhfy/uP7FNhROzaxsgeNY6JLTtHlhojYtfRH4fUmbJ2Xet/7zzBrrLOkPj19EGGMgMiK+qyT4PU9c0zc5I3MC6KDAhuqF32qTMlvuq8zxKeUR7QZEr6Rp53FOkSvbG4yVBnSvom1hU5GoyJr4mRfVpMWbup5w4jlm8mJlosWLq5PhgQPmXuKNMnuIX72eGIDnOWb6kN2sxI3cpj8nRZsLauHhWWby3fLIW9JpKnyZz0+fys4JDiZXye8rx+BoX8fPG55ob/HllRDon+5kSwzi41RsSnJ4LT5GgwJvlbn6nkgDpjEr87EdyFHA0mJH/vPg5pMyM9870nCrSYUnvJefyc8VlZ8rSZkfrjieAsBboEfzoRLLFBjjrHZH6hjx/6HBbhH50IziFLgylLP9YORfpER8ZJhgZzln9yItiiwoT0T33nkTpTVn7mMWWGxMfapMQx8TeFgvTPnaPEgKVvu/YNefqmdhix1NcvZbrMOf1556gzJv4F58hyLDdHf7dPwz/s2eDxsfJ0cJ6gyfK5fM6dyBflngJDUl3fceWIIctfOhHs0WDB6pd9ZpAu0a+YD+rMWO25RpPQV12jxIj018zBZ+X408Y0Orfvy9ijiV0OqdJj+RNyRYURKy1rivBvfB/u9cbwOuN+E7fT78u0+2a5r4uXs457yvAHzJfj3ivE8UreYhxskadD8FafAydLlSHRtznHHhWGhCs+x802R/QJv90aIEONKcl3WK/k6RF9p7VEjgZjElXrjwJ9Yu9ynQYT0u8WIyWGxN4jh5RI1NTliAHR94qBfWqMWXqfOCnRI/R+MdKk8ibkbvxSY3yDe14rlywfuYcqQyLuWWOP5YL+2C4gl5vy32ZO+EbnCQ6102RCvGQdkSOm3fKrtFcQk3pFtl/+T5LuPz7u+Q7g+LdtWqle2m/Ta8UW3CYIikPRUhyKojSboihuVAXFsaK22g5BUO0hCLo6BGHBFzUx2XYjIyY4lAbBIQhizlZbR9ietj9ej8t9f3x+vH993p/Pfb+fqGcFuV/rmibnUHk5W0A=
*/