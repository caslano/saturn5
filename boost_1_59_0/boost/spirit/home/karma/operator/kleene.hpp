//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_KLEENE_MAR_03_2007_0337AM)
#define BOOST_SPIRIT_KARMA_KLEENE_MAR_03_2007_0337AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/karma/detail/indirect_iterator.hpp>
#include <boost/spirit/home/karma/detail/get_stricttag.hpp>
#include <boost/spirit/home/karma/detail/pass_container.hpp>
#include <boost/spirit/home/karma/detail/fail_function.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/container.hpp>
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
    struct use_operator<karma::domain, proto::tag::dereference> // enables *g
      : mpl::true_ {};
}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    template <typename Subject, typename Strict, typename Derived>
    struct base_kleene : unary_generator<Derived>
    {
    private:
        // Ignore return value in relaxed mode (failing subject generators 
        // are just skipped). This allows to selectively generate items in 
        // the provided attribute.
        template <typename F, typename Attribute>
        bool generate_subject(F f, Attribute const&, mpl::false_) const
        {
            bool r = !f(subject);
            if (!r && !f.is_at_end())
                f.next();
            return true;
        }

        template <typename F, typename Attribute>
        bool generate_subject(F f, Attribute const&, mpl::true_) const
        {
            return !f(subject);
        }

        // There is no way to distinguish a failed generator from a 
        // generator to be skipped. We assume the user takes responsibility 
        // for ending the loop if no attribute is specified.
        template <typename F>
        bool generate_subject(F f, unused_type, mpl::false_) const
        {
            return !f(subject);
        }

//         template <typename F>
//         bool generate_subject(F f, unused_type, mpl::true_) const
//         {
//             return !f(subject);
//         }

    public:
        typedef Subject subject_type;
        typedef typename subject_type::properties properties;

        // Build a std::vector from the subject's attribute. Note
        // that build_std_vector may return unused_type if the
        // subject's attribute is an unused_type.
        template <typename Context, typename Iterator>
        struct attribute
          : traits::build_std_vector<
                typename traits::attribute_of<Subject, Context, Iterator>::type
            >
        {};

        base_kleene(Subject const& subject)
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

            pass_container pass(fail_function(sink, ctx, d), 
                indirect_iterator_type(it), indirect_iterator_type(end));

            // kleene fails only if the underlying output fails
            while (!pass.is_at_end())
            {
                if (!generate_subject(pass, attr, Strict()))
                    break;
            }
            return detail::sink_is_good(sink);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("kleene", subject.what(context));
        }

        Subject subject;
    };

    template <typename Subject>
    struct kleene 
      : base_kleene<Subject, mpl::false_, kleene<Subject> >
    {
        typedef base_kleene<Subject, mpl::false_, kleene> base_kleene_;

        kleene(Subject const& subject)
          : base_kleene_(subject) {}
    };

    template <typename Subject>
    struct strict_kleene 
      : base_kleene<Subject, mpl::true_, strict_kleene<Subject> >
    {
        typedef base_kleene<Subject, mpl::true_, strict_kleene> base_kleene_;

        strict_kleene(Subject const& subject)
          : base_kleene_(subject) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Subject, bool strict_mode = false>
        struct make_kleene 
          : make_unary_composite<Subject, kleene>
        {};

        template <typename Subject>
        struct make_kleene<Subject, true> 
          : make_unary_composite<Subject, strict_kleene>
        {};
    }

    template <typename Subject, typename Modifiers>
    struct make_composite<proto::tag::dereference, Subject, Modifiers>
      : detail::make_kleene<Subject, detail::get_stricttag<Modifiers>::value>
    {};
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject>
    struct has_semantic_action<karma::kleene<Subject> >
      : unary_has_semantic_action<Subject> {};

    template <typename Subject>
    struct has_semantic_action<karma::strict_kleene<Subject> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<karma::kleene<Subject>, Attribute
          , Context, Iterator> 
      : mpl::true_ {};

    template <typename Subject, typename Attribute, typename Context
      , typename Iterator>
    struct handles_container<karma::strict_kleene<Subject>, Attribute
          , Context, Iterator> 
      : mpl::true_ {};
}}}

#endif

/* kleene.hpp
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
*/