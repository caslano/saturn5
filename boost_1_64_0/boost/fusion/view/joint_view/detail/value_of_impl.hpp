/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_IMPL_07162005_0132)
#define FUSION_VALUE_IMPL_07162005_0132

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/detail/adapt_value_traits.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<joint_view_iterator_tag>
            : detail::adapt_value_traits {};
    }
}}

#endif



/* value_of_impl.hpp
Ur/m1GsxOrMXzMC5L8NZ+8EpLGQrPEIjCmQ3fD2LzUcfA37J3b21XfAOoO+8Fercr4tYQrKGE2ujVjlA5ZPv5btZrBBlgJ9/rih8al/Zwm+95Z1xHbyLs/bb212n4lP2E/Oy2UnYfr6h/MWWOXtJdKNXlImasLs5oDpqdQwUxZvtbwsTII6BfAH8UPwmjBWzwStUsSCc+JthBa25nlL5pu/tXtnsemw/d7DadVThR7KF33iFPsq/u/5fHbN0ypWKT/Wx6pbN+uH4xy+zHH5B0ZUS/dobjufT5rZ11/46W5smVHzKvtEZ2XTO+RzjnPNX3gw8idGplbP214TtmkCofPI7fjyb/Gr43tHgZbdNQA8CL3MH9DvOc9b+WK21mzsMAuYZpLez2TfIA+5IEVt/zHsS/dLbE8fABhf3uIgqWvW/NwgYa+F12WwI8mAa/yyYtEGi67w5yIMX3emCtWV2zaFUPo0DP2TTXd7nc+/Cdc/0kC38gmyh693pAbWhCquLYSqf+sAf2RAtULafO90/8+jnGEHxc0/dXTPOXfvjE8JVVvuAImDYA9Jz2BbkwYV8FXRW/3sl+pm3n2q1Qx6cZtUeJIo3dcEWOax1jmz/dK73fnriHRL91Buu7kd2ZwuHCtoVASh/O23Bn3jqvh7mu9gzl/WrtToEiOJNe8iuOexu1IUvFmevH0Gv0rVevvsxYHK01uocQOXTWqBLDrsTzx/xPaH7v5qK548+9iJpyq0MPE3dtL/+4J4HWpUARcCQgQNyyCY+w7CJf+S5PXMAZ6NCtfzDomHcoGHaRgty2NXIh0vhc2DairWypR96q1X8Jye+VKqO8GGdDYKEefagMIedgHy4jO+MhO/FMzgfeLFWqBdCnwja5kMF3E0aiYTL6A87vGhMxuRH8XU57FLkx+Xw+ezXlXtK9H2P4gS6iNeQrGh1JAInhyzFLWhEJjVG1vU57FTkx0x+S/JBP+BdXu95VwdQPv4DflRZsiM2IpM6ft6QQ3cGcwfUGSdeNUOia7xFKB9j/gN+JCyNHY3IpK4r5+Sw0ciPK/kew5gB+wkQdh4n/Hf9xVqck1QyjeQD+DEQ+XEV9zZbvRN6W73rTfNx98U9P6rDcScDCNGhNddNOXSmic+37Xa/KSZb/I43+7/rL1E344cgY9qigB8qJtI1Rkykt2kN1j7gICZxRVk8MbbCZlAkg4IhE3fkUEykWUZMpLe8M8knxx0PLA4WVL7hw35XDsVEutaIifSmNy1f3YfnsP22giJp5Ru692c5FBNpthET6Q1vjIoL5vD9WwyKZFAwZODrHPbizpIH18H3aL+7uTohTn2+peKCORwH7AVFMgiYumVuLuuO6/Hr4euZ9y5Fe8Qq8lcv9F2sPSaUwT/8sNgdGpMx12J75sK6W/LjBm6f2Ov93hJ9zZvnoe7gO/DXqqguq4BfpWX2DoKbJEw+bAI+qL2KOfB584zcnyS60mufruxUDu4PVpWM2ecDkTD2bnPJd5k7rnW/LXu+RF/12mRgT3GxZ4OVLLPVL6j4FF26Ty7t3d5k7N2u8O7piHuXsG/X2n774/y/xeuDDQrGvk2/XFaEPLgZPod/NPY12cpXvM/zcP0NfaGNMx4kLBntNQLbHY/5ZW+hcuEPMPv326gq2nJk1Mo3YgwPzmUPoQzcwrf0s7zvZQtf8toEUFcIOrjnSNXP1mGmlPJpXhyay/rhvsWtXG2YOONXlHyvAVs8IcNh++1pCAYBw4/l2Fx2PcoAP+jZ95nhGB/lBa/TLhgLAHxa93DHA0ve/AYBUy+oz6W9i3nG3sXzXokWR7SVMx7Y2rgwCJixtqfksiOwL9zOY2JMWVkj0ec=
*/