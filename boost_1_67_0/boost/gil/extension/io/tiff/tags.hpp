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