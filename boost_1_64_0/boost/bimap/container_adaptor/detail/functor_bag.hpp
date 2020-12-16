// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/detail/functor_bag.hpp
/// \brief Defines a EBO optimizacion helper for functors.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_FUNCTOR_BAG_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_FUNCTOR_BAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#if defined(BOOST_MSVC)
// This bogus warning will appear when add_const is applied to a
// const volatile reference because we can't detect const volatile
// references with MSVC6.
#   pragma warning(push)
#   pragma warning(disable:4181)
// warning C4181: qualifier applied to reference type ignored
#endif

#include <boost/mpl/placeholders.hpp>

#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/inherit.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {
namespace detail {

/// \brief EBO optimizacion helper for functors
/**

This class is a generalization of a helper class explained in an article by
Nathan C. Myers.\n
See it at \link http://www.cantrip.org/emptyopt.html
                                                                                    **/

template < class Data, class FunctorList >
struct data_with_functor_bag :

    public mpl::inherit_linearly<

        FunctorList,
        mpl::if_< is_base_of< mpl::_2, mpl::_1 >,
        //   {
                 mpl::_1,
        //   }
        //   else
        //   {
                 mpl::inherit< mpl::_1, mpl::_2 >
        //   }
        >

    >::type
{
    Data data;

    data_with_functor_bag() {}

    data_with_functor_bag(BOOST_DEDUCED_TYPENAME add_reference<Data>::type d)
        : data(d) {}

    template< class Functor >
    Functor& functor()
    {
        return *(static_cast<Functor*>(this));
    }

    template< class Functor >
    const Functor& functor() const
    {
        return *(static_cast<Functor const *>(this));
    }
};

} // namespace detail
} // namespace container_adaptor
} // namespace bimaps
} // namespace boost

#if defined(BOOST_MSVC)
#   pragma warning(pop)
#endif

#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_DETAIL_FUNCTOR_BAG_HPP



/* functor_bag.hpp
va98A+u5NmQt13rWcf3O13CdURp5Fo9skS2yRbbIFtkiW2SLbJHt+74dpff/gsIy0wHwtd7/ve/vRxIte77JsiZalwLpimxAcr1r7+2pa/6/5TqXP9by79fXuL3jSIqNe7XG6Neey5/t0T6OufyFxn1j2Ln88fjNMjorjLvYjqNn+LH5GneZZ/R+ZtyT7P2ODTufv6/y5Jj7b9LVvps5xszS0lkzZ8+xbP3UEP1l0m/iS9OsPJY/DLUB4NRfiTtkXVx7PkqZ8qzx+Wwan68xnpeY8PMphekxx+D/S85zk06MbaHA/sFvTyefbNDc/0zLdbNt/r22J3hcYr7LvP9i3JzXWmMMy8LM+6+qY95/dci8f+Ix5UdZ42eXtfGnnLSepMr0e2aDcI7pg9r8xAntHrr+2ZVbt1332XE9bsgJP+bNvS8o/JhJ976sb24s5f+KDcLGjqX80Ky9pTYLt0naIKWONV0QKwWeBAfAUfAEOA6mwTyYDq+AQ+AqeCJcA4fCW+HJ8C44DG6Ap8Ccr2jD77seV/Btjin4quMJ/lvHEhzNcQTVkT7LyBbZIltki2yR7SttR+n9f+bCeQO/9vu/9/v+SQm8FzBpI8p8358yfhyGUBbkVVT4v/9XdeKZ1h+eg9l6Xv6zCxfnzayssnoSflcSz8ZP1gq3Y+miOA764zAdBwu9+5v4ZyVYHCA4TPvax1/pD8+pnFVaMtt/eHP82xLYvVa4otAYhYOJPFdr3YAWPH4Z6nwdg2zl/Tpzl/o4nJkoqahrjfPTvBHGk4ad7L/blEHpfN5M2U1rsuuYS8McM0fHdCacfRt8zMyngo/pXEt9WBO9wCMdxGzvWA8dUye7qLyw0PQhHJds+lZKznP0IVxgdPsH1lc37ni5PdbPjdujMRwcp6MR5kr68tA9fB7s9R44Lu/t5rhB6U/VXIwE7dQJGY/utuD0n1dYkWrSP86RfqVXugkm/OVehLNegqXwbPfwhf7wnEB4vevcx2qd+3GBvNhr3RMvfhxXfgkBP46lPKuerG3qXk/2B+eZU93wOrLyifB1pG8z3w6TkPZINjKBPBwOPt68wkWWXUeskDoS97zqCHUgCv+/k6oZOv+pYdMXnI7c5r6A83W+c5GJ3rr6fFA6FnKua9XVWKXjYqM7jPfs1jr//v17yIaEsYejc+8PI5XqC/yRcZ/Ke3hzh/5Ce175EhM+kSN4VD/8cSQq73b9r6vujwpX99vhlwE5Ln7lxp0pNzqmvAaovLapgtyl8roeyfGet0B5Eek8R79sxeKyQrtfVno9fLbQzLH9NmkKzlvIDioj6SXaZdD6BZ9Nnwz+B+IusPtiO1rQ6HRTXyxxqJw1Fz2ojU6yw483aclS/2ilX8/E7LS9Kn31j+a4rOli972G6ObibhWow3a96W/Sm2d1QKuLdXrMDI59iIb3ure/dH7rvs2j2ninsrhe46KsiTGx2ie6BXWffdp0nGqve3O1dPz14zDhHyQ2vH74+kzNuTN+GbZdVXOejF+mrWfOg/HLUj+sv27Fa42WSvmpXI1urnPtlpB2ub8N/7QuUA84Gp7pvQa/YNezCwrLS4rongxX16SbZc5Bfvi6Jr0Ue42dQz63bMz59QP9/sX2Psn2ujsHjHuI7ImqDhlTWwG7v61f9NkPVf1THNmWjuOsd7bNiolmnwed9VD76TtAXfUwRHeZXVbBffqdYDNznLYetRW2AmN7Qu3UWX9t+6jRZp82nlbKM18GjD51RXlSPI48xcBLzH5NrFi12yMmja8zD7KJ2jKhu302J5Ko49up3xmtfe2iebMmF8e3HqvG4do2wj5T/N4c9wdyB45h2pKOM6O12lLn6g0=
*/