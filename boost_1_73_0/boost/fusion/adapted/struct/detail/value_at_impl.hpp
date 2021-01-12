/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_AT_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<struct_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : access::struct_member<typename remove_const<Seq>::type, N::value>
        {};
    };

    template <>
    struct value_at_impl<assoc_struct_tag>
      : value_at_impl<struct_tag>
    {};
}}}

#endif

/* value_at_impl.hpp
Zc+3l5Pn1cvMEyliJiVsHPLvrf+da45mhR7AlIVUQDKR0/g54UsTXzMmjJPrlUotA9XE7AirufsYTd3SuJN0ySiYmJ3tGndqVuJmoLyLe0MkrUJx00rMJLnXV1+6xr3pn9aT5wOs+ucY248Rc5VNn9tKpjyeR5/7HOURvfD5fokH014NFHMa3oixFgkmf2OoIKLgSCj1VSidiu/RczYLOs1SGePqG8XO5d7j9Hxu9USF5tFE
*/