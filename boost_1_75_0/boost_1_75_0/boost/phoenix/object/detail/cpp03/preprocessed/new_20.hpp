/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <typename T, typename A0>
    inline
    typename expression::new_<detail::target<T>, A0>::type const
    new_(A0 const& a0)
    {
        return
            expression::
                new_<detail::target<T>, A0>::
                    make(detail::target<T>(), a0);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1>
    inline
    typename expression::new_<detail::target<T>, A0 , A1>::type const
    new_(A0 const& a0 , A1 const& a1)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1>::
                    make(detail::target<T>(), a0 , a1);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2>::
                    make(detail::target<T>(), a0 , a1 , a2);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
    inline
    typename expression::new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19>::type const
    new_(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19)
    {
        return
            expression::
                new_<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19);
    }

/* new_20.hpp
paCW2vJjtHqF8Z4DxxIXP9HYnR6nOzKE/yMO2Zv4G/jrDNcarqbaOh0sqMFiF38mf/5M+TkoUu+iRWrYF/6BFqmXdLCYxnxvFa6gq7fjytvpdoUzvjgqJTdpd6G+8rq3VkpVe4a5Ldm4+tDvL3o+1losN8d1UXrQr/O/yzp08nLCuUWnvAfKlQSpvzmZaPRk5ITayiNHv962IVfby+3z3zPmz3pupfYjT8axh9+dCsUCrz61l/KPK/lNiz6d8d2ac1KZI/NOqfVvPjVxe8nv285N2umZa9D4YHFY47H8wy2mP1q3arpN3TElYZLvUkP/UW5Dhgzeu3hKwdKnC21bX027E+wzwnH7H8ud3/bXvzvqTrmw33HVINVRy0dtPffX/KCxwQpnZ804cen0dzP6/D6s8qGT1e78tSYq/X1qHl5PWlz2w5Ij32zyvvVafnTm0yb1lodSLXFhKu9a1isrDbI5xw+d63gxY/P7vj/lLv02fPspvYMqa2a82Lh6ZuAw2V/9D72a5Hf2VNSDPr7OUjvXbj+UeTb92ue7V0g92DXq4YlPDEyn5hwdNXWS18J1uqffjN9+4vjKwaut6t3tIyru/LJJLylh/W+uO7f3eaEoteLqZSOFk2ff9/WuWXZkseK76MBla69efewX/fKbEvfh/i5xS8zkttz08ZcOVDO+NGLs8Dv3z7wvd02YOvpOP/X5WV7rXz37u2/l
*/