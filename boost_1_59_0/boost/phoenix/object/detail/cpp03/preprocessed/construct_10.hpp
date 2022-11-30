/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <typename T, typename A0>
    inline
    typename expression::construct<detail::target<T>, A0>::type const
    construct(A0 const& a0)
    {
        return
            expression::
                construct<detail::target<T>, A0>::
                    make(detail::target<T>(), a0);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1>
    inline
    typename expression::construct<detail::target<T>, A0 , A1>::type const
    construct(A0 const& a0 , A1 const& a1)
    {
        return
            expression::
                construct<detail::target<T>, A0 , A1>::
                    make(detail::target<T>(), a0 , a1);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2>
    inline
    typename expression::construct<detail::target<T>, A0 , A1 , A2>::type const
    construct(A0 const& a0 , A1 const& a1 , A2 const& a2)
    {
        return
            expression::
                construct<detail::target<T>, A0 , A1 , A2>::
                    make(detail::target<T>(), a0 , a1 , a2);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3>
    inline
    typename expression::construct<detail::target<T>, A0 , A1 , A2 , A3>::type const
    construct(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3)
    {
        return
            expression::
                construct<detail::target<T>, A0 , A1 , A2 , A3>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    inline
    typename expression::construct<detail::target<T>, A0 , A1 , A2 , A3 , A4>::type const
    construct(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4)
    {
        return
            expression::
                construct<detail::target<T>, A0 , A1 , A2 , A3 , A4>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    inline
    typename expression::construct<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5>::type const
    construct(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5)
    {
        return
            expression::
                construct<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    inline
    typename expression::construct<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6>::type const
    construct(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6)
    {
        return
            expression::
                construct<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    inline
    typename expression::construct<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::type const
    construct(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7)
    {
        return
            expression::
                construct<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    inline
    typename expression::construct<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::type const
    construct(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8)
    {
        return
            expression::
                construct<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
    }
    
    
    
    
    
    
    
    template <typename T, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    inline
    typename expression::construct<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::type const
    construct(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9)
    {
        return
            expression::
                construct<detail::target<T>, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::
                    make(detail::target<T>(), a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
    }

/* construct_10.hpp
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
*/