
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_MEMBER_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_MEMBER_HPP_

namespace boost { namespace local_function { namespace aux {

// Metafunctions to manipulate data members.

template<typename T> struct member_type {
    typedef T& reference;
    typedef T* pointer;
};

template<typename T> struct member_type<T*> {
    typedef T*& reference;
    typedef T* pointer;
};

template<typename T> struct member_type<T* const> {
    typedef T* const& reference;
    typedef T* pointer;
};

template<typename T> struct member_type<T const*> {
    typedef T const*& reference;
    typedef T const* pointer;
};

template<typename T> struct member_type<T const* const> {
    typedef T const* const& reference;
    typedef T const* pointer;
};

// NOTE: Do not add specializations for T const[&/*] (ambiguous on VACPP).
template<typename T> T* member_addr(T& data) { return &data; }
template<typename T> T* member_addr(T* data) { return data; }

// NOTE: Do not add specializations for T const[&/*] (ambiguous on VACPP).
template<typename T> T& member_deref(T& data) { return data; }
template<typename T> T& member_deref(T* data) { return *data; }

} } } // namespace

#endif // #include guard


/* member.hpp
FQV54lEuiobKNmXbZ2Nr4xBesKLMpKW9lbVYiUfI3pJtM/nIAp40cyXfU7Lma58v8xWSAW3+xPlGFw4W0qg3m0PBieaSHxNy5ISdD8e96W3pgYIAx4XPjMtvhuN/vanYrgfjD5OLAczYcDroXSBA4dPNdDgf4L5Y8Mc5F7Op4Syfpu+n14ZWPk0n8ytDw6cyeHgqL+MulRzEqefGGlMo+NssklGCkJVhqmQJzKeLAeW5yD2PshXPvETXgXasEsLSXG5yyUiGhcWRI9JPcjnTTx1cFU7rb4G22KTCgZnQT5MgWkHHU99262ur5Hkfp0s3LhhW6u0Ely+HowF01DFOYbwYjYh4MThfvO/NZoPp3CIz7H2iUUBkLQo3a9rhWSU7CqwD2n54RvITd83h2zc46DRpNnxVp0SgSAJL73agPeXrVGrQVjtDzKIkBXxbyfDgLmkr7VD4+7I3mg2I8r2lNWslkWCez/ZVYRz9NPkHQvs9zyhyHFEF8QkDqBSqcBEjVhoEvlbkhW4GHWXLKTSPUGdwDUfhS2VM4RsTcT/KClMAig2uKez2S9F9KdoOPNzkgDrFidlJ/nXr56IPz7I0q/kRdxNOY3Gm2a5y22Ouo893810YVR1PrwQ+nZ6QjlYcLNc+lt8ci2XCbqaT
*/