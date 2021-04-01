//  Boost integer/static_min_max.hpp header file  ----------------------------//

//  (C) Copyright Daryle Walker 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_INTEGER_STATIC_MIN_MAX_HPP
#define BOOST_INTEGER_STATIC_MIN_MAX_HPP

#include <boost/integer_fwd.hpp>  // self include

namespace boost
{

//  Compile-time extrema class declarations  ---------------------------------//
//  Get the minimum or maximum of two values, signed or unsigned.

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
struct static_signed_min
{
    BOOST_STATIC_CONSTANT(static_min_max_signed_type, value = (Value1 > Value2) ? Value2 : Value1 );
};

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
struct static_signed_max
{
    BOOST_STATIC_CONSTANT(static_min_max_signed_type, value = (Value1 < Value2) ? Value2 : Value1 );
};

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
struct static_unsigned_min
{
    BOOST_STATIC_CONSTANT(static_min_max_unsigned_type, value
     = (Value1 > Value2) ? Value2 : Value1 );
};

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
struct static_unsigned_max
{
    BOOST_STATIC_CONSTANT(static_min_max_unsigned_type, value
     = (Value1 < Value2) ? Value2 : Value1 );
};


}  // namespace boost


#endif  // BOOST_INTEGER_STATIC_MIN_MAX_HPP

/* static_min_max.hpp
4RzChPDL7NpKmi9979hsFQUPug6KhlPUT64/q+AX8KW80Mujz4UsR21f/uPt+P2Ml5apy6X4z+lnDNkc5c8cjtlh3pX28r7XIbX/kOOj/RokneA3WUulT4Id2YzKrv3QeL62VEsqg2Vmsx9nOXRBujqqVIsNLnfFScF2H9HVqkW6zcCI4c458MBmxxaroNUsEwyDvwJwWNDTeULaUregm9wOLTnZNbclmcMlOh7O5DAbgfmWyuOKUlQ9VUxJSwH6iZvjYP+LRcZj+GDN0MFF9mdaYWEKZOABvu4m2hJ3gB0fdId+7lPGqoAPZXX+nLaHpyT17Zn7Yv9tjgDWJeQtI0V40KTlep0d8Ad8d1OAv6POAVoKNTSy3nWjWm/xZucM4nqPU/YWWYGVn0FZx6WwbDB6dfLxntEzLAhTHWRgSOeM/dne3FSbUlaxtEIh7cQUEdq+9GZmvhZOj0oMbECpxaiEnoGisll2tnSaf5Vv/WsHfwvpv+FRZK6eoT7E3ZJ4kDbxqnUA6Mf35IShkRinflNFxENUhWe+DH3VCvVb8ZnoCHr+TS4MinHEQQ==
*/