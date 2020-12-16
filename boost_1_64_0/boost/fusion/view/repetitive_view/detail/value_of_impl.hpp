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
URa3YXTrvcICW3RgZGZfvWw67QXbZV+jyb5G86DlYUZ9jeZXMdiBfc2M+hrNjhYrjfU1zmu0BMX24jhkMe/U0hihRTHjc96wE+c8Mzq7odlSGJ3P0BwpjH5bB82JNpLZuZL1kml+/q4DO7OBSTWoTCdaHDMIBmbRWkHLxkz+ZhTml8IKT15Qh/Lbhfu8NPY3xP3BjrZasX3ghMcFh84RZt2tg+1aaQuG384izL1Pedas2MAxlnhhtv14HWPWefTYssLgAI67NDbuGIcWy4zGFs2JZtRIS+gasZb6xYfnLCVuP+bnKj1zBeV+EOc1M9OF83PIDuF6YNa6x9o7wgJo+ZlNsZ87R3GHQ638/qdbhNlTWHzG27tpbNGimLXKVSGS9jO01sxKNZsaQfUdCY1rdr1pd5qfaHpmfL92pIhbtWS5nJ9oOmb03BTNhTaR2drN9e9SfUd1MJhZm6ae+zQOaB15mTkrdKC2HNPBMmZnrpTtT+vheGjcIN8H2ss9aHeZ7Ri0yCvMd0IHOTTS8lS01qF2ngqNu5kxO42747QOBjL7MmjHGVpHaGuYBYZecFN+Z3TQn9mv1S+dpf48GzrublO2OpQDWic+DrPK/EK5n8M9i9mfmWtTW9xoJq20qNv/xFN+F2gdoYVexxLRCjHj1yoPWiwzvn8G0LYpdgBt7/o0oyn3i3gtZnbaUHAX9eclHeTTSmsc8bCzMLiqg5IgbfH9+Lm0VtAqM9vcJ/km5Y42kZm58bliFHcN9zpmAy9Yg5Q7WnuNtA9t+tBasd7AZ5zMru9+8JDm0k3ljKnYZ33miWLvSbylg2glPx84YWXT/YuFGe7is9FwabXvuo8LczyUz/IOor19P7m/MA9aAWa5ux5dJcyP1oDZz6tn3xZmf6SDHszulDhXl+JS2NmRZ3tSDo91MIBZn4v6q8LgD5xL0kL3ZLRYMr4nlwAnWnfFDkFP6LXVmF4YPNFBGmabEvrsEmZAy5fmmx1GO/Fo73g697zUAUR9syNQHLbHt19I7wJGKJr2mx3FTN2j8gwgSxcFQYu0IufbZgbxbuy8UZBdiTv2//PnndnK/UoZcBSOgmSlvuNom1o26/LNbOCsHAWxYd/sBCTDxmqFgmRVo+CMQVr859P9yZpGwT8lyTDfm9Fkc6PgeHFp/c8WjRDmvRoFhVl96Zy7osluRkFFVl9EMJNB5ACvouCWMj9PYg4l2l6h36/yvImCu4qdwn767+D1x8Ls76OgC0h7eWdTa+W5MPjRSih2GschbtaDUsIMH6KgSLi0NVfKp/1m7cDxOQrSfffNzkASRL4f2+SbFYdAAT08jPhmZ3FueceIe+ZeYC+qhzBlTpyDsrDl8fmW9LsmpfSwN/KbnQcnjK/Ta4sYd59dD44M38wPbWHU0VnKfEmGYH099FRyv4D/H7Y701mROzTU0/3YRSynS+GmAdHXiWji71cuYZwreG/BN8M2J+jpO0qXoQ/kW57mMa2VRnroyCzizNxuFIdWiBntyWhBtDrMNk2K3iLM0VgPTZnFL310UJgPbViEtFJtXj+h/aWVHpqAtCHTo/+lPau1HiKZ8d8BsKKJd2tdwUxnr63wTJi7nR5ya6VtchTMTuuvox5aZfpmV3GOpPPdPSrGD0bo6Zn4NfxXz7O1ZwlzocUxO7+h/RRhAbTqzBrcfPRcmN0Vai26vd0szIM2mpkjPv8kYY6ResjPrOiqK6WoLWh/aaT1ypq9rbDgaD2sYnb5hS4b5TdWDyeZOdY/G0HtHK8HH7MD754HhDkn6mECSBt0pfb3wqyT9PADs3KHdCcpDi21HDxoscyMudJSWwIqcYbJeljJbO78AYcoDm0sswg=
*/