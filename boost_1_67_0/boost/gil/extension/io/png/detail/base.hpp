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
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
*/