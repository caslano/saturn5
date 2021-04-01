#ifndef BOOST_MP11_MPL_TUPLE_HPP_INCLUDED
#define BOOST_MP11_MPL_TUPLE_HPP_INCLUDED

// Copyright 2017, 2019 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/detail/mpl_common.hpp>
#include <tuple>

namespace boost
{
namespace mpl
{

template< typename Sequence > struct sequence_tag;

template<class... T> struct sequence_tag<std::tuple<T...>>
{
    using type = aux::mp11_tag;
};

} // namespace mpl
} // namespace boost

#endif // #ifndef BOOST_MP11_MPL_TUPLE_HPP_INCLUDED

/* mpl_tuple.hpp
vG2Yc18+1LYY9nGECaQqPCZxwwN/AKWwLCqoHQ5vFT83CGLefNyl1vjrKLqFQsmAEf9EtIRxXvWPW5/KtRjLYJ/ZR9xB3W3IEZTbBkxIHJVjdcg3DbWkFkhPJ7/Bjg+KEEm05yNRIIjuNMvvzMJOri+55fspAo4B2/h+9GuBwNElcthUAzI9caAJUHyjwxB0uwMFXPuwZLn8BwOmlJk09ybOU1RrMi/1jy4nkOisGiT20I8CfRsRldnuTlMaPKC/Epgi0pFccuAjqpMAL7IUFHWSOhVcRyh5aErsVdUPSydIE43xr34KFDLTkIiZ1G8w4vUiWV3UvojQfPxlmWwmyS+BpsmfkOPhpGUDtbQlgrpZ1ZwU3nlu2tAjlO+ZsfL6I4JXz1Qc0fAhzWdzbHO2Z7XmeTfXZUVGSjjiY4bHwhxpAKaQ5XkIgS8pUpmDGQ9AFJwQvhAsbUxKdftis3gmaat+3rh5iB1j3dG7vsG22NKcontdgFhrS2se1LnCSbPvp/cLJTpWMJc/rHiks7sFVSpkR3Od26cXCfBvChId0czGCq+IWqMfq9LafQ==
*/