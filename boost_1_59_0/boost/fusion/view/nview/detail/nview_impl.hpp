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
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
*/