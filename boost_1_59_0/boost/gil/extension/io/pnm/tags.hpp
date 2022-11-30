//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_TAGS_HPP

#define BOOST_GIL_EXTENSION_IO_PNM_READ_ENABLED // TODO: Document, explain, review

#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// Defines pnm tag.
struct pnm_tag : format_tag {};

/// see http://en.wikipedia.org/wiki/Portable_Bitmap_File_Format for reference

/// Defines type for image type property.
struct pnm_image_type : property_base< uint32_t >
{
    using mono_asc_t = std::integral_constant<type, 1>;
    using gray_asc_t = std::integral_constant<type, 2>;
    using color_asc_t = std::integral_constant<type, 3>;

    using mono_bin_t = std::integral_constant<type, 4>;
    using gray_bin_t = std::integral_constant<type, 5>;
    using color_bin_t = std::integral_constant<type, 6>;
};

/// Defines type for image width property.
struct pnm_image_width : property_base< uint32_t > {};

/// Defines type for image height property.
struct pnm_image_height : property_base< uint32_t > {};

/// Defines type for image max value property.
struct pnm_image_max_value : property_base< uint32_t > {};

/// Read information for pnm images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< pnm_tag >
{
    /// The image type.
    pnm_image_type::type      _type;
    /// The image width.
    pnm_image_width::type     _width;
    /// The image height.
    pnm_image_height::type    _height;
    /// The image max value.
    pnm_image_max_value::type _max_value;
};

/// Read settings for pnm images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< pnm_tag > : public image_read_settings_base
{
    /// Default constructor
    image_read_settings< pnm_tag >()
    : image_read_settings_base()
    {}

    /// Constructor
    /// \param top_left   Top left coordinate for reading partial image.
    /// \param dim        Dimensions for reading partial image.
    image_read_settings( const point_t& top_left
                       , const point_t& dim
                       )
    : image_read_settings_base( top_left
                              , dim
                              )
    {}
};

/// Write information for pnm images.
///
/// The structure can be used for write_view() function.
template<>
struct image_write_info< pnm_tag >
{
};

} // namespace gil
} // namespace boost

#endif

