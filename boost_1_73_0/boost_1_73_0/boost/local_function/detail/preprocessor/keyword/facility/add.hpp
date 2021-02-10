
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_HPP_

#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/logical/compl.hpp>

// `is_front_macro(tokens)` is 1 if `tokens` start w/ `keyword` to add, else 0.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_FRONT( \
        tokens, is_front_macro, keyword) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(is_front_macro(tokens)), keyword) tokens

// `is_back_macro(tokens)` is 1 if `tokens` end with `keyword` to add, else 0.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_ADD_BACK( \
        tokens, is_back_macro, keyword) \
    tokens BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(is_back_macro(tokens)), keyword)

#endif // #include guard


/* add.hpp
bW/iRhD+7l8xTaQTQW5IyJdeL63qAkm4Ixhh56JUkVaLd8Hbml3LuyahTf97Z2wgJOJAqm4RrNmdeWb2mZf1sZpqIadw0wu6vTHr3I0HLA7DAeuG0X1/yG68Y9xWWu6RaDW/3/CgCQcHq74MB86Vxqgwf8rE7ZZm7AXqD2o94nzISAteVV7YCRxWeYFGpcJWVi7pmbFDhh7JN/ppkeYjo0dcQTXS7Jh8WahZ6qDROYHzjx9/gh+hfdY+86HLtZIZRE7qiSxmPlyKauW3lD8/n1r5qw/SAc9OV1BxqixYM3VPvJCAz5lKpLZSALcgpE0KNcE/SoNLJUxVJqETjh76w2sfnlKVpASyNCXY1JSZgJQvJBQykWpRY+S8cGCmqI7gQlmHgKVTRp+ibQlOFnNLGGSeZ9YAX3CV8Qka4g5S53L7c6uVlEWG3reESWwrWR//NHXzzUke0Ik5X4LJHTgDpZU+kKQPcyPUlGYkBBfzcpIpm/qv3qApLVqmACuzjLBQT0lbuy0hWtHjkxjk6LFyNFmjLZl6Ss38jSDySCjTstBoCHlAIWGQZh9KLKqiEq5Ovjax4rQi+JuhefVXgNHoDBwFEfSjI5hwq6wP9/34JryL4T4Yj4Nh/ADhFQTDBwL70h92MfQKjRUgn/NC
*/