///////////////////////////////////////////////////////////////////////////////
/// \file as_lvalue.hpp
/// Contains definition the as_lvalue() functions.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007
#define BOOST_PROTO_TRANSFORM_AS_LVALUE_HPP_EAN_12_27_2007

#include <boost/proto/proto_fwd.hpp>

#if defined(_MSC_VER)
# pragma warning(push)
# pragma warning(disable : 4714) // function 'xxx' marked as __forceinline not inlined
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename T>
        BOOST_FORCEINLINE
        T &as_lvalue(T &t)
        {
            return t;
        }

        template<typename T>
        BOOST_FORCEINLINE
        T const &as_lvalue(T const &t)
        {
            return t;
        }
    }
}}

#if defined(_MSC_VER)
# pragma warning(pop)
#endif

#endif

/* as_lvalue.hpp
+hOMK8RpAZ5CKI1K/HoVrydoW+DOKlmuBnwKYRjyA8DRKlmXceD51ZIvApYpznhJDZ4PxF8CvLZGllvMMoTnoxJX1xroFfBSYAJhDDwJfKtWxj8BNG+XnLFEcSuwTnFGr+IacHS7bENGqpNyxiWKM+6sk3bWAz9U/BRw9z0oMyoxeY+UM/6L4seBF94ruQl47b2qXsDjCIt60KbAxX8q5VcD/TtgO+QaMLVDjU/gScX5nHjxTpknn9HerTifC/9XxU8BV+2S8a1AOwLP54ya4vuAJfXIC2WNAj+qlzZkgQUNWIsgNwGTjRjj4Hxuu9Cl6gKsUbweyOfwOU/GC9xyfFqAf4ZwDGnZl+Ipt8z/APA0wijXHdjRJONHgb0INi4L+BLLwdmJ8TOEONLyNzf4qzHMGesVZ9yjOGNMccZ/VJzxtOKM7AfKnHGF4uxTu0txxoMIH8M2/szIJwi7sQ9k/0r+zAfHYXzAI+Xstf8PSs5YeJ9My18ZYL90ljNuVpzxURWHMa7kjPxdheqIxGvvl5y/S/AkwpvYH/K3AH6pOCP743NaRvb/ZjkjO15z/ozs2sz5MLIfKnNGr+KMg4ozsrMm58nIjo0sZ1yvOCP7q3D+jOx3wvEZ9yvO2Kc4I/uDZKISP0YoZL8Jv4EuR3genL8BttYvx8l6YAuC66DEfYozZhRnPK74/42rQPz+YsFrHfuB2PLOG8tL+j/Y
*/