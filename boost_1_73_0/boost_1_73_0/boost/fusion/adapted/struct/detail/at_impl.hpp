/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct at_impl;

    template <>
    struct at_impl<struct_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : access::struct_member<
                typename remove_const<Seq>::type
              , N::value
            >::template apply<Seq>
        {};
    };

    template <>
    struct at_impl<assoc_struct_tag>
      : at_impl<struct_tag>
    {};
}}}

#endif

/* at_impl.hpp
3VZbiLAb9iu41kmUxup6f4PitcYPrXv1p/S/J/mpvkRyA04N4nPH2p5s05uTuBCcrozz6BPYjbTpZgeukQaTUsGxLOD1LcaOwOuJJ8ou3hJzb9Bnw6mPLlK+2z3Q3XfF6fkjuvTV+bi4uokV1Ln1udX5j8YC9K/SyX+0AEFcR9Hj1vWcW1pi3ueKEu2YfDOLyXBSo2/tuXF53973zVHBUsPQWGVtJ2cq9vs3QA8nbEVaoax4Dacyxm+HnAFPKaw=
*/