/*=============================================================================
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_OF_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct value_of_impl;

    template <>
    struct value_of_impl<struct_iterator_tag>
    {
        template <typename It>
        struct apply
          : access::struct_member<
                typename remove_const<typename It::seq_type>::type
              , It::index::value
            >
        {};
    };
}}}

#endif

/* value_of_impl.hpp
bqUGe3cgN/qegWyN/4tZ1iiXFijXb3iWYOcItkqw1YKt+CKLLt+ZG+MIfVtWfBHw5R1fXvnzTnr+4DfevKErvvj7N9hdZmGYn47QkwTYsHigXa8aqlNgueE6BWHiWJ2CGFGqU7MpdaJOLaHUyQO9gwVecZKvKS8xdCn9HhxvUd2U7UvaEm2z2xbEE206EPuiudSnPfvBO1rbWB4s9Fzt8A072DQsS1T2GrZ5t3oK47n8q+WhCDdvmCiuEjETxNA=
*/