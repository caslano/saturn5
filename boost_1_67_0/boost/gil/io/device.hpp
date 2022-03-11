//
// Copyright 2007-2012 Christian Henning, Andreas Pokorny
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_DEVICE_HPP
#define BOOST_GIL_IO_DEVICE_HPP

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/base.hpp>

#include <cstdio>
#include <memory>
#include <type_traits>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

namespace detail {

template < typename T > struct buff_item
{
    static const unsigned int size = sizeof( T );
};

template <> struct buff_item< void >
{
    static const unsigned int size = 1;
};

/*!
 * Implements the IODevice concept c.f. to \ref IODevice required by Image libraries like
 * libjpeg and libpng.
 *
 * \todo switch to a sane interface as soon as there is
 * something good in boost. I.E. the IOChains library
 * would fit very well here.
 *
 * This implementation is based on FILE*.
 */
template< typename FormatTag >
class file_stream_device
{
public:

   using format_tag_t = FormatTag;

public:

    /// Used to overload the constructor.
    struct read_tag {};
    struct write_tag {};

    ///
    /// Constructor
    ///
    file_stream_device( const std::string& file_name
                      , read_tag tag  = read_tag()
                      )
        : file_stream_device(file_name.c_str(), tag)
    {}

    ///
    /// Constructor
    ///
    file_stream_device( const char* file_name
                      , read_tag   = read_tag()
                      )
    {
        FILE* file = nullptr;

        io_error_if( ( file = fopen( file_name, "rb" )) == nullptr
                   , "file_stream_device: failed to open file for reading"
                   );

        _file = file_ptr_t( file
                          , file_deleter
                          );
    }

    ///
    /// Constructor
    ///
    file_stream_device( const std::string& file_name
                      , write_tag tag
                      )
        : file_stream_device(file_name.c_str(), tag)
    {}

    ///
    /// Constructor
    ///
    file_stream_device( const char* file_name
                      , write_tag
                      )
    {
        FILE* file = nullptr;

        io_error_if( ( file = fopen( file_name, "wb" )) == nullptr
                   , "file_stream_device: failed to open file for writing"
                   );

        _file = file_ptr_t( file
                          , file_deleter
                          );
    }

    ///
    /// Constructor
    ///
    file_stream_device( FILE* file )
    : _file( file
           , file_deleter
           )
    {}

    FILE*       get()       { return _file.get(); }
    const FILE* get() const { return _file.get(); }

    int getc_unchecked()
    {
        return std::getc( get() );
    }

    char getc()
    {
        int ch;

        io_error_if( ( ch = std::getc( get() )) == EOF
                   , "file_stream_device: unexpected EOF"
                   );

        return ( char ) ch;
    }

    ///@todo: change byte_t* to void*
    std::size_t read( byte_t*     data
                    , std::size_t count
                    )
    {
        std::size_t num_elements = fread( data
                                        , 1
                                        , static_cast<int>( count )
                                        , get()
                                        );

        ///@todo: add compiler symbol to turn error checking on and off.
        io_error_if( ferror( get() )
                   , "file_stream_device: file read error"
                   );

        //libjpeg sometimes reads blocks in 4096 bytes even when the file is smaller than that.
        //return value indicates how much was actually read
        //returning less than "count" is not an error
        return num_elements;
    }

    /// Reads array
    template< typename T
            , int      N
            >
    void read( T (&buf)[N] )
    {
        io_error_if( read( buf, N ) < N
                   , "file_stream_device: file read error"
                   );
    }

    /// Reads byte
    uint8_t read_uint8()
    {
        byte_t m[1];

        read( m );
        return m[0];
    }

    /// Reads 16 bit little endian integer
    uint16_t read_uint16()
    {
        byte_t m[2];

        read( m );
        return (m[1] << 8) | m[0];
    }

    /// Reads 32 bit little endian integer
    uint32_t read_uint32()
    {
        byte_t m[4];

        read( m );
        return (m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0];
    }

    /// Writes number of elements from a buffer
    template < typename T >
    std::size_t write( const T*    buf
                     , std::size_t count
                     )
    {
        std::size_t num_elements = fwrite( buf
                                         , buff_item<T>::size
                                         , count
                                         , get()
                                         );

        //return value indicates how much was actually written
        //returning less than "count" is not an error
        return num_elements;
    }

    /// Writes array
    template < typename    T
             , std::size_t N
             >
    void write( const T (&buf)[N] )
    {
        io_error_if( write( buf, N ) < N
                   , "file_stream_device: file write error"
                   );
        return ;
    }

    /// Writes byte
    void write_uint8( uint8_t x )
    {
        byte_t m[1] = { x };
        write(m);
    }

    /// Writes 16 bit little endian integer
    void write_uint16( uint16_t x )
    {
        byte_t m[2];

        m[0] = byte_t( x >> 0 );
        m[1] = byte_t( x >> 8 );

        write( m );
    }

