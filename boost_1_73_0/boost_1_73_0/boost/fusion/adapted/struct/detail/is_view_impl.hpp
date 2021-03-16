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
h1NulEpUl/ftLVqXm5hUm3x8Da6TGPcYLKFnEvMeYSWq2Ttj7i0v79S2tAI43j64mVi2p9YdsFmv7G76nTJr82ERbqp7J/dW9cZ26ofLWKC/VVlZBvNXuixzm5O5YPiQYo0Sc+sV/cwPrXMX9c/EKYa9i6bUY5Vd7e3QWJbKl0VElp5VYdoU4aoWGj152rAnFWlhBzECHNVunJWmJoA7tDrLE0TDgrnxBi0M4WUKNHYbDdMBmhAC1J8DqpbmR28=
*/