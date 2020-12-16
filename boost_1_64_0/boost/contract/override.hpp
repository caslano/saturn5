
#ifndef BOOST_CONTRACT_OVERRIDE_HPP_
#define BOOST_CONTRACT_OVERRIDE_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Handle public function overrides (for subcontracting).
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/config/config.hpp>

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Declare an override type trait with an arbitrary name.

    Declare the override type trait named @c type_name to pass as an explicit
    template parameter to @RefFunc{boost::contract::public_function} for public
    function overrides.
    
    @see @RefSect{advanced.named_overrides, Named Overrides}

    @param type_name    Name of the override type trait this macro will declare.
                        (This is not a variadic macro parameter but it should
                        never contain commas because it is an identifier.)
    @param func_name    Function name of the public function override.
                        This macro is called just once even if the function name
                        is overloaded (the same override type trait is used for
                        all overloaded functions with the same name, see
                        @RefSect{advanced.function_overloads,
                        Function Overloads}).
                        (This is not a variadic macro parameter but it should
                        never contain commas because it is an identifier.)
    */
    #define BOOST_CONTRACT_NAMED_OVERRIDE(type_name, func_name)
#elif !defined(BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS)
    #include <boost/contract/core/virtual.hpp>
    #include <boost/contract/detail/type_traits/mirror.hpp>
    #include <boost/contract/detail/tvariadic.hpp>
    #include <boost/contract/detail/none.hpp>
    #include <boost/contract/detail/name.hpp>

    /* PRIVATE */

    #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_(z, arity, arity_compl, \
            func_name) \
        template< \
            class BOOST_CONTRACT_DETAIL_NAME1(B), \
            class BOOST_CONTRACT_DETAIL_NAME1(C) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_TPARAMS_Z(z, arity, \
                    BOOST_CONTRACT_DETAIL_NAME1(Args)) \
        > \
        static void BOOST_CONTRACT_DETAIL_NAME1(call_base)( \
            boost::contract::virtual_* BOOST_CONTRACT_DETAIL_NAME1(v), \
            BOOST_CONTRACT_DETAIL_NAME1(C)* BOOST_CONTRACT_DETAIL_NAME1(obj) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
            BOOST_CONTRACT_DETAIL_TVARIADIC_FPARAMS_Z(z, arity, \
                BOOST_CONTRACT_DETAIL_NAME1(Args), \
                &, \
                BOOST_CONTRACT_DETAIL_NAME1(args) \
            ) \
            BOOST_CONTRACT_DETAIL_NO_TVARIADIC_COMMA(arity_compl) \
            BOOST_CONTRACT_DETAIL_NO_TVARIADIC_ENUM_Z(z, arity_compl, \
                    boost::contract::detail::none&) \
        ) { \
            BOOST_CONTRACT_DETAIL_NAME1(obj)-> \
            BOOST_CONTRACT_DETAIL_NAME1(B)::func_name( \
                BOOST_CONTRACT_DETAIL_TVARIADIC_ARGS_Z(z, arity, \
                        BOOST_CONTRACT_DETAIL_NAME1(args)) \
                BOOST_CONTRACT_DETAIL_TVARIADIC_COMMA(arity) \
                BOOST_CONTRACT_DETAIL_NAME1(v) \
            ); \
        }

    #if BOOST_CONTRACT_DETAIL_TVARIADIC
        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(func_name) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_(1, ~, ~, func_name)
    #else
        #include <boost/preprocessor/repetition/repeat.hpp>
        #include <boost/preprocessor/arithmetic/inc.hpp>
        #include <boost/preprocessor/arithmetic/sub.hpp>

        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(func_name) \
            BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_CONTRACT_MAX_ARGS), \
                    BOOST_CONTRACT_OVERRIDE_CALL_BASE_ARITY_, func_name) \
        
        #define BOOST_CONTRACT_OVERRIDE_CALL_BASE_ARITY_(z, arity, func_name) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_(z, arity, \
                    BOOST_PP_SUB(BOOST_CONTRACT_MAX_ARGS, arity), func_name)
    #endif

    /* PUBLIC */

    #define BOOST_CONTRACT_NAMED_OVERRIDE(type_name, func_name) \
        struct type_name { \
            BOOST_CONTRACT_DETAIL_MIRROR_HAS_MEMBER_FUNCTION( \
                BOOST_CONTRACT_DETAIL_NAME1(has_member_function), \
                func_name \
            ) \
            BOOST_CONTRACT_OVERRIDE_CALL_BASE_DECL_(func_name) \
        };
