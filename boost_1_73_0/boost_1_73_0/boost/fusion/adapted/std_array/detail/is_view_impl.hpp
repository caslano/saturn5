/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_VIEW_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_VIEW_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<std_array_tag>
        {
            template<typename T>
            struct apply : mpl::false_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
dyc7mYP/LHWT3xz/x3pP0Bfylcrhf/maAEJPbiIuAeP7UWHWQcsJOD+wY2JHtNNkRzT5siAFG2J+EyrWonl3zHRAHBKyEzuhyeYdlVKD7/EjTXYYUokU09dRqTLIWfE7SAZreF6THYdUDI2vNDEYxPiWLC2L8OpvZPkNu6/JcprQOoO7dr4jy42yi2Q51KYkMzjddXPc0AQ4vgmoUCegQpVsIdgPwB4G+ynYU2DPgL0E9iew/wT7L7ALYF+BsXM=
*/