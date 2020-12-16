//
// Copyright 2010 Kenneth Riddile
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/targa/tags.hpp>

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// Read support

template< typename Channel
        , typename ColorSpace
        >
struct targa_read_support : read_support_false
{
    static const targa_depth::type bpp = 0;
};

template<>
struct targa_read_support<uint8_t
                         , rgb_t
                         > : read_support_true
{
    static const targa_depth::type bpp = 24;
};


template<>
struct targa_read_support<uint8_t
                         , rgba_t
                         > : read_support_true
{
    static const targa_depth::type bpp = 32;
};


// Write support

template< typename Channel
        , typename ColorSpace
        >
struct targa_write_support : write_support_false
{};

template<>
struct targa_write_support<uint8_t
                          , rgb_t
                          > : write_support_true {};

template<>
struct targa_write_support<uint8_t
                          , rgba_t
                          > : write_support_true {};

} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel, targa_tag>
    : std::integral_constant
        <
            bool,
            detail::targa_read_support
            <
                typename channel_type<Pixel>::type,
                typename color_space_type<Pixel>::type
            >::is_supported
        >
{
    using parent_t = detail::targa_read_support
        <
            typename channel_type<Pixel>::type,
            typename color_space_type<Pixel>::type
        >;

    static const typename targa_depth::type bpp = parent_t::bpp;
};

template<typename Pixel>
struct is_write_supported<Pixel, targa_tag>
    : std::integral_constant
        <
            bool,
            detail::targa_write_support
            <
                typename channel_type<Pixel>::type,
                typename color_space_type<Pixel>::type
            >::is_supported
        >
{};

}} // namespace boost::gil

#endif

/* supported_types.hpp
pL2Y2P2yNIdK46nG0edkH1K5eMR87s9qTdMvxHQAEWL4NDnKdFYtl/sN358xyN9ArnVgOpGfSxaV2mgqkhgjMoy7iTeupBly0BrU/VjWFQunh4i6T5z3kk9RPvc6SQ1rAlTUwR/dyc7DfDGS4XfyDCq+AXzleEKz9zmOg2wCwZ5TLKkRZ+R6pcIjSaeu6eQfI4L8wHoMX/wK+dc4SB2BjRt7d7dCB/l91ZHes/xSwNQ49ueNKNepabRfUvMVRypHJInSafp1P/5iqlixF2dXnUmVFtHWK5nKn9kbZgr153RQdv/1Hor09f/Oi7FBSVT9lWJNk+tZzz30/giWQUjfitOPfL6ym0LLG3KZYl84Kf3MoAw5/jiVnt5FWWqtS+UJVszy0NEgMU0+JnmY8njU+ZuXds2m0jtCYVfYjUsHOh2GZ0ZxdQWmoVnDFfbPXKhV/BP5Z+W0Rizjull+MdwjbzwP5Ge5+LGAxJylCN9U6RA+NoMhM8TNXkbNQYI2XsmCv/Az9l/H0fREWc5juOdhTVOL8WZcSnpUlTu2VRbp/Vnqe3/kciXq7C0QEnd6dyX00YWev4Cr6MQ3Jr6cVebtgTnGlTdruNwG64UhrB9/vecEM9VHLvaiKfU0f3UtI0EzA10Yv4Dg71xweItMD/nI8vD+iGJmgouaz3NmUwTmNrqDVpTezHMDRabnXgufb9nE51vO0dkWkYMW+UtAWTfS8qAKLt1NLt/XZKrxoUykSjkV5Zt1WfFMzUIgs43e63nf6oPE3k0xlrF/QP6P8C8L4XuwLLYUsqnKoMKb9UXpB9N59NxK99+Oc9+/IW918Z9l391qrT56gqt/oV555wNrOYf1NNorPEVbu071KjqPD1h6cR5+qmGF2kyhbUrrOuWOP605olpu+DEKQ6kkzxKHBJBEH+NlBX0T+BRazA7VO/HnevWOH9PrfY8EVkhsE0CA7gi7poaikb35bGjWITHhFAs0BbjtDBk7DG2SSdgwmXyH01nqVbc6KxsftgxWYIJw5M3aX9m0xHko0TwP8eg/s9HtGG7jxJRQG4myjRPCdZzbaIQ2YgFZ+SYjsYhbZe324dqrw7XbyNpHxe0nuXYzuv9Okds/UcSmEsSp3g3EcHe3r7PJMOW+iH9JI+ZJVzrCQLtNPAS0us/iDn/l/s/HWIhniKUVk6QQqaskwRNw4UkPDr9Djc+5B+B9JHiT08SWCvKq3pzEAxffSf17/dqrURsUpJwMUbC3q0IUzA9R4HnZsGNbi1jVlhg3Kbay/XPhCjV/JWvAJBk6OEJ9TER7juQY4ASA6D1J/4pDjBV7sY94sGPYLz67G1gxHjh6PkKXpwbEw55dTZd+80xGPSAGWWcl2pwznPVoAq9IAvgMIZ3Lsetb9E3I0ssLCGfttAufXXOnN8qF+zpamf1Kkcma66N9al9NhHXBc0jJuxNt+JuMnZbJBmhjO/xdxhNMv1bC9M+YiPV6tXUB3WIgSfpmLVc8rkx1YHIMfff6SBQs65/Nsstcoe9E1tCCIyyJp09RoMwvWsjclTL3ryROZaK0sb2/4DnhL87ccw712eXWnMWgBi88K/xZVngcFbIwK5Q/K+u82FmRn3qx5v5LhilcEvBhwrz6WTlV0fxB4g4W1sj7X4Bx5Pc10d2dk4Cb3RDuFQn38w8huBsJbnBDuGcA57BubEJAgC//gdvOAqyDoniiQ8MK3STid8KIq2hP6ZcJDeCaSbi/huHWENzehnDBavDsoPcmYtM4VHhQUjCGqF0zga5bQveRMe2knLauHZROW5zGSj9GZtNZcaqx4TtZWoUpwWB89WHGaKc+wdAMYArePirvD/fYJ48V/4WGzR8=
*/