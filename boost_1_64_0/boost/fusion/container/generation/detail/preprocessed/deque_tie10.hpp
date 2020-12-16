/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct void_;
    namespace result_of
    {
        template <
            typename T0 = void_ , typename T1 = void_ , typename T2 = void_ , typename T3 = void_ , typename T4 = void_ , typename T5 = void_ , typename T6 = void_ , typename T7 = void_ , typename T8 = void_ , typename T9 = void_
          , typename Extra = void_
        >
        struct deque_tie;
    }
    namespace result_of
    {
        template <typename T0>
        struct deque_tie< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0&> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0&>
    deque_tie(T0 & arg0)
    {
        return deque<T0&>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct deque_tie< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1&> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1&>
    deque_tie(T0 & arg0 , T1 & arg1)
    {
        return deque<T0& , T1&>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct deque_tie< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2)
    {
        return deque<T0& , T1& , T2&>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct deque_tie< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3)
    {
        return deque<T0& , T1& , T2& , T3&>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4)
    {
        return deque<T0& , T1& , T2& , T3& , T4&>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
}}

/* deque_tie10.hpp
7l4TckS4vJfTr88qX9P/rMz75nh+88PJI1L2fuW/T8p/vozVuEKJn/LfVc+//AtqseYkc4Rlnnvt15zM0il/e7A6FWRtgDh51M8MI09oxX7sXBahypN9qnINHFD/vzZP9iB5KtbJkzMgT8HXTOijmfuvl39lv54B8/hlvE/wufOUif7c+bQGh3bufM8gc+dLGhy5ufOV9fXnzlc1OHxz5z11uEsD/bntUZEHf257RQP9ue2JkYd/bnv/SP155c7IQz+v3JOG0sjAdQtuakf98KYhld9777IFNaZBfV7rNQw8r8NIW7X/sSnq0PPG74jkzT8fC3XWCVhCPqIa+sclp7VO8XnO6S2ac6rOc6OjA9NRSjpSNOlguYI6pcH/bzFrFRjv0qnVeIlDPS7i/7YuccK5yufffz9lYrPqxj8tem2c44r2pj11GxdRFea5/+c3Q/pdlT/iG8J875iPwfaYgLHYAzthP4xDCyZgJp6CudgVZ+KpOAfNuAj74R3YH9fhAKzEgbgVB+EXmIRHk4bBeByegU1wCCbgUDwHh+EYPAsvxBFow5G4AM/BEjwXK3A0bsMx+DGOx314nsyXT8VOeD4OwAvwLJyAY/BCTMU0zEIrFuAkdGI6XoMZeC3acCVm4p04Ge/HbKzAKfg05uDrmItbMB8/xAL8Gh24GwvxLyzChpyvi7EVFmNrnOl591CY5xkH5bx2lTHg6vUmHpLz+rCc13U4Gh/FNKzAy/BxvBafxLfxadyJz+DP+Cw249iVGIvPYWdcj2Z8AYfjizgGX8LZuBHn4su4FF/BlfgqPoib5Ly9hk9jFb6Jb+IH+Bb+hG/LedyM7cnrFjwF38GeuBX74wc4CrfhePwQc/EjvBK340KsxiX4MS7DL3AtfolP4A58Br/BSvwO9+FuDKe892Ak/uRd70KeeXC+jKNQr3dxh5yPVTgU78RiXIOzsBwvxbvwCpR1NMiXPHfI84hy3Bbu8TFs7CTHvQr74DwchPNxMi7AmXg1LsRr8EZciKvwWrwHF+EGvA5fxBLciNdjFd6AH+ON+Dkulut2CUbjzdgNS7EXLsNheAuejctxIt6KVlyhWucgrUFo6z+UNAht/YeqBqGt/xAV6YvXGRZ8HYbESIm3hv2ckRJvDftVyn7NCZWa9FlV+1V70lfDflENJX017JdSw35OY1zJIRlX8m8bU2KsQ3/gY0lSLo0w5RDmEsoITxGqCY0uY3wJIYVgJ5QQ1hI2EXZeZowxMTZjMzZjMzZjMzZjO5zb4Xr/H514B+X9f+s7mDhGlN/a+ico7X3YGI9W+uF+UPf9y+RHi7XAM28zq4a+Sztq+ymLg/RTOlE7f3l+kLmLJd7Pff2MpZo5lI39+tlzpX9d4pB5q9K/rp03qV0j3Cb7qtYjKMzN1qwfzz7yOenUzJt2yrzw+AZ8H2OwG+VbuVuvfDmGlG9FDWMsLvhVxljkZrj+/7Rf/cdcVLrSG/q84uj6tZ5X7C3/HTrlv0tT/nt1yp8E65Z/mnffJIrDV0fed+072J7Tzf2ZwxvHcBLojre/73xo6gvnUo6VgiNd4yLSHcW++ir7pXiPVepNxxD+36/vjv9X93tPcf1/snf/4dKn7knz8CmevvNi33nxn//LPkSs6V8vcv1/lvc7g/mO+toYw1f861t1hP71XPm7bn1zZPYxrudQrmejT8/o0zsSfXpprj69oeZ335tzaaNFDzZyvH9d7NIOdevTc5rk7zqeIH0Cx0p996x1Ho0dMQ47YTeMw34Yj6mYgLOwM16Bp2A1nopfohm/wW7SV9cdG2MPzxrkR8nfP/m7SDpc/SALUdlGSTpSMAXH4AQci3YchzNwgsQ=
*/