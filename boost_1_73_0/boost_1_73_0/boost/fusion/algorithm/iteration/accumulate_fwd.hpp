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
r2DbBHtRsDcFe1swJ2CxYMBipYKNEmy8YBWCTRdshmDrBFsvmP58BAthJb5vSJKPVxQo7GzaH3M/JEWxs9TohEng2GVZBLOi/pbCXVA63X7dcTMO1/VW0+j+fHXpqBKc0+uWAXRf0jfCYlvMaJGJycm/Oonx+HdC8oCTKIDB/O0gYtlWU4G9Y119oSTOx9/eyuenjII9Y+94SmQjcQpO2alPATPaL1KmwAilNnU7xhKvb6if+DL7WUjqsQcpOwM=
*/