//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_WRITER_BACKEND_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_DETAIL_WRITER_BACKEND_HPP

#include <boost/gil/extension/io/jpeg/tags.hpp>
#include <boost/gil/extension/io/jpeg/detail/base.hpp>

#include <memory>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#pragma warning(disable:4611) //interaction between '_setjmp' and C++ object destruction is non-portable
#endif

namespace detail {

///
/// Wrapper for libjpeg's compress object. Implements value semantics.
///
struct jpeg_compress_wrapper
{
protected:

    using jpeg_compress_ptr_t = std::shared_ptr<jpeg_compress_struct>;

protected:

    ///
    /// Default Constructor
    ///
    jpeg_compress_wrapper()
    : _jpeg_compress_ptr( new jpeg_compress_struct()
                        , jpeg_compress_deleter
                        )
    {}

    jpeg_compress_struct*       get()       { return _jpeg_compress_ptr.get(); }
    const jpeg_compress_struct* get() const { return _jpeg_compress_ptr.get(); }

private:

    static void jpeg_compress_deleter( jpeg_compress_struct* jpeg_compress_ptr )
    {
        if( jpeg_compress_ptr )
        {
            jpeg_destroy_compress( jpeg_compress_ptr );

            delete jpeg_compress_ptr;
            jpeg_compress_ptr = nullptr;
        }
    }

private:

   jpeg_compress_ptr_t _jpeg_compress_ptr;

};

} // namespace detail

///
/// JPEG Writer Backend
///
template< typename Device >
struct writer_backend< Device
                     , jpeg_tag
                     >
    : public jpeg_io_base
    , public detail::jpeg_compress_wrapper
{
public:

    using format_tag_t = jpeg_tag;

public:
    ///
    /// Constructor
    ///
    writer_backend( const Device&                       io_dev
                  , const image_write_info< jpeg_tag >& info
                  )
    : _io_dev( io_dev )
    , _info( info )
    {
        get()->err         = jpeg_std_error( &_jerr );
        get()->client_data = this;

        // Error exit handler: does not return to caller.
        _jerr.error_exit = &writer_backend< Device, jpeg_tag >::error_exit;

        // Fire exception in case of error.
        if( setjmp( _mark )) { raise_error(); }

        _dest._jdest.free_in_buffer      = sizeof( buffer );
        _dest._jdest.next_output_byte    = buffer;
        _dest._jdest.init_destination    = reinterpret_cast< void(*)   ( j_compress_ptr ) >( &writer_backend< Device, jpeg_tag >::init_device  );
        _dest._jdest.empty_output_buffer = reinterpret_cast< boolean(*)( j_compress_ptr ) >( &writer_backend< Device, jpeg_tag >::empty_buffer );
        _dest._jdest.term_destination    = reinterpret_cast< void(*)   ( j_compress_ptr ) >( &writer_backend< Device, jpeg_tag >::close_device );
        _dest._this = this;

        jpeg_create_compress( get() );
        get()->dest = &_dest._jdest;
    }

    ~writer_backend()
    {
        // JPEG compression object destruction does not signal errors,
        // unlike jpeg_finish_compress called elsewhere,
        // so there is no need for the setjmp bookmark here.
        jpeg_destroy_compress( get() );
    }

protected:

    struct gil_jpeg_destination_mgr
    {
        jpeg_destination_mgr _jdest;
        writer_backend< Device
                      , jpeg_tag
                      >* _this;
    };

    static void init_device( jpeg_compress_struct* cinfo )
    {
        gil_jpeg_destination_mgr* dest = reinterpret_cast< gil_jpeg_destination_mgr* >( cinfo->dest );

        dest->_jdest.free_in_buffer   = sizeof( dest->_this->buffer );
        dest->_jdest.next_output_byte = dest->_this->buffer;
    }

    static boolean empty_buffer( jpeg_compress_struct* cinfo )
    {
        gil_jpeg_destination_mgr* dest = reinterpret_cast< gil_jpeg_destination_mgr* >( cinfo->dest );

        dest->_this->_io_dev.write( dest->_this->buffer
                                  , buffer_size
                                  );

        writer_backend<Device,jpeg_tag>::init_device( cinfo );
        return static_cast<boolean>(TRUE);
    }

    static void close_device( jpeg_compress_struct* cinfo )
    {
        writer_backend< Device
                      , jpeg_tag
                      >::empty_buffer( cinfo );

        gil_jpeg_destination_mgr* dest = reinterpret_cast< gil_jpeg_destination_mgr* >( cinfo->dest );

        dest->_this->_io_dev.flush();
    }

    void raise_error()
    {
        io_error( "Cannot write jpeg file." );
    }

    static void error_exit( j_common_ptr cinfo )
    {
        writer_backend< Device, jpeg_tag >* mgr = reinterpret_cast< writer_backend< Device, jpeg_tag >* >( cinfo->client_data );

        longjmp( mgr->_mark, 1 );
    }

public:

    Device _io_dev;

    image_write_info< jpeg_tag > _info;

    gil_jpeg_destination_mgr _dest;

    static const unsigned int buffer_size = 1024;
    JOCTET buffer[buffer_size];
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // namespace gil
} // namespace boost

#endif

/* writer_backend.hpp
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
*/