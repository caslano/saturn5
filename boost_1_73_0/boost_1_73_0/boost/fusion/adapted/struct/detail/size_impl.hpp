/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_SIZE_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template <>
    struct size_impl<struct_tag>
    {
        template <typename Seq>
        struct apply
          : struct_size<typename remove_const<Seq>::type>
        {};
    };

    template <>
    struct size_impl<assoc_struct_tag>
      : size_impl<struct_tag>
    {};
}}}

#endif

/* size_impl.hpp
jsXgVrc0B9hskwrpfs3lHpFyGeEll8O2lx5fUkeFTOvOJtz6xJrybQRV9Z7dWdNb5dh+XBpzpxWT6BnriZeY4rA09Py02HtRI5qKpeLzSMpS8ZjSlor/S52tp/S0UI7Yj7RN91sw+FM6dSalNutUA6We1qnLlTU2/kJZKQDSe7oU8BeVaYDcoNgACePkyvQ+37qoNXFYA6TX4GjdyPMsu0ohIGMD/bCGcmIhsEa6kgjB3OPaSEvLl143hma8Mno=
*/