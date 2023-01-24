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
if5NiX5NCX7wNtG3Mc4HybsxzqsxxhMqDty6N0a7NUZBNUS6NkS4NIQ7NYS/IG7DHOvD7OtD7epDbetDgGyggqzqgyzrAy2FgRbCAAuhv6nQ30ToZyr0MxH6Gtd5GyIZ1Hnp13npEfIEt8/rvJ7VeuhAUXaNzLzkhY6ZhiZgnRkVmRIclAhCtj/Ixn3TwsOLAOvkpG5kXZ2XUAvXc3Xeh+PSWQOspeS1dIF1Q4wbU+5icvuAol0p1Ue51Ec6Ewp3qo94ARUOBAhiOQCUwlA7YYitMNhGGGwNFWQlhBwtIccAi7oA8zp/kzp/0zo/Eygf4zofozofw1pvAyT9Ws/ntR7P4K0nRClw166F22JoC9y0oFyfClyANAm5PhG4atY6P6l1fVLnoil01RS6aeXbPjW4q+5l55QVE50aHJwY6C9inc5izcTNTZzCLTa1GNl1t7Gu6BJr+MXShL9tulgvQCCQ4LEZlJ8pQ74mNBlDQViGUN6GtV4GtZ4Alh6UO0BGyl1X4KZd66Zb66YjcNUWuGoJXLQEzk8FTpoC5ydQTo8FLx4JXoDbxzUOGjUO6vDWXr3G/oFIdndr7O/X2AE9gLe26Nj+HpTtXYH9PYHDA4GjOlCWhYbOzTseti+yAevQEMKu/fxA+MZ2HeRgkxfnX54RRuKmQZfAmoWbYl3NZs2slNJX84lfjw9XxblYt3KxftMm61zL+x+W1QOk
*/