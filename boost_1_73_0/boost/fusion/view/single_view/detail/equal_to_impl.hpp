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
+HeWr7302Lsh5p46jAfOp9skVG2bhxkixiFUH+KH8pthx9Tf0YUzd3Vnxr/vdXf39Zz34wuTp2FblsH1q8/aQkdRXW4WdcEetq2bOjNILoJiVuzuEm6CjsYV3LsyWtRP7E2+Kvgkgb0gWsBcG0rsPVWrS5s32s3aNoaKPQG4gMZGv7N7nb+TctdlrAd/8hbtHbutoyj/T6L8NIiaIoHrpJTlb53HnMQEQFU6dxfxufKTo/OH
*/