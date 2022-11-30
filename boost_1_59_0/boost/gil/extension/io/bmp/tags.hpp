//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_BMP_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_BMP_TAGS_HPP

#include <boost/gil/io/base.hpp>

namespace boost { namespace gil {

/// Defines bmp tag.
struct bmp_tag : format_tag {};

    /// See http://en.wikipedia.org/wiki/BMP_file_format#BMP_File_Header for reference.

/// Defines type for offset value.
struct bmp_offset : property_base< uint32_t > {};

/// Defines type for header sizes.
struct bmp_header_size : property_base< uint32_t >
{
    static const type _size            = 14; /// Constant size for bmp file header size.
    static const type _win32_info_size = 40; /// Constant size for win32 bmp info header size.
    static const type _os2_info_size   = 12; /// Constant size for os2 bmp info header size.
};

/// Defines type for image width property.
struct bmp_image_width : property_base< int32_t > {};

/// Defines type for image height property.
struct bmp_image_height : property_base< int32_t > {};

/// Defines type for bits per pixels property.
struct bmp_bits_per_pixel : property_base< uint16_t > {};

/// Defines type for compression property.
struct bmp_compression : property_base< uint32_t >
{
    static const type _rgb      = 0; /// RGB without compression
    static const type _rle8     = 1; /// 8 bit index with RLE compression
    static const type _rle4     = 2; /// 4 bit index with RLE compression
    static const type _bitfield = 3; /// 16 or 32 bit fields without compression
};

/// Defines type for image size property.
struct bmp_image_size : property_base< uint32_t > {};

/// Defines type for horizontal resolution property.
struct bmp_horizontal_resolution : property_base< int32_t > {};

/// Defines type for vertical resolution property.
struct bmp_vertical_resolution : property_base< int32_t > {};

/// Defines type for number of colors property.
struct bmp_num_colors : property_base< uint32_t > {};

/// Defines type for important number of colors property.
struct bmp_num_important_colors : property_base< uint32_t > {};

/// if height is negative then image is stored top-down instead of bottom-up.
struct bmp_top_down : property_base< bool > {};

static const uint32_t bmp_signature = 0x4D42; /// Constant signature for bmp file format.

/// Read information for bmp images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< bmp_tag >
{
    /// Default contructor.
    image_read_info< bmp_tag >()
    : _top_down(false)
    , _valid( false )
    {}

    /// The offset, i.e. starting address, of the byte where the bitmap data can be found.
    bmp_offset::type _offset;

    /// The size of this header:
    /// - 40 bytes for Windows V3 header
    /// - 12 bytes for OS/2 V1 header
    bmp_header_size::type _header_size;

    /// The bitmap width in pixels ( signed integer ).
    bmp_image_width::type  _width;

    /// The bitmap height in pixels ( signed integer ).
    bmp_image_height::type _height;

    /// The number of bits per pixel, which is the color depth of the image.
    /// Typical values are 1, 4, 8, 16, 24 and 32.
    bmp_bits_per_pixel::type _bits_per_pixel;

    /// The compression method being used. See above for a list of possible values.
    bmp_compression::type _compression;

    /// The image size. This is the size of the raw bitmap data (see below),
    /// and should not be confused with the file size.
    bmp_image_size::type _image_size;

    /// The horizontal resolution of the image. (pixel per meter, signed integer)
    bmp_horizontal_resolution::type _horizontal_resolution;

    /// The vertical resolution of the image. (pixel per meter, signed integer)
    bmp_vertical_resolution::type   _vertical_resolution;

    /// The number of colors in the color palette, or 0 to default to 2^n - 1.
    bmp_num_colors::type            _num_colors;

    /// The number of important colors used, or 0 when every color is important;
    /// generally ignored.
    bmp_num_important_colors::type  _num_important_colors;

    bmp_top_down::type _top_down;

    /// Used internaly to identify is the header has been read.
    bool _valid;
};

/// Read settings for bmp images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< bmp_tag > : public image_read_settings_base
{
    /// Default constructor
    image_read_settings()
    : image_read_settings_base()
    {}

    /// Constructor
    /// \param top_left Top left coordinate for reading partial image.
    /// \param dim      Dimensions for reading partial image.
    image_read_settings( const point_t& top_left
                       , const point_t& dim
                       )
    : image_read_settings_base( top_left
                              , dim
                              )
    {}
};

/// Write information for bmp images.
///
/// The structure can be used for write_view() function.
template<>
struct image_write_info< bmp_tag >
{
};

} // namespace gil
} // namespace boost

#endif

