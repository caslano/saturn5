//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_TAGS_HPP

#include <boost/gil/io/base.hpp>

#include <string>
#include <vector>

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
#ifdef BOOST_GIL_IO_PNG_FIXED_POINT_SUPPORTED
# error "Cannot set both symbols"
#endif // BOOST_GIL_IO_PNG_FIXED_POINT_SUPPORTED
#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED

#ifndef BOOST_GIL_EXTENSION_IO_PNG_C_LIB_COMPILED_AS_CPLUSPLUS
    extern "C" {
#endif
    #include <png.h>
#ifndef BOOST_GIL_EXTENSION_IO_PNG_C_LIB_COMPILED_AS_CPLUSPLUS
    }
#endif

#ifndef BOOST_GIL_EXTENSION_IO_ZLIB_C_LIB_COMPILED_AS_CPLUSPLUS
    extern "C" {
#endif
    #include <zlib.h>
#ifndef BOOST_GIL_EXTENSION_IO_ZLIB_C_LIB_COMPILED_AS_CPLUSPLUS
    }
#endif

#if PNG_LIBPNG_VER_MAJOR == 1
#if PNG_LIBPNG_VER_MINOR <= 4
#define BOOST_GIL_IO_PNG_1_4_OR_LOWER
#endif // PNG_LIBPNG_VER_MAJOR == 1
#endif // PNG_LIBPNG_VER_MINOR <= 4

namespace boost { namespace gil {

/// Defines png tag.
struct png_tag : format_tag {};

/// see http://en.wikipedia.org/wiki/Portable_Network_Graphics for reference

/// Defines type for image width property.
struct png_image_width : property_base< png_uint_32 > {};

/// Defines type for image height property.
struct png_image_height : property_base< png_uint_32 > {};

/// Defines type for interlace method property.
struct png_interlace_method : property_base< int > {};

/// Defines type for filter method property.
struct png_filter_method : property_base< int > {};

/// Defines type for bit depth method property.
struct png_bitdepth : property_base< int > {};

/// Defines type for bit depth method property.
struct png_color_type : property_base< int > {};

/// Defines type for number of channels property.
struct png_num_channels : property_base< png_byte > {};

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED

    /// Defines type for CIE chromacities property.
    struct png_chromacities_type : property_base< double > {};

    /// Defines type for gamma correction property.
    struct png_gamma : property_base< double > {};

    /// Defines type for physical scale unit property.
    struct png_unit  : property_base< int > {};

    /// Defines type for physical scale property.
    struct png_scale : property_base< double > {};

#else
    /// Defines type for CIE chromacities property.
    struct png_chromacities_type : property_base< png_fixed_point > {};

    /// Defines type for gamma correction property.
    struct png_gamma : property_base< png_fixed_point > {};

