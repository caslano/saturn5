/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PUSH_FRONT_07162005_0749)
#define FUSION_PUSH_FRONT_07162005_0749

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/single_view/single_view.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct push_front
        {
            typedef fusion::single_view<typename detail::as_fusion_element<T>::type> single_view;
            typedef joint_view<single_view const, Sequence> type;
        };
    }

    template <typename Sequence, typename T>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , result_of::push_front<Sequence const, T>
        >::type
    push_front(Sequence const& seq, T const& x)
    {
        typedef typename result_of::push_front<Sequence const, T> push_front;
        typedef typename push_front::single_view single_view; 
        typedef typename push_front::type result; 
        single_view x_(x);
        return result(x_, seq);
    }
}}

#endif


/* push_front.hpp
zw7mhSF+5ENc78J670r9E2v53VORdKeIDOZfhD58lu3HvIgGKbQffg/EfOaV1JX5+TFfpo1MoVyDSYfn+b3DYJZTmRaTiHSiMeW4yd9y+H/hDvLBTKa5uYM88CBxk8/c/Vku4iDzOsFng/2pd8KpG8uH2URjbmotwDp8diGFsqMP4ZZFPflTliG0KX5PVdIQuwjv+dQzeg2hXPzfI4syYhYxjM/yMBILmKaQuE64ejMPvjA9z9+WDmFaIp8YzLJcwAbeTDOUvDGAiCUaD6UcC1hmb5YDe/F7EAZhMqYTqUNZv8SeBbQBPKXojcQFomAo80mlPrwptyK/B2MqUWcYaTGAOnDvznIQXsQePgvlM9/utMftlIUynlE+y+LvpHF6lP/zNwvRi+03mc89+Sx4GMuPyZhOpPH3ZH7PHsb6ZB75mIPpfJ7N52eU9Uh4cGPbYCKWyCAOEjcJD250CyTSiF3ECcLpfdoEEUIsJ/KIy0Tjg8yDSCIyiROE0yGmJUKI5UQucZ5wP0xfTQQTS4ls4hShXKDyIkKIdCKHuEDU4YKVDxFJZBB5xAWizgd8TkQSy4kc4gxxk/A8RnmIUCKNyCRyiRPEdaLOcfIiggkLkU5kEwVEEeGez9+JACKSWExkEnlEIeH6IXkQvkQokUZsJHKJM4TTR/yd8CGCiSQindhFHCXOE8qFtcZELyKIsBDpRDZRQFwm3AooBxFEJBMbiYPEecL1E/oOIoCwEBlENpFPXCZcP6UMxGAilEgl1hK5xHniJtHgM9YFEUj8/+f/P///+d/6qUjMcHJW3ynTJyTewttP4uckRESp/02M7Rg+JyY2smOXTl06eU3rODexq1eXntrfknt4d0yMDkuIiuwYGRU+Z3rx3yMSUixJ8SHKiKHWf6bO7daJV16TRx8nn1pOoco50/08S7U3zElzVExEQnxi/LQkjzbj2nqMUYb8jJkfEzfdwy+eN3PHRiVwL2NArXhOjAfJeKVc8+NH7o8nVhNHe3J+87j1O4xgJWP/4CCG/x8+ZjSDwUaFMeR5eMrU0cMHl/mdHYd7qu/z1N5RZHg3aG3DezVjkrR3f8m7QCPDksLujCfbsba8D1vSemFl63Rq/TCmqbZ8sTKOQHUWphm64jHKE5pW8vKNGTSi1OWrwftm/J9Q3y3HaLIlLC8Wl6+cy+ulX17Dsl2QZWtFWMfgI46Td/a/2TsT+KiKM4CHGxVCghBuWCBAOAJJyAEIGE4DhBAgSMBoEpKFBDbJkmwwKGhUUFAUUFFArdEih2c8q5UqVm2t1Rq86oE2WrXUakvr3Wrt/+1+O/v2vbfJbhKPtsmvX//u8Ga+b+bNzHtv5puZi6zy5j6uDF3FHF8S/LklY7tLXkT3VNGdJ4+qfqK7L/IcuusD6tbyFLzeWKXXP8/HRG9f0dsHeR69ERcH0CvHxIdyVksg3Q5ZU52BRCFzkBfQHWepu8JU3r0b0W0z6Jb9e3X1xP8edO7gSeAcGYtbhhzV2q61PXIPgt+D2mhLmqF+GvcS1pfVbrHNKbatQV7CNtslAWyT+xTKefFm+6ChH0gWe7Z19CSwCOX94Xz4itZWfPasG5+bX1ioHYcc1vhZ4Vrbf3KTru3z+0++3wn6MzMzx/r2aC6ysNupytBRVgC9/dz7vcxnGEm/Sf3Tl4F2VIInPf1e1NGdZG8Gqa8Lkd9rfd9mXZ7lGAuiB1X2cm6Z2CbnXVvYb7Pot+ResOetuR39MpHnmZ9dtF2MCub8V2/ZTEr02TRBb5Oh78ruLHtdSP+VjrxOuaReaqFfHnahlI3ejjSLs/Iz/c76d5aps/L1zzGDzbaTZD0T0h/5CfKmVn8D2cwDLBg=
*/