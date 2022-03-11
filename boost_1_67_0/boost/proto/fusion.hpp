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
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
*/