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

template <typename Reader, typename ...Images>
inline
void read_image(Reader& reader, any_image<Images...>& images,
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
template <typename Device, typename ...Images, typename FormatTag>
inline
void read_image(
    Device& file,
    any_image<Images...>& images,
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
template <typename Device, typename ...Images, typename FormatTag>
inline
void read_image(Device& file, any_image<Images...>& images, FormatTag const& tag,
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
template <typename String, typename ...Images, typename FormatTag>
inline
void read_image(
    String const& file_name,
    any_image<Images...>& images,
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
template <typename String, typename ...Images, typename FormatTag>
inline
void read_image(String const& file_name, any_image<Images...>& images, FormatTag const& tag,
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
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
*/