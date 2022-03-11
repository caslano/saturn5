
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