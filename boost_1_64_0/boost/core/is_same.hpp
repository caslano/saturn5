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
y17IdY1mQb1Okh2aktsxJF5FX/21AuOw+954k3kk5Q5minNHQ0uyexn5K7oa6yEVWrOiDbSeKFt6CKNbv1lwRMQVKG4dQ6LWqa7f/JmFPpNnhEIk6RELTCVDYeBbokxgyC/rO+ErMcqEmk0IM/WQ5x2L3WSWoglz27+vii7tx31onYVNrr0a4flLcfN8RItfMmSsv8WqATzC3cgc3pWE2jPSbD2pm4ucyzJKb2c+TPkIvu511j7T8mZDBCLI/SyWXQhePCVb1TR9jIjyKsDR2LslnsT1N5qSAB/Mo/2+UpgJLTa5HUxCNxhT420yQf52ZcRtJdIk0PKXXLhKc4/LUdyVEg7JWezhKoDqP8uHAdw/OdP7tL71Tn/nPQ8/TAc6UQzxP1EWv0pz9wB4OZxkKLcvDTRq0mP3jkuMF/x5tcMNNWyT/TrJYrM7rK2elReEVYtsQugzEXRHU4vBrA0xJ20UAZW59k5OFvlA9mJSrZSM4KOBb0OjJJlD23YhVbWYu2w5bhEQWbcmVAvO5o8qMIM2jKOLyLwTM/E+22nGV/1Jkw0CodURWRXvjA==
*/