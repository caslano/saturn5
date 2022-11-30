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
8rnWhUl8hZVk82RhK5/ncHGF9E99WBkU6ORC4DGkBU02M0qPJrDlnE46AqTRoNo6Ar/VJEJs55UFwHcbnYpioLkx2LYzSg1r6RwWatVaWnU/U70H5HJQ6NkkOyGT6fOITKbOUZlMm1PlspOAnOWyTsCCIGH6hzKckHnFWDD5DnrnDc3Fm0qXYd9Y/6SqltNKQSfanRxonFC9DEbrrDxeqF4MNySHt74rmXqxCZVC9WyMgsaBLm0yeMS7TUpBn+XcvPy9vDgXbJ66MYl21+G0FxewvmErtfSvAxEXUQQLkpRIksusoJ1e7mM9H+l/D5PKEkCV1bVJ1RPFHPrmQLHfaXReGojYARHqxlBmB713F1NvuSLBILhxIkcioblb5Ca+MPByRmGSNIuuDJUVHwVCS8KBpUAEc2mE6GrGjN1BP9/JCAYy6O3hrD+AcreEA8nYTlMdQ1Oi0BNlcHHLYISDCnYGjDQGzEio76G/AyNAN5nG/SYWjS4dsQ/6H+zKJhT/23/ETGZNvKKRFJsCMSByUmDyrIg3aYqU4MD1V5BuIc1mnt6cI07MkWa4dJ5s3o6svHGdMQ6dnU+/2KSqgaRwyi+GpPxl06BlUv7ILJPGWFxs2CjJZUmcaMYB5EBk4FA1nS5LwbVtSe8I6FUphRIgpN6rYQgHrbsKTVhgKMVFdhh9WRCvZPPI8cMmRuXb60jlDhBVlAOgGhQeWB43oQGsul/PdOsSyKCQLopCg1PJDM4CmgUhDwvRHJjSZUSJFhKpebw7Nf83WZVSgamhoMZBf7MJq0zG2cILTLGS5AoTJxnpkzicpGSPrdvusfUBbpZSCulXm9G494GpsOZ2r/+x7DWBVc33bOq23rtlgXVtsOIBwvsuGvQ5BpLX7T4tRlb+DCah0zxFXT36LGkKMEAQSaXgE4ABLnj6u358NpGMK/snklVbH1bhBWsUhFrW7Vq+smTgKdwMcAYAc5PIPIOjEOwylxm2RA+iJXqQV3KD8lV1i8HaDO72d9HYBv442oKM+wU3BRuGFuEtNAaC+wc4RLMTrA3iSM0uxDK7ILgRMsnlyTBDjoQ7+jcjChqNDMy5/go06IcQQ5iBVYD9d4xh4+vSOcC40nEHNPUHMd4OLGTcL93GDFGKVttwKxSLNUHOGzwQ/plxwIkI1Qp2ZikSZzG02Ih6w1t6lH0sHAX6VFTtlVZYzmVMLB8PqkUW6g2lq3AqP2OdqkJSXLbcYIbO+StdwiN7KO0lQdR0wJF2T+7JJhv/IqI0Pwzk0udhoHlsJ+1NtpMMuj2zC/tlUH6v6TT5Ce6X/pHofq4bUCJh63lcWrB12LWHpUGmQm9sRBXqYirUIciHMcsms1LWSXKDngVd4NoyeOG5WkQyi7uF56pQKaPAhzM/SN3e8nUkGz24Z5mBgLO7BDGT1Q3JRI+PBMBT0j3fhl34LWruJbnBkGG7VHFBzaWyrRsGKOUqjgV+iJpY1gYMkeJuVTrPPHxYI2GkmeiYPtZ0UtbJVLILH6s2JQCbVluH8HM7WqyypMqyZE6MgU6n/T0o08oyFXTmD4zlKZBlIpON8POXMaYi2a0K1b/gcEqd28t6TrPB1A2jmlbi5Wn9gONei6u+ZamDztshGWHEol1JpRYRuUtyqQ7GsokWs0abQRD0x734VDlJftrEbbgNORTcKniy8OAP5g8Z/a8yg5NC9fqh2GV9JMetHHhah5aJXKaOV8EmMkQ/FL/nw0y+EUdVnYYPbEmAbpi+HMP2v8U0PIXEWz8Sb6m6dhua7pHEPPms9cN1MT1ZKTrB/Sso1jPX4BQny5sMoPQy4hTgWipz4dM01rqKbta6gEveBLaJEai6hqJdtwwBqbgkI0OaLm8269dNzShK2HA7yUsmS3iwP+OFg1Kqg7U72T7Q7jz1NDQ6MFGLB8EMSaK/0kTCZhHL2fPnRA5mOA1q4h74CbcbZ+gzq0fgfHE/RKutKJFdlRCBM86hSbhcLo1TZ9bI4ckl6RrIsBMzNIYnoGySqc7cNpATyfIaWVxsH21XZ24fkijHYYq6qzqUPgJmYy/ihC2OUfcLP4Ihz5e2ovssA5hZSh+HYuxpGIKu7BV1vkSz7OQ5i7pAKU9Qytc2bsUtBvMatz4Mw3heU3apFwi54mjvj0IrfeqGUpgfAoGwe7wfrZ6JnsUMSlkfsZmU7DUw9vhdd4yGaWb2GnXDGnqLBVLDJRJRuy170auqC4APIH/8UVztAzIH2Q3BzRtslVydiS0kQfpbLNrKZLkovCwvGQeW5e9zaDmHCw/8aJILRluQrdWoiVtwCX6RQVUiA9EOetuTEGvpgZqWQvxKrRsctAKHNtbDu8yU+63K5quIQoIoxnt+y8yCu0eoDqK+Z6eis7bT9p9gxuypWug9LTRDCx3VQrO10B+1UJYW2qWF5muhX2mhHC3k1kIrMrGbMELECBDX44+G113LS92qeAs0IZktWkhClYo9JkYV0gWYOSzzQq2X0h/V+gEnnaR8DZSdXEhN0yHSmondJSZUqfZE+DXJczgJiCjTh3TcBGa6vl6D0Hv9b1QVxwLrPm4V6zW4N9HulVoPsj0drEvEh+UyAAG3h5SezGQD5iy0cVS405i6nlVbFRtfAgPue7oS/dYm4GJA16NdMIlk4wchUuFQ1Q66VSmaNoIBt3hXNjjITHzcW9oMlqtQPVv6Nv7urkbaZ0v3sUCNFtjLAqzWs3Im5uDITKxhNw46cbSciRk5MU7O3MZuYDorpe7C5jASu3DsNRmxYOvUeLPCGrBbG7BoO3aHeBeqfYjKmUWwoyCE6n04JrJ+DVKeicXJTI7JSMsTYlYTSIhZzRCEmGV10I+KcT1X/A+SiSIrff+H8WaNmvqR2ro7bEPmh0fPvREDoyd9+Oj5iI2ccThyjl2/eeTgs+wo+vh1FG7JShwXKZtgXEzYAwpyFH1m1iYoPJrZitZAVAg4h1XoDwie7oW8DXQ7y7wFMkeorf79uM7Ll2YhrdO7UQ7Py0MW4/4RvTJckCv9/G5oKrPSu7GU9tiAwUVDfh5YJAZTwTTxBWDkwZ+Sn/TRHW/iyrTaurKEXCiGuAISqLqKwFwyHkZPlkc3Qo7iouUt9SbOKXztzcsnPrlDgC6vIPXyZxU+GiXe69mTij7TKVTo4G+uGS8peEnHSxZe7HhZhZe1HgXBao7UCp7pXlLvowZRCOg9D7LyngfNOVKP/JkgJpN6yznflxEir4z1PGh4SArKHXoxsmbs3Bzp2vJlDaSt9xygurQPLd4l5EP5M0zTzX1IuuYLYBmgZHhYCj7iL0CZxsCgQMFk7cCtTSGPXmjpwQG1vRSfQxTBcLk9w/giSG7DRIeauAn62rOVAiKwapF6uRksIj67fJc0DSytIZGBLW4ZiPqCiLr+ZVoNN9EKUZr7FuMJmZqK+2r+RWq+71ALr9n++UkkqLEGFM3/KsWjGkVavYINK941mm6F26Ie43YYKhFivEtXCq4sy6WnT1GGOOHujZ3hJ8wwT9mFGUkBP7nA1HtqcnPsu0ocxgxZy39ZHgyyJbNxoS2RVptpvUCfeTm8rxFXIIU/5sIk8DJ4Jl22xSv3d2wc5XDx4UcMa7XV8Oly5jJcrBWTHXTXF2w1QzoN02ZoQWSYVCAO9B0qi2zSYURYbHmIex30kBc3lJhItqlo78+lMTSCMRGNqGyRKQXE478LOntvlhhHv3gJkyZBUuCv+ZZze3XiaKXEsNesbZYji3i5o18ZoWQjMbnja7k5Au4hh1Lc97oJh9pUevsq3MuZYu0STXQcu8+ydklxCPqee0N7BhPloFa87c028VCoUKiuZJ6XJ/d7cnTKCLIoKS34oLLIYL1ePr6QbcocvZ49RIJBH8iVm1OgVny0vhn6BOaG4jj5ar84GkfzRHLKd83o64jUG17IejHJHDDWzQI32JNlSBETXBH5+Xn07OscN7kep/ZgPKdArbW5fA0fGA3YpRCnUFjdb9eFq8so6xOjQ3IK8OFdliuXhyewPVmmLDFS3sRz4i121M6s9ThTPIzb9pxWn2SUR8CUX40Md0nPPFOWg3ThBKgP/M7T4EejwKDpIgPz5NsBJpu48plQi3CIU3NNdtJA/xPXIWx8hHy/WiQJ8pw7JbNrDsSX4+Ix5q9oRdduJLY+JSrMVdUlQN5DniMBRXxUabKcKyRlCIw9nr3X8XnMebwe7cDrK2+za5BdW9m1m13b2LWOXc/AlT4CM1H69g4s/zKEM15BKtKd9PUdA/suXv9cVWe9sh/ixRji3ocIfNXaG6hr3TEwNK+Ip4VDIyynlVcoI3uJXU/g1dMJV6f1PaH6T5DTFbFcf0U+irk45YAXfoRtOyDeM7fDKQeXbRSEQz7hWGX6JYC9HQLuyRKOVdfbIeiK8gUNjyjunVDGWi88kwKl1FT3onnxYDVlDzYN+H+RSYG1zc3a7GatdTMpuLG1/i+icYuuT6Yp4kMy1Yv3yJQXp6Q1iIkQEtzNkCx7MD/vf3vg3uDfN3Cv8++B+yp2j4rufwGC0UzQ/lq4dcpX75Smyk0GrSNIRZ9yFHmByaXiGqTYyzrFvwxXQBivT3hjhEMtnvl8q8a7PxMzv4Yt4/x3hwnfNpxwd4hwPCPMpOA3MpLdN5HEsP9LXmt88EGxUA6WitlycI2YJAc3Cu4P+HCjcOOT38tjhfevkcbor4Si8YkF6zP/bj7cDLP//xi4T/ETRj5SDt4jTXTK5REzpCS50RAqXjlQfDUWCVq0PNO1PK9hHrUCH2SyPFksz2qh+l5287hQ/UN285RQPYXdSEJ1MrvZJFSPYjfLhOoYvHkNdQQkgGqc5zmAytbE+h5RNU0EWOO/GBWSw2rhubsicCnHi3PkYL7w3DjIJZbLdK5oBqUogj8+rUFwf4rrPr6UJqZiSEjTbK3lWTLrCM7zSh/81OFmW+WVLqZzOBQEzy8hpol1QSRqzCUI9jKlTEeJuXFOF5bh29zQNCkqFE/Y6JWvq5IRt6tXgBr0sFwpQ7QBqxSqe8FWgC+N3bVzPD5HxEj5tUtMJgcw4D4nPGuG5tRGVgOyjYQ7zXwIB715dvrpc6GHebrsbJWxn8HG85ZW/zkgLFMQ87fAPwilGtcj0uqF6h7AeiikIwYUaxTwZunJDrN34MygUXLvQRPyQI27+To+2cZa7YT9NLpbkEN1H+6F97B0u8eN4rTTX77G9tC5vZsF5QAO7kCUU2FpWg6tjcoBZNN/jwEXdwZGCTTkPpKDW18smlRRu4Xj0H1YRhy5I61+UDn8l3GZ5bUzbMh9gY/uB0Vop2/9CSTjb8UswbXCc0Ed6k0HrrgFHxO2HWPxPxae9eMTquDj4k/l4JPiHaix7l9DmiaOyiY3qg2P6ziPhgYGCDNQQO4dYJlu24OIRqj+D2O4WIpochI3arIT5sa8dqtENjFTxzjvNoRVKEurAnfsEBbR68OxJ1T/FjFgFCk0yE28/0N076Od8lHM+2OpWNNOJBXIy2D35ZGa0ahiuo17V8vvJQdYTGOxDmea9m9BIIr7hCZm89BuIG2BGI3kbrbYRmbiRAEqVtzbMXlBn+J+flAH1AM4rIRjjHOVVaLJAlIusWxYKt+uznwzNBMlR7Fp8onkqi/QCIvjQ0NQSgiRzFdn1oXyFhUNtDMJBsaQHPsHclRap0nxoQ7BpRVt/Ob7I/vRenSH+kx5Ab1qIFWm64Xqx/uY1ldvwycZ6Dve0uEoxxy3czd1uJmtF6+BnK70ZaC8J1EILKvszYPw+9fDrtm/oJ91mRkNQy6ShpHuSxGTNIH0+ACfCMcX9AUMwqEFfTsCo0CWGKnfAe7y9GCmce7TFWO2wAx4fXxvm3ya6/14sHWhkbAdeuYaaZMiLGpIemWmIXpwi8yMci+zZ8N1gjTENkmRtzLv6jlwHXeHsHiVuSC3tyISc4jTCGv8jiX2wnzatw3a4ktXXtnG9INck69mlEfqPSiEmhGLAkc9biSU1pgdYg+tKDNACjNb4kpcdSGNlbPSxaUqG76EaZxmpRq59EAmM3t7Bsaslj44vgMxDzvlWZwYJXsj3Oekb9JY+qmgVo18FEcTSH0vDhTGA6DotNdRYqLBNS0wAgC0wZUWiNwbAegzpcipeE4y+m0h+oQ5+rSjl9iVQQ+md3tNUmpgguaRXCmaS1pMCS4JMyykFokGt1rxiXoAy5CjCMMIg2EepilgCTEbrYESmlrxRUXiXdqtQbqNsFoCt7jSNdqkYTGddjP1z+SjzLBJTxBm0N3nyh8lzGUMM8RhC4yWutD+ME3cyYyv4t7GerY8VT2wh4mWsceqo75uVdUfxQxF7nMV+wI/lD2s4sAUbfhqLVJZN4bbxQoe6kZnEwKEWyyhBol3hhr0HZEt675ZZPJRND+cOEo9gDf0chF6OxZXRDSEeQiUlqFQ0J+7yAs7GUPMZzb7nwApUe+zA0DXew6G7NH9zAHEfztwPxT1asZ3YH/ameW4i2n7p/fFm1tmxZuvw9+yjHjza/D3J/gLwh9njTd/L47PJ8UJ+NjQ4i3EhY8yk8ezn+k7c5mvINOK+83rgwhWQ7PMPGpYn3Gl4UX6Sydcuj1hHA/z0DT6N89A0/72MTbHG27O29cHQfzfwVlYeqz94gfCoTEKk7VmxhUmVOUAm128gDJzWs8K1XsYlC/SX1WOojQzWAlh2yZE8g8MIPl64WDl9kEkTxitJ7zRwsHq9H0I6XkfNZRo/sPaKFQvZm+jRQnPxGnYfsTi78H2+4bI4fwQyTDE3MGwfT1i+xzE9jPSGsXUNNynhOb5IOL0AwynHxqC7N8YguxfHY7st2MJFvS7GQC/dqeURvRygyHcOW1sUAiKcyiwZ2Z8KUPhbddDKPxdDYWzpIwhwH5amO6UYXS7Q3RHDMH1EcNx/btDcP0XvNZwwPV5iOuzBnH9yeG4/ijD9XPWSPH6q4O43v+bIYj+v4Yg+md5DdEBoh/rlCsA0Y8EfzSI6P0/CWF5ljpdSx3A8v7FYRSfHUbxmWEUPyOM4tPCKH5SGMWPZSiejWHCbPeSMIpvDRlaurgLsVhXVKjZAOPvZjD+eBjGJ6PRrtBgvE98BP74NJ/gvogwvn4ojGdaTZiIQ/jJc3QQxR8dRPHuFkF5djiO/+QmHN8yBMcf/Qc4njlaGSbYxuMMxzcM4HjW9WR5nwY9hOqriOPP/RMcrwrPxg/g+CiG49F8aDh+TPV3cPzREI4/H8bxnyKO9wnVuLFAplFCdTcCeV8YyKNCDgXyrUOs0nAgv1/zH/jzz4B8y44hQB5H8v8lkB8cE/8SkA/rRwjIt17/XiD/zWvDgPzfGJD/y3eA/BchIP8kAvnUm4G8cgAVR/zREBDvGGAWepE2vqih+E3Xwk57KIrXD6B4fRMzaozt3qEoHunHDGiRhuF3QDb9J2RekOT3+f8XMfxIsB4/lgqH4LaHrc3lfAinNVdd1ZC7508aZn/ZD7FM5wG5773+Pcg9OAy560PIvSGM3OcNIHfW6WHkXh9C7az5w1B74VDU/koYtf/1O6idkSu8CbUjo4jazw3NMQS1zxmG2hdo47XQP7Yfm9PNbAb6zyiUi4ban+5jKl79chi1v89QO+YahtqxZg21b7kJtWPWIajdg27I
*/