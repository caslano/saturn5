/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_ITERATOR_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_ITERATOR_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct equal_to_impl;

        template<>
        struct equal_to_impl<single_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
              : mpl::equal_to<typename It1::position, typename It2::position>
            {
                BOOST_MPL_ASSERT((is_same<typename add_const<typename It1::single_view_type>::type, 
                    typename add_const<typename It2::single_view_type>::type>));
            };
        };
    }
}}

#endif

/* equal_to_impl.hpp
LSjbcxD2/hMBtCoJUvhl4A0E8J2jBWqFsNpleoBHZl1hnAHyhehCCOMSdMIynU26dq1LpbAwXBtP7zHO84AOizHUPabj9KqMyrv+bYq+HU2ySJAICG3sN4/QNMRjImMEx2KEYsU3mgL7Bp6DbB5PuGrqLMtOUoIOzvTAh+RyGWarCjOBrwwQtRtnsyv6TwPx8aNY5WbQZGDmY+ze0HwFtoqsRzGHnL7TithwPXl1fOxIKWqlYX+LDAwdBEmBLIO4syYrvVC1TvTy8cS0Qfo9RLhQAzYuw+PTg5/Dw/3L/RDg7T7bPyCn5cXRyU/Hw4CGxr12HyMa068byPCIrwEAYEgMPeRN1ghmgPLT2w3Roptn0QK1NoRbcgZtzc1i7wHLLF8KGMbehheYnXnoy/tR3rIPCtAUmY24zoqrKFPgSP97hh4KoIY81sgM/yco1YUSv8T4DX9UKjWzKz5y8dsMeKCWYwRVGBMpKBLsfwaGlicZ8AOaAkdTzga2H/tVNEJ7AdT6AbG49Po3IE80Gciig19kfrNjPIawr6wo3s+mejU9Q2xKYo4AkWc5nzrOAzvMpMM9FwiDkQQlnXTDBQT4AEajP64ShXhDitTDu2uNy+PLzfXCV2CvSJQ7VvmidyFoRPiM5ucnafJ2zsX6
*/