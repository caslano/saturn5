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
LLKj1/O3ylOv5SFvWt35RPRpF7CvUC0YUxyBz7FFzi8Abogq+KI3bn+N2JGoDRQu9X2YI+gNrgOsWl6Pn+SRFrLn7kzknpa60/i7rsavOhOjtOcpH88EhoF82Bh9GPlI1EFUsQfVjCF25U0L7fZykW9VxEvFk1pxr/VmPW+pGGeQtzal80IXQJ5/BiW1BwhdGEBmxTNg7slng4O96V3PQS0Fr6K+nOcqjN5uwxXjOow/MB8ACGjq5+Cee73dNnI8eqMdWsKo8TGMWrPe5Lw08oZBJsEHU6f7lvOrLEGlok5aFI+nPPxJZ3onxWU3WXhQ050sV84nM8gDro6MK9Gq8VeN9N8g+7sE+FMsHD0KOf6Ftzrr1HGe3WmLTZ71GWQDQM2BFaA/hcj63N9dPnETrfyNTZkO8hv0GwzhHoQq3U3sLnWlXP+h9/Z0s1rdCuM7Pw1+qEvnZJIf4/z4fuQnqUxNh3/apRNZJS8DzDHx6CkfWFXw0bwh0EGOB9nfKszEUaZ3VqTTsAXo6u3y/pag5jPqxpNTdv6F+KPSyRmCWhSsMaX+vrzIR1XJ2JlSPjf2fA7X99twJYTesEExLn5tnt8gR9tFL38NNIrxcOR3Z1kmkM2V9HWZ3v9+OX+5fOOz5ePt7gHucQnwtvZPG/lItqrYjzFmZSi6oFMm398xnTcwrOwg6Dz0lf0hfpvdnwKUrpltxsjxtuADtrTT
*/