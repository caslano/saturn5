// Boost.Assign library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/assign/
//


#ifndef BOOST_ASSIGN_STD_SET_HPP
#define BOOST_ASSIGN_STD_SET_HPP

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/assign/list_inserter.hpp>
#include <boost/config.hpp>
#include <boost/move/utility.hpp>
#include <set>

namespace boost
{
namespace assign
{

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

    template< class K, class C, class A, class K2 >
    inline list_inserter< assign_detail::call_insert< std::set<K,C,A> >, K > 
    operator+=( std::set<K,C,A>& c, K2 k )
    {
        return insert( c )( k );
    }
    
    template< class K, class C, class A, class K2 >
    inline list_inserter< assign_detail::call_insert< std::multiset<K,C,A> >, K > 
    operator+=( std::multiset<K,C,A>& c, K2 k )
    {
        return insert( c )( k );
    }

#else

    template< class K, class C, class A, class K2 >
    inline list_inserter< assign_detail::call_insert< std::set<K, C, A> >, K >
    operator+=(std::set<K, C, A>& c, K2&& k)
    {
        return insert(c)(boost::forward<K2>(k));
    }

    template< class K, class C, class A, class K2 >
    inline list_inserter< assign_detail::call_insert< std::multiset<K, C, A> >, K >
    operator+=(std::multiset<K, C, A>& c, K2&& k)
    {
        return insert(c)(boost::forward<K2>(k));
    }

#endif
}
}

#endif

/* set.hpp
wnQrLovXMaiua8jGOH2MSdmaElu34pjBR+XF1iemcbNj6g5T/5h6wtQ/6pzbLCda/NL8efkl3jqrYbx7t9t5KzctGzbbE1bnze3aiEFZgXLPNXrE3Nu86tzGxCj6hqZGmRcpijJ/UmrDyX1F6CUqraITcYMKxu/w8w4EX4B+ynBqTWU4pWTmjF4xy1Hjj7TzZqvF/pLaHdP1Q9feMlY5a/wCtSPbLPYmkeVu5QsfEP/lfq0H3vjYbfzIemH7t0rxv8EflCe86j3XfrzWm2B6Oba/WiH2+62MUTu5n4PUP3h/zSPrmZURekTiX+kPyh/dIPYu4ToSPXUrxam+HnrDZuJm+3HtD4P3dYWE8zkR123T6h+RVlvc0kJpUeaansotvSZhT/en6X10e1/mWllVtM7Ku63Sshe7zZt29pw5EefMknNqfy7PLun3xC/PRH+GpGJ7S9LwW52n74j9KP9FvpXqxuzqB67bYjPUNPPq8LP1bpRc/zX22btcwmfbemhcO3EzxN8xy8T+oEkkzELcQ3OzBaJLyMpfSX163Sd2T/1I84SXu/TMa38vcTr6xG7Lqovn/gtL5P51nvt3cr9jnIBdwkfIf+i4Qcch8yT9h30H02cl41va3O5hL+ZC1ds6Re0DswImP0WM9G+VNTzXlnmea8kfhj/Xdkbp+/ZF6fuMU7XvS3Sq9n0pTtW+L9OGK7Xh2tpnn9RleU5mWTet4+qeZ5+Jth6GPQM3Jes8nz4DB2Pi3XVoH6XE1KupPWisvlPjDo7ZN6p/zGeg+sd8Bqp/FB2Ytu/RMFbfZcznZXZE2KXVPC/7R4Rd5nle5ujzcmLs5+Wvop9PZQuq1KNlUZ6hI7QOPKnyzp/HyfytWQcTqAOVNdcBfYpGe44OkXFAm4+lv4rTuqFpnqV1xTG9xb9eZF2x/XNz8T8/TuuONz72YPwmseqShs+zfZKR8NfGRdQtq/+1qfhPiVtnyv1a3zSNQpOhci3vfOra/0Q9SzdzTZeq9VCfVV9IvCVx7yMrLTIuNu6TNq63zlZ66hbXHu3ZK+05Xq7xurjgs/djiZcVqtMRaU10qq/T3rBToz17dYzSQc67MC74rGws9n/62tAH22dhRHpF1Tx/c+BgSePkUJrbXHuc09S8bp+/30t6o+w150acozR0f/Iccm+whT7/Tpf0v0Fmu76Z6c8yt/t7VtEBO3dOoaqA5Vq1zLOlnD4xvzcDrP7oNz/VZ56Wi5H35MICnpT2mbRLzveck6Z1Zesnrv0Rp9jpEvO5P0zi+K3+2uFi7xqX4P/eZIgbNVjOPdDpaTqY702XcB3p2jZ6SN5d7qwwY+y73jkSr4O2l+D1NI2VbtXnv74vJ8g1/S4umi7gNL2POyWtufQh3U1GRB7x9Akbx30u6W03wXaxV659le8RM8s53tclUn+wzd83JV5z00LH5WliPy+ukNLd4880A+I6mjQdE98tfjv9T/v9kbqC7Tj4S6lHKzz3RW3Q+wqOSy6X+0pVebxgno12epl2kmeReozTVG9xdwm33axRWcTZtg51kWscSIwW2+T6/X38pGPHjKVF+WVFnnUR3rGkUZ3jAd24byQzpEuzemhHx9JD+6nkRUAX73LCb8GoHtqJVg+tptc3PZjekkWx0suS+2go6W0jrez0YHpLLrZ6fTW95emqg7fekueTfYnJvhQTUw/vyZJuaxNPfrvx+xP3KsyQiPiR59gQvOa4JRuT/ehUrm/k2q7H/cXgtfmXbLV6UTXeUBrJs4F4K5L9icn+esnx8dy0mxebiJfTxObFfbHy4kRPXuwhzsAmNi8el/OpOYyxQkM7TpVxKcaOS2W82r1FaPyaH6ELeGc=
*/