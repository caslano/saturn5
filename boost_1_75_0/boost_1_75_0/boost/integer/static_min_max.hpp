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
eYn9aNnv022/bQnYkcRDsdL9Euw6tgT7tEjJcRyjRzPvOTb90+1cVasvZhXHH1eSh5bI4vtizVlvkwfD7xZwBKJ8PO5wBtoPOqqks5mMvnDuNTlfkb2F5Mt/So12DWOP2BCIx8exF4vOPUOBFtXHHVDz4z2mPv8uoxuakKK96QlJQWcF7YR4TvCOqPHACLbl8ZqSxnmf+UF4HtNlOXYKvdGj4hr7cWFIpjI1EE1XJJliTn8Phzljp/uk6PU7r//5bAEalyjdHRRjRn0nvOeEMa3BmrKbi1tzdw/3PfGGPwdNyf7bVvCb+/cXojdA1a5kRU/teDDF2/aYV0NoB393ln9zRs1EO268u1R/4hjcH6zP33GQrkOvAMTiDexUUsp0Icp6ZgF0L90XJqen8lxI56IxGbWdUNtTXL74nJqjq0759kxiSkX23rRNIPXxeNwh9zwzReFOav1sp/VsZ6lWuhjfXKeexXw5pGNt98rUHhIh3mXTRWjF3J4Ddi8gldi17ZSzUWiePqlmyYqceXSEz9CMFS97a7CdtvyMNVcz7kElkY7IXib16WrpPszXk1+4qb2QhmcX/B9d4H5K196cntzSNMnH1IvwuisaFbYi9JkjTAl7SvVtUT04VKO2utiXtpOw1aoIdbk6ZZi2dzWVP/l1NmZDKTZCwrUiJo82bRzE69iabH9Zqn+6LjwV6+t8PvbiT9JL+Rzl2ZvU
*/