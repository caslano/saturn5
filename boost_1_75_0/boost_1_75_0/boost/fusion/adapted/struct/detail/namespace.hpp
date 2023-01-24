/*=============================================================================
    Copyright (c) 2009-2010 Hartmut Kaiser
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_DETAIL_STRUCT_NAMESPACE_HPP
#define BOOST_FUSION_ADAPTED_DETAIL_STRUCT_NAMESPACE_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_BEGIN_I(R,DATA,ELEM)                \
    namespace ELEM {
#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_END_I(Z,I,DATA) }
#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION_I(Z,I,ELEM) ELEM::

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_BEGIN(NAMESPACE_SEQ)     \
    BOOST_PP_IF(                                                                \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(NAMESPACE_SEQ)),                         \
        BOOST_PP_SEQ_FOR_EACH_R,                                                \
        BOOST_PP_TUPLE_EAT(4))(                                                 \
            1,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_BEGIN_I,                        \
            _,                                                                  \
            BOOST_PP_SEQ_TAIL(NAMESPACE_SEQ))

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DEFINITION_END(NAMESPACE_SEQ)       \
    BOOST_PP_REPEAT_1(                                                          \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(NAMESPACE_SEQ)),                         \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_END_I,                              \
        _)

#define BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION(NAMESPACE_SEQ)          \
    BOOST_PP_IF(                                                                \
        BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(NAMESPACE_SEQ)),                         \
        BOOST_PP_SEQ_FOR_EACH_R,                                                \
        BOOST_PP_TUPLE_EAT(4))(                                                 \
            1,                                                                  \
            BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION_I,                  \
            _,                                                                  \
            BOOST_PP_SEQ_TAIL(NAMESPACE_SEQ))

#endif

/* namespace.hpp
RTO2LK9bMg9zwXwqeJjFCm7dS7fExC1zJt/qR7dmslGDWz3plpgWZs7lW4l0C/T9JN9y0C3YItL4VgjdgsaI5Ft/TdNpSouz5FPTAoDZtk0zVxOPPGVX0aUr8Ik3cz5vE82dBpPzTIQ8yhhG7v05Ngryc+qJjx0W/42rVkP9ht2NcSVf0uIqegldIxeJq/FcKnkkHF8MmzFVxp+L6emvfP2Rrzv4uomva/i6jK9f8/VTvs7h63S+vsrXyXx9jq9Pc72bvqDrGr4u4+vXfP2Ur3P4Op2vr/J1Ml+f4+vTfH2crw/zdSRfh/F1EF/78fUmvt7A12v52o2vl35hxnupq0/v7+DeSTtWO1vKNedJCal92u9Y+LLcq4Lj95Uv4vH7FtDEAsqLVH49LjlTeuGS8/JQPH7fYqRMweP3LX7HIy/T8fsWI9MD680Cw03QR76BBq83p4TwdsjdwoIWCB3rfRdWJARYWJqhEki7NQFpD9xidMLl34Qttb3Qfah4qkSd7Yyos6Ku/o/TUvMGBXR2B7wCnoEfPgArzeNQV1rKEycLLpIrTUF6Fa7tBm4RVHYZOyvhx927aq8ARi7DyvyvMH52gcGrTMjlg7g38ER8g/jGavMbq3lluBI3dAoOmw8OW6s/ANxFIMvlm8lQV2cKpbnYVVTlh3E3PeVqGndbjnQWpQwVSlkl/ujlHFpwlbnYOMjG9vp4hJhP8651
*/