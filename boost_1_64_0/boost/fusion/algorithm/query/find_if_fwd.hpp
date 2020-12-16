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
nJ+7TLtOVsql23vugJTrUaSbzImcTLq4pfpyZWVnR2cU5ywpWpiTHUhcsQ86iT6adbCTXc/1nEy+87bb/MJcQzy9fueY+0oiacPK9frxBs3v+v3AIoZhlUU+x/mXZH0+fsci0ueVpbP5WInZt0re5SxHro5FB31e7hCGc9mZKKc4oDhzRpsnwqtG6dcTJ8PnxQ5KPLWQZe7nvqmGvRcbRNfZomsaMo000cusdS2h1WUV+LaP1LtJ1xiDrtJHJD6dnF1iyK200TnvB/yRejwH6YRMJ021WWfXVSIjO6s0y4/3k4p+bfU66/cM+4H1OFurz5ex0ndenjG2TjfG6vOLbmseY2fE8htDfgxGPuvDHRtG9j2V814q9huIXBPLn+X685ZgP7niytXWd7k8NuSajQ2VXxn2kD2XP9LW2knslVTyjjPm3QJ1J/vHyl5cnMgQH++Q6JIkY+NkRWibTr0uMtI2rc131O2nVuxq1zXLZT1LrD5OxsR2spZW9BmKLAinvkUf7c3TvEX+j4d58p5VdOGzOSZmTTvz+DgT/aJWmPIOaCyebOHLiGpvzmsu/5Npzivg8Zj8TPdHm9tb99v6Rab8Auq79aft47Y2tDf33VnKGGUuo9/99zJpJzES5+5ACLaEz0L2u8NR4jo3DY/N7gKIZWi1112eRXwOp0U8iHKo3etOxnh5r44HscR73RoSLt81cn2IMsQhUvbBO4Utu1BmZT3r6BLKCMN18UoL87PFRkr/cpS601wb676OTFU/6/cNPCV2LJd3oyWyb2CmU7UjNyzY0o9r89nYN1Diguju+a807O/3mYylf0Fmk65uhaq73M1l5JeUlOUUZyzKKp2X57Mc9vcY5vjJybp7PXN8JaXuTmPjOnSNV/xZFd66GwCfdsW9me/xOenGwi5h3tjE4TAaxo1SnJ5q+bhESNlKfMeckvbrLZc55q1B/wVqG73WrSeBpMQW3u94nPbW/ceuNi9ml7b7PmUPC6O+UDoF3YHYztxH0i36yACdjb1x1mIlBktWCY1M7Ke9d9gRZvYnXq+0j1V6fyLXN59jj2dsfacZfsSxncz63Ig+UZUGfeSZMZAxf04z9tWts9Ark/M5DXrJWO23TleNaopOsg+BxO4rRIG+cD6cyPmqCt065eRmeB8OxU7lPtp+lUWf3mpxL15tvBeX73ep/d/d5Rw27dM8hnvH+raRrnT0I3154yQW32K57ymQ+zCHrrxyG+bHdU3iGZn6ep73PkzXVw50NvuXX46hHio9/uXA+8oHfsZIjutizntuLH9u9uTd9H4xLtZOB30fqLXQITsW3VQdmtYHJof7t39vusQX/LAV+cNjMJf8K935M86XOTPys53NfUb+wjXeuk8UYWinzoyiwoJl+hiatV3NMULno1f9rZ4YjJMTpiekxCe5wjCmqhFC/YmVqs0nLcIYFxPpzZ/Vlvn4GTNZH+/xVDdzrM6YCPtYnfUWOuUrbcJOJyJ1NlUfT/u41hC7dozHPt3MMVQ7jqR9WOoSWHzh7hGqHvrydzPH3wwjzxrLPAOPkds9wnf8TY8u6ZHm8tfykNig6qKf/hJobOsxI6xtcCLSbIOXSRu1xjrfQONbjxnh2waeNlDQ3dweF9IeM1Vd9I+NRIDzW4+PzW2RsUvaoqGvftLdXBcVXKuqrfXIL8koKSouzckOpD6Wj7KONZ7Zw5z3ImxQZ503w5HvPCMkz4Wu8s7DbYNXyJDv0R7WZXastco3sP5nV9Y5Pa3rO9oyz8DiZgdS3w0WehShh9NaD65VyquZDGVAbZI+MjY3Wh/Zvcz1cZAf1djoRANski7asaChl3ksuIm6q7fMM/DxcPko32M=
*/