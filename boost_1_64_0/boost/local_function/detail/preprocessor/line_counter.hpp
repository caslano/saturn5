
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER_HPP_

#include <boost/config.hpp>

// PUBLIC //

// MSVC has problems expanding __LINE__ so use (the non standard) __COUNTER__.
#ifdef BOOST_MSVC
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER __COUNTER__
#else
#   define BOOST_LOCAL_FUNCTION_DETAIL_PP_LINE_COUNTER __LINE__
#endif

#endif // #include guard


/* line_counter.hpp
m7RqQmOaKsX61UMyEOxaxRQnkt6MRVrylU2b6GX9oAoll6ofRig5VNruQrbc1gpgSVYdnjaP+WOvHfRc2oE6RxxULraqyxFv6eSIw8goEg4/VFJRlSIkzntA4COFiNn8cGYpfGW3pRiXWcVl9Yb+XqIPM4ZpGkDXUFTp0ghXwQtUA1tY2T+wPdFWyG725kmVBfzghLGkR57f1AZWKQn4lzDWlTUUkPZIFcN8pNbcTjEHTTt5XMWrj7nTpp11MMUeQc8SRghEBBA6aRXgiepY5a5ogA1wWXpgZ/0QhQDBphOxyjt7g3SsyclVF08fYjv3RIxRosZJVMOVkgPnn0S91T79e/CoWHkRV7KIn9xNYDdvuUTF7ZfE5WK5Vyq1Afc2Rhumn2qVyvKhmUd9Vyt1WydU8gWIjc0DUKIAcJjBGALx37D8ifAof0tlAzxNpMTfb1AXmDgUL+T0q8ACXfTw23sroNa+LYM+L7U7n/K4R6XwofXJuS9XmHAmwNlnwocFM1i0rnPugheoi2akbigxgP5I7MJkcRZOG2lA8flzUSjBke7KwF729QqvVw==
*/