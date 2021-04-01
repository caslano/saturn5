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
ercXs9eMLoOh7zshA3kZJ4Y1yJsQIM7RKMD3JEqyUKe1DBMqVZH7Ep+XNGVHQOlnQcHMlr6zS6AR3sguO2kGGKaLLKdqIMxupbcsql/drNN8R2x1Q3ER/15pFQNyJ/JPS5Dcy+qmkBBlb/CHtggnpEu+r0VdgyYPplg9NBbzeaHAcuWWHdrzMmaekhvNjGTxyIpggQAonE1yt2b5jAm+Dfq6GHF6+SB3Clmj/qWVDNUodbafkeAzTrrKizhceGSzy34V9y2gUMx0oDvOip4JpbjTD3Ws583StFA1CfbbCmVX5EKOuzrVig5IQJJF9V2XyOkC295on0g/R+pV+RshZQrMiINlgFcBuNzEEF6duzp81PwzFmkEDsnGQfBZqEZD/+nDQebq1cEkVXqB6znAEe4sZrck9Uc3O65jZQn7j6WWC8CQixOv3S8EK1ZIF45YmOrO6oirhVH/eTJlHs8D+wD3+eG6G9fiez/4XsxpY2o3s/Q4boG1zAjGHPbgwnLDf+Q4IguRKDEaQEcyFZrP6S1W+XbbW/TQ7SboIg0g62fmGmRD1Aw387LLKA==
*/