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
M6oR/7I10v52fj7jbYf19+bb2ZWbtfblXV5/9mN9eYd8TThQYtt0mpduMvHN821NPY096wJlsGv0JP32AbK8B3w7mDm50WCFCmsG++SWyI7C2sAuEuqweQY7y/DtL2ADnc+pWK5MdXjn8yvIn1uVkk0ppnEkX/tzLc7eu4mJZ2+9q7x+OELxhOu57sg6JrP3LK8yfNZ9MFqTsjxOXrimKU7jNPIONnVSe/2ap0fLpy4jDDrm81N+4vCZYjLvLrj0jmA6RtWV7+iWpXwMW861GR5TBFVWbfmpoVtXSLXlOkULl/bNavJXfDfk8PW2d60wtlq1+UaXrzuYMDPtucmlm2FkFG3862aXxwbfzE6CGstbNK8OEap551aHx7jPtrzbHLoJ8UVnVMJLczJrhNs3xBu8U9oTVtKWf4fzTLoV9n0Oh56WWC37mn54Xxv/twcNrH270+Gz3aZilSpPP287+xXqLoO7HD502KyE1JrP4THxT1uqU6bDRxd2Rz7E+P75OnAm7Jjdq3gC02yY+BvJpfe033ef4sXVt/3+gMJTJjSiZf5BTXdkXs8rD7t8rryque/RbN4iVz8ez6bjlnR3Rk5PRh5+7eGxcfqmjNw9pfh0iD1d1m8dutIdOw8+4+FxB1iPnfu+v14Qp/N8zs2THINbU8OBy+Sa7w4BMwxBltH+oMkXe+t9h8PltzL0gubvT+/dMd6A3k/svz5W7tt6Bsw7oHYa3m5c8qx56CWH30il7YdXHLo972OUgtnayt7vHF7O52g5sHLze4cveIkykmMlqSr28se8/CnC06uDSSnVasZkWjpm5z7TFRzPSvV1MAXayit5Gps7pyq/OjMfvOXQu1OrzH6tzczyvu3hNW/XWl47T7u8fT3dnF20ffuOpvdj59/TfBuw826erp2f6Lc7auiD5U0vo6Hiig4vc4LdgLBxRYenl5Bay8oN90lvT19Kn/X5i6bbuUDyts+dUwo8OhO+Q7OctnvsC1ocjCHtZriDflpJvE/158cjss9eMT+Z43WhI6rOUprzFs3NVMWu3+29JOG278qurLaeYXxOxwe2z3YaergJ7LwHe5yh+Xxjt07uOzrxkQq32gDdydvogBnq3LYiKJ1ottgYbzpfXhHRtsTN1/XB9Vld6Nb/Hu/U1+d7u/2s/W6nvXn96S00nRMFjcFoOecMQ3pXJlyrY7Fbpp/vI06vztaDWf9cy9RI004uVyIiHQwaC8wgWoAsN7bTz874Gx/e9sc2przAV9bOQKvaK/qE5qFh+vzEJYMdWriN2hWYCdtn2+nnbcegQ546aGNvD9+qugwyvGp9YPt2cBatNQjXN/eqsRni0oP9QdWXQyP6BtcNwzRfaDTaWlvMbn06r+0zPEWZt1Hs8iHzfkaGj9BJaEesXo5UNNQ62Ri+UL68RetXgeLRyy97TlnTw3OrLd58xio+7XfZ2JxLpxHjfTQz1xkW22c75fDYs8eWZ7zm4SiGzUjtx+zs4VE7LdIfHzrCHY1wqTHfxfB512MqprNrxLfBdVu6LRMUv3Os3/bpboqHcFtXj7LXu2uakcAdHNsHjVHMyPdE9Uz6TRWt659U9GBTzE4Wqtw9DY9eS3rkPlSfUOAcuS9webRQ6v0Pl89UWNvKSYpHLfX1e9KWruddvQ5zedy52ZkDfWtk2zeTVX16uOTd+MnO8+Y97MZov30HH315xifey+TpXXN76+f6YV4dM36k0THVp0UOjzGCTjkO3ez1pHmm6DzYiVR2zdcftid1f5WYPJy4gK3HVEV3l4y+urq+m1sPNxag9NSlY0rQVqMTjgxZB8YnE2uMTPjGfI0a8+nmGU5XRXF9pmzt4xQ4z8M=
*/