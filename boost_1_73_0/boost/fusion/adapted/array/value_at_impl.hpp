/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_VALUE_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<po_array_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : remove_extent<Seq>
        {};
    };
}}}

#endif

/* value_at_impl.hpp
Rtpt1B02xJ3PCYf0oX0h/q/UcIRN/iJeKovKY3WAaWIvxexL1EDMp1ptcXcc+rZaN6gUfX1fCrG+nnNvEGNtyJXnECf3Ix8hsubQ2E3w/YS9Qtr2D/E1nt2ENRYXc4mL2Ptzh9j3mX7vm8Q82T4KGzvIXb3sBM2DhFTuM+CaW13G4o6YX0niFpfq13Cx39WML7SU86f7Yu7nGvfZTrr0jH1DJdtcr5xQtDH931nixxyXH+XG
*/