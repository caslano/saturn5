//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_RULE_MAR_05_2007_0455PM)
#define BOOST_SPIRIT_KARMA_RULE_MAR_05_2007_0455PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/function.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/size.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/cons.hpp>
#include <boost/fusion/include/as_list.hpp>
#include <boost/fusion/include/as_vector.hpp>

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/argument.hpp>
#include <boost/spirit/home/support/context.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/nonterminal/extract_param.hpp>
#include <boost/spirit/home/support/nonterminal/locals.hpp>
#include <boost/spirit/home/karma/reference.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/karma/nonterminal/nonterminal_fwd.hpp>
#include <boost/spirit/home/karma/nonterminal/detail/generator_binder.hpp>
#include <boost/spirit/home/karma/nonterminal/detail/parameterized.hpp>

#include <boost/static_assert.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/traits.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_reference.hpp>

#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable: 4127) // conditional expression is constant
# pragma warning(disable: 4355) // 'this' : used in base member initializer list warning
#endif

namespace boost { namespace spirit { namespace karma
{
    BOOST_PP_REPEAT(SPIRIT_ATTRIBUTES_LIMIT, SPIRIT_USING_ATTRIBUTE, _)

    using spirit::_pass_type;
    using spirit::_val_type;
    using spirit::_a_type;
    using spirit::_b_type;
    using spirit::_c_type;
    using spirit::_d_type;
    using spirit::_e_type;
    using spirit::_f_type;
    using spirit::_g_type;
    using spirit::_h_type;
    using spirit::_i_type;
    using spirit::_j_type;

#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

    using spirit::_pass;
    using spirit::_val;
    using spirit::_a;
    using spirit::_b;
    using spirit::_c;
    using spirit::_d;
    using spirit::_e;
    using spirit::_f;
    using spirit::_g;
    using spirit::_h;
    using spirit::_i;
    using spirit::_j;

#endif

    using spirit::info;
    using spirit::locals;

    template <
        typename OutputIterator, typename T1, typename T2, typename T3
      , typename T4>
    struct rule
      : proto::extends<
            typename proto::terminal<
                reference<rule<OutputIterator, T1, T2, T3, T4> const>
            >::type
          , rule<OutputIterator, T1, T2, T3, T4>
        >
      , generator<rule<OutputIterator, T1, T2, T3, T4> >
    {
        typedef mpl::int_<generator_properties::all_properties> properties;

        typedef OutputIterator iterator_type;
        typedef rule<OutputIterator, T1, T2, T3, T4> this_type;
        typedef reference<this_type const> reference_;
        typedef typename proto::terminal<reference_>::type terminal;
        typedef proto::extends<terminal, this_type> base_type;
        typedef mpl::vector<T1, T2, T3, T4> template_params;

        // the output iterator is always wrapped by karma
        typedef detail::output_iterator<OutputIterator, properties>
            output_iterator;

        // locals_type is a sequence of types to be used as local variables
        typedef typename
            spirit::detail::extract_locals<template_params>::type
        locals_type;

        // The delimiter-generator type
        typedef typename
            spirit::detail::extract_component<
                karma::domain, template_params>::type
        delimiter_type;

        // The rule's encoding type
        typedef typename
            spirit::detail::extract_encoding<template_params>::type
        encoding_type;

        // The rule's signature
        typedef typename
            spirit::detail::extract_sig<template_params, encoding_type, karma::domain>::type
        sig_type;

        // This is the rule's attribute type
        typedef typename
            spirit::detail::attr_from_sig<sig_type>::type
        attr_type;
        BOOST_STATIC_ASSERT_MSG(
            !is_reference<attr_type>::value && !is_const<attr_type>::value,
            "Const/reference qualifiers on Karma rule attribute are meaningless");
        typedef attr_type const& attr_reference_type;

        // parameter_types is a sequence of types passed as parameters to the rule
        typedef typename
            spirit::detail::params_from_sig<sig_type>::type
        parameter_types;

        static size_t const params_size =
            fusion::result_of::size<parameter_types>::type::value;

        // the context passed to the right hand side of a rule contains
        // the attribute and the parameters for this particular rule invocation
        typedef context<
            fusion::cons<attr_reference_type, parameter_types>
          , locals_type>
        context_type;

        typedef function<
            bool(output_iterator&, context_type&, delimiter_type const&)>
        function_type;

        typedef typename
            mpl::if_<
                is_same<encoding_type, unused_type>
              , unused_type
              , tag::char_code<tag::encoding, encoding_type>
            >::type
        encoding_modifier_type;

        explicit rule(std::string const& name_ = "unnamed-rule")
          : base_type(terminal::make(reference_(*this)))
          , name_(name_)
        {
        }

        rule(rule const& rhs)
          : base_type(terminal::make(reference_(*this)))
          , name_(rhs.name_)
          , f(rhs.f)
        {
        }

        template <typename Auto, typename Expr>
        static void define(rule& /* lhs */, Expr const& /* expr */, mpl::false_)
        {
            // Report invalid expression error as early as possible.
            // If you got an error_invalid_expression error message here,
            // then the expression (expr) is not a valid spirit karma expression.
            BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);
        }

