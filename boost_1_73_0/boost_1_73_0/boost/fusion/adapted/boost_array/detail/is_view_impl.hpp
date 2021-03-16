/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_VIEW_IMPL_27042006_2221)
#define BOOST_FUSION_IS_VIEW_IMPL_27042006_2221

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct boost_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<boost_array_tag>
        {
            template<typename T>
            struct apply : mpl::false_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
QOvdQsWLQh7bOaNtGxT9pX1Ddr8OCEX3hRaJ2JBSebLTO09a8IgAxbWwcacENa+T/VCqMHq/mfWYo7w26HQW9g065nu6CvsOHfv7DefMsD3YxCiwL+l508ccs8PHC912+njv5ls+TrzT4ON9O2/Lcqgs/yhLeuMeWU7Q14nTVoHTVilumQ2sBNgvgN0J7EVgW4DR3BNjV1sGqxubG2MfJ8rCfI9H+/9/GXS0ZMjxn3rIcZ4ecvTVQ44G0LhB0WQ=
*/