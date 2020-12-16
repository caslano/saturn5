//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_READ_VIEW_HPP
#define BOOST_GIL_IO_READ_VIEW_HPP

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/conversion_policies.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/path_spec.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// \ingroup IO

/// \brief Reads an image view without conversion. No memory is allocated.
/// \param reader    An image reader.
/// \param view      The image view in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename Reader, typename View>
inline
void read_view(Reader reader, View const& view,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_reader<Reader>,
            typename is_format_tag<typename Reader::format_tag_t>::type,
            typename is_read_supported
            <
                typename get_pixel_type<View>::type,
                typename Reader::format_tag_t
            >::type
        >::value
    >::type* /*dummy*/ = nullptr)
{
    reader.check_image_size(view.dimensions());
    reader.init_view(view, reader._settings);
    reader.apply(view);
}

/// \brief Reads an image view without conversion. No memory is allocated.
/// \param file      It's a device. Must satisfy is_input_device metafunction.
/// \param view      The image view in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename Device, typename View, typename FormatTag>
inline
void read_view(
    Device& file,
    View const& view,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_read_device<FormatTag, Device>,
            typename is_format_tag<FormatTag>::type,
            typename is_read_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<Device, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file, settings, detail::read_and_no_convert());
    read_view(reader, view);
}

/// \brief Reads an image view without conversion. No memory is allocated.
/// \param file It's a device. Must satisfy is_input_device metafunction or is_adaptable_input_device.
/// \param view The image view in which the data is read into.
/// \param tag  Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename Device, typename View, typename FormatTag>
inline
void read_view(Device& file, View const& view, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename is_format_tag<FormatTag>::type,
            detail::is_read_device<FormatTag, Device>,
            typename is_read_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value>::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<Device, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file, tag, detail::read_and_no_convert());
    read_view(reader, view);
}

/// \brief Reads an image view without conversion. No memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param view      The image view in which the data is read into.
/// \param settings  Specifies read settings depending on the image format.
/// \throw std::ios_base::failure
template <typename String, typename View, typename FormatTag>
inline
void read_view(
    String const& file_name,
    View const& view,
    image_read_settings<FormatTag> const& settings,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_supported_path_spec<String>::type,
            typename is_format_tag<FormatTag>::type,
            typename is_read_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<String, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file_name, settings, detail::read_and_no_convert());
    read_view(reader, view);
}

/// \brief Reads an image view without conversion. No memory is allocated.
/// \param file_name File name. Must satisfy is_supported_path_spec metafunction.
/// \param view      The image view in which the data is read into.
/// \param tag       Defines the image format. Must satisfy is_format_tag metafunction.
/// \throw std::ios_base::failure
template <typename String, typename View, typename FormatTag>
inline
void read_view(String const& file_name, View const& view, FormatTag const& tag,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_supported_path_spec<String>::type,
            typename is_format_tag<FormatTag>::type,
            typename is_read_supported
            <
                typename get_pixel_type<View>::type,
                FormatTag
            >::type
        >::value
    >::type* /*dummy*/ = nullptr)
{
    using reader_t =
        typename get_reader<String, FormatTag, detail::read_and_no_convert>::type;

    reader_t reader = make_reader(file_name, tag, detail::read_and_no_convert());
    read_view(reader, view);
}

}}  // namespace boost::gil

#endif

