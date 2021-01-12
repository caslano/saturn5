/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_VIEW_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_VIEW_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_view_impl;

    template<>
    struct is_view_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : struct_is_view<typename remove_const<Seq>::type>
        {};
    };

    template <>
    struct is_view_impl<assoc_struct_tag>
      : is_view_impl<struct_tag>
    {};
}}}

#endif

/* is_view_impl.hpp
HQeZtZIB8vwO7PioNydaoTttMmbM1Xj3wevE3CjO+7HD5uonZBcWhNJ9tpgZQ83ZXN23rQdF7xLiNAr3vWFzDwUmTVeJmS7sUYw1fd/doucz/bLTRNiZ8xjXltVmE3/oSfyVGGP0r6/z5FGMY5W3Yr/2e6E0JSOUev/phWLuGe8jnmg7WEeLXVzqFuUx6WH0w8YCttxFWlQQXsdeqf1J7dO6uhUT7pYZG+flZ03HNToXqdqP
*/