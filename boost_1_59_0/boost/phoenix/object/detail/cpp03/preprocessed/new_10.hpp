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

/* new_10.hpp
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
*/