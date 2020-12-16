/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ELEMENT_TYPE_HPP
#define BOOST_ALIGN_DETAIL_ELEMENT_TYPE_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#else
#include <cstddef>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::remove_reference;
using std::remove_all_extents;
using std::remove_cv;
#else
template<class T>
struct remove_reference {
    typedef T type;
};

template<class T>
struct remove_reference<T&> {
    typedef T type;
};

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template<class T>
struct remove_reference<T&&> {
    typedef T type;
};
#endif

template<class T>
struct remove_all_extents {
    typedef T type;
};

template<class T>
struct remove_all_extents<T[]> {
    typedef typename remove_all_extents<T>::type type;
};

template<class T, std::size_t N>
struct remove_all_extents<T[N]> {
    typedef typename remove_all_extents<T>::type type;
};

template<class T>
struct remove_cv {
    typedef T type;
};

template<class T>
struct remove_cv<const T> {
    typedef T type;
};

template<class T>
struct remove_cv<volatile T> {
    typedef T type;
};

template<class T>
struct remove_cv<const volatile T> {
    typedef T type;
};
#endif

template<class T>
struct element_type {
    typedef typename remove_cv<typename remove_all_extents<typename
        remove_reference<T>::type>::type>::type type;
};

} /* detail */
} /* alignment */
} /* boost */

#endif

/* element_type.hpp
eGCJORqnjDRHY8kSczS8Y+inFJDzJg1ItTR8/E2oCU2VFqq2n0CmXKP7WMocgz+F3ZGwDcL+IMUixpjdGA2QtO3W/13R9T87uv4DPO4nk5kxcwOwLrAOWGA/K09DfF10Dwi/Q8VsoY2XFy0+nsaHKvM+KXMo8mwwF791la9BTEvLSjeZudmxt79Zrxn7xTbaqKcBb1T7Bi/abSf+z7p+Vt1syEvr+BS1KjS/pM6Vley7ADjN+cZN72e3yVCca2o+6YEutL/PSlub0FAkqbwTTFsHFy1X/bZGNcE80bYm6X+Kxov4f7lJSeL8lmpkR5+/1xnh2GZeU17VH9DE0RDYEXoPLzjRpF6H5TNwKYXi8hbgBLvn5Sb4u86bGR/v7zAPZsr9aeTDmJgOXQK8pZ7OF7jZW6Un9iqcmSKeX42SYUSVyq0pYJp6zS0HFCPNE7yirzd4KVb/Eh7e24fTcs6/hSmoJxuhvuFC0u+PMiIv5N9DsXM/EKGLwLYT9CeiwUr+bVYD7SExLShWwnwmI1spCflqxXdtzWBzZ3l6sKkd9MCdanPFOqkEp3WCOpnKGWH1/UGUd1Tg1RJ4t1f7hWxlS6h6/YKZPOTzzWAZlXwEc3t4317V1H27ifBl1f+cqdiEX7HC3ohsXS9gKHIVhfyunDqtnvhp7d1rH01gevedOSB0j8CWWhg8R3sHZIv+dK9F+mzyfxckKvyoXOb/7+RbL4FV0Qzu46msvPdqRcTlXL5J23REhVGZ+/e2/YA/qzy40L9uNFxNZTJi+nNYrpmbHeebpGbnzcMRamLxURnQnsV2xJTz8DQglmVbAUm7yEvi4GPgs7FYPA/qd/ych+O8o9a1e5FdXYPNK8dylFxCJY9DyaWq5H4TueQhRy253LZkV/R2dI6hBmqQ5r6HAMdx/jXQf/WbXse1r2vmm73AtElHgqojf7nFJMjgKGoWBCtfHVDof250B/ZGjglLqD/G/7U0gmilfGIU5u/09zHIii/ot9waQ1ZEZVaP0nx8Y0ZoCeTqnd3EYK9jzlPFbGSKFnQuCjoUMIy3+doZKnqTh7DjUn9CuEQFubV39FEIxX4+aKkKw5J7jAgW+Zt8p4htHv0Kr/CVVQoIQ2UMEWEo3EsHsla/G8vPTeuP2O08u2brf6x5Nuiz7XxWedyKWxWx8+KeFrHcijfntmTIk08WyM/f4xy9h7o37mraYSpDI5kGWgnO2/tntojz5Cfd4Vx5HC6bGu0PN91g0seZ9lNJQPS1BxiYnk/H1gG0r11oWHzs+rausojQSQU4MxbynYcX2lOy0IJPCIAKbEopTQXQY+znDYlYf5geS8NOd7ED98/inYt3YmiXRgky0wLUTh2kw9Q6pjxlOiseiLdSNJ0L2+Kb5OLu5BvndkIvJs9nvwXwsUvUsbWTMCuhsogb7L45Ld3PeomrSZ0mr7W/nsRJQzPj9aX4CZOHRoq7mAAzjmL1TWWCBuRDmMitvYYg1PInFdj7Osrnd0i+8E8pQ4YmA0w71sloIDJR0l8u5CzUxpSpkvvJMlpLqX4oqr7KnqVv5SXSTEqjsnKwRCim+hz2pIiFYCX5PEI98cjsqS1yj4VXvfa8vRFw1vMPl1+v/MFa6ftpC4iW8Vi9ElIYViiOTS/EhBBIgbieo4J2nSPuzAL1bXyzGzdALsGy+V8a2ZF/eO6vaD6DZwmBSVkUE1/UgKxpVgITJJlWKEmmaxOYLfzC6VGTaGt07ZKG8i/hJ7b9e/9hP2FIr74+5n66x2fuHdkTqwPrDjAW54keGveBEKWcTtf0EWm5LFAj1t9hscU4eyJJcaoBMQsrIiptaNlqZmgERBxGaYKBZQ+58vRRWqE=
*/