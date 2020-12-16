
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

// no include guards, this file is intended for multiple inclusions

#ifdef __WAVE__
// this file has been generated from the master.hpp file in the same directory
#   pragma wave option(preserve: 0)
#endif


#if !BOOST_PP_IS_ITERATING

#   ifndef BOOST_FT_DETAIL_CC_LOOP_MASTER_HPP_INCLUDED
#   define BOOST_FT_DETAIL_CC_LOOP_MASTER_HPP_INCLUDED
#     include <boost/function_types/config/cc_names.hpp>

#     include <boost/preprocessor/cat.hpp>
#     include <boost/preprocessor/seq/size.hpp>
#     include <boost/preprocessor/seq/elem.hpp>
#     include <boost/preprocessor/tuple/elem.hpp>
#     include <boost/preprocessor/iteration/iterate.hpp>
#     include <boost/preprocessor/facilities/expand.hpp>
#     include <boost/preprocessor/arithmetic/inc.hpp>
#   endif

#   include <boost/function_types/detail/encoding/def.hpp>
#   include <boost/function_types/detail/encoding/aliases_def.hpp>

#   define  BOOST_PP_FILENAME_1 \
        <boost/function_types/detail/pp_cc_loop/master.hpp>
#   define  BOOST_PP_ITERATION_LIMITS \
        (0,BOOST_PP_SEQ_SIZE(BOOST_FT_CC_NAMES_SEQ)-1)
