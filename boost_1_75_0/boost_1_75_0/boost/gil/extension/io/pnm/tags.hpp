//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNM_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_PNM_TAGS_HPP

#define BOOST_GIL_EXTENSION_IO_PNM_READ_ENABLED // TODO: Document, explain, review

#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil {

/// Defines pnm tag.
struct pnm_tag : format_tag {};

/// see http://en.wikipedia.org/wiki/Portable_Bitmap_File_Format for reference

/// Defines type for image type property.
struct pnm_image_type : property_base< uint32_t >
{
    using mono_asc_t = std::integral_constant<type, 1>;
    using gray_asc_t = std::integral_constant<type, 2>;
    using color_asc_t = std::integral_constant<type, 3>;

    using mono_bin_t = std::integral_constant<type, 4>;
    using gray_bin_t = std::integral_constant<type, 5>;
    using color_bin_t = std::integral_constant<type, 6>;
};

/// Defines type for image width property.
struct pnm_image_width : property_base< uint32_t > {};

/// Defines type for image height property.
struct pnm_image_height : property_base< uint32_t > {};

/// Defines type for image max value property.
struct pnm_image_max_value : property_base< uint32_t > {};

/// Read information for pnm images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< pnm_tag >
{
    /// The image type.
    pnm_image_type::type      _type;
    /// The image width.
    pnm_image_width::type     _width;
    /// The image height.
    pnm_image_height::type    _height;
    /// The image max value.
    pnm_image_max_value::type _max_value;
};

/// Read settings for pnm images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< pnm_tag > : public image_read_settings_base
{
    /// Default constructor
    image_read_settings< pnm_tag >()
    : image_read_settings_base()
    {}

    /// Constructor
    /// \param top_left   Top left coordinate for reading partial image.
    /// \param dim        Dimensions for reading partial image.
    image_read_settings( const point_t& top_left
                       , const point_t& dim
                       )
    : image_read_settings_base( top_left
                              , dim
                              )
    {}
};

/// Write information for pnm images.
///
/// The structure can be used for write_view() function.
template<>
struct image_write_info< pnm_tag >
{
};

} // namespace gil
} // namespace boost

#endif

/* tags.hpp
5Fma8KwHeWbMZTNGpli8+77rJm7CwMH5ayYuw8Cxe67aiPckYviO+67a+BgLA8DGt+Ik8q0s4cD81upuDCzsv666gyGr7nVehsEH9t8IfYGZkHYtwbv/RlAxmlUdcW7B4EsXd1SvwMDxgzfRzHvmd1ZXOmtzCWdTPuFM9cMkrpBwRgcSTnkw4dhDCWfVcMIBPUg4A5aecEwrnnAMK5Fo7Y+QWQ+YbGaVA0a6L2ykTbT+YId6iR3qI11ktnVRlo2ZvcTS9BFLY5KxoadTlwUNdy5suPNosqGefFs9ORSFPB0Vsp5yt2LuDdvogMkuEAsro4VtwdyPmAt0PDA7Yu5i34m9ltFet2AeQMyDxOy6I0DQ/IPMDvtWGGKWb/sgVgS7DbI6TGTVQlktzmVXGCuKMzdua+Gppiqe5QWvnViiEIAs2q8DexMuJfln4PATY6/DdYRyWXIPTuCBiQH2lNyDE3hgQmZPRwWLkADLgKtSD+BSQeCAmyhneHu/u0ayglSoVkzAXpUAWy3BUsmiSPtBuB6FnKjxD8QxcLzHDrxGuqjilc+5dxmgf/569KEzeA/olXjAfUCQ77pV2GG/Hs/EJgQ89cHdykrxEDv9MP6ch5/PnId2PIjt+BzZtSbF8YrxS+hC3I8fdgPnWeBfscQJ794/ifvIf5qPD3XkY1JgtXLcbcjLgsfLnkBOB34GDxbi8Sm50lYox94l2MfW
*/