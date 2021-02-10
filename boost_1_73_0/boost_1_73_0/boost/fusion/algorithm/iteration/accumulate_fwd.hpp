/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ACCUMULATE_FWD_HPP_INCLUDED)
#define BOOST_FUSION_ACCUMULATE_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename State, typename F>
        struct accumulate;
    }

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence, State const, F>::type
    accumulate(Sequence& seq, State const& state, F f);

    template <typename Sequence, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::accumulate<Sequence const, State const, F>::type
    accumulate(Sequence const& seq, State const& state, F f);
}}

#endif


/* accumulate_fwd.hpp
rl8MGLu8M+vN+fWAxXFp4warXc7cnvN7LM1dDuSt7xrkdmjeHmt3dcnDkyhWFKqPEZ1kOKyp89JqPUzvQR3aH0tzN15n5AZoFyku8a6fht4EingfEXXfm8uO0h3sM+RhH1SA7SFr6aqNvCkDpq3/CuYiGyel2Utr6hZGo5RgrM/Dz36ZCwK68xZWHCZgjatqEym7oivcRsNIETnWqQ/sbpErwggzzAF0nocwcZkRuTsxVrM+RWH+PfbY7sv81GamfsrLh6Ev0GJLyabe301joH5fFmePHPh4o9OgY8Yjqwfmn5GMgbpnjHRGoPONAZNm6eD06qjibC8i7EFiXBFhpFxlupe1Y2XvYqA0hvQR/NmootZLglV1fuqdaCM5xmbbHFSt8R4tn45SZxyl3Im78Ikiv43DktK2vLh7y5bFOKlAH8ifXJCfdXW7MGZYcZFF7risshHFR8Mu6g1htJ4KVzZIpsslE+aPBW6vw9bTWKfY0y2R7WEOO8IKnxq/UZnORlnfMMxGMh5AJYnSrs6horgV57h/8yNzsoahskCyzSFWtU28HIk9dsgRCbKqoxKuhceceS7sQjS/uWnJ2gath/QJp8eBDi/iLLGokTCgGQ8GxfN15ERvtkE7xD7rfBZ8ZrCdyGN8anAstwPZ
*/