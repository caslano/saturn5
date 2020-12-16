
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_CONFIG_HPP_
#define BOOST_LOCAL_FUNCTION_CONFIG_HPP_

#ifndef DOXYGEN

#include <boost/config.hpp>

#ifndef BOOST_LOCAL_FUNCTION_CONFIG_FUNCTION_ARITY_MAX
#   define BOOST_LOCAL_FUNCTION_CONFIG_FUNCTION_ARITY_MAX 5
#endif

#ifndef BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX
#   define BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX 10
#endif

#ifndef BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS
#   ifdef BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#       define BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS 0
#   else
#       define BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS 1
#   endif
#elif BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS // If true, force it to 1.
#   undef BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS
#   define BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS 1
#endif

#else // DOXYGEN

/** @file
@brief Configuration macros allow to change the behaviour of this library at
compile-time.
*/

/**
@brief Maximum number of parameters supported by local functions.

If programmers leave this configuration macro undefined, its default
value is <c>5</c> (increasing this number might increase compilation time).
When defined by programmers, this macro must be a non-negative integer number.

@Note This macro specifies the maximum number of local function parameters
excluding bound variables (which are instead specified by
@RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX}).

@See @RefSect{tutorial, Tutorial} section,
@RefSect{getting_started, Getting Started} section,
@RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX}.
*/
#define BOOST_LOCAL_FUNCTION_CONFIG_ARITY_MAX

/**
@brief Maximum number of bound variables supported by local functions.

If programmers leave this configuration macro undefined, its default
value is <c>10</c> (increasing this number might increase compilation time).
When defined by programmers, this macro must be a non-negative integer number.

@Note This macro specifies the maximum number of bound variables excluding
local function parameters (which are instead specified by
@RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_ARITY_MAX}).

@See @RefSect{tutorial, Tutorial} section,
@RefSect{getting_started, Getting Started} section,
@RefMacro{BOOST_LOCAL_FUNCTION_CONFIG_ARITY_MAX}.
*/
#define BOOST_LOCAL_FUNCTION_CONFIG_BIND_MAX

/**
@brief Specify when local functions can be passed as template parameters
without introducing any run-time overhead.

If this macro is defined to <c>1</c>, this library will assume that the
compiler allows to pass local classes as template parameters:
@code
    template<typename T> void f(void) {}

    int main(void) {
        struct local_class {};
        f<local_class>();
        return 0;
    }
@endcode
This is the case for C++11 compilers and some C++03 compilers (e.g., MSVC), but
it is not the case in general for most C++03 compilers (including GCC).
This will allow the library to pass local functions as template parameters
without introducing any run-time overhead (specifically without preventing the
compiler from optimizing local function calls by inlining their assembly code).

If this macro is defined to <c>0</c> instead, this library will introduce
a run-time overhead associated to resolving a function pointer call in order to
still allow to pass the local functions as template parameters.

It is recommended to leave this macro undefined.
In this case, the library will automatically define this macro to <c>0</c> if
the Boost.Config macro <c>BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS</c> is
defined for the specific compiler, and to <c>1</c> otherwise.

@See @RefSect{getting_started, Getting Started} section,
@RefSect{advanced_topics, Advanced Topics} section,
@RefMacro{BOOST_LOCAL_FUNCTION_NAME}.
*/
#define BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS

#endif // DOXYGEN

#endif // #include guard


