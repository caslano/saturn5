// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_std_set.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
# pragma once
#endif

#ifndef BOOST_PHOENIX_IS_STD_SET_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_SET_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <set>

namespace boost
{
    template<class T>
    struct is_std_set
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Pr
      , class Alloc
    >
    struct is_std_set< ::std::set<Kty,Pr,Alloc> >
        : boost::mpl::true_
    {};

    template<class T>
    struct is_std_multiset
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Pr
      , class Alloc
    >
    struct is_std_multiset< ::std::multiset<Kty,Pr,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_set.hpp
G2V6PS4vw9V5ahP/Zso5tfhx7G/Hj4qLHTXRtXqhS/K2LbUx9e1vNvXct/ttsM7/XGX9bsxn4rAJo5RFqNo5rA+2tmfnBmt7ziNWiTWW1pyr097003PGZno2kkupTQya8yXHXdX0pG60zsu7lP7AGkubjdWZHndMNM3HXQGe5+N5ySVMcglhWKx8uNWaC3szXufg6fqw222WsdxN1nrZHMyYrbm4FjFv2vZ6+2XMeOxkk7Wd9aNCog3xtSZ2ydiGY0ubre1rGznFGMdN06r+NG2VadJPwwubrXXYn2lwGuNIs6r+Oj0qwNimajeztCltWvtuseYwgByKTDnQS3sdX7v2UtqPftpLbOLeGsz3xrhK0/Fqedrque1oy/TIrdblaAkfyrTYyh6tcqyXvTN2ublijmuSqr88vWWa/hMy/bI82a4zHt1qbc9LyanCQ07ebguo0x5eZG3bK5SK2G4fx9vtgeVh+vdBybwuss7rgjBKeojpy/rwLVOb7x1kafNaHfTdZs1nNflEe8jH220E6qCK/kuum5Ec2kkO4Qw3US5BcuBakLmJyd7fz5/LwMlEwzXpEbe4fzhVYk1mWEusIi2WvLslJ3tRdrwjKcl9uwDP0OAeCy/up1SW83yU6ba9t+NRyaWn5NKd4Wal/d2m5SL3BygX82Q4vTnuncOvElG/bTjXdF4s7lb+kriNGboy/J2RRHuIHz986qhhU0aMiR8xISb+2onVOJdALnI+MTHedH4xvvKYtuRmeG5koul87hnJtb/UVT+GPfyuwJKrM9eX+rpHiemUHOXzXNO7ZsZvdxfcJTnsUO/9qcxBd94ScvOrHd+ufZRutz4bdYPSVm83xeMu9FQlWjWmN0jiFTIepZh5HVh4m1xDLseIr8ZNYeSixXQ/SpttY6/O9eVmEVu3LKRkZ2WYr8uiezWdD5VzgNTDGvKawufdO8gDzcc5mQZjv3Z75fsjGsszpzYzHTE7tenQv2eB1Vouz4O59PUtrvqT8zOL5GR3kOS8lfHLV7b3pOcRW96jYHzeh+QaL/N5trSrospcle7bdZ9hPCfmUxzZl5zPdvcDvynxbyFPw/vhd1ifyVqf3wTs0uLPc2gPSI2fuyQ+zaf3bRjWgxLzM5k//1CfyWWIqV3/TB/MLEp25Pv6XDbt/EKy8Z3ma3Za3xt5K9NefIenPOTfyp0D1brfw/4epSZ81o/oSu25wPrvlcs35+Wmqn2j3JuYZLnux3R/9y7+ku8bMzgYtitt/06baQLWbcqheq+npTo5ac8p22V9n9XtYXxvyiltXqYrGV+uJQjSrevcjbXy3q8CCjjlnUPqcztZoccnXmo6aC/66ThwhzuBx2Q6HmJoGMI2y25tOrROxdUvV2s66gc+T3n3Offqv78jV3sOV+U0hAdY3/fIEXv3dMv/pybPs7ybc9Cd1vPcZ5Ugd2vTxZMRc/V9ULWXQ23+6O9dYjyW4+53yftkJIci6bPLdDlkSU9dnfPtlr7afL4wL0Nysvbd5/V9t5yj0p5PQV8acY+7L13X1N23jpLP6+XzND7bvTNnzV3mfRt5/sQ92jRmeX3PjfnaN4lRKDHWMRwNYd5qMdy3CidlpcfnZrkuYMicV42YQfrtarlIT78dv3y3+8eJEjeeYafS7xRrcbMdzvTEJNeScelraa3bKtbzy/r2c0Hij5P4YxgcSvvR4lfe3ZThvPT0NtHeEarblpbPc83n1u92F9wrbfcehgbKe7T2WGIrk1KNPkEX2/q8Ye1e9cZMgf4+vmB1W4TvuaicmZuVzdlnw3waVOwOtFWelbwRXdfe3VuZq/t9qgu0a7qiqpGrtpzL8qKsy5yuW3tludM=
*/