//
// Copyright 2007-2008 Andreas Pokorny, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_DEVICE_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_DETAIL_DEVICE_HPP

#include <boost/gil/extension/io/tiff/tags.hpp>
#include <boost/gil/extension/io/tiff/detail/log.hpp>
#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/base.hpp>
#include <boost/gil/io/device.hpp>

#include <algorithm>
#include <memory>
#include <sstream>
#include <type_traits>

// taken from jpegxx - https://bitbucket.org/edd/jpegxx/src/ea2492a1a4a6/src/ijg_headers.hpp
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_C_LIB_COMPILED_AS_CPLUSPLUS
    extern "C" {
#endif

#include <tiff.h>
#include <tiffio.h>

#ifndef BOOST_GIL_EXTENSION_IO_TIFF_C_LIB_COMPILED_AS_CPLUSPLUS
    }
#endif

#include <tiffio.hxx>

namespace boost { namespace gil { namespace detail {

template <int n_args>
struct get_property_f {
	template <typename Property>
	bool call_me(typename Property:: type& value, std::shared_ptr<TIFF>& file);
};

template <int n_args>
struct set_property_f {
	template <typename Property>
	bool call_me(const typename Property:: type& value, std::shared_ptr<TIFF>& file) const;
};

template <> struct get_property_f <1>
{
	// For single-valued properties
	template <typename Property>
	bool call_me(typename Property::type & value, std::shared_ptr<TIFF>& file) const
	{
		// @todo: defaulted, really?
		return (1 == TIFFGetFieldDefaulted( file.get()
				, Property:: tag
				, & value));
	}
};

template <> struct get_property_f <2>
{
	// Specialisation for multi-valued properties. @todo: add one of
	// these for the three-parameter fields too.
	template <typename Property>
	bool call_me(typename Property::type& vs, std::shared_ptr<TIFF>& file) const
	{
        mp11::mp_at<typename Property::arg_types, std::integral_constant<int, 0>> length;
        mp11::mp_at<typename Property::arg_types, std::integral_constant<int, 1>> pointer;
		if (1 == TIFFGetFieldDefaulted(file.get(), Property:: tag, & length, & pointer))
        {
			std:: copy_n(static_cast<typename Property::type::const_pointer>(pointer), length, std:: back_inserter(vs));
			return true;
		} else
			return false;
	}
};

template <> struct set_property_f <1>
{
	// For single-valued properties
	template <typename Property>
	inline
	bool call_me(typename Property:: type const & value, std::shared_ptr<TIFF>& file) const
	{
		return (1 == TIFFSetField( file.get()
				, Property:: tag
				, value));
	}
};

template <> struct set_property_f <2>
{
	// Specialisation for multi-valued properties. @todo: add one
	// of these for the three-parameter fields too. Actually we
	// will need further templation / specialisation for the
	// two-element fields which aren't a length and a data buffer
	// (e.g. http://www.awaresystems.be/imaging/tiff/tifftags/dotrange.html
	// )
	template <typename Property>
	inline
	bool call_me(typename Property:: type const & values, std::shared_ptr<TIFF>& file) const
	{
        using length_t = mp11::mp_at_c<typename Property::arg_types, 0>;
		auto const length = static_cast<length_t>(values.size());

        using pointer_t = mp11::mp_at_c<typename Property::arg_types, 1>;
		auto const pointer = static_cast<pointer_t>(&(values.front()));
		return (1 == TIFFSetField( file.get(), Property:: tag, length, pointer));
	}
};

template< typename Log >
class tiff_device_base
{
public:
    using tiff_file_t = std::shared_ptr<TIFF>;

    tiff_device_base()
    {}

    tiff_device_base( TIFF* tiff_file )
    : _tiff_file( tiff_file
                , TIFFClose )
    {}

	template <typename Property>
    bool get_property( typename Property::type& value  )
    {
		return get_property_f<mp11::mp_size<typename Property::arg_types>::value>().template call_me<Property>(value, _tiff_file);
	}

    template <typename Property>
    inline
    bool set_property( const typename Property::type& value )
    {
      // http://www.remotesensing.org/libtiff/man/TIFFSetField.3tiff.html
      return set_property_f<mp11::mp_size<typename Property::arg_types>::value>().template call_me<Property>(value, _tiff_file);
    }

