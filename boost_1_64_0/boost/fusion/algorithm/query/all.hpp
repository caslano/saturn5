/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ALL_05052005_1238)
#define BOOST_FUSION_ALL_05052005_1238

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/all.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct all
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    all(Sequence const& seq, F f)
    {
        return detail::all(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* all.hpp
X6o34j6mpY7ltaqNu2aqYqUbpb5AeUFTSgQ/XJs9q1Nfrvt5xlqxz3G8PqOpss9582dm5vEyddy8jcTNO0o+fzvKJ+xjsF6dRIQ8iZtLLoEql3+VxFluo3zG9pMdtp+ZlXVmekH2nOyZRekcaXCfZ3Ey8fAPLNsIyS4oMHq+guQVsFWHvALp+4XFyn+rxjuwnpJa4LQP5fIVd4vswybZh+BKp30oKlhYaN0FD56lr+zDa5Xe70Oozj4Ea/dBdW4FSxx+FuV4Sjblc/ah2XMO+5CXm1lYO5ue+/nzlLYGqtoq8wkGWOaZzHeqf7vUXyOxxy+VQv1lmvqJzJ/pfuyLPANbVb/S1/7NlH/nZ87Ldh7zQpt0zwH1sY51eM5/E0oo5SvaWfm8vZ1KD6nPV/fzPzr1l6rOCqkzVOrsLnWatqrrVJ1fHsxxqK3TfjwiAvTPhziHOudmL8rNOkrnw94A/fOh0rn+ejkflLwi784H6/VxhMTwJ8tnwHjKbS1o9zZ7O+VUULJ1Cjy5PspngO5x2SD1pUh946S+jBfs9SmngVRXp7p4dr0qJyBa6uqrrD+AzzfnurItOQlt3NQTjJsd6gmX+HaJ1JMt9WRQvlauny/W1kOnKyeZ98dY9TkmMfSBcj5FUWqoo9xSR1Zkbrrqs8yb4/SN5N1Y4+azLblq+XJO0Sa0n1Oqdq2UdvWRz45wyvfRtM3SrtzIrLq3i3NW1a45zSVHSZ37wRtcf8xexEv1N2av7Hj9MXvJLzXsmL0Ya27eCfrPNyp7qWGeb3QINzY2ilUbx/ivrc1FOLnqxNJZXT4c9MPTfR8/bd7InPrLvdDPafA+J0M/x8IoN8Ioh8MoN8Iol8IoB8Io18H73AX9HAijXA2j3AujHBqjnAajnAzvcyk21OZAlLyZ9PvOrm2ue3jS9vLr7r0+yjjHwjg3QmJuW+yxNHNjdSytsy3mJr9RMFBnvWDbehRZr6OL7ZkpybLeKlnvBMyS9S6SmGiJzH26GCPxUhyJl+FovBzPw6W4CK/Aa3AZrsAr8Ta8SuotM8l3etwi9Z6CS6TeHKl3DgbjXAzFPByA83Aw5uNQNOM0XIBpWIhLsQhLcSHeh+fiQ1iMT+Ii3ITn22Lb8j1dvq+ZHWPbkmtwPE7BXpiKETgVo3AajsfpmI1pst0SSplst0a2exIWyXb7SE5FPwzB/jgWB2AqRuE8jMbFGCP7FYurcCDeg4NwJw7G3RiHX2K8fY5R+X4t55nTHKP3yhyj92FLXIPdcK30/zrbduQ7M4TqbOdO2c4q2U45dsW7sDvebe9vvgcb93e69HeG9Hem9PcM6e+Z0t9Z0t8U6W/5fmvQ3wnS38Okv4dLf4+Q/h4p/T1K+nu09PcY6e+x0t/J0t/jpb8nSH9PtPWTfH/FyTr9dLPkStyCnXAFDsRbZb9ut21Hvpdiis52rpHtXCvbKcNYvA7H4Q22HAj5zinfRc1OORBdZTvdsC92tx0n+Q6J2TrHqYe8rie2w17YAXtjMoZjCp6BGRjhmDMh2x3o5rpXI+v1cbmefNfC1nLsjcbLJst6Pd2sV+ZmvYN+nuU4RBX41eY3FF+gn99gz2uw5zOErFflNEgug14eg1EOgz1noZjiIk9BchRU+QmaPAR7DoI2/6A0XJVvoMkzOExR5xfo5xao8wokp4DSJt6ePyC5A5I3YM8ZSFhvzxew5wq4zxP4CiUvQDN2deUaSy5A6FAKamP/rsepZq3XxP1Vsf7USHWMPzCB/aEU87olymtQYvxexfddx/Y9i+tb4/nBrDMCtfF7z2P3ZRiFKRSJ0ROf18bmD+NhbDlCHYePo0j8XRV7Tx2hirmr4u1pvOc=
*/