//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_READ_IMAGE_HPP
#define BOOST_GIL_IO_READ_IMAGE_HPP

#include <boost/gil/extension/toolbox/dynamic_images.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/path_spec.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// \ingroup IO

/// \brief Reads an image without conversion. Image memory is allocated.
/// \param reader    An image reader.
/// \param img       The image in which the data is read into. Must satisfy is_read_supported metafunction.
/// \throw std::ios_base::failure
template <typename Reader, typename Image>
inline
void read_image(Reader reader, Image& img,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_reader<Reader>,
            is_format_tag<typename Reader::format_tag_t>,
            is_read_supported
            <
                typename get_pixel_type<typename Image::view_t>::type,
                typename Reader::format_tag_t
            >
        >::value
    >::type* /*dummy*/ = nullptr)
{
    reader.init_image(img, reader._settings);
    reader.apply(view(img));
}

/// \brief Reads an image without conversion. Image memory is allocated.
/// \param file      It's a device. Must satisfy is_input_device metafunction.
/// \param img       The image in which the data is read into. Must satisfy is_read_supported metafunction.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename Device, typename Image, typename FormatTag>
inline
void read_image(
    Device& file,
    Image& img,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>,
            is_read_supported
            <
                typename get_pixel_type<typename Image::view_t>::type,
                FormatTag
            >
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<Device, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file, settings, detail::read_and_no_convert());
    read_image(reader, img);
}

/// \brief Reads an image without conversion. Image memory is allocated.
/// \param file      It's a device. Must satisfy is_input_device metafunction.
/// \param img       The image in which the data is read into. Must satisfy is_read_supported metafunction.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename Device, typename Image, typename FormatTag>
inline
void read_image(Device& file, Image& img, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>,
            is_read_supported
            <
                typename get_pixel_type<typename Image::view_t>::type,
                FormatTag
            >
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<Device, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file, tag, detail::read_and_no_convert());
    read_image(reader, img);
}

/// \brief Reads an image without conversion. Image memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into. Must satisfy is_read_supported metafunction.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename String, typename Image, typename FormatTag>
inline
void read_image(
    String const& file_name,
    Image& img,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>,
            is_read_supported
            <
                typename get_pixel_type<typename Image::view_t>::type,
                FormatTag
            >
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<String, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file_name, settings, detail::read_and_no_convert());
    read_image(reader, img);
}

/// \brief Reads an image without conversion. Image memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into. Must satisfy is_read_supported metafunction.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename String, typename Image, typename FormatTag>
inline
void read_image(String const& file_name, Image& img, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and<detail::is_supported_path_spec<String>,
        is_format_tag<FormatTag>,
        is_read_supported
        <
            typename get_pixel_type<typename Image::view_t>::type,
            FormatTag
        >
    >::value
>::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<String, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file_name, tag, detail::read_and_no_convert());
    read_image(reader, img);
}

///

template <typename Reader, typename Images>
inline
void read_image(Reader& reader, any_image<Images>& images,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_dynamic_image_reader<Reader>,
            is_format_tag<typename Reader::format_tag_t>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    reader.apply(images);
}

/// \brief Reads an image without conversion. Image memory is allocated.
/// \param file      It's a device. Must satisfy is_adaptable_input_device metafunction.
/// \param images    Dynamic image (mp11::mp_list). See boost::gil::dynamic_image extension.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename Device, typename Images, typename FormatTag>
inline
void read_image(
    Device& file,
    any_image<Images>& images,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t = typename get_dynamic_image_reader<Device, FormatTag>::type;

    reader_t reader = make_dynamic_image_reader(file, settings);
    read_image(reader, images);
}

/// \brief Reads an image without conversion. Image memory is allocated.
/// \param file      It's a device. Must satisfy is_adaptable_input_device metafunction.
/// \param images    Dynamic image (mp11::mp_list). See boost::gil::dynamic_image extension.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename Device, typename Images, typename FormatTag>
inline
void read_image(Device& file, any_image<Images>& images, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
        >::type* /*dummy*/ = nullptr)
{
    using reader_t = typename get_dynamic_image_reader<Device, FormatTag>::type;

    reader_t reader = make_dynamic_image_reader(file, tag);
    read_image(reader, images);
}

/// \brief Reads an image without conversion. Image memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param images    Dynamic image (mp11::mp_list). See boost::gil::dynamic_image extension.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename String, typename Images, typename FormatTag>
inline
void read_image(
    String const& file_name,
    any_image<Images>& images,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t = typename get_dynamic_image_reader<String, FormatTag>::type;

    reader_t reader = make_dynamic_image_reader(file_name, settings);
    read_image(reader, images);
}

