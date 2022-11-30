//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_DIRECTIVE_REPEAT_HPP
#define BOOST_SPIRIT_KARMA_DIRECTIVE_REPEAT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/detail/output_iterator.hpp>
#include <boost/spirit/home/karma/detail/get_stricttag.hpp>
#include <boost/spirit/home/karma/generator.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/operator/kleene.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/fusion/include/at.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_directive<karma::domain, tag::repeat>   // enables repeat[p]
      : mpl::true_ {};

    template <typename T>
    struct use_directive<karma::domain
      , terminal_ex<tag::repeat                     // enables repeat(exact)[p]
        , fusion::vector1<T> >
    > : mpl::true_ {};

    template <typename T>
    struct use_directive<karma::domain
      , terminal_ex<tag::repeat                     // enables repeat(min, max)[p]
        , fusion::vector2<T, T> >
    > : mpl::true_ {};

    template <typename T>
    struct use_directive<karma::domain
      , terminal_ex<tag::repeat                     // enables repeat(min, inf)[p]
        , fusion::vector2<T, inf_type> >
    > : mpl::true_ {};

    template <>                                     // enables *lazy* repeat(exact)[p]
    struct use_lazy_directive<
        karma::domain
      , tag::repeat
      , 1 // arity
    > : mpl::true_ {};

    template <>                                     // enables *lazy* repeat(min, max)[p]
    struct use_lazy_directive<                      // and repeat(min, inf)[p]
        karma::domain
      , tag::repeat
      , 2 // arity
    > : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::repeat;
    using spirit::inf;
