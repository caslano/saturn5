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
eb+diSEZl3j+Z5y7tVeSDhrGJE1fSQP1O3ph9yWKHyVNRuIncy9LWJrs1sy6ALGR+bIeDMPSJK9gljNpmzEhx6W903i+XszPs5q5r4Woe3aZ44hDYqaKnjFu1sIom+eOs/NZ19U+uezF54+aRan9tWah/pp21M4vDzZz74+55jk1a+os0385j/PQz6f/EuyTHmpsyR8wZzWtdt4SCuN0oj97nFx7Pp39OOcXVuy7zYW6hRWz
*/