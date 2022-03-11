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