        template <typename Auto, typename Expr>
        static void define(rule& lhs, Expr const& expr, mpl::true_)
        {
            lhs.f = detail::bind_generator<Auto>(
                compile<karma::domain>(expr, encoding_modifier_type()));
        }

        template <typename Expr>
        rule (Expr const& expr, std::string const& name_ = "unnamed-rule")
          : base_type(terminal::make(reference_(*this)))
          , name_(name_)
        {
            define<mpl::false_>(*this, expr, traits::matches<karma::domain, Expr>());
        }

        rule& operator=(rule const& rhs)
        {
            // The following assertion fires when you try to initialize a rule
            // from an uninitialized one. Did you mean to refer to the right
            // hand side rule instead of assigning from it? In this case you
            // should write lhs = rhs.alias();
            BOOST_ASSERT(rhs.f && "Did you mean rhs.alias() instead of rhs?");

            f = rhs.f;
            name_ = rhs.name_;
            return *this;
        }

        std::string const& name() const
        {
            return name_;
        }

        void name(std::string const& str)
        {
            name_ = str;
        }

        template <typename Expr>
        rule& operator=(Expr const& expr)
        {
            define<mpl::false_>(*this, expr, traits::matches<karma::domain, Expr>());
            return *this;
        }

// VC7.1 has problems to resolve 'rule' without explicit template parameters
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)
        // g++ 3.3 barfs if this is a member function :(
        template <typename Expr>
        friend rule& operator%=(rule& r, Expr const& expr)
        {
            define<mpl::true_>(r, expr, traits::matches<karma::domain, Expr>());
            return r;
        }

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        // non-const version needed to suppress proto's %= kicking in
        template <typename Expr>
        friend rule& operator%=(rule& r, Expr& expr)
        {
            return r %= static_cast<Expr const&>(expr);
        }
#else
        // for rvalue references
        template <typename Expr>
        friend rule& operator%=(rule& r, Expr&& expr)
        {
            define<mpl::true_>(r, expr, traits::matches<karma::domain, Expr>());
            return r;
        }
#endif

#else
        // both friend functions have to be defined out of class as VC7.1
        // will complain otherwise
        template <typename OutputIterator_, typename T1_, typename T2_
          , typename T3_, typename T4_, typename Expr>
        friend rule<OutputIterator_, T1_, T2_, T3_, T4_>& operator%=(
            rule<OutputIterator_, T1_, T2_, T3_, T4_>&r, Expr const& expr);

        // non-const version needed to suppress proto's %= kicking in
        template <typename OutputIterator_, typename T1_, typename T2_
          , typename T3_, typename T4_, typename Expr>
        friend rule<OutputIterator_, T1_, T2_, T3_, T4_>& operator%=(
            rule<OutputIterator_, T1_, T2_, T3_, T4_>& r, Expr& expr);
#endif

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef attr_type type;
        };

        template <typename Context, typename Delimiter, typename Attribute>
        bool generate(output_iterator& sink, Context&, Delimiter const& delim
          , Attribute const& attr) const
        {
            if (f)
            {
                // Create an attribute if none is supplied.
                typedef traits::transform_attribute<
                    Attribute const, attr_type, domain>
                transform;

                typename transform::type attr_ = transform::pre(attr);

                // If you are seeing a compilation error here, you are probably
                // trying to use a rule or a grammar which has inherited
                // attributes, without passing values for them.
                context_type context(attr_);

                // If you are seeing a compilation error here stating that the
                // third parameter can't be converted to a karma::reference
                // then you are probably trying to use a rule or a grammar with
                // an incompatible delimiter type.
                if (f(sink, context, delim))
                {
                    // do a post-delimit if this is an implied verbatim
                    if (is_same<delimiter_type, unused_type>::value)
                        karma::delimit_out(sink, delim);

                    return true;
                }
            }
            return false;
        }