/* config.hpp
3fP+nztmwLBs1uOqAjOfrWFK11otlWsfjvhfN+XtyZ8R1ZLHT1RaH/F7abY2id/Ua+uvafFS7u8ov7a0qFu49949b97PkPftKs4VzFSqov2gt1Fpj5N+auSAYaPIvPld10bVazNCVjbr5irltklfyvOxG31PnPQ9NaSf2SLPp63Ie4jXuYPf8kTWlcq7VMwfNHaxoJ3s0yYJJsnYRf5Wax8V+NiFO57u137NOQLKv4x7HFDKcHsA+6eWNl6x9Cp3wId02pywLuGKNlivwX+8IlX6kb0q3Bx9ErFnkdJ88vcKPdAxzk/yd2O+i3shffQou2smHfvxicZyzV8o/8l6c2bi5tJaHyf2Oq0R8yLrMyZYh/0dy9j1t6LXeV7b1LcN/0rmd+pN6rya+Szdqc6bm+9jj8l5E/v+lvRsxyLM+3miit9bq65+Jdbtx/9ER5xZ/6OyJvT3bgMVNhphKjv2cZ8oHffoY6jl+5EHye+r8AvkG/6ux/tkV6Q7fV1d2lGEz/d4shJ5NwhgbND8jlb5sswP23juOzp8o/k9a34fv/+26dbC842ba7q1Vuc93/b+5v1pw+//zbuyo6aOtrq7HV0B4437YaP1fnB+50yUetirwqfqF6H7Om02I8i28yHQa/P+aZmXc0T519EraGV4CmdoZzSXfXvfaPtuar6rfKb8G+kJxt2EbEI0+3E1dAX+7iph/drjRdI/fKP8a3L3R6h31ze56lOIvINav5HNd9DX6dv/kYQE0P5+z3fQvKvdCQ30vFPJ711p28+1hUB+q05X4f9sW/9pQfxWnRbEb9VpQfxWnXaBv1X3VfGutc7XM/dvTvgv/Z06t7M78ft199zuOTL+kfKFp07V2hzHeSVN5drTVPjb9WTuy37on8/z7i1kE/ITUp/7vaf9PU9aNnVuWQvwnPKvrDcn5zchGcijyFrkqP39j07n37FiYbUvDf+HtXieHVfyFMqG8ZJeTxW3t5aA7q6ITXsS/T57iVPiTaV/GaP8r6E8IrVMyuQeymA2fBjZgpQgtXTbsRDRbW1/rIyy/FZwm/K/CH/dnF/+V+UWqeI8o9rmBFVBTeWeu175j9aN0Zzu9D33U/KvI2uQk0h1vqc6I3I95thKoqSZqsprtlYBlxY8KQdB2bfcfF4mW95hk2ERsgN5NpH3h//o77OqLrzG+XKul31SpH28KOMm6Z97t3PzQWY3zidt/SYVZ5FmPMsGa9F2bRq9DuO6Uh/DlP9cNRe5p1bBrg2jw2FcV9rpQOU/X6vGlWbZt1N0BP7skrDWNuQ1R3SE8s/XKvH/rYjM3ZDxNd/nlrxD/YHzlD193NQu7oTeljGzDZqMnRww6571gecfOxmiwq/QJqDlWWroVft56Oh1mp8s787udLVrCD1ei7Kre3TY919x0n9tVf7NCVvHrt6J7zA+K/HfVv4pWoTDOhJr/OdUW5hIYZx7nxut/JdpOZR0AVpe4Fqszz3resBdv7L+g7v3z83N2KnyyJh+M+8x1D7d3AnPkt/YZ2rub7z8D63tQX3jnf8b9UPb7zVzTPpp5T8a/05aX/tnFTpsv83s6pWwtt9VdnUoYZ3rcIHyn6xdYsyiMFJF4rzCyvoaeQa8rsJ3kHPCfqTGXqzf30jw8wV+q2+VtunuRA5KuR6QPj7tI2u9lr7OpAq8WoXfy5Qe3a7ORZ/zOpO+yv9Np3UmxHdeZxIPeyj/jVo1+z6d+IH36YS1awPm7zS3KP/VajWDzTeIjIHL+R/Yl3vu3cjuMrYkCdZAdjShj3DbxeeebdmCGiZa6b/R11fhE+zqV3Tpfr/fqznoyq9yaWNM1xvh4t1lIH2XpG+xvT9fZ338ZcY=
*/