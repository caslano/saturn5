/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::it_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
XK6gOCI/3O/Vleo7ioYLJE+1NNrkvW8a8aCRk2hGZQsGq+duhZysDYlnT93m6BN26A3yLZPO7tTnuI6IO9JghRNcHWTP4/D7g9CVVeIMCYG7ParIldfJA0Tv+iKgF3wZFE3dI2bwN2cs69Nyz557YfUmkrHWEMkSxloBq0/SnZ96h8fAo2frfPhaXR11JQ9iJtfmJHpYVuXXKuszXXH/pjEi07u9VgxqLeY0/o2w/PTkmSPQ911Z95Z9807nhl+isa/GeRoYoGUnx4mmZoAEACKjgxwfv1npElpzg9ZLCNEFq4/xIH3VCj6YXEm//F16I85vLdIUuV8d8LLRfL7FZcj6od//NsvO9DWX17Pv5CRCcftIXczhGRDwYGJq+yg89r7CVZJS9pgkWDpPQBovl60pgq5dHvDN/q8yJ4vO2r1ZIo5URK01L5xElvN0JBgBFM6UvJ0tg0Ibm5yV2p2IgEtg6dkuNshqPUBven06w5ZDI362jbEI5A9e2E7cas1av1zxkfOS+OKgfHFggrRj6CR+MEviAxvhpjDfgObfGMlfBLgAfbhsmVUz7A==
*/