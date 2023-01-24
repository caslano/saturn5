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
f7wcrvYhmQrjYz65aWZX6IR02jxaLdGHRI+foFAYz69W4D4o9f5b+HG9Jebji6C9SWvjeHu4Rsdea7TwXnsi8tjG7gZRxIrLsNPE/MqZiQZpiivmQ4GIs+JardtHVczTroZVrNKuHHLhAKPFG2b2lDaKFyO0tniiWddIYsVHnB4+m1JgaU0PJ1xhUBxhfX0obAu0WIUlDoRpkR0Pc4AeswspEwaCXKZfEInCZt/DgRYgyg9QrqIEGdCZXzk9qyJHuxQCmP2jItW47YpiRwxUFobXx5E4rinNJjhCSjxQFTSBqXmgbHwjCOsXiYXN3aHT6oUAg7LhhVhTuUWrafFMvH1au51uR/8X+FIU/r7ItvF4d1MY/cMq3tXfd6t4DVNpysPTS/PrS52Cc3P4OqhgAw4SgKKyNDsE/dZVWELJbJdVnqhfC0hegu0mYkPYHRwD1RxTAAdCRbr2LrKrAgNjU3v3VOCavSP8VuQa+K1r4vgtfAurydG+9SeJFfdD74aRtBWztKdC+WLylCxYEsbcsBUn9NKd4dmr4fvxWVPss5pwkZl8RnvnYrd8vMhWcKI7vLZUhvEIiBhoFoWFg/jVHTPm8dGKDS0kQfeVfrukC97u028XqShdCkV5ft1JHGF9oU9zoENHbQ5/RyxxubCowqQxyXN0EefLD4Qtvn4LWlDkCuW4FIPvvzbh992FJe+ZOE+kh9fwN6MP0huo
*/