    /// Writes 32 bit little endian integer
    void write_uint32( uint32_t x )
    {
        byte_t m[4];

        m[0] = byte_t( x >>  0 );
        m[1] = byte_t( x >>  8 );
        m[2] = byte_t( x >> 16 );
        m[3] = byte_t( x >> 24 );

        write( m );
    }

    void seek( long count, int whence = SEEK_SET )
    {
        io_error_if( fseek( get()
                          , count
                          , whence
                          ) != 0
                   , "file_stream_device: file seek error"
                   );
    }

    long int tell()
    {
        long int pos = ftell( get() );

        io_error_if( pos == -1L
                   , "file_stream_device: file position error"
                   );

        return pos;
    }

    void flush()
    {
        fflush( get() );
    }

    /// Prints formatted ASCII text
    void print_line( const std::string& line )
    {
        std::size_t num_elements = fwrite( line.c_str()
                                         , sizeof( char )
                                         , line.size()
                                         , get()
                                         );

        io_error_if( num_elements < line.size()
                   , "file_stream_device: line print error"
                   );
    }

    int error()
    {
        return ferror( get() );
    }

private:

    static void file_deleter( FILE* file )
    {
        if( file )
        {
            fclose( file );
        }
    }

private:

    using file_ptr_t = std::shared_ptr<FILE> ;
    file_ptr_t _file;
};

/**
 * Input stream device
 */
template< typename FormatTag >
class istream_device
{
public:
   istream_device( std::istream& in )
   : _in( in )
   {
       // does the file exists?
       io_error_if( !in
                  , "istream_device: Stream is not valid."
                  );
   }

    int getc_unchecked()
    {
        return _in.get();
    }

    char getc()
    {
        int ch;

        io_error_if( ( ch = _in.get() ) == EOF
                   , "istream_device: unexpected EOF"
                   );

        return ( char ) ch;
    }

    std::size_t read( byte_t*     data
                    , std::size_t count )
    {
        std::streamsize cr = 0;

        do
        {
            _in.peek();
            std::streamsize c = _in.readsome( reinterpret_cast< char* >( data )
                                            , static_cast< std::streamsize >( count ));

            count -= static_cast< std::size_t >( c );
            data += c;
            cr += c;

        } while( count && _in );

        return static_cast< std::size_t >( cr );
    }

    /// Reads array
    template<typename T, int N>
    void read(T (&buf)[N])
    {
        read(buf, N);
    }

    /// Reads byte
    uint8_t read_uint8()
    {
        byte_t m[1];

        read( m );
        return m[0];
    }

    /// Reads 16 bit little endian integer
    uint16_t read_uint16()
    {
        byte_t m[2];

        read( m );
        return (m[1] << 8) | m[0];
    }

    /// Reads 32 bit little endian integer
    uint32_t read_uint32()
    {
        byte_t m[4];

        read( m );
        return (m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0];
    }

    void seek( long count, int whence = SEEK_SET )
    {
        _in.seekg( count
                 , whence == SEEK_SET ? std::ios::beg
                                      :( whence == SEEK_CUR ? std::ios::cur
                                                            : std::ios::end )
                 );
    }

    void write(const byte_t*, std::size_t)
    {
        io_error( "istream_device: Bad io error." );
    }

    void flush() {}

private:

    std::istream& _in;
};

/**
 * Output stream device
 */
template< typename FormatTag >
class ostream_device
{
public:
    ostream_device( std::ostream & out )
        : _out( out )
    {
    }

    std::size_t read(byte_t *, std::size_t)
    {
        io_error( "ostream_device: Bad io error." );
        return 0;
    }

    void seek( long count, int whence )
    {
        _out.seekp( count
                  , whence == SEEK_SET
                    ? std::ios::beg
                    : ( whence == SEEK_CUR
                        ?std::ios::cur
                        :std::ios::end )
                  );
    }

    void write( const byte_t* data
              , std::size_t   count )
    {
        _out.write( reinterpret_cast<char const*>( data )
                 , static_cast<std::streamsize>( count )
                 );
    }

    /// Writes array
    template < typename    T
             , std::size_t N
             >
    void write( const T (&buf)[N] )
    {
        write( buf, N );
    }

    /// Writes byte
    void write_uint8( uint8_t x )
    {
        byte_t m[1] = { x };
        write(m);
    }

    /// Writes 16 bit little endian integer
    void write_uint16( uint16_t x )
    {
        byte_t m[2];

        m[0] = byte_t( x >> 0 );
        m[1] = byte_t( x >> 8 );

        write( m );
    }

    /// Writes 32 bit little endian integer
    void write_uint32( uint32_t x )
    {
        byte_t m[4];

        m[0] = byte_t( x >>  0 );
        m[1] = byte_t( x >>  8 );
        m[2] = byte_t( x >> 16 );
        m[3] = byte_t( x >> 24 );

        write( m );
    }

