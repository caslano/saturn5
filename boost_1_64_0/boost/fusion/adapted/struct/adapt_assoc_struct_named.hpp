/*=============================================================================
    Copyright (c) 2010-2011 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_NAMED_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_ADAPT_ASSOC_STRUCT_NAMED_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/struct/adapt_assoc_struct.hpp>
#include <boost/fusion/adapted/struct/detail/proxy_type.hpp>

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED_NS(                               \
    WRAPPED_TYPE, NAMESPACE_SEQ, NAME, ATTRIBUTES)                              \
                                                                                \
    BOOST_FUSION_ADAPT_STRUCT_DEFINE_PROXY_TYPE_IMPL(                           \
        WRAPPED_TYPE,(0)NAMESPACE_SEQ,NAME)                                     \
                                                                                \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_AS_VIEW(                                    \
        BOOST_FUSION_ADAPT_STRUCT_NAMESPACE_DECLARATION((0)NAMESPACE_SEQ)NAME,  \
        ATTRIBUTES)

#define BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED(WRAPPED_TYPE, NAME, ATTRIBUTES)   \
    BOOST_FUSION_ADAPT_ASSOC_STRUCT_NAMED_NS(                                   \
        WRAPPED_TYPE,(boost)(fusion)(adapted),NAME,ATTRIBUTES)

#endif

/* adapt_assoc_struct_named.hpp
m9RjQQT9Ot0n2OKqf5z9oyWvGFJcnuW+2s7IupsotoV26OqYAaIc4qd69KyUd4uFChiXepU59w/RQxh+amJnN7c8pVPdd9Z6w+NvPoclJ99O6MQAdCZ70Eus5HpDciCp9f4ADMjer2yAcaPFEHuA3RSUgp0Ql5ny2t2nX3mYOQRQNlASgVuxRLJZbi6ezqlmuEiM6GELowA7wWp7tpiMIVQwUl67D/fwLRfuL+7ZfRrG+k45jCLGam08wPW9e96jeh+LzZAwyWeWcJjIodcZHiCYdxbs/RHC/MviRCYlxoN2Z0s6RFDw2GlyO9mUlyHlSsarvIi94YKk2pyoc7YGB6zCt9lyq+NqmfDwRmmqL5XD0R9cij8qpCk4MecFo7W87A8D7OskAgb3ZnffUdZLe9/sELirvoDKAhxAXLQzBA8UCg0+cNbNSZP3cgc6tznz7S4Etgx9x8bObSIH81dQLcYgXepg30oN/ycpibgIsQtBGFP4jjVogjNwjLArYdb+VtpulxS/E0isoZ3NkJ44t9jpyl8HJcXgS80XQmyPs7fJbFAW+0YAQo4OMw==
*/