//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_MAKE_DYNAMIC_IMAGE_WRITER_HPP
#define BOOST_GIL_IO_MAKE_DYNAMIC_IMAGE_WRITER_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/get_writer.hpp>

#include <type_traits>

namespace boost { namespace gil {

template <typename String, typename FormatTag>
inline
auto make_dynamic_image_writer(
    String const& file_name, image_write_info<FormatTag> const& info,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_dynamic_image_writer<String, FormatTag>::type
{
    using deveice_t = typename get_write_device<String, FormatTag>::type;
    deveice_t device(
        detail::convert_to_native_string(file_name),
        typename detail::file_stream_device<FormatTag>::write_tag());

    return typename get_dynamic_image_writer<String, FormatTag>::type(device, info);
}

template< typename FormatTag >
inline
typename get_dynamic_image_writer< std::wstring
                                 , FormatTag
                                 >::type
make_dynamic_image_writer( const std::wstring&                  file_name
                         , const image_write_info< FormatTag >& info
                         )
{
    const char* str = detail::convert_to_native_string( file_name );

    typename get_write_device< std::wstring
                    , FormatTag
                    >::type device( str
                                  , typename detail::file_stream_device< FormatTag >::write_tag()
                                  );

    delete[] str; // TODO: RAII

    return typename get_dynamic_image_writer< std::wstring
                                            , FormatTag
                                            >::type( device
                                                   , info
                                                   );
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template< typename FormatTag >
inline
typename get_dynamic_image_writer< std::wstring
                                 , FormatTag
                                 >::type
make_dynamic_image_writer( const filesystem::path&              path
                         , const image_write_info< FormatTag >& info
                         )
{
    return make_dynamic_image_writer( path.wstring()
                                    , info
                                    );
}
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

template <typename Device, typename FormatTag>
inline
auto make_dynamic_image_writer(Device& file, image_write_info<FormatTag> const& info,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_adaptable_output_device<FormatTag, Device>::type,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_dynamic_image_writer<Device, FormatTag>::type
{
    typename get_write_device<Device, FormatTag>::type device(file);
    return typename get_dynamic_image_writer<Device, FormatTag>::type(device, info);
}

// no image_write_info

template <typename String, typename FormatTag>
inline
auto make_dynamic_image_writer(String const& file_name, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            detail::is_supported_path_spec<String>,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_dynamic_image_writer<String, FormatTag>::type
{
    return make_dynamic_image_writer(file_name, image_write_info<FormatTag>());
}

template< typename FormatTag >
inline
typename get_dynamic_image_writer< std::wstring
                                 , FormatTag
                                 >::type
make_dynamic_image_writer( const std::wstring& file_name
                         , const FormatTag&
                         )
{
    return make_dynamic_image_writer( file_name
                                    , image_write_info< FormatTag >()
                                    );
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template< typename FormatTag >
inline
typename get_dynamic_image_writer< std::wstring
                                 , FormatTag
                                 >::type
make_dynamic_image_writer( const filesystem::path& path
                         , const FormatTag&
                         )
{
    return make_dynamic_image_writer( path.wstring()
                                    , image_write_info< FormatTag >()
                                    );
}
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT


template <typename Device, typename FormatTag>
inline
auto make_dynamic_image_writer(Device& file, FormatTag const&,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename detail::is_adaptable_output_device<FormatTag, Device>::type,
            is_format_tag<FormatTag>
        >::value
    >::type* /*dummy*/ = nullptr)
    -> typename get_dynamic_image_writer<Device, FormatTag>::type
{
    return make_dynamic_image_writer(file, image_write_info<FormatTag>());
}

}} // namespace boost::gil

#endif

/* make_dynamic_image_writer.hpp
JxBIgrDyVxASrfNgj8MF9Cgca35uULzfLvcAGl6iBCLno7JgY7CmskbrpVLdNxIQrKElWzkIkQtP01CjTWVKqvLxXwKQfvEHU4+jjPNG7ftVbxrib/Wj+9gKCLrvz65N4u2x6TRobbl+Gnb/8tuzqWPbuTn+pWA37o3Om2GvpAKwDz8IUJY2Me3i95OuzrIEf9oVtY91+AAd8boq51H2vxT4qZLNPV8W0dxuNkzUZsZF4ue9EANPPlvhCcTCo/bVu4BBDrd3nmM2/Ua0fLV3f5eg/mAAr3v1LmaAL9rXyTYN2OdT4YA86W/OXbeDRxlP+Jl9CA3pbSIX86aXS5urdc9GnZ6Zo+E0WeMKc1ocxWrh/miXPiBxuafvtQV0+ghTxw19W89ZVndPgH6X/8FGZqbW2y7d18/qVPM0rDEB1vc1Zc6IFUOWtRTIy+u3gOSMHzsACSmqFafzpoybxTRxCpoKqXl2zXKpRdKfOSJEXPv9NkfjlCUa8dWDTzHoHSBVqraHMVjH9U16j3uaE1h55m03S0FkeflSKdGJIGyx1V0SGlhhMErw9wTpVqUzIDykF7o30zhmJ01PZSMaHS+hYen+wepwj/RwlytFcQKhZXGnVgn9mT++ePDmChhDOUh/+XZTfG/Eb3s+qJmd4gviTBC36/0jHiRiqH7Mae4SghXO1kYtijiCCRGWv0HouLizDn6zUxWiKy1qPeBz
*/