    // TIFFIsByteSwapped returns a non-zero value if the image data was in a different
    // byte-order than the host machine. Zero is returned if the TIFF file and local
    // host byte-orders are the same. Note that TIFFReadTile(), TIFFReadStrip() and TIFFReadScanline()
    // functions already normally perform byte swapping to local host order if needed.
    bool are_bytes_swapped()
    {
        return ( TIFFIsByteSwapped( _tiff_file.get() )) ? true : false;
    }

    bool is_tiled() const
    {
        return ( TIFFIsTiled( _tiff_file.get() )) ? true : false;
    }

    unsigned int get_default_strip_size()
    {
        return TIFFDefaultStripSize( _tiff_file.get()
                                   , 0 );
    }

    std::size_t get_scanline_size()
    {
      return TIFFScanlineSize( _tiff_file.get() );
    }

    std::size_t get_tile_size()
    {
      return TIFFTileSize( _tiff_file.get() );
    }


    int get_field_defaulted( uint16_t*& red
                           , uint16_t*& green
                           , uint16_t*& blue
                           )
    {
        return TIFFGetFieldDefaulted( _tiff_file.get()
                                    , TIFFTAG_COLORMAP
                                    , &red
                                    , &green
                                    , &blue
                                    );
    }

    template< typename Buffer >
    void read_scanline( Buffer&        buffer
                      , std::ptrdiff_t row
                      , tsample_t      plane
                      )
    {
        io_error_if( TIFFReadScanline( _tiff_file.get()
                                     , reinterpret_cast< tdata_t >( &buffer.front() )
                                     , (uint32) row
                                     , plane           ) == -1
                   , "Read error."
                   );
    }

    void read_scanline( byte_t*        buffer
                      , std::ptrdiff_t row
                      , tsample_t      plane
                      )
    {
        io_error_if( TIFFReadScanline( _tiff_file.get()
                                     , reinterpret_cast< tdata_t >( buffer )
                                     , (uint32) row
                                     , plane           ) == -1
                   , "Read error."
                   );
    }

    template< typename Buffer >
    void read_tile( Buffer&        buffer
                  , std::ptrdiff_t x
                  , std::ptrdiff_t y
                  , std::ptrdiff_t z
                  , tsample_t      plane
                  )
    {
        if( TIFFReadTile( _tiff_file.get()
                        , reinterpret_cast< tdata_t >( &buffer.front() )
                        , (uint32) x
                        , (uint32) y
                        , (uint32) z
                        , plane
                        ) == -1 )
        {
            std::ostringstream oss;
            oss << "Read tile error (" << x << "," << y << "," << z << "," << plane << ").";
            io_error(oss.str().c_str());
        }
    }

    template< typename Buffer >
    void write_scaline( Buffer&     buffer
                      , uint32      row
                      , tsample_t   plane
                      )
    {
       io_error_if( TIFFWriteScanline( _tiff_file.get()
                                     , &buffer.front()
                                     , row
                                     , plane
                                     ) == -1
                   , "Write error"
                   );
    }

    void write_scaline( byte_t*     buffer
                      , uint32      row
                      , tsample_t   plane
                      )
    {
       io_error_if( TIFFWriteScanline( _tiff_file.get()
                                     , buffer
                                     , row
                                     , plane
                                     ) == -1
                   , "Write error"
                   );
    }

    template< typename Buffer >
    void write_tile( Buffer&     buffer
                   , uint32      x
                   , uint32      y
                   , uint32      z
                   , tsample_t   plane
                   )
    {
       if( TIFFWriteTile( _tiff_file.get()
                        , &buffer.front()
                        , x
                        , y
                        , z
                        , plane
                        ) == -1 )
           {
               std::ostringstream oss;
               oss << "Write tile error (" << x << "," << y << "," << z << "," << plane << ").";
               io_error(oss.str().c_str());
           }
    }

    void set_directory( tdir_t directory )
    {
        io_error_if( TIFFSetDirectory( _tiff_file.get()
                                     , directory
                                     ) != 1
                   , "Failing to set directory"
                   );
    }

    // return false if the given tile width or height is not TIFF compliant (multiple of 16) or larger than image size, true otherwise
    bool check_tile_size( tiff_tile_width::type&  width
                        , tiff_tile_length::type& height

                        )
    {
        bool result = true;
        uint32 tw = static_cast< uint32 >( width  );
        uint32 th = static_cast< uint32 >( height );

        TIFFDefaultTileSize( _tiff_file.get()
                           , &tw
                           , &th
                           );

        if(width==0 || width%16!=0)
        {
            width = tw;
            result = false;
        }
        if(height==0 || height%16!=0)
        {
            height = th;
            result = false;
        }
        return result;
    }

protected:

