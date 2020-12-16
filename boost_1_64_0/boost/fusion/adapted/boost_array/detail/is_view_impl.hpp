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
uQpajTi8EWXQ0HUovylqXrwZ49p13hA1029BbogL8IegwYhL8PqvIU+7p/Bh0Ax7LcG927AOiDNfj5qp0CjbD/xmaJLdR/iz0Gh7bXwD1yC0DHEKfuBGXD+2H/ij30T+iNPfwryg1XZc+EnfwfPEln8X1zX0gM0N3g09bPu8A88GaAtiF776+7iXbZ9FXLPQNpvzpqi5BXoZcQj/wF2Yv+0TPhfagNiH3wfdYceF7/cDXG82T/gEaKNtAw/uxvV2BfYUPvKHuLYQu/DfQnHEyXuiZgrUD7EPP/hHuIYRZ+CD7sU9grgAv/E+rK3tBz79fqwt4uB+1D+IfbHnwvv8GGuNOAUv/ATridgJo+a9P8V62vbwTdBIxCH8FWiUbbMZa/Iz7BHiEtx5FOuCOAv/QBfW3OYD/zG0zOYAH/sY9tH2Ca/9OeZr5wIfvxXrgLhYiprfQBsQmyej5qZfYr9sm1/hmdaNdbPnPhs17/kN9suuCTyzDftl5wJvfh77hdiD3wg9ZXOGvwhtsX2+EDUfhuJXIjf4FOhV2x5+J7TNtofv9iLWBW2S8BHQyyjPwldBfVEewMvQEMROGa8LUH/EWfgiqB9iH/4gdCjiEnyvl7AXtk/4MdAwxC58BTTU9gn/2G+x/rYfePAy1h9x6vdRMxkaidiDfwMahbgIfxaab3P4Q9QMhGYgTsPHQ+tsDvBbodW2PXz3P2LNbZ/wtX/GetocXomafV7H/W7bwF+Dlto+34ia46D1Nh/4KmiZzRO+Gdpg5wXfGouZbTaOx8xTdTHThbiQiJnHoMRVWPP6mNkfMohT8PiuMeMg9uC/gTKInT4xcwSURJyFL4IaEPvw56Bm289uMbMKSiMuwd3dY6YJcQB/HGpEXIYfuEcM75MwFvw1qMXGTswUoCziED5kz5jJ2bHgM/vGTB5xeu+YOWsf9Iu4CB+4b8x4tj18xX4x02rL4cPeFzMb7bjwffvFzN323H6o3x/zt30mY6b+wJh52LaHz/twzLxqcxsQMy8PxPwDtB8UMyMPj5kHUF6C9xwVM3fYNfkc1qEZ62nbw686HufY9cnEzL3QFrsOw2PmAGidnRd8OLTBjgu/EFpvc4Mv+3LMDA5w7slYP6hPgDbwy6G+iAvwkafGzCibz2kxs/h0rAviEvxXWdQhTp0RM+eMjpmh9twxMbPPBMwfcWYi8oJGI05OipmjoH62HH42dChiH3471B9xCH8dWmbzmRwzn4Ym2fbwkVORs+1/WswcNCNmViMO4OfNxBwRF+FPQksRl+F7zoqZGXZc+DHQfHsu/CLoDnsufAu0wbaHb5uNvbBzyWM95mO/7HwXxMwrC1BnyxfGzPEe9sLOHT5wMfbR5gaftgR92Rzgj0IbbRv47mdjH6/GGsL3Wor9RXkIX3AO1iVAObx5GdYEbcrLcc1ejDVBnF2FfqAhiM1qrN8a5IS4CP/EWqyzbQPf5RJcq4jT8D9AwxCn2mJm3OVYT1u+LmbOgPogduGXQn1tPvAnINeWXxEzT0M52/5KtIeKiD34OqjDtoc/ZMuvQZ7wPlehHHEKPhwyiF34MqjHtoc/BJWuRXt4nwD3O+Ik/CgoQJyFz4faEPvw2yAPcQjfBuURm6txDUMlmxt8FNRlc4ZfCgUYtwjfCrUhdq6JmUFQEnEGPglqQOzBr4bS16I9fAvUZHOD73st+kebNPx0qAtxAN8EZdGmBH8VarH5r8e1BAV2/eGLoDbEPvw2KItzQ/g2qAWxuQ75Q0Wcm4aPgjoQu/CVkIc2BfgDUB5xCR65HnkiTsKHQE12LvA5kMG5Afz7UA/KQ/ifoKTN7YaY+QzUgDgDXw51IrcA/riN7d4=
*/