//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2001-2011 Joel de Guzman
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SPIRIT_KARMA_OPERATOR_LIST_HPP
#define BOOST_SPIRIT_KARMA_OPERATOR_LIST_HPP

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

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_operator<karma::domain, proto::tag::modulus> // enables g % d
      : mpl::true_ {};
}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
    template <typename Left, typename Right, typename Strict, typename Derived>
    struct base_list : binary_generator<Derived>
    {
    private:
        // iterate over the given container until its exhausted or the embedded
        // (left) generator succeeds
        template <typename F, typename Attribute>
        bool generate_left(F f, Attribute const&, mpl::false_) const
        {
            // Failing subject generators are just skipped. This allows to
            // selectively generate items in the provided attribute.
            while (!f.is_at_end())
            {
                bool r = !f(left);
                if (r)
                    return true;
                if (!f.is_at_end())
                    f.next();
            }
            return false;
        }

        template <typename F, typename Attribute>
        bool generate_left(F f, Attribute const&, mpl::true_) const
        {
            return !f(left);
        }

        // There is no way to distinguish a failed generator from a
        // generator to be skipped. We assume the user takes responsibility
        // for ending the loop if no attribute is specified.
        template <typename F>
        bool generate_left(F f, unused_type, mpl::false_) const
        {
            return !f(left);
        }

    public:
        typedef Left left_type;
        typedef Right right_type;

        typedef mpl::int_<
            left_type::properties::value
          | right_type::properties::value
          | generator_properties::buffering
          | generator_properties::counting
        > properties;

        // Build a std::vector from the LHS's attribute. Note
        // that build_std_vector may return unused_type if the
        // subject's attribute is an unused_type.
        template <typename Context, typename Iterator>
        struct attribute
          : traits::build_std_vector<
                typename traits::attribute_of<Left, Context, Iterator>::type>
        {};

        base_list(Left const& left, Right const& right)
          : left(left), right(right)
        {}

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& ctx
          , Delimiter const& d, Attribute const& attr) const
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

            if (generate_left(pass, attr, Strict()))
            {
                while (!pass.is_at_end())
                {
                    // wrap the given output iterator as generate_left might fail
                    detail::enable_buffering<OutputIterator> buffering(sink);
                    {
                        detail::disable_counting<OutputIterator> nocounting(sink);

                        if (!right.generate(sink, ctx, d, unused))
                            return false;     // shouldn't happen

                        if (!generate_left(pass, attr, Strict()))
                            break;            // return true as one item succeeded
                    }
                    buffering.buffer_copy();
                }
                return detail::sink_is_good(sink);
            }
            return false;
        }

        template <typename Context>
        info what(Context& context) const
        {
            return info("list",
                std::make_pair(left.what(context), right.what(context)));
        }

        Left left;
        Right right;
    };

    template <typename Left, typename Right>
    struct list
      : base_list<Left, Right, mpl::false_, list<Left, Right> >
    {
        typedef base_list<Left, Right, mpl::false_, list> base_list_;

        list(Left const& left, Right const& right)
          : base_list_(left, right) {}
    };

    template <typename Left, typename Right>
    struct strict_list
      : base_list<Left, Right, mpl::true_, strict_list<Left, Right> >
    {
        typedef base_list<Left, Right, mpl::true_, strict_list> base_list_;

        strict_list (Left const& left, Right const& right)
          : base_list_(left, right) {}
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Subject, bool strict_mode = false>
        struct make_list
          : make_binary_composite<Subject, list>
        {};

        template <typename Subject>
        struct make_list<Subject, true>
          : make_binary_composite<Subject, strict_list>
        {};
    }

    template <typename Subject, typename Modifiers>
    struct make_composite<proto::tag::modulus, Subject, Modifiers>
      : detail::make_list<Subject, detail::get_stricttag<Modifiers>::value>
    {};
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Left, typename Right>
    struct has_semantic_action<karma::list<Left, Right> >
      : binary_has_semantic_action<Left, Right> {};

    template <typename Left, typename Right>
    struct has_semantic_action<karma::strict_list<Left, Right> >
      : binary_has_semantic_action<Left, Right> {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Left, typename Right, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<karma::list<Left, Right>, Attribute
          , Context, Iterator>
      : mpl::true_ {};

    template <typename Left, typename Right, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<karma::strict_list<Left, Right>, Attribute
          , Context, Iterator>
      : mpl::true_ {};
}}}

#endif

/* list.hpp
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
*/