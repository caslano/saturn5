//  Boost string_algo library slist_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003. 
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_SLIST_TRAITS_HPP
#define BOOST_STRING_STD_SLIST_TRAITS_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/algorithm/string/yes_no_type.hpp>
#include BOOST_SLIST_HEADER 
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  SGI's std::slist<> traits  -----------------------------------------------//


    // stable iterators trait
        template<typename T, typename AllocT>
        class has_stable_iterators< BOOST_STD_EXTENSION_NAMESPACE::slist<T,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<has_stable_iterators<T>::value> type;
        };

    // const time insert trait
        template<typename T, typename AllocT>
        class has_const_time_insert< BOOST_STD_EXTENSION_NAMESPACE::slist<T,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<has_const_time_insert<T>::value> type;
        };

    // const time erase trait
        template<typename T, typename AllocT>
        class has_const_time_erase< BOOST_STD_EXTENSION_NAMESPACE::slist<T,AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true };
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            typedef mpl::bool_<has_const_time_erase<T>::value> type;
        };


    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_STD_LIST_TRAITS_HPP

/* slist_traits.hpp
SutvW6z3b7Tt9f3L9m8wO5/GB4vmW/Pt+HUlP2/YQFz/1YOpzvGRl3XnGJ6AjRy+iMKHqS72Yz9HSF2eT1+97idZjLTr5ZR+dUOhjcVXPyVvGROt/xafxR9FaRt/y++GQBTFjZy+pShUv+wxuz62tn7hd0P1sUdC9fN/GKpf+NNQfc0v62t+U7/s9/fbyTbeFYLnY/L0OQvpzJD5x8SzgVCwg5fjaRG+MdE0ioqyLLUGe5L3diPLCq6lLANJ2rDeOAJLivXhFzmdY3bhGmwx2+K+kyz1BtYn4vc/eNanZ9CzfEY3pmYYdnC/6uCVtn3Y1Ns43GyjS66ZoJnMpr3dRn9wDT0jGzM3wCiNxyAggTtK5vDzm1PP38Zpeb4VbMYcBjDgx38mdP4NmDRuxUySWouH4nmh4Ismk+8nbMLmcyEVe0S1ahTagQIwfdYSJAZjYmkAErlpJPIYiaYUEjuRFiRocruJuHCi2sNYrD3Q+Gt6Yj4xoZ0eS9PkajUQCu611JPMBVwJhzZq/aS5K+7LxSycsUs/9wTM/QARLYQOyhqSRqWAUUmkUNmDtEalyQomANvoxQLStzf9eiuY0YLHWQbvCwqISNQaYIIpOLONZtCCe6lKLmMUbAkxKljycFEZCvG5mLRTzrA0JsNxTQtmryuXhBYLb04pNNqYCfHPXdG0YIrFGGGuer/FiITUZgjI3BwO/sHSmECshMkGwqQvZGygJ40QuVDyxPTzT6Lnt+LRB4At0MDcV9febszSk4TxCuEBs0u1BptBvygBpl53D919OaGDlS9WSIvW9p6HNjJTelEPC2vBXhQyLqJjIbOLJfRUyOjSfBkZNvcDp3DwIEtjNeWN2tsN3DCtLtiN5pInU+xJcjqHUILMtUzGmJhh/dYnL/wshMd8sQixdpotfYWe3sRYiJLhNXRgETL6CfhYIgIIeG335LTpiuWOw3fXcZO2XUObLgtbo1BMKKy/aswPU2xpJUSgAq9YbEXYBwMMzC1WcBPKGB/WtFaWEJyHsUE//xSINK0szJJT4WPS8goO9CQ5KU8CJjM6ZA/LEw/+IGcDr/308dOTtFh1gK0mhLfwg00sGhyJ5jqRkNEoBjxee5F6XwlvNyKK0uw5LY3IhIEuJW+gS9GMKSXGZF5RO0wYQ8s8iheWrOAb8Gdi0gMN2nUqEJKgdPqhPuWMNBYTB/qUgoE+BSvehMATd51NSxK0LWsSNkeEARlbsVQfRIGp/7VgLx7fJYLBxSSHAjTi+QF8oY7WzxtH8b4nfD0bu3f2rsOmKL1X58z0VqmzcMWGHXT3H2llqY8IKezSSKBLGR4yHc7KCQdfDjGB6BfM7sp4fibt3PtU87L8+VFV0wp8sYSluoAWrb0PB8ZDzG5GFre5ZjeQhcvZSqiFMIPKu7cuypRNh5TkXYmSNHBVHXj6SYQ/0FE9ePRecH4dWWqO2oVbWo40EsG9YTTwWcQKehgeSZu+sImveuETNxJSaj1QChvNZnfYeBaFofqSEkGozQp2mruFV08auzWvLsqGpad51UdZg9K45TCvWvzR+ppW1oERYfWa8Go0PCpn5YSChCHSwY40qz558Oeb7wBG5PjgePpVLwaIPiAHVJCVy6gH14QEpaiaD57uDpGDw54oQk71ASe1GQTnsghnZ8Jz0uau4DNEuiA4m/koSeIji1PwG8dy1IitBfPCqOOjPQzfHfSHhxgE+MXohbEcZjTCuhk9S/ADmhbht1Fk2IiZfc2z2dkQvGYZ4o+7KWuQFXwqjYqwrclPX0+Z3+qiFFRtghJpR4pVoXht9e6HEoxMB2ya2KU28/6HTWZ3cDNyw4YDjKwVQ2ijRTdA3gcc0Vc=
*/