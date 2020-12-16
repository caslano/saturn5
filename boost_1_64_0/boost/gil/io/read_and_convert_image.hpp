//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_READ_AND_CONVERT_IMAGE_HPP
#define BOOST_GIL_IO_READ_AND_CONVERT_IMAGE_HPP

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/path_spec.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// \ingroup IO

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param reader    An image reader.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template <typename Reader, typename Image>
inline
void read_and_convert_image(Reader& reader, Image& img,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_reader<Reader>,
            is_format_tag<typename Reader::format_tag_t>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    reader.init_image(img, reader._settings);
    reader.apply(view(img));
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param device    Must satisfy is_input_device metafunction.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template <typename Device, typename Image, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_image(
    Device& device,
    Image& img,
    image_read_settings<FormatTag> const& settings,
    ColorConverter const& cc,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<ColorConverter>;
    using reader_t = typename get_reader<Device, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(device, settings, read_and_convert_t{cc});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \param cc        Color converter function object.
/// \throw std::ios_base::failure
template <typename String, typename Image, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_image(
    String const& file_name,
    Image& img,
    image_read_settings<FormatTag> const& settings,
    ColorConverter const& cc,
    typename std::enable_if
    <
        mp11::mp_and
        <
            is_format_tag<FormatTag>,
            detail::is_supported_path_spec<String>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<ColorConverter>;
    using reader_t = typename get_reader<String, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(file_name, settings, read_and_convert_t{cc});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param cc        Color converter function object.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename String, typename Image, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_image(
    String const& file_name,
    Image& img,
    ColorConverter const& cc,
    FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            is_format_tag<FormatTag>,
            detail::is_supported_path_spec<String>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<ColorConverter>;
    using reader_t = typename get_reader<String, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(file_name, tag, read_and_convert_t{cc});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated.
/// \param device Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param img    The image in which the data is read into.
/// \param cc     Color converter function object.
/// \param tag    Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename Device, typename Image, typename ColorConverter, typename FormatTag>
inline
void read_and_convert_image(
    Device& device,
    Image& img,
    ColorConverter const& cc,
    FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<ColorConverter>;
    using reader_t = typename get_reader<Device, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(device, tag, read_and_convert_t{cc});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename String, typename Image, typename FormatTag>
inline void read_and_convert_image(
    String const& file_name,
    Image& img,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            is_format_tag<FormatTag>,
            detail::is_supported_path_spec<String>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<default_color_converter>;
    using reader_t = typename get_reader<String, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(file_name, settings, read_and_convert_t{});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param device    It's a device. Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param img       The image in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename Device, typename Image, typename FormatTag>
inline void read_and_convert_image(
    Device& device,
    Image& img,
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
    using read_and_convert_t = detail::read_and_convert<default_color_converter>;
    using reader_t = typename get_reader<Device, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(device, settings, read_and_convert_t{});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename String, typename Image, typename FormatTag>
inline
void read_and_convert_image(
    String const& file_name,
    Image& img,
    FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            is_format_tag<FormatTag>,
            detail::is_supported_path_spec<String>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<default_color_converter>;
    using reader_t = typename get_reader<String, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(file_name, tag, read_and_convert_t{});
    read_and_convert_image(reader, img);
}

/// \brief Reads and color-converts an image. Image memory is allocated. Default color converter is used.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param img       The image in which the data is read into.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename Device, typename Image, typename FormatTag>
inline void read_and_convert_image(
    Device& device,
    Image& img,
    FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using read_and_convert_t = detail::read_and_convert<default_color_converter>;
    using reader_t = typename get_reader<Device, FormatTag, read_and_convert_t>::type;

    reader_t reader = make_reader(device, tag, read_and_convert_t{});
    read_and_convert_image(reader, img);
}

}} // namespace boost::gil

#endif

/* read_and_convert_image.hpp
7OE6OCv3cC1qaQ93k9p/N8An9jfxYa/gptgL67J+O+iVC9ZvmS3PBztY6E3uvJY8SdTlWWHmFfgBM7+MlTNg+U3IzBVAlP6kSSVmHkAh6cQHWMVvYTndmDGdrARvLW4+dgbc3Dld7f7OVOHmqECV4cjCIg5HHnBUGY4MdVQMR7p9KlleHWtR+S0nKZoMDGs8cv4TAq51WCR++hkh8eo1keX0t94Nh0HeR74geUchVMn7LyBgfSTsqkTetTWVvNs/kZIvrUnyvoUPrL/WtAcQ4unltpUcQLxUUwcQs2taA4hd53Q1/XoejonnUnrl84DuFa1ld/T5qkz5DbTBGLAuRv+psH+oKeMlns8rwi19qZ300KY772g0KXcw6SQyoIhmuOHThKBwesGQ+JGzfMadsem4qS99eBl9JzKBL9NdYTpuEKFIPd/R6/pGbgPidVYJdKXoNRqas14WVxskbhQQPeEvYZ+Nc0R3Wjba3mT4tZrYPxX2H5gchuZBTyzT/r9MzyvUsfv/p63+f5n2/4o2QtFO1Lb7fwttMNFyu/aHWudo19coim5M02ro+KSRzmbob6K2dfblEafDuj/sirve4CG6uFikjVY+sB7Tzst13I+R41Akj6Ajp6rIXSmg+LS9X0D22q2i7AWhWOOvFtmjntmLT529WFbrEIEVS0UG3wCD9GY08Su1nJgqgxOWEvA2AZTBqOkig8mrIWI+aebx0szXm+YKSuGBaZarJfEJkGo2IGKcD9HpcElPn9wao7LYY6n6wcAn+hN8gEQt8QF6PBTHFtoU0Uiw7Djxr6TeXawZQvCkC7AZSpce+RL512iZcfwL+pGuXbyuIsvHUikdurQvDt3A+QhC6f/zpLBuc136/8xX/58AmV/jHeTB3YJ6QsubtAeXOU0agIuhCibq/E/ymhBd4cfT7XXBFVv/MoodhHF9R73xuGdT9cE7zxLCSU29PIi24U77QOOPOZ/AM8fkDsj8Ui3PxyzPuDwpTw2WpyvK48P9D8iue3GetBeHnBgTZXHyrApYqL4I2EGXjkf5VVXAdj5UIWB/LBABW3hCBCyrbiUBO58rOc84UUXAZuZVE7DNn1PApp+tImATz1YXsIEfiYB1d1kC1k26kn5nbQFr+hEBaQRQwF7LFwH7YaUtYJPfVQGbVkgBm5pvC5j5CZHijp6pLFy7o1S4gpYdND4xnlwiPFuPD9Di2ToUrs8RTe7zrVNduGb8VUm4gk8JB6ZbUpVuiFR5XbZgZRXH5uZAYvzG4cltcfs6nBvVnNgcOs5b8AX5tYKGjJ52JcZm+NCfllT053uprrXAg0ZMQqJEd88InkEtLe036Rr6KfJC4OJ1v9LWr2sKLtCv5vCnxPV7Vv0VKcrpDAdP5qHjV9XrdIjq3YzO1tbXlfRvoujfQxH96+0Eheh+dlCF8pX8q+jfRhfTv2Oq6F/ICrTvlS/8v9r3OpQu9DL249XYOu5PaQv/iomo1ZFTVa1GLxbt+6qi/XZc93dstNsstJ8+FO27u0wbx9Z60jiKdXq1i19VG0fjURWN45tXpXE8c1waR896TmkcKRSE/VMk20ePV2kcj0+t1jg+KGTjeKisSuPILKveOLqwIrD7d1iN45Bo305lduM4+wEBbQlg48h7ShrHF5/ZjePxV7Rx/P0TNo4RT1XVvnOIGLMV3UWFu7vCsEsayEYkTT2IT/iNwwdI9CY+QI+fYtlAXkY0Euz32OoN5KFj0kCULhsnS+QHERkCNwtK+z9r38cRivjtjum+KZI2A4gOUFOAzLum/Dfta8sv/b+ja4UsVtG/SZuofcdU0b7zn/sv2nd5RPv+s1T7e5bn9CQpz3SAzNWTpe0=
*/