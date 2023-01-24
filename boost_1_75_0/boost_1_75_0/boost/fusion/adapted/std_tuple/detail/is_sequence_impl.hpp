/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09242011_1744)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
Qhf4aKdQKwi6egkg99HKUb51RxSlLcixSOfINpuvlOvB5ZKsckmyXKVSrhU1TstDLSnfjzFvKAf7eIqW4Csh4CLlOHy/Q6ttybdsBTHiVseRDs1YIorXRotfm39tqRmfil8Z3tYW2jYAReSgzSrGJqDWcvqnqmbq1RbWqk8vzooEw114ZSyaKE9NaqRMDCfLP9yCmhc0y1kxNUIzYU+MsgfJaWxAC5JtUr41svrMLmv0BZF99AVxWpdvCyLBr6tkW8HvJesK4sBPqIrGEShp/CyGOZRO8oTCFqQ/NwUa2b+agxinUEG9eA/OfwbnASFg2jh6I+cByWU7n0s2qE1lnDmJMNxdoiXBkntxro4mdy7PJnLJOMF+iN/xUBIH1NeMb04NkWUzJ1VZRHzrdtMrCa1blmrdqDjO99qBzuNvYXPnahY5ymt+PlfgsdGEU7QB/QkpVNzeH2AWkAcFYHPQxHwoRXrFCYg3LpqhFIfiHd1x8lVMFMScvbX17EPxrCaOM0lF8sdehI5ML9Nvy5nJF6kUI+iImdyyQEw6NkGG83y36X0yTLxVO5kTnKyXrMvTTLNSvXgUpyCJNIeAmjsgsrfBN8vVvtnaTfbN0QhqulSrb1Kpbx56A/tmCwP6yC5K5S5Kt97CLuqG8H7rTecSrL3MKu9QaoGl/MtI1fttyTa99KEItQfSBHMo0vE2c9lDf66n5JJSpHtFsEjD
*/