/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_27122005_1256)
#define BOOST_FUSION_VALUE_AT_IMPL_27122005_1256

namespace boost { namespace fusion {
    
    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<boost_array_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename Sequence::value_type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
IU7fEsdnWeF6RuzDz7kV17ltU8B19W1cb3aOt2Ofv4u1RezC978Dedv+4bdCG20O8EF3Ym1tOXz3u7Cetv8fxM33oAdsG3jD3VgTmw98DrTFjgsffi/mbuP74uYr92N9bAxPPoD1tH3Cb4Vetf3ABz2IvbPl8Dk/xl7chDWEf+Mn2CPEZfjAEHuHOA0/H+qHOICf/BCuJ8Q+vOancXMo4hS8DRqMuAjffzPuEcQZ+M+goYjNw3GzEBpm+4FvhUbaseBH/Ax7b9vD6x/B9WzbwN+AJtn+H43j9QLrjzj7eNzcBs2wOcOTT+BatXnCT9mK+/FmzBE+oIR9vBnl8DFP4jmGuAB/Amqz48I/8Es812z/8Jt+hWsAbZyn4uZaqAlxCO/3dBxfC2Pv4J1QCuXpZ+LGhQooD+AHdeM6QbkP3/ps3JRsPs/FzXehHsQl+EG/wf6hjQff5/m46UC58wL2F2pEeRmefhHPCsRZ+EtQEnGyHDeLXoqbsu0Hftzv8My1574cN8dC7Tb/38fNXVBo5wXf8w/IFXESvvqPcXx+Hda/J24+B2Vt//CLoRbEAfyTf4qbHGIXfiWUt2v1Zzz3XsE8bfwqrmfIQ2xei5v3Q62IU/B7oMDmD7/odeSDuAivfQPrY/OHr4vXmA57bm2NmQcV7bjw/epqTKddT/hnEzX4nDusIfwZqGTb19eYM6E2Ww5/EvJt+S41ZirUZcvhh76nxoR2rL41ZhHUtAH9w4/au8akEbtwZ98a04zY7Fdjjnx/Dd6jYA0/UGNuPbAGn5eHcw+CQ1nbHn4lZBAX4E9APXaO8I9/qMYkUJ6BX3FwjUltQDn8XPzn3g22PXzwhzEe4iz8D1Cj7X9AjVkPJRGX4IMOqTFl9JmB33xojXFR7nykxgwZWGNyiEP4foNqjGfzgfc/vMbk7bzg6wdjHey48CM/UYPP80N7+AVNNfgsP6w//IIjavAzf8Tw2iOx/jYH+OlprL8996ga86XPYv1t//DnoNDmcDRygboQ+/A+QzF3xCn4uVDZ5gCPfa4G7+1QDl8Mtdly+C6fxz7acvi6YdhHxOnjsW4nYH1uwfUP/0MG64A4O7zGXA8NRlyE7/YVzB9xclSNmQYNRezDX4SGIXZOrTHToYQth98PjUJcgn/8NKy57RN+G2QQh/BvZ7FuiFNn1JhV0EjEBXjiq1g3Oxb8LshDXIb7Z9aY0TYfeHY01tCOBU+PwRoiduHfgoq2f/i6sVhDG8P3Ho81RGwm4DqHuhAH8PMnYq1sG/iuk7BWdlz4LKjdtoG/BPl2jpOxflCPbXMW2k7BXL6GPt0a83kXeSPOwg+divnaGD45j7VF7M2tMZ+eh7VF7MK750PoJ7MAOUNlu1bwQQuxL7YcvmoR5ob2ZXjtYtwXX0M5fC3UgrgA37QEa4HYObvGTDgX1yfi9Hm4N6G8HQu+FvIQB/B7oFbEIbzufNwjNjf4Q1CjHQv+xAWYL+LkhTXmt1Ab4tQy9L8ca2Xne1GN+SjUYecINyuw5rZ/+EtQwebj15iLoW7ERfiJKzFHOxb8HqgHcQl+1iqcfyv6X435QgnEBXjtGqyDHRd+KdRl+4G/AoW2/7U15gyo0/YJP/4SrDvO9eGfb8P634py+LjLcH8iLsEzJ9eaUYjLrbVm5Pm1ZhhiF/7n88GIMxfUmnEX1prBtg189rJaMwRxAB+wvNYMtW3gfS+qNctsDH8JchEnV9Sabfid/aWIsytrzR8PqjN32PIv1pmzoQ22H/iHhtWZjTY3eP/j6sxqmzP8vcfXmXWI0/A/QuvtmpxQZ06GQpsn/BaoC3ER/juohNjB7+UfAXXbfODLobIdC74Z6rE=
*/