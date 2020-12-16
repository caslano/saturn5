//  Boost string_algo library list_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_LIST_TRAITS_HPP
#define BOOST_STRING_STD_LIST_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <list>
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  std::list<> traits  -----------------------------------------------//


        // stable iterators trait
        template<typename T, typename AllocT>
        class has_stable_iterators< ::std::list<T,AllocT> >
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
        class has_const_time_insert< ::std::list<T,AllocT> >
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
        class has_const_time_erase< ::std::list<T,AllocT> >
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

/* list_traits.hpp
JL0rhExIFC4Jxhq0LsYf9A7/l0IaaMQshsEYHWgzydgHMZAMjDfVWmI1CiFvcFALjfa6brDMjWFjc3ALGMTlG+QB8DnGRmMz7CBkvp/svJuuFWYfOowx4AjIKwJDcCnRGm3uIN6E1d7ulURaQHXQZVrYfCGkppWEMF9h3lrix38oAu4h800U+0SHre4nwSvQrXqs7lazj0QH1rR+Y9vGjy5vov/DxpOYvBXVhEBDoprkUcFRoxNFoJXpB1YGk6tEzJAxnukTMEhhOqIXIrPMN7jy6+BHdyvxwnwtZIANXQCQYsY6aCckI21RxdgCFLkI/IDpgRn5JGk/2RGJdifdFUp9ogiEQB4sVqDZYmoKUhVWoRyniY4BHSadAm504qPtQAE3k9CiO2H2wLp9QhgIIZoVMuBhlicIBOoiGxgjt8zsQbt8cw17e3N1d6Iet66nV7iRRiAW92iq7mEOkRyBBNPQSfSandzWn/LuCmk0ZR7gLr/EpKcRYuYarjlGdYAjKf1KAHWhqklaERuQDU6kniio4v+1KEJyMsBIkTAIrNFVUyi3IwtGhIdzW3Ix4BUxBHeFaJ5f4rIJlVLN1uEWqBE6aMesEeZ2yVOBfMDLosBAFnVrLFzeEGPRWD8T/7s8QvpQHvnMToCQ563rJragRREaiNKL8IvSbFIp5jFvwFzUwPNwTB4cB3DjJxanOYSbQ9hDCrYabAGGncKblDZyWw+LWOBrmUHzkG+uMQk1qBzaomYplEIaEstcDml2mGuYQdgEYq4lxQXmqYZlaOjhSVmaJyGYPTqMRrqHR9Am9iY6UOFrElBgnyVkKgoWS4bczapjHoSFoqgUgIMd9XAjxv6weRCuAiTn9VCHEIBHRdW87hDO+CW1R1NmQbZJOBl9BLKQKFbwXN2Yoa/Dcsl9YBxwnhRWCQDqo+rwbXjIWjg+CuZWs5Yb60jjwvH7qQnYNQmgwTlRANVn5XXDwQZXodPpJm4xb40eVCwMqyZWdAiPgIfjD8pTnyauqR8xMyleygOwYF89VYVLgZRwKbOC7QAI3miuM8h8KIRo1A5cSsIKh1iVlJBzHkP/FdJ/pfQsxs4HjgEM/I88uV4eaTwNjwveUUhQhIeznwqCd814INoafWiHh/mCHVa8ganez6wGd8FoqpLXjTbgMuAbTwXXpvlJjAQ/wUepBk6CgcZ6NakERPk0F8lpUgRr7gSLuleqvvpJJVSf0A+AodCV/GAPOg/mbNj8MySru1LqVhDOcUdarDlqrCfGk+8Fb6lTEqaCymAfETkZLLXM7ST8UpetRk/3SiBPhxrD+YOTDNDcy2pgvoruiPqJYEd3C/XB01IsRHcL/sGrEzuawTahk3ho9IEd6F48bFM9qIcisA3ME/Yy24z1f41rYBnM3mUXsaXM6MUFsqYi9GNgCnepYGCKNWHzTSIxgM4V7A6br4EVk4hPZcxv83UIQ4ma4xFgDnW34DAFHKuITyHRYMtgo6oAd4j0Es1lMBHsBf/AXbALDCZQQQBsgrUsb6U6y5u4pvmy8TRxdwu4ixh2g/BL7aExSUs2ptmplrDXYrslhesLEveMV1jV1EEy6VbmRbex3thPnkCRwfXmQTE62ZDBrxBZTBiGTQ5drQFroDkdxJlJzEYLnsmg8Ro8BmJlCUEQlmzlSI0aUFyP5gizICFRwtc4OgNzwBotAnTixHk+mr2XuDImD6p1HakpOwuIAWwT8faR1ranrZ18xDpwDMNHsErbWM/yFioGxZoPUj2tWx3E2URKtXpTkSRMaQdZErQG5gNOozkFGB31yDQ7oEXLE72J97VTo04mx2iFfsPlonehkDGkXiRFKkIEBscJNTJlJIc=
*/