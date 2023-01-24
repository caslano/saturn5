/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BACK_09162005_0350)
#define FUSION_BACK_09162005_0350

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct back
            : result_of::deref<typename result_of::prior<typename result_of::end<Sequence>::type>::type>
        {};
    }
    
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::back<Sequence>::type
    back(Sequence& seq)
    {
        return *fusion::prior(fusion::end(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::back<Sequence const>::type
    back(Sequence const& seq)
    {
        return *fusion::prior(fusion::end(seq));
    }
}}

#endif

/* back.hpp
8QVzTiuu1PxXQL8F5SEv8IPZl4U/3QInMd2RWV9CKaUAfcSqXA9/hI/5okFbUIQFE07IlcKqEN2mURABfezQKNN9HjCKvKNW2QuVLAIeQ+5UJoI+tWz/UmdmQcF6c2BYUR5x/BZ4VW11wQ2CoGBor0WVvrFK/y5w9yQUUd5IJlNRvzG08STAH+VMKlmKr1RcvHg6vP/PaHrfGyY9ZX8qVtqYy3eaCgapy7YrG0GBLFik+m9SpiaTt4MUyDVhYJwaJcFKtaR52NaNceTAuEtiFg9L2QiiX1R3q9Y3oKqK1q44NMpjFPINCQh/JtS9InYfLadgWQuzTs7FnEzzUnQnCHJQVGuCVg+8UEbEaT2THhh2IwLtv16ZAJgpryTBz+0pILX69oPnJkDjF+hSx56CZXVKCkB9Yn+Pg4HDZuV21FWrIq9xIF6Fz1as0NYu6Sg3gzDPByWbnpDJzaMCHAUJJ+TZa65PNs1LcFSGcUTKwzF7yEwXnn/18I3rRN3ZLdIV5kURRQ7qryg8/kKrva1sHybbXH0aZ0H91fOxrw69f1x7FVDN/uug0kHwzrEH322Bd5htYlVI2UobbdZTY7hJqIteRrXniBRRzRpQLf4Co9qrY1r0wVRqDfEv/Z3lYjPq5JGuelnV/lOBDnmkk+MgZWyjoTErms2p3VwAcwxNLzBI/FZlXGcyYZOu10bUh586g6k9d4T7dOEL/3b/
*/