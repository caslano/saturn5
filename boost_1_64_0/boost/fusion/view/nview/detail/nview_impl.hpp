/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_NVIEW_IMPL_17122014_1948
#define BOOST_FUSION_NVIEW_IMPL_17122014_1948

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/view/nview/detail/cpp03/nview_impl.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, int ...I>
        struct as_nview
        {
            typedef vector<mpl::int_<I>...> index_type;
            typedef nview<Sequence, index_type> type;
        };
    }

    template <int ...I, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline nview<Sequence, vector<mpl::int_<I>...> >
    as_nview(Sequence& s)
    {
        typedef vector<mpl::int_<I>...> index_type;
        return nview<Sequence, index_type>(s);
    }
}}

#endif
#endif


/* nview_impl.hpp
d5RfnajujhPC8hDaL1mkIDgt+ZDKSPI+5w0LPPHk0spLDiNVkfiWNpf/evzPGdtjRG34POhy3LOncPrYqmnmDBWumHJeVGllhIeWfOXiTdhLMdhAkkzjZyYDP1zcGKJGeO+JCJOxlCnAA149pEWaAJPtrh3y2fdY9Y9CQow4SEdsIzfFgkHrkRSKZW096kN4eCqpDhHHTYe8seM4097xoxwNfIKvVr4UkwimThyQkhYxsaZIc3KDwtvyARAxZSICG3BGuA7USmvqfGCReqyhRCtQeqj/Gvm5rvwJmRIWV/eAd2MagWlLqs/Ni9rrPPODK0Jz3AHpauPP9OEXsTO+wcESsvBw3GCcqv3fz8WluWZj6Ex0gmKSLrEd3DjSBcuvNRYfBdks5Mw9uzvgGAUOiOOuNrMZtjskEoldpLHgvEjmzkGhXIbizrEJ5KswZ29ULb6rGX8fDg08qFUjhAjlD7YGduUsk029eWLZRGSg9Nusn5ffaIihOS5c6AmUV76Fc0cSIXYH3YNAyHxOjQwELcDE5a6JTvQO0AWjgggeQoDB9hWhLVelCs7ocA==
*/