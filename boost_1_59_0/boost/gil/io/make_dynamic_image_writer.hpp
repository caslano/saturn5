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
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
*/