/* tags.hpp
GZy9GHH3LwthTIAkiCdo9JjhUBr06qPaLoVNSp9FOb4I5VuojYUGP1DKOaXtFt74JyProEP86F/IrNRX/MGp+xzaDfbY5DWJPKK4nhlOhFhxBMVPszjb+DmxKod2LTENXxCdAPRoLDPgKqRmCwcb7k5NfJXcBq5O2wbEb86CTpmRLySkFKYShgSLzkoY4kLCkIDDzBhyQqtyMxu77FVifxY5wm5QfeXNHIu6yEGQ0aaiKuI/Nzr1GU7NomYj0tktHFoi0vAL7Juft8t9s6s4DqbOIfmNTHEZNYmjvpjPwbC85nqsksjDZWVlOBEdJS4hkPbqkbug3YdmtU/8ckq/XlaB3JRQ6EKnF/NXM58xp4GNAGLzqtWqAs06h89VAg56rC4s4BrfvM0q7JXUzBX/geOHxGiNeIY/boTo2BVdXGBpyP3W7t5bHBdHqccg1v52sSztcTEeJz7T/G3i52e/Zeytt/dZgowb99gxLFpwi6fxqM7TYTwCLDHKP+/XTYVUKlpNKY49tBvygqdakMDnwEZr5Cb9Aaf4w1ZorzwznZF7SU7wzHTcH9Zm2pFEZcLKRF4YjuoZw7MtCJpjJ3b05LBsdgk9qXToSFHh8M503HsocY1YvhW6WJJFCmF26KCqB4bxa9TlMrGbrrl3h8WNs3X9ZhLLVIfyPwbeVYDbbtiAGXV9Jme0A1zp450yKGYVVCM43vDRbmwvxjFhu0qgWjSVATAE59sMAPHOdmYWhTj+izPEcUJDQ3fQFU9eckYPECPcdSmCJKJKmKoIVb7QJTbRXfGxG4JSzSeGoXqoovx/oeUkjOk2XusSxVQxBG2NPZwRoguLJY6UZKM2XQomXFXaowO6dLuntnawSiLH249XCLcIsXYEYnySBv8VcRIHAT4MNvYkH8WWGxhmB4ZxPbG+nuvIO3VZAb/4EJ+ayObf8gJB2wBfYLLwgzUi3qxbLRJ/WwzuV0AV81dc7k1cg4hgfXWQHgyoUeOMbQ09wDZ+U7yWeu9Pi6EYEud/amDuUbHr+94+ibcTcc3fItb929ZNP/F/tmGaac2OQZCZyBhtNQKzeA+QYCUDF6nrUKDyYw9fK54KzKfw3m86lsP590AkW0x9zGYBsoP9pAW+tQN7YbO6Am+J0jU2iyYvy48nFTzEdp4QHAoDIZ8KHtkHbYd52I6Ef0+tsjEreUBMoNYNspPMaRgMCfsSIm/QxJZqzfrjUJ9rRbSNvZCHxDhjcunXBsIOKmQ7Jj4+RZ9yaAG7bR4Cy9kO2E7Y/qUusy9Si+QSaIh/OtptahscFbgTo49YIeCoVnoDHF7Y+sgemDKKi5Y7LHv1NxCzR6z6sk+XjD0S1a3nMCxWJQcS9EJ9PeQ3ogJm9p+Qto0zyvh7ieH+TVnxseANWhNdRrSlDu067RDQ54q/Z0OzA0fP3mgDmC5LxA7qY+S1juQTicngSrkRHCmc/AbXIyPYgzK0vdq5rFd6Yg9R71KOnwWi69DnuKM3F+hE8WMLb1mEIYuHN/QhoRFnZwTjjpxV+hrE+5H8LCRd/W3EMhIv/a2PqYurZjU0icYhxwkYYx4CY4FMlJyAJ3GflNQ/GvwIAS4T5VIG3z74EexvE1MqFu+C/GY8Uv5WsWMr3a8x79+pmDU71y2qX2GdwzCpO+dIQEC8RalwUpgEqR9SHJ4VcK1SLpDmutI2dU0bTWzoFUNVYg/bEhlhe3mAbSgd+qip4zhzdpI5eQPTFaLtBBmkxmjLHNo1REJrvs62eJHigMjw3/B5vCGKXuzD1nNChvl8CXEHLNFdQGxL5NJQbDWMcEXdFcyJDdHcYSsh7hy7UUP5bNHCFBrlS9Piy8Pg5u8qIiBsBbJRH0YGxfkdrEgeQg+bRSk9NNELbIC2Am7Soe0INwIY4Ajsmo8yLDo3gERTx/4X2hBOgzV7Y7+ZBssrQx0iBsMrlm7W5zDU8nA8nh3OKD5J2EAVeqTuzRlEiEj4TnycIdNjmUcuj5QUAGYBcWt+P4dOM9bJbfRZE4PPRZp2ngoawaaXOWRixlTans3wmWmBa805KNYT+TwLP9BKHJpVuyY2r2uOHnBqvp5CX5etl6ainXY1YlGK/7JQjKnLsezfK557wcTwwcFwg8Vx7QT0eLBgTAtirmVByyWDVNHumkfQD8MDorXKTpQbctYtdGvz9djopZl52uo2BOza83AGR/pEyQqcNdmm2W2IUNStzszXtsJ4w7uP6uzDrjszX+pDH9ogTRVS9FBOkfB+kZyf119Kzg9YRzlFTjgTbY2zgfidV9A6HLNMRlUYxcpBl/Hsw+hL+Guhdwv5wWXabyOg8TMKIiMD8lUcUOpvo5Sqv4y/KUobTHbo1c/RoQ2l1KELXzIWziiSHYjsOjOkSwFROsRcMhDRmPF7U+99WWe8l0t4zy42zVhuj4/H2aiNeKWkAG28e03q3Vf/zbvjBr9rrJy1cu2P1g55VrBe0hEQP/xhv57IpKeBxUSLz/rSwfYkuKfyl8B6wcim2mpk47SatIO7c4HZnaEMgj9thpp+3GfYPKz6+gLOd8vrsFHaXF2YgvVIfSsHoRu1mCYs+hKuLWkdinaNTaFoKDyCiO+oCfTmktr4g9AJsifxb7G8y3A4sk851yDOQzAEGWDopg9IwEGk0QXg12R4UX3U5CtkrNNBQVBHOS4fyeGTJKOOHMsdOGGnV0QIaUsaFlksMva6jLwcGeJRhIwghDCct/CpxSLx5gtYaoNztopnkVWQCcjUQalaOTjkCTFzody8e5Obd7g4tgwW0kR/bdmLVF5G0bhLXYHVo67AOiOh6wVEVeVtEzErcVLxYI/cmCJ3BOXG89CLxvwM09whE0cTNwWldnjB2U+h60z8MCh3puuMp8qIoNyPfnR2dTvmt3XRQm3vLeZR1Xx7MFR7jLpS9BwEB4dWRL35lphQ2nhKHcV67QeRc2hXplJl6Mxo3O79173fJj7Qqhy1MFS4ERnhSFY8cb33yH0jYvY/aJOo3HE9Kh6591u0RxzIJC2LuJAZJBa4Fy1UrSkFPpRQHLXzfdjX9rqxK4RtwrkBLKsjLecjeJ+gVsTag2VOku0K/xUq3BeYExSHr+zXZcpoYg6/hAzQ+oGhDRW7DvURU96UtQpK0V0caPEidZGdBER1kVNdh1lR1/EMrevgX8G/XfyL0MUkmPO+BzPxdT1cDL9ZMbmecGs1mCkW4Bx3UEfZNEdduGzlwojKBynqOo6TuA6+M+o6eNYuUdchRKOAHVNsBT4ZUNdt4EocB45xOnxb+LayspC6bhM/qOdf9mZex2Ef13FMxnW8H67bzL8N/DI2/+hq9E+PrkZndXXdDn4e518sWHXh8iZmK6xctIy7lof9Yp9Y9gH420eAuntTVINJy9/WD6YaK5kvNHnIkrY+XSY7BwsQ40L9miTdODfcjbv1dPcKPZHKxIV7k3wlEqopudECY/ycZdeYymFHkoptzKERNFrMJ3Y4DfxnfuWwyHliu9am/7aw+pq2O/2bPhKAjph8Oy/f07G3gQlBDrTMmWR2N8uNJlgWEsuPJelpN8wyW2nYxyLe6O29Mhz89lYZORLqljqTNPUGOODxQQ543KtGy3kD7lOjt9IFYr6m4mozbcX3io+FvHsjD6TI653GfnXor31sGt9D0liPuqDX/EhPgA1s+CNZiB7VC1PoHsnxSm7kMBikC55nJnNMtLLPGhkdHllG/yqe9nLa7MgVMHQpZ1Yg/kmfVHslQ+meqN71DIi6qxbn7fw1yzi40HipS9FdvB/jSM+hrsY1cbHEBB7atwIvEb44QFymcGdXwPI3oH8saSj03ButkStSdzXxZeeJC17t0ytWPAw3dH1UD2IvkRTMbwN58fZq4Oei2v3KsKDcHwoPZoBr7F9qsaSdInRBC0j80K4NDFfCce+ZyO2T1qFfyu30Vbm6OAyn9zPlwqg+JFIc1XMjlxgcHeQd5sgRGxv2b60p0HCf2Qjq6+L9ntVYfBBO+CLxofxI5ABJ+OBlYFCykosMcOziFUaC5pnkGH55IAMBs54HlxYekdwjXSu/5vNOV83fsHc85DAcnaCfc9XAiC26HavW4arlXfhtkA+5Z8x8Tq5OVw0iYTNf/R/lUvWBrsR83cXHArCsWtAjkUnLLqO9rofYMaVbD+TSjhGR49yIadu+NDHaXSZOrCX0Hz1/Po7OSXbUJxZ9BhSj95Auh16c44aWZq2x51zt8fVGfiibgY+CXJ/i4l8SafwdxorUyy/DFXDUcpul8zkOfmCcy66plmzPKI+vTznfePOrJQ5L591UDcpLV82dMiCCJSSh+B+ECZ3lrD83WCfuewX6Lq4xOhW5iHguCza+9gwjMe7EvPl5nNdn1G1XyKQGZ7MunOBJ+0SzERfRblDB3Wg2JD6FEeTllvnzVV+HtHAHMsO9J7pMjiCnTHbv0f0ZVN7G4Vzjncfo4UmfsGrVAISrBhHu6L46giTT7ugyxGxGmFFX7TtYV9Hlhhg+QfN36G/lG4ep6xG3IwuRulZKeEYyxf7f2CzRF1GfCE5H5738YobyVy2aLyWdlkBIXIFuV3Zwv9sju6j0nWJ9pvofyV5fpL/FnNjDHyU5sT3NGRbmUM57ksgR9xu23YRaQfok9QsyN7T5BKJZxNJ3npJjetRVkwMNNn0u9tZ44IG0io4MC1tjGk/ssxUOS5lYiWhTExfTbMynRrTepkxc80AYsuCPVX4OZz3W7xCgedBHH7SBXDtJsLNCpADnTyTRwmnF01k+5T81vyBe8xD0QkG5vL17lVmar91TpPhkbFBWCwWkHIZQioTZSldQ3HgJ4nYmLRqJJedurWdAVA0JZ5L0+IeLwaeIpJHIkj+mmcBAKDqtZRsYZCyqtc9AzUm4eTLyUykPPS0hOznNepK+xcsIvPnGjAi+dUhccXE/x1HkJ8iISIvv5meA51KFkK5hWp6eOOWT6ocilmAoMmTfDRFLZ2e2xVK9XZL5mk3ZUFcXx2d6bljuqn2SJeyNqm8TTI0NSuHb6I2CHCsuzbfJG+3l9zZky1lSH1o+aN3tepolkO7U2qiJPziNxjpFdjslno9P4t75Bu7ZjiZxz7cPuBdxlBG2rUI8qylzqTjVaPT2evp/vUWbmDtO5t1e+8hX1aDD5clmzzWa3fRhstlv3sOaXI8c0jCd8h3VfG6kV/Ad5e37I82/XjyLsFS+erDM8NMkUe2omLHMRpi9NiNyTthioPBxQuHO27OA8WutrppbsrD8qMmN3KSEH5ok3BuIXKr56r37IvmepY7IaM9SO/HT1aDkTb61zIX5ViWyo/5VuqqsNfeD4v3YEZ7eoypPq/4nPMpaV83nsLXVQ97DrtrnsLP41yM0qLJJVzbCrqVbxsTePEjY+9EfMR+qr8F7ylXDlnkpKi9nzPlHiY+qsgF1jiTrrLTKoG6cecnfAPpjFm2ymAlE10yyySLe8ZQGCefGPRlcWJNsDPOORrrRDG683cqvNGUzNoA2+J1XtiUT/EllG/TcnPlvh1oZVysb1cpmyayxXX2bruwwAxMom/geCDudc4xEXJqyocmHdUU7hJU7xtAKW0PmNmbCzW2AIfMpCQbAYBZTkyQ7AEf/5NA640wVXYOeK8HBo+xNjrJX8WiVDUZluccRF8TLXgIzcl46tCM5TT6seZrnxP8DAAD//wAALP/TrL0PfFPV2TieNGl7gUACtFAEtGoFNKhoAckCWoVb6p9ASmgCYls3RbvoXkFygU3Cn6VBrodgp+hwMoYTHHtlEydiFayFMlpHLVWrFum0vvbdTpe61VGhSuF+n+c59yYp4L7f3+fz8yPNvef/ec5znn/nOc9Nz9fU8N6Y3ObVlueq4TY13K6GO9Qw17LvmTDcoSm7IU9Tdnm17FnwHq0NZbEM1qRVbTebTMyz2+lpdzesmscyYp6u4pjnQDFrUsMH1HCtGj6shhvUcJca7lbDPWq4V6uaaDGZqMUDqS0qWZTW1a+XG5i8V5W3uOtD45lnT4A/GbKY/DGWC73yqxdLpk5XGva/hy+HjM6J4iVo5g/Cq/u0vfJGM3ZV/eZdfx/p4L96J82kyjvEwHdADnQwwBXeYa8chLMIV7OMAGatpSx75TcmSKXCVZg/kh2D2tpTmzFb3hEaxJr4Zx9aoKiSzzKCJiyYlyaqvpWoupkAVM16mVm8uOvt0ecx2xJZvNfEjmpVS8RQJokKG8TbFd9bXcmsl/fCkwmAla+JBUsBLy2Ya8bKhTmOUGa1qdtkig/CFsxGY3u8mrI3pnRFuhysbyf8x19WLKYKLBk0d7bj0JTt6470Yg/hrp07oZudXu21A/C+kx9t6tNYA98ZPqtduFz2yg1UGwBJc4Pxb4EuvRW1fx7u4Panz2qsd+HCqBaaBNA6xqU55zSY6ZUskx3TqlrEvLPFvDeKN2Oq/5cJ/AOWO6WItzNf07RIeKNpVQb8tawekZoZJITZAXNmFgT/bkjMPwVL61K2huZBeS10vUvZrFzDXsvD/vZPgL9Bk451xfdJJpUyVMro/CMMz6VssUd3woOBm7nlEvXyp2UWkUmAOco/+ruGUw5frlRdrmyOyVUAu+njhzuYUsXCm53UrpPaza9V5UZVblblFlVujcmNXm1ZrljcgJ9es++C56Ac1IKwFM0wE6UxaOKmSwDKclVs/0RoJKY0AnjUCM1D3qxGsOWdp+Qda5VRfOCv+7SK9Wtwblp2DwwCmtwNP5Gr5sNuMcUnMdmmypVMdqjyhphcKQaQReRgA7NoSiVCb1IaTeyLo4AXnr7ysvz3FvH3Ng0yvXvIZmKan33Nj2BWE//0b5pWdgjAopUwWLoJL2y05Tjy/6zKfVCIrV8JIwvka4DeI7R9iGv83sY+zSt27m9r0kyulZI9+j5k+ADrzidTF+4AnZZp2ZPhReDU/QiFVvFcgQsot7pqKqHF0E3uz0PXsvVb4dkidwezVLnXKXezJi+Te5zYm9KtKV0B/mLOWU2lKqLiImWmK9waupnJvazB6cGam7YSurY7Pdxy8PvaWQTt1K/HFgRy95Xnv1fGn40B2Op0+IxJwsfnD8TkDtjq7GuDKCPOJMBw/tQ1hWtKh5ZdeRWsKf/qL32AH5y1QhpVMWhrtvtzxZp/Im5hi3LdZblKen5tQTwtvzaxjBnfMx4xnFNe9q2qdKhK6nBW5KpKl6p0q0qPqiSHQ3SiI0nqB7newA2hWBId0vw3iv4AHyI1eyDfFFCuBeScsvazkY5gOq2mhKu5qRryIu+a1fV7iM4WG3SzvExUZ5QRgEleJZDAmqgGpOklajvyxbn+9WiaWaloqdjyawPsW+Bpqgz/d6tyD6woyyxGelWN2PT4doEy7Ji50ApYcHWhjcld5gxY76sLJX60QewKnF01w02RwP/pyY6YLPn87LgqN7DISiJGAfcR5VJBcvnCdxPb4Pn9aSb3EXtlDyLgEtgOceICbbgzVaVNVdqNBTF2AOzMN1cAQbAgX2ZH+y2OmEFEnwHgZhc1RWQFKihtsTBSD3Z0p+CW3oqqNhhEUeystnChKh8G6M7UpsyfmeNgpQ2CQFm1bA5Ix5+ZfU4j6gxUGlpw7NxJb5pyWFAkH2vYqT11FzQad/KKixfWS2pKAxUu
*/