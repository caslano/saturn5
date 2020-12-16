// Boost.Geometry Index
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_EXCEPTION_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_EXCEPTION_HPP

#include <boost/core/no_exceptions_support.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <stdexcept>
#include <boost/throw_exception.hpp>
#else
#include <cstdlib>
#include <boost/geometry/index/detail/assert.hpp>
#endif

namespace boost { namespace geometry { namespace index { namespace detail {

#ifndef BOOST_NO_EXCEPTIONS

inline void throw_runtime_error(const char * str)
{
    BOOST_THROW_EXCEPTION(std::runtime_error(str));
}

inline void throw_logic_error(const char * str)
{
    BOOST_THROW_EXCEPTION(std::logic_error(str));
}

inline void throw_invalid_argument(const char * str)
{
    BOOST_THROW_EXCEPTION(std::invalid_argument(str));
}

inline void throw_length_error(const char * str)
{
    BOOST_THROW_EXCEPTION(std::length_error(str));
}

inline void throw_out_of_range(const char * str)
{
    BOOST_THROW_EXCEPTION(std::out_of_range(str));
}

#else

inline void throw_runtime_error(const char * str)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!"runtime_error thrown", str);
    std::abort();
}

inline void throw_logic_error(const char * str)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!"logic_error thrown", str);
    std::abort();
}

inline void throw_invalid_argument(const char * str)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!"invalid_argument thrown", str);
    std::abort();
}

inline void throw_length_error(const char * str)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!"length_error thrown", str);
    std::abort();
}

inline void throw_out_of_range(const char * str)
{
    BOOST_GEOMETRY_INDEX_ASSERT(!"out_of_range thrown", str);
    std::abort();
}

#endif

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_EXCEPTION_HPP

/* exception.hpp
9cxsN5wDN3UOjzHVnP7OGA7LPehF5BhpO+hMm+dcU5KUNsPrmKOE6aifh6qU/rjtfNNv1LEyKUczbHu3sYgcTuX67uIrdXyr0rO0/7aWOaSTONZtmXFsgtfvAE6osFvUc9gaMmdXP3MOaaJ1Dqn4Od7PnEOa7nUOqXWea4199lqOFafJtc7sT5E3Mk65bJmea+pRrqGXWOtsM659lcp/SeEMVWeHjkxMGD4+Ob0437yevO8ctyd6Xa6E8ayLwZG1r4vEh70qPg/7ttjY1wL7HMut9qmZGmJfaZjFPsJ42hcQXnv7iE/s8/xectEAq32fNCW0ti/p4vh+yfl5+a55JBOston/aNWXYnyMvw3vmcW5aW5zsKrZX1UH+ye47NfPepwHN30ez/fnlzpjuVbeM02WZ9ZBki4+KU7jQ+OC5Gmpri+vvDzLXKPCDKFMfSS9ZjwtbJ6Ha24Hns+unu/pkgY6PX7t6xz3+yvszx+7td16arJYbft8IP6jdT/2sNLfZWlvP7fnKIlCX4/NcJGOFnINeVvpo3yjsfJ3rKYZ7/MXvT/y+hXKr+9AViGu9k5D592HKvwh31D+N/wEq1TKs4r0xf1KDT/Eq3RLvNLHLpqZL/GGw4UqzGRGrS9U4wkpuL2nznXUdwhl0gR9fAT1RsYTfgxX40h6LAmhP66eBTlejbV4d9KC1qfsZMii0DkBgbshUzf1Ny6ez45J+pomeW5+S6jHwkmfXOsySJu6/oR7jgfnD5U1iP24TwrbxeJ+l0fdYELELF05bOqG+B+t71/PKX2xn+tbaPVcL+1W/PN8Fa2Puz+lSR9Y+0tQZTQZfYfSc/zu9jnoo9wo23tW4cauHH0ck8w6o+9bLaTOVKlwIX7tWIW4it5/mY9rDMFvtdq3Q30XFS/tVe59um7sUeGT/SY6AvxaKzf2E1lpuGX7BvH91hJGy74ixlCfKT6ue2cmz/POOXu5nOd+ZSf7fiudETalr/fpgt0tdBie+sycZhZkWlaGtA2u+8qGgbSkDrq9XKziaOJ73CdIf/dPLcxj/qR6fDP7DLHK1hLRGcFY7fpWeaXKLzX2oPJgEJorDcY6BcpdXR9d357l6L2dPlA2dFZh2qsBiWnFjGGrMOw/rMb+pnINOjaY9dKNfoA/2/u2DGwYGtbQHOdTx4OHSF8isuRUtb6E9hM3RN5bBi88rL6txF8j/CU3dbbDP0hbNHjIrS22ilTXUXT8QbM9Vtgvvzg0XKW1f/gGjo8jv9Q+YyrPwow9NPqZ+244y1Dtta7a6Ekfz3GNKvSMKBnHkXdVJEjcPOu851i8qr+677JSuakyqvbex1k+uKm8Jv9xI/+l3R9X5a6+X1B6wt363azSW5Emlc+RnuPIXYY7MyKb68H5wguJe9A9+rpgGk8PyON9RUGavoeb/rvoe0aO0i/1+7tvkNs9Q6Y/6HuGGa69CheNnqH0YX6nfcP1uRyyHoZ5XyhRfi70O+wbrfqnRUOd690GEWFowIKTrj6Y9/5a53vVe0r97n+40kM95pIy3qfeje9Adsl9wJALopw8FGmKrn+413z9N+pT+/tc9SnC8/2nylcZM5Sy1/mmyq6T9L92S9nFuPW/umNb6VpVduqdnhrjw41r2kR0Sa/pJ6bWfSjiwA6Jg/r0wFpdvzzW8zh0uTN0gbyXmC5zTyu0Tbyvk8FJj3d2UravKn+TTDsJJ/0+PXaSL/cW81hzfS96XelJqk7sIW/yL5fnkdB4y3OI63vrGp8/7N7JKr2vHlfJV3nSaJ3nc8Ypo2z8vO3F4n0vnGi1Z8yDT9730u/fuKHqVxE7ojoHfzu27nvz2O+J4m3Pm7rvxWK/t0rd98g=
*/