#ifndef BOOST_CORE_IS_SAME_HPP_INCLUDED
#define BOOST_CORE_IS_SAME_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// is_same<T1,T2>::value is true when T1 == T2
//
// Copyright 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>

namespace boost
{

namespace core
{

template< class T1, class T2 > struct is_same
{
    BOOST_STATIC_CONSTANT( bool, value = false );
};

template< class T > struct is_same< T, T >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

} // namespace core

} // namespace boost

#endif // #ifndef BOOST_CORE_IS_SAME_HPP_INCLUDED

/* is_same.hpp
4nWjpJWaD8XCC8O892bfzrgrG85+2WW5mg5+epXTXeKF6xGUDuJfWqsfA8ryEQ4/BK5wfYWUB0+ox/IUXoV6hJMJVRqta/1clq+QW+ki9Z+nwatSP2LkgDT4mej3A7tvFZzMTuHi/fvf4S28O3937sCcdIxyyBXtKjrcO3DdTJG/WvLw4Er6wQGqgHD3GWHRMglSrNWODBTwmbOadpI2QCQ0VNYDq/CFdaBaCmvGKcySdBnGHx3YtaxuDc9ejCBbMfIGWrKlMNCasu2BpieDArFGBuRvmFTIOSomOhflKSg6bKSh0UUQLgWQLWGcVChHFLRK9fIPz6vHgeNOvEbU0quPVrit2rzY1RKr2ZA9iF6BEjBK6oDOd2AjGrbWK1qEwX6sOJOt81QWCnaNJwaQlHNDh1BG5WELFHLjlqMzocfqmdKLFJ3UartWbJ4loq2GaD0OHcqhLZjXCDTegbFr6DDlT0YcVYzLk+U/ObKn2hsQHVYFtp9DmNtQEcmkA1/D4i5ZFPDVzzI/LpaQ3IIfLw3fpzCeY28wVB2APvQDlVjFAGzTc0abZ+K/dNItt7iD2SKLkrQo58HN4uPcL3y4BPviCv4eO2zsi99ssDmr9MnDlXt55Z5jQL+VlMh9KanSZ4w3tpNExvwOYv9z
*/