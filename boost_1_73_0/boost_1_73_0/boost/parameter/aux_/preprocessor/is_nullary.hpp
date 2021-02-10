// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IS_NULLARY_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IS_NULLARY_HPP

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
// From Paul Mensonides
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/detail/split.hpp>
#define BOOST_PARAMETER_IS_NULLARY(x) \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_IS_NULLARY_C x BOOST_PP_COMMA() 0)
/**/
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#define BOOST_PARAMETER_IS_NULLARY_C() \
    ~, 1 BOOST_PP_RPAREN() \
    BOOST_PP_TUPLE_EAT(2) BOOST_PP_LPAREN() ~
/**/
#else
#include <boost/preprocessor/detail/is_nullary.hpp>
#define BOOST_PARAMETER_IS_NULLARY(x) BOOST_PP_IS_NULLARY(x)
/**/
#endif

#endif  // include guard


/* is_nullary.hpp
ixCFQCZLsvSYI35Ruk/Lw6icpRgI0OlXM6xcyhqXnEEzOIrnc97Y3MdXgkLCFFDhyPGrIvdncQrrb44BX4ov5Hbvln7Q0VIPY+ABXMNU1VjrKg/l1YhtwE0lRp4eZXYOvR2ZYzTzWgly2P2WGr93Q4AdRld6mxsB8ZBtWi9Q2hya7397b+fIAp9Q9o6JXkdhC1Oo9vuUBK/WCL/qR6yjL/aaQ0p3iDs2678EqWOaSfMcurFm03+RiIaU2HYsEn/qRLdQhXPqtNdqfdV60lG9adMKefbFldpXsXQKrRy+bc/UoOs6UupPV6b6teZy33l3/KH75p3/9k/+nY5Clq3wrVKWofKD3R5mrSxtbbGXdGwEofEJ2l5KrygmnIlFCuPFx+LFjUFyFpwXjTH0/k19/0/9rMLe9eD6NZC6fHOzTZkrfHN0wt0d9brYr3xscyXouOHZnGN6CeoSWIPbauK+j12HtxRQ7kUJoFwfEQnodZSfe0Sk84yULS7BolaJAH8265afIc9OpnzhmRKVH8i6m3K8VJRUzglReOM4yIpDJZ1vSmgsrRaUjuP9h5NHdApLwtlWeQ57N/d67Cs87oOxKIZf+JNksGPf4rkd2V4v1978WBWvjNcSKneFAlmFSO1j/XXFZke+GPdQHEZd
*/