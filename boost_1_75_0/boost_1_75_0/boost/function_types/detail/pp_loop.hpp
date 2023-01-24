
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusions

#ifndef BOOST_FT_DETAIL_PP_LOOP_HPP_INCLUDED
#define BOOST_FT_DETAIL_PP_LOOP_HPP_INCLUDED
#   include <boost/preprocessor/facilities/expand.hpp>
#   include <boost/preprocessor/facilities/empty.hpp>
#   include <boost/preprocessor/punctuation/paren.hpp>
#endif

#include <boost/function_types/detail/encoding/def.hpp>
#include <boost/function_types/detail/encoding/aliases_def.hpp>

#if defined(BOOST_FT_PREPROCESSING_MODE)
#   define BOOST_FT_loop <boost/function_types/detail/pp_cc_loop/master.hpp>
#else
#   define BOOST_FT_loop \
        <boost/function_types/detail/pp_cc_loop/preprocessed.hpp>
#endif

#if defined(BOOST_FT_al_path)

#   define BOOST_FT_cc_file \
        <boost/function_types/detail/pp_variate_loop/preprocessed.hpp>
#   define BOOST_FT_variate_file \
        <boost/function_types/detail/pp_arity_loop.hpp>

#   ifndef BOOST_FT_type_function
#   define BOOST_FT_type_function(cc,name) BOOST_FT_SYNTAX( \
      R BOOST_PP_EMPTY,BOOST_PP_EMPTY,cc,BOOST_PP_EMPTY,name,BOOST_PP_EMPTY)
#   endif
#   ifndef BOOST_FT_type_function_pointer
#   define BOOST_FT_type_function_pointer(cc,name) BOOST_FT_SYNTAX( \
      R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,* BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)
#   endif
#   ifndef BOOST_FT_type_function_reference
#   define BOOST_FT_type_function_reference(cc,name) BOOST_FT_SYNTAX( \
      R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,& BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)
#   endif
#   ifndef BOOST_FT_type_member_function_pointer
#   define BOOST_FT_type_member_function_pointer(cc,name) BOOST_FT_SYNTAX( \
      R BOOST_PP_EMPTY,BOOST_PP_LPAREN,cc,T0::* BOOST_PP_EMPTY,name,BOOST_PP_RPAREN)
#   endif

#   include BOOST_FT_loop

#   undef BOOST_FT_type_function
#   undef BOOST_FT_type_function_pointer
#   undef BOOST_FT_type_function_reference
#   undef BOOST_FT_type_member_function_pointer

#   undef BOOST_FT_variations
#   undef BOOST_FT_variate_file
#   undef BOOST_FT_cc_file
#   undef BOOST_FT_al_path

#elif defined(BOOST_FT_cc_file)

#   include BOOST_FT_loop
#   undef BOOST_FT_cc_file

#else

#   error "argument missing"

#endif

#undef BOOST_FT_loop

#include <boost/function_types/detail/encoding/aliases_undef.hpp>
#include <boost/function_types/detail/encoding/undef.hpp>



/* pp_loop.hpp
FIcKbMW5gEPDBMP3+pG2YqufK0rpYQkLjzUFZQ6skvrq4OxDyU6JMmc6G8jttGNco3AfPhoW7lsA7ttcS67BM8I3RuAiMLrQlu8nR5sCeVqDkN/TVkKe1xaXb8yZDcdeiR/X6H50sexDmFxPoi9Xu8vOQcOPyCbBXL6yIZg/adPAGI8Z2+gYP3ak0THO5DF+LjVojAceaQq821c0BG+zNnKM/0nAMX65fcNj/M6YRsd4y+FGx9jFQ/zS4aaA3LVBkG9MaGifajUm7D6lyMf5h4nupZh0LyVteJ59Olk9BSgbqDw6Sj8CUCh3mCh9GB/iAyparYKTmEoEz+rgqr8TtJRNLTW9caNKYux0z+UN0c3h8XKeBsUTk3eItrR97RveB06Obnw8Ov39345Hi5IGxyMjaDwWHfrvx6PjsobGo79D5X9z0Hj8kojj8V0j++K++xsfj1aH/tvxODG+wfFwB43HvIP//Xi0XNrQePS1y/EQ510cj+3tcDy+bBcUR00aglPK4Zhd9ynho4FSrBrU0NdhaFoYgdyA8539gj8WB7aimyAeUH0nm4woAyyyKwJZ5PcnIYs88DZkkTvghZxjjXP2kdkf3AScufuRUeZ3F293aO7dJLWGUXroQIJNin2lVRrdudKm5NqnT4xG0w97+QP4Y7e9fBK72ldhv5qptLd+585ZoFHjY+Ft0Wi0uijbl1UAWRmdhccDIKeB
*/