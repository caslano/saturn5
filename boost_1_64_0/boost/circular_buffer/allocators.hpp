// Copyright 2018 Glen Joseph Fernandes
// (glenjofe@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CIRCULAR_BUFFER_ALLOCATORS_HPP
#define BOOST_CIRCULAR_BUFFER_ALLOCATORS_HPP

#include <boost/config.hpp>
#if defined(BOOST_NO_CXX11_ALLOCATOR)
#define BOOST_CB_NO_CXX11_ALLOCATOR
#elif defined(BOOST_LIBSTDCXX_VERSION) && (BOOST_LIBSTDCXX_VERSION < 40800)
#define BOOST_CB_NO_CXX11_ALLOCATOR
#endif
#if !defined(BOOST_CB_NO_CXX11_ALLOCATOR)
#include <memory>
#else
#include <new>
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

namespace boost {
namespace cb_details {

#if !defined(BOOST_CB_NO_CXX11_ALLOCATOR)
using std::allocator_traits;
#else
template<class A>
struct allocator_traits {
    typedef typename A::value_type value_type;
    typedef typename A::pointer pointer;
    typedef typename A::const_pointer const_pointer;
    typedef typename A::difference_type difference_type;
    typedef typename A::size_type size_type;

    static size_type max_size(const A& a) BOOST_NOEXCEPT {
        return a.max_size();
    }

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template<class U, class... Args>
    static void construct(const A&, U* ptr, Args&&... args) {
        ::new((void*)ptr) U(std::forward<Args>(args)...);
    }
#else
    template<class U, class V>
    static void construct(const A&, U* ptr, V&& value) {
        ::new((void*)ptr) U(std::forward<V>(value));
    }
#endif
#else
    template<class U, class V>
    static void construct(const A&, U* ptr, const V& value) {
        ::new((void*)ptr) U(value);
    }

    template<class U, class V>
    static void construct(const A&, U* ptr, V& value) {
        ::new((void*)ptr) U(value);
    }
#endif

    template<class U>
    static void destroy(const A&, U* ptr) {
        (void)ptr;
        ptr->~U();
    }
};
#endif

} // cb_details
} // boost

#endif

/* allocators.hpp
Ote5rrXuC9n/N01xnoH9/64qSfY0ssQ2JrIuqqiqWlJfHTTG2Q/XTews18uqisJIiqrAcxH2goqUyBI8la70OnMj5z1tWS5J8G9mK1XcRa+Vjps4cfa0mZMvkMfx19bKGskb2QG9AYtDa2NM0/aENniDa1/IQ84aLw7bZ+zpIS9MlAj/O9BWR+FpUcnSxRUrlRNPTJN02jy9Rp66mLTEA6BtiMZTjV/bXn4xkiemyWLYUNslbLS0tnS+dW3pxSCPXDO6SdJDfjjbznOFN7Ju/wia5ig8V/pXoAk5l2PzadbtWPKE8ybigs/Zh3W7OwpP1TVVdVWlVRUt8MV07XRZviVh72nz+V1fZNm9BVrVNYJPMYxp9o0W+ES60yu/8eRrakz0vpHSAl9F1IXvwBvSnl4fCZbZAQfechx4E6u1LfCVc5p8BfeDqmMpl8tEafBvgzbfzpfYNq0hP38Wfkqs+2ikT281P38WfpBHGD8qju8gJvLC/xW0hXZ+bGPb65H8kN7Xan5ed+BnO/npzvaexfIptvPDcc2xfEjfXe8PlJzE/oAuq7A2tYs2J4bSJvEg+HdB2xjGm2n13rROz109pzJjulzLflll/VJ/zeJSvYdnp6GtDOautK3iB4QmUz/rS+mt2/fKD6sH6k3lvhV5ibBPoe9vq7cr2yhxo3mTUfCHkfeBsLJZWrKkpXoj/Wi5flCu15ZY9RvxeqvbmaUutX39gxKHfMNk0+IpUzSXbW8W/Ptm3+xmf4ZK/3Lyb5Fr4T5VodAOxzpunLY7/t6J7Y7jnWp/X+4gL14SeOA/wP2awnipLqkrP0E7Yxqv7K+iTFpddrpthPE2lYPqMo5fS+CPmO/yMN5qSpbzMy1y3EgV3pgGOc1QXfR708iRbxKLnFU165/01CU8C+EXJDxfDeM3zCx7eupFqdB2eZ4T+gXqAmVwP03y5J607NfRrn51QJ6C931DaHqjHNqRF96Hsi+5ev81ZK/h1W5BmxOJ2l5DR0kTd0r9MxlxI/U+HcrEps+4wtYf9/BjYREz9cN/ZI7rORF1JF3SoT+SfpFljOKbQI9Rmsay37m83F/jZ/la8mA58bpZWKwzex7dhaa6KqjTEmO2VV4AtCfU6+0wBlCvnB7j+CykzdJ7pcKf0ObovdIQz6AVnrpLvPBpK/s5yXqfSVwm/D/Bw77IspfEDv2W9B1arcfjdYf3VnW76O+tw2H81Pprli0u1a8tJ76Q7sTvLdJY3lvMXfG9ZWL3L/K9xfuHjWW+lMjvn6PIu6B7WNno72rHckGaE34DtVRf+ru6KQpPH5t914GnokrMTCprzcd37scnyZvTN9DIcD3+/F4sjsobv/edy4zp2reaL11mYe/u7emUUTMC/bU98DhoGzRfXIWwytPIt5TmhbSDtQ78hyR8zGLvR7chvgOYhjr9ZyL8gIQPi3zpbnleLn5wghHUFX6/0P1TwuU6n/7RxlktM7tTaA6pr6tJlHcLpsvTMrQ39jDDbSz56NmNdQxlOrvurmPCL97XNh3sdtqtDrYXs4D3BeiMVH39spLFRaThM/QT/iaF8yt5vpQt37dQaFQr98q32IF7Iz3wDbUf+IZ8T53YtktXyGQulPxVT7RFDGqLqvABWlFRVVrkr6lRyZbrZjjVZvNL2gb1YDHOMoZkUw/WbmmP9jqmLiz7O4bxjTpe14vWh3VM8mL5c5x7SeICZZKNtbVXEM6/zWz75ZAxwrMsLCldIvu7SSIDliPrbpZrwZUy0nyK9OvTHGj8tbKG0yNQJsoIkwOtkPqRM/aqH7AW6AWNytV9DJqoav0yATKLymYjLhTJbz+mizG+pL6H+4quPNKFvqFWCc0=
*/