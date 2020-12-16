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
A1nnf+/q/G+N6LddOdVvfDmr/i6rJp3v/d/b62+FSB1fBVyv/iZ76++b06niw2Wv1/ve966q+NXVVPGCsv4q/rqSqnj+AoHoo0pU8esLqOLJlSwVc6ZixC6jiv9SSVX8QiVTxV1Fxca17fPfGbsSuKjKLT7DgOKCg2tWlriVZQuF5YIaY6BDzRjlrqmUZr6XlfXApXALSKcrqWVpvXraqq1aWpKZoqaomZKZaZaaWd1xNNFScWPe/3/OnQuIb9HfZe493/m2c853vu185xuAbGkncJmwuHMMWDz/ebLYtFjcoeHF9HObOmrXliCcbqiJHEyoxOkbl1zI6Z+iLU53e16q8XV0ZU5/83yV9hv/Fdvv1tpV2m9x7Yr2u7BIGDyrgcXgPjVlXFD7Av5mFsm6OMC6/zlH9z+3CH8H11b+9q5t89e8RNrvY4ur8vcmmiXTju2/6uc9b5O/MbUvpp8fnaP8XfgV+ftzrcr8/aq+8nfPaiHMyvrk74eryd/C+jZ/65G/3g3k7+v1lb8v16+inw8rfz+vxN8pyJZ2iJcKfwe5wN/Vs8lf4pK//etLhad8eC4s/J0k/E1D+TgPbi78TdZEoptznYFMJZc57kdyHq28cnYEkgb8z6jKnD01uwpnb91Ezv4VW4WzR2IrOPv1KuHsp/EWZ1+LYYm+io2MlwtWkaUrYi2WNnleWHrXZmHp9Fhl6ZRY9aYEljZuYo0fK+nj++JFH8f/F2YmvEVmdoytoo+NxgufUz7u20Q+XhpbmY+ueOVjQ5SQ679u8vG3L8jHUrfNR7f4V/qSfPzBrXzc7rb4OEH4GKuj5PbQWTi+M0JMbMfgshPU2A8e5R2K1nP4N/4TaCv2N3E/9aYFqQMIlih2zJECPOSMlvWhS/Q+4A0zHQ7LkrVoM0jR+OxKQUtVtO8a6nHhMvNVIPJKv2QUfQvsURTtCkX70EYba6E1UrQPFO2kQ9Cm2Wh3WWhHEL6F+16K0K8J7/9CGKgZbuxdJWn8TdP4WFFut9OoY6XxzkpB665ohqI1s9EOPqtoTyna5Yo2QtFONIigfWGhDVa0vz4XtK6KttVGe9FCa69oXytaE0VbaKM9aqHFKdrbinY0LG1mio3mtdB++1zQJivaRkUbaKO1sNBWK9oARXtN0W620c4UKNo8RbtJ0Z5QtDo22rcW2mOKVlvReivawfoRtPcttDsU7ZcVgnadon1ho+VbaK0UbaWixSjaizbaUAvt3ApBe0HR9pYL2qM2WgcL7TtFe0TRliua10aLt9A+VLSeijZL0VrYaMEZijZN0RIU7W+KdiY+grbWQstUtNOfCVp3RfvWRvunhdZJ0bYr2uWK9r6NlmWhNSAax7/nNR0IpDlghiXaDyu1ntU0vleUUXYaiVYaWz8TtAcVbYmieWy0WhbaQkVLUbSAol1mox0wFG2Kol2qaPcr2p/uCNrnFtpAogHBY6XDgs83rIIv08p/p7bTVyrKYjuNcVYajTWrDxXt1DlBm26jZVhofxQCTU8t0qXANsVbBFE1r4/k2J05Uo/djSVIXgHVFN0dbFxrU4Or7lvpVE3X4kXRdIdmciUwbnZtGZbd0zQKXcM0dD9yDzq+uNIq3cniAuQHE1woQiDOXgjtPWMmFT2Pj/P+D5THfPMZqUMS3istv95qcBDaPYo9li4hD5fTByvl3nT0MEvdUj7zwVet691rpnaKqR0lLp4X4niMdCziBGVjVk3zRmDhCvy1s2SFEydkpnDkO7XYXuNcLl1NpL+ssfbCMW6RU8e4by6XmhXUsjrKg1HsGF9DqBiI6vhnOWEFgOn4x9DxzzpUH6wAkYrfD3PZFxT9ehWXe4uNyHLv+bU=
*/