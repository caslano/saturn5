
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: pp-list of result types (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_RETURNS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_RETURNS, decl_traits)

#endif // #include guard


/* decl_returns.hpp
JJb/FZiI9p0AA8OCS1gvfMV9l/1QGIlEAgaJ8izvy4BytQGqQEERPY/UoAF8K8KcAbRyqBkE0ZAXQvY3byfh+1Crf8K0LS/LN9geYFUa5MR2+3shnIM9YpiApDCcr8QCippwkKLdZmG5bYIqYvDgwr50CDccs47EMhcjc2EHoAeNQt6FBVFKQ38Ee95/8TnpzduzuUd7tvXWnmwkodd1p7SjBNzHctju++UvlF1KQXR72s+s
*/