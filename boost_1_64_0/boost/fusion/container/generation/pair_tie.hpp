/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined (BOOST_FUSION_PAIR_TIE_20060812_2058)
#define BOOST_FUSION_PAIR_TIE_20060812_2058

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion {

    template<typename Key, typename T>
    struct pair;

    namespace result_of
    {
        template<typename Key, typename T>
        struct pair_tie
        {
            typedef fusion::pair<Key, T&> type;
        };
    }

    template<typename Key, typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename disable_if<is_const<T>, typename result_of::pair_tie<Key, T>::type>::type
    pair_tie(T& t)
    {
        return typename result_of::pair_tie<Key, T>::type(t);
    }

    template<typename Key, typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    typename result_of::pair_tie<Key, T const>::type
    pair_tie(T const& t)
    {
        return typename result_of::pair_tie<Key, T const>::type(t);
    }
}}

#endif

/* pair_tie.hpp
8isrxnwIIkMWg3yokR88z0e7ppXHfbDnI65hxRgeD1IeJa75iBodW7U4Ho6YSA0rlvdDbH9Phe1X7br/xaCsP3ETXyOkkXGcEv9Vlx+npKSRm9ghq/7Y2CGVxe2I81XmH74rbf5TTb9//sRVEz7bcfdrwb9fnwHjtv6qx/nwt+XzQNyjg06sywxb0GXPu9/+Mq+jN27H/1rcjmkjlPlDOt4169hHPz7addEt0c9fl9P/t8XtCDdJ/S22k3GePsipZ1KfoVQHV2JDXIVtcbVmHH+JrL/BYBz/Hnlm0QcYiB9iT9yL/XAf3oQHMBk/wlz8GFfiYVyHn+KLWIZl+Bn6sL9jWBu/wG74JfbCE3gTfo3j8CROwFN4L36HhXgaF+H3WIRncQ2ex7X4I6p9I6QeFm31wbq+EUtYrjEuxQBchl1xOfbCFTgYH8UR+Bgm4eOOZ8VJfSk+IuWofVZcD4nP0Rv7YB+MwHAch/2k/CKl/AZI+UVhMQ7G53AIluIw/AZHYB32NxK7Yxz2xlF4LY7GaByD6XgDZmICLsBxUn6JchxbTFIfio3lOJRyWS/HUS59T85gJzyLA/AcjsHzeAP+hJPwZ8zAX3AeXsSFWE3iYFTHtVgDN6MPHkRfPIy18Av0wwtYW+KQ1JHjrodXYH1n/qkfdZ9/f7meG2MnvAoHYFMcg83wBrwaJ2FzzMAWOA9b4kJsLflvI/lvK/lvJ/lvL/kPkvx3kvwHS/47S/67Sv67Sf4tJqk3xSy5TutimuS/WPL/tOR/PXbGZ7A/bsBIfFaOp0SOZyMm4iaciJsxHZ+X/c4mFcl+n5P91ker7HeL7Pdl2e8rUm6vyX5KZT9vSLltk3J7U8rtLSm3t3EVvoPFuAufwd2SjxKT1G3it5KPRsg6tilZ3kcpGIyp2APNOAgn4lCchMmYLseZgXPxVpyP2ViEOfgkWvA1nIKvYy7uxTzcj1b8BKfilzgNv8ICyXdgNUddpOmCXHet5RpUpq3yvnkdO+EbOAC34xh8E834L5yEO3A67sQH8G2ch7twI+7GLbgHd+OHuA/34o+4T8bH78dWeAA74kHshB9jZzyEvfETTMdPMReP4MNYhsvwKD6Nx/AlPI678XM8gF/gIfwav8Vv8DSexHN4yhGXQOou8VaDuAQX5Dr7BYPxIqZijepq+fig41l7sh2rbEf7rL1I9tcEB2ArjMJQjMaeOAgH4WAcgkPwZozBRByKqRiLWTgcc3CEHMcJk9QjYpGc76uVzzuS/OydHYhNsAc2w1HYHBMwADOxBc7HVrgKA3EDtsZt2BbfxHb4FXbAf2MQ/oDB+At2xhZK/SZ2xG7YHUPwGgzFa7EHpmAYZmAfnIx98UHsh49gBC7Ha+V4001Sb4jTpbzrYKIc7wPy/WIudsB5GIzz8Vp8EEfgAkzBhWjBRZiLD6EVF/+HvbuBi6LMAziO4guZFpUpKiq+ixqCcorvqKioiKugotkBAgqdwgqL4kuJZYqlhvmSXlpcWmJZR2pqlxpdVqZm9nZ5nhWVvVuRvXmd3d1vdv+7Ozs7w+6q1b3sfO65r2yzz/PMM7OzOzPP839QjhO5X8i+0jlOdkv8iifxBtyD/XAvxuI+qfcGklny+UjyCcYVkk99mYv2SgzHhjgYr8IkvBon4DU4A6/FHGyMK/F6XI3N8AFsjg9jCzyCLfE4huFpbIPvYVu0xb2Se3n4rE7cq3Fy3kjGcJyAg3ESJmEKZuFknIE34jycinfhTbgSM/AJzMRdOB3/hNm4H9km+f6R+3X4uc73zwL5fC7ECLwFJ+KtOB8X4a24GNfhbbgHb8cDuBTfw2Vo3R8o8efkHh2fQZ34czPl85w=
*/