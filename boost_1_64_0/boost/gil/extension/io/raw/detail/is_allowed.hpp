//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/raw/tags.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< raw_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    using pixel_t = typename get_pixel_type<View>::type;
    using num_channel_t = typename num_channels<pixel_t>::value_type;
    using channel_t = typename channel_traits<typename element_type<typename View::value_type>::type>::value_type;

    constexpr num_channel_t dst_samples_per_pixel = num_channels<pixel_t>::value;
    constexpr unsigned int dst_bits_per_pixel = detail::unsigned_integral_num_bits<channel_t>::value;
    constexpr bool is_type_signed = std::is_signed<channel_t>::value;

    return (dst_samples_per_pixel == info._samples_per_pixel &&
            dst_bits_per_pixel == static_cast<unsigned int>(info._bits_per_pixel) &&
            !is_type_signed);
}

template< typename View >
bool is_allowed( const image_read_info< raw_tag >& /* info */
               , std::false_type  // is read_and_convert
               )
{
    return true;
}

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* is_allowed.hpp
S5IDtq2nuoZrjH92MhvstY4zrAJs8k73On2d/haSAWepXc3ZWGvc2TlKBluxvAE9JffV1SB0+ZL9IqM3Oedp/LD9zzNVWqwW5pxI6DiNHPUgt/bH4VOtC93pUofeOgfp79y4arocSkvnl2xFOrv59PP0m8xvGp0Qzvmcn9CLTAwkI+RzA1nd1D2qbocN3mZ9p5KhI9jWu+11BSLBVhAydrrH587OnAvdvpwdaO4eSyLsJzvIJ2jWV43QBu+1COEUdL+HvR9tDd2zOrvRzT46TrJ2eFNnSJ5xHZuU91M1HEvo4EVqDtQPFaffx9dWU7QM7eybn9KvkzLPSUKI7c9hf7IolpeuUYtOe53dMYRYHvMY8hLLi/Wf4FmsQ2LsfMt+l2O9/a9w7NMJ6v5in08I1ycHSm8PKOb+/K8q9Dqdjn7kNVHCembxYK/z9xKBsCT4ZAgRJGQjBGd6eULwnZB4i7d4i7d4i7c/1S4pKw4Whw6sLi4qJ349Up3eF2IsvmplscLeuZGw3t65k08x4VaxuZh5WU2+8FC+8w0hTO2fsD9+7TE4hJ7nem+SPfYFfoZ9c2NffroESqJ9uqQamert+dNf60tcv5YfMZqfMIAvU3VoNFy9my9VX80b/7JAZfH5JjX2x/LP+tlTD1FP0ct4VqkB7iP+5QdVWGR/F1esXCBH4L2Xa0fD+epyku37dfme6erR3uWLLS+iPoO/sKtCCN+VU4dYQq5A/9343tXEKu8P1t+WaNh6Rwi764mXr1ezMiRWz8ZXFddOlK9oc7x4LA9/ubM8QUsxBt/nHvt6mpxFLX5qtdPDfp926gI+Cd+o6VZ+8/ZoeFyt3xb+9YfyCGfyqerljYZD7fVThsViLz7OcP6K+V/PJyoxWTxULhqilULox1cuyjdt3VtMkc6XbcynE68fJkeR/CGf6Sv7fQf1OrdaGzVvvcvLqUyPhsVXm299zp/Ih+FL7uD7FdqoLlJM8tIMfqrYYIj48gZzW2gKH+n+aOifn783ORLeqmDNk8WxagXT+FBfR/laxjWrQTSU/Vjeoru1XSsunK6es6qYZ0QkPMjfTRDHvXGT+RILL/penDvXc4mtDl/P1+YP3iVXcl1ZPuIKse2dPk++9pGRKYv5/OadmxjOvDESlkwWN7wUwij9dNonbntYna04se18siEuu3kvP72Iz2413spqHcVPF7wsd+Rz394qRyXW2dHJdxiq8hNzm3/XvGkNh/Jvh/J5c3YRJ5vrxKP55MiLPMiPEberRSwnjlf7G5rwwU+2VufJcz3Bb1R3VmYq3/3yaGgmhm99m5i0l3X2HYgitSJh2+389BryL3y29NvV6vEBq3wWDWVqqUUd53ZkpPRQNdsp9CNHJFQ9QU0/3zLPWeqzGsuptYqGnO4/V8xe7BLyaW2KmcNzV4rRFZZ8nxQNN5mvdv3E06fIx+UlM9Y+qYRraosbZpJHuarzD5UHGU6X36SP7tNLzDZK/N2WTObrZB33uk9dsSwZrtFKfOz67TWsez75Kzq+p6Zc01eR0L6BHEUlNaRvRUOuJLmTQiHk1k/zvurf5fT2tRHnFPG3ifSxJn0sqOZebiHjbM+6Ur6sIDvCF00tRC8b0Rd/35qijm0Mn3uhvEgP8edS4zDvE/EIEl6kk9bp5svVRPYRn+cnW1eGsGq32F1/td6VS6JXgbxf8VAIlaqJiZ8L4XU5sfxd6G8Zvjwf+SS5jsLyl3Pl9Gr73L735Z3GR3/+jtP9sXVPyez3USzFW/gYn2AR3sAyrMBqZCCxFJnBkSiG2HeAinotjhRzMWVaJHyxk1xM94zPm8/1rulqHdLEU6PITXHfZ6ji+xsJsZpkORA=
*/