#endif
    using spirit::repeat_type;
    using spirit::inf_type;

    ///////////////////////////////////////////////////////////////////////////
    // handles repeat(exact)[p]
    template <typename T>
    struct exact_iterator
    {
        exact_iterator(T const exact)
          : exact(exact) {}

        typedef T type;
        T start() const { return 0; }
        bool got_max(T i) const { return i >= exact; }
        bool got_min(T i) const { return i >= exact; }

        T const exact;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(exact_iterator& operator= (exact_iterator const&))
    };

    // handles repeat(min, max)[p]
    template <typename T>
    struct finite_iterator
    {
        finite_iterator(T const min, T const max)
          : min BOOST_PREVENT_MACRO_SUBSTITUTION (min)
          , max BOOST_PREVENT_MACRO_SUBSTITUTION (max) {}

        typedef T type;
        T start() const { return 0; }
        bool got_max(T i) const { return i >= max; }
        bool got_min(T i) const { return i >= min; }

        T const min;
        T const max;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(finite_iterator& operator= (finite_iterator const&))
    };

    // handles repeat(min, inf)[p]
    template <typename T>
    struct infinite_iterator
    {
        infinite_iterator(T const min)
          : min BOOST_PREVENT_MACRO_SUBSTITUTION (min) {}

        typedef T type;
        T start() const { return 0; }
        bool got_max(T /*i*/) const { return false; }
        bool got_min(T i) const { return i >= min; }

        T const min;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(infinite_iterator& operator= (infinite_iterator const&))
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename LoopIter, typename Strict
      , typename Derived>
    struct base_repeat_generator : unary_generator<Derived>
    {
    private:
        // iterate over the given container until its exhausted or the embedded
        // generator succeeds
        template <typename F, typename Attribute>
        bool generate_subject(F f, Attribute const&, mpl::false_) const
        {
            // Failing subject generators are just skipped. This allows to 
            // selectively generate items in the provided attribute.
            while (!f.is_at_end())
            {
                bool r = !f(subject);
                if (r) 
                    return true;
                if (!f.is_at_end())
                    f.next();
            }
            return false;
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

    public:
        typedef Subject subject_type;

        typedef mpl::int_<subject_type::properties::value> properties;

        // Build a std::vector from the subject's attribute. Note
        // that build_std_vector may return unused_type if the
        // subject's attribute is an unused_type.
        template <typename Context, typename Iterator>
        struct attribute
          : traits::build_std_vector<
                typename traits::attribute_of<Subject, Context, Iterator>::type
            >
        {};

        base_repeat_generator(Subject const& subject, LoopIter const& iter)
          : subject(subject), iter(iter) {}

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx, Delimiter const& d
          , Attribute const& attr) const
        {
            typedef detail::fail_function<
                OutputIterator, Context, Delimiter
            > fail_function;

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

            // generate the minimal required amount of output
            typename LoopIter::type i = iter.start();
            for (/**/; !pass.is_at_end() && !iter.got_min(i); ++i)
            {
                if (!generate_subject(pass, attr, Strict()))
                {
                    // if we fail before reaching the minimum iteration
                    // required, do not output anything and return false
                    return false;
                }
            }

            if (pass.is_at_end() && !iter.got_min(i))
                return false;   // insufficient attribute elements

            // generate some more up to the maximum specified
            for (/**/; !pass.is_at_end() && !iter.got_max(i); ++i)
            {
                if (!generate_subject(pass, attr, Strict()))
                    break;
            }
            return detail::sink_is_good(sink);
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("repeat", subject.what(context));
        }

        Subject subject;
        LoopIter iter;
    };

    template <typename Subject, typename LoopIter>
    struct repeat_generator 
      : base_repeat_generator<
            Subject, LoopIter, mpl::false_
          , repeat_generator<Subject, LoopIter> >
    {
        typedef base_repeat_generator<
            Subject, LoopIter, mpl::false_, repeat_generator
        > base_repeat_generator_;

        repeat_generator(Subject const& subject, LoopIter const& iter)
          : base_repeat_generator_(subject, iter) {}
    };

    template <typename Subject, typename LoopIter>
    struct strict_repeat_generator 
      : base_repeat_generator<
            Subject, LoopIter, mpl::true_
          , strict_repeat_generator<Subject, LoopIter> >
    {
        typedef base_repeat_generator<
            Subject, LoopIter, mpl::true_, strict_repeat_generator
        > base_repeat_generator_;

        strict_repeat_generator(Subject const& subject, LoopIter const& iter)
          : base_repeat_generator_(subject, iter) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Modifiers>
    struct make_directive<tag::repeat, Subject, Modifiers>
    {
        typedef typename mpl::if_<
            detail::get_stricttag<Modifiers>
          , strict_kleene<Subject>, kleene<Subject>
        >::type result_type;

        result_type operator()(unused_type, Subject const& subject
          , unused_type) const
        {
            return result_type(subject);
        }
    };

    template <typename T, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::repeat, fusion::vector1<T> >, Subject, Modifiers>
    {
        typedef exact_iterator<T> iterator_type;

        typedef typename mpl::if_<
            detail::get_stricttag<Modifiers>
          , strict_repeat_generator<Subject, iterator_type>
          , repeat_generator<Subject, iterator_type>
        >::type result_type;

        template <typename Terminal>
        result_type operator()(
            Terminal const& term, Subject const& subject, unused_type) const
        {
            return result_type(subject, fusion::at_c<0>(term.args));
        }
    };

    template <typename T, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::repeat, fusion::vector2<T, T> >, Subject, Modifiers>
    {
        typedef finite_iterator<T> iterator_type;

        typedef typename mpl::if_<
            detail::get_stricttag<Modifiers>
          , strict_repeat_generator<Subject, iterator_type>
          , repeat_generator<Subject, iterator_type>
        >::type result_type;

        template <typename Terminal>
        result_type operator()(
            Terminal const& term, Subject const& subject, unused_type) const
        {
            return result_type(subject,
                iterator_type(
                    fusion::at_c<0>(term.args)
                  , fusion::at_c<1>(term.args)
                )
            );
        }
    };

    template <typename T, typename Subject, typename Modifiers>
    struct make_directive<
        terminal_ex<tag::repeat
        , fusion::vector2<T, inf_type> >, Subject, Modifiers>
    {
        typedef infinite_iterator<T> iterator_type;

        typedef typename mpl::if_<
            detail::get_stricttag<Modifiers>
          , strict_repeat_generator<Subject, iterator_type>
          , repeat_generator<Subject, iterator_type>
        >::type result_type;

        template <typename Terminal>
        result_type operator()(
            Terminal const& term, Subject const& subject, unused_type) const
        {
            return result_type(subject, fusion::at_c<0>(term.args));
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename LoopIter>
    struct has_semantic_action<karma::repeat_generator<Subject, LoopIter> >
      : unary_has_semantic_action<Subject> {};

    template <typename Subject, typename LoopIter>
    struct has_semantic_action<karma::strict_repeat_generator<Subject, LoopIter> >
      : unary_has_semantic_action<Subject> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename LoopIter, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<
            karma::repeat_generator<Subject, LoopIter>, Attribute
          , Context, Iterator> 
      : mpl::true_ {};

    template <typename Subject, typename LoopIter, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<
            karma::strict_repeat_generator<Subject, LoopIter>, Attribute
          , Context, Iterator> 
      : mpl::true_ {};
}}}

#endif

/* repeat.hpp
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
*/