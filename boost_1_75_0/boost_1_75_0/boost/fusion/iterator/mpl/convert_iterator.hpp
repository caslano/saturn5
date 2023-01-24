/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_ITERATOR_05062005_1218)
#define FUSION_CONVERT_ITERATOR_05062005_1218

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/is_iterator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    template <typename Iterator>
    struct mpl_iterator; // forward declaration

    //  Test T. If it is a fusion iterator, return a reference to it.
    //  else, assume it is an mpl iterator.

    template <typename T>
    struct convert_iterator
    {
        typedef typename
            mpl::if_<
                is_fusion_iterator<T>
              , T
              , mpl_iterator<T>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static T const&
        call(T const& x, mpl::true_)
        {
            return x;
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static mpl_iterator<T>
        call(T const& /*x*/, mpl::false_)
        {
            return mpl_iterator<T>();
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename
            mpl::if_<
                is_fusion_iterator<T>
              , T const&
              , mpl_iterator<T>
            >::type
        call(T const& x)
        {
            return call(x, is_fusion_iterator<T>());
        }
    };
}}

#endif

/* convert_iterator.hpp
GU4ssB0dDy5Gdro+C/9GF+iYrbBs83er71tJ895ds33zNe4uUbdjSt6yvrlTsCLlgHp9p6qGKXjnfZ8y3Z6/G1mj+hTVENimNcpWYNrhKcCRdTaceprZsLHlxdzwDP839JtV6qMZBhMcPCl43q3Uqh3ESYMphv/bn2GCCp6RafAMFjRwp/zgj8QoVM2W83WCkCErtwDnm5wj526X1qPaH50rMnWiL/zKbMqvjd7lhhLu3O06eZRpaaoMXVNU6Nz9ygEULZrO8I4usC0Dt/Ezk+2oD/Gh+ekWOz6XySTJ1l9h+srY9UuQHPEmRfVoP/YbAIF/Bxwk31F3IRNX836tduEbLNginO9PI28rwkxJbtiH0LF0lh2kNmq++oSFRrUvbS6FU3PQmazPaRrfpHAKjI9o2L1RbFggO1Ek6XL/mB1LjHKWEjv7cApug555YC/HAGqkFSZsyZ1iD4yDGVDgVebaI9M09rfc74KtXG2j82Atz7i1X1GLro1M1tyO2mVpcOPNh2l4oHmwZIE7ZE/Bo0yqK+I0u8IpsOmkYVaLV07xtCrhZhcneKAye5hXfzntdJHq3783tvWOaIJI5ViNc391Hjuw34BtWdhIc3939e7gYF2Iyjt1uRClpqaYTBu71v9XH3rLTszjrOQ5Zb0vz3Ff3lKx1xYp76p1W5Aok/NknkEww9Sna7H4tEz14H/oDCCHF4C8MQ34S1Ku
*/