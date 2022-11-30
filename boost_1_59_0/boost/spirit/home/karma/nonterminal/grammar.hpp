//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_GRAMMAR_MAR_05_2007_0542PM)
#define BOOST_SPIRIT_KARMA_GRAMMAR_MAR_05_2007_0542PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/assert_msg.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/nonterminal/rule.hpp>
#include <boost/spirit/home/karma/nonterminal/nonterminal_fwd.hpp>
#include <boost/spirit/home/karma/reference.hpp>
#include <boost/noncopyable.hpp>
#include <boost/proto/extends.hpp>
#include <boost/proto/traits.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace spirit { namespace karma
{
    template <
        typename OutputIterator, typename T1, typename T2, typename T3
      , typename T4>
    struct grammar
      : proto::extends<
            typename proto::terminal<
                reference<rule<OutputIterator, T1, T2, T3, T4> const>
            >::type
          , grammar<OutputIterator, T1, T2, T3, T4>
        >
      , generator<grammar<OutputIterator, T1, T2, T3, T4> >
      , noncopyable
    {
        typedef OutputIterator iterator_type;
        typedef rule<OutputIterator, T1, T2, T3, T4> start_type;
        typedef typename start_type::properties properties;
        typedef typename start_type::sig_type sig_type;
        typedef typename start_type::locals_type locals_type;
        typedef typename start_type::delimiter_type delimiter_type;
        typedef typename start_type::encoding_type encoding_type;
        typedef grammar<OutputIterator, T1, T2, T3, T4> base_type;
        typedef reference<start_type const> reference_;
        typedef typename proto::terminal<reference_>::type terminal;

        static size_t const params_size = start_type::params_size;

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef typename start_type::attr_type type;
        };

        // the output iterator is always wrapped by karma
        typedef detail::output_iterator<OutputIterator, properties> 
            output_iterator;

        grammar(start_type const& start
              , std::string const& name_ = "unnamed-grammar")
          : proto::extends<terminal, base_type>(terminal::make(reference_(start)))
          , name_(name_)
        {}

        // This constructor is used to catch if the start rule is not 
        // compatible with the grammar. 
        template <typename Iterator_, typename T1_, typename T2_, typename T3_,
            typename T4_>
        grammar(rule<Iterator_, T1_, T2_, T3_, T4_> const&
              , std::string const& = "unnamed-grammar")
        {
            // If you see the assertion below failing then the start rule 
            // passed to the constructor of the grammar is not compatible with 
            // the grammar (i.e. it uses different template parameters).
            BOOST_SPIRIT_ASSERT_MSG(
                (is_same<start_type, rule<Iterator_, T1_, T2_, T3_, T4_> >::value)
              , incompatible_start_rule, (rule<Iterator_, T1_, T2_, T3_, T4_>));
        }

        std::string name() const
        {
            return name_;
        }

        void name(std::string const& str)
        {
            name_ = str;
        }

        template <typename Context, typename Delimiter, typename Attribute>
        bool generate(output_iterator& sink, Context& context
          , Delimiter const& delim, Attribute const& attr) const
        {
            return this->proto_base().child0.generate(
                sink, context, delim, attr);
        }

        template <typename Context>
        info what(Context&) const
        {
            return info(name_);
        }

        // bring in the operator() overloads
        start_type const& get_parameterized_subject() const
        { return this->proto_base().child0.ref.get(); }
        typedef start_type parameterized_subject_type;
        #include <boost/spirit/home/karma/nonterminal/detail/fcall.hpp>

        std::string name_;
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename IteratorA, typename IteratorB, typename Attribute
      , typename Context, typename T1, typename T2, typename T3, typename T4>
    struct handles_container<
            karma::grammar<IteratorA, T1, T2, T3, T4>, Attribute, Context
          , IteratorB>
      : detail::nonterminal_handles_container< 
            typename attribute_of<
                karma::grammar<IteratorA, T1, T2, T3, T4>
              , Context, IteratorB
          >::type, Attribute>
    {};
}}}

#endif

/* grammar.hpp
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
*/