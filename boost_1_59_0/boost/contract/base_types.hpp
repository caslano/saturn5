
#ifndef BOOST_CONTRACT_BASE_TYPES_HPP_
#define BOOST_CONTRACT_BASE_TYPES_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Specify inheritance form base classes (for subcontracting).
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp>
#include <boost/preprocessor/config/config.hpp>

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN

/**
Used to program the @c typedef that lists the bases of a derived class.

In order to support subcontracting, a derived class that specifies contracts for
one or more overriding public functions must declare a @c typedef named
@c base_types (or @RefMacro{BOOST_CONTRACT_BASES_TYPEDEF}) using this macro:

    @code
        class u
            #define BASES public b, protected virtual w1, private w2
            : BASES
        {
            friend class boost::contract:access;

            typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
            #undef BASES

            ...
        };
    @endcode

This @c typedef must be @c public unless @RefClass{boost::contract::access} is
used.

@see @RefSect{tutorial.base_classes__subcontracting_, Base Classes}

@param ...  Comma separated list of base classes.
            Each base must explicitly specify its access specifier @c public,
            @c protected, or @c private, and also @c virtual when present
            (this not always required in C++ instead).
            There is a limit of about 20 maximum bases that can be listed
            (because of similar limits in Boost.MPL internally used by this
            library).
            This is a variadic macro parameter, on compilers that do not support
            variadic macros, the @c typedef for base classes can be programmed
            manually without using this macro (see
            @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}).
            
*/
#define BOOST_CONTRACT_BASE_TYPES(...)

#elif !BOOST_PP_VARIADICS
    
#define BOOST_CONTRACT_BASE_TYPES \
BOOST_CONTRACT_ERROR_macro_BASE_TYPES_requires_variadic_macros_otherwise_manually_program_base_types

#elif !defined(BOOST_CONTRACT_NO_PUBLIC_FUNCTIONS)

#include <boost/mpl/vector.hpp>
#include <boost/contract/detail/preprocessor/keyword/virtual.hpp>
#include <boost/contract/detail/preprocessor/keyword/public.hpp>
#include <boost/contract/detail/preprocessor/keyword/protected.hpp>
#include <boost/contract/detail/preprocessor/keyword/private.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/push_back.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp> // For HEAD, TAIL, etc.
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_BASE_TYPES_REMOVE_VIRTUAL_(base) \
    BOOST_PP_EXPAND( \
        BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL(base), \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_VIRTUAL \
        , \
            BOOST_PP_TUPLE_REM(1) \
        )(base) \
    )

#define BOOST_CONTRACT_BASE_TYPES_PUSH_BACK_IF_(is_public, types_nilseq, base) \
    ( \
        is_public, \
        BOOST_PP_IIF(is_public, \
            BOOST_PP_SEQ_PUSH_BACK \
        , \
            types_nilseq BOOST_PP_TUPLE_EAT(2) \
        )(types_nilseq, base) \
    )

#define BOOST_CONTRACT_BASE_TYPES_SKIP_NOT_PUBLIC_(is_public, types_nilseq, \
        base) \
    (0, types_nilseq)

// Precondition: base = `public [virtual] ...`.
#define BOOST_CONTRACT_BASE_TYPES_PUSH_BACK_PUBLIC_(is_public, types_nilseq, \
        base) \
    ( \
        1, \
        BOOST_PP_SEQ_PUSH_BACK(types_nilseq, \
            BOOST_CONTRACT_BASE_TYPES_REMOVE_VIRTUAL_( \
                    BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PUBLIC(base)) \
        ) \
    )

#define BOOST_CONTRACT_BASE_TYPES_ACCESS_(is_public, types_nilseq, base) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC(base), \
        BOOST_CONTRACT_BASE_TYPES_PUSH_BACK_PUBLIC_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED(base), \
        BOOST_CONTRACT_BASE_TYPES_SKIP_NOT_PUBLIC_ \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE(base), \
        BOOST_CONTRACT_BASE_TYPES_SKIP_NOT_PUBLIC_ \
    , \
        BOOST_CONTRACT_BASE_TYPES_PUSH_BACK_IF_ \
    )))(is_public, types_nilseq, base)

#define BOOST_CONTRACT_BASE_TYPES_(s, public_types, base) \
    BOOST_CONTRACT_BASE_TYPES_ACCESS_( \
        BOOST_PP_TUPLE_ELEM(2, 0, public_types), \
        BOOST_PP_TUPLE_ELEM(2, 1, public_types), \
        BOOST_CONTRACT_BASE_TYPES_REMOVE_VIRTUAL_(base) \
    )

#define BOOST_CONTRACT_BASE_TYPES_RETURN_YES_(types_nilseq) \
    BOOST_PP_SEQ_ENUM(BOOST_PP_SEQ_TAIL(types_nilseq))

#define BOOST_CONTRACT_BASE_TYPES_RETURN_(types_nilseq) \
    BOOST_PP_IIF(BOOST_PP_EQUAL(BOOST_PP_SEQ_SIZE(types_nilseq), 1), \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_CONTRACT_BASE_TYPES_RETURN_YES_ \
    )(types_nilseq)

#define BOOST_CONTRACT_BASE_TYPES_OK_(base_tuple, bases_seq) \
    boost::mpl::vector< \
        BOOST_CONTRACT_BASE_TYPES_RETURN_(BOOST_PP_TUPLE_ELEM(2, 1, \
            BOOST_PP_SEQ_FOLD_LEFT( \
                BOOST_CONTRACT_BASE_TYPES_, \
                (0, (BOOST_PP_NIL)), \
                bases_seq \
            ) \
        )) \
    >

#define BOOST_CONTRACT_BASE_TYPES_ERR_(bases_tuple, bases_seq) \
    BOOST_CONTRACT_ERROR_all_bases_must_explicitly_specify_public_protected_or_private base_tuple

#define BOOST_CONTRACT_BASE_TYPES_IS_ACCESS_(base) \
    BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC(base), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED(base), \
        1 \
    , BOOST_PP_IIF(BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE(base), \
        1 \
    , \
        0 \
    )))

// Cannot check that all base types have access specifiers (unless users have to
// specify bases using pp-seq, because user specified base list can have
// unwrapped commas between bases but also within a given base type, when base
// types are templates), but at least check the very first base type explicitly
// specifies access `[virtual] public | protected | private [virtual] ...`.
#define BOOST_CONTRACT_BASE_TYPES_CHECK_(bases_tuple, bases_seq) \
    BOOST_PP_IIF(BOOST_CONTRACT_BASE_TYPES_IS_ACCESS_( \
            BOOST_CONTRACT_BASE_TYPES_REMOVE_VIRTUAL_(BOOST_PP_SEQ_HEAD( \
                    bases_seq))), \
        BOOST_CONTRACT_BASE_TYPES_OK_ \
    , \
        BOOST_CONTRACT_BASE_TYPES_ERR_ \
    )(bases_tuple, bases_seq)

/* PUBLIC */

#define BOOST_CONTRACT_BASE_TYPES(...) \
    BOOST_CONTRACT_BASE_TYPES_CHECK_((__VA_ARGS__), \
            BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#else

#define BOOST_CONTRACT_BASE_TYPES(...) void /* dummy type for typedef */

#endif

#endif // #include guard


/* base_types.hpp
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
*/