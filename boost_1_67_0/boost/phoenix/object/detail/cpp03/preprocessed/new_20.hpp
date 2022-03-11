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
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
*/