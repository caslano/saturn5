
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/transform.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_APPLY_( \
        d, bind_macro, bind_traits) \
    bind_macro(bind_traits)

// PUBLIC //

// Expand: pp-list of non-const bind-traits.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BINDS(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_BINDS, decl_traits)

// Expand: pp-list non-const bind-this-traits (size <= 1 after validation).
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_BIND_THIS_TYPES(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_BIND_THIS_TYPES, \
            decl_traits)

#endif // #include guard


/* decl_binds.hpp
9NYL4GOAs0QkVYTIxbpFubLOtumI8mI6mw6TkbjDbsFRwVmMGrJcblmA/itCl3kCfj5fjjqzjJNEFu54EoZZkUlh43mc4X1aIJzB0dqFNMOkbRUSpVuhtxkFmcAjOBG3FvY+mgmUgIPjLb3+BJ3CR45S5+BJTNAQGgN/j3GQy8JuBoCmwVy4goNLJwCtpzDa6XqYnhDBBvYNDqwnVaaDSbAY3x+jHwSHKsrMg9H16cWCu3gfEYG2sf9psJsB9XtsSxLELWk1qS4xBUBbA9cWQRKd5+CIowHazFo80Kq7MwGcLLE9EVAWpeNh50FJQfulaVstyLXQJhKBWohE1pNmOhFZhdCGkDNqeVhIkAzu3Dhw+rbtQZYxzy0Hi5cpzxTkGQPwtv9Jcwux1WwgHQnKl2rHcu3Ihb1mZyf0b/TqhP7FZomkCj00bQpJ66eeCRNusfmaizQ1o+40A5j/eBoTfWKxTZu9ZHqpcg4JHDr6BuwyyxEX19SGFsLarTZpG1obY6y5Dzs+zKcZ63Nrxvbw7G2BoPgIomT0ACfT9/GSclSsmW7vbn7+xC9ms1sQlK+oIhHlumboAWtIjmsrCwGL1N1CTuvCuEkK1yHB9ddWXiNxkYFeLeDR0kkdH+PQMQ4dN0PxgqywntnvKo18
*/