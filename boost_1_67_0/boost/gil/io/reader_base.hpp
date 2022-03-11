//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_READER_BASE_HPP
#define BOOST_GIL_IO_READER_BASE_HPP

#include <boost/gil/io/base.hpp>

#include <boost/assert.hpp>

namespace boost { namespace gil {

/// Reader Base Class
///
/// It provides some basic functionality which is shared for all readers.
/// For instance, it recreates images when necessary. It checks whether
/// user supplied coordinates are valid.
///
/// @tparam FormatTag        A format tag, like jpeg_tag.
/// @tparam ConversionPolicy Conversion policy, see coversion_policies.hpp.
template< typename FormatTag
        , typename ConversionPolicy
        >
struct reader_base
{
public:

    ///
    /// Default Constructor
    ///
    reader_base()
    :_cc_policy()
    {}

    ///
    /// Constructor
    ///
    reader_base( const ConversionPolicy& cc )
    :_cc_policy( cc )
    {}

    /// Initializes an image. But also does some check ups.
    ///
    /// @tparam Image Image which implements boost::gil's ImageConcept.
    ///
    /// @param img  The image.
    /// @param info The image read info.
    template< typename Image >
    void init_image( Image&                                  img
                   , const image_read_settings< FormatTag >& settings
                   )
    {
        //setup( backend._settings._dim );

        BOOST_ASSERT(settings._dim.x && settings._dim.y);

        img.recreate( settings._dim.x
                    , settings._dim.y
                    );
    }

    template< typename View >
    void init_view( const View&                             view
                  , const image_read_settings< FormatTag >&
                  )
    {
        setup( view.dimensions() );
    }

private:

    void setup( const point_t& /* dim */ )
    {
        //check_coordinates( dim );

        //if( dim == point_t( 0, 0 ))
        //{
        //    _settings._dim.x = _info._width;
        //    _settings._dim.y = _info._height;
        //}
        //else
        //{
        //    _settings._dim = dim;
        //}
    }

    void check_coordinates( const point_t& /* dim */ )
    {
       //using int_t = point_t::value_type;

       //int_t width  = static_cast< int_t >( _info._width  );
       //int_t height = static_cast< int_t >( _info._height );

       //io_error_if( (  _settings._top_left.x < 0
       //             || _settings._top_left.y < 0
       //             || dim.x < 0
       //             || dim.y < 0
       //             )
       //          , "User provided view has incorrect size." );


       //io_error_if( (  ( width  ) <  _settings._top_left.x
       //             && ( width  ) <= dim.x
       //             && ( height ) <  _settings._top_left.y
       //             && ( height ) <= dim.y  )
       //          , "User provided view has incorrect size."       );

       //io_error_if( (  ( _settings._top_left.x + dim.x ) > width
       //             || ( _settings._top_left.y + dim.y ) > height
       //            )
       //          , "User provided view has incorrect size." );
    }

protected:

    ConversionPolicy _cc_policy;
};

} // namespace gil
} // namespace boost

#endif

/* reader_base.hpp
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
*/