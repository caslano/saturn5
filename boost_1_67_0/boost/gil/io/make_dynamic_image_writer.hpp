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