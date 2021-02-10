
#ifndef BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/O1_size_fwd.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct O1_size_impl< aux::list_tag >
{
    template< typename List > struct apply
        : List::size
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_O1_SIZE_HPP_INCLUDED

/* O1_size.hpp
Y3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NzE3VVQFAAG2SCRgTVPbbptAEH0fyf8wcmRVSksxjpPUK2Q1StMkzcVRTPNabWAwyLCL2CUJ/frOgrErIS4zZ8+cOTOEloyNpaElhLlKNT+21L7rOjFLuImiJ1ivLu/WpyCL4k9V648WQv+ACP3+0BEc4ZrqN6o9kycEYU1V0XI+kVb2RH7wNcDZdIqrO/ghLQmMGvqC0wU+6jdOBFMM5mK+EAy5foigpxPoBHqm+/BTuSW4lxx40Eme5pTsWIIT/NUoR88sMxFMB5arSG4EjmfBdHbqJfG5d7KYn83mi29juIhjqqz3LNWGjMDXlivBpVaWlPXuSW1sJvDMRRTFNtdKYFxoQ3tM1Fbk9H1YP7NlAT8bpVovI8mqWjJ8AXip1h7b1PtwhCXZTCc4w9xg7yxKs83VBlNdY8N9fq6kMc5eCPuu4zJZwnAOHASbvyc1DDis5t1LCa8y3pJKKl1bnDjPn1bPERf/jyf0d5PpRnZZ5K6RfmRx97Ecyi7B6HhrTiGzttqTcFrJkrdlJ75bCZSNzRjSZ5jXynpDFiV2UmwmLb5r9cnd6y2+59xL4+LUe4Cl3OQxYBjrspSKZbqawvcnN6t1dPskAv88OEfvA3tJ
*/