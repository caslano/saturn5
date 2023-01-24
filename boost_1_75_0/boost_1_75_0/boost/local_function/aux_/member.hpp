
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
rU9PmLEDwp8DYIGmQFGY4sAB6P6VHf2+ZeEd7GNagKqdkD0JipHINnAvAavPQSpsu/WjkP2D/+ssiDxOD+wq7L/dSunXt/K+niN69iQYJsm0DNxRTVn1lbiqzt/sSZCoaPyBc/oA7v1cZ7YFE76x+WHZewfbC8sb34KGu8fbp+O7G75S8nLyVPuyRGrmWw987VNHXDO1hc8LHvZ1dBWAMWWDWje6slH9N5/48rYl+HOfPxQw6b6dFDYciUB4SI7OX/SOc8rJOl/+KN01zCu3yLuceMns5I6f+UgmQI6u1KRaoVyF02UDwqQ4nC0dqBplc4rWk9+EGyhIbOm72jrwWXswe3LMqpkf9U49/v0yrJLPU0VBAUH86x9u0sGYWQkKFBRC4v+dn4kN8B/zM/nYkw67bCHi4PVYK1KkmEg2TzXKSKV8wka8Es37lPCYK3waSfBRuv6jqOSVWDY6zPwOZYSqdmAM3nCZhobc749Z+mky4mpzcFLJPOTyJ65sc4IvkmuCqzIlTzTnpexZZRkyfBargJgZkCsIQzIuCFnuOdSs3s63Rc9ua83nxZUwtKsH0uEi+LZ4/gJJTg5+qwzx0bbWd6lmi9vOC6YKHfHTZiA43929HCiheyXY6fNYozyciWSdeCIR48+HngkzF+GguRBZj1an1/avEq1MteEy9I6VgQh48/QrpkjUp/VTMwTX/SoeawFGGODe8lhl
*/