   tiff_file_t _tiff_file;

    Log _log;
};

/*!
 *
 * file_stream_device specialization for tiff images, which are based on TIFF*.
 */
template<>
class file_stream_device< tiff_tag > : public tiff_device_base< tiff_no_log >
{
public:

    struct read_tag {};
    struct write_tag {};

    file_stream_device( std::string const& file_name, read_tag )
    {
        TIFF* tiff;

        io_error_if( ( tiff = TIFFOpen( file_name.c_str(), "r" )) == nullptr
                   , "file_stream_device: failed to open file" );

        _tiff_file = tiff_file_t( tiff, TIFFClose );
    }

    file_stream_device( std::string const& file_name, write_tag )
    {
        TIFF* tiff;

        io_error_if( ( tiff = TIFFOpen( file_name.c_str(), "w" )) == nullptr
                   , "file_stream_device: failed to open file" );

        _tiff_file = tiff_file_t( tiff, TIFFClose );
    }

    file_stream_device( TIFF* tiff_file )
    : tiff_device_base( tiff_file )
    {}
};

/*!
 *
 * ostream_device specialization for tiff images.
 */
template<>
class ostream_device< tiff_tag > : public tiff_device_base< tiff_no_log >
{
public:
    ostream_device( std::ostream & out )
    : _out( out )
    {
        TIFF* tiff;

        io_error_if( ( tiff = TIFFStreamOpen( ""
                                            , &_out
                                            )
                      ) == nullptr
                   , "ostream_device: failed to stream"
                   );

        _tiff_file = tiff_file_t( tiff, TIFFClose );
    }

private:
    ostream_device& operator=( const ostream_device& ) { return *this; }

private:

    std::ostream& _out;
};

/*!
 *
 * ostream_device specialization for tiff images.
 */
template<>
class istream_device< tiff_tag > : public tiff_device_base< tiff_no_log >
{
public:
    istream_device( std::istream & in )
    : _in( in )
    {
        TIFF* tiff;

        io_error_if( ( tiff = TIFFStreamOpen( ""
                                            , &_in
                                            )
                     ) == nullptr
                   , "istream_device: failed to stream"
                   );

        _tiff_file = tiff_file_t( tiff, TIFFClose );
    }

private:
    istream_device& operator=( const istream_device& ) { return *this; }

private:

    std::istream& _in;
};

/*
template< typename T, typename D >
struct is_adaptable_input_device< tiff_tag, T, D > : std::false_type {};
*/

template<typename FormatTag>
struct is_adaptable_input_device<FormatTag, TIFF*, void> : std::true_type
{
    using device_type = file_stream_device<FormatTag>;
};

template<typename FormatTag>
struct is_adaptable_output_device<FormatTag, TIFF*, void> : std::true_type
{
    using device_type = file_stream_device<FormatTag>;
};


template <typename Channel>
struct sample_format : std::integral_constant<int, SAMPLEFORMAT_UINT> {};
template<>
struct sample_format<uint8_t> : std::integral_constant<int, SAMPLEFORMAT_UINT> {};
template<>
struct sample_format<uint16_t> : std::integral_constant<int, SAMPLEFORMAT_UINT> {};
template<>
struct sample_format<uint32_t> : std::integral_constant<int, SAMPLEFORMAT_UINT> {};
template<>
struct sample_format<float32_t> : std::integral_constant<int, SAMPLEFORMAT_IEEEFP> {};
template<>
struct sample_format<double> : std::integral_constant<int, SAMPLEFORMAT_IEEEFP> {};
template<>
struct sample_format<int8_t> : std::integral_constant<int, SAMPLEFORMAT_INT> {};
template<>
struct sample_format<int16_t> : std::integral_constant<int, SAMPLEFORMAT_INT> {};
template<>
struct sample_format<int32_t> : std::integral_constant<int, SAMPLEFORMAT_INT> {};

template <typename Channel>
struct photometric_interpretation {};
template<>
struct photometric_interpretation<gray_t>
    : std::integral_constant<int, PHOTOMETRIC_MINISBLACK> {};
template<>
struct photometric_interpretation<rgb_t>
    : std::integral_constant<int, PHOTOMETRIC_RGB> {};
template<>
struct photometric_interpretation<rgba_t>
    : std::integral_constant<int, PHOTOMETRIC_RGB> {};
template<>
struct photometric_interpretation<cmyk_t>
    : std::integral_constant<int, PHOTOMETRIC_SEPARATED> {};

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* device.hpp
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
*/