    /// Defines type for physical scale unit property.
    struct png_unit  : property_base< int > {};

#ifdef BOOST_GIL_IO_PNG_FIXED_POINT_SUPPORTED
    /// Defines type for physical scale property.
    struct png_scale : property_base< png_fixed_point > {};
#else
    /// Defines type for physical scale property.
    struct png_scale : property_base< std::string > {};
#endif // BOOST_GIL_IO_PNG_FIXED_POINT_SUPPORTED

#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED

/// Returns image resolution in pixels per meter, from pHYs chunk data.
struct png_pixels_per_meter : property_base< png_uint_32 > {};

/// Defines type for ICC profile name property.
struct png_ICC_name             : property_base< std::string > {};
/// Defines type for ICC profile property.
#if PNG_LIBPNG_VER_MINOR >= 5
struct png_ICC_profile          : property_base< std:: vector <uint8_t> > {};
#else
struct png_ICC_profile          : property_base< std:: vector <char> > {};
#endif
/// Defines type for ICC profile length property.
struct png_ICC_profile_length   : property_base< png_uint_32 > {};
/// Defines type for ICC compression property.
struct png_ICC_compression_type : property_base< int         > {};

/// Defines type for rendering intent property.
struct png_intent : property_base< int > {};

/// Defines type for color palette property.
struct png_color_palette : property_base< std::vector< png_color > > {};
/// Defines type for number of colors property.
struct png_num_palette   : property_base< int > {};

/// Defines type for background property.
struct png_background : property_base< png_color_16 > {};

/// Defines type for histogram property.
struct png_histrogram : property_base< std::vector< png_uint_16 > > {};

/// Defines type for screen offset property.
struct png_offset      : property_base< png_int_32 > {};
/// Defines type for screen offset type property.
struct png_offset_type : property_base< int > {};

/// Defines type pixel calibration for property.
struct png_CAL        : property_base< std::string > {};
/// Defines type for pixel calibration parameters property.
struct png_CAL_params : property_base< std::vector< std::string > > {};
/// Defines type for pixel calibration x property.
struct png_CAL_X      : property_base< png_int_32 > {};
/// Defines type for pixel calibration type property.
struct png_CAL_type   : property_base< int > {};
/// Defines type for number of pixel calibration properties.
struct png_CAL_nparam : property_base< int > {};

/// Defines type for physical resolution property.
struct png_resolution : property_base< png_uint_32 > {};
/// Defines type for physical resolution unit property.
struct png_unit_type  : property_base< int > {};

/// Defines type for significant bits property.
struct png_significant_bits : property_base< png_color_8 > {};

/// Helper structure for reading text property.
struct gil_io_png_text
{
    /// Compression type
    int         _compression;
    // Key
    std::string _key;
    /// Text
    std::string _text;
};

/// Defines type for text property.
struct png_text_    : property_base< std::vector< gil_io_png_text > > {};
/// Defines type for number of text property.
struct png_num_text : property_base< int > {};

/// Defines type for modification time property.
struct png_mod_time : property_base< png_time > {};

/// Defines type for transparency data property.
struct png_trans        : property_base< std::vector< png_byte > > {};
/// Defines type for number of transparency data property.
struct png_num_trans    : property_base< int > {};
/// Defines type for transparency data values property.
struct png_trans_values : property_base< std::vector< png_color_16 > > {};

/// Defines type for png function return type.
struct png_return_value : property_base< png_uint_32 > {};

////////////////////////
// Write properties
////////////////////////

// relates to info_ptr->compression_type
struct png_compression_type : property_base< png_byte >
{
    static const type default_value = PNG_COMPRESSION_TYPE_BASE;
};

// compression level - default values taken from libpng manual.
// Look for png_set_compression_level
struct png_compression_level : property_base< int >
{
    static const type default_value = 3;
};

struct png_compression_mem_level : property_base< int >
{
    static const type default_value = MAX_MEM_LEVEL;
};

struct png_compression_strategy : property_base< int >
{
    static const type default_value = Z_DEFAULT_STRATEGY;
};

struct png_compression_window_bits : property_base< int >
{
    static const type default_value = 9;
};

struct png_compression_method : property_base< int >
{
    static const type default_value = 8;
};

struct png_compression_buffer_size : property_base< int >
{
    static const type default_value = 8192;
};

// dithering
struct png_dithering_palette : property_base< std::vector< png_color > >
{};

struct png_dithering_num_palette : property_base< int >
{
    static const type default_value = 0;
};

struct png_dithering_maximum_colors : property_base< int >
{
    static const type default_value = 0;
};

struct png_dithering_histogram : property_base< std::vector< png_uint_16 > >
{};

struct png_full_dither : property_base< int >
{
    static const type default_value = 0;
};

// filter
struct png_filter : property_base< int >
{
    static const type default_value = 0;
};

// invert mono
struct png_invert_mono : property_base< bool >
{
    static const type default_value = false;
};

// true bits
struct png_true_bits : property_base< std::vector< png_color_8 > >
{};

// sRGB Intent
struct png_srgb_intent : property_base< int >
{
    static const type default_value = 0;
};

// strip alpha
struct png_strip_alpha : property_base< bool >
{
    static const type default_value = false;
};

struct png_swap_alpha : property_base< bool >
{
    static const type default_value = false;
};


/// PNG info base class. Containing all header information both for reading and writing.
///
/// This base structure was created to avoid code doubling.
struct png_info_base
{
    /// Default constructor
    png_info_base()
    : _width ( 0 )
    , _height( 0 )

