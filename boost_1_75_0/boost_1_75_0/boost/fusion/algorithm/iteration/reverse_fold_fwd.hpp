/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_FWD_HPP
#define BOOST_FUSION_ALGORITHM_ITERATION_REVERSE_FOLD_FWD_HPP

namespace boost { namespace fusion
{
    namespace result_of
    {
        template<typename Seq, typename State, typename F>
        struct reverse_fold;
    }

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State const
      , F
    >::type
    reverse_fold(Seq& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State const
      , F
    >::type
    reverse_fold(Seq const& seq, State const& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq
      , State
      , F
    >::type
    reverse_fold(Seq& seq, State& state, F f);

    template<typename Seq, typename State, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::reverse_fold<
        Seq const
      , State
      , F
    >::type
    reverse_fold(Seq const& seq, State& state, F f);
}}

#endif

/* reverse_fold_fwd.hpp
UE7JO/LlVflSa6JJqtoLIEr7uK9N9kFs50swHJ79ob7UWHECruNB6kIppw7FVHvy7hQ8VtT3RjQHA5e6VsaHDCxoH8flr8ARxYeP6FLO7gHZaxDNKaaQkqETlMzloyNX958zKHtfPFQHB0XgcgioG7S/iDmlHVwVjTHUkFbnLfzR7/F4nMP6c8pXkOJ7H+WsfsvXY4CByVnu9nlXOKu9otn8FapzCDEQz8eDwCAn3nZ2DsTEzk89bOuYv9+WUoWShLNzakSinxxdd8yvdSveFXlKF5etrjINHPoUUyCg7DSHm26pZ6W5s+nuLmcb3eH6c2rYU1LOMZQMgnJrnuLHGyalqhaxxmKiQYGz2U/ACH07iVqEvSBKAMQFqCG6ehtcHDxKQl/B8FTRKO077sW7T+J3VscBkar5mbJVWoDWopMcia+q5Xq7TJ/BhbsLokSCbZ2Cl/5Ay9nghu4nh830MdzQBW4RtWzTaiG+3r50BV5UCQp8eg/xqdRCOUMvK6izQCe38gw5bxItcNbck1FOU3lp/FwB06Zyb7RLOQoM1g+xSLaWZrqV96kj6G6U7kwEK+hvMIXQ6nKxDTS+HEBpsj5uMHrzfURGbzniePfvpkVo0CcjV/mc58MTC3l+YvgtX87GqEIvfdYJ5b0l4CjclNPBVFlf6hZ17jcxT+nf36JKYivBozVmyj7RJ3DXAhenf6KAyC+1c6zcT41V
*/