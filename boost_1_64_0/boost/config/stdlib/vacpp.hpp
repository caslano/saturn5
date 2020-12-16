//  (C) Copyright John Maddock 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

#if __IBMCPP__ <= 501
#  define BOOST_NO_STD_ALLOCATOR
#endif

#define BOOST_HAS_MACRO_USE_FACET
#define BOOST_NO_STD_MESSAGES

// Apple doesn't seem to reliably defined a *unix* macro
#if !defined(CYGWIN) && (  defined(__unix__)  \
                        || defined(__unix)    \
                        || defined(unix)      \
                        || defined(__APPLE__) \
                        || defined(__APPLE)   \
                        || defined(APPLE))
#  include <unistd.h>
#endif

//  C++0x headers not yet implemented
//
#  define BOOST_NO_CXX11_HDR_ARRAY
#  define BOOST_NO_CXX11_HDR_CHRONO
#  define BOOST_NO_CXX11_HDR_CODECVT
#  define BOOST_NO_CXX11_HDR_CONDITION_VARIABLE
#  define BOOST_NO_CXX11_HDR_FORWARD_LIST
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#  define BOOST_NO_CXX11_HDR_MUTEX
#  define BOOST_NO_CXX11_HDR_RANDOM
#  define BOOST_NO_CXX11_HDR_RATIO
#  define BOOST_NO_CXX11_HDR_REGEX
#  define BOOST_NO_CXX11_HDR_SYSTEM_ERROR
#  define BOOST_NO_CXX11_HDR_THREAD
#  define BOOST_NO_CXX11_HDR_TUPLE
#  define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#  define BOOST_NO_CXX11_HDR_TYPEINDEX
#  define BOOST_NO_CXX11_HDR_UNORDERED_MAP
#  define BOOST_NO_CXX11_HDR_UNORDERED_SET
#  define BOOST_NO_CXX11_NUMERIC_LIMITS
#  define BOOST_NO_CXX11_ALLOCATOR
#  define BOOST_NO_CXX11_POINTER_TRAITS
#  define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#  define BOOST_NO_CXX11_SMART_PTR
#  define BOOST_NO_CXX11_HDR_FUNCTIONAL
#  define BOOST_NO_CXX11_HDR_ATOMIC
#  define BOOST_NO_CXX11_STD_ALIGN
#  define BOOST_NO_CXX11_ADDRESSOF
#  define BOOST_NO_CXX11_HDR_EXCEPTION

#if defined(__has_include)
#if !__has_include(<shared_mutex>)
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#elif __cplusplus < 201402
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif
#else
#  define BOOST_NO_CXX14_HDR_SHARED_MUTEX
#endif

// C++14 features
#  define BOOST_NO_CXX14_STD_EXCHANGE

// C++17 features
#  define BOOST_NO_CXX17_STD_APPLY
#  define BOOST_NO_CXX17_STD_INVOKE
#  define BOOST_NO_CXX17_ITERATOR_TRAITS

#define BOOST_STDLIB "Visual Age default standard library"

/* vacpp.hpp
zDKmtX35VxQkc8dZclPrNa4BTeZibZWQROZHyyFsW3RsP64hzpo8OpWXLBxnGX/O/pRriLNMV4/zexMypbW/w+sn8PzF2X/OjsrF9aHJ+rL8++Mqrg+tubBRtWvl51zQ0gn7Y81lfr/H4ux2qcSrZJDZCnZhj7728PvIGWcbtrgGcp5xdu74EROZN86K1qx0kechc9z7fWf2rmQBtEzCDnTJe5DnKM6GNs88hSwUZ1OKJd7m+Yuz87lq1iCLxFntKtl4m4/GWW5z8eE8nnH1ta0X3kbmMFuhqLB100t3IvOg5RbG52pofjS/Sbemk7/l7cVrtYJNxLW+8qgQxyksiJZVGB9noYUVFlUY2IzNqTA32rKENzYAbdjOPFV43t+yQvFE3Y4crXqSLYsVeifpdunHg3l5rHNZIb9oc+eYt6pzfXmsUE6zgWh9n//9LbfptMJFk27vgfsQ154f8wTd8pg+/oUs9L4VGgu7kn1RgHMpYIXuss0/VhQjixS0wklh1XPm/YvjiljhHOjW0l4iO49nUSu8J6zosIKVyDxog4T99tX0IVwDWmlhfP8lNCde8lheGN9/Cc2Hll4Yr+Gi+dEShfFaCVpAYUG0ecIaH1/B26e3OG4vwuT24ldYUGFhhUUVBiWMzakwt8K8CvMrLKiwsMKiaOk1G4TWsUOGjWQxNLewbS+vX+EaPrBCdmEVDpw/zzWg1RC2NnHrT2QhtHHCPr486WuOK2mFucJKjN3T5o2lJjpLWWGmZoNNqYlFH6bayCJo44RV9Lz9mMzvsoJP2HfnKzYkc5S2wlfC+rfofZYshtZcWJc7t0aQectYoYuwnUeHjyWLok0QZnmn1n6yQFkrzBL2YsC4C2SeclaoJ2zywP6HyUJodB7gQ7v6VRMP11AB30fC3p6e5S/Os6IVPgXdfnr7h9NkUAmPhYXxtVtoDjSPsN6/nH/J44l2XVjf7MPukQUrW6GWsDtjlp4jgypW+FLYxJQ/mvP8ofURtq6k+V0el6pW6JegW8qRreW5vhpWKCziVrfJWY7HGi03iLgzMxLJwmgNheW75DeROWvi9pLujX2CVmzd+cJksXpW+E8G3cb/2/h7thZWyKPlmYy2+kIGF4/LR1bYqfWXghb+IzXMebbE409h+vr8pMQg2kNtboeYJiUuKfNuaTJHGyu00Gwo2nB3mTFk4ba4nxfW6X6f52SB9lboALqduLU8RgYdrHwtzjC0ht/1asa5oLlMup1ZlziDzNnJiv+tm9Vdsw/358XPYtDtxMTC17mGbjhHwnIcTjhB5kZ7T9iSkyXWkfkUcUFFXAStlLAM5w/n5ly6W6GKsNEt1tYj86JNFDajzuD1HNcD5122WXNPlGtA+0DY8rltDpP50coI+2hTnlY8fz2M64v1MK7P2dM4zoNmFOdXxIUUcVFFnKOXcZy7l3GcTxEXREsWdnFExSZkrt7GcV60wsLsx89PJAugpRfGxy9oQTSzMGvDHR/yuKAVElYidc5yHhe04sKOnwt7eY76GPfnQjPqz402TVixv8dWIouh1Rc29dNT13je+xpbCM0hbECeDUvIImhZhMWyJA/g/tBqaTYc7Wax00O5v35WGCxsxfbKTh4XtJEm3TI//X04Wbi/FW4Ly/J4+688ZoOskAK6Lam/9B+uAe1bYePPB4/w3A62wgnR5q7bXfJxfZ9YoaOIaxp+9yDXkGzl72VGoPF122ghNKp9JNq/oxZxDY4UK7QWdq9QqzVkfrT8Jt1e3nprFY/nECusFOb0rDlLBsOtMBZ0GxFaMJcsiOZP0G1Dut6VeTxH4b5OWLuBXxfgXD618rW9o9D+XnN8CNcw1gpDhVX/4f0=
*/