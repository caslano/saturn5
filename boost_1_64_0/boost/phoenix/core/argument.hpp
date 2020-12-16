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
eYGS7UtM9HQ/hf0WbAY55tfHfd7BOhoBv94qIO1JUFGsdxP8OnQaOebR0a0wXTpYG2Jek+bOwLzA94NaE9sdX6AxxgA2ldiJZ7cXc78/zDV74AWJFQ08koL9HawWsQptKq3DugUrSmxkypm72F7A/IkZlPTqWC5ghYh1KpM1G8sTrBGxdNPMPpjPSdAfiNXpk9EDy1NnwzbNlfNBsAhiczYuPIDnA6tIrN7LYROwnYEVIeb39C05R5kMv9Ahdqv8oG54PsYSwOgxD2YsbIflAqa4SQuZk4hjjxluNpuTdE8mVf0OjwmWXUBamfAp5XGc/xjapyLNZcYsLBcTtA74F9FOns7C+a4VzMUobcOWE/sx3aew7mWQ9s2IX1K43/3iuARWkdjSD+Z3xXyChRL7oV9wSSxPmG0GENtSe1E0xg7WjVjt/lPC8Zhg1Yn1/va311ieK2HdjVi73n+NxHRgl4gVbdK6Dvc7b8wnWD1iQUt8XDGfYMWJ7TlsWIRlBlZaWs5v5rHMGMsEq0Dsm5Ql2De91+RtFjCal3lZ/qE4RoJVJFbNvdd5HF/APImd7DFT3luA+RA7fGjzE4yBsUywlwZpYXemlsC8QI4/UaRZIh5sxvPByt1tYkNa1TmE8cG/tYUcc5r7pct4TFgxiiF52TixaD/MC1gzYt5bZnbE9rIV1iOJGQ8WaopjCFgPcr6luwMn4/m2w9NiD2nW3jsCcZxPtfdpaVcLJW7CPrYX0pFjTpi9ajam2yfE127S6h5b/RhjPyzELlIuZY5sXPUv92bQtzPGMsEqSNO2s+/yNgtYcWnadgZWUZq2nYF5StO2MzAfadp2prMGwfewXDLBmhaQVr3jYlw/s8GZG5J00T06DsJjgk0htjD7uYwBPsaykNiBPctwPmG6CN8lJeZZKaA5lgsMLt8ZpHUoBtOJ3HECXveYQNIVNFimcnuKYLlchbe5jdJcYrJeYQw3wIS0X2K6D8BjQimUJ8fcmTWoBNZDJpQZsf6Dy7XFdLfAyDE3DO8XhOUJZiH2fbFuf2JewN5VpMUUNL3EOoIV1DvkfFHHjxXHMoOXl5aSYx6d7lUIx+T7YCRdUPOX73D7z+SaFayINM2av01n9RLeVMByAXOVpl1jYSyZsTTG0hnLZCybMfuCYwVixzN+L4JjHVhbYn8/numBsYP9bpC2ul1LrD/v3+BehliXdz5NxL4CH51q4SFt0PfDZR97Ds8fSLrjwTUqYzo4ur+7tFdj2+C4a3WV+0mBada2o8FKkmM+uP+rN54PFqxMJN3Hb6JjsczAaHuZ+U4BfCZlgeAuEftrUuIuzAssiL9NrPnM44ux3j20+Tw0PS4d8wJWiph1yuxSWLdgZmJL1qQUxP5XQJsusewOgfkEW0fs64A2a7GOPOGtCBrf6TOfYzqwCcR2lT00EvMCNpnY425dR+GYVdAgdhI7OutgeawHL9jHk9itOvcGYbmAvSTWL7bPCqyHQgZRn9iCaW9VxXwWNoh3iS1rOL0Q5hPsC1LvTd944hgiihqEjaQr9Th7LrZrsH3Eio/8JBTjK2YQVmL+wz5fhPkEK0fMOGE+xmDyIfUun0XmuR8YGrx8/5jYtiJt0rA8SxjECmKvnz2CKst7fzUsM7DTirTMZzvkGnwZA9xPS7sSM1euE4FVM0ozdHpxF8u6AvQxkq7joEXJWNYVDaIFsdE1aszBGMB8ifX78gf5rBysGbGza8Q2PB9YF2JVV0fg8xyrL4ldlnVee+7JdXawgsSiVk36DesdrCqxVa/eP4JtV3fMbb1bv419GuwDRdoln5vYzrIrG0Qtg7T7K2aUw7zAltWLyTHPrQmpinULry5ZiLk=
*/