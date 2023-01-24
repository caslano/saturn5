
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
a/yIgUkBIQCVfIQbxqFGiBDVy5sUNYpDoH7nETQfMB/E7e8tSiKWKZobxB3U9cYWzrbomjWQgkEwShKzBneLCiCfq+9ATnx6Xjh+4n7Fwb/ak6Vn43Mq+md+uJPvwQ0j4VqJ0xBDbNxDvEwwn1Z6WY6S4CzuEwcZVchV1MGV4gDqhuz8qQe/B63tw+EP4OWK3HNWrv5z/Tanop+jne5vwylUuWJ9tz8zgDjhQwJ8fR+vkZTmVfyuk/vRDzONF4Tm+Lq5nDIwLA35R/tOjh1IRoPTFFmJyPZVotsWVwpU+5gAOQt2VTz6sCtQGkSX/1zIOrKdZfcYzOSGM+1X4DrlDEiBRo+tv/8sbCkDUynxQCUDp3uMfogVfSwUwsnNsXvsPyY3iZXhimvz8kdruO/e9WHPfKHOOIAVvhd59+M5V8f4FJbyBNVrmemAdibPZMwjjTg3BwHOD4ZjoNVI44geAVmizmIYAWCElw87aI8MFgIHyJixaH6EXyggOKDEE74/NYtP5uJjVJsiiHz++EGCYiJGNT5pUG9M8DXw8lMluXkj5heMnQ9Vt8jc40OvAvYzupa4Uhi9oM/EcFon0DC95yPZZwQx33tEvjx/enow5j5PcQcjCfUM7vcY6pFS6zmta9s8Y0w/+GAuC6lxE7TJY/QshjKkIpFQIH+67ED3TB0Py/i5jXZ77cy9rlS765HMyqamwfVE1OsLzem8
*/