///////////////////////////////////////////////////////////////////////////////
/// \file fusion.hpp
/// Make any Proto expression a valid Fusion sequence
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUSION_HPP_EAN_11_04_2006
#define BOOST_PROTO_FUSION_HPP_EAN_11_04_2006

#include <boost/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/is_view.hpp>
#include <boost/fusion/include/tag_of_fwd.hpp>
#include <boost/fusion/include/category_of.hpp>
#include <boost/fusion/include/iterator_base.hpp>
#include <boost/fusion/include/intrinsic.hpp>
#include <boost/fusion/include/single_view.hpp>
#include <boost/fusion/include/transform.hpp>
#include <boost/fusion/include/as_list.hpp>
#include <boost/fusion/include/is_segmented.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/eval.hpp>
#include <boost/proto/make_expr.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4510) // default constructor could not be generated
#pragma warning(disable : 4512) // assignment operator could not be generated
#pragma warning(disable : 4610) // can never be instantiated - user defined constructor required
#endif

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Expr, long Pos>
        struct expr_iterator
          : fusion::iterator_base<expr_iterator<Expr, Pos> >
        {
            typedef Expr expr_type;
            static const long index = Pos;
            typedef fusion::random_access_traversal_tag category;
            typedef
                tag::proto_expr_iterator<
                    typename Expr::proto_tag
                  , typename Expr::proto_domain
                >
            fusion_tag;

            explicit expr_iterator(Expr &e)
              : expr(e)
            {}

            Expr &expr;
        };

        template<typename Tag>
        struct as_element
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Expr>
            struct result<This(Expr)>
              : result<This(Expr const &)>
            {};

            template<typename This, typename Expr>
            struct result<This(Expr &)>
              : mpl::if_c<
                    is_same<Tag, typename Expr::proto_tag>::value
                  , flat_view<Expr>
                  , fusion::single_view<Expr &>
                >
            {};

            template<typename Expr>
            typename result<as_element(Expr &)>::type const
            operator ()(Expr &e) const
            {
                return typename result<as_element(Expr &)>::type(e);
            }

            template<typename Expr>
            typename result<as_element(Expr const &)>::type const
            operator ()(Expr const &e) const
            {
                return typename result<as_element(Expr const &)>::type(e);
            }
        };

        template<typename Expr>
        struct flat_view
          : fusion::sequence_base<flat_view<Expr> >
        {
            typedef fusion::forward_traversal_tag category;
            typedef
                tag::proto_flat_view<
                    typename Expr::proto_tag
                  , typename Expr::proto_domain
                >
            fusion_tag;
            typedef
                typename fusion::result_of::as_list<
                    typename fusion::result_of::transform<
                        Expr
                      , as_element<typename Expr::proto_tag>
                    >::type
                >::type
            segments_type;

            explicit flat_view(Expr &e)
              : segs_(fusion::as_list(fusion::transform(e, as_element<typename Expr::proto_tag>())))
            {}

            segments_type segs_;
        };
    }

    namespace result_of
    {
        template<typename Expr>
        struct flatten
          : flatten<Expr const &>
        {};

        template<typename Expr>
        struct flatten<Expr &>
        {
            typedef detail::flat_view<Expr> type;
        };
    }

    namespace functional
    {
        /// \brief A PolymorphicFunctionObject type that returns a "flattened"
        /// view of a Proto expression tree.
        ///
        /// A PolymorphicFunctionObject type that returns a "flattened"
        /// view of a Proto expression tree. For a tree with a top-most node
        /// tag of type \c T, the elements of the flattened sequence are
        /// determined by recursing into each child node with the same
        /// tag type and returning those nodes of different type. So for
        /// instance, the Proto expression tree corresponding to the
        /// expression <tt>a | b | c</tt> has a flattened view with elements
        /// [a, b, c], even though the tree is grouped as
        /// <tt>((a | b) | c)</tt>.
        struct flatten
        {
            BOOST_PROTO_CALLABLE()

            template<typename Sig>
            struct result;

            template<typename This, typename Expr>
            struct result<This(Expr)>
              : result<This(Expr const &)>
            {};

            template<typename This, typename Expr>
            struct result<This(Expr &)>
            {
                typedef proto::detail::flat_view<Expr> type;
            };

            template<typename Expr>
            proto::detail::flat_view<Expr> const
            operator ()(Expr &e) const
            {
                return proto::detail::flat_view<Expr>(e);
            }

            template<typename Expr>
            proto::detail::flat_view<Expr const> const
            operator ()(Expr const &e) const
            {
                return proto::detail::flat_view<Expr const>(e);
            }
        };
    }

    /// \brief A function that returns a "flattened"
    /// view of a Proto expression tree.
    ///
    /// For a tree with a top-most node
    /// tag of type \c T, the elements of the flattened sequence are
    /// determined by recursing into each child node with the same
    /// tag type and returning those nodes of different type. So for
    /// instance, the Proto expression tree corresponding to the
    /// expression <tt>a | b | c</tt> has a flattened view with elements
    /// [a, b, c], even though the tree is grouped as
    /// <tt>((a | b) | c)</tt>.
    template<typename Expr>
    proto::detail::flat_view<Expr> const
    flatten(Expr &e)
    {
        return proto::detail::flat_view<Expr>(e);
    }

    /// \overload
    ///
    template<typename Expr>
    proto::detail::flat_view<Expr const> const
    flatten(Expr const &e)
    {
        return proto::detail::flat_view<Expr const>(e);
    }

    /// INTERNAL ONLY
    ///
    template<typename Context>
    struct eval_fun
      : proto::callable
    {
        explicit eval_fun(Context &ctx)
          : ctx_(ctx)
        {}

        template<typename Sig>
        struct result;

        template<typename This, typename Expr>
        struct result<This(Expr)>
          : result<This(Expr const &)>
        {};

        template<typename This, typename Expr>
        struct result<This(Expr &)>
          : proto::result_of::eval<Expr, Context>
        {};

        template<typename Expr>
        typename proto::result_of::eval<Expr, Context>::type
        operator ()(Expr &e) const
        {
            return proto::eval(e, this->ctx_);
        }

        template<typename Expr>
        typename proto::result_of::eval<Expr const, Context>::type
        operator ()(Expr const &e) const
        {
            return proto::eval(e, this->ctx_);
        }

    private:
        Context &ctx_;
    };

    /// INTERNAL ONLY
    ///
    template<typename Context>
    struct is_callable<eval_fun<Context> >
      : mpl::true_
    {};
}}

