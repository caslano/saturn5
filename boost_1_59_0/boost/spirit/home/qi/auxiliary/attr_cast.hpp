//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_QI_AUXILIARY_ATTR_CAST_HPP
#define BOOST_SPIRIT_QI_AUXILIARY_ATTR_CAST_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/qi/detail/attributes.hpp>
#include <boost/spirit/home/support/auxiliary/attr_cast.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables attr_cast<>() pseudo parser
    template <typename Expr, typename Exposed, typename Transformed>
    struct use_terminal<qi::domain
          , tag::stateful_tag<Expr, tag::attr_cast, Exposed, Transformed> >
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
    using spirit::attr_cast;

    ///////////////////////////////////////////////////////////////////////////
    // attr_cast_parser consumes the attribute of subject generator without
    // generating anything
    ///////////////////////////////////////////////////////////////////////////
    template <typename Exposed, typename Transformed, typename Subject>
    struct attr_cast_parser 
      : unary_parser<attr_cast_parser<Exposed, Transformed, Subject> >
    {
        typedef typename result_of::compile<qi::domain, Subject>::type
            subject_type;

        typedef typename mpl::eval_if<
            traits::not_is_unused<Transformed>
          , mpl::identity<Transformed>
          , traits::attribute_of<subject_type> >::type
        transformed_attribute_type;

        attr_cast_parser(Subject const& subject_)
          : subject(subject_)
        {
            // If you got an error_invalid_expression error message here,
            // then the expression (Subject) is not a valid spirit qi
            // expression.
            BOOST_SPIRIT_ASSERT_MATCH(qi::domain, Subject);
        }

        // If Exposed is given, we use the given type, otherwise all we can do
        // is to guess, so we expose our inner type as an attribute and
        // deal with the passed attribute inside the parse function.
        template <typename Context, typename Iterator>
        struct attribute
          : mpl::if_<traits::not_is_unused<Exposed>, Exposed
              , transformed_attribute_type>
        {};

        template <typename Iterator, typename Context, typename Skipper
          , typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr_param) const
        {
            // Find the real exposed attribute. If exposed is given, we use it
            // otherwise we assume the exposed attribute type to be the actual
            // attribute type as passed by the user.
            typedef typename mpl::if_<
                traits::not_is_unused<Exposed>, Exposed, Attribute>::type
            exposed_attribute_type;

            // do down-stream transformation, provides attribute for embedded
            // parser
            typedef traits::transform_attribute<
                exposed_attribute_type, transformed_attribute_type, domain>
            transform;

            typename transform::type attr_ = transform::pre(attr_param);

            if (!compile<qi::domain>(subject).
                    parse(first, last, context, skipper, attr_))
            {
                transform::fail(attr_param);
                return false;
            }

            // do up-stream transformation, this mainly integrates the results
            // back into the original attribute value, if appropriate
            transform::post(attr_param, attr_);
            return true;
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("attr_cast"
              , compile<qi::domain>(subject).what(context));
        }

        Subject subject;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(attr_cast_parser& operator= (attr_cast_parser const&))
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generator: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Expr, typename Exposed, typename Transformed
      , typename Modifiers>
    struct make_primitive<
        tag::stateful_tag<Expr, tag::attr_cast, Exposed, Transformed>, Modifiers>
    {
        typedef attr_cast_parser<Exposed, Transformed, Expr> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            typedef tag::stateful_tag<
                Expr, tag::attr_cast, Exposed, Transformed> tag_type;
            using spirit::detail::get_stateful_data;
            return result_type(get_stateful_data<tag_type>::call(term));
        }
    };


}}}

#endif

/* attr_cast.hpp
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
*/