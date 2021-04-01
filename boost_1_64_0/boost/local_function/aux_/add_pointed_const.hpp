
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_ADD_POINTED_CONST_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_ADD_POINTED_CONST_HPP_

namespace boost { namespace local_function { namespace aux {

// Metafunction to add const to pointed type `T` (i.e. converts
// `T* [const]` to `T const* [const]`). `boost::add_const<>` cannot be used 
// instead because only adds outer const.

template<typename T> struct add_pointed_const { typedef T type; };

template<typename T> struct add_pointed_const<T*> { typedef T const* type; };

template<typename T> struct add_pointed_const<T const*>
    { typedef T const* type; };

template<typename T> struct add_pointed_const<T* const>
    { typedef T const* const type; };

template<typename T> struct add_pointed_const<T const* const>
    { typedef T const* const type; };

} } } // namespace

#endif //#include guard


/* add_pointed_const.hpp
sskZhVFlnFAX79g0eaCX87XNvcaMB+WakfrSKdeI9iT9unhzv90xQTDJHeJDtjT5/wcI9ggQaqWtb9uJvlEufImr3cxzuzEzEGplN2ZCTa9IYwKoqUl8l/2km5nWGRckXvjvOI34nkSCd9L/nBYgVWuB3Jsg6EX6/rwa4PssZbmiM6bODA6FeRplBHfoUW6hDMvpp6DBx0jEX3M6TYikgSICcr1x1BHGtOKyZKYO15K2djPfNpguX+wLFSmoAxPVmhiVXe1UW532POyE+mryiyrAeywNf4IPR2u1aGXs8S2cApO6tS7+efL4ma4JuGxl4KGzyiWA+60fESnQQHQhwidq8IMKSm8ZH1Pkkhn5HODZNK6xbORcFuXsewebs9KKUkZ25FZrlAK8M4mlTqWQFEzYNsVzZIbUsZ0RCT8TjaNW6jfA4vOKg8XgqkzlYmkf4+ork6OEP0RShs0a3gw4GBOSJ6F9oKc4H9ohHQZwIBndcChQdffAAwFZNRoiEoS2IFdXOc3FudGMNhxcrCj3P1vaUZYEwb6D5ZnI7kyXE0L8YmMmxetXEbNdKg==
*/