namespace boost { namespace fusion
{
    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<typename Tag, typename Domain>
        struct is_sequence_impl<proto::tag::proto_flat_view<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
              : mpl::true_
            {};
        };

        template<typename Tag, typename Domain>
        struct is_sequence_impl<proto::tag::proto_expr<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
              : mpl::true_
            {};
        };

        template<typename Tag>
        struct is_view_impl;

        template<typename Tag, typename Domain>
        struct is_view_impl<proto::tag::proto_flat_view<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
              : mpl::true_
            {};
        };

        template<typename Tag, typename Domain>
        struct is_view_impl<proto::tag::proto_expr<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
              : mpl::false_
            {};
        };

        template<typename Tag>
        struct value_of_impl;

        template<typename Tag, typename Domain>
        struct value_of_impl<proto::tag::proto_expr_iterator<Tag, Domain> >
        {
            template<
                typename Iterator
              , long Arity = proto::arity_of<typename Iterator::expr_type>::value
            >
            struct apply
            {
                typedef
                    typename proto::result_of::child_c<
                        typename Iterator::expr_type
                      , Iterator::index
                    >::value_type
                type;
            };

            template<typename Iterator>
            struct apply<Iterator, 0>
            {
                typedef
                    typename proto::result_of::value<
                        typename Iterator::expr_type
                    >::value_type
                type;
            };
        };

        template<typename Tag>
        struct deref_impl;

        template<typename Tag, typename Domain>
        struct deref_impl<proto::tag::proto_expr_iterator<Tag, Domain> >
        {
            template<
                typename Iterator
              , long Arity = proto::arity_of<typename Iterator::expr_type>::value
            >
            struct apply
            {
                typedef
                    typename proto::result_of::child_c<
                        typename Iterator::expr_type &
                      , Iterator::index
                    >::type
                type;

                static type call(Iterator const &iter)
                {
                    return proto::child_c<Iterator::index>(iter.expr);
                }
            };

            template<typename Iterator>
            struct apply<Iterator, 0>
            {
                typedef
                    typename proto::result_of::value<
                        typename Iterator::expr_type &
                    >::type
                type;

                static type call(Iterator const &iter)
                {
                    return proto::value(iter.expr);
                }
            };
        };

        template<typename Tag>
        struct advance_impl;

        template<typename Tag, typename Domain>
        struct advance_impl<proto::tag::proto_expr_iterator<Tag, Domain> >
        {
            template<typename Iterator, typename N>
            struct apply
            {
                typedef
                    proto::detail::expr_iterator<
                        typename Iterator::expr_type
                      , Iterator::index + N::value
                    >
                type;

                static type call(Iterator const &iter)
                {
                    return type(iter.expr);
                }
            };
        };

        template<typename Tag>
        struct distance_impl;

        template<typename Tag, typename Domain>
        struct distance_impl<proto::tag::proto_expr_iterator<Tag, Domain> >
        {
            template<typename IteratorFrom, typename IteratorTo>
            struct apply
              : mpl::long_<IteratorTo::index - IteratorFrom::index>
            {};
        };

        template<typename Tag>
        struct next_impl;

        template<typename Tag, typename Domain>
        struct next_impl<proto::tag::proto_expr_iterator<Tag, Domain> >
        {
            template<typename Iterator>
            struct apply
              : advance_impl<proto::tag::proto_expr_iterator<Tag, Domain> >::template apply<Iterator, mpl::long_<1> >
            {};
        };

        template<typename Tag>
        struct prior_impl;

        template<typename Tag, typename Domain>
        struct prior_impl<proto::tag::proto_expr_iterator<Tag, Domain> >
        {
            template<typename Iterator>
            struct apply
              : advance_impl<proto::tag::proto_expr_iterator<Tag, Domain> >::template apply<Iterator, mpl::long_<-1> >
            {};
        };

        template<typename Tag>
        struct category_of_impl;

        template<typename Tag, typename Domain>
        struct category_of_impl<proto::tag::proto_expr<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };

        template<typename Tag>
        struct size_impl;

        template<typename Tag, typename Domain>
        struct size_impl<proto::tag::proto_expr<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
              : mpl::long_<0 == Sequence::proto_arity_c ? 1 : Sequence::proto_arity_c>
            {};
        };

        template<typename Tag>
        struct begin_impl;

        template<typename Tag, typename Domain>
        struct begin_impl<proto::tag::proto_expr<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
            {
                typedef proto::detail::expr_iterator<Sequence, 0> type;

                static type call(Sequence &seq)
                {
                    return type(seq);
                }
            };
        };

        template<typename Tag>
        struct end_impl;

        template<typename Tag, typename Domain>
        struct end_impl<proto::tag::proto_expr<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    proto::detail::expr_iterator<
                        Sequence
                      , 0 == Sequence::proto_arity_c ? 1 : Sequence::proto_arity_c
                    >
                type;

                static type call(Sequence &seq)
                {
                    return type(seq);
                }
            };
        };

        template<typename Tag>
        struct value_at_impl;

        template<typename Tag, typename Domain>
        struct value_at_impl<proto::tag::proto_expr<Tag, Domain> >
        {
            template<
                typename Sequence
              , typename Index
              , long Arity = proto::arity_of<Sequence>::value
            >
            struct apply
            {
                typedef
                    typename proto::result_of::child_c<
                        Sequence
                      , Index::value
                    >::value_type
                type;
            };

            template<typename Sequence, typename Index>
            struct apply<Sequence, Index, 0>
            {
                typedef
                    typename proto::result_of::value<
                        Sequence
                    >::value_type
                type;
            };
        };

        template<typename Tag>
        struct at_impl;

        template<typename Tag, typename Domain>
        struct at_impl<proto::tag::proto_expr<Tag, Domain> >
        {
            template<
                typename Sequence
              , typename Index
              , long Arity = proto::arity_of<Sequence>::value
            >
            struct apply
            {
                typedef
                    typename proto::result_of::child_c<
                        Sequence &
                      , Index::value
                    >::type
                type;

                static type call(Sequence &seq)
                {
                    return proto::child_c<Index::value>(seq);
                }
            };

            template<typename Sequence, typename Index>
            struct apply<Sequence, Index, 0>
            {
                typedef
                    typename proto::result_of::value<
                        Sequence &
                    >::type
                type;

                static type call(Sequence &seq)
                {
                    return proto::value(seq);
                }
            };
        };

        template<typename Tag>
        struct convert_impl;

        template<typename Tag, typename Domain>
        struct convert_impl<proto::tag::proto_expr<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    typename proto::result_of::unpack_expr<
                        Tag
                      , Domain
                      , Sequence
                    >::type
                type;

                static type call(Sequence& seq)
                {
                    return proto::unpack_expr<Tag, Domain>(seq);
                }
            };
        };

        template<typename Tag, typename Domain>
        struct convert_impl<proto::tag::proto_flat_view<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
            {
                typedef
                    typename proto::result_of::unpack_expr<
                        Tag
                      , Domain
                      , Sequence
                    >::type
                type;

                static type call(Sequence& seq)
                {
                    return proto::unpack_expr<Tag, Domain>(seq);
                }
            };
        };

        template<typename Tag>
        struct is_segmented_impl;

        template<typename Tag, typename Domain>
        struct is_segmented_impl<proto::tag::proto_flat_view<Tag, Domain> >
        {
            template<typename Iterator>
            struct apply
              : mpl::true_
            {};
        };

        template<typename Tag>
        struct segments_impl;

        template<typename Tag, typename Domain>
        struct segments_impl<proto::tag::proto_flat_view<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
            {
                typedef typename Sequence::segments_type const &type;
                            
                static type call(Sequence &sequence)
                {
                    return sequence.segs_;
                }
            };
        };

        template<typename Tag, typename Domain>
        struct category_of_impl<proto::tag::proto_flat_view<Tag, Domain> >
        {
            template<typename Sequence>
            struct apply
            {
                typedef forward_traversal_tag type;
            };
        };
    }

    namespace traits
    {
        template<typename Seq1, typename Seq2>
        struct enable_equality<
            Seq1
          , Seq2
          , typename enable_if_c<
                mpl::or_<
                    proto::is_expr<Seq1>
                  , proto::is_expr<Seq2>
                >::value
            >::type
        >
            : mpl::false_
        {};

        template<typename Seq1, typename Seq2>
        struct enable_comparison<
            Seq1
          , Seq2
          , typename enable_if_c<
                mpl::or_<
                    proto::is_expr<Seq1>
                  , proto::is_expr<Seq2>
                >::value
            >::type
        >
          : mpl::false_
        {};
    }
}}

