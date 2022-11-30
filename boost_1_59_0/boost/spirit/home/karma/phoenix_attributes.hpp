//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_PHOENIX_ATTRIBUTES_OCT_01_2009_1128AM)
#define BOOST_SPIRIT_KARMA_PHOENIX_ATTRIBUTES_OCT_01_2009_1128AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/karma/detail/indirect_iterator.hpp>
#include <boost/spirit/home/support/container.hpp>

#include <boost/utility/result_of.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace phoenix
{
    template <typename Expr>
    struct actor;
}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    // Provide customization points allowing the use of phoenix expressions as 
    // generator functions in the context of generators expecting a container 
    // attribute (Kleene, plus, list, repeat, etc.)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Eval>
    struct is_container<phoenix::actor<Eval> const>
      : is_container<typename boost::result_of<phoenix::actor<Eval>()>::type>
    {};

    template <typename Eval>
    struct container_iterator<phoenix::actor<Eval> const>
    {
        typedef phoenix::actor<Eval> const& type;
    };

    template <typename Eval>
    struct begin_container<phoenix::actor<Eval> const>
    {
        typedef phoenix::actor<Eval> const& type;
        static type call(phoenix::actor<Eval> const& f)
        {
            return f;
        }
    };

    template <typename Eval>
    struct end_container<phoenix::actor<Eval> const>
    {
        typedef phoenix::actor<Eval> const& type;
        static type call(phoenix::actor<Eval> const& f)
        {
            return f;
        }
    };

    template <typename Eval>
    struct deref_iterator<phoenix::actor<Eval> const>
    {
        typedef typename boost::result_of<phoenix::actor<Eval>()>::type type;
        static type call(phoenix::actor<Eval> const& f)
        {
            return f();
        }
    };

    template <typename Eval>
    struct next_iterator<phoenix::actor<Eval> const>
    {
        typedef phoenix::actor<Eval> const& type;
        static type call(phoenix::actor<Eval> const& f)
        {
            return f;
        }
    };

    template <typename Eval>
    struct compare_iterators<phoenix::actor<Eval> const>
    {
        static bool 
        call(phoenix::actor<Eval> const&, phoenix::actor<Eval> const&)
        {
            return false;
        }
    };

    template <typename Eval>
    struct container_value<phoenix::actor<Eval> >
    {
        typedef phoenix::actor<Eval> const& type;
    };

    template <typename Eval>
    struct make_indirect_iterator<phoenix::actor<Eval> const>
    {
        typedef phoenix::actor<Eval> const& type;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Handle Phoenix actors as attributes, just invoke the function object
    // and deal with the result as the attribute.
    ///////////////////////////////////////////////////////////////////////////
    template <typename Eval, typename Exposed>
    struct extract_from_attribute<phoenix::actor<Eval>, Exposed>
    {
        typedef typename boost::result_of<phoenix::actor<Eval>()>::type type;

        template <typename Context>
        static type call(phoenix::actor<Eval> const& f, Context& context)
        {
            return f(unused, context);
        }
    };
}}}

#endif

/* phoenix_attributes.hpp
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
*/