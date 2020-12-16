//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_BIT_ALIGNED_TYPE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_BIT_ALIGNED_TYPE_HPP

#include <boost/gil/bit_aligned_pixel_reference.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_bit_aligned metafunctions
/// \brief Determines whether the given type is bit_aligned.

template< typename PixelRef >
struct is_bit_aligned : std::false_type {};

template <typename B, typename C, typename L, bool M>
struct is_bit_aligned<bit_aligned_pixel_reference<B, C, L, M>> : std::true_type {};

template <typename B, typename C, typename L, bool M>
struct is_bit_aligned<bit_aligned_pixel_reference<B, C, L, M> const> : std::true_type {};

template <typename B, typename C, typename L>
struct is_bit_aligned<packed_pixel<B, C, L>> : std::true_type {};

template <typename B, typename C, typename L>
struct is_bit_aligned<packed_pixel<B, C, L> const> : std::true_type {};

}} // namespace boost::gil

#endif

/* is_bit_aligned.hpp
YnXfXGwfuGVNxHLORf8BpGBD2npm10r5Bi/kAe5KVZ5Tc4cepT8DkK/gw/EKHo8X8AS8gMsefvH9m+oZqjKtnFmrPWRp+YbkypIM+KeLFnr/HCkdNC9jCaNhun1yj+KRI3RXvAc8K0mF2bVyxsdEjI2hlqUhQr11004OKmHu5jzr2qXQH8Ut8Ef8+Gp17Rvju0m2v67ts4+iq/2gcVf3Jaa2WeN7NCfg8j00MRDpqEY94mcoB5EdCXvymRiAmYq4HxHfj9EZ7J7hdwSXAP9f8gX/tfmCf1CMb2w5/nzXaLSVJm3ApJcjKTQ+TtxNcUDyuzjxlkjbIfRHwJ9s+SPhr2/5XfC/7FB/NZxHUpXKTOMEDUwSLkUYpsWYSIGmCGCxXjRDv9MlFzex+nrVylNNCiaPkzXM1KHASnwdD/2oC9EWublrBBT/id1SEQ/yun8B8vpOqcS3OXEUvJqHkEvCJ5EWkKM9vTUCVF945j4PTzw879MTDU8XYMKu0ECmvpsr/dwF6qWtOp1+lyGOOTkf7XxXGg7lToCaEbSbIA8JtNVRTG3Y1b+pxr4ihrUG5nhMWbGTC/+8xQDGMEG1r8L53YD8eN1taKtZ4vs9sCDYTJxv4XV91EhU6aITZ8JHHpnfLDphP8SBEdf/pNNHzvsW/SR+tTNsD/KI6caylB/6lah0/zIcLrxyjcJ4V2OBNdmJ/hRhyjzeCdzOPRNFiqBH+xCy79XaTPnSKfofr1A9n9vZFMvx8LH4G8J7trbaNi7lisoLvQ1vrQn71Ebjtka1VIHqV1hrhMh6DzMhJAX5oDxt8d2e31fLNzr92RQcYiseeB4zD0lYdjOQV65micmwWXtxXzQDYoCG+algwx0hS2RxrsTmKu3AiispPtwi//Y+oC27YKW0LC5nVIVzCgzjBqt9k5M5+6Jgd1O5Js3seXI3v4L6zEtl97+2lQv8D19LI1xO/z3fCNPTS4hu2Tcdrom41N6NRMGfCXyUQGUK/r2ltN1eGi67BZhQ3948c1zGupIpDfGlup/OlTRE1J6IJmB5znL4WsjTcyFiSbPlaKyaPIchVuAutMvFqFN6Ab0Y/X72CqspDoftjkLJuKyrKbtMnuAf35m69zZKG7RBBUivzpepEXcJPk0vqYhmWU7Cx9S0d+C12GC2c7PuNDfcPIuBL/gFwoxXK9GK9o8vl+YpRJhp89VFsV78teDf93fhz1LJVHbzWTPtC6e1g4MSuRvDiu9g1n1K6ZEbALTeK84vtd8rFgHI9wpw08YwZF2bsop03gvbWulBWgIPS6B6YlpwVm2GOGPplS5HXv0t+G8+QpGobw8iXwhYC5Dw6St0nn4S772BiYABb2V9lfuKBXuGqARZBH4BaqgMbP8cUMyjO60yFGgsZs5ZPhvtC097UzpfPNzJ/wqYMRiuSmm7E8OU9/LUhTSMbg7O0yWoQIpygf6x/mH8SDp4i75FPGvO228Rp+Ut4iRvWiAS5N2FdQsGvPADs3PN/LF5bv+N8Xk3x2tz5j2TJY1btdeLouX54uZ4/lTp/X+rD1HL+F2RU3VgZZIkfVhVb/rP+YO0puzirn2HiZDeV3uoolDPVs5lThbICjaSx65BYmV4DwzMP653XLzpoYJ/NYdmg2UbaoJ9wmk9+6qykFw7cdfJdnG76mTeYzvq63cbEt8V+QxF3mjxYF0JFN8bZibw4Vqnp9whTEqKOX+55vmXc+R59R5BzSdsE0u9oYy/O3WILCu0OmepqISQpfcIssXR/FGzB1lAjTsr/Asii6on8pdtUAMktCVprp+L6QiK2DGsvy++6rBNQis5OHlDTpTqN85JLoZX7k1Z7gVto9P9Rb5G0HA=
*/