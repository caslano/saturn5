//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_STREAM_TRAITS_HPP
#define BOOST_BEAST_DETAIL_STREAM_TRAITS_HPP

#include <boost/beast/core/error.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/type_traits/make_void.hpp>
#include <type_traits>

namespace boost {
namespace beast {
namespace detail {

//------------------------------------------------------------------------------
//
// get_lowest_layer
// lowest_layer_type
// detail::has_next_layer
//

template <class T>
std::false_type has_next_layer_impl(void*);

template <class T>
auto has_next_layer_impl(decltype(nullptr)) ->
    decltype(std::declval<T&>().next_layer(), std::true_type{});

template <class T>
using has_next_layer = decltype(has_next_layer_impl<T>(nullptr));

template<class T, bool = has_next_layer<T>::value>
struct lowest_layer_type_impl
{
    using type = typename std::remove_reference<T>::type;
};

template<class T>
struct lowest_layer_type_impl<T, true>
{
    using type = typename lowest_layer_type_impl<
        decltype(std::declval<T&>().next_layer())>::type;
};

template<class T>
using lowest_layer_type = typename
    lowest_layer_type_impl<T>::type;

template<class T>
T&
get_lowest_layer_impl(
    T& t, std::false_type) noexcept
{
    return t;
}

template<class T>
lowest_layer_type<T>&
get_lowest_layer_impl(
    T& t, std::true_type) noexcept
{
    return get_lowest_layer_impl(t.next_layer(),
        has_next_layer<typename std::decay<
            decltype(t.next_layer())>::type>{});
}

//------------------------------------------------------------------------------

// Types that meet the requirements,
// for use with std::declval only.
template<class BufferType>
struct BufferSequence
{
    using value_type = BufferType;
    using const_iterator = BufferType const*;
    ~BufferSequence() = default;
    BufferSequence(BufferSequence const&) = default;
    const_iterator begin() const noexcept { return {}; }
    const_iterator end() const noexcept { return {}; }
};
using ConstBufferSequence =
    BufferSequence<net::const_buffer>;
using MutableBufferSequence =
    BufferSequence<net::mutable_buffer>;

//

// Types that meet the requirements,
// for use with std::declval only.
struct StreamHandler
{
    StreamHandler(StreamHandler const&) = default;
    void operator()(error_code, std::size_t) {}
};
using ReadHandler = StreamHandler;
using WriteHandler = StreamHandler;

//------------------------------------------------------------------------------

} // detail
} // beast
} // boost

#endif

/* stream_traits.hpp
zXpuT77zd0M91vqW01HP5RndQr8bytePZfbmEU89t3ldj32H8bG6D94r/hnIxeW4lrVeaAaDgwSViP7xEOT8JHSeT3qjf8R37RIcZ0ySdukaEh7UPxrxNYhbAydz5D381watunPr86YtvQeCR64LWvWpE/r5y3jVALTXd/xlTH3aUc7j3vGVM/OhnAf7ypnxZjmPfad1Oe/7jlXOSWgnaf2c5fwZ4gf3a5uc4/tunZwHO8j5K2a4mHKeD5c8EO3MRs7U253bs6SZqJLM7dkk5zRfOTPe0p7Fn4tcnOX8po+cV0CG5yWZ5NzHKudcxK1MopyjWpZz/Q5bJ+c0BznPSfZvz9uloZ29ayPnWa2053d92zPzoZwH+sqZ8Zb2/G4b2jNozHJuhFB+7e/cnlcjrql/29rzeclbJ+eBWs5WvXl1iv8aQZgxNvvKuZ3zEJ70Y/U8xEfi72b6hsBtttdI+lH0W+lRRKEXO/vcm8H86df08j6TB1llI9EFwOBY6OBhWz8P0SVSwvQ7Spa258dy4fn36rtaJ7e05dMH8OxvyjiG7yjqPT8Z58suEGe5Ms0OjvteGG9uS23WlVvbm2J+97hoRyVXInnqZSDaTboDT/mVVRUt8MV0iRI/WNoHEjS3D8b3MvENqTO+RMf3bCvfrdb3YKlvlIF0fFe1ncfPHOi/12QGKrnAVxalR7RUt6Bv314Tllu/f614z/79K3eQ/1rqfmgstT7lY9uzbVvRyksf6zj+PfOe4x4gkemD77W0B4jx3ANk3XvUtrVaysXcZvW+DJQFYUUWucQN9n1/lnoDsVUu1e78iqJix3ojfR/bdflkxrFdYv38r7VL37VzGV+4Vp6X6kk8inwMhwsy5pI9fGCPX76RCfbZlY+EWdeKMuc2yDSjTG1gqRvA8cUuvrBi8Uj2Q5/0wV0Zn0G9szm+A8YklMuvb0pZJCxb76Hj/dE/Dt2ox2frXoOhnDNFZAKwEW4zwlZ65GfcvNWx2XjPeETon6EsvemHO4zVjKeN4t5G/xD/ev8xkO8g90v8IXzmedOn6u/0jmxg/7QZI2OBdwj9m+Iv1en7+/XVXIX3Sol717GvJsq9wiHHbrp8QyRspm955F1ofirkOoT7TcbJfpPksEV4H+qynd9eE5k3pf/mKO8Y0La9QPyGza/d5NnssyywGedLNB1lx/w4fkg7em+jdf/HJLajE9KUXLFw29P9BJoGkUNN5cH5eWPSx+VPnDNn1h6T9pkzNd+91M0NQSLnR6Klzg9W5nk/yjAa8XMk3khQXF2+kM9GE415n49z/0qy9K9HhC/PPWPZv+ZImPc+nCcnj6HDlVwL4OK4nt/F4NvzfWp1eSVGy8KyxS3Mi5E2TbebNPGP4byEf79KlPjR5NebPtFxPiwKmCA0seIv0WkSTH3rYKPS9TeyqRI/iuOUlz7VZh6s7c+hrZ0D87RNKaf+RvKzf5F9o/baMYLtOIRffcclj73y3CFNR0avjhka+uNeTvaVt719I/tvJzvum9BI4Wt97uVTP7upbPTKtPp13/x2xiCMK/KNZ/CYD34r+HbYYfse9vGJn9/21EKnbzw77tvS9tpD2tb2pLcYa19KLtmb3gA+l3IPvvH7bYU8+TsZ7jn+ngC3jr+7Gb97e35/DfpP+Ptj5dkfmYnf+yrZnyrhxsB1Kn8b4/+Z/D0P7gz+vhjuQv6+Du4C/l4L9528Z/PbASCqX+K68j1TvvE3bCQBP+bZWZ/xu87PgVONMgJ3p5/fm3K/PvP2+d60BgNvD+CxQCO/44Cj6Z9Ev7dcdcwnw7dc/K50e35XOoC2oAbz+9KhPMNrGMON/FbANTK/w5lfBPAo5nc=
*/