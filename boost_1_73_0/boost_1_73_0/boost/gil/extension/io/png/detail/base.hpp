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
umjjRbFjM4cWsa6BqXJXcGlFID9wgdBaeG6WEGQQpdLjvE7QtLClDlaEzNgxXSuNLm8FD487w6NB900nfNru9c4vekeVp8PO6KIfPuqftj9WnqC2Wfho1GkPSEjthU/fdUZIkN8+64w6g9qH1r0adI7OB8e1ZyilFD48bQ9HWBJG/t6K/CGy5KAsFoP0Nxesxrz+P2ryAdKGyj6+UcVB4fJfV3TORE9u8olNNXr5kHGOUIoUg7A0HAIq4rGMndAG5OPhdjVJjMhBGRyED2vPnVhkBs0cg4ShpC4gTQLdYciWoPdHKnZpkEGRr0AQ7aH1su6ure5sUoEmc0lrfa/ZlBplU1Vg1arVS9hAYtLhOv5DZGD4bt6noSJ/oiXJjOt28+x4oBa6X8bZu5o0lPtpGn56kl1zoZ+wOGK3s8ttsZNv26fDjlTEa/q26zl4eyTRmFki+US9QEqx05Ok+iKepAs/BrbyZmfO1pz1gUF+vJVTvaivDrwcbbJmqa6NVAq23LfWCi805tUkodhEVR6H1DT85wbOFpNVKmYx1urtRedIdcLlwsacJ0pE260356OTlhas4NpHb86PP4ZKHowBKv56/O+lQcQiO4ufnicxb6Ir2843TagkJ4gwikATG82YuLnMrHiIiAGXIW3Z
*/