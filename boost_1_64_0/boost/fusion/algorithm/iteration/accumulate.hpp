/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ACCUMULATE_09172005_1032)
#define FUSION_ACCUMULATE_09172005_1032

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/iteration/accumulate_fwd.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename Sequence, typename State, typename F>
        struct accumulate
            : result_of::fold<Sequence, State, F>
        {};
    }

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence, State const, F>::type
    accumulate(Sequence& seq, State const& state, F f)
    {
        return fusion::fold(seq, state, f);
    }

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence const, State const, F>::type
    accumulate(Sequence const& seq, State const& state, F f)
    {
        return fusion::fold(seq, state, f);
    }
}}

#endif


/* accumulate.hpp
hpq6vjAXAurPWqvRdk/hJlJHY19jWPxfMVyreS1ExR1x1TeJg5+Xkyl3rMblk0c2+Eyw4DqeTnq5UEpi04U8EqzW37kMhaWEHEgbYcwHWc4LELryTIkv6xaLQic4E8h+nCON/9aocvXOgigdJY6y1ddxwz+Vu08xxYrEFwTYRJsc8L6xOjQXmp30oqlyJ6jZREdQaH7meWXKHDT6Qt/oYgBdXEbGIjdd+ngvb8uQypHYtpPTnA9Np352DGMxEobW0q2xPcg0gMAe7pjOCgln2235t7ZGZfyJqWpOXmdT+TQBtU4mrX7pk3ZZ+8MwhiSrjfCrv6uh2KA9QPnUe3Aj0+gW0S+KIwfeBoZ/1lLidJ64LbjlKvr1l2RhLJf1qtbVDHk8tfuOy9gBA22OgdCr92pGuHLvpvAia+fKeqtrZZHiNAif94qDiH1Qa/2lVbn6CRXJFQUbkwK9XsEsIM+pMXuhEMagzG6HCY192K/WgfKcBdeR9j6oe/uooEv78BaxJhFuBugTteLmg/kKY55iyfx6mGh4xIvbcAhetrtDhBPMhpezXBLItp5MEg==
*/