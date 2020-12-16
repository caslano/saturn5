/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_JOINT_VIEW_07162005_0140)
#define FUSION_JOINT_VIEW_07162005_0140

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/joint_view/joint_view_fwd.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/view/joint_view/joint_view_iterator.hpp>
#include <boost/fusion/view/joint_view/detail/begin_impl.hpp>
#include <boost/fusion/view/joint_view/detail/end_impl.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;
    struct forward_traversal_tag;
    struct fusion_sequence_tag;

    template <typename Sequence1, typename Sequence2>
    struct joint_view : sequence_base<joint_view<Sequence1, Sequence2> >
    {
        typedef joint_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef typename
            mpl::eval_if<
                mpl::and_<
                    traits::is_associative<Sequence1>
                  , traits::is_associative<Sequence2>
                >
              , mpl::inherit2<forward_traversal_tag,associative_tag>
              , mpl::identity<forward_traversal_tag>
            >::type
        category;
        typedef mpl::true_ is_view;

        typedef typename result_of::begin<Sequence1>::type first_type;
        typedef typename result_of::end<Sequence1>::type last_type;
        typedef typename result_of::begin<Sequence2>::type concat_type;
        typedef typename result_of::end<Sequence2>::type concat_last_type;
        typedef typename mpl::int_<
            result_of::size<Sequence1>::value + result_of::size<Sequence2>::value>
        size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        joint_view(Sequence1& in_seq1, Sequence2& in_seq2)
            : seq1(in_seq1)
            , seq2(in_seq2)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq1); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        concat_type concat() const { return fusion::begin(seq2); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        concat_last_type concat_last() const { return fusion::end(seq2); }

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(joint_view& operator= (joint_view const&))

    private:
        typename mpl::if_<traits::is_view<Sequence1>, Sequence1, Sequence1&>::type seq1;
        typename mpl::if_<traits::is_view<Sequence2>, Sequence2, Sequence2&>::type seq2;
    };
}}

#endif



/* joint_view.hpp
Pbt+ROPQlmEZ/q7Tp+spianxIHyfyVQGackMpcHgmMSpoDTjmd+1615H/niW4EwFH4Ft1KKdIm09T+n7OzQXjIf2HPpecZ6laeG45Fr9xrcYX4Ljt7rssg0hETZI+3j4ZgIZrxlL8zyJvezQ79nhHUxX3mIgUx6EymOnztXzUou7RXBK+Englx5bPFnj3P57YId4H0/e6ptBmqvMSF+YpXTY/9909fOPlN56t/jSHKGTd4u/S2nk3eLHziPNHRjI+2lKx7dqDe8RpLUGBL5PRjHQqc1+noydTx/V2HZsiifeBdIrHXEVA8v4Y0PXnpqYD9K2FzTNOFgi7b613D8amikD2ttbz3bv/fpCxkHmcZZ7KxlG/0Hb7GKfFQaZr98iht1DcxWE3j3+hIs9I/JcpDIpwQNucL0VU/ALLvasCnmelmXK9IEExu8m7wG4+CBnhUqKuDj8Pe0HwBrkGKxBfmnWIOYZlkrHIP3R2n4YW35le3ett93V12tr2n2AR53VZdD+cnZt46w1ZrTsqRcf0L789gDMuvZD2B+irI3ZqThjD/ENzbkmBqhdWEL3YFO4LjjOnxFLLpfe6BaCAxllvne+hWvJfDq+4fmfsF3YHpvMU3+k8WR+bJoe57vDo5oOXK1qm0kq4jp3OQhnhjzODV97IA7vM6PM4wsHYs3kFOemB+Lw+jLewz5z1xprqmk+c2gDPlvRxs04uMfvZtINh+nsjmM3DA2FYdlP3B3Tp64T0NfuWfTufhR7ItFvib7QzIvObl+ifpzfJfiI+yqLywDwFwz+TBP/Yxe/lKYqDkSWAL6adl1qxjP4jYs/JVSqozwCllfASzh/dXGBZHGZxjlXh378ytqoE2fdfLVLViYDT+cctGIRPvUsifuh/MgLkpKZGaSE383Y4WeI7FxEse/FKdNoi2UW+1wXuygLL/REFX8RJU/ibpJy5Iksi0Lmphy8mFIOTspRhHmZRdLILrAc2g7+4X7GIQiw+uykCjCl0/8I6ZdMu+vQZTtrN2CNfS+Ib/4nSDfIwS7aqt/Az/2JHajClvWv0/fMp2PgTqYzhz0x28TBV1AvhwwG7R5gjBds4eUhSiJ7LC0M5obj6ZvzgCHf4YqXHYH06jtsjjW6W/DAjzMO5VFNh9sPcFHFHZ/HFqp0jANnYzvctU7vj9a7uvEc2tfvVtPg+LPmQ3nfvXtNA+MHp3PIc/MeVbp1HXZtzlvvXdGcRkH7e/w+mjbq75j7s6YkI5f3s0iHVqrI+O1deCadk+Zh4ee++J/Wzsc79PKr23+3Z5BOLsd2nDX0Z+cQo8kklsj9qnSMW2Q0m7xvhxhXH/HbxmeRjlFUUSEnyyGS530rvAlJ5UbIw/XZTBODUe4Q89k2BiPH4bu0S413v7xApOmhnwTtYJzaJXpOVYReGldxjkUBoTkEx9ijpL736biXevGtuslbBTNNjPnYIf2vLbr5fKP+b8xqent8/sakN4KAuG8gzGs6XkBz6LhGBfrGNDrOw++D7zq36b+t6Afmf2uhoo8pHftPLdHvmdKOdWF56A6034a3LpFzw9SP4iwKGRyr6rh7aPIR/36CD0tVFkI/hdK7jnj6hpKLz5kKQlXGCraPzurQmfCTms/byfPnoOCnYPlgJHBlr0K5OnOsQy6Rt/biXzuDGHrR3NGLl85pTHsf9acmfX2ot0HX3b2KeZu+Ruzr8SM2XR8mTtK/gOl6KTJJV0d1+mCnTka7+csqfaS3PGGfT2eNtOFdapoxL2a6i/I6C5oGd9trgfhWgkkf7/X0AWe/vffy9rsa+o2hoTnvvxO9ShmXuRSeOqxakXfU791pvH9eT0rx/GFmGgYvqaOs700=
*/