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