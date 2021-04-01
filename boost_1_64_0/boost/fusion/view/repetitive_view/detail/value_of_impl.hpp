/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_REPETITIVE_VIEW_VALUE_OF_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_REPETITIVE_VIEW_VALUE_OF_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_of_impl;

        template<>
        struct value_of_impl<repetitive_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
                : result_of::value_of<typename Iterator::pos_type>
            { };
        };
    }
}}

#endif


/* value_of_impl.hpp
/IuUcJxNp5s1vsgB0CBQ+R9VUN2jh3gv01pRxdvRA8SP7jU9vZpSOxkI4l7Q/UzIz6PLxr8gapo4+jIpW/fJWB8gYK8z8Fa14drPk/j9RJBtp8r13/kVzy/NasE63YHJAXD+tvsZVLg9pRKiDqGtGnpR59buup23k8k5+4MqpNQYXGCHQdHsn2m32pKowobxRFBv/L9E9e9fsbUDEti4QPXJ00e48Rf0lu14zs/oyI8ssWmCoZiy4um3fVYcJyOMuIOQMUYc1KGnuZ8JXx6JLAQRg5sXrvVLnT99j/p0TjJVWWIyXYSyelawSPBOwi/JkSC4MyjsckrTZe4TXTNH/JA1TWXIdjSIiiCHoY9MYFVBv2greOcDPi0WM4ALXb3QJVhviv7sjJZRmi0717sk3UiEM16yKzX64//JyX/Rala1I7/YpIkFNjQF1xj82D93PJGU95rVZNQPBEiQ5ru8lujRzt1QNSxEqSCrbaFyWKm6DJ9gZWGuJR8YbsU6dHZtf/GCzkhRvwkDX8RWJVopbDZTfWM5Wk5FdO7Kd3MHhAZt7FOFfhiSXBwbKw==
*/