#   include BOOST_PP_ITERATE()
#   if !defined(BOOST_FT_config_valid) && BOOST_FT_CC_PREPROCESSING
#     define BOOST_FT_cc_id 1
#     define BOOST_FT_cc_name implicit_cc
#     define BOOST_FT_cc BOOST_PP_EMPTY
#     define BOOST_FT_cond callable_builtin
#     include BOOST_FT_cc_file
#     undef BOOST_FT_cond
#     undef BOOST_FT_cc_name
#     undef BOOST_FT_cc
#     undef BOOST_FT_cc_id
#   elif !defined(BOOST_FT_config_valid) // and generating preprocessed file
BOOST_PP_EXPAND(#) ifndef BOOST_FT_config_valid
BOOST_PP_EXPAND(#)   define BOOST_FT_cc_id 1
BOOST_PP_EXPAND(#)   define BOOST_FT_cc_name implicit_cc
BOOST_PP_EXPAND(#)   define BOOST_FT_cc BOOST_PP_EMPTY
BOOST_PP_EXPAND(#)   define BOOST_FT_cond callable_builtin
#define _()
BOOST_PP_EXPAND(#)   include BOOST_FT_cc_file
#undef _
BOOST_PP_EXPAND(#)   undef BOOST_FT_cond
BOOST_PP_EXPAND(#)   undef BOOST_FT_cc_name
BOOST_PP_EXPAND(#)   undef BOOST_FT_cc
BOOST_PP_EXPAND(#)   undef BOOST_FT_cc_id
BOOST_PP_EXPAND(#) else
BOOST_PP_EXPAND(#)   undef BOOST_FT_config_valid
BOOST_PP_EXPAND(#) endif

#   else
#     undef BOOST_FT_config_valid
#   endif

#   include <boost/function_types/detail/encoding/aliases_undef.hpp>
#   include <boost/function_types/detail/encoding/undef.hpp>

#elif BOOST_FT_CC_PREPROCESSING

#   define BOOST_FT_cc_id  BOOST_PP_INC(BOOST_PP_FRAME_ITERATION(1))
#   define BOOST_FT_cc_inf \
        BOOST_PP_SEQ_ELEM(BOOST_PP_FRAME_ITERATION(1),BOOST_FT_CC_NAMES_SEQ)

#   define BOOST_FT_cc_pp_name BOOST_PP_TUPLE_ELEM(3,0,BOOST_FT_cc_inf)
#   define BOOST_FT_cc_name    BOOST_PP_TUPLE_ELEM(3,1,BOOST_FT_cc_inf)
#   define BOOST_FT_cc         BOOST_PP_TUPLE_ELEM(3,2,BOOST_FT_cc_inf)

#   define BOOST_FT_cond BOOST_PP_CAT(BOOST_FT_CC_,BOOST_FT_cc_pp_name)

#   if BOOST_FT_cond
#     define BOOST_FT_config_valid 1
#     include BOOST_FT_cc_file
#   endif

#   undef BOOST_FT_cond

#   undef BOOST_FT_cc_pp_name
#   undef BOOST_FT_cc_name
#   undef BOOST_FT_cc

#   undef BOOST_FT_cc_id
#   undef BOOST_FT_cc_inf

#else // if generating preprocessed file
BOOST_PP_EXPAND(#) define BOOST_FT_cc_id BOOST_PP_INC(BOOST_PP_ITERATION())

#   define BOOST_FT_cc_inf \
        BOOST_PP_SEQ_ELEM(BOOST_PP_ITERATION(),BOOST_FT_CC_NAMES_SEQ)

#   define BOOST_FT_cc_pp_name BOOST_PP_TUPLE_ELEM(3,0,BOOST_FT_cc_inf)

#   define BOOST_FT_CC_DEF(name,index) \
        name BOOST_PP_TUPLE_ELEM(3,index,BOOST_FT_cc_inf)
BOOST_PP_EXPAND(#) define BOOST_FT_CC_DEF(BOOST_FT_cc_name,1)
BOOST_PP_EXPAND(#) define BOOST_FT_CC_DEF(BOOST_FT_cc,2)
#   undef  BOOST_FT_CC_DEF

#   define BOOST_FT_cc_cond_v BOOST_PP_CAT(BOOST_FT_CC_,BOOST_FT_cc_pp_name)
BOOST_PP_EXPAND(#) define BOOST_FT_cond BOOST_FT_cc_cond_v
#   undef  BOOST_FT_cc_cond_v

#   undef BOOST_FT_cc_pp_name
#   undef BOOST_FT_cc_inf

BOOST_PP_EXPAND(#) if BOOST_FT_cond
BOOST_PP_EXPAND(#)   define BOOST_FT_config_valid 1
#define _()
BOOST_PP_EXPAND(#)   include BOOST_FT_cc_file
#undef _
BOOST_PP_EXPAND(#) endif

BOOST_PP_EXPAND(#) undef BOOST_FT_cond

BOOST_PP_EXPAND(#) undef BOOST_FT_cc_name
BOOST_PP_EXPAND(#) undef BOOST_FT_cc

BOOST_PP_EXPAND(#) undef BOOST_FT_cc_id

#endif


/* master.hpp
InC5/ji8IP35kAGuOD2O27OnL8aHL6TePYQh9WQfehlvoB6HH4LSE6jHZE7qMakLTg/0Mj1Bekz2AtMTqOfJa0h64C/TA71MD/QyPdDL9ATqebIbkh74y/RAL9MDvUwP9DI9QXocxgmur1JIfUEv08N6mR7Wy/SwfmSgJ7ETPM6X1Y//8SNs3m2o0RRywsJDKbd/8vGzejhDBow4a72sbalPev+BRgDv7llSLeEgVfNBQ+2yGHxU4moaAzKbI3Jc0GYMrx3Da6g8pQ6x+p736S2Z5eMxkrv1YVgRn3ch4LPT39Me2d2nz2cUsu2RKayeU4lED/ov7ltmlvvtULwzUlGDEvwxvnBZubNe2HHrkc8RYnxGeK5PpCF8ss324tIe39A4PV57W5a119sfi3sNJLsTKn1RWp85bucbBmSE+fK4qeyRJFbMOovA7ri0xyfiXHtbXHviGwuwR5Jge3RHU99UOUDnJ2iibWbJPNdrqxMepDGuWAN04PnaltHNFOiKut2eXm0xnUE7IaDzsxO0uIj2UmejIzDSKvXPAY38PZ1yWa0bh9N8T6SlR6FUVMs8uOmACa1ZLT6iG6/3c8NH4MA7Aupn8s6ZANqtJpvO1o/nuFBkD/1BR4q0nbGsYdrlUmVJm+A7I3w5J6Goe7Dh1DDaSVWd5K/QMnmaNjFMpiODCOeeb6RNfZUp51Q0W/WfC0FgGS5VNjPOSo25wRE/7y4b5TmTEdo8Z6vSLpa/Qf5Y5qIfSh7LS3d82Yb2iAbo+kf5ZJ3LexPr6vSzNtSK1FMipd4s0rmWUhlBhN5NvLBPPSMhA8r4kDkRPmtNmnbVG4ZKY0yVxpjOkNBjd1VHI/TIELQdPP/MWZV8uVTKs/0c7UDHJismzprzpbd1aZcGburqangVfAYH/LAfhGkS2vku2voZ6uhsa4tu79Q1yj6tUfoyJkYUXNifqrt3DaaGjSGjo3OzE95Q4Q3XU5rAftaq49/euep4IHXjwe2Dx+uxSbIaZo9lvF/mTZ8aepEiaDEeO/ELE7zfxuFVpN4SCCsa2n9Jc4K9Ce3rScS8BR6cZYRXBYvwXdvd8GgQbvj2rrbObVGSIBwahBs2mlFtjN1R6gug6f6M5UCQPQzo+l7um9bTPuJEVNmqcCG69hB9cD0nh3ayPRSDbDcox55etodiCClvA0JPOgelXbf1KTHsYjoZXA+w6uytee1wyUTjTj+k20KU+jF9jzPHj+703t4SvToWHSDlfcHQ/jNM45Lz9dQUTp65cSw3X5F23PQKY9hf5umETLeMX/YrtJ3lyicWFeFX0HcH6rkfIsJlwsdleM6naheriL8nNH5qL6sIP2jTw5FoG/0n7XD/VQlZvZ1WaccdHyhBK9sZ6osHpQX3p+2B/SS83Znq4CoeMwSEW7HeaziiX6vgBG9w/Cu2B6Ffsf5xrrLHudEvDb9i/asZBvVbHJVeLvxoJiezjnkrbaHzA89V5JvsBGSdNuPpPHxx0uTZ/mrsiCKR9YDqDB6HQ1oCfy/Qs2AUK2J9bd58I/1PM7KibeejbZvbNrdO3KgnMTfqb7DZCsdoJrk54w23KV9TONh97Rg9lx/TWpDwpxPuFK3rztbKPl4dKR8rmgfG1NOiGde/aGXb80W/m+z73Db4kpWl87O0+q7vD0wVSweKBmnOKH95a9yXv1vSXxP93YL+1tPfOny+kv6uwOcY/e3A5274V+lvJ/zj9LeP/sagycHOHelvv9JAb6vP8D9AfzXon7QmElmzRn+eW6M1RwhfsJbca7X/Cwlfgs8vInwpPr+Y8GX4fIHKCMI2ez5f2KQ0+vNFTWQTny9uIpv4fEkT2cTnu0Gv0nyZ0uM=
*/