//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_PIXEL_BIT_SIZE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_PIXEL_BIT_SIZE_HPP

#include <boost/gil/bit_aligned_pixel_reference.hpp>
#include <boost/gil/packed_pixel.hpp>

namespace boost{ namespace gil {

/// pixel_bit_size metafunctions
/// \brief Accumulates the all channel size.
///
/// \code
/// using image_t = bit_aligned_image5_type<16, 16, 16, 8, 8, devicen_layout_t<5>>::type;
/// const int size = pixel_bit_size<image_t::view_t::reference>::value;
/// \endcode
template< typename PixelRef>
struct pixel_bit_size : std::integral_constant<int, 0> {};

template <typename B, typename C, typename L, bool M>
struct pixel_bit_size<bit_aligned_pixel_reference<B, C, L, M>>
    : mp11::mp_fold
    <
        C,
        std::integral_constant<int, 0>,
        mp11::mp_plus
    >
{};

template <typename B, typename C, typename L, bool M>
struct pixel_bit_size<bit_aligned_pixel_reference<B, C, L, M> const>
    : mp11::mp_fold
    <
        C,
        std::integral_constant<int, 0>,
        mp11::mp_plus
    >
{};

template <typename B, typename C, typename L>
struct pixel_bit_size<packed_pixel<B, C, L>>
    : mp11::mp_fold
    <
        C,
        std::integral_constant<int, 0>,
        mp11::mp_plus
    >

{};

template <typename B, typename C, typename L>
struct pixel_bit_size<const packed_pixel<B,C,L> >
    : mp11::mp_fold
    <
        C,
        std::integral_constant<int, 0>,
        mp11::mp_plus
    >
{};

}} // namespace boost::gil

#endif

/* pixel_bit_size.hpp
32TbvxorrTF7p5Io7gaQuuz/UAQnZ+gKveatyiw1NcwkGWBTZRvlOb7FV3qOn6e6P/tX0f35r+Qdnv1SL7WujvHUCHw4VagxpNvSPl688mfsIHcJSuJ31QSEJPNGiHEt9WNpDBdj3IIYwcYI4PXpmFvtiSCAzyvXICwD5zZfFGdfBDlU9Znt1xnKOtDE6aCm4xcoHgL+NaR2SBFmK54o4AHJghr0d0vPxN2BnHWsZ80MkzraYiB11SId3a7yX7GU/5p+sacXUYuSMQC8NdhVsA+PH/VAWlLx+HtE5gX2wkmurfMD++hbnR/R1qP//Onsf4eUMYFYvDxHSWDcuVrILwURCK6aI/XfVFf7RyidaTSdyBco8s8AIfK+Fy1rTvLLQOwQ5qHRimIRUWz8q0V/QZJ/9X6UUEX/cAp0Bi4soMz6uLn2uezPaOtcljuvmpi546k173PubLjaYWZ48UUBNPwU689k+RnaF96F6k3wIGJfeEabPa+yarA1LkofUdqV2yKYaLQaDl6yQ74mOCVdf7gCuFnEqqB4eGdpPglO+WmuP179SZEfPDubFn+1eE1F5SPk+hX1JwLJnYaQNP8JAjThTkXaV7+y9Ge6Agv0p7UFxI8nb2gKXFu49kVpGarP2MsfQBLzMr9jjQfB3x3uONw3cK3hJqmq5IXw/oMakUP4g78ldDPj5zVobsbPtKK0LAvXZLjmcCVwv8N1RgH6azkOa6nm6c8064uFQ8NrlET8POJ+Iu5dXLChJ/+uAlt/c5r/PJQ1p/n35mViZp+Ahue8zD1U+JyXX0C9zfklkZJ9DJAMUlzttdr0DlfvVFbSw39Z/DccILrTcB5P/mMRXn+NY+7xuTyY4TefVFHTMlVe/uJq0qhUHuyMuBx4B5T/q/k/zZitbznZQ0Lq2PSq+A07ret8gnCWbOvQ3WMmPKTxYQQtcjRH7FOrzodICwOA2kEV+JsC5yqwQIGrCfTnEy/o/5EImGVGvSongFeGR5GSjCX3dKKU9UGUy/zeTc7jfb48r9ZwJzWsSYuCENYGk+tWKo9IBYUsyv3CNvix2LRFIsRP26byTy6g6PEa8PO8BkBTDV6zJYKW26vTxiZCeeDLxshEyTiXzJHX6c8czb0BXnPdaxJWwrAaM8RfqotEEYMTNHingp4S3H8n7qYacFoD7paARQyIkoDMeEB7CPRbQv94tZzpva2AvyOYfUEd0+TXEej3hC4RaL701pVvin+yysuFQqIle4wmSzAjNKZhqOsVAfYnvXYzcC1aBlyLpWtGavwCBM2VoJ/CQfdq0CwEvSZBy8NBKYr8sLwfnGfnxuVhOTR9Nckg8nC7RhFyEyBYg4cgNpc0bpGhz3SLjI+RLbIguvIWSTn36rAA4Z40pjo7uuRT7grZdXLOdPDFwQZIas6fTvdLIxg28ebjFC+LHFUtVIjNdDiDsmPA/Zk7pDoPHX9gWrlf2hxNf4D+/G/gDy3JOdPH/cKyamI6DbJofz5jyaJ5/MGitNdIyCD9JrSMJLDATMTTgIaVA57XAPMjFFvYHTi4VGzUIS+eo+ui3cn6yjBepbOqORAaqRyuKaW605iX9ZI5OtDBQjiMCLXrm1TCt+xlxYcgonNWRHdkk6KbgThcgwO7XYqtObHpqFu9qSK2bBtbvGD72lUB2wcWtp6KLT7wOkLB50SUh/LGvhaoRsnW5e04ZXO5RAdE5c43CphGwAAXV+nWTGPeJpxKrjv9yD17ILY5LEG18OPOTYKf/J8RMkcf2qIsVJOAI9CcOPsrTm5DATcBtymAmANlUcxkspOBR+E3HTWwgIBdBFxmlZGAEgLi24nm84ywdvrxAIgNfGpC/5xRDrY=
*/