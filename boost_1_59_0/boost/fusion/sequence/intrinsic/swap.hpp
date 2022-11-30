/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SWAP_20070501_1956)
#define BOOST_FUSION_SWAP_20070501_1956

#include <boost/fusion/support/config.hpp>
#include <algorithm>

#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/view/zip_view.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/sequence/intrinsic/front.hpp>
#include <boost/fusion/sequence/intrinsic/back.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/mpl/and.hpp>

namespace boost { namespace fusion {

    namespace result_of
    {
        template<typename Seq1, typename Seq2>
        struct swap
            : enable_if<mpl::and_<
                  traits::is_sequence<Seq1>,
                  traits::is_sequence<Seq2>
              > > {};
    }

    namespace detail
    {
        struct swap
        {
            template<typename Elem>
            struct result
            {
                typedef void type;
            };

            template<typename Elem>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            void operator()(Elem const& e) const
            {
                using std::swap;
                swap(front(e), back(e));
            }
        };
    }

    template<typename Seq1, typename Seq2>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::swap<Seq1, Seq2>::type
    swap(Seq1& lhs, Seq2& rhs)
    {
        typedef vector<Seq1&, Seq2&> references;
        for_each(zip_view<references>(references(lhs, rhs)), detail::swap());
    }
}}

#endif

/* swap.hpp
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
*/