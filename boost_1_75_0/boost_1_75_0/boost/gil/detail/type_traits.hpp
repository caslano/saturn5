//
// Copyright 2017-2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DETAIL_TYPE_TRAITS_HPP
#define BOOST_GIL_DETAIL_TYPE_TRAITS_HPP

#include <boost/config.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

#if defined(BOOST_LIBSTDCXX_VERSION) && BOOST_LIBSTDCXX_VERSION < 50100

template<class T>
struct is_trivially_default_constructible
    : std::integral_constant
    <
        bool,
        std::is_default_constructible<T>::value &&
        std::has_trivial_default_constructor<T>::value
    >
{};

#else

using std::is_trivially_default_constructible;

#endif

using std::is_trivially_destructible;

}}} //namespace boost::gil::detail

#endif

/* type_traits.hpp
4IgI8zekp98GqxJ/nflgMR6hLvryokSaMyDnAf3wy50XiR521aPpvJaqZgi6MLXQj3OvztVVZmPxZdsTm9AUTPpW54ePPGN9LD1ObNH1XNzTieJBqUaaLcPPRqgZJKhQzjDNkj+l6V7m+OHTtjERswS1jQe6iwoJB42gipbr4vEdAtj2wjwl9NyCMLJ6H2EwRW6fq2Fg4Gf3CDNT8d1zyXjkS6rjjH78hYJu7iHNFUDNAWR/SGDrxDTOtunqz+esrvdMgHB9bs6rgjZtIIPgqn0ru+1yg4AW5eifSeN8G6U0b20jLjUnq3n5Eysia5JNRrNYf2ryUUBaeZalHH73ZY7u0R4TpXnW+MnsmOyG4q5/E/igOqiuzL/5nRuR6N42hz2Y0de5/VHRqam7XsDV0oAfZdOnvx6v0hhgkZnUfXButHuj4JWVFqd+s7ka4+SixxhEoaw7gXERIIM4i+9LGxo4QnwCPb1Qy20iJHSsto9zArcklr/I+UodjqDD1ZU18ni/3KRW4jksWsCWeWtDj8aGhocq2E5o1pdg+ym6zSvDfRJCUCnsXs6an5v5dfYvvuo/Wc2kuXgSL7v6Zw7F9LT1Ui7RVaXxLE9nsazOnRvF/5zErlB+B6Nvft/ULc+aKO5J3SfKFDc7dkOkrMNhzAiqfP2XlRGT/qZd9UdfQaMjqEjeHOFsPIUc3/FZiiLd7JX2X6+cXaD47oqc
*/