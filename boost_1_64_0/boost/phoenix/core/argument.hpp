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
mLhAY1iC9Ioy8HinwYDoumtIwgeAKKoMgtIll/VW2kneIaX4hOvrMmg8sA11JoQ4ON1uNMY62Zs4xDXTJ93vvHLUANw0ZBvdDGqxUcJSuLbZwYOibmDenvdamu7Mjadzy5U4kgpRMl1M/IU0VvnO+/WeO/lrAtWaVa+E2QBuhm+qrj+CNdLTlreGImrT1JZBxuUNO1M3YZT7lHdx5FjYJvTn+/KKA7h6P4U2sWi6xlFTRf6g5lz+V2Yvv1v9MXpJGCnT0yhpKgKkDCv3xmy1kiTAVPSFc35obq/mVLy0XCxDSmXxYMuZgDVfAyZkyd3ixibSVJ4KF8GSU9w7oI2LgFx3EvcoutY1dkGtPiJU8WOVATQcxWCHa1tU7jW+JkfLwE6GP0Mh2jT2PAt9BlZzKPwcrNbn8A5LBRsYS0a5i56ThOPQWQAefxuZuAJEE+V1mGtyQgAGOFldiszmXMyQtgzUd5uCpl2q3WtTvPSOUkedx9Y2DV7lGwPuFBQu3Xj/Cf1jRFOdVU/i9HaPWQf59wTYFotnhpHGFMvRPEjudjjrhbNdnjQaKURMXQ==
*/