/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FIND_IF_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FIND_IF_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>

// Forward declaration of find_if algorithm
namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct find_if;
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find_if<Sequence, Pred>
        >::type
    find_if(Sequence& seq);

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find_if<Sequence const, Pred>::type const
    find_if(Sequence const& seq);
}}

#endif

/* find_if_fwd.hpp
TEY01ALKEZoaHEKRCTRlbvnRB4Z9N8vW/udIjloF6IyUQKUzgv6oAnNmpQ3hpT++f5qM4aUzHHYG4yk8/YDOYEq1HvqDLp23JCYD+JobtMRsQKa5kihKwo9bQb5ayoyrQmB83+t0e8MR3MIsAChPMCnNGg15yOyWTJobmbkFedYJniCjHlm/XygnyXqs2+ZIIb6qLzn3mVvrMCWHirHcZ9Gx00QRLvhDgZDmFs6rx7daOUdBEN33oofRMAIfjkbxefVnrRaQ06KdNlFpqAAMJ4PyFlbgvP3VRy/g1psDqlULglKVNfw6+ER7+7K19nNv+NimLKfzmKIltZLz5iG9kSuod9/H9zJLiQT9u5FEJxcQTYaP3d73yZ0fMjpHgfNiCfNCKkFzsEGwnO2uqtWF4X6QaWCUoju5LBQzdEtWNFPZWq/QBhSoK82ZuoaDtgAzujDBb1BLAwQKAAAACAAtZ0pSNhUoq9x8AABQzgEAHwAJAGN1cmwtbWFzdGVyL2luY2x1ZGUvY3VybC9jdXJsLmhVVAUAAbZIJGDUvXt320pyL/q/PwW2Z91jSYd6kHr4NZNzKBKyGVMkh6T8SDKLCyIhCTFFcAjSspJJPvutX1V3owE0IMqzk9yrZLYloFH9qq6ud/0hulnMwhuv
*/