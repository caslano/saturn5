//  Boost string_algo library string_traits.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_STD_STRING_TRAITS_HPP
#define BOOST_STRING_STD_STRING_TRAITS_HPP

#include <boost/algorithm/string/yes_no_type.hpp>
#include <string>
#include <boost/algorithm/string/sequence_traits.hpp>

namespace boost {
    namespace algorithm {

//  std::basic_string<> traits  -----------------------------------------------//


    // native replace trait
        template<typename T, typename TraitsT, typename AllocT>
        class has_native_replace< std::basic_string<T, TraitsT, AllocT> >
        {
        public:
#if BOOST_WORKAROUND( __IBMCPP__, <= 600 )
            enum { value = true } ;
#else
            BOOST_STATIC_CONSTANT(bool, value=true);
#endif // BOOST_WORKAROUND( __IBMCPP__, <= 600 )

        typedef mpl::bool_<has_native_replace<T>::value> type;
        };



    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_LIST_TRAITS_HPP

/* string_traits.hpp
plHPsFkrgn2cpK3PPtutV3F9rglOT/O7x+rd7RW8byiewUK8PZjAEcTfw1p0ME93dvcO9Mfvbn+Yjd9VcXACrqwaNPeG7EmRRf8BUEsDBAoAAAAIAC1nSlIdChCi+gEAAKwDAAAgAAkAY3VybC1tYXN0ZXIvZG9jcy9FWFBFUklNRU5UQUwubWRVVAUAAbZIJGB9Uktv2zAMvutXEM1lM1oXW7fLbmkRoAGyLGjcPU6FYjO2EFk09IiXfz/SXo1k2HayJVLfi5zB4meH3rToorZKbalF2KOOyWMA7SrYJ1dGQ05bE09gHJTJ26FizW789wgluWAq9FipLFt83yyelp8X62K+yrJcqXMOCKnryMcJqkXtwiel3uUXWs5UMH7n6cj4FUQCbS31kAL6IMfoTxAbbIFSFF0K4LWdMbDa6fIA5P4wIgbmmyVgLGGHe2IOBjlBaEw3FGuMgnRVan9kXlYbIjm8ytX7HH5QgjaFCOj0zg5PX/VC36Dj9iMdjKslmL2p5V4HIO7zvQk4Ou+NtcLhKLIG2CVjI1/G5gKv4ww4kVzd5fANWYUnV1t2UB1NybC1No6VpCB0sTFhesmaOYgqDbZz9SGHLGMEwWNPA4k3dRMlxbLRrmYN2OijIZ9lQPtLW6xLEg7RlOJM
*/