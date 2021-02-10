
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_HPP_

#include <boost/preprocessor/tuple/elem.hpp>

// PRIVATE //

// Param 2-tuple `([auto | register] type name, default_value)`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DECL_    0
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DEFAULT_ 1
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_MAX_     2

// PUBLIC //

// Expand: `[auto | register] type_ name_` (parameter declaration).
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DECL(param_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DECL_, param_traits)

// Expand: `default ... EMPTY()` if default value, `EMPTY()` otherwise.
// Leading default is kept because default value might not be alphanumeric
// (e.g., -123) so failing `CAT` for `IS_EMPTY` check.
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DEFAULT(param_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DEFAULT_, \
            param_traits)(/* expand EMPTY */)

#endif // #include guard


/* param.hpp
TDmmIT02KgVHiXlQpubI4/OW0U2arF1RC8e0b46H1WM6vWARcuSmV6Iodlzu5Bw2Z3mQM1/7mxIaZdVodU+Jzn+tMjBRnzidfN4OXmI42oBppidVmHtNVSy/mMz428m78cer2Um0RZjdN+LwRjbRcSKBl/8g8BUZoE9HLsa3dNoVNtucdVIKChfV1RhXOTVMa4dPwaMataHf20rgxdZyqEM2X0d1ZfwODDtc0lM03H3LAqurzWPjORhwSAXG2VbsLPmq6s20QBX7Pv+6DTZz+i9ZYMwLvYMq1D+nLPfP4Zd46CUQqvlWetu5ron5Hp+x77/Hoky6ozpj+f4Hfy/jY87nqQToBJAdW9QMyu3hMK9vZv8HozNiNKX3ZOaY4FfsIlaROqzLrrji/fkbIqIEVbBiKe0RpK0W8zgXIlzsqEHllmhaPY5tXhUa5GRmPzu8XnS7fX7/YwHpF72qSPUC5nXgZEKXS1FlVGVL2BRih1Ed1uc28d7LgY6s65P0aacDDxn7G8+HL7BElGk3p/8pGKOMGMJyaOsRp3B7DQFC8rRcFwN5JsVwvNODYZ+OQMWmzT0jKhyJNuc5+emaYpaA1UIBGijxb9WBbxDjAq+1kOqVO0QA81oX/2pqreokfTOuR0pO7fbu5v3dZDrl
*/