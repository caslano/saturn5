
#ifndef BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>

#if !defined(BOOST_MPL_CFG_HAS_TYPEOF) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   defined(BOOST_MPL_CFG_GCC) && BOOST_MPL_CFG_GCC >= 0x0302 \
        || defined(__MWERKS__) && __MWERKS__ >= 0x3000 \
        )

#   define BOOST_MPL_CFG_HAS_TYPEOF

#endif


#if !defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && defined(BOOST_MPL_CFG_HAS_TYPEOF)

#   define BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif

#endif // BOOST_MPL_AUX_CONFIG_TYPEOF_HPP_INCLUDED

/* typeof.hpp
y2Mp7JNc8UaLU5LX5GRRsmT3oki3AbBMMHsxqmpOKYPBG34lHR401CW3f5+XazUNVRmakxzkGPJWcra2/RgcHu5tjYXR0S0a8QbYtrt1OG8ncJ1Engo2M8lrfdnGBUVKu4i+ctnbxQCyXNlYTEuO0hx2+1gP23CM1lLFMgqyYd3uWFUry82eYSHurTtD4dpGajC8Mar5Q6kVU1mpKKw+Psb2mfsXQ9kmc/4DqEYnqgzzxdFsrq4kaCtHpHGQWTdrCRe96odU/P3GJycLdoXlqepSrDq7g+4AJwSU7ehENieDNuU4HQ8/2q26nAtDWM4esCftnOKqX1Ip2/bGbCGbn8irIH9YcsoM88rF67yy7vQnhm3paPI0k0m+olanqpdvJ1MrmCn0dzcVshh36rWXx1u6B/lMtTw29m+MWhv74joPZeyk7LMY+PgoKpit5ithNRUqoR3JJnOhPGd59LD8RK6SFYNaKBcMKO1y9cjIvntZwxTfRLpYmM67Phy7wn6ubUWlJ1kuFrKYE/SmG9ys8HzBAK7iNtkpzG5iny3ZdBiWd8YxlHBtmR3L1mcZaCddWbXu9gO9MJm4UU6wzjmUxn5Gkcu0uy7DxvAgW7jatpra0tlQITdd2x7i6LMW3q+tM8y/vakgc5t2WrgX1jfU218oTVR0Jq0SRnw9yfFxHhczbBJzHgxuFObUh0WSpeo+xTm15eWtkK0gBnOs8VCiJ65t06Y+L9tp58t7E7a5bl+qmaK1mVemZ3Ca635S2yPJclr6PBud8WblxVgmV3vVMIxxvPThpwnbbDD61ZmXjcZ8cx2nG51jipteTEYPBqeHes5Em3G60sOalVcs4s6ZMsTkLEWP9yQrqUw4nc8WGKlxWP2+y0FmfTV9brTD25uFDdvj6zDoqz+eerbrOY115jS07S9sryvLaLlcLBNp7cCEe+1Az6AnapyHbB8YYpxjhDpzmrCm51i07lwibsI3Nz/HGKvuHGvCnRl4D3Dd+QTeiNWdY3V2Xjaa8IbnGO2N84nUZA3PsTpbLyNNeNPzC2HNzhUG1YcxWn2dZySzHhOajJnSublvmLwcLHr3J1jDm4Z755ye70h/b9ZxO7t1PnC5ljntiMwsef0R9CxSQorjuDfms81npTpV+w1lTKWgY5FFK1Dt51oyj63bYrrX7bH4Wbgw7W1XMBmzrcPbTk1iHTc9sm5f1ZpEZtTeBfx9EcxnFyuKRSRyJulkcFyJFXf7KhzB1lg1/2xffLY8PBNZVBEjrFK9A8sZK43jl10hH5MO3ZjOYusf+7hUspRE7x77x86jFl5tCrwuqj+sWlDMsBmHO6dzd3Yg4kuN4TLyqdY2fZt54xhjWrrR1jgO647ktNUwz4xnpk8u6SNxl2WrefG7oW31IGKiLZHBSEYxHH93XtFMJxTd+BgxquM9bTHMoTXOQyjymI0NeaKjsT0uGX6+nifIeDmv99lt8yShPRxjpI7t2g06q1rNLaan2VVnfSuq7rhbOHoN7Lmv/ZEIrlvk2LCKZasiRWABc5Dki4MzsNeelF0id8cQaVvm+L1I/r56qD+cCIeggMF7s9hzx8/COJVwhhYwc88xrT/8UZit07cfk3WSps1GjNiltnJA7QsbLE5yuNqL+bpI78Z1sp7GXF0qnR/j/Y2hcDTmTZDHo4mAKqPEppBsZCsTISnmRw31DyZC/fGhEENkDFzExHUo6xRDtBJ7uT9Q4JA5pI+gJS/0rdtYQw1t8k48j4Oawq4NFHGnzj9/WwvLMYxxNsUGfXYYvU6i4JEK6nkBt4ux5s0rGHO17cZcbbsxt+qFY5vhai5UD5dthvv8dxv+uw3/3Yb/bsN/t+G/m8c=
*/