namespace boost { namespace mpl
{
    template<typename Tag, typename Args, long Arity>
    struct sequence_tag< proto::expr<Tag, Args, Arity> >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template<typename Tag, typename Args, long Arity>
    struct sequence_tag< proto::basic_expr<Tag, Args, Arity> >
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif

/* fusion.hpp
Bc4UuOhVe+86TYFB3uIKjHFjsQgPbffiZNzkKbHbVKQHFZb3S9nUMi+dnRs8BLnk7kntuZimkYX91R4RFjuiqDz8RKWD/M7dRfZSxSVhuX3VU2fjhCSsvngVAxiWkQLZzZC4iw2FMSKwE6OXrS/iHY4ATbfBNSw58/P6qLrxuEOT0C/dDdkLxtiW7L0D4wCBh8dJb6iHr+IIEa+2FjEqlTeZckMdMGcUptf+ClZxsHUXZeTerkJww24FUkAIWXAAIWKA/B1JeuCj8oxaeRcE64O7FBSOI7f9MswlmeERJR2PF6X20ndfzL8mPkQqWknnCBvxNaEIh0uD22R79dVikHNCGKa5ZELWg7hGwqpqAVXTG9EbQFKzmjS2pP00zPRpVi4Rc1s6604sM1m5WxR6NX8K/HQv/Iuvlk78eXxX+yXGzV+Om0AtD49VsKsVOl9eTbe7De5Oz+yvmAY4RrvuWxeJ3WywgeqbKCFG0VF9cwOuLFXkSrfGI4DJi18aN4u3png5grMmyM295yiAdHQUCMPV7QE84kwnTxgen7jBUPC4jHdvFfk9vDRrvSF6lB0Ovnb1oaoNFYHVTelnbDWM0U7kEaCXFowlMti7AYGL+DumrmvEkTGcg468df8+bmmZyuQtW3d2lhQayFcrDQKCGIYopg8nBe+wrPH0GzauXCqShr9LhaQntaO+w7VM8G+AQJhVSiFMiKBtSCCh+yLrZykmdyk7x6ILJjKk2MtUshwPJIqJl5T4hLqt+oYgE1A8IV/WQ+VK7cjukzM+zmeoLlV1oRf1a9Ow4Yf38tV1NvmCdOfIWvUUUBinXuBOXhFgPLulutgkt1Qko/afXlbTdTKnpq4OJJkoGDDtcKJ5TlkLdsWBxHu9QF7x270PTAPvJtAOOAuqdN4QcjIVOM4jqw/KLHldzkf11bpPQSEvN7i2oJW7dUtFypSRe06ueHZ9ivHkrG0QPYHyUHM+Z3ZL5LvZOUrvFPoW3Eh4vzdF/FwmQbqm7SKAmqojRU9XnV7e9tBGK63IlThX+EB83CxQvUs0zmsvRBMRsNPJyAA4+WApi+tq9hSbMuyJFCgLQ5TLqNpm8sngxLM0R6/yuzg6aS4RCxvNXdKgE1HNSAYx4nKcNpZkqiUUWZX4dJcEcZrdrHGweOa4D6H1Vwyod6dOYh85rKaQWFMqrPXXFLX0tUqvtEX4xM/vZitpVyin5FlbmkY3tIec5VH/Mfr2pyNuQ5vZwU5Re99n1nADCMbLu50LfDSHqmL8G+a9EZJODyut2E5FTqzdj+9BNd9SWHAZ062uQf5OAuc3Ra5U2kKyiM6zA2TIUsBs/5n6DbitN52SQlh8jv/2pyyy9QpbWVL6XMxaRJBZhdXzk+Hf22NSECXMEQ66ecPR5HSNjoVDSre0EwHzOF+XNRYPcv+kbNiO3zkqz3p18OV0g5jHRG8G8cxyu2mxJZuSkWeMYO7EIjvJTBRm/+4E+qVuwZTjJqFZXQWmuQmsxgEzetSfdiLU6lGShU07MTGvMRBdUdgCVtaFqyd5uG6vf7O1Q5C+PP+2AH2Sf0zl2BKF4bCSuCtVzfd4UR3wwI2pSOi6eemSn0o0Njd0u29g3kl0ZxiSavEMS3uc25W9zaIH0XbxyAcE2WnyHc/GNj4ogoZ69XYneFbd7ptjRSjqwXBULWZPGC/f0I8hx8hYZA27NEgZbN2DaRTYBQpe6zKN9KqozggiyrVezkTNxnED6ElCl/QtaTe4nhrImiZ4sBcEup5dOQ2kpkrWsCda/u1nrqZyooVrfcckks9M6uWgpaLbLfkg6gkL5pVhj7gGjEtKWS9XjgL0cgUDgonB0+Ob+jX6ugAsUMDcPg6XAbb0YPP0WZ18bwLAW3++AdaE4+p7TAL0Xtj5NcSP7ONbRGiwwTJtqScyjhp33F2N/JUpWcMAN6uspZGTLsLprpDDTDUmTKDm8gF8IFUSxQ5FS9hO02hf1jUTdwNaWyrqo5OhD5Qt2zPKB8+/u5RlRV2iXQxZQ3OwvaviD+aZZgv7Hv5A7C5FCR3uV1R+iM67C7GNfmit8IRvTgJT1facP5SC84aJ0OciTiIGWfH7kKdn66ZN42qRncJRI+sAx+T9HjB5zejxpxkWm8CAKrVVPBhHjES86vcVwKjkuJK9MlRfIMRvS0DOzp49V+Qzh+8rmqnQw/5AhSh2HTSM1eQNBehVlQH7AmaSK263PWXccBr5rnP6myNhBt/NBZ3qmh0GvkutKvdCKNbFSmTGXEDilPGZC0Z5ql6ezRV7a0D/bEnj0PpmSrJTcbiR7AViXsl2RbKummuE8Y/VuVwhwYfPGes7tGPft2zjDckZh12tHqDLJsc7vmWKOpKTaGnpjtWhEVbSv/urmX2ntmyYpXY+BCvZ20mCmxBEfTFmnW4/Hp9/U05QMGsnx2HxR+FUu8LtWU6l6/5rO6Je0RIGBgMBfRPHznNRFidEj9DvQmr10VLM5aX67pzhMEqwl8gZQPadDz66WPPsa3n9R9eu+nRuqwO+76rOrbyOaizdzpW62Q+y/veAjTdp4nQwIk8e9XVp8KUn1GkfesdNd1PXicAfnlo929zJke/MQmBmf2SQfBadJJWVyMS/f3i011MQDpJxC+cSwE7bG0Q9/HjNbOwI9BUgRnYYhg5nNIapXQVAtNfaLs9XCsl9XnKyYPib5uT6QjHTX/z1woHuzbrjfO79r+FY+b3rwff0YexnmYwKYnIWoOuecs+QngogZ+AgmdzG/VMFRyhkWbDLAS0Sx9Rhx0e7eCZ6mtPGIQAi4NjlLq9HQB4SWT2ZPeGd8NPKaegvs4YDj5r2ilb8yolaLSYVS0SOJlReR5z9mg/IigiY9jGEtq7UE8YPac3etlQU1YZqYt128Q4TWw/cRzX3JqHzdjlW43IvHHTkso6eNzzXyAKr699RTrYVXw+qh+V1kB5UstVazEFL6s2A2vWlIdehsURipr5y/D9/By4z01hWGh6t4du2xzIFS8tZ9T80F/VMyuc/d2Sncqzaf/PisPtuJds3aOimtmGcUlK7qkmNjvXaaiHFX6VjXTU1PPD15QaRRIPTH6ufnZ553x+0n7KfrLJvkSLfgUM8oYiHQmYaG6z3Bxh+KQVMlavoNEsEczqQpjOwJuCl1kHGugiY8xcYy0a4io58ujLfj0xAy6YGvw5+gD+I68lnqLANFdnApdVLTaf0GqI2ojP9qZ0+m/rvY+KBEH1ogLv1YH2BS1ZvVm8TE2A+vQZ5mU55O9DPoB1nuMDm69GpRmxwHWFbiKrrMt8wtTpaGZiTUg4RlBWlqCUVoYjbPYzsV/pa7TLOGyj7mg+XgAa9jm+u55JckOaYkObSSDgzC7ZZZnfr3aSxigioJGbxq7wz/87hoK1H76sWlct3g7yaXpKNGZyAXb6bTe8gXy897jYiCxiXTk/jFzaeFfle3/aNYQSNeA9wsA/WzQKjNIxcIlRorJFx347DGyE+x6znCwUcCuK+XJ2sBtkQILUMFUozAhNvYLIlsgDCI8HOoPDM5lmY2+YLdAUHL5Bi2IZpz9wf125KObxjV+lYOPLpnL2frBs3lJbEXzlOOFJqliCFUXrhsxY/iRYJpUpUn1rsyjRDFX/6zkAsXVaqd0K3VdUMKRaWqAie//Dv6MR7m4/F5b3VnhNTtmr7R4TafuF+oahvjRPfASzigT734TZqfao4Wbz7q+OBqxabzEJ+IZ3brYcu5WY+303nZj/XGpbgNCKzOQ3TimykeqcUjEZXzMKMDhwacmyaaLib/tiDOIiZbhoWUWtaDC9JHbBSiHdT0JpgbeIaRim3YryvJz01CZ1pMNSW1hcEgD4y3WCtN+Wmt9ZemZ1cMR/r4IGHVJmIyjHXA92D2tzrUjJ7e/sOQtGIWCozdzw+MdhKu+5R6bjl1yQ+wGWd5P8t5h3jDMlw9/G7gEMpEqICN5PyyKFmHQs1vEvwug0/eTUYyCblmdnBayXNGMy+WGsGP04wnLZFxFWrjn191+7OnPmD4ZddSOOo+++Dg27vi5Fuz/a7U43T/HMn+L7OgLRX9uixSiGeQI91vrCmPNxbASmRTUXnIQk32O80SomamNwU/OHqErKNrmK55VQz9UXLSoamg9JC46Hdh7O2fGsYNLLMb3THgg7BsBqJ2FCLRFRilv/+eHYN4ofyjqRnLQJkymBs6qzheTRbR9NvATvtM7QZx7M4uHKSdfbiblnCSdzkseEH6ytC0x/oPFn1WIWa7zommdqBM55Gk6WM51SN8CcDJtmPG3qIR3xLPQ0ukcT9PYJBmRC2b+reCM0MIR6xBVL+pETlxCjk5AuTteLciSttafLZQ8wKO/QQkf70JG3sW3VoJ+81Fl8XTaukwq6fZCC9pqRB0HAVklD3zbS10zqJYvvQpXPTUCZjbNC/YIWMcNtT3ebU/FOk0ECu2OZmXnb5LQXsfEpSpBG9VbbV7rTMxMahi90oe/rJS3eCbTnKRoyqsm5N8dxEWKAMopKkeps9Fho4WXtnwHUTXmmnv/KI3bf0hLr31k40eGYSm42OGYJvm2ngvkOF+BszrU6ZDpB0nq5Ps/UhpmWD0mGH7LpNJ/SqY52W59iCihyhJwc6z4rCH29kybD/inMwvVkny3hDhN3sUrmPnCN8DkwB6cjwwKHNDLkkUnIysBUG+HMIWidj++1pK8PrERKeZz5pcBstjRXqBDQk5czBz/vgzUvwQtRnf6CZ0/VVGNY1BK0K7QUDAAIs/dPMV4qBvN43BToknbDVDzXfRcL1rnu/QUhHU9prqbbwdCalgvzdqNoHh96LV9eyg/i+qkMh4Qbe5CXa30JavemrHlzSS6s4YBEh2ciDCN9k5S0FmINWTWMN1GyjOXDN+ZuxiOCn29ap4ajfVkZz6byivom8M+pqxlWkq+5wF1WvI2OQEmQ3M2SvdqbY6s8yI4sjBENYnWppUtjsy7bDklmX9F/1WA5ldRJC+IxF48Mn9cUSZOy76XwcPUf+Q7JHc4w9QbYCKCQi1/1xpPWa6nwGl/QfwGnMDsJ9BZvVc5TCy4I6ydhU3gRigA24kVbZ9wfYb69ovupXpH+5tbeloL5BCy0Ld6Df+OGeSrNz8qqw1neu9aoDTyvCc7pr0YOIhvDoDwFEEBuuxqLdB/haM1xKZyi+JLFszmd7oe1PHScdTYxpDwoTXF70aTazKS3lH1uGKwm21ZegmCHbmxFsKKHNJo/DRLgahLBmte6yGXHShb5LnHcSIQYyahCL3g64C3/+rSwuxgSef1c78Ka2TFI2uOxC0Vh1LKm2Z4dHkFh1DLU8Q7p0sQlp0TvokC9hnbiEc+wQOojRz1w6hXs7UZ4D5YlKRw0k8Gw5XmQS9L4OwdkTve7bbgZP4MsWF6A0dbypjmKdsBwsIM1EJyEiI9JCnM8QfwyrUXz7Ia3QLSbQV+921+kXfem+ljzyuLy4GIigoVST/nztJz4YKhIHQNbzzlaHDwHqhEy4k6i2LFJ5u/u6+g6BEw0F9XT694z4BmPH3TIW1dLZUU9TH8JohPpIUftjfliDavwrFXLmb/5E6e9yovb9GnEi930y2zZSvSNs+yw+KCNkiF+pkGBOBKJCygYNqps4jUo5foijWmu4C8Y8zELaZA/T3yC1QaDp2LSUo72OdrvaDLEZXGGIsen6tPumFOR4tPB2Urywa8m1vUaD/CAaEvbWA0LExVzJzYtvufZFYo7hRqUyb4J9gxQQKo2CIIEbvRBZYZdQoVmaAjh59OmH3P7u9VeaBc8K5oOfbvnoAJyW6d7NeobyV3K39d3N0v7o9W+8mFO33278oWYvJGEXm452FLuaSEz12YKX+95N7eZ+exSDzdl0uVd2v+8xavvAOvgeRc/lmZ94+eGLjV/ZQf8Ji6qvcI0KLuUEm156Txxufx/qqTk9jUU1WFmNVKsfTJounn8CXXbW1mRds2ZU0QuRwZ8m4JyrwVVruQkxWzs2SrhBLM2VbWqGshQz+Zj4bAXz/eIZf+7+fAD4Cf5BZ7DvJ9ryIoO4BpHOCl9jLW3BwQEJNCfAJb/2J+HERM/KbLunsLdpGWfA9i+ihnR5n18kVH9C+XLmSr4yJ1CFP4aGY/tCq+Lc3LJ6m2IrljVhitik8R3SUHEOEsLHyu4v4FIH/fFu1ZUzhlsGBmMejcnoKKQew1A3YdINz9e738+26upcpoZ6g2oKL+1U22xrlaqsBTq2l/6G4BQE8JtDN1mnvyB0z+bSuhAZD9TZiuoNsf2SZdHJ/AMDZFUwBOu1B0rPcj5GWziF12FvM+ZcI/YXV4+bGdW6tNkDWPUpvJHImgwnie4gpuUfUO+hb/+7q35wjudeIA4YuKVDw+OzdNobO0tp9DGPhsy9OKnE35R8Xqbc2H/rATYZ6b3aHzO0FK82kAPAc0BNn+3+oBxZsC3jekaDMlROus8hOJx8PS7B06AzAaMJk55kAn+nayv6DcasK9ZU36jTJmB3bhlhUoMN+axfHSYkiMJ5dDRvmHOXsoupRewxARbZLrbbTe+uPnTe1wasJ/vJ6M1NC6UeWgl9xRK7hDWL4BVCZALTb1C4tsG5IHqp7i6DyYpk2f55AN9WIVbOXEZDD7WfqsNk08X4VDeumTYLZKGAWrMCai2hb+geB4x6F0yIAzgw8DUsCQ0j6YQ0x7m5RB3GTC41q+92FxodRtysFaA01I+pPnHYu1znOgW19uLLeemapBBEDOmKlt28fB5k2GnY34aX7wBd0xuHYVfgZ9gtuI490PF/84e81RH4O7VKQg4SlhLshOXriR1N0YdntszPStAWorbEHWLW+tZSdWwrV4zkJXkBN4X6P08oFBPCDAW+3rqBhOJ0kiyYb1CCpvbGsoKkmu6aaHkg63oxPW44lAx1i9MtyBFGob93uA6ybV/NP7pvorPsrm91Sz3EjhylmV0YaVbadJpPjp11pKMU6SA62iSPJuDj6tTY2e88dBwN6aVeWDl+PSjmMR3KAVdq9FU4SShTaXqfcX8QZSPox6w4WzB0hu5Jumk3ZPRJjRg9ahOYY+FrAeU9lUqNfVL2eZyQY2jl+3O0VC4ES8UhD7PlPL/32fLgB1Y3ICMbVfAWkmoVY4FoIoWOP2FYu8d0A4vItON2ftLpH0v0xC1YOoLVpihRwlrYh1FJcXBtXaNmRyKQBrVsc2B4wjkTUqhnsN9c2Fqwl4Nbn/TxZdPMAIQGHnH9mfqoH5o4+WM9X+QTM2kUonY5CaG6FbQJur6VJQ08l/PzZ5Ko5wPXT1WasPBWd/f4q9WKFA8AZES4T0Gl0bEr8UrQ3FStVWpHgxSJrgeJ6Opzp/A1JSjjEqg8h8IZyIGwbwjWdvfBlv0cmZkq0Qk3PAPOviniLfZcSthxRppbjXkO8StR9q5v4HNN8G/dD3W7opxRcQ++hQABQ60JkaL4BqWZXxQqzcKL8nvvYc760uQLMzRwvGeGavwrGiKJT7u0XjpeWO/2E0cFQ12qqIoNKl7CaYMVdu3UKXObEQFZVxhdcNey9D3m132YEXR570vKOe9QrKIvnbfAVzs6WRzKbG6kXk3p92Ci1JOOI1aFT7mazJ9aURXYSPcyD58wNHWtQfcsalfXB1dA04aq4PUr
*/