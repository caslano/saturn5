/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_COPY_02162011_2308)
#define FUSION_COPY_02162011_2308

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/detail/equal_to.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4100) // unreferenced formal parameter
#endif

namespace boost { namespace fusion
{
    namespace detail
    {
        template <typename Seq1, typename Seq2>
        struct sequence_copy
        {
            typedef typename result_of::end<Seq1>::type end1_type;
            typedef typename result_of::end<Seq2>::type end2_type;

            template <typename I1, typename I2>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static void
            call(I1 const&, I2 const&, mpl::true_)
            {
            }

            template <typename I1, typename I2>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static void
            call(I1 const& src, I2 const& dest, mpl::false_)
            {
                *dest = *src;
                call(fusion::next(src), fusion::next(dest));
            }

            template <typename I1, typename I2>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static void
            call(I1 const& src, I2 const& dest)
            {
                typename result_of::equal_to<I1, end1_type>::type eq;
                return call(src, dest, eq);
            }
        };
    }

    namespace result_of
    {
        template <typename Seq1, typename Seq2>
        struct copy
            : enable_if<mpl::and_<
                  traits::is_sequence<Seq1>,
                  traits::is_sequence<Seq2>
              > > {};
    }

    template <typename Seq1, typename Seq2>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::copy<Seq1 const, Seq2>::type
    copy(Seq1 const& src, Seq2& dest)
    {
        BOOST_STATIC_ASSERT(
            result_of::size<Seq1>::value <= result_of::size<Seq2>::value);

        detail::sequence_copy<
            Seq1 const, Seq2>::
            call(fusion::begin(src), fusion::begin(dest));
    }
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif

/* copy.hpp
b3WeoMmHhkaUDzFMPZ1OMFUjYUpKhkBXuxJJhyn0uJMeEypDfOPI9QMg83yjA1meciBCfNoFt4btyfyqH2yVKlJu9zlApx/ueKqwL2Qgk9XT5T0qPihVz0gEQt07Kc//MfFcuP/ETt2FM1VolnHWX8CZF5us9EKOG1jj4Eyvw+1fQD6wd6rnCeY+F8QWVvXis6Hu0nsDUWWlAujT1W5ipQLRbmVdri8mTUbAxiGsuyXiVg1TXM45K2SrOsMEblNn41xOEg+1nw/fx89udV5T951qXi++5X+f188S/o/n9StFm9dvzwqZ1wx17fzW5nVSUXvm9bcz25zX7rNwLjuJh9pIdHDcrIjzCvimfk8LfBM2r9+ObzGvzbbKdA2B2HBe3205r+RMQL0nHpnLqodxJV4Ond8vw+Z3rza/Q1vMb5o2v7tU70Mwv1+K1tU5/bD+ylcAF8Taql9EKhmFzaMKBJ4oInSZiXfLm6XgOTbXNyo+0A3kpCXdTS5SIU/uLt4Pu0CLPGRddtx8inVBNDImrRU0QuvywAxci5nioV78IL5PntEqvKd/fSp4H35z2LqcGsz/HdtOMH+inWD+n2oNzI+mIZjfIcD8TgHmheoeX2tgXnlTe8A8tm8rYA72n9PFJB4iZHzO9EhnKczhD7tONYdRN/3vOOMxy/8xznhunjaZr/UNwRklqr+6tckcPK49k7myT5s446dpOJXf
*/