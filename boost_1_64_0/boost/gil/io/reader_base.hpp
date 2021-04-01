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
bHHSWgEnvJvTsodD38r3bbuTFTwgxh+BgqJz206iCl1MolF17JiQ2/m6nUvhpBQ0mUKDmFaG5wD1HPHpNVtnP+uOnlIaqUzWa/l+lNNv9agvW7QYVz47JPeCCsSmcqf+VUYyO2Pszlh9uWu+RS6wwrfR+IHZW3dFGm5+nnJDlA5mQAClwr2MKLbooqy2TkLws0KdQHAYSBQhBnyxtp0Zs/sayHH988Xj+FBN84uVjC+PP+bGxRdtU190fBWlTJ4hH84srAAV0APjJiSBbQaefAYE7mknH8wBRvUbFbiT/XquK4oG+cTHIHrvCF42hY6yMYwlDzSeEvVi9CkgsHXmrf279w2Y3rwnY/d/Xp0SdCkDJjwzlP1QqQdkGYdMdXMTDk6asdM9RyCHQxzNYGxnQkK0J3hsp0QR4HukQ7mOSdNCFnSi8UJv07zhagN1C2XstWonUKr4M3Y3d6ed82Gjx9wD5XuBJWKcJWjaTFGKgFZaMQYDdmr/sH8uKg4JIUZcaEExX1X5v4gdOP78xm+JmwV8i68E4ioYK8xhiGs74I1dazk35ApFedcKuA==
*/