//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_RGBA_HPP
#define BOOST_GIL_RGBA_HPP

#include <boost/gil/planar_pixel_iterator.hpp>
#include <boost/gil/rgb.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>
#include <type_traits>

namespace boost { namespace gil {

/// \ingroup ColorNameModel
/// \brief Alpha
struct alpha_t {};

/// \ingroup ColorSpaceModel
using rgba_t =mp11::mp_list<red_t, green_t, blue_t, alpha_t>;

/// \ingroup LayoutModel
using rgba_layout_t = layout<rgba_t>;

/// \ingroup LayoutModel
using bgra_layout_t = layout<rgba_t, mp11::mp_list_c<int, 2, 1, 0, 3>>;

/// \ingroup LayoutModel
using argb_layout_t = layout<rgba_t, mp11::mp_list_c<int, 1, 2, 3, 0>>;

/// \ingroup LayoutModel
using abgr_layout_t = layout<rgba_t, mp11::mp_list_c<int, 3, 2, 1, 0>>;

/// \ingroup ImageViewConstructors
/// \brief from raw RGBA planar data
template <typename ChannelPtr>
inline
auto planar_rgba_view(std::size_t width, std::size_t height,
    ChannelPtr r, ChannelPtr g, ChannelPtr b, ChannelPtr a,
    std::ptrdiff_t rowsize_in_bytes)
    -> typename type_from_x_iterator<planar_pixel_iterator<ChannelPtr, rgba_t> >::view_t
{
    using pixel_iterator_t = planar_pixel_iterator<ChannelPtr, rgba_t>;
    using view_t = typename type_from_x_iterator<pixel_iterator_t>::view_t;
    using locator_t = typename view_t::locator;

    locator_t loc(pixel_iterator_t(r, g, b, a), rowsize_in_bytes);
    return view_t(width, height, loc);
}

}} // namespace boost::gil

#endif

/* rgba.hpp
Ad0R4rFo37dvcNS+xOTaLpwLZo7eN0DvkjfJF4TKHuabgLnyItefk2eJouvnW/b7pvt55UUH823ArPiTMOv7e+e6b/uO5Wd1oAUWuqy4yDxn+3Dtf3e8cFl/zUZjuPH5LmDmHR1HYx0bYuHeSd34HH5xN4dbC0t+wypp6GzxSmp/hGhHm2t/mGs/otrBZAeAJoJ5vISx30gw1ufg5+AzzE0Wn1xrT0bxSe5zcOdbQYfs3sMdxMbm4syFLffmNb6rV7dRcFZJZP38WbdDtes52enH1MFt3HYC7vTW3oL1NbvdBIwbYvRGcJen4NyyARzxfuj2E3BoH3i6NNGO1YQ+Rphb30HCkIbO+N6bgnFBJNwX4oaG21qsrcPLpfNLdDAvvCPBHFxIl/U5uxOH71Vzxx71ubcEM9HnYpzzP0t4N2pju7kzb6cRIXq/kO0L8DRFkN6pT90F8KPPBb3r/rn73RWT3kcSvNPcrjC+Z//rrh2c7da5E41+Dxt3Q9t/PUshswz9/E/Y/tzlb8LnDlmcm+k9eH2bDhR6V37E3S3MNur+z20SHxvaj9ax/ceqfQ/6Pfc5eO49bPuBTI39dHCwW/FtvT8nXlfuudzuxotofXkChh732Xff/l7LcPP9xTk+9lcmYLjpjff3iHtPwMKSxMfpKsG4peUOo6H9gffR7eCc4V9Zbt+Hix/zfdDt5LJAfbxPw7ivHtoP3aTa3VcM7Zd0e++GRGv59vdz7XaG7UixfXepb0McUNfqvn7k//j90c7vPqyn7dd2Jc9pTo4/UMHAy2Mb4RvsDiPYjz54Gtb9ccHvk2ccVrDYEqxIF51Xv5yC23z1nH9H9jAF4yoB4muJt38RzHSBd7GmH+lgJwuxY/873q4+ysG54cXET51bYGePvvsRj3Y4E0XA+fhcf4yD45ea9Y9EOV1+377hsQ5O2j+p/YZrd3IXzcR9hvF9nGvvsEbfuZXHu98xUGepzel33K8TkXE7u5gL14blSm3p5l61vtiLbeycbRtstj8T9vUoP9n5bs4uDO2/XGrftFN5YbAx/wPtZFfv1sNFu3PdyhnpPLGzv3cORc95bnsyXtufg9JZsns/RbeTd+Nsc4B5+gSM2+IE4ykYytsOmMc6mGQKBocb5Yo9PdrjKw2LW73bGxiDob+TB/WHsUDq2/VuLTnYF07A9uPWzcz6APfyA+BW+kBJ6m/jALijCu4VCk55fRLc/EC6nSPvbPjmVx/Un0tyz7/5DQfArnSFNGG/dHCXR7jnxyfz5EVrxj/p1wB1Yun2JjJ2Yr84+Gsd/NbqxprFmSXDnH117AecQ/w4/YrNM+pt5kcE0x3Ui2Gd/sL97hzfsJO7e3FnaP81tfPMwrOdgfbhB7o3EJeIZZyxcU1depCEodliY/bTOwkYrDrXT0/v3AB36C4a7ugk3PX7K5r9ZbB/AacpJusc8f8QBUdA4zeeuo2D6USaDZZbmd6o8PC23A/+x7kzjrEEf36WsnuHeQuvoa42kKv4RVWzVf0X8imfCb89W9OnjAIEZPz/D0ubF3j8bMb7qzx45yHECP6AAHXpIaRf1wslfB3hgRvvRxbeBVpKm9w5Dn8sTdoqxpux1/sWHu3+Q/UV6H2X46xmBTzNijTyns3MMc8m2/azVc2mOoSxEC/S+pgHbo5/UlumYgXOjcelXecq7wflZVDGHK/goYszGlIhP5ls99aWcQ+71si+YIPV+ylfA43BuGDhvgF5cG91Gg4C+MVOB3I2ld8e1J8915k5xerNBnKiu43i4XLQv7uLpfv9J+J3SNx2n+L3u2AE1IlFtwPXCx8Pv/67z1wBZGw/Vmtz9lgH8wOCcYfpCDPIGgQ=
*/