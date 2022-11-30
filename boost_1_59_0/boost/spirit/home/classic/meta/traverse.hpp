/*=============================================================================
    Copyright (c) 2002-2003 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_TRAVERSE_HPP)
#define BOOST_SPIRIT_TRAVERSE_HPP

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/meta/impl/traverse.ipp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Post-order traversal of auxiliary parsers.
    //
    ///////////////////////////////////////////////////////////////////////////
    struct post_order
    {
        //  Return the parser type, which is generated as the result of the
        //  traverse function below.

        template <typename MetaT, typename ParserT>
        struct result
        {
            typedef typename
                traverse_post_order_return<
                    MetaT
                  , ParserT
                  , traverse_post_order_env<0, 0, 0, 0>
                >::type
            type;
        };

        //  Traverse a given parser and refactor it with the help of the given
        //  MetaT metafunction template.

        template <typename MetaT, typename ParserT>
        static typename result<MetaT, ParserT>::type
        traverse(MetaT const &meta_, ParserT const &parser_)
        {
            typedef typename ParserT::parser_category_t parser_category_t;
            return impl::traverse_post_order<parser_category_t>::generate(
                meta_, parser_, traverse_post_order_env<0, 0, 0, 0>());
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Transform policies
    //
    //      The following policy classes could be used to assemble some new
    //      transformation metafunction which uses identity transformations
    //      for some parser_category type parsers.
    //
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    //  transform plain parsers
    template <typename TransformT>
    struct plain_identity_policy
    {
        template <typename ParserT, typename EnvT>
        struct plain_result
        {
            // plain parsers should be embedded and returned correctly
            typedef typename ParserT::embed_t type;
        };

        template <typename ParserT, typename EnvT>
        typename parser_traversal_plain_result<TransformT, ParserT, EnvT>::type
        generate_plain(ParserT const &parser_, EnvT const& /*env*/) const
        {
            return parser_;
        }
    };

    //////////////////////////////////
    //  transform unary parsers
    template <typename UnaryT, typename SubjectT>
    struct unary_identity_policy_return
    {
        typedef typename UnaryT::parser_generator_t parser_generator_t;
        typedef typename parser_generator_t
            ::template result<SubjectT>::type type;
    };

    template <typename TransformT>
    struct unary_identity_policy
    {
        template <typename UnaryT, typename SubjectT, typename EnvT>
        struct unary_result
        {
            typedef
                typename unary_identity_policy_return<UnaryT, SubjectT>::type
            type;
        };

        template <typename UnaryT, typename SubjectT, typename EnvT>
        typename parser_traversal_unary_result<
            TransformT, UnaryT, SubjectT, EnvT>::type
        generate_unary(
            UnaryT const &, SubjectT const &subject_, EnvT const& /*env*/) const
        {
            typedef typename UnaryT::parser_generator_t parser_generator_t;
            return parser_generator_t::template generate<SubjectT>(subject_);
        }
    };

    //////////////////////////////////
    //  transform action parsers
    template <typename TransformT>
    struct action_identity_policy
    {
        template <typename ActionT, typename SubjectT, typename EnvT>
        struct action_result
        {
            typedef action<SubjectT, typename ActionT::predicate_t> type;
        };

        template <typename ActionT, typename SubjectT, typename EnvT>
        typename parser_traversal_action_result<
            TransformT, ActionT, SubjectT, EnvT
        >::type
        generate_action(ActionT const &action_, SubjectT const &subject_,
            EnvT const& /*env*/) const
        {
            return subject_[action_.predicate()];
        }
    };

    //////////////////////////////////
    //  transform binary parsers
    template <typename BinaryT, typename LeftT, typename RightT>
    struct binary_identity_policy_return
    {
        typedef typename BinaryT::parser_generator_t parser_generator_t;
        typedef typename parser_generator_t
            ::template result<LeftT, RightT>::type type;
    };

    template <typename TransformT>
    struct binary_identity_policy
    {
        template <typename BinaryT, typename LeftT
            , typename RightT, typename EnvT>
        struct binary_result {

            typedef typename
                binary_identity_policy_return<BinaryT, LeftT, RightT>::type
            type;
        };

        template <typename BinaryT, typename LeftT
            , typename RightT, typename EnvT>
        typename parser_traversal_binary_result<
            TransformT, BinaryT, LeftT, RightT, EnvT
        >::type
        generate_binary(
            BinaryT const &, LeftT const& left_
          , RightT const& right_, EnvT const& /*env*/) const
        {
            typedef typename BinaryT::parser_generator_t parser_generator_t;
            return parser_generator_t::
                template generate<LeftT, RightT>(left_, right_);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  transform_policies template
    //
    //      The transform_policies template metafunction could serve as a
    //      base class for new metafunctions to be passed to the traverse meta
    //      template (see above), where only minimal parts have to be
    //      overwritten.
    //
    ///////////////////////////////////////////////////////////////////////////

    template <
        typename TransformT,
        typename PlainPolicyT = plain_identity_policy<TransformT>,
        typename UnaryPolicyT = unary_identity_policy<TransformT>,
        typename ActionPolicyT = action_identity_policy<TransformT>,
        typename BinaryPolicyT = binary_identity_policy<TransformT>
    >
    struct transform_policies :
        public PlainPolicyT,
        public UnaryPolicyT,
        public ActionPolicyT,
        public BinaryPolicyT
    {
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Identity transformation
    //
    //      The identity_transform metafunction supplied to the traverse
    //      template will generate a new parser, which will be exactly
    //      identical to the parser given as the parameter to the traverse
    //      metafunction. I.e. the following conceptual 'equation' will be
    //      always true:
    //
    //      some_parser ==
    //          post_order::traverse(identity_transform(), some_parser)
    //
    ///////////////////////////////////////////////////////////////////////////

    struct identity_transform : transform_policies<identity_transform> {};

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif // !defined(BOOST_SPIRIT_TRAVERSE_HPP)

/* traverse.hpp
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
*/