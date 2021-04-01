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
wtkF1IUOY5XcmxY6QW/zY7Yt6bqOG+kv+6SqsVTu+qZv9Hmh+XIefnSv65LhcyCCrrjH3rVf80AGtpZ6CnWbpHpTrl4XvVXa63JMMswGF3FnMhT1KQgnJe4r7FvqEXX/mmPkur3h3fWRv68Dn3uQQ2tqF13QE4BZxgi/sOkAJTjtC5iNq296UqISeEDLmgTq3kvP8bfsCoftsNGJjfa40dKXbjOFShJ1Dxjd4xez6Sok2OJbbqKjts3ljX6zJ/norWMRxTbCbTEbX6k1vk7Ui7eJx6Gs0wFQuFiGp8PrYah5PfhEEhR6bWFdrmZdWJuAwcHTmZYKDTGLTzoVc5yU5rG4EdJ/9VQUUih3+JZrzc6m9cBDoCWJqjNps8tVAYqfRhnttZhbequF27+AitTj4DorWvc1YqbACYNCEec+ENOPKeH+3E71lzkqlaProv2qRL4hFhg4ctcrK1HD5jFZ29YtgETyHkyruRrn9d6DI+E9epHeVROxOwK1aGQzW/rYJMffU6lj+3Se6EMz5Wmxvefoi8tDMnvODj99DI/bTKzZi/e8JFobrnWDvg==
*/