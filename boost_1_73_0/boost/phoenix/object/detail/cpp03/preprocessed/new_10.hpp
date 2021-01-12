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
4DSTfh/dTRJ0iNS0CWljuolTi1YxCgXOh3b0xKRqsebpif9oS3/7wl2fHpHcIsNN35BRrM1spCv/o8DL4QqHfFvsu2J9N6b1vbX96YQGNR3u37wt6hYuN3qkwEfXnfOizOMF3ZjNINWaYWBbGuMHVa8RWp1QgrImnqllJlE84QXqk7MS9TDR61BlUZthRVqNseFslTK5ZtTAMhAHFNuFgn8CJM89Gj2vqYdnmXYEe/IqmrAi
*/