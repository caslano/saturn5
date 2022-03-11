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