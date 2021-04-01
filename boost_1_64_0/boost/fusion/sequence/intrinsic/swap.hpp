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
9E9GBrzTNf2ENsx/wJXRzctv2hWYrAHoMCU8+KQR+zUrrUrBpM32SOeAL2v54okznCLBZXNjFtAIL2AtctDBFbVE/e0bb2WWx81GZ5GWsv6HInpo2abutt253gzqQ87rNLAZAw7EXxmgyuxlUJiGEmB2MAK/upYz4t67DzGzFxujQTE9tQy1ZaVXAMi30HQscytkVYce3u30/qo4/qyEXCKom0/QiYu+E7i9gbYJTUFzWPAmQcjpgz/Z6Wc83mnyhCkLF9Rm1pAL5J8xHUg8Dc+fK2g9qhSE9HrylaUjbV6qlPitVThBuEDM65rs1bnNAGbWRM4HVWCI/A1kBqn104C9jOM+aamMTY7khDwF1xsiJSHSRmUH/VoNeb6RjaE/Yd025onWBCqaBi3J/UC7Uw5de22iSDl0EphWNON1mn0LiL+tKNrC13edzNRwEr/xOU+CK7myXsj5B3nWMmehxLUKuIx4E9ZiIlD3oQhgOLDockvajat9KCLXKW/QXw6D6jnQ7ZYT3eH1vvuiso9l4qcsGG85OdTsTZe2mN18jrkVJAViqJFVcz3INQ==
*/