#else
    #define BOOST_CONTRACT_NAMED_OVERRIDE(type_name, func_name) \
            struct type_name {}; /* empty (not used), just to compile */
#endif
    
/* PUBLIC */

/**
Declare an override type trait named <c>override_<i>func_name</i></c>.

Declare the override type trait named <c>override_<i>func_name</i></c> to pass
as an explicit template parameter to @RefFunc{boost::contract::public_function}
for public function overrides.
Use @RefMacro{BOOST_CONTRACT_NAMED_OVERRIDE} to generate an override type trait
with a name different than <c>override_<i>func_name</i></c> (usually not
needed).

@see    @RefSect{tutorial.public_function_overrides__subcontracting_,
        Public Function Overrides}

@param func_name    Function name of the public function override.
                    This macro is called just once even if the function name is
                    overloaded (the same override type trait is used for all
                    overloaded functions with the same name, see
                    @RefSect{advanced.function_overloads, Function Overloads}).
                    (This is not a variadic macro parameter but it should never
                    contain any comma because it is an identifier.)
*/
#define BOOST_CONTRACT_OVERRIDE(func_name) \
    BOOST_CONTRACT_NAMED_OVERRIDE(BOOST_PP_CAT(override_, func_name), func_name)
    
#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Declare multiple override type traits at once naming them
    <c>override_...</c> (for convenience).

    This variadic macro is provided for convenience as
    <c>BOOST_CONTRACT_OVERRIDES(f_1, f_2, ..., f_n)</c> expands to code
    equivalent to:

    @code
    BOOST_CONTRACT_OVERRIDE(f_1)
    BOOST_CONTRACT_OVERRIDE(f_2)
    ...
    BOOST_CONTRACT_OVERRIDE(f_n)
    @endcode

    On compilers that do not support variadic macros,
    the override type traits can be equivalently programmed one-by-one calling
    @RefMacro{BOOST_CONTRACT_OVERRIDE} for each function name as shown above.
    
    @see    @RefSect{tutorial.public_function_overrides__subcontracting_,
            Public Function Overrides}
    
    @param ...  A comma separated list of one or more function names of public
                function overrides.
                (Each function name should never contain commas because it is an
                identifier.)
    */
    #define BOOST_CONTRACT_OVERRIDES(...)
