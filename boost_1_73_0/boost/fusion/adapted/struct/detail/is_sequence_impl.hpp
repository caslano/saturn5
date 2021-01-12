/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<struct_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };

    template <>
    struct is_sequence_impl<assoc_struct_tag>
      : is_sequence_impl<struct_tag>
    {};
}}}

#endif

/* is_sequence_impl.hpp
yR+b9STTR8mbksFAXOoj1/KsdmQ80oM6anzN4niLbxGfRoZJdeL2fPKM9UlxW1fWHGyimLnCulj7lfX1nVtranvV0l/VGxPf02mbkvxRwSpd3+/aLpl+0kXi9kVWRXX7fPukWr/zfve8UjW8Xo+Iz/A1yFO1Lfm7X19yl56X3CU8jZ3qfdzkrEKZUXJP6yT0ezh2cKEaqXoD4XFdg9Z0k3URSWu5G9v0p66R5yOtLu5rj9h3
*/