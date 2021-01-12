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
BuUWhNYeRkp8LCP2o8ye2GOi9xhzLlWYFfO4pAXmjDopfO9Hdj7NafheykQxE0Bt/FDibuk4eZffmE8RdU2z1pwgam481LlFn6gbMYP7iP26HUWaXaBmeaZuhcLL9nlCGz5X/pyYSfxd+aEwGDZnV/TEUNhOSfx6zF2xZ0Qdh9uojX/e5PawDcav6Xz7N80T4FzWVhpvwbldHStpuCeI3YWkZ6zOEwf9OtvjQbeIVf+qrJw9
*/