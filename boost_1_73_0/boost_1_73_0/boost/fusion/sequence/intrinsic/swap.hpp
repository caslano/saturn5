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
avb3mvcd7ftmA6+y/LstHMD2bozNvQouD9FyuHSf78udPO9f6/vQKU65kNvwmO9+4Apc9u3vV2u9i1O8BBxPrztbGHLfvhXybhBQ2fYE1AublRBdtqOWZm6gPT46HbztDmuKSf2pqD3r6xRCQu7dMi/UDrpIsyFCbwMlM8UM51KdyqTLdTyijUo5qMzMsdVStSvcb6tpEdARVbjGLQTOw5bEzwv7QLWzsVxK3lRGl/N8janOKfbVm8WWb9Hi/Jmrapvl9EJMfjjA3Da05BML0f5/QwuRO/fsg1vEpCpcUnKxnopc21xex/we9xMWMqisjW6FXHNX/JdvZsgB9v3MiTGQa/livyzgeasTEq1wV18udP6pMxIfOGy15RUlpBwJnCXlbusoscy5Yud5/cAy/6m1xCJnUWqznk9+bSwj3acgIQqR8BxbZr4VQv9kSPtkOaMXsZ8X3q9GaVHS+hymfam6rxilIGHphFPg5AoJ+yocL6Vlq92DGwuKZjG3xQGd0iw3gsqLEU1tyL13OKLXyHOeMkMxrhfa8Jluc3kpUiVnXJpyiMPOF8fcvtd0udEmKcQ/J/NDIy6SdsRz3+3/soxTli5atLjOU3Up8IKZrWCeuyZGNmnc2VUN7qVuzp3MvFQicq8urH3269rc
*/