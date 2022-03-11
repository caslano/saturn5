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