        template <typename Context, typename Delimiter, typename Attribute
          , typename Params>
        bool generate(output_iterator& sink, Context& caller_context
          , Delimiter const& delim, Attribute const& attr
          , Params const& params) const
        {
            if (f)
            {
                // Create an attribute if none is supplied.
                typedef traits::transform_attribute<
                    Attribute const, attr_type, domain>
                transform;

                typename transform::type attr_ = transform::pre(attr);

                // If you are seeing a compilation error here, you are probably
                // trying to use a rule or a grammar which has inherited
                // attributes, passing values of incompatible types for them.
                context_type context(attr_, params, caller_context);

                // If you are seeing a compilation error here stating that the
                // third parameter can't be converted to a karma::reference
                // then you are probably trying to use a rule or a grammar with
                // an incompatible delimiter type.
                if (f(sink, context, delim))
                {
                    // do a post-delimit if this is an implied verbatim
                    if (is_same<delimiter_type, unused_type>::value)
                        karma::delimit_out(sink, delim);

                    return true;
                }
            }
            return false;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info(name_);
        }

        reference_ alias() const
        {
            return reference_(*this);
        }

        typename proto::terminal<this_type>::type copy() const
        {
            typename proto::terminal<this_type>::type result = {*this};
            return result;
        }

        // bring in the operator() overloads
        rule const& get_parameterized_subject() const { return *this; }
        typedef rule parameterized_subject_type;
        #include <boost/spirit/home/karma/nonterminal/detail/fcall.hpp>

        std::string name_;
        function_type f;
    };

#if BOOST_WORKAROUND(BOOST_MSVC, < 1400)
    template <typename OutputIterator_, typename T1_, typename T2_
      , typename T3_, typename T4_, typename Expr>
    rule<OutputIterator_, T1_, T2_, T3_, T4_>& operator%=(
        rule<OutputIterator_, T1_, T2_, T3_, T4_>&r, Expr const& expr)
    {
        // Report invalid expression error as early as possible.
        // If you got an error_invalid_expression error message here, then
        // the expression (expr) is not a valid spirit karma expression.
        BOOST_SPIRIT_ASSERT_MATCH(karma::domain, Expr);

        typedef typename
            rule<OutputIterator_, T1_, T2_, T3_, T4_>::encoding_modifier_type
        encoding_modifier_type;

        r.f = detail::bind_generator<mpl::true_>(
            compile<karma::domain>(expr, encoding_modifier_type()));
        return r;
    }

    // non-const version needed to suppress proto's %= kicking in
    template <typename OutputIterator_, typename T1_, typename T2_
      , typename T3_, typename T4_, typename Expr>
    rule<OutputIterator_, T1_, T2_, T3_, T4_>& operator%=(
        rule<OutputIterator_, T1_, T2_, T3_, T4_>& r, Expr& expr)
    {
        return r %= static_cast<Expr const&>(expr);
    }
#endif
}}}

namespace boost { namespace spirit { namespace traits
{
    namespace detail
    {
        template <typename RuleAttribute, typename Attribute>
        struct nonterminal_handles_container
          : mpl::and_<
                traits::is_container<RuleAttribute>
              , is_convertible<Attribute, RuleAttribute> >
        {};
    }

    ///////////////////////////////////////////////////////////////////////////
    template <
        typename IteratorA, typename IteratorB, typename Attribute
      , typename Context, typename T1, typename T2, typename T3, typename T4>
    struct handles_container<
            karma::rule<IteratorA, T1, T2, T3, T4>, Attribute, Context
          , IteratorB>
      : detail::nonterminal_handles_container<
            typename attribute_of<
                karma::rule<IteratorA, T1, T2, T3, T4>
              , Context, IteratorB
            >::type, Attribute>
    {};
}}}

#if defined(BOOST_MSVC)
# pragma warning(pop)
#endif

#endif

/* rule.hpp
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
*/