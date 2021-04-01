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
gAs/J/wLiRaK4T3CcAB/gvfwPUFrn3NtvcbhHTub62gFBcC737jXbvb2YCHMRDkYgyvu1V/iyScNKg3H6cfGznZAbhAYO75NzU2Sptt6jbrm6REaV0r70PKIKWVp9F/4FGdHlT+bMAk9KzDXJvi7h2RzivgooUoNt543a/zmDjRrqWC92r170TfRGbC1EFZ/nyMyh3KNYpEwPE1znEDFmwC+53Sk4SmQyJuVZTwhqIgIBsb90AjL97Zd+N/vH+Ubo5QZ82xXoRNsuV4xl3HBNW0NFgdMxxJ8DWreS1TnGmym+Zh3+nLy0JhEGTUzD5aJAf5VgPM4XutnAIPy/sewcyJy+IWAujipQG67h2GC47sC/zqDth6ybjRTex8g7y562tFCVJK/bBc55+Gy9imUulvuo1rzy64YbFvb56LdFGgu/W2HLzy+UR3bZpIjXe6OzuZFOb71QS+7he3lVeiWKxr0WlW+SBR3r5m0wGWzAmePRSu+QHRsfoMaXUiuzx5ef5gJn6BeY/WTvcDhzpPGD5wO/FK6yNSondtAvSichXhIzUReNe+5+GIUzw==
*/