/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::false_type
#include <boost/callable_traits/detail/unguarded/pmf_4.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT

#ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#define BOOST_CLBL_TRTS_NOEXCEPT_SPEC noexcept
#define BOOST_CLBL_TRTS_IS_NOEXCEPT std::true_type
#include <boost/callable_traits/detail/unguarded/pmf_4.hpp>
#undef BOOST_CLBL_TRTS_NOEXCEPT_SPEC
#undef BOOST_CLBL_TRTS_IS_NOEXCEPT
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
/* pmf_3.hpp
uN96VJvkv3b7hO7GrCOrmOthN+AW94aNes10+CjWEofoa4TvVwS7QViRl7JeoL6hwcxzibVDBSQ76FJiirXYC4K4UJ4rdoQLuJUij/fcdtGVWuL96YSzJT7Uqz6ltKz3O5JnS5ub/g0CZbHwFKZhzey6VXmgTIWAIbL8iCco0gP8uvz/gxB9CXdi7oX3J3xlxORjpIMfiDhUgBX0+adLFsJLh/505oV6rr4CuYdlNo2/ri1CAufh+qyHFhT5V3H06UuiEz/7SAPyUsc8pkSwF7HcFT8s+NWoP/tL3agoFnIjIJ+UkKccZtX6+EI8k2Jl3jFQmyJZ7UQHI1YqHEkBEa6BJ6RTY3OYIVPXgjRCHlpAXjJL1+JAAvv0sPeXOcCc8UsCY+QfOkvVaeYn145lMUTD3Ww+QAfXd1akhzf2ppj8RGff/LQQFmNVnFY6rMg8nqiWhlDuq+PytYqByR29kHL3Ty/aaLsIhIa+aSzmN8I8dnokvJRKk9T8C+HnejgFgJIo0XpamPhmrQ+LQI59TCARVpjS4JtSXLsL3s8SGYe4JmoIVOaLHY224g==
*/