    , _bit_depth         ( 0                            )
    , _color_type        ( 0                            )
    , _interlace_method  ( PNG_INTERLACE_NONE           )
    , _compression_method( PNG_COMPRESSION_TYPE_DEFAULT )
    , _filter_method     ( PNG_FILTER_TYPE_DEFAULT      )

    , _num_channels( 0 )

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
    , _valid_cie_colors( 0   )
    , _white_x         ( 0.0 )
    , _white_y         ( 0.0 )
    , _red_x           ( 0.0 )
    , _red_y           ( 0.0 )
    , _green_x         ( 0.0 )
    , _green_y         ( 0.0 )
    , _blue_x          ( 0.0 )
    , _blue_y          ( 0.0 )

    , _valid_file_gamma( 0   )
    , _file_gamma      ( 1.0 )
#else
    , _valid_cie_colors( 0 )
    , _white_x         ( 0 )
    , _white_y         ( 0 )
    , _red_x           ( 0 )
    , _red_y           ( 0 )
    , _green_x         ( 0 )
    , _green_y         ( 0 )
    , _blue_x          ( 0 )
    , _blue_y          ( 0 )

    , _valid_file_gamma( 0 )
    , _file_gamma      ( 1 )
#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED

    , _valid_icc_profile    ( 0                         )
    , _icc_name             (                           )
    , _iccp_compression_type( PNG_COMPRESSION_TYPE_BASE )
    , _profile              (                           )
    , _profile_length       ( 0                         )

    , _valid_intent( 0 )
    , _intent      ( 0 )

    , _valid_palette( 0 )
    , _palette      (   )
    , _num_palette  ( 0 )

    , _valid_background( 0 )
    , _background      (   )

    , _valid_histogram( 0 )
    , _histogram      (   )

    , _valid_offset ( 0                )
    , _offset_x     ( 0                )
    , _offset_y     ( 0                )
    , _off_unit_type( PNG_OFFSET_PIXEL )

    , _valid_pixel_calibration( 0 )
    , _purpose                (   )
    , _X0                     ( 0 )
    , _X1                     ( 0 )
    , _cal_type               ( 0 )
    , _num_params             ( 0 )
    , _units                  (   )
    , _params                 (   )

    , _valid_resolution( 0                      )
    , _res_x           ( 0                      )
    , _res_y           ( 0                      )
    , _phy_unit_type   ( PNG_RESOLUTION_UNKNOWN )

    , _pixels_per_meter( 0 )

    , _valid_significant_bits( 0 )
    , _sig_bits              (   )

    , _valid_scale_factors( 0                 )
    , _scale_unit         ( PNG_SCALE_UNKNOWN )
#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED
    , _scale_width ( 0.0 )
    , _scale_height( 0.0 )
#else
#ifdef BOOST_GIL_IO_PNG_FIXED_POINT_SUPPORTED
    , _scale_width ( 0 )
    , _scale_height( 0 )
#else
    , _scale_width ()
    , _scale_height()
#endif // BOOST_GIL_IO_PNG_FIXED_POINT_SUPPORTED
#endif // BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED

    , _valid_text( 0 )
    , _text      (   )
    , _num_text  ( 0 )

    , _valid_modification_time( 0 )
    , _mod_time               (   )

    , _valid_transparency_factors( 0 )
    , _trans                     (   )
    , _num_trans                 ( 0 )
    , _trans_values              (   )
    {}

    /// The image width.
    png_image_width::type  _width;
    /// The image height.
    png_image_height::type _height;

    /// The bit depth per channel.
    png_bitdepth::type           _bit_depth;
    /// The color space type.
    png_color_type::type         _color_type;
    /// The interlace methos.
    png_interlace_method::type   _interlace_method;
    /// The compression method.
    png_compression_method::type _compression_method;
    /// The filer method.
    png_filter_method::type      _filter_method;

    /// The number of channels.
    png_num_channels::type _num_channels;

