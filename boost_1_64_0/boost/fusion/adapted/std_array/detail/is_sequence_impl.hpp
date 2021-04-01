/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_SEQUENCE_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
wKCbf0nsr8Aq3JV6yYYLnjaMB4jf9KEgdzvXrVEAqAYhoApv6kE5pbKHMSUEWTFnpYCLSy/57eZHlAR70Ww/NlwiBFnqZsiwM5jc6LOrKYv3N/oOOE78cRzqFh8scNZ56Ql/TcUggCpe01+RwFIWM/8BQvD5mDHfNE8bmM2JKw79FA6pX4AR41U9CbMcmD4kTyi3pCNZf1dmvenOegphwEEDBHa11NwWucgWm7EgJYvmidv+jsdHJecruq011oOfzsyrcI+jcUF7iRYGSq/5ZgdI6QqYCftWan9Skvswls9KDotEtUWvY8ttWEoCrA45baRHAwL9l8f94mhcfpEqFF7IxZQ42AzHcVTnBDFXuljs/8Lk0Ru64A7gbb1RS88OPNl5sJ16r4oT2gE/hoHO3xC3cr9TgfMIzwi4uMx4rxtBx0Y69P7wkBNRybt08jrglT+Ofmuh4ZJ1jF8KUkRh8uPNDfil81DLC8dAQJpjGYka6f03pP8wp7ZYxn7Mn4w4zqoMHwbrETIWS5glOaPf4VDfYHV2WNgeKPHHMpg8L/1mmstoxs7uEyPSXw==
*/