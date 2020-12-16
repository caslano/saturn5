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
F6A5GLyY0g6CwYvJ74BssHy3JJ8MZkMVQHMx+AZlxCLfoJyo9eWz4t+rMWnKt/lXunx1AYnweiCLXOAQS+EHLW0l3h+kzIfCx4U2OEIu/oBgHLwSeIfGyiiHKMohUXpRr4ZESfo/Q2IdCiWX8JAofUMyk2vMcbAOiTJwHHYGjsfOwPHYOQiV/96a+tp+xn73Xc+o+t1rrGibKyfQTXr9iSbmSh9fJ7HxOHUESvKe9UMXGxTtg03H4SSjHwx3+iP9//hRHJPf+3/+Svl9J6uTM8Ge/a1L9nvunWdV/vSYaA0mDjN1rgE5/0Hrkh947i23iu2QdibkQc6yjh4cHmSp9cgwIUusW4YJGbCuGSak16q2QQ5erJ2qTKs7PYlDDDPWwKTv+I9cvWHuX/g+ykPuuJ2hpgQNM3I2DmMjZIp+DejGbpyG2j/DPnEgmzi94wlsBByTxUxMkk4KlOB6QzIh00eWcULB7Bf2N7rLQkdRS2CssU9tKvrqrAuB+NXr/5vx6IWDnB+h6zr/DSeBeD6TsumZtzkD/TPaLsE/SJSOAbi9iK9zJ1eQXM8Z1yHjeopcU8i1j1yzyPUIuU4nVzu5ziDX18lVRq6t5JpNrs+Raw65NpLr9eT6FLneQJxazREz1zHOzMflX1T+XSn/LpV/9fLvQvl3nvyrpP3JCnHPlX9z5N+p8m+q/Ctpb+AVVvu7WO7afh39cyMycXjjhVXOQD2e9+P5MJ4GPI14bsCzCc/n8dyF5xt4HsTzPTw/wnMAz8/xHMaTxtON50U8x/AUgMNVeHx4TsJTgmcqnlPxzMEzF08FnvPxhPE4SvXPaVwut0e5Coxf4QjvyKJRvtFj/IGx2m+cCT0pqF3j+V2M52QTWmJcE06ZOGnyFHJN3fff+6P6fBvf//dUrv4IaajpXftN8/h+jRb9uYA/b0k03uKI+bKG/TJTotdHgs9Akr0ALyteyg1Mwp22u+gXuZR1q9s41jiladBC/nxi6Dbq1Q9BYY5OMdmMLIwEWdxHnGW9dRrphqyhqKE1SdZJSDRCYX9EepebcNq23SdM4x7EZmRrnZhW9RbIMfdfdx1TZ3NL+Sgr8sCnNprkWOt5U+U07Wp92nsno72lVKPds4Z8HEzCbY5YNVs4bZBgvrQFwXKSluFg4oQarHDq03DphH45RRIqloSaOstdbEf2h6xKMdCarZyMT5+umdSRy6QF1gTQkOST5RSZHcm1HbzJRG7i1mdcxC3bWZ3M1Cy3OnK5JaeJ7v9xllv3DOTWBJWJWpfiVjujjU7Ncqt9ILdCU7Pcatfcalfcah+UWzsmS0KWM4dbKx4bnFuLhVuJxg1kbgz2TC2nSZNr31wXZXYrZdbaN1kNOlsSjVscjQXpBJ+zaglbX5+irRyYo/xskbalzvqJRGJzwL5xsUK8p8UXa4tEsIarTTxucddvSdZvgzVUd2ibuluwZrOb/rYla7bBaqu7fpu2WbLRjT+AhbZl3tFas8UWfh2Hb3GHNks4jLcSghTjq9/srt8IMFs6jK9mm7tmI5BIrvFZ0UJ8W1Ua+eXAsqyZJCxuxifIJsuUdiuas0PcwGmKcdilbUIqkz5RB3iCWrMubKWYLyWoMC4Y/qlM1Wyvtd7Jft5ogPeTFsqXjP/zIxlDyUJNyfcmMiWIHdoetsbq2Kwx5ZYvbWe7b/8JSd5r/2E8iJzjVPzX/T3VkDr9MZc+rBYuEAWxpwme/NMX7VOMV77szG5f8y50K3qAOOhgu1tO0kHACdGoI+rWqR/g3mT5BE4diwcyH7h6ZiSqSY4sJtdM0ftPMVgQs7DfUhLVp3iURndyLSWRk1z8dZFlTlPvNIZ3GAxbJXd11uQ=
*/