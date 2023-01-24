//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_BASE_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_BASE_HPP

#include <boost/gil/extension/io/png/tags.hpp>

#include <boost/assert.hpp>

#include <memory>

namespace boost { namespace gil { namespace detail {

struct png_ptr_wrapper
{
    png_ptr_wrapper()
    : _struct( nullptr )
    , _info  ( nullptr )
    {}

    png_structp _struct;
    png_infop   _info;
};

///
/// Wrapper for libpng's png_struct and png_info object. Implements value semantics.
///
struct png_struct_info_wrapper
{
protected:

    using png_ptr_t = std::shared_ptr<png_ptr_wrapper>;

protected:

    ///
    /// Default Constructor
    ///
    png_struct_info_wrapper( bool read = true )
    : _png_ptr( new png_ptr_wrapper()
              , ( ( read ) ? png_ptr_read_deleter : png_ptr_write_deleter )
              )
    {}

    png_ptr_wrapper*       get()       { return _png_ptr.get(); }
    png_ptr_wrapper const* get() const { return _png_ptr.get(); }

    png_struct*       get_struct()       { return get()->_struct; }
    png_struct const* get_struct() const { return get()->_struct; }

    png_info*       get_info()       { return get()->_info; }
    png_info const* get_info() const { return get()->_info; }

private:

    static void png_ptr_read_deleter( png_ptr_wrapper* png_ptr )
    {
        if( png_ptr )
        {
            if( png_ptr->_struct && png_ptr->_info )
            {
                png_destroy_read_struct( &png_ptr->_struct
                                       , &png_ptr->_info
                                       , nullptr
                                       );
            }

            delete png_ptr;
            png_ptr = nullptr;
        }
    }

    static void png_ptr_write_deleter( png_ptr_wrapper* png_ptr )
    {
        if( png_ptr )
        {
            if( png_ptr->_struct && png_ptr->_info )
            {
                png_destroy_write_struct( &png_ptr->_struct
                                        , &png_ptr->_info
                                        );
            }

            delete png_ptr;
            png_ptr = nullptr;
        }
    }


private:

    png_ptr_t _png_ptr;
};

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* base.hpp
x33p5lEyKESiU9Xo1dkgJUQ8CAvwdWuQqAD/1P56Al9XUuRCY/wZTfZ6X9Jkr/dlTfZ6X9Fkr/dVshRI+Y2um8zC0CvY+zA7w96HmCHPQUyFLrqWnKijYAqKIwuDREJ3AZMNFUElQyEPc/xlLr2SR69zu6EAqqtCqNzibrnNXjnSX5rq9rCEPYyXIzg5hMuF4XAkFVT0cVToFWIncN8F72Pnt+k8vaJ5W5zP00CC76eBpMAarwuMprjA2pYQmIYkZeCKrgBP4urggYSszemKOgcjx5wulx7kBUIAq0JAKlktwtlp18YUoQObnWxM0MCoxZ+dP79vtAda9zdoPxTQX5AKTUPhwiBYIDMrm1nl1ONEbHCIA7NSll05V+2/I9cu4dUKJEGxl4i5KeBXNqlRgU4f/wrYkHzjytMcHlAvH4OZeq5RqwbQ/H03NKhFTg0K5Ru1YN0/7lYItRMkD1RHhp5yQ3kvlIPRg7Tf25nN19Fs0n0TvAfyLjLvQs7oTLXkzfg+liD07+6fbcRBDxKC0kBOBvkjUVUDz6u8Q8nV1hiy5gonaSWogOpqHRIMxjThrApA/bgTFJi3pGMHIP+uG6RmjnxdJG03Zzz/F/x37m4ip1bPAVdShw/MubI6pwsggAeZBEM4cdDavI/JsSAP+jEQZi+cFRUVkGh4osYQrfyBObe+6z29CNd34dX4mNFdvnyuFPqOAA/IEJfu
*/