#elif BOOST_PP_VARIADICS
    #include <boost/preprocessor/seq/for_each.hpp>
    #include <boost/preprocessor/variadic/to_seq.hpp>
    
    /* PRIVATE */

    #define BOOST_CONTRACT_OVERRIDES_SEQ_(r, unused, func_name) \
        BOOST_CONTRACT_OVERRIDE(func_name)
    
    /* PUBLIC */

    #define BOOST_CONTRACT_OVERRIDES(...) \
        BOOST_PP_SEQ_FOR_EACH(BOOST_CONTRACT_OVERRIDES_SEQ_, ~, \
                BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#else
    #define BOOST_CONTRACT_OVERRIDES \
BOOST_CONTRACT_ERROR_macro_OVERRIDES_requires_variadic_macros_otherwise_manually_repeat_OVERRIDE_macro
#endif

#endif // #include guard


/* override.hpp
kQvbkn0Jhm1FGYVzyW19ynSC614N7Iu6cPk4p7/uvk1eED7Do+1am2gsI+Pl/UDX57q+x+p4Y0MjdD4EgG3+SLHFevOmWwuF27GtwPv9WRPqG3zY/s7P8J5G3OvEa3PuZC1FFhjXweTmgWRH2m3TVb9SDrIftwt7inneV99T0XvJYZ+rls8Ls/wf1qlKKctJ4+GOR/nWfvse43Pv76wWHnsBj7HyrfZkeeBc0gEUH88MttCxegw/TNeBZtlb0w2XJrMuZD6W03qmBGUO7tgvM3cJH0Tpa14HigLa8oi8fnw23uHOKuQ6eqDWBaI9lL51D7HaPsGEH6Rh5p3qoM4ivZUJ3xJoAJ94qPGJC7AuclhsQcrD7q0/TOmLgjD7HylLbOsnyTvij8u+sF+PwzNwfDaLw48SHMPPmvAfTPgpE34cwnjnhOODdtxGsiL+Dwa/kvALc99N5fxwS0MTDdSb2aSiEJn2bdXsYAz3zizfFlaLLTxQ6uOOD/kO2nSsb1+o/2AY3W2B62yy55HBr+Ge/t5OhB01W/YgyF6WmPiQT4EPKd3p3ucRxY4PjtHT+hPffAzh0f6P9e2N86/t03GmHUhgm1Hh678dymc1fTs4lk8nwaR/wLjCCstjpLcW2qc01HGXB/QnXVCf0+Z3lMnP8VB/RohMJB/bXI+ReQ8zDupTmUFftk8zADwKJV+Y70GpY1tgX+ZncG+lvG9QZ/ZlbtQ8Ml7zF+2fNxvaiWOz055gaMuLs9OeKLok2VimObCHVd9VQPxnVV+At+stnzM0LKtdxyKabP3aA0y/9oCd3tmVOw7fO4f2LW3I6aZvegbYEeL4zhPI0+lZ+r5nEVznewo5T72d88QvPFnu8pbqStQEc7ZnQ75/7GjjDp+5VBIB2c+X5xGP18ooLTtfVU19I3wbg/tG0C8rlP63hCl+l6ff472uLvRtk2kOXV6ZzPix8yF/ZSRnRwx3Z0M4a7nmjsNvdkWU64WmXC+Ccr3QlOvXtVwZF70eeAnBT/pA474m74Peb3eozH1fFupfti5uaVq6oGZ+dcj6M9Cdjgfzj8/nZyN0vdXo+krQ9Vaj62+ArrdmqUNXE1z667IeFOwnLjO628/ortzorkt0p+Ee1/7q/kQ5L/Mt0OeAuyssNm9+SBkA0jYX6xBV6+g1nzx58TngCL1eb/R6A+j1eqPXG0Gv12fR63Zpo97idknGoXJe4NDxfhv8+xJph0yf9iaJ+y60b2/It9NFPdwDMknn+0uDvfjfZx1vyKzr3Ubhujzm/XVf2A84/iJP+daZcj7Zo7k/2sKotrB+Co0pHUzKWt+t/SGU9TZv1aLFrc0ty5c3Z1Z7QhBKP9Lf5hGP39CLKNPbTZneAWXKOLw3EMr09ixl+lOCN4T6p7ZvSusNiZRn37TQcLHOr4h+fh7qd/a3Hx939Gq8EKY8ch9O+m96/7y9V+0XYje/FF1Mx3Mkcl+ZC9/DY+61fXh35r0gS7HHd1nJWR4WBgF4zxvZcXZ57hN57t+JPA+APFUiz4MR8vR2siwaYDmkvDlPdmz2MMEi27ncuua++iPQV3/U2NZvItJ6TPL6uNDinSJPDKOn/gn0cR+I4Pdbsc/yYrkvZly2vHTR4i+22RCGsb3tk6al7NxfO7Z/VvLyOxifP0ff9oyvg+n+H/Vn2Nd9Hurbc2Zc/SfNv+CeM3X1z1Afn8vST3jJ0OjeMaT5q/LVdHW+IFInUfrYzXsFxlCEU3r23TiG+geOoWDubub4iPPPwFPagMg3JV6TsjgZ2oI++D7TjHvuoDJYYe41e0N4nKO0hKuQM3Rnj8PxR/CucaHY3dtQhi4fqMt3CYdvWy8ttXnyf3Y=
*/