/* tags.hpp
q16mJ83L3pbQyefZQdRDuSqKFdEDhgaACoPW7jk4ua+M7DbbasZpI1H3Lt8+uaqJzhRmyG8/aWKwr5NoIdkMyW/nPKGCgXfBT9X4LmTGWYdZVy1NEk5qVX5dk7L3pehaV4Heygryh5Q1EEX595L2tlcM6sdGYubW78V8mkwfwqry/K8ulW6RjRpy7R+Wl7KwqPGmUtALWTxVYhg2r9vWMbAsgo7QqIjjRDfsCyus35Ik/lX01mDECbLhPfx+mN5i3sur9kSVOfipWt3lJvbPC6U8oV01Ebt9NHG6pXhh+EvSDK8pyVIRi+K6k0at/+C/C56LPE7NQ9bu0LHrHjHfUMpjEQGiiSkQGXo+1VPHLa4krmToriG7DzrtR81jLuFLoGFAGE7ut+WYb+q/GwXB37Ie2HJ5JsCi463CU9Rp4bgOwGZjd3ADklPsJ6bbMzzTvgeRoAJpvdvb9bAEPJn/OxZ5gz1CE/LkOO5CFc1E6Kfy0DPEcPoKKwzlGahihU0C6ocZ7AzQd94jmpgCcV1QR6HVhMOg5DDa1Z+UA+TnM5m3Yn9d5jeXEPH+FMV1awtNQPac2inGFupLbJ7HAxcqXDN9FFjg1nFQvHMZQW2hO3IOOxN9UTj0a+MInrO9gEJk+Rj1rhGKKU9mHh8CV6pZaFAkMAjBybmzkVM7euHb+bw+0Tg2Kcy3cs8bExhyeopuUnlTOZH4ws82XP2hrvcPD9KucSNej9yhFWbj0iSpHu3dtTT6rb5v602buyHgZhZMahrmFuCPpyTSuoTCXSwGBj9+Ixu5dIi3WGxBiclGDLEgRI1LpPipigrC8RazAHT9effr5VRJFvjditJqYGuuvM42yp3ZhaE+bkr1PPUZfmj0CFBceI4wZVcRJHILQLQMCgDbmyGdxyicIctUcQjlCjwcpf3kb4hS9/UI7oZvwhHhM93NwZ2ZxNfoUkPdfGNii8H8FKT+b8aKZbgYcDqgA6qMbZbBGbFvExqbmGTiSIycwRzyqJ/2YSuMWGGwegr2jTp6e9IB8ouaiPYLnCDYzPEs2fArWk8g33lnm27xPQHVBRU9IC8Aiwxp4kVZMPe/R2ggkqlmZIuv7BvedD3jWcEuXo02E1dLszO4McfuAt+qIdjRmHdR6y9aKKj8+6JztBz7M7m5F4Km4oAq8Uq7Uw5/iCQUBUylJyiCWCazMC44oOP1tZo9sMS0uCiVc7dhPgIXk3EHLizJxA+uxHc0dC5EwQEPNqFel1pPHxxmWTgJGYVjNlVOBt7c763pXBsM6VCeZuAPFCkAYt2qfK3LTNkKrpu1TSN5p2TcWKwKlXhEtg9y2n2cnssEIzs9ckvzcILKZFSxw/oE//QAgPA6g63Jt6KADbfUEc8cpGaV2khR1gjarxqAWCRlLFKy7ff21I+lo3JrP5it8qSRsL3l78+7f67BdL21k+Pe8CQDI7JRbAYWW1KbpSiJVsZ0Ca5cUwxODH5zv8U7sy6ud7aoEv1vQNIVLPhIJRkN2u5SIvwuuIsdcePjOyU7oHd95+NnK+BB2GKILSPcBIq5cOeKLv6vCCSqlZZ8R3hiS8S8ABcs6NMXIzE120ABCc+tBZr6uKhEAWFf6ib3VvLUt5GTqZX8wb9fdZwrWCh4PtLlHNKRcwVPHW5ORagzrv/U4ZQ3FPHw1MreZidJrGMwcm9iL5Qs4jzSd+D76J/qRKQuSBS+KPiL3iWAcQXmoIzS5RLp/DECIzouelR6iMq37Ms3PK9tWrsHbMi8GrZlPEiw/0m+AletG0NDm/W2Ss8nVEku6OdCVoYbfhZL6+B4WJmUzTi1pjgM0QZ9YLG9Ldrk295VC7+kFIZW2iWVmKyUzkohdxywTcR1BJNx7PC/ErEQp+/6Zw1LC3MV520arlSh1JtB6R5VDpx0xRps5zf1pfGlUXvqQX7nx4tS601qChY09bi4XNPupyB0zurRe7jvD8rJ4J/96GJnPinNwR0E29Pgdnhb7DQbC/tUg6fkZq8tcmoa09sXfk5+Y8leitJygeOQxrgPdA1RuVzbe8RpMbB9xHP9IppMiYZcfybYbofcTrHMLY32+oBu+h2L3WS0M2+5thYT1f0qJyEewtRzzYy5vPSJ0u7E59T919CemjhKTMEy2YN8wy3lB8WAP/FVsJuMdQQTHltiD0pvHpi0VRhjKUcWx2gPgUhpGOIdQzU/jdMQhs2+bDoqIsQGXo5U1J4+NHRMKeOKvUJYvkZqD3OVR88Xs7PmepqhUIAo0CItbMtWZyrH4yJwIpdnsUTd1Sl3LW9GkbzEbuzsad4XZl++oDS4n2mkk0BlclXKUqg7qUc8ru08QGbfSr9Lr8bNjdl/4qJ7lbYuR1YztvvumkDmpZvPO93mOvRPL1C/i9ghVrQvstOY+fdDONvHHu9Lcg7ysv6mtxQgLGF/+udKwtcNimi3G34T6H8AEYDuf1ezAPHhr/GsYB1vyYGsEFA1Y/z1oxjTXGMueCZAy1nNGzUsSi2VMvrOl3NazDYouNpDr6IC18VufXN6ymsZ9gM26NZTgpeGLMXeoUiCcNfhveVBEbMnlbfc+bZOTA9PtDhpYUJ4rBr8WrktrFtwluVF34TmHPVmk3r1xrSZOTvDQ7nmab1UUpCcdm8lD8+ggTwLBj2RDzfclVPvpVUlEdYFnn2pYjhHhpSSSyScROpNmZYqf040hXlnZV72weKkLO8wlnGMfdY9PUttrEqE9yA/rfVOcMun9I7OMUeFAZYBJtO4EHC1ZO3DvAKEBfWw7+yodqsZ07nh4aWBgtbOvoe5WtPXqNb8wUqpKZ+9bi3R+6ig9oaRHUvNdz9em1l9rH1eKDpLyU520+Dc4KmYIY06lOKxlpXZ/bCrrwYc7zwfsoXKpYnuc0gPMzt91GHwMniPn1nCVpRURk1ZyTb2hm9nb95iqfoxg9MNpbwzYq5m+5od+wj5yzTc2457/wwpyOh/F21zt/CtAc6T7hG4k003lf+q+It9KKbrEeIDbRnPBJ0AbXhQgcQE8Riadq4FJGClV3fhXO8jvVewtmewtLezcOE2VA1ZXf8aNnnFCo5uogcGWzDYzLcv+rk/UvN+r3fC5lEzVdUb1ZGR+mvxc3TbyqD1eJA7rVenxMwq90O60gv2214fUfbd9dY1MrV0ubDxPAJ+shyU2128md70aGkCfM+6Z/lT/WGkd/Tx1f0RPZjaTuNTD+43k1us8xZaKWB4xUT8rOdtZO/ke8+wX/BzbHupLL7/c+HvPv+B+GHy45uxUTXQ9TTIq8G6vg//Jen1A0/zNuar2Mvn+kAOpi83rLva+2H5uHkX/439Ev1z+RvCbry8H/liaBvwqeTjgHphwNTmRf8jqiaZudq75uv3DJ36w3MeNWylbWeP/5lwsyV1mwefmhzLK9rcN/vTc3ITT5O8evPuz1v8DgytR37X7PUl0Fnp/uveO8E2x7e62Ek+UZAJ/2a5a6mpdQJvXd96+1mlO/tQf7td9vDW68sCydZV22MCq2TIf/5zgMQk1eXrbv5Y+SGgkuJbK9NKctPF5m3lt6r943PUff968vOEHhn2mraKiVXNSRNDZvXFR5GTS4HXvfuF30Tg8AE574PON+wjFeBo8EoepjH9mnHumGXPq/74Os/54aH3a4suK9/2+QmvS+REie+blhto//hJoTcK8jnM924MHhDRuSvUw2ZtEzi9m0Hxevg9PfvzFtv56vb38U34OnL4qOHjVxul8lFGu8/Mx8cywoih7ofFN1lr9zsytxUtK0XO9vY4yZdXJXzrpwNcL/G59zs5F3GffTOLfdeL/HP6NyLm8QH6fX/i4ZGj9ZngrvIEZgo7nhf7zLbjVY4scOmLO4C+ZzZ0Rfbz/uc9/clG9n1HiZvRdyv1RNfXTDe0PZdp151jxauWshjnsndVjf4HBsx8wtc/iz1Q6MMrluN6NH+V9eFAA5Nl1TdWprLse2L2D74XN0OF7edHRpVYkZc5d+Jl1fbHvX5mV2u7LWxzKAcHk3lC47TS47O4Qcwj1rQE09oJ5+OdKZx7NFNoAse05WX9SmAYx7Q1K/lFq9eiIc9hur7NzFSmkZWjys8EnziYzHVONe8I/GH6RNB36JipmBlZuF7cnJVtxMu7vnz2CdO1bW8t/mh3i/vv++Azx0vz8yPDb6v3o6swUfpsS61vNy/O1BayL5lv7W7eU+9IXS3McMn7I2aUY9b7M5NBj7PJ5yt8IZ+9eS/Ao7Vs76+xRPDN1m1uPNHAbSfK1zc+/ALUrm0Ms1yEHivU4LPjNMFvjy0O2sxOry3e/uu41A9q8MvxUG4lVW8GPjN6yOct8Fe37xu0VnCa5wMoePXwga76z+/XrpNyua/WswUvvslUuWfBQsH1Oz/dtpflzUHO92P/h2uvLVvT7qunkTzn6yvoa39i5uf6hdpd9w/W6um0Rmby7+H6tFO93on6d/l7h1qJD3LX7s33nJ63I33+zSMbyIWeELfvB8NA96Hw8q0vT6Kp6Zdd7snF56bc8zUe34idyzG8j91v27B22w96Uy6abxT4+UlVeqDeImXW6C/q6/dnLIel6t7Dw+tsmd/lbXTBsMaXlBby9pSeXvn9qu2pl+vuqYRj4xsba2qvuTTWrVVMpN7qW1tOSXtG1l/H1xNqH/3p48sTljUciF5ZDj5LPPaNryC+1n/+Pl8tJwRvPN2vbXxXobFM1l2V7X8eP+5Gp1ZXdb/kvHBfdz67WN6nMo2jX1nZsuR+LHasv81YnuvxZqcak9l7eVdkfmZMc1l8WL7NeJzTDVty7H/cq4trm9u+6CTW53m+mGPvc2NVHU+9n2/DfG8lzt+rer9Ng/m/eOk84LOsZc12nr9zmKfqk2d9C/HYv3RjM+CzDOAe06cFavCrSpkc7Y6vd216fpFP1Pf5hOBPpvFOaL6rfPUdAez+7weJEhm6kgAA6AF0/F7cIBmH08MR11yxbjygxKW3MTjJo2EKiHSodna0VXZadmQKa1CxVXt4OFNVRJH+hSigjwfE6Qsu9KPPi4WCIi6AONsB5wUDAGICECEGcP0LYAP/uvPqO/nrmivRm10DTjJQS6DRCMa8t6jasty06hrNrNWk22mow0Xa6dlgCed0c+PisKpds/5254w+XjWINutGQJIk3l8BwSJLb04EQoiA0DfEFqaHkQvADwBgIgqVBwhx3f3iYr0aVR0IimEJSUAYDGNhqGWOa0IqhQnJDqjsv4ZMmIcah3QCFS/Jbw5QEX+Pd42wb0+O53cHhBh3Bd+ouS8bjW0uLw/uXtBfxMPvn8npfuJunPF1vbhLPbvLEG1LneL1QfVwDgyc9lwb5D3Z4gT0NekaCmncv5Hd3N5NC8RxrIMq9tUX69p3XTmrvLUTZ71snR3N4aMfx0aUCUaJi8OjbRT5IdYOLGJE1EvH60jz/pGpgltm3RMDLx7rI28ymmmLL9H3aSyPC8ItJ1YLt9eM7cg6ho+4JZDTXDBLHyMISAZMFj3hQ2A6MUdgebe+xfbQ/HhJNV1ZUiQg8IPw4Ra7cNV77lhZ/PbqF1x9ri5WNM/4e6MaPCnxcnMukTrtktDb6ZOg9aXs0GlK2h64nSitt/pLqpQoK2CTsA2RQZSmuRQW+jzfzOm5mGVN3w0YOg8ePDe9MjgalCJuzJfDDDrhGM1ZK/HnAQ7Sxwclhz6AJTXg7Mi/R0luVPAna00b/WDYQGzhdhDp8jH9LlbaqsA8Nr+k8DyNjbgr+LsT/PaHluy7xYpFpTj1ruap4fz1WKi8zVVjp1kXjCfFiqqpWeJNhZUW5IXxGtR5n64rmO15ZEnzFUxV1EH4Exe+auyOdAICu1NHl5mg7p3RlyRXSueD5MRoj06fyjAjPA4Z3GE+0ghQiAJ/JGt2jD1UuZG8BBeGnNQqzVLrsmUKbxjEqb2PcRD7KWBJj7WQNn0Z/NoqNdrbesCAb0B1RfuLZr3ubzrYwkLuxTqOEUVVgy3IzlWd8XExJnTQduXYRygLdqlHn+davWbDoKGeXC062FqDpiF8io6c/rU22buWZonHCAR2CWkf14hxnO4KF9yjFdx0C41H1Lu+5GNoUnKKaCpaeyrm42cg5pkT2MgNjkKwodwlSAG5fhGa/7P7DdUueL0hPwwMBQJApaRohbhoJVmhjU0CPB1Mx7FuJTPMRoOmCh2MhYtd15f+szwMayljQFbcI45LOg6ZtbwKsIFISJ3Cuz94QCDDBDV/MpBb2KS9NrwNa5b9OmoEIVz32DLYOxKU842ffEhuVAWwGzAYwxlq2cercQULNLADJPmzcQ3rBnAFg9MCmNfTlArLmHfwVpVRrPt417pSojsQDlTjoOKNmFY2JmGAnW1Pmj2+d9TzQ0wNkjT9pzH579c8+hPbHsZf7pKybdRfYz7NH+N3zh4ShsvILAq5YbRGRWW8A5LvkRJJWPynnIXTjU9oUareaXTP+yYTzu9cugGMzsYZrEfFcnOPhiyGoGDGaubXXI9ew9c0Vk9u6PTJx2NdV99+Fjsv80R3srJhelnvkWDdgTiOAaLYG8MDJfRCfYOPK17wAWjVBsh+xIs3zLA48CBGGeMKGgOCQPwi2rGnKYSInjhzIcKKfl2CtAmjFAmIau8yIhoVEMZeHKlVEEZXBAohOVEyQH/+PViMkWp0owcwCEO9MeF9eMagMItDlEYuXoIzMFiDy+J0T/AThW4XoHQpacQ0SAcKfafBNmBGnbjOeV/pq4W/M4+WHlAradDs/CVDRmWKNLOmV98ot2nl2QCXL4objsbsjXoAfx8W/5ic7JN06/+m1314AZzizFTo4+zt+0PY1WOOhM8AYh5EDeKwTPJ8IK1V2BthQoQG+CMczQximsR0s1ipcDDCgAj188ctnRr8fqMbBjk6mmcpzaJWsmgjqzGgr1x83P+M9OIswokosoTy/S5BLxnW74ifsaXiLjnUpy6IojuMqE2fdO/p+vM9uEp1Nf+e4P3op8whLcMbYFB5XDUG3okjT5F/GKY2/Yn2Yc8Te9RJNr5c4+55s3PkoP36BiyA17mL+eKEnVuGF4fays4RiZudXjdeOnO0NY+scJx3G26diJM7jB53Awle7ZLIva51/LkkKRMcfYAdYPstaBw7/uUe+/x9jY2TZPSF8cdP+1XucVblf/sdSRiPok4btsDUhQcdFSskeD/L9Zbe56O/94j5apuMEKYhAxIcr/5TMqxuk9w3qWtsBLQaVBNWwhzR8seHPlbs1aFxmm3dALDlD019oN5ziUtUGzeh8FTYvVIpQOnGcpQKjHxFP9Ws2RnkQKGoCUStouhALTNUc7KoaowGNZN8cyQx1qNkyRVhAEuJMIbk8km9wbwqcZVil/uONru9GjFipCTsqYrlNzGQ6DZEofIKTiVJXQ+TxTUGy7FwvWTbM0J98cqjen1ZDaIq5Q23MDUlK68qWic5kUrETezwgdObkLr/LMitGVcBuT8eKs5ezBtkfuhOoHcYXpTGm9Y5D0XY21ghfUBErDush26dEgBvZ9cb/xxRGYJeIDyiOONcFDMWBFRUJ7ZTE0AOQmt4M/QB64E1Ii4gWxu8feILgg0QnqDsBGHQ0PXQVh8PTPaWUEe4JwRneRcBHsYAGAKRQaCw6hkWBDHg
*/