    // CIE chromacities
    /// The return value when reading CIE chromacities.
    png_return_value::type      _valid_cie_colors;
    /// The white x value.
    png_chromacities_type::type _white_x;
    /// The white y value.
    png_chromacities_type::type _white_y;
    /// The red x value.
    png_chromacities_type::type _red_x;
    /// The red y value.
    png_chromacities_type::type _red_y;
    /// The green x value.
    png_chromacities_type::type _green_x;
    /// The green y value.
    png_chromacities_type::type _green_y;
    /// The blue x value.
    png_chromacities_type::type _blue_x;
    /// The blue y value.
    png_chromacities_type::type _blue_y;

    // Gamma Value
    /// The return value when reading gamma value.
    png_return_value::type _valid_file_gamma;
    /// The file gamma value.
    png_gamma::type        _file_gamma;

    // Embedded ICC profile
    /// The return value when reading ICC profile.
    png_return_value::type         _valid_icc_profile;
    /// The ICC name.
    png_ICC_name::type             _icc_name;
    /// The icc compression type.
    png_ICC_compression_type::type _iccp_compression_type;
    /// The ICC profile.
    png_ICC_profile::type          _profile;
    /// The ICC profile length.
    png_ICC_profile_length::type   _profile_length;

    // Rendering intent
    /// The return value when reading rendering intent.
    png_return_value::type _valid_intent;
    /// The rendering intent value.
    png_intent::type       _intent;

    // Image palette
    /// The return value when reading image palette.
    png_return_value::type  _valid_palette;
    /// The color palette.
    png_color_palette::type _palette;
    /// The number of colors in the palettes.
    png_num_palette::type   _num_palette;

    // Background
    /// The return value when reading background.
    png_return_value::type _valid_background;
    /// The background color.
    png_background::type   _background;

    // Histogram
    /// The return value when reading histogram.
    png_return_value::type _valid_histogram;
    /// The histogram.
    png_histrogram::type   _histogram;

    // Screen offsets
    /// The return value when reading screen offsets.
    png_return_value::type _valid_offset;
    /// The x offset.
    png_offset::type       _offset_x;
    /// The y offset.
    png_offset::type       _offset_y;
    /// The offset unit.
    png_offset_type::type  _off_unit_type;

    // Pixel Calibration
    /// The return value when reading pixel calibration.
    png_return_value::type _valid_pixel_calibration;
    /// The purpose.
    png_CAL::type          _purpose;
    /// The x_0 value.
    png_CAL_X::type        _X0;
    /// The x_1 value.
    png_CAL_X::type        _X1;
    /// The calibration type.
    png_CAL_type::type     _cal_type;
    /// The number of calibration parameters.
    png_CAL_nparam::type   _num_params;
    /// The calibration unit type.
    png_CAL::type          _units;
    /// The calibration parameters.
    png_CAL_params::type   _params;

    // Physical resolution
    /// The return value when reading physical resolution properties.
    png_return_value::type _valid_resolution;
    /// The x physical resolution.
    png_resolution::type   _res_x;
    /// The y physical resolution.
    png_resolution::type   _res_y;
    /// The physical resolution unit.
    png_unit_type::type    _phy_unit_type;

    /// The Image resolution in pixels per meter.
    png_pixels_per_meter::type _pixels_per_meter;

    // Number of significant bits
    /// The return value when reading significant bits.
    png_return_value::type     _valid_significant_bits;
    /// The significant bits.
    png_significant_bits::type _sig_bits;

    // Scale Factors
    /// The return value when reading scale factors.
    png_return_value::type _valid_scale_factors;
    /// The scaling unit.
    png_unit::type         _scale_unit;
    /// The scaling width.
    png_scale::type        _scale_width;
    /// The scaling height.
    png_scale::type        _scale_height;

    // Comments information
    /// The return value when reading image comments.
    png_return_value::type _valid_text;
    /// The comments.
    png_text_::type        _text;
    /// The number of comments.
    png_num_text::type     _num_text;

    // Last modification time
    /// The return value when reading modification time.
    png_return_value::type _valid_modification_time;
    /// The modification time.
    png_mod_time::type     _mod_time;

    // Transparency data
    /// The return value when reading transparency data.
    png_return_value::type _valid_transparency_factors;
    /// The transparency data.
    png_trans::type        _trans;
    /// The number of transparency data.
    png_num_trans::type    _num_trans;
    /// The transparency data values.
    png_trans_values::type _trans_values;
};

/// Read information for png images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< png_tag > : public png_info_base
{
    /// Default constructor.
    image_read_info< png_tag >()
    : png_info_base()
    {}
};

/// PNG settings base class.
///
/// This base structure was created to avoid code doubling.
struct png_read_settings_base
{
    /// Default Constructor.
    png_read_settings_base()
    {
        _read_cie_chromacities           = false;
        _read_file_gamma                 = false;
        _read_icc_profile                = false;
        _read_intent                     = false;
        _read_palette                    = false;
        _read_background                 = false;
        _read_histogram                  = false;
        _read_screen_offsets             = false;
        _read_pixel_calibration          = false;
        _read_physical_resolution        = false;
        _read_pixels_per_meter           = false;
        _read_number_of_significant_bits = false;
        _read_scale_factors              = false;
        _read_comments                   = false;
        _read_last_modification_time     = false;
        _read_transparency_data          = false;
    }

    /// Helper function to enabling reading all png properties.
    void set_read_members_true()
    {
        _read_cie_chromacities           = true;
        _read_file_gamma                 = true;
        _read_icc_profile                = true;
        _read_intent                     = true;
        _read_palette                    = true;
        _read_background                 = true;
        _read_histogram                  = true;
        _read_screen_offsets             = true;
        _read_pixel_calibration          = true;
        _read_physical_resolution        = true;
        _read_pixels_per_meter           = true;
        _read_number_of_significant_bits = true;
        _read_scale_factors              = true;
        _read_comments                   = true;
        _read_last_modification_time     = true;
        _read_transparency_data          = true;
    }

    /// Enable reading CIE chromacities.
    bool _read_cie_chromacities;
    /// Enable reading file gamma.
    bool _read_file_gamma;
    /// Enable reading ICC profile.
    bool _read_icc_profile;
    /// Enable reading rendering intent.
    bool _read_intent;
    /// Enable reading color palette.
    bool _read_palette;
    /// Enable reading background color.
    bool _read_background;
    /// Enable reading histogram.
    bool _read_histogram;
    /// Enable reading screen offsets.
    bool _read_screen_offsets;
    /// Enable reading pixel calibration.
    bool _read_pixel_calibration;
    /// Enable reading physical resolution.
    bool _read_physical_resolution;
    /// Enable reading pixels per meter information.
    bool _read_pixels_per_meter;
    /// Enable reading significant bits.
    bool _read_number_of_significant_bits;
    /// Enable reading scaling factors.
    bool _read_scale_factors;
    /// Enable reading comments.
    bool _read_comments;
    /// Enable reading modification time.
    bool _read_last_modification_time;
    /// Enable reading transparency data.
    bool _read_transparency_data;
};

#ifdef BOOST_GIL_IO_PNG_FLOATING_POINT_SUPPORTED

/// Read settings for png images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< png_tag > : public image_read_settings_base
                                      , public png_read_settings_base
{
    /// Default Constructor
    image_read_settings< png_tag >()
    : image_read_settings_base()
    , png_read_settings_base()
    , _screen_gamma( 1.0 )
    {}

    /// Constructor
    /// \param top_left Top left coordinate for reading partial image.
    /// \param dim      Dimensions for reading partial image.
    /// \param gamma    Screen gamma value.
    image_read_settings( const point_t&         top_left
                       , const point_t&         dim
                       , const bool             apply_screen_gamma = false
                       , const png_gamma::type& screen_gamma = 1.0
                       )
    : image_read_settings_base( top_left
                              , dim
                              )
    , png_read_settings_base()
    , _apply_screen_gamma( apply_screen_gamma )
    , _screen_gamma( screen_gamma )
    {}

    /// Apply screen gamma value.
    bool            _apply_screen_gamma;
    /// The screen gamma value.
    png_gamma::type _screen_gamma;
};

#else

/// Read settings for png images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< png_tag > : public image_read_settings_base
                                      , public png_read_settings_base
{
    /// Default Constructor.
    image_read_settings< png_tag >()
    : image_read_settings_base()
    , png_read_settings_base()
    , _apply_screen_gamma( false )
    , _screen_gamma      ( 2     )
    {}

    image_read_settings( const point_t& top_left
                       , const point_t& dim
                       )
    : image_read_settings_base( top_left
                              , dim
                              )
    , png_read_settings_base()
    , _apply_screen_gamma( false )
    , _screen_gamma      ( 2     )
    {}

    /// Apply screen gamma value.
    bool            _apply_screen_gamma;
    /// The screen gamma value.
    png_gamma::type _screen_gamma;
};
#endif

/// Write information for png images.
///
/// The structure can be used for write_view() function.
template<>
struct image_write_info< png_tag >  : public png_info_base
{
    image_write_info( const png_compression_type::type         compression_type        = png_compression_type::default_value
                    , const png_compression_level::type        compression_level       = png_compression_level::default_value
                    , const png_compression_mem_level::type    compression_mem_level   = png_compression_mem_level::default_value
                    , const png_compression_strategy::type     compression_strategy    = png_compression_strategy::default_value
                    , const png_compression_window_bits::type  compression_window_bits = png_compression_window_bits::default_value
                    , const png_compression_method::type       compression_method      = png_compression_method::default_value
                    , const png_compression_buffer_size::type  compression_buffer_size = png_compression_buffer_size::default_value
                    , const png_dithering_num_palette::type    num_palette             = png_dithering_num_palette::default_value
                    , const png_dithering_maximum_colors::type maximum_colors          = png_dithering_maximum_colors::default_value
                    , const png_full_dither::type              full_dither             = png_full_dither::default_value
                    , const png_filter::type                   filter                  = png_filter::default_value
                    , const png_invert_mono::type              invert_mono             = png_invert_mono::default_value
                    , const png_srgb_intent::type              srgb_intent             = png_srgb_intent::default_value
                    , const png_strip_alpha::type              strip_alpha             = png_strip_alpha::default_value
                    , const png_swap_alpha::type               swap_alpha              = png_swap_alpha::default_value
                    )
    : png_info_base()
    , _compression_type( compression_type )
    , _compression_level( compression_level )
    , _compression_mem_level( compression_mem_level )
    , _compression_strategy( compression_strategy )
    , _compression_window_bits( compression_window_bits )
    , _compression_method( compression_method )
    , _compression_buffer_size( compression_buffer_size )

    , _set_dithering( false )
    , _dithering_palette()
    , _dithering_num_palette( num_palette )
    , _dithering_maximum_colors( maximum_colors )
    , _dithering_histogram()
    , _full_dither( full_dither )

    , _set_filter( false )
    , _filter( filter )

    , _invert_mono( invert_mono )

    , _set_true_bits( false )
    , _true_bits()

    , _set_srgb_intent( false )
    , _srgb_intent( srgb_intent )

    , _strip_alpha( strip_alpha )

    , _swap_alpha( swap_alpha )
    {}

    // compression stuff
    png_compression_type::type        _compression_type;
    png_compression_level::type       _compression_level;
    png_compression_mem_level::type   _compression_mem_level;
    png_compression_strategy::type    _compression_strategy;
    png_compression_window_bits::type _compression_window_bits;
    png_compression_method::type      _compression_method;
    png_compression_buffer_size::type _compression_buffer_size;

    // png_set_dither
    bool                                _set_dithering;
    png_dithering_palette::type         _dithering_palette;
    png_dithering_num_palette::type     _dithering_num_palette;
    png_dithering_maximum_colors::type  _dithering_maximum_colors;
    png_dithering_histogram::type       _dithering_histogram;
    png_full_dither::type               _full_dither;

    //png_set_filter
    bool _set_filter;
    png_filter::type _filter;

    // png_set_invert_mono
    png_invert_mono::type _invert_mono;

    // png_set_sBIT
    bool _set_true_bits;
    png_true_bits::type _true_bits;

    // png_set_sRGB
    bool _set_srgb_intent;
    png_srgb_intent::type _srgb_intent;

    // png_set_strip_alpha
    png_strip_alpha::type _strip_alpha;

    // png_set_swap_alpha
    png_swap_alpha::type _swap_alpha;

};

} // namespace gil
} // namespace boost

#endif

/* tags.hpp
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
*/