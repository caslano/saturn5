/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_VALUE_TRAITS_05062005_0859)
#define FUSION_ADAPT_VALUE_TRAITS_05062005_0859

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/value_of.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_value_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::value_of<typename Iterator::first_type>::type
            type;
        };
    };
}}}

#endif



/* adapt_value_traits.hpp
t+j3Phdxvm90PFYYv7sfcfzfMP/8xPryfdfbVa5vlxhXd9lvzt+9l5rvqv29De4nn3B87jXOtjiuk61PX3WcTrS/r3M/Vub6a146usf+nTh2XFbh/Bhyno8/H3Lfu8F1+13n9yHrol2HjRPrhUV1jqP9O+Ua7z/WcXzNOFnr/W40rm91Hf+z8ZHl/I34fPop+9v6ffmd5sO/G/frbPeQefss21dvPbBxgvdj/VdrHbDe1z8y
*/