/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_FACADE_09252006_1044)
#define FUSION_SEQUENCE_FACADE_09252006_1044

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct sequence_facade_tag;

    template <typename Derived, typename Category, typename IsView = mpl::false_>
    struct sequence_facade : sequence_base<Derived>
    {
        typedef fusion_sequence_tag tag;
        typedef sequence_facade_tag fusion_tag;
        typedef Derived derived_type;
        typedef Category category;
        typedef IsView is_view;
        typedef mpl::false_ is_segmented;
    };
}}

#endif

/* sequence_facade.hpp
0KKi3wWXFeakc3ri9IbGFPEN9NyFlPQMuZyRlpauF9Izxmb0yMR/9HAspXndUwoH5+SlOOsDOQVlDpadkpebp0TRI1WHO4sa6BXpZ3MLvay8tGBI//JCKCvIKyoYVlDUG8qGDigvyHVCiocUjcB/5WXgsrt0dQYU5OUXFqQ4f5blpDgloqN/3mAR3y27e+CzYs30s46x5/+DhfyCfjlDi8ohp6io56V5xYNLigoGFwwpL+6nn+h5abXcAqVlOSU=
*/