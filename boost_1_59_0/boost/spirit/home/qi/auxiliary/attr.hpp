/*=============================================================================
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_ATTR_JUL_23_2008_0956AM)
#define BOOST_SPIRIT_ATTR_JUL_23_2008_0956AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/mpl/bool.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <typename A0>       // enables attr()
    struct use_terminal<
            qi::domain, terminal_ex<tag::attr, fusion::vector1<A0> > >
      : mpl::true_ {};

    template <>                  // enables *lazy* attr()
    struct use_lazy_terminal<qi::domain, tag::attr, 1>
      : mpl::true_ {};

}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::attr;
#endif
    using spirit::attr_type;

    template <typename Value>
    struct attr_parser : primitive_parser<attr_parser<Value> >
    {
        template <typename Context, typename Iterator>
        struct attribute : remove_const<Value> {};

        attr_parser(typename add_reference<Value>::type value)
          : value_(value) {}

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& /*first*/, Iterator const& /*last*/
          , Context& /*context*/, Skipper const& /*skipper*/
          , Attribute& attr_) const
        {
            spirit::traits::assign_to(value_, attr_);
            return true;        // never consume any input, succeed always
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("attr");
        }

        Value value_;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(attr_parser& operator= (attr_parser const&))
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::attr, fusion::vector1<A0> >
      , Modifiers>
    {
        typedef typename add_const<A0>::type const_value;
        typedef attr_parser<const_value> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename Attr, typename Context, typename Iterator>
    struct handles_container<qi::attr_parser<T>, Attr, Context, Iterator>
      : traits::is_container<Attr> {}; 
}}}

#endif



/* attr.hpp
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
*/