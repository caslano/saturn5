//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_BUFFERS_REF_HPP
#define BOOST_BEAST_DETAIL_BUFFERS_REF_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <iterator>
#include <memory>

namespace boost {
namespace beast {
namespace detail {

// A very lightweight reference to a buffer sequence
template<class BufferSequence>
class buffers_ref
{
    BufferSequence const* buffers_;

public:
    using const_iterator =
        buffers_iterator_type<BufferSequence>;

    using value_type = typename
        std::iterator_traits<const_iterator>::value_type;

    buffers_ref(buffers_ref const&) = default;
    buffers_ref& operator=(buffers_ref const&) = default;

    explicit
    buffers_ref(BufferSequence const& buffers)
        : buffers_(std::addressof(buffers))
    {
    }

    const_iterator
    begin() const
    {
        return net::buffer_sequence_begin(*buffers_);
    }

    const_iterator
    end() const
    {
        return net::buffer_sequence_end(*buffers_);
    }
};

// Return a reference to a buffer sequence
template<class BufferSequence>
buffers_ref<BufferSequence>
make_buffers_ref(BufferSequence const& buffers)
{
    static_assert(
        is_const_buffer_sequence<BufferSequence>::value,
        "BufferSequence type requirements not met");
    return buffers_ref<BufferSequence>(buffers);
}

} // detail
} // beast
} // boost

#endif

/* buffers_ref.hpp
HFJ5+FqdtuHqN7ZDqrOjjernGK6qHZ+pz3HTzKmwTJUdfkxlo1QXeO7qkHw4wscip9PVcJz7OaQU4miHOPIQR729jXrdnql6Ob5U9yKORxGH5/xQewmbrv+OviL56SO7+Cx9ymDr/SlRwrMrwtKnSLsez3Xe18U/NzwKsXZXv1XHsK5qGM9jxbmt+gPwYVtb9ZTteXWTva3aaN+n5jnaqmWOt1RuWFs1L+wtNSG8rbqGMn5J8rcwLAItJRLURT2nDgOPgk7i97OGTb0Aest4Tt1rs6mfgR6zvaJW2XEvNmij/YCqdNjUtaCbHAfUzDCbmgXy7N+7Q+p0hIpj+T+VvCeqFuZ9IaDekg9DHZB8XI2Q76kPQLuN99SdtsNquf0LVe74Qt8l8bWEt1tlN0Rkx/J0Fv/7VT/W/6/FnhluRx9+FPW211iOMhxS19uvVzNRX1PD1qnezOvPJA9XhdnVcnAeUk+Dd4PtY3WdfZ0qBW8b5rVe4szWepAHJNzDYRPUfCPMVmW8Yr/ViJM48bc6y/Q7ZHf73WS00neDOPV3lS3xZUVYyiT93RTWd774Xx7hru8X1TfAKGO3OoC/9p8Bd+Cvym9tu9U6e4zabH8G8opRKx2vQpoxqiLsVTUxPEYVhD+vRkW01feoJEucv4lIV5dErI5opccfMaY7uOIok4Vif0PX1zVs1wVS5h7hbvdwOT14BL8/x+8tKP1zhh2yDlcrMBa7z2ZXD2D0VmCPQ33a1Q32lirbEYd82pXL0VKNDItDXu2qMKylvpfol9JuIvi33GKnXFexHfTmubz5kp9rwsLVO+pjUL3xjvqp7V0cKPtEzXd8Ym0vg6yyjXV/SxEJkOkgtVdFQqaJxuPqKPDvwBcg23dtj6ufQbZP2B9XyyHb9Y5nVElYDHqmF9R0yLYsfJ8aFxGj4tjmiiWvsymzVnp8c4Gk9Sbd8Q3ym+greT9Hy/JZlaBlea+RoGW5xJagZZljT1BLIcvrIcsRjm6qGLKcC1kOCOuGNm1XM0xZsn1WSn5Qx5RVluSjrerNb+o8SX+an+zeQbtvULN8ZOdKlcEEZbdCwi0NM9tlT/Wk+gxoGE+q30J2fwButsWgH3pG3QjZ3Wt/RVVBdrc6XlFFYTH6+9wuebkvLFK1VNNUpbEffXu0rcK4GX36y/abDbPP6se2uEHS2xzWQkWpLFVhPAdem63auB793Av224188Hr6mVqJ9wrUa6RKVfXhvSXPnm+1wK+sh9RKtJMKlFXqUH+3d9jD1U6j3thnxLPd6fDi/mtjpf0t40x7fdvwXpikcJ619L3Lp3iRn14oeibIuOjTew6lHH7ytj99/acDGw9Vz3XrhVbrOZPMI8UMBC01Hbhftzv1Q2m8fyWd+4J/RPvdtNfx/pWd3C/8EfAc4KfUJ31JPVI7A3kHdgD2AHYC9gReAOwFLAf2AV7Ls5v/4NlNw+bWMzmA/YERwAHAjsCBwC7Ac4FdganATOAg4EzgEOBSYBrwPuB0YB1wmJlf4PlmeLvb3gNo2lOBFwDTgCOAtwBHAtcBM81yA0cBfwocDdwMHAP8HDgWeBx4CTDD4b7/ZhJwInAycBJwLzAb+BpwOvdR1yqOcziuUtzjv4oNYAbveyk2EUyzgH8Gzga+inKUAB9BuqXA1Yh3DrAc9ToXeDXaSxlwIuItB14GnA9cCawA1gKrzHIBFwKfBy7226e9F/q0oyGdWsiETMiETMiETMiETMiETMiETMj8n5gfWP9fMq+gUP4R9f/3oP+Px0JJP+pdTtn1m76qO/HeFOg30kTvknXpqNGii38/RnTMC51584osen/yjdT66y/F/raaynuSw6Ob6F4YJkM=
*/