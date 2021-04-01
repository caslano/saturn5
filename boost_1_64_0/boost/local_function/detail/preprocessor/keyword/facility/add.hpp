
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
ovzAAhrje6XZzLNvxNgxV0BOa84vqPJ/Z2RStQhtxpXdTBVLQFe2IBHfAevNxIUFhUf34V8wOztclcZAaUh9CNUjTNJO9/+JGAsHbwbqBb5h9N48OR6pR1naO+feWhj6kImyfCbSO9OcSBg7p/B8+P1dDWupsTt/3mKtjN4fl4QQx9JPLlP+xqzTGTzjl4ZJmve5Y1448FJz9QbvbYRkG56XS479HYkEMPnNpcuodKypwDYPRf/KYbbCkZiKqUvt8S+LHTcY9Xu+CZ84PG+/M5nthSd06fc3/WA/kRi5s5BwxiSv3Ke5BUEIfA0x96S1P51P0ePlvKqApzvJKrNd4wcj+FaeLwTEwU9mzE+Mwap1ONKgUfsOG35Wv9Elh5QtweqUJSWfwQHjn3QBDXdYSeAZ2zxJbPWe66Q8cs4Ca2QXQLRx8m2PsBaj+kN6tJdmXrGQmU4zp74/putD2lbwavw40Is6fJh97kiLLmSlE47q2gvldo9Pv2YKw1sgdNL+zdhD4D2W1WtsL0xXByJkRwNcezZGS0sgeJsHdB75gvdUTyj3ySnX4UL2xg==
*/