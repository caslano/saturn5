/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_RULE_HPP)
#define BOOST_SPIRIT_RULE_HPP

#include <boost/static_assert.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Spirit predefined maximum number of simultaneously usable different
//  scanner types.
//
//  This limit defines the maximum number of possible different scanner
//  types for which a specific rule<> may be used. If this isn't defined, a
//  rule<> may be used with one scanner type only (multiple scanner support
//  is disabled).
//
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT)
#  define BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT 1
#endif

//  Ensure a meaningful maximum number of simultaneously usable scanner types
BOOST_STATIC_ASSERT(BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT > 0);

#include <boost/scoped_ptr.hpp>
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/non_terminal/impl/rule.ipp>

#if BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT > 1
#  include <boost/preprocessor/enum_params.hpp>
#endif

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

#if BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT > 1

    ///////////////////////////////////////////////////////////////////////////
    //
    //  scanner_list (a fake scanner)
    //
    //      Typically, rules are tied to a specific scanner type and
    //      a particular rule cannot be used with anything else. Sometimes
    //      there's a need for rules that can accept more than one scanner
    //      type. The scanner_list<S0, ...SN> can be used as a template
    //      parameter to the rule class to specify up to the number of
    //      scanner types defined by the BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT
    //      constant. Example:
    //
    //          rule<scanner_list<ScannerT0, ScannerT1> > r;
    //
    //      *** This feature is available only to compilers that support
    //      partial template specialization. ***
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        BOOST_PP_ENUM_PARAMS(
            BOOST_SPIRIT_RULE_SCANNERTYPE_LIMIT,
            typename ScannerT
        )
    >
    struct scanner_list : scanner_base {};

#endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  rule class
    //
    //      The rule is a polymorphic parser that acts as a named place-
    //      holder capturing the behavior of an EBNF expression assigned to
    //      it.
    //
    //      The rule is a template class parameterized by:
    //
    //          1) scanner (scanner_t, see scanner.hpp),
    //          2) the rule's context (context_t, see parser_context.hpp)
    //          3) an arbitrary tag (tag_t, see parser_id.hpp) that allows
    //             a rule to be tagged for identification.
    //
    //      These template parameters may be specified in any order. The
    //      scanner will default to scanner<> when it is not specified.
    //      The context will default to parser_context when not specified.
    //      The tag will default to parser_address_tag when not specified.
    //
    //      The definition of the rule (its right hand side, RHS) held by
    //      the rule through a scoped_ptr. When a rule is seen in the RHS
    //      of an assignment or copy construction EBNF expression, the rule
    //      is held by the LHS rule by reference.
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T0 = nil_t
      , typename T1 = nil_t
      , typename T2 = nil_t
    >
    class rule
        : public impl::rule_base<
            rule<T0, T1, T2>
          , rule<T0, T1, T2> const&
          , T0, T1, T2>
    {
    public:

        typedef rule<T0, T1, T2> self_t;
        typedef impl::rule_base<
            self_t
          , self_t const&
          , T0, T1, T2>
        base_t;

        typedef typename base_t::scanner_t scanner_t;
        typedef typename base_t::attr_t attr_t;
        typedef impl::abstract_parser<scanner_t, attr_t> abstract_parser_t;

        rule() : ptr() {}
        ~rule() {}

        rule(rule const& r)
        : ptr(new impl::concrete_parser<rule, scanner_t, attr_t>(r)) {}

        template <typename ParserT>
        rule(ParserT const& p)
        : ptr(new impl::concrete_parser<ParserT, scanner_t, attr_t>(p)) {}

        template <typename ParserT>
        rule& operator=(ParserT const& p)
        {
            ptr.reset(new impl::concrete_parser<ParserT, scanner_t, attr_t>(p));
            return *this;
        }

        rule& operator=(rule const& r)
        {
            ptr.reset(new impl::concrete_parser<rule, scanner_t, attr_t>(r));
            return *this;
        }

        rule<T0, T1, T2>
        copy() const
        {
            return rule<T0, T1, T2>(ptr.get() ? ptr->clone() : 0);
        }

    private:
        friend class impl::rule_base_access;

        abstract_parser_t*
        get() const
        {
            return ptr.get();
        }

        rule(abstract_parser_t* ptr_)
        : ptr(ptr_) {}

        rule(abstract_parser_t const* ptr_)
        : ptr(ptr_) {}

        scoped_ptr<abstract_parser_t> ptr;
    };

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* rule.hpp
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
*/