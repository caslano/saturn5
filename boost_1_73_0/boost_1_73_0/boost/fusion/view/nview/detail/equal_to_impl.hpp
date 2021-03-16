/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_ITERATOR_SEP_24_2009_0329PM)
#define BOOST_FUSION_NVIEW_ITERATOR_SEP_24_2009_0329PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>

namespace boost { namespace fusion 
{
    struct nview_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<nview_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
              : result_of::equal_to<typename It1::first_type, typename It2::first_type>
            {};
        };
    }
}}

#endif

/* equal_to_impl.hpp
60tRs6ArRXHwRiYPdA70YYpd6tH+rAQi7Q691fmZ/MP468bGrp+4mH+1Y/kX7XXqAVNXl5/5SrpnfN2YpojTVOYP6wvbIr5bjcavUTxGmqlYI5yleIwEPZoDGG5HI7fr7Yode81WbLYHfS3ZL9wEFCeE5gB9WpHzfDLTg7R00EWl4qlDvB+/J+iTNGUII3znTIs2eJKnzoVA0XEE9NdkjlcLFMZX2Gs7aHGzFCgu9sHoyUEdPQwUfQyCXuDg8tE=
*/