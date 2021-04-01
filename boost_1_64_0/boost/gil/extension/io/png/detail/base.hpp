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
hzWW19dhG2XdQTju1+cURK/LRgb6Eyoru7MAf6dWEwyvdKMiVZvzMzI4TxawhdaGpN8U2PPGJKn+zalcjcPCdIMRonPMQaBNV+35EE8Zbs9ASvHssnGr5gkhTtYLqHS6DaemZT1O2DsDisPWXuEQC4Fp3p7vXhdFvPQH2MXIRjNytRGCkO3MuNQ4lLE88MjpXWeTV+Kj1sxy4o85qwOCla2jwVeO/yThHY2t6gOE5vK5tI4T5xqFJoFIaBt43hiFJSYbis3ija6Xn5lQ7I9VInuJziz0SJ8ZAgPJswn3S2hXGs0EX+E+rN/gj9Ki7qqgW+AlhBn+tKFQXLUzo0dAhwmb/qfKLfmKpeRETgDWDIHPeO4TVnxjkCS+RvGPsJ3svu4akb3sz5eR+QqvdXsAaRfG5L/lPVMNIk6oLUJRVFo0a3Fi86pXyvyGU7mMDSJPUqoDQt73y1iOgUDRMAd18Sx74JxZZ0hVk4sNAW9mAhi4SIYVlWQPb4Oje2wQMUVym5qSsr9LBOa24r0SsC/VpSjm+h1Z/4/iE2/sZ7sqqofsIkB76kVPeLmmcw==
*/