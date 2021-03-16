// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_remove.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_remove
        : is_std_list<T>
    {
    };
}

#endif

/* has_remove.hpp
XKez2ztmz2pegupcurAN024Avy2MGI973tGlAG+xMe9t9vcO+9uRPbvML95lv8vnJXPZ5dVV/j221VXTqqZV11dFaqdVLR+IZXJMiLaKWTOWt2dSPZnOvnJ8Q5Itn7KmMXLA8mXJ/nhqMJuHSF3tdCSSXdGZScS3m8xA33aTGEz2c3mWzCqfenSRZ0cr33/1b8rvV4hvyu9V4Ddl9/+3MWc4o4LABdXfNjCt7FAGUML+RrK/1UzXH+b3t/8zG88=
*/