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
zPoIT325ygFjJ8OEd4OjwLkh90ERfq6jcf6Jh4GmFafsVbR65JJu+KeLwoNZzwBOq5e95ZlLdm5j1UWwaXCAWXA/nSOePl9ZLr4RsMSGZoipSroGk9tdp1ibYUfrTF0O8MIDVWcOrkAUw0hNO+oh3RrEotMo3s4jUcwULlPcKbvuM+P+Cd36WRAC4Su+EPFBl4/1Acif6Y9Tv3E+B/Ikk3UTv9xQQV2642+zpp3VnhBLbEmrf+dsEg7dUENSGddggZ1JAZHqa4q1aYIEez/Rcw16SoIlksCeaN85IjrdyVxw28MFrD9sZi/DXdhlKlJV5eVENBIDxdWWzZo6ixma+YaYynDvMHW+mE2IfU4l+8d/QpVNhdBpMbqNXiXczW4FaJqr7NZBRrPtvKTmw82q73eXNEGS9ag8K2iHCK1Yz3qSgL6t2N6D7PUX3cM5GVOCS9cc4xlsXCUF8APfxOTaVVCCQVGU2Dx5jmUMX2NZk4d9/MV4XPI2Yvx3ZbzTz+s9EcIjD976gvLUarHKsuzw5bnU7rmVSgXEDp2W1Pnm5SWwG2ZlpOE2ggppeXXMSQEg1Bq1zNCc4rQbVZIzPs4TxDVIM6ishOk5zlMalXmeLudPWlGALYctZS8TrIYtCCCjT4n/eNwr4yApcDhXlQIRUDQgnfZOJ2ckYEIKZUVmXkBXZFFWI1BWYyZnwET0MwiYkjKvatUhwTaPcGaF
*/