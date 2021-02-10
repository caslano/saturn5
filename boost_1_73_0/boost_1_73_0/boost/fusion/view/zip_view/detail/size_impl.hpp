/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SIZE_IMPL_20060124_0800)
#define FUSION_SIZE_IMPL_20060124_0800

namespace boost { namespace fusion {
    
    struct zip_view_tag;

    namespace extension
    {
        template<typename Sequence>
        struct size;

        template<typename Tag>
        struct size_impl;

        template<>
        struct size_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::size type;
            };
        };
    }
}}

#endif

/* size_impl.hpp
sxysa82Bjl1KdNAZqHLecMzm0tNGCPsmLqUILSRnIStgIqpeU12anWa9nNb9YTPAqstU8F5OYpEDLhiEr7DEZ8Tz2jLZ7TfHOp9VKV4uDmgUsSJdBbwURFXiWam9xtc9HiaunvldwKE9l4OJ0YhXFXcx3aokgVYGWpOzOjc8Ga4y6VbnqATAiggLM2/1/N7Afe/YuueXszl3vuUKoc7Ey7wxaZU4D7nAPEdq+EAcBjxe1w+S/g1g+E7bPNJDtsq7TTb/Z2HODGf9/xLo3gplCtedtfPL8JACY2fd48GjVvgha7HbFt9Y1zV36PMXfy0JXaYUpkRTjy/Pzo4ZjzIGpMvZ0G9wbzIGCM4aETbj1PwOPXWp1zFGFv+c53YI8VzT91kQl3mWV1xKukAm65WCXzHs6BvwwGCEF1g98GqGKrDlCvY8ueGhrN1kWM1DO/Y0aiWI6y0BU+MAcCxLh0mBgJltBP/tyLV6BO/qee2af4Geuz7+ltjhQ7HDLTkkTWAb2WS8HM8uhoMtzq8tN3Ha4Pplqa9DT5/SL4/NlE6zrfDC61aR5UK54F2F8cFuDmvrwGaEIKHZkKD2U1s6WEuWCGgJDgPt5cESeaGBT3SNzpuOuS8kntRJd2PTlCLTFlcwNedTRD2d+/PBRYde
*/