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
kaO1PZ/UdGZNANvxqZ0Y0/QkoBLVfmeNdxfJ3H3yd8d6O43QhCwZWsihxYquwJS/uqlQ/vX4UgapRF1n2JhWHiktSjfFXPIqmFNI5R9k1LHLnH38xDfXQqKkCZ+rlCYdusT+pMhKzZpomPoMyG9PqxzL2rDLFp3Oei4nOH9bf8w3bXxgPQIavvNSKcuNLJRrBWkZg9H6pWFQw5GrOA4oC07vEXzeGsVwpYozvwIjI33PwezAtig/d4jqkDC9YzOA+rpoWRAiFCWqdiz/I+bpZ+Qq/7N+1OjN/CQwt01D0rq5LMKTjSVTtMoo2ldz3QWRj3UHq3s09qxP8XzzD0IQ9mo2WL2Wpcn6ZQjmrcSEbEad/+2APfQ/NJYU1DDYzVuSvDmeByqQFq2o0FwosQ/5eFgmEvMRe7lLtN6Ca9Bqt4DtDQL7oPDxNdn04W3/aQULwHZXhUlnP0myl3J8d03SzDWDh8qFJhtfGXDq8+x1khYcqw7uNhz50L3Ff+mjiAFPEkTmFW3MxPR+zBtBWCvKb2b6a2QuGOPIo2pjGB3NC2HnuiYfyBcu6M19bg==
*/