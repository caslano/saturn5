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
00nO3oWeqHAkhVR6Q46CcOT/ijw+hkdsz0K6gpbxzAYfVD8zEeYfrCpeS4qXBpZkZ6ygg7gKV9Lce8qpHcPDehTU26tITFPiCCGuNV5epU16k72MyYaNzxOk/eU47pFDugSyT5dAWmMJJBFLIKlYArHMNhZBzxelcjyXoOfGZIhfIxhHrIKFBjfrPIFw//4g05pfTDworb+zUSa3f51J7X86CT0fNoHTJ2N4PU2wP4tzvVUOFPZA7Fe+hMRyEqrdqbXvIQSyYmRwvsb7/ttZ/RD7UHtdeOmGprqqccWjNTLdNWFP38OlcFbbSq2PE36KfiQEKQX3MM1Fy3WULeSokvmshaySqIlLnbGQkdUR+qswYU1h91CUBF0LSbRNcWkaV7WLz3zedXxuN+Z12gHJK7vOY7CExs5jWlcnu4pw2eYqyg/pcIc2xHQatDwLtSY9NcmzGel3s8DutYjOmSeztd6WAjOi11uKv2aZ8RXSf4caRdIlpViuoGVNaZ3af1E6GsrHl3Ujcy6M3vnxB00xbX2lW8SB2QYMliqHGTt3s20enoIF41E16M6rIo6TzmoFqxLuzI9NDioqaOTJL2jAc1faiXaW3AvtHFguJeBZkIzpK1DS/iZFdVHq6KXiPaPdLueEAR6afjpffwlB/vsv48/zxC7e7OT6l5qg5LQPgjtHNZJKCwqjiS3sa5uLdPAGRnrOS9sCnK8GCkt6KjlgQ7gP7GXDjLDdJgMtc9L3IdMZkmmH5WtE8s2Wfcl5h7htbpOS4Xx1ig22pT7YJDZuCBmQqhQmi6HGzF0C12DC1YJI9VOksiLh3DfQs1bykh8svrgLOgI9EkD2kuL5DBCz0wMdPjLPP2tLb5HL5L4G7x9YbqG6NHX0IkX1rHPCGhjHiDrOtdHzQJCS0VkjHgDJqGZFBPhvvAF2c4WA5Uim/ygwyc6UImyzLFHWbOtfe6X0wk6qQzBGI9/hr9lfnONwMD9kNCgOczXs2u/dXexH7mcYOHJ/VlWO/zRd2ciKZ9l2XFWciF25zRwPjs2uQq2dwLYTulZ5Kjt+A/wcc7khdxa6H94PSslNGZ6Gm+EprsO8DsG+ZQYMMNzHKR/ve/KLCDup8bmJlcWw8E2cPYin1MomRHzIqCxG+uNzu5HqOuday3WXZJ6LCgIOxsBfPPTVyyC9DNHLcL1k62WcXibqZbLEnqIPcVXk0loviXpJ1UuGXrrppa9eBuGC1+CvsesJdrZFujdl7WB2cVGtD17xyJ6rIN2BUtb5anWvA4KZzweZx7qPb9Z3WZDDTcUZlfvLZgbjlfU+m/GsWoann5KPriE5JC/BHFIedsiZ42EQwJ0n9y2nIMw9B/fGCkTSnQmfy/q3puGJeuAsG7MiOQd/5HatusksuKM9f30lwDHsBXXZVOMeGUC1gL6N95dIyY3FPULG36K2dDmguuWzQB+mre4Eehr9npDtc0/guI2eiaN43l5hK4nnvjsQY272MIydgtgFMyDxEfQIBSFU5wDj3Sd1O8Mmte+/sP+Kx72wmP4PHuFOC/au9ZEK4vP8JyRrFC/m2OEk7d/5uACppvXHalE6PVAfYg+ZiylRuqs41XVvEaJHPkDDR6MMpK4iueKGN8/9JLpJDCQxd1TE/FAHQ53GUSG8DDvygoCskwhKnR9kBl1abQ/6m4GA+dxQRPvbN4Zzx+GYNco7ElfQxon9FO6teBhVvF6k2R0uYlykGC8iWwhwBEpAHwm4xIB+DND2u1POKbhNjMFbAHWiY1hd5HlUzU65I2PC8H68862tjP278p4MyCoAXzdHZojx1FYOO0qp06XA+3UsEiavTM821mO/hPiIzWUVl/W/nTriQNs=
*/