/// \brief Reads an image without conversion. Image memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param images    Dynamic image (mp11::mp_list). See boost::gil::dynamic_image extension.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename String, typename Images, typename FormatTag>
inline
void read_image(String const& file_name, any_image<Images>& images, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t = typename get_dynamic_image_reader<String, FormatTag>::type;

    reader_t reader = make_dynamic_image_reader(file_name, tag);
    read_image(reader, images);
}

}}  // namespace boost::gil

#endif

/* read_image.hpp
SzMiATxGeXq4WLXlOu21IYsT00EkQ2ZkXXegBwk+el44PEpTDDDFDf9Q/ccUZ2QJWQf+WbWzfRmvKBhCbkOIOy9fRtC3hlQRt3NGet1OzmpKuPvpCiV88yxRwqGDooT7bXdUKGGPFqLkYBUl/C2gFyjheu9RCW85VEUJrzlUXQm/ukCU8NPHLSXcXMr88iF79HzvAgICBFAH/5olOvjK920d/I9ZsgZufrWQOnh9li7Ramd76j12tjcdqtzZXn5cNXA7tdaui0/I+3zRwDXxAWp0PO9kPx9UDdwdXxdq4K2/VNLA7R6XBrf5mGpgu8Pt7q6/bF3K/TUduWFnNa2beMl/0LqQgZIXw2FVvmORpsS6Sfrt4Dtn2Hod86Xo6b+IePxwItIsX39Mm2UKwjE578IKuPM3C8nNO2XFqwTV+zUR8nR4+fmwuku52Q7YwoBvEYD30efwXox3s6kdPoKwpYSNzo/AMgibT9hhG68LYQZhpTasLWHjCOtlx21E2HDCRtgwB2F3AcZ9+rm5EfARThU6AoyuLBOyXSAuJgaZFItaCP8O4aGGeNlBRLfWIZZpufAuPVNtfAViWsuk8Hp/wbnwBf6J4kxtKIeQgpzIgHO4OfliTrD6U/q0D6JL5nr9z/jFen3OFiCf3sL7OBFM3+WL0FDRgO5+3OXA5y2z8ekr+ISOujCXKGizHgmj+0Hu22Zw3yOc1qmbO+9Fhxg3zYIqzmroM1xIdDwQjZ1mOpINQWRZrcek/gB4eKpkGEqAIrqK0b/Hz1gPL9r0ir7NiGGfMLY+LB7i6PYe8dJIl7j8Ip57xiv2XbaM9LonbTYPf8IqNbGqVM+q0rvAu4pV+hrB4Q105yU+83OLa+SWX+mecQfEj1X78DxresvcwxUjnn0w4Cj+g10zCYsqreyqOw+LtYLvISyrFV7eRs+Q3Yr3OiQ7Se/NZ1C1IcgvNdD1aSABJRcoWUnI6EoMAV43zjHPHrHA3XBGhoQ1uWpI1+67jW/RLtkRNEMCoZ7AGwq8mEc0ThNEeQ9RjDkSw912q7vtBokH8nyFZy1i414ogkqshL5dhppzQBuPWtOZmXtGImqN2gWPyMS0ASqN6oKNschFqpvqkPrqSt/rWt/Pj1j1/fRXq74DO0t9fziN+j68TOr7IpCA8jxQsq7T+sa1RIGlvlLQHkbejZyl2xVNQsyQx6poXJwiN0HVuhtzBBNVrF673ZWrWLq0ahUxQe+KKnJhdAwqeBMcUqK6Z7SelfiZKfX7TOu357BVv50HrfpN6CT1e531K1gq9fsUSEBZCpSsWymsQzioKwmAO/hIYw3+eVpZuqAaS9ORRqgXEfuSpy9LLE0ibiJi+YwaqDZ4u8Cu9WY866TWiZKWpNQWf/sgvdMfs9q4ICKedwFo1TGsbancrSOzzDbtkQt8312/gZU/lW6Awfsi9afOhpsiq/6hSP1/idS/o9S/gdT/Y61/SOsPlKz26BDiX2mFDoFY0cACb6+uKPs6Y6ddZnodQAqhqnFM+B3uZUQnAR/MvtqmGCNbsRojlgx6tX7lqF/3sOX4Ls04Gsx7OxyeNfsKl4PP+ubwV9vM5TiB5xZ8e/CcwPM7nlI87+PJwGPfz1bJ/7jejNUkV/yOy9A/5tKd1AOlPnqq5p+OIOfdxzA2UJjXUzDKyZcBuJ0AvyxQWSruqdko+mMXX4scRDdTEcpLPfrTuay4H77erc6xR5mt6qvLaSwbQ3Xxno5p58K5ZXHjfhU/3dflWH66zSdq0mOxGfraHFNTI3tDawLvSx6hQl4zHfoYnxv5+Y7ps3AGhF41U/hu7Ao9b94qaZSFAuZ18rY/mANqms0t5Mzgw/yMF3w=
*/