/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_VIEW_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::false_
        {};
    };
}}}

#endif

/* is_view_impl.hpp
SpAojumRFLmCDjeduYfQ5Gzt7T1O/NF1eBn5wdBDmxbm6xmJWfBAxrEs3d0lkarpOpYSk2yTZmQ5acYJInOhB9OW7CR85WLLTWPhyJF1WuAqFeEplZbxMkf3a+T9lpVlM2q4AJrnuqD0hnJgTf+smH4wWIc6b82AQjjLaC4pimDIjg7mUMIVVYznok3fFhtDW7TagP1gFCb7IiYYsxdruYZ/JqVLqkcOzr5cZxOJVREu8yaxJSWVdtIi8DetxPFyhyMHA8UAZV6X0LkX7sBWj2CsGmqZ0A9x6IStiUoLxldOS52ROxvH1uOSBGHgQXfQMyKTaRiHw3AcWVdxPLFhpG/TOJo0g2zkjz0j5/3hXk/0nudWQ2PTeb8+IDnjTHWRtCzv6sMe/GPBtz2gDw7cx8WGzv0op7cExwt1UrHuoCFU7x/BR8JrUu3gxMa2Px1oapz8dH7+5uzsdDCAo/7LIHvu2w80x3sAPz++NlSk2XGEPU0NVchSIBkMVZBq682rkR608v81yx56QiucMs2HoZ0xT3E2jUiT0nfWv5aTM1MR97Prj90P/tiP55ZrGsWcT714Ng3ABGxNKfYFfoG0J14SfjISncjzwB1HIY7FD9Nv0wQdZDmWxfoPUEsDBAoAAAAIAC1nSlKlyrCO
*/