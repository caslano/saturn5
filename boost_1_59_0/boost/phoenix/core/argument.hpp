/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_ARGUMENT_HPP
#define BOOST_PHOENIX_CORE_ARGUMENT_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/actor.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/terminal.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace phoenix
{
    ////////////////////////////////////////////////////////////////////////////
    //
    //  argument
    //
    //      function for evaluating argument placeholders like: _1
    //
    ////////////////////////////////////////////////////////////////////////////
    
    template <int I>
    struct argument
        //: mpl::int_<I>
    {
        typedef typename mpl::int_<I>::value_type value_type;
        static const value_type value = mpl::int_<I>::value;
        
        bool operator==(argument) const
        {
            return true;
        }
        
        template <int I2>
        bool operator==(argument<I2>) const
        {
            return false;
        }
    };
}}

namespace boost {
    template <int I>
    struct is_placeholder<phoenix::argument<I> >
        : mpl::int_<I>
    {};
}

namespace boost { namespace phoenix
{
    namespace expression
    {
        template <int I>
        struct argument
            : expression::terminal<phoenix::argument<I> >
        {
            typedef typename expression::terminal<phoenix::argument<I> >::type type;
            static const type make()
            {
                type const e = {{{}}};
                return e;
            }
        };
    }

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/core/detail/cpp03/preprocessed/argument.hpp>

#else

#if !defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#include <boost/phoenix/core/detail/argument.hpp>
#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/cpp03/preprocessed/argument_predefined_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#ifdef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#undef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#define BOOST_PHOENIX_NO_PREDEFINED_TERMINALS_RESTORE
#endif

#include <boost/phoenix/core/detail/argument.hpp>

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS_RESTORE
#define BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#undef BOOST_PHOENIX_NO_PREDEFINED_TERIMINALS_RESTORE
#endif

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "detail/cpp03/preprocessed/argument_no_predefined_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#define BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#define BOOST_PHOENIX_NO_PREDEFINED_TERMINALS_RESTORE
#endif

#include <boost/phoenix/core/detail/argument.hpp>

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS_RESTORE
#undef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
#undef BOOST_PHOENIX_NO_PREDEFINED_TERIMINALS_RESTORE
#endif

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#endif

}}

#endif

/* argument.hpp
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
*/