    void flush()
    {
        _out << std::flush;
    }

    /// Prints formatted ASCII text
    void print_line( const std::string& line )
    {
        _out << line;
    }



private:

    std::ostream& _out;
};


/**
 * Metafunction to detect input devices.
 * Should be replaced by an external facility in the future.
 */
template< typename IODevice  > struct is_input_device : std::false_type{};
template< typename FormatTag > struct is_input_device< file_stream_device< FormatTag > > : std::true_type{};
template< typename FormatTag > struct is_input_device<     istream_device< FormatTag > > : std::true_type{};

template< typename FormatTag
        , typename T
        , typename D = void
        >
struct is_adaptable_input_device : std::false_type{};

template <typename FormatTag, typename T>
struct is_adaptable_input_device
<
    FormatTag,
    T,
    typename std::enable_if
    <
        mp11::mp_or
        <
            std::is_base_of<std::istream, T>,
            std::is_same<std::istream, T>
        >::value
    >::type
> : std::true_type
{
    using device_type = istream_device<FormatTag>;
};

template< typename FormatTag >
struct is_adaptable_input_device< FormatTag
                                , FILE*
                                , void
                                >
    : std::true_type
{
    using device_type = file_stream_device<FormatTag>;
};

///
/// Metafunction to decide if a given type is an acceptable read device type.
///
template< typename FormatTag
        , typename T
        , typename D = void
        >
struct is_read_device : std::false_type
{};

template <typename FormatTag, typename T>
struct is_read_device
<
    FormatTag,
    T,
    typename std::enable_if
    <
        mp11::mp_or
        <
            is_input_device<FormatTag>,
            is_adaptable_input_device<FormatTag, T>
        >::value
    >::type
> : std::true_type
{
};


/**
 * Metafunction to detect output devices.
 * Should be replaced by an external facility in the future.
 */
template<typename IODevice> struct is_output_device : std::false_type{};

template< typename FormatTag > struct is_output_device< file_stream_device< FormatTag > > : std::true_type{};
template< typename FormatTag > struct is_output_device< ostream_device    < FormatTag > > : std::true_type{};

template< typename FormatTag
        , typename IODevice
        , typename D = void
        >
struct is_adaptable_output_device : std::false_type {};

template <typename FormatTag, typename T>
struct is_adaptable_output_device
<
    FormatTag,
    T,
    typename std::enable_if
    <
        mp11::mp_or
        <
            std::is_base_of<std::ostream, T>,
            std::is_same<std::ostream, T>
        >::value
    >::type
> : std::true_type
{
    using device_type = ostream_device<FormatTag>;
};

template<typename FormatTag> struct is_adaptable_output_device<FormatTag,FILE*,void>
  : std::true_type
{
    using device_type = file_stream_device<FormatTag>;
};


///
/// Metafunction to decide if a given type is an acceptable read device type.
///
template< typename FormatTag
        , typename T
        , typename D = void
        >
struct is_write_device : std::false_type
{};

template <typename FormatTag, typename T>
struct is_write_device
<
    FormatTag,
    T,
    typename std::enable_if
    <
        mp11::mp_or
        <
            is_output_device<FormatTag>,
            is_adaptable_output_device<FormatTag, T>
        >::value
    >::type
> : std::true_type
{
};

} // namespace detail

template< typename Device, typename FormatTag > class scanline_reader;
template< typename Device, typename FormatTag, typename ConversionPolicy > class reader;

template< typename Device, typename FormatTag, typename Log = no_log > class writer;

template< typename Device, typename FormatTag > class dynamic_image_reader;
template< typename Device, typename FormatTag, typename Log = no_log > class dynamic_image_writer;


namespace detail {

template< typename T >
struct is_reader : std::false_type
{};

template< typename Device
        , typename FormatTag
        , typename ConversionPolicy
        >
struct is_reader< reader< Device
                        , FormatTag
                        , ConversionPolicy
                        >
                > : std::true_type
{};

template< typename T >
struct is_dynamic_image_reader : std::false_type
{};

template< typename Device
        , typename FormatTag
        >
struct is_dynamic_image_reader< dynamic_image_reader< Device
                                                    , FormatTag
                                                    >
                              > : std::true_type
{};

template< typename T >
struct is_writer : std::false_type
{};

template< typename Device
        , typename FormatTag
        >
struct is_writer< writer< Device
                        , FormatTag
                        >
                > : std::true_type
{};

template< typename T >
struct is_dynamic_image_writer : std::false_type
{};

template< typename Device
        , typename FormatTag
        >
struct is_dynamic_image_writer< dynamic_image_writer< Device
                                                    , FormatTag
                                                    >
                > : std::true_type
{};

} // namespace detail

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* device.hpp
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
*/