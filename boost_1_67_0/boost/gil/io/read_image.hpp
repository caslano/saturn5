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
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
*/