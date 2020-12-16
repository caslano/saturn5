//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_MAKE_WRITER_HPP
#define BOOST_GIL_IO_MAKE_WRITER_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/get_writer.hpp>

#include <type_traits>

namespace boost { namespace gil {

template <typename String, typename FormatTag>
inline
auto make_writer(String const& file_name, image_write_info<FormatTag> const& info,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value>::type* /*dummy*/ = nullptr)
    -> typename get_writer<String, FormatTag>::type
{
    typename get_write_device<String, FormatTag>::type device(
    detail::convert_to_native_string(file_name),
    typename detail::file_stream_device<FormatTag>::write_tag());

    return typename get_writer<String, FormatTag>::type(device, info);
}

template< typename FormatTag >
inline
typename get_writer< std::wstring
                   , FormatTag
                   >::type
make_writer( const std::wstring&                  file_name
           , const image_write_info< FormatTag >& info
           )
{
    const char* str = detail::convert_to_native_string( file_name );

    typename get_write_device< std::wstring
                    , FormatTag
                    >::type device( str
                                  , typename detail::file_stream_device< FormatTag >::write_tag()
                                  );

    delete[] str;

    return typename get_writer< std::wstring
                              , FormatTag
                              >::type( device
                                     , info
                                     );
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template< typename FormatTag >
inline
typename get_writer< std::wstring
                   , FormatTag
                   >::type
make_writer( const filesystem::path&              path
           , const image_write_info< FormatTag >& info
           )
{
    return make_writer( path.wstring()
                      , info
                      );
}
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag>
inline
auto make_writer(Device& file, image_write_info<FormatTag> const& info,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_adaptable_output_device<FormatTag, Device>::type,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_writer<Device, FormatTag>::type
{
    typename get_write_device<Device, FormatTag>::type device(file);
    return typename get_writer<Device, FormatTag>::type(device, info);
}

// no image_write_info

template <typename String, typename FormatTag>
inline
auto make_writer(String const& file_name, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_writer<String, FormatTag>::type
{
    return make_writer(file_name, image_write_info<FormatTag>());
}

template< typename FormatTag >
inline
typename get_writer< std::wstring
                   , FormatTag
                   >::type
make_writer( const std::wstring& file_name
           , const FormatTag&
           )
{
    return make_writer( file_name
                      , image_write_info< FormatTag >()
                      );
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template< typename FormatTag >
inline
typename get_writer< std::wstring
                   , FormatTag
                   >::type
make_writer( const filesystem::path& path
           , const FormatTag&        tag
           )
{
    return make_writer( path.wstring()
                      , tag
                      );
}
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag>
inline
auto make_writer(Device& file, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_adaptable_output_device<FormatTag, Device>::type,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_writer<Device, FormatTag>::type
{
    return make_writer(file, image_write_info<FormatTag>());
}

}} // namespace boost::gil

#endif

/* make_writer.hpp
eD62g3g+29TCsxTxDNjvYf/XVPHs3NSG5yo7ni2bWng2i1E8H1gueB78VvA83uZGeB6rZeJ5z0yH1P9aNjx3z7ThWfMQ8dxR34bnxvo+PH/YLnh+1MTE86daFGpWfT88h2wn6WOSiOfFbwTPWw9b7ed6xXPfPuK5A8GKZ8Rh4nl3fX88WzRRPJPV8LpBE+JZZTvxrNvEwjOUeH6/l3iWbaJ4BjWx4bnOjufhxhaeu+spnoHLBM8PIQ7PyWh9Izw/qGnieXmGQ+p/TRueuV/b8Fx1gHi+Vs+GZ049H579twmeaY1NPHNrUqi+9fzwjN5GUjpJxPOrmYLngYNePI0liudEAhD1GoIVz7yDxPNSXX88DzVSPM9uFeE3NyKe+VuJ5/pGFp5imfXIHuI5v5Hi+UMjG56b7Hi+08jCM7eu4jl7qeDZeabgmXbbjfC8u4aJ59dfiUhta9jwTJhhw3PkfuLZtq4Nz/i6PjwrbRU8r8SaeA6oQaEiwGHhuW4LSVejvfZvX6v92wFr/rFI8UwkAFFtEax4DjlAPGdE++P5dqziOQ1p4nFsLPF8fgvxHB1r4VmaeFbYTTyfjFU8+8fa8Cy045kSa+GZEK149lsieLb7WvC80vJGeF6qZuLZY7pD6n81G54nptvwbLqPeB6rY8PzYB0fnos2C54zG5p4tqtOofLq+OGZvVnWRUginqVnCJ537PfiOe43xbNwF/E89pUXz+j9xLN7HX88kxsqng8iTTy2bEg8G24mns1xb+IZQTwX7CSeNUAlnpUa2vA8a8fz3E0WnidqK54VFwueZyAO181a3AjPGVVNPMt+6ZD6X9WG58df2vDctYd4flDbhuek2j48n9skePa8ycSzYjUKNaS2H55xm0jqRRLx/GW64Hl6r1Xff1U8pxCAqA8QrHiu20s8y9T2x/NsA8UzGGni8TAecU7cRuK5v4GFJ78dG8/uIJ4rGyieixrY8Cyy4/l5AwvPj2spngsXCp5fTxc8e8bfCM/uVUw8538uIt1dxX7+7xc2PCfsJp5317LheWctH571Nwqe5SCQ+muqQqGia/nhuW8DSeEkEc/HvxQ8P9vjxTPVxDODAETdjWDFM3sP8ZxX0x/PaTGK5xykicd3YojnqxuI55sxFp4ViWfd7cTzxRjF87kYG55V7ePPLjEWnul4n6yPLtD+COLQn9mtN8KzTGUTzyenOaT+R9nwvDrNhmf7XcTzUg0bnmdq+PDcuF7w/LW+iWdeZQq1roYfnhPXy7yYJOJZ7QvB84Hd1nhpvuLpIABRlz734hm3m3g+UcMfzwfrK54DkCbn//WJ523riWdSfQvP6sRz/Vbi2aS+4lm/vg3PmnY8Q+pbeF6trnjWy9P+6AvB89e4G+E5L9LEs8ZUh9T/SBue30y14Xl8B/GcUd2G59TqPjxz1gmeg+uZeL4XRaGyq/vhmbhO5sUkEc/l0wTPwF3Weq2J5ywCEDUDwYrnvp3Es3p1fzyD6ymekWpLfq4u8Ty6lnj+gXsTzxrEc/QW4rkTVOK5sa4Nz2g7nj8i1MTzm2rm+vffBM+yn+v69y03wvOJSt717091/buSff37MxueH22X9e9qNjw7V/PhGb9W17/rmng+HSnr39X817/XyLwYJF3/nqrr3zus/mieuf69Rda/p1rr3zuI54qq/njOiTbXv9fo+ne0rH+vkfXvaAvPmsSz+Wbi6YpWPHOibXjGKJ4LgSdXpzK4OpWhq1O27wu0pp6j41H0EEaDH2kxU44B40NpX9lQzYwr/WhfzVoWv5PLwOXx0ja1yiEHSGB5My48hgydKgpa2cw8JXEygir/dsVTUk8LK5h6qj9Fsjq7gk0=
*/