/* read_view.hpp
1JX7I7ymr57Uc7G3U/ZcnCFFFWVgsVH70ZGa6Dgkav6Y6XBIAp9zYon7mbKa8NwbgoDYhrMFZLs8Uy6/KAbo3eMcHw2hN9ETCl0O6ByBDiV0H6D5e7Lq0v6bGfjvI1baNvqtjmXXV/Is+0b/9+YHFCOeD3hLAPvMsTiYQLHyN6dIzRuvw68Up4gWhaXy+MtIy+WlRbWoN//EtDsxt+gMLn8yUP1x9bCwOJEhjf5CSBPsuGfH8C6MDoBn3Qx4F6VA9jco4A/DkD6oTftHfHOcsckh1C5CSHAfFUiBf3m68R1uWCrmeLHbPBnE1QXqnibocJcARWgo5M6/wynk9rpTrzhX4rJpGquJz96hiQ9H4lRQj80h12ltq37pszh+Sb5iLWJmxQu9XtR7cgbL6f+T2ZlMsCHtv0vULhi1NxsPk5XAL/GOARFtTQ5xl/Q+QHXY1QIRni6RRcb5QKKPKmAAcdOPQNw51OFA2u68k1Ch9LeEQmo6/ZhOY6SDMm6LVKWr5jwSCXFDZt5QyXx+ETPfyQHZQQgB24WlhWjFXEszf6JI4iB2xo8s4VBLNCci44iYxCdtZ8UvwYSfumrIXDNqWIVsFm3TczrInHS8HCkAH5SctqRi0HUDkmMXkrRHhq6NhspgIMdnTFyo9rY9IuOB8BB7/NEjMGR+fnjCtRwcy1gE1tP+dsUYQ118OJJ6FiNo41vuE/COevf8IhMiGWbi1qDhlSEyaJiFfH+PsM2h5Z+KJmMORXh+ePytUp7vJcqjACFZaikmDJI9CkwEag4+2sOeCoeTwqHeuRPnO3iF0JCFrP6Bx3SgeznPvW2VPNKOK41O3QtBvhwbGZEy5Gi4n2X4AYFJkN9T3sBEyXISMQYpRm9iFAKD7QoUdINHi31GR7rZp4LxDX84F/RJzz1fy52HtiCW5/kN8BLJqr4mdM9fSOhRJpQ2jQyCszjhgg4SzX/cKwzyqD1iZf4Mu9fiz9js+A3Ofmkc1W/FfajvnKpC6ZvvFUpviGT78tdqx8/GUTZYWvhc2nDvkFbng9R6v7Lvn7ILO0Jj/cRYaweLVL+kMaiL8WYeX6+xSqIqYt2gsYoZawZipYJYKUl7OOh5YV2QJiqUqGZCW0pw+RbBv+QYm0KxORBRPEv6pguPzdl/YRCzCxe0XYnkJ9fCMIbEza7hkTseQBTgfHAyHBaS5z/tkMSzB3H/Q5PdVYpixAy2iLhPqNMInxxzPM7+eSUTAh01rftOVqHjoUFCx/2iz4LdgY/WGegcrX6PNIenS7XgC4AbRlWD9LGE8tRw5x9xMsL4pEoM/Bew2P417uMal5PC+yTAtcHRL/gteADxowiG8VzCG4Jrp8N4w2/0ig/V9Bl+iDhvplsOHYylnhG8zbLvKZn0yk5KOmeeUhOdBX7i4rxxlV5MczLkdBCh2yACVztFN9Ukn0OyhvT2QVp6S2CRBh5FYFFIZ5uxUkx/TYDdsMPPGkgV1Qc39R11ZPnxc8qR1QM/YQevYElbzdArPYUbNesnQzqPXTdQ0r2EoY1Q9KMkfY8Y4Ur+d1Gag6dws8ZKQyzzxYEC5cD7lhC7168QaE5R6CWANhfoFkL/rlAWu5ZAvya0j0JPsR0cInQrod0UGmb9BbqN0LaAitzqOIA0PHpKFIY7zylKLa7nZuFgGeXrrQHQKFuBALbHuvNXC9snNOf6h2Id/0NlJGeAJSOnnFWa9XTA5WKlWOz1dRmbzai/bZKov1tRPZGoFNgu/XDgstIIZYXihizcxpJcf84ESFnfsXCYTahShpcAg9SvzS9MbeJDNXzGXWL1k1bsM3rGI3qsSFZVqfpZt7i5wVeRexfN/Wsr97n9HY6qIhs=
*/