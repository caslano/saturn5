/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_JOIN_200601222109)
#define FUSION_JOIN_200601222109

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/joint_view.hpp>

namespace boost { namespace fusion {

    namespace result_of
    {
        template<typename LhSequence, typename RhSequence>
        struct join
        {
            typedef joint_view<LhSequence, RhSequence> type;
        };
    }

    template<typename LhSequence, typename RhSequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::join<LhSequence const, RhSequence const>::type
    join(LhSequence const& lhs, RhSequence const& rhs)
    {
        return typename result_of::join<LhSequence const, RhSequence const>::type(
            lhs, rhs);
    }
}}

#endif

/* join.hpp
KGl3ebZRzz/9N99kyGeQu5Ebfnlx41e6V7isDS2VhqGRlE89A20UEDKmgnCk54SzHBVTCZqYMc6cbaGUxDZuQ3kWPXcCo6dWECbe9F9BMHhSq7Kf2NcXqnWflBMMVv6KbN/4nGZFB8CHUU/s637hBLVrW32hQb6tss1axkErnfzN6qmcf7NpkWVvwqcNLt6SWc9AI2lmtn+nVTEDTvOzuFdY+uuL2tD5XyFLdRzKGxT5ayH+tIh0Oz2PthiGRY7z9LvtnUxpqTWV2oRAugWOrKnXTefEJzkrdXBLgKdbgVVM59TsWc3iohrTjDUMny2fsJxRIvpJFHmpUWXEv/WbzBUJPmUVoZgY64srNVoxghmGGn/Rwpbgncr1UnEZsJdQcXyKKBC8fCAN7N1E+iRzxv0CfkOFpwN0RBYAJXcb8nTbuRpIJNdyWQy06MXxCUEChn5SG6xsUaf7nyBMusslIub3s2VJRvjMqA9UFiD4qHZGmd2ujLE6cW+W/+7IBr/2rMZSQ9iuO+opEuX/pBtMeRmA5Y+WOsDGjU4TdxeQY4JkDBH5pSrh2cr6Cw==
*/