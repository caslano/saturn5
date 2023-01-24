/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FRONT_09162005_0343)
#define FUSION_FRONT_09162005_0343

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct front
            : result_of::deref<typename result_of::begin<Sequence>::type>
        {};
    }
    
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::front<Sequence>::type
    front(Sequence& seq)
    {
        return *fusion::begin(seq);
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::front<Sequence const>::type
    front(Sequence const& seq)
    {
        return *fusion::begin(seq);
    }
}}

#endif

/* front.hpp
mhSQG+gtFYpKAkz2pFCoN1yIQp1kJcOJaBBVXV4Tz20IhVqyMgSEHooVLxCPoowtx+AbSiJtg/IvMJ0aLB0K7aAuwd/xZsKt21UYhsZMGwM8q63sahRWkr1MwkZ3XsUDVxbA/HcVbeAnw1RvkyWL8ndaH7yUWW8lMxT2WWufV7nXpXfY0OUwFf5ELsbjQ4B/J9XeiPNloMom5X89LRx7liL228jt9O23t7f+9m/n+DaqoqY6MHH3a04WcjkOOtl2cUHjI77JD4kLjo6a/IjfyfawRketKI8wu5JqhNfEBcfuf2SyOxif6UraBvXEsxaUc8Hxmcn+QimQkvB2kknt23iTKgyr7GQ2+bKGlXSKM/n6DJuKfy6zrmv5DdZp6TMzpQ1mk5nmLElYE5re1cms/7om2SQGaszOoHU3XEYS4FkNXFTg4tApS6fyG+f0Q1ihdSfDlVC83raw8XDn6YmupBB8u+oanCWnr00ycc/JlKlwKWw80lUIPM0f3AkPPsF5OthrPH/XY/ps+O05fTpUb66XQt+kS0n1tEWNM3P6FVU3VPknMGs/KB2osVVb7XCB/B20XgJX4omqdF9uoCa92vrbW0kmK704CVcVJpOl3pmx35m/359GNWU2DG3wpwRSDsLbgmCv3W/x8ZqFC2xKzfd5Ksl4R2WetRFewvIEtK576ZjSb8NQdxJtcHmILkFah7gMlngkmj0UedQ+
*/