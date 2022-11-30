/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_DOMAIN_JANUARY_29_2007_0954AM)
#define BOOST_SPIRIT_DOMAIN_JANUARY_29_2007_0954AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/meta_compiler.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/argument.hpp>
#include <boost/spirit/home/support/context.hpp>

#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost { namespace spirit { namespace qi
{
    // qi's domain
    struct domain {};

    // bring in some of spirit parts into spirit::qi
    using spirit::unused;
    using spirit::unused_type;
    using spirit::compile;
    using spirit::info;

    // You can bring these in with the using directive
    // without worrying about bringing in too much.
    namespace labels
    {
        BOOST_PP_REPEAT(SPIRIT_ARGUMENTS_LIMIT, SPIRIT_USING_ARGUMENT, _)
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
    }

}}}

#endif

/* domain.hpp
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
*/