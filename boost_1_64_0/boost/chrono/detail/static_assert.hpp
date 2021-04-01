//  static_assert.hpp  --------------------------------------------------------------//

//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt


#ifndef BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP
#define BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP

#include <boost/chrono/config.hpp>

#ifndef BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) static_assert(CND,MSG)
#elif defined(BOOST_CHRONO_USES_STATIC_ASSERT)
#include <boost/static_assert.hpp>
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) BOOST_STATIC_ASSERT(CND)
#elif defined(BOOST_CHRONO_USES_MPL_ASSERT)
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES)                                 \
    BOOST_MPL_ASSERT_MSG(boost::mpl::bool_< (CND) >::type::value, MSG, TYPES)
#else
//~ #elif defined(BOOST_CHRONO_USES_ARRAY_ASSERT)
#define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES) static char BOOST_JOIN(boost_chrono_test_,__LINE__)[(CND)?1:-1]
//~ #define BOOST_CHRONO_STATIC_ASSERT(CND, MSG, TYPES)
#endif

#endif // BOOST_CHRONO_DETAIL_STATIC_ASSERT_HPP

/* static_assert.hpp
84NunlgdEd6kd/LU2OPwX6ykr7MQUUe2g4GojSXCP8x9vLU0kzMumVQY7QO0iBiUWZMq7uvdRakBohJlq++1H9H/juyJjiJ1gFtBQDLrJz5IUNkib+aToJz6B7MmVxzSjgLado7sD/EUHM8sCoHT7ErhPAEi+C4itLwmUOi69yIf1LIOlqFe8kr9cjpt57d6blXd6p0etf0J2YMvipHR/HpcoHqs6QHQGRn4G+7FJgQqiFDCDlxK8kWNBc76HnLEFoY1iI6WWxDUyy4ZA026fMLCATUX8pzyH3fI8wkGgwH8NnzEe6Kt0JEmLZw/bMg463q/d4S/zzxTGo/3XMh+8LOdkXTxlCyRH0XHTp4i0E09qNKsJL4IRt3uuX9Xr6mO0l9wEi5zP0F1jqaxTqhbJMn5m0UGMAcOi9lrr+DnfViR0JWSYwObXu9c5D56Emnd+oTu/oGqOaZNnEQQ5QkAaHm/tIUgVBUVdY0uJ/jXMonIlMbSx1drUfI+4t99Rdl4qN+hJv36a7eTq6BA7ZvT8uzpJvsAQQwehruRkAyNNiuEYb+sqU1J5GsMvA==
*/