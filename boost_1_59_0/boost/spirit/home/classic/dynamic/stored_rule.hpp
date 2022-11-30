/*=============================================================================
    Copyright (c) 1998-2003 Joel de Guzman
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_STORED_RULE_HPP)
#define BOOST_SPIRIT_STORED_RULE_HPP

///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/non_terminal/impl/rule.ipp>
#include <boost/spirit/home/classic/dynamic/rule_alias.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/spirit/home/classic/dynamic/stored_rule_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  stored_rule class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T0 
      , typename T1
      , typename T2
      , bool EmbedByValue
    >
    class stored_rule
        : public impl::rule_base<
            stored_rule<T0, T1, T2, EmbedByValue>
          , typename mpl::if_c<
                EmbedByValue
              , stored_rule<T0, T1, T2, true>
              , stored_rule<T0, T1, T2> const&>::type
          , T0, T1, T2>
    {
    public:

        typedef stored_rule<T0, T1, T2, EmbedByValue> self_t;
        typedef impl::rule_base<
            self_t
          , typename mpl::if_c<
                EmbedByValue
              , stored_rule<T0, T1, T2, true>
              , self_t const&>::type
          , T0, T1, T2>
        base_t;

        typedef typename base_t::scanner_t scanner_t;
        typedef typename base_t::attr_t attr_t;
        typedef impl::abstract_parser<scanner_t, attr_t> abstract_parser_t;
        typedef rule_alias<self_t> alias_t;

        stored_rule() : ptr() {}
        ~stored_rule() {}

        stored_rule(stored_rule const& r)
        : ptr(r.ptr) {}

        template <typename ParserT>
        stored_rule(ParserT const& p)
        : ptr(new impl::concrete_parser<ParserT, scanner_t, attr_t>(p)) {}

        template <typename ParserT>
        stored_rule& operator=(ParserT const& p)
        {
            ptr.reset(new impl::concrete_parser<ParserT, scanner_t, attr_t>(p));
            return *this;
        }

        stored_rule& operator=(stored_rule const& r)
        {
            //  If this is placed above the templatized assignment
            //  operator, VC6 incorrectly complains ambiguity with
            //  r1 = r2, where r1 and r2 are both rules.
            ptr = r.ptr;
            return *this;
        }

        stored_rule<T0, T1, T2, true>
        copy() const
        {
            return stored_rule<T0, T1, T2, true>(ptr);
        }

        alias_t
        alias() const
        {
            return alias_t(*this);
        }

    private:

        friend class impl::rule_base_access;
        friend class stored_rule<T0, T1, T2, !EmbedByValue>;

        abstract_parser_t*
        get() const
        {
            return ptr.get();
        }

        stored_rule(shared_ptr<abstract_parser_t> const& ptr)
        : ptr(ptr) {}

        shared_ptr<abstract_parser_t> ptr;
    };

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* stored_rule.hpp
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
*/