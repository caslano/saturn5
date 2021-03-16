/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
Mx7SO+EPa5uxCU3bpMhUBKwY2FJgtwLbD6wRmCZx3V31dgrXC7eRkqZLUtGvJqBwWfHC4rIE5E0T0el6rhurptJaSeHYaXp+olePSt/vpPBeTeF9eiC/X1P4NCh8OtkYKYzNBLYU2K3A9gNrBBazvlOlqLpw6weCe7ldPttCzYO5K4ddafo5Wp6ZW1cbJPavfY3miIZH6tVFMyFgX77ZV5jOaKAwnZEc/uno7KZVaf4qxyPWAL1/gvx19mpVMyE=
*/