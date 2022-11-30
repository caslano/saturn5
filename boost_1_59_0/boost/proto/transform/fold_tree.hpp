///////////////////////////////////////////////////////////////////////////////
/// \file fold_tree.hpp
/// Contains definition of the fold_tree<> and reverse_fold_tree<> transforms.
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_FOLD_TREE_HPP_EAN_11_05_2007
#define BOOST_PROTO_TRANSFORM_FOLD_TREE_HPP_EAN_11_05_2007

#include <boost/type_traits/is_same.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/matches.hpp>
#include <boost/proto/transform/fold.hpp>
#include <boost/proto/transform/impl.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Tag>
        struct has_tag
        {
            template<typename Expr, typename State, typename Data, typename EnableIf = Tag>
            struct impl
            {
                typedef mpl::false_ result_type;
            };

            template<typename Expr, typename State, typename Data>
            struct impl<Expr, State, Data, typename Expr::proto_tag>
            {
                typedef mpl::true_ result_type;
            };

            template<typename Expr, typename State, typename Data>
            struct impl<Expr &, State, Data, typename Expr::proto_tag>
            {
                typedef mpl::true_ result_type;
            };
        };

        template<typename Tag, typename Fun>
        struct fold_tree_
          : if_<has_tag<Tag>, fold<_, _state, fold_tree_<Tag, Fun> >, Fun>
        {};

        template<typename Tag, typename Fun>
        struct reverse_fold_tree_
          : if_<has_tag<Tag>, reverse_fold<_, _state, reverse_fold_tree_<Tag, Fun> >, Fun>
        {};
    }

    /// \brief A PrimitiveTransform that recursively applies the
    /// <tt>fold\<\></tt> transform to sub-trees that all share a common
    /// tag type.
    ///
    /// <tt>fold_tree\<\></tt> is useful for flattening trees into lists;
    /// for example, you might use <tt>fold_tree\<\></tt> to flatten an
    /// expression tree like <tt>a | b | c</tt> into a Fusion list like
    /// <tt>cons(c, cons(b, cons(a)))</tt>.
    ///
    /// <tt>fold_tree\<\></tt> is easily understood in terms of a
    /// <tt>recurse_if_\<\></tt> helper, defined as follows:
    ///
    /// \code
    /// template<typename Tag, typename Fun>
    /// struct recurse_if_
    ///   : if_<
    ///         // If the current node has type "Tag" ...
    ///         is_same<tag_of<_>, Tag>()
    ///         // ... recurse, otherwise ...
    ///       , fold<_, _state, recurse_if_<Tag, Fun> >
    ///         // ... apply the Fun transform.
    ///       , Fun
    ///     >
    /// {};
    /// \endcode
    ///
    /// With <tt>recurse_if_\<\></tt> as defined above,
    /// <tt>fold_tree\<Sequence, State0, Fun\>()(e, s, d)</tt> is
    /// equivalent to
    /// <tt>fold<Sequence, State0, recurse_if_<Expr::proto_tag, Fun> >()(e, s, d).</tt>
    /// It has the effect of folding a tree front-to-back, recursing into
    /// child nodes that share a tag type with the parent node.
    template<typename Sequence, typename State0, typename Fun>
    struct fold_tree
      : transform<fold_tree<Sequence, State0, Fun> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : fold<
                Sequence
              , State0
              , detail::fold_tree_<typename Expr::proto_tag, Fun>
            >::template impl<Expr, State, Data>
        {};

        template<typename Expr, typename State, typename Data>
        struct impl<Expr &, State, Data>
          : fold<
                Sequence
              , State0
              , detail::fold_tree_<typename Expr::proto_tag, Fun>
            >::template impl<Expr &, State, Data>
        {};
    };

    /// \brief A PrimitiveTransform that recursively applies the
    /// <tt>reverse_fold\<\></tt> transform to sub-trees that all share
    /// a common tag type.
    ///
    /// <tt>reverse_fold_tree\<\></tt> is useful for flattening trees into
    /// lists; for example, you might use <tt>reverse_fold_tree\<\></tt> to
    /// flatten an expression tree like <tt>a | b | c</tt> into a Fusion list
    /// like <tt>cons(a, cons(b, cons(c)))</tt>.
    ///
    /// <tt>reverse_fold_tree\<\></tt> is easily understood in terms of a
    /// <tt>recurse_if_\<\></tt> helper, defined as follows:
    ///
    /// \code
    /// template<typename Tag, typename Fun>
    /// struct recurse_if_
    ///   : if_<
    ///         // If the current node has type "Tag" ...
    ///         is_same<tag_of<_>, Tag>()
    ///         // ... recurse, otherwise ...
    ///       , reverse_fold<_, _state, recurse_if_<Tag, Fun> >
    ///         // ... apply the Fun transform.
    ///       , Fun
    ///     >
    /// {};
    /// \endcode
    ///
    /// With <tt>recurse_if_\<\></tt> as defined above,
    /// <tt>reverse_fold_tree\<Sequence, State0, Fun\>()(e, s, d)</tt> is
    /// equivalent to
    /// <tt>reverse_fold<Sequence, State0, recurse_if_<Expr::proto_tag, Fun> >()(e, s, d).</tt>
    /// It has the effect of folding a tree back-to-front, recursing into
    /// child nodes that share a tag type with the parent node.
    template<typename Sequence, typename State0, typename Fun>
    struct reverse_fold_tree
      : transform<reverse_fold_tree<Sequence, State0, Fun> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : reverse_fold<
                Sequence
              , State0
              , detail::reverse_fold_tree_<typename Expr::proto_tag, Fun>
            >::template impl<Expr, State, Data>
        {};

        template<typename Expr, typename State, typename Data>
        struct impl<Expr &, State, Data>
          : reverse_fold<
                Sequence
              , State0
              , detail::reverse_fold_tree_<typename Expr::proto_tag, Fun>
            >::template impl<Expr &, State, Data>
        {};
    };

    /// INTERNAL ONLY
    ///
    template<typename Sequence, typename State0, typename Fun>
    struct is_callable<fold_tree<Sequence, State0, Fun> >
      : mpl::true_
    {};

    /// INTERNAL ONLY
    ///
    template<typename Sequence, typename State0, typename Fun>
    struct is_callable<reverse_fold_tree<Sequence, State0, Fun> >
      : mpl::true_
    {};

}}

#endif

/* fold_tree.hpp
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
*/