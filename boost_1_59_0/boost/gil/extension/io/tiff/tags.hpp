//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_TAGS_HPP

#include <boost/gil/extension/io/tiff/detail/log.hpp>

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

// taken from jpegxx - https://bitbucket.org/edd/jpegxx/src/ea2492a1a4a6/src/ijg_headers.hpp
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_C_LIB_COMPILED_AS_CPLUSPLUS
    extern "C" {
#endif

#include <tiff.h>

#ifndef BOOST_GIL_EXTENSION_IO_TIFF_C_LIB_COMPILED_AS_CPLUSPLUS
    }
#endif

namespace boost { namespace gil {

/// Defines tiff tag.
struct tiff_tag : format_tag {};

/// http://www.awaresystems.be/imaging/tiff/tifftags/baseline.html
/// http://www.remotesensing.org/libtiff/

/// TIFF property base class
template< typename T, int Value >
struct tiff_property_base : property_base< T >
{
    /// Tag, needed when reading or writing image properties.
    static const ttag_t tag = Value;
    /// The list of argument types used in the interface of LibTIFF
    /// for
    /// this property:
    /// http://www.remotesensing.org/libtiff/man/TIFFGetField.3tiff.html
    /// http://www.remotesensing.org/libtiff/man/TIFFSetField.3tiff.html
    using arg_types = mp11::mp_list<typename property_base<unsigned short>::type>;
};

/// baseline tags

/// Defines type for new subfile property.
struct tiff_new_subfile_type : tiff_property_base< uint32_t, TIFFTAG_SUBFILETYPE > {};

/// Defines type for subfile property.
struct tiff_subfile_type : tiff_property_base< uint16_t, TIFFTAG_OSUBFILETYPE > {};

/// Defines type for image width property.
struct tiff_image_width : tiff_property_base< uint32_t, TIFFTAG_IMAGEWIDTH > {};

/// Defines type for image height property.
struct tiff_image_height : tiff_property_base< uint32_t, TIFFTAG_IMAGELENGTH > {};

/// Defines type for bits per sample property.
struct tiff_bits_per_sample : tiff_property_base< uint16_t, TIFFTAG_BITSPERSAMPLE > {};

/// Defines type for compression property.
struct tiff_compression : tiff_property_base< uint16_t, TIFFTAG_COMPRESSION > {};

/// Defines type for photometric interpretation property.
struct tiff_photometric_interpretation : tiff_property_base< uint16_t, TIFFTAG_PHOTOMETRIC > {};

/// Defines type for threshold property.
struct tiff_thresholding : tiff_property_base< uint16_t, TIFFTAG_THRESHHOLDING > {};

/// Defines type for cell width property.
struct tiff_cell_width : tiff_property_base< uint16_t, TIFFTAG_CELLWIDTH > {};

/// Defines type for cell length property.
struct tiff_cell_length : tiff_property_base< uint16_t, TIFFTAG_CELLLENGTH > {};

/// Defines type for fill order property.
struct tiff_fill_order : tiff_property_base< std::string, TIFFTAG_FILLORDER > {};

/// Defines type for image description.
struct tiff_image_description : tiff_property_base< std::string, TIFFTAG_IMAGEDESCRIPTION > {};

/// Defines type for make property.
struct tiff_make : tiff_property_base< std::string, TIFFTAG_MAKE > {};

/// Defines type for model property.
struct tiff_model : tiff_property_base< std::string, TIFFTAG_MODEL > {};

/// Defines type for image orientation.
struct tiff_orientation : tiff_property_base< uint16_t, TIFFTAG_ORIENTATION > {};

/// Defines type for samples per pixel property.
struct tiff_samples_per_pixel : tiff_property_base< uint16_t, TIFFTAG_SAMPLESPERPIXEL > {};

/// Defines type for rows per strip property.
struct tiff_rows_per_strip : tiff_property_base< uint32_t, TIFFTAG_ROWSPERSTRIP > {};

/// Defines type for min sample property.
struct tiff_min_sample_value : tiff_property_base< uint16_t, TIFFTAG_MINSAMPLEVALUE > {};

/// Defines type for max sample property.
struct tiff_max_sample_value : tiff_property_base< uint16_t, TIFFTAG_MAXSAMPLEVALUE > {};

/// Defines type for x resolution property.
struct tiff_x_resolution : tiff_property_base< float, TIFFTAG_XRESOLUTION > {};

/// Defines type for y resolution property.
struct tiff_y_resolution : tiff_property_base< float, TIFFTAG_YRESOLUTION > {};

/// Defines type for resolution unit property.
enum class tiff_resolution_unit_value: std:: uint16_t {
  NONE = RESUNIT_NONE,
  INCH = RESUNIT_INCH,
  CENTIMETER = RESUNIT_CENTIMETER
};

struct tiff_resolution_unit : tiff_property_base< tiff_resolution_unit_value, TIFFTAG_RESOLUTIONUNIT > {};

/// Defines type for planar configuration property.
struct tiff_planar_configuration : tiff_property_base< uint16_t, TIFFTAG_PLANARCONFIG > {};

/// Defines type for gray response unit property.
struct tiff_gray_response_unit : tiff_property_base< uint16_t, TIFFTAG_GRAYRESPONSEUNIT > {};

/// Defines type for gray response curve property.
struct tiff_gray_response_curve : tiff_property_base< uint16_t*, TIFFTAG_GRAYRESPONSECURVE > {};

/// Defines type for software vendor property.
struct tiff_software : tiff_property_base< std::string, TIFFTAG_SOFTWARE > {};

/// Defines type for date time property.
struct tiff_date_time : tiff_property_base< std::string, TIFFTAG_DATETIME > {};

/// Defines type for artist information property.
struct tiff_artist : tiff_property_base< std::string, TIFFTAG_ARTIST > {};

/// Defines type for host computer property.
struct tiff_host_computer : tiff_property_base< std::string, TIFFTAG_HOSTCOMPUTER > {};

/// Helper structure for reading a color mapper.
struct tiff_color_map
{
   using red_t = uint16_t *;
   using green_t = uint16_t *;
   using blue_t = uint16_t *;

   static const unsigned int tag = TIFFTAG_COLORMAP;
};

/// Defines type for extra samples property.
struct tiff_extra_samples : tiff_property_base<std::vector<uint16_t>, TIFFTAG_EXTRASAMPLES>
{
    using arg_types = mp11::mp_list<uint16_t, uint16_t const*>;
};

/// Defines type for copyright property.
struct tiff_copyright : tiff_property_base< std::string, TIFFTAG_COPYRIGHT > {};

/// non-baseline tags

/// Defines type for sample format property.
struct tiff_sample_format : tiff_property_base< uint16_t, TIFFTAG_SAMPLEFORMAT > {};

/// Defines type for indexed property.
/// Not supported yet
//struct tiff_indexed : tiff_property_base< bool, TIFFTAG_INDEXED > {};

/// Tile related tags

/// Defines type for a (not) tiled tiff image
struct tiff_is_tiled : tiff_property_base< bool, false > {};

/// Defines type for tile width
struct tiff_tile_width : tiff_property_base< long, TIFFTAG_TILEWIDTH > {};

/// Defines type for tile length
struct tiff_tile_length : tiff_property_base< long, TIFFTAG_TILELENGTH > {};

/// Defines the page to read in a multipage tiff file.
struct tiff_directory : property_base< tdir_t >
{
    using default_value = std::integral_constant<type, 0>;
};

/// Non-baseline tags

/// Defines type for icc profile property.
struct tiff_icc_profile : tiff_property_base<std::vector<uint8_t>, TIFFTAG_ICCPROFILE>
{
    using arg_types = mp11::mp_list<uint32_t, void const*>;
};

/// Read information for tiff images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< tiff_tag >
{
    image_read_info()
    : _width( 0 )
    , _height( 0 )

    , _compression( COMPRESSION_NONE )

    , _bits_per_sample( 0 )
    , _samples_per_pixel( 0 )
    , _sample_format( SAMPLEFORMAT_UINT )

    , _planar_configuration( PLANARCONFIG_CONTIG )

    , _photometric_interpretation( PHOTOMETRIC_MINISWHITE )

    , _is_tiled( false )

    , _tile_width ( 0 )
    , _tile_length( 0 )

    , _x_resolution( 1 )
    , _y_resolution( 1 )
    , _resolution_unit( tiff_resolution_unit_value:: NONE )

    , _icc_profile(  )
    {}

    /// The number of rows of pixels in the image.
    tiff_image_width::type  _width;
    /// The number of columns in the image, i.e., the number of pixels per row.
    tiff_image_height::type _height;

    /// Compression scheme used on the image data.
    tiff_compression::type _compression;

    /// Number of bits per component.
    tiff_bits_per_sample::type   _bits_per_sample;
    /// The number of components per pixel.
    tiff_samples_per_pixel::type _samples_per_pixel;
    /// Specifies how to interpret each data sample in a pixel.
    tiff_sample_format::type     _sample_format;

    /// How the components of each pixel are stored.
    tiff_planar_configuration::type _planar_configuration;

    /// The color space of the image data.
    tiff_photometric_interpretation::type _photometric_interpretation;

    /// Is tiled?
    tiff_is_tiled::type _is_tiled;
    /// Tile width
    tiff_tile_width::type _tile_width;
    /// Tile length
    tiff_tile_length::type _tile_length;

    tiff_x_resolution::type _x_resolution;
    tiff_y_resolution::type _y_resolution;
    tiff_resolution_unit::type _resolution_unit;

    tiff_icc_profile:: type _icc_profile;
};

/// Read settings for tiff images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< tiff_tag > : public image_read_settings_base
{
    /// Default constructor
    image_read_settings< tiff_tag >()
    : image_read_settings_base()
    , _directory( tiff_directory::default_value::value )
    {}

    /// Constructor
    /// \param top_left  Top left coordinate for reading partial image.
    /// \param dim       Dimensions for reading partial image.
    /// \param directory Defines the page to read in a multipage tiff file.
    image_read_settings( const point_t&              top_left
                       , const point_t&              dim
                       , const tiff_directory::type& directory = tiff_directory::default_value::value
                       )
    : image_read_settings_base( top_left
                              , dim
                              )
    , _directory( directory )
    {}

    /// Defines the page to read in a multipage tiff file.
    tiff_directory::type _directory;
};

/// Write settings for tiff images.
///
/// The structure can be used for all write_xxx functions, except write_image_info.
template< typename Log >
struct image_write_info< tiff_tag, Log >
{
    /// Default constructor
    image_write_info()
    : _photometric_interpretation             ( PHOTOMETRIC_MINISBLACK )
    , _photometric_interpretation_user_defined( false                  )

    , _compression               ( COMPRESSION_NONE       )
    , _orientation               ( ORIENTATION_TOPLEFT    )
    , _planar_configuration      ( PLANARCONFIG_CONTIG    )
    , _is_tiled                  ( false )
    , _tile_width                ( 0 )
    , _tile_length               ( 0 )
    , _x_resolution              ( 1 )
    , _y_resolution              ( 1 )
    , _resolution_unit           ( tiff_resolution_unit_value::NONE )
    , _icc_profile               (  )
    {}

    /// The color space of the image data.
    tiff_photometric_interpretation::type _photometric_interpretation;
    bool                                  _photometric_interpretation_user_defined;

    /// Compression scheme used on the image data.
    tiff_compression::type                _compression;
    /// The orientation of the image with respect to the rows and columns.
    tiff_orientation::type                _orientation;
    /// How the components of each pixel are stored.
    tiff_planar_configuration::type       _planar_configuration;

    /// Is the image tiled?
    tiff_is_tiled::type                   _is_tiled;
    /// Tiles width
    tiff_tile_width::type                 _tile_width;
    /// Tiles length
    tiff_tile_length::type                _tile_length;

    /// x, y resolution
    tiff_x_resolution::type               _x_resolution;
    tiff_y_resolution::type               _y_resolution;
    tiff_resolution_unit::type            _resolution_unit;

    tiff_icc_profile:: type               _icc_profile;

	/// A log to transcript error and warning messages issued by libtiff.
    Log                                   _log;
};

} // namespace gil
} // namespace boost

#endif

/* tags.hpp
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
*/