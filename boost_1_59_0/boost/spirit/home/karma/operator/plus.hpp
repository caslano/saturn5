//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_POSITIVE_MAR_03_2007_0945PM)
#define BOOST_SPIRIT_KARMA_POSITIVE_MAR_03_2007_0945PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/detail/indirect_iterator.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/karma/detail/get_stricttag.hpp>
#include <boost/spirit/home/karma/detail/pass_container.hpp>
#include <boost/spirit/home/karma/detail/fail_function.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/proto/operators.hpp>
#include <boost/proto/tags.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_operator<karma::domain, proto::tag::unary_plus> // enables +g
      : mpl::true_ {};
}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    template <typename Subject, typename Strict, typename Derived>
    struct base_plus : unary_generator<Derived>
    {
    private:
        // Ignore return value in relaxed mode (failing subject generators 
        // are just skipped). This allows to selectively generate items in 
        // the provided attribute.
        template <typename F, typename Attribute>
        bool generate_subject(F f, Attribute const&, bool& result, mpl::false_) const
        {
            bool r = !f(subject);
            if (r) 
                result = true;
            else if (!f.is_at_end())
                f.next();
            return true;
        }

        template <typename F, typename Attribute>
        bool generate_subject(F f, Attribute const&, bool& result, mpl::true_) const
        {
            bool r = !f(subject);
            if (r)
                result = true;
            return r;
        }

        // There is no way to distinguish a failed generator from a 
        // generator to be skipped. We assume the user takes responsibility
        // for ending the loop if no attribute is specified.
        template <typename F>
        bool generate_subject(F f, unused_type, bool& result, mpl::false_) const
        {
            bool r = f(subject);
            if (!r)
                result = true;
            return !r;
        }

//         template <typename F>
//         bool generate_subject(F f, unused_type, bool& result, mpl::true_) const
//         {
//             bool r = f(subject);
//             if (!r)
//                 result = true;
//             return !r;
//         }

    public:
        typedef Subject subject_type;
        typedef typename subject_type::properties properties;

        // Build a std::vector from the subjects attribute. Note
        // that build_std_vector may return unused_type if the
        // subject's attribute is an unused_type.
        template <typename Context, typename Iterator>
        struct attribute
          : traits::build_std_vector<
                typename traits::attribute_of<subject_type, Context, Iterator>::type
            >
        {};

        base_plus(Subject const& subject)
          : subject(subject) {}

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx
          , Delimiter const& d, Attribute const& attr) const
        {
            typedef detail::fail_function<
                OutputIterator, Context, Delimiter> fail_function;

            typedef typename traits::container_iterator<
                typename add_const<Attribute>::type
            >::type iterator_type;

            typedef 
                typename traits::make_indirect_iterator<iterator_type>::type 
            indirect_iterator_type;
            typedef detail::pass_container<
                fail_function, Attribute, indirect_iterator_type, mpl::false_>
            pass_container;

            iterator_type it = traits::begin(attr);
            iterator_type end = traits::end(attr);

            // plus fails if the parameter is empty
            if (traits::compare(it, end))
                return false;

            pass_container pass(fail_function(sink, ctx, d), 
                indirect_iterator_type(it), indirect_iterator_type(end));

            // from now on plus fails if the underlying output fails or overall
            // no subject generators succeeded
            bool result = false;
            while (!pass.is_at_end())
            {
                if (!generate_subject(pass, attr, result, Strict()))
                    break;
            }
            return result && detail::sink_is_good(sink);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("plus", subject.what(context));
        }

        Subject subject;
    };

    template <typename Subject>
    struct plus 
      : base_plus<Subject, mpl::false_, plus<Subject> >
    {
        typedef base_plus<Subject, mpl::false_, plus> base_plus_;

        plus(Subject const& subject)
          : base_plus_(subject) {}
    };

    template <typename Subject>
    struct strict_plus 
      : base_plus<Subject, mpl::true_, strict_plus<Subject> >
    {
        typedef base_plus<Subject, mpl::true_, strict_plus> base_plus_;

        strict_plus(Subject const& subject)
          : base_plus_(subject) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Elements, bool strict_mode = false>
        struct make_plus 
          : make_unary_composite<Elements, plus>
        {};

        template <typename Elements>
        struct make_plus<Elements, true> 
          : make_unary_composite<Elements, strict_plus>
        {};
    }

    template <typename Elements, typename Modifiers>
    struct make_composite<proto::tag::unary_plus, Elements, Modifiers>
      : detail::make_plus<Elements, detail::get_stricttag<Modifiers>::value>
    {};
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<karma::plus<Subject> >
      : unary_has_semantic_action<Subject> {};

    template <typename Subject>
    struct has_semantic_action<karma::strict_plus<Subject> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<karma::plus<Subject>, Attribute
          , Context, Iterator>
      : mpl::true_ {};

    template <typename Subject, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<karma::strict_plus<Subject>, Attribute
          , Context, Iterator>
      : mpl::true_ {};
}}}

#endif

/* plus.hpp
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
*/