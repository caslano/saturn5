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
MBspBm1tTa0xrAsw6cFxaePBEQzrfeuQ+yj2cHQnfO0pqfqjPoL5jkNYxQeCgmnlI5g93bRuG/U8l2H7RPcyKFgbxTBXcxLJp2H2xCfaYRdB2HV7rDT/pNGwQlp3AFNJF5WCmV1cRRJb3YVMOyxerFbz+0tYKWVpmQImr1tITDmAIdgpL+o+NLk3OAuTRWl97vZqFLTTkdQ4nWRP0bOih87QSaHHrFj4vTQuVtM6Jys3XzdMnAuFRfFFlRMncm3tKVdqR8LgudWwbqEg4jjWS1ImxVrHvI6wTZVMMWaPHrfpTCtb0VRHu5uIzr295ZiPMpzAuj1YyEPGKsKEPI7ZZbWUheMN4jBZOIxVB9jLVYMGbSmWGjF7MGVXBtjO+zsJjFr6PfjkQq9NVJ3bY5TFKXebrBE1dgUghGF1mJCjCtPVINy0Lqaqc2Hbk0brpteEIYrJdMJWPeZCGmFmagbIIGwqBg9RE5FyA3VVgNhpMn4BNcZT9GDAFrbbZVMyf0eIUQUZY+XH/QSYWwi3aa7cItrMGbbbFnmS8e057B8e88MDwz5owDOaH4Ez+dZuRDRLwSiWeudRJ5hTyVnhoR28oyRgTtfjOd6umbTHKG1MxTPF7dBGW5AVWdsvS57ReIQeJ5i7fNHHZrYnFNUS
*/