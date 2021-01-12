/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_IS_SEQUENCE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct is_sequence_impl;

    template<>
    struct is_sequence_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : mpl::true_
        {};
    };
}}}

#endif

/* is_sequence_impl.hpp
ulYGpqVyvruabev3YvZbTSkPyvF8Ffc1Aou8qmgtBdic2p/M/lPi3yWZNW1M/pg5Q78S9x3VbPyTcsC8Cw5hvqA++1z7gHN84p8Pk6eG6Df8X9A4fBaZl4O5U+19fSn963wmdnaqO0/hj3fZrWnyuZzP9UwTdXvAbwG+JXbqm33vb+jsmIMmD4/MqHnnHw9vTydOEXl3/oPPoVcZ6s7XvbLUAx99a3AgPDqb63WOi0eaYRWF
*/