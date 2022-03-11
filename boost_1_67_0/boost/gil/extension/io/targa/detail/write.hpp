//
// Copyright 2010-2012 Kenneth Riddile, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_WRITE_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_DETAIL_WRITE_HPP

#include <boost/gil/extension/io/targa/tags.hpp>
#include <boost/gil/extension/io/targa/detail/writer_backend.hpp>

#include <boost/gil/io/base.hpp>
#include <boost/gil/io/device.hpp>
#include <boost/gil/io/dynamic_io_new.hpp>

#include <vector>

namespace boost { namespace gil {

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

namespace detail {

template < int N > struct get_targa_view_type {};
template <> struct get_targa_view_type< 3 > { using type = bgr8_view_t; };
template <> struct get_targa_view_type< 4 > { using type = bgra8_view_t; };

struct targa_write_is_supported
{
    template< typename View >
    struct apply
        : public is_write_supported< typename get_pixel_type< View >::type
                                   , targa_tag
                                   >
    {};
};

} // detail

///
/// TARGA Writer
///
template< typename Device >
class writer< Device
            , targa_tag
            >
    : public writer_backend< Device
                           , targa_tag
                           >
{
private:
    using backend_t = writer_backend<Device, targa_tag>;

public:

    writer( const Device&                        io_dev
          , const image_write_info< targa_tag >& info
          )
    : backend_t( io_dev
               , info
               )
    {}

    template<typename View>
    void apply( const View& view )
    {
        write( view );
    }

private:

    template< typename View >
    void write( const View& view )
    {
        uint8_t bit_depth = static_cast<uint8_t>( num_channels<View>::value * 8 );

        // write the TGA header
        this->_io_dev.write_uint8( 0 ); // offset
        this->_io_dev.write_uint8( targa_color_map_type::_rgb );
        this->_io_dev.write_uint8( targa_image_type::_rgb );
        this->_io_dev.write_uint16( 0 ); // color map start
        this->_io_dev.write_uint16( 0 ); // color map length
        this->_io_dev.write_uint8( 0 ); // color map depth
        this->_io_dev.write_uint16( 0 ); // x origin
        this->_io_dev.write_uint16( 0 ); // y origin
        this->_io_dev.write_uint16( static_cast<uint16_t>( view.width() ) ); // width in pixels
        this->_io_dev.write_uint16( static_cast<uint16_t>( view.height() ) ); // height in pixels
        this->_io_dev.write_uint8( bit_depth );

        if( 32 == bit_depth )
        {
            this->_io_dev.write_uint8( 8 ); // 8-bit alpha channel descriptor
        }
        else
        {
            this->_io_dev.write_uint8( 0 );
        }

        write_image< View
                   , typename detail::get_targa_view_type< num_channels< View >::value >::type
                   >( view );
    }


    template< typename View
            , typename TGA_View
            >
    void write_image( const View& view )
    {
        size_t row_size = view.width() * num_channels<View>::value;
        byte_vector_t buffer( row_size );
        std::fill( buffer.begin(), buffer.end(), 0 );


        TGA_View row = interleaved_view( view.width()
                                       , 1
                                       , reinterpret_cast<typename TGA_View::value_type*>( &buffer.front() )
                                       , row_size
                                       );

        for( typename View::y_coord_t y = view.height() - 1; y > -1; --y )
        {
            copy_pixels( subimage_view( view
                                      , 0
                                      , static_cast<int>( y )
                                      , static_cast<int>( view.width() )
                                      , 1
                                      )
                       , row
                       );

            this->_io_dev.write( &buffer.front(), row_size );
        }

    }
};

///
/// TARGA Dynamic Image Writer
///
template< typename Device >
class dynamic_image_writer< Device
                          , targa_tag
                          >
    : public writer< Device
                   , targa_tag
                   >
{
    using parent_t = writer<Device, targa_tag>;

public:

    dynamic_image_writer( const Device&                        io_dev
                        , const image_write_info< targa_tag >& info
                        )
    : parent_t( io_dev
              , info
              )
    {}

    template< typename Views >
    void apply( const any_image_view< Views >& views )
    {
        detail::dynamic_io_fnobj< detail::targa_write_is_supported
                                , parent_t
                                > op( this );

        apply_operation( views, op );
    }
};

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

} // gil
} // boost

#endif

/* write.hpp
My0Wnq4wr11JiZXhlwe/Ar265zMEba3L62x6j0Tyzlh3QYOD4I/pnzB1ANly7AD1sCDqwXFqcSuDhGNvBKnaCPQSZikzALdOJ5/judlBs5U+foCV1x7rZ5ligLreCT3wOJ6lDQ9dqT/RXFLdU0sVbGXmTOlfkDonp7D1kSw0z23KqQgyI/2BLycgwH1YlEf9ebVB7QRrUeERpd8tDc7ldsSUCIdB+86oeEceSSkdH+yG/JC7xonEGOuDQbju4naoZmc12G2pLtrWRLAunlT7iTxCPD+lnXT4NnxCmfP2byeE+ThBp1SkRpaPemkLGytMFhNBZwanPe/opg6PNfVxPyWdq+Nt6fCCMABGt7ughffv9Cx1OJeOri7RmJ+nUak9G6N/WhZ3iZ5ageVPyVMnYJIbQrq7QpfwXf6bM+HStBocT1/XmuatPO9aEFXK9WWPWMvUYT9b0SMy+BYoo6Ms9KxwR+y6V13paLiht8UzphcqucDBtuIgldUjYT3JHQ5xr7R20FlkKJ7dFuC+6vvITzhxdPpRrqhEZqlT+3TPw+Qu4ruKlRDlaga/s+rFIHD1Qea7Ubba9lT5IYUty6luFsYF5mFRbWmQNVBFKi/sRxEaAPcLwMlv5e8KfqgwQLfFGkNVNGNTaK5fCyX80DP03+KnIaC4OlVdyVp8S1LovzckioYUORAWbHJw8f92gK8Wt60Kwgl5mVyn1CwCFGERV27jkixLXdtU9uuKLww++5SOQSrLv53h4IJ6Zc1WgQs7MYB+HySKl7tfA7JgAawWUEz0g6bUamI73m1xBcH0xDLyFCy9dcbEhWA+Wy1LvQcZrbTTPzVp/wAo4onkCS9raaihc5gEjfa1kY3kCsEJGB3v18AdljA5Zx1jaiUOtXohkQRv5thIb8ysFQl3HheIRAhw34PrM5NLto4Zee6gdw/C86tZSzQbCwy+X3R/bdiFtZAyj5zWE9XfvuUHNbXhXqDpsaReR9I8RuSw3hRoy++SDbVc3wj+p+XpUCs+95FDiX9YRjQngbcPfwBySv0flfVIuIjObmrhphWilN/IWSr4I5dV2/IqPh3nYG5vNtycw/ut6N5UpP2JcF506awQAtSqV2yeXNBT+VUnQPCNJk3Jhwzx4muuiDsijsGcrM/cJunpA52/wQNeal9O8EczRHN3a0m1aNvlusjWUfUCfoWCGZEoZyzrDK1XcISeMkg6fugg3my33lqqjyJH2b37Gr3uL00cbKx/wpHbhZ5Tfko9MJqugx6RkGPa+RZDGw1/dVzba10C/ACUv2MRSlvK6z++PGs3BegH58JZ858Pdix97yrDIIX9bnJZgYbs2IGxccxpW1FD24+4wW2kztU65eURfkt5y0QL64l/0Bf8u22dMgV4dgniFLN0dsb/dQ6vGsZ7KOPl4LUXBU2imR4C53P5GuP7OfyusBdJIqO7MfgBnCXtx9p7GKVQzZCIsCKIQLbdLPLLaWZj9FX09hm02MfGSXKoYXHljuDW13OaMiSumiZGAlD7Tm/YPojtv/T7clKXu4eJULlf0N21SuClnY8CEADDfUyhNkwDyc7/F2FA8V5qNdRAsMfvHljlngnbFHNplt1imvzkjQcqvXVrakaIbtQnU/dfrwPA25NnTum9slpHPL3ALQFJa0UFJesCZ95/HvAs/wVNKdMzdjujT8IVgIWYNyCI6SpJ+EuBhmHIAIoi6QCiO/J5c9v/Z5zPv4VA4QPhXdbJNRSXpJ4XIeIlPleMLB/+qclmQKEuS3JTlPvPhudHcRcNU0w2ZqR0LoPvanq+KEHQl9QESO4c1ZvXympxE6ODhM+rdx1ELGJGSu5oaLgIbc3kKIHvecyC36Gnd+4TmjqplAk6R4QPsIAk2fzwRM9SzTra5yOVNWzxHlUFSsBx8akkT+MIlLprqzIezW6FNEmbNjLiKu8T/SKmgg5uCPB+KzXi4yAZwxVUv+sZtsJ9IO/SB1xWKHblPnIQ9pAG8WN0M3iCWyNLg1CMsHeEcQnRpErKQpfdpqoqKmg8WM0cYo4wF8whQ0Bwq1f9QJYPekWH5FywwfhMfo3UBQ7B35K7tw8loVbhPJUGsyGi0B7ha9FFOvI4HIpKFWD6Y++mKAUyDUMgFwgC72nSEE0viJ6dZapXgn/MMatb+NMFyjLYXmzs2kZ4YgDcF97NXFEU0tbmVvg49uzHBkygoLrewtE/xUzzJO6LOyymoa06F4c0b7LToTEaIBkYg6jvnlfLAgTh1KV0FrmXms8g7MEAJcHSr4KU+thF0dGLasJvmheRUQ/E/JcnVubTX1BFTfOxY59gl/UzAAGcKkK+2DxA8+GMRh5rQmMS7ZBUDisl4Mx1dFX+SbPtv8zN2Glv6MzOvBDk6vc1haP6YTCieO6rffP6SnF8Ncq1q5lGfD+6uksgNx+jU8YNndPk2LXsx8ah4LPs4SHLklnULlKP0mTZIEufrcCpExIqCc+Sk611er8c96KHwK5Tx4pjyW0am2lgwVpyeytLArTiZ7lNTwXcSVtsexnoFQBH6txZ1+T+B23FXuDzAelsjtmmfLwlcXchevSqfarJfBE4u/mHd7M4WjpBYfPw0K7eYUI5YpQO9tnTRNQCRgtgPwfoKKbJNf8gJwQn/kw4FOtJZA7h/lTzZRMCDhFc+wy9H2hrfCyIfD+uMkTK9q/BTRjKribaw8d3Aqz0L7gKt8kQoljivRcYtAjuixm/H8UOsCYxdJAw+dlpoITi4wNdZUoDhfjUmtXjZK7YXhar56Y1pXoV4q77yt6Q0R/h1B7IyGeCydp+Q6Bcac3uJqRYKJkDCixcgMbEM6tAED76g3Gu0YQlgfavZ3jwJj0n8foPSS2Hn9HL8MAFfr6RQJRpAUJPtjBwPwA/QUlAAL9f3xKAPXzdV90ifo5vN0ecLaEcMiV9y5NBiNEghznlJ9lWJPzqeM+rkmR1n7yrl3chBv7yR1MgnPRZuA6R5ybMl7jpZAiPX4yZZmwFwB3o6isCzsqccwl0Y5c8YGoYRj1r/V99qJyu+ONyE5bc5M09WOf46ORN7WOVp6nypk7K6tuSLhxY9r6h4gCVA/T69aqtCtqmisgqORQNJbT18dxQnfp2EXh3YPPTkN45it19FMKsK/A/LogyLtUQZJqR2wNvT6z6RzVb//T8oFrn5gUsrWrQCZQYsWKt6K0cry4NuJg5I39AdvJe98YJPa2QZOLxC3hngY2CXB/1OghTlGLRsm0TToG4Z+NDiZRTq9mahxxe+lXI7bo2gPLAG6CLVmVD0EcVaeYZE0/eqkESZJezntiRlSr5Z1h1qhT1leqL4TOZfw+q8lSZUaGYXjG2tF5tBLAgzOigg8L/XWARe38KeWhu+8EUwTaHj6Lt5TQNWgLynFiiNQGw3o2OzprXIxak0WU68yNP/NRPQd4IsgpmDoeYU1XR9JYZN62vlzTZeHDazHZt8Py+zj0wL9VC9jlxc5DOn2k+Qnr6K0xp4GMv7GWcgeeCgMZbSq3v0Bw4zX3nXLRWyMgee7mjFzCD8bGXw1+wtt722+rVClHgNuSrcAeOeFfnNRtdubHJso3bpJXngkGxfHrnm+yWZqNEsHfhdYbs9NBeXufubeLbAxOom3XVRgWs/vqZZoa+w0RpWUSTMMVlilu3CWEZNXcwyZa+EMF6tCZv4cxQZQNl+X4kjABMvQq2bKB6WVZbVzGpSF1LFbsEeAXNj9DjW1hv+VgjpRZiia84/WylmlEEbJw+beCdwpV/j6YXvEhwU4OKsGdf6CayLKI5Mv2IWB/ImRF3PQFSj+v7XKYakQDrgwHWqgGcePOSrXmicvhPGqXihTxETRkCXYGyX8JmLWqCfNcK/s61ZorQx4og7NVo1UtU2Ma5TvvttxT02yHAhtRqeQKK7vZ7UTyI+b2WDtscefaiM54DnKoUQmL5Um6DpP/45rHxDxRPo2v7oeJ4eAED8gUGnpxUSERsdIvbukbu0NIhRscAjYMWNY7xU/2KH7JbveKQ9/NP7yPryY18/i7tvmLdZtK696aBP72O+9GZTfJbWu/up6M1+bbLmFiaZK9od8jMwlxc/udeBOPNZkNnaGJNVoERGk2jWA9g26CZm7788ZiSf1NuFolQLVjohcui67om19HLvWkA9e7+8KbKckODn3ZPZTulNj5z9/KI4X5zcN+YKjKFBiufCHo5KhhqiN/X5XxfNYLmjTN6aGZEX5PXYnKuaQYRFO2+GQ2c9/Z0UHibeW8HHbR42OU2AgqrbkrwFQCCSUP3Av7Wja6xf+gF4Esygzq7ujI1mgjEi0jE+zSKlxY6QAGfbvkGRtfBy696AAAs/9NFjDCXCcbc0V+St4ndZgrbooaSk8KOmSoPQy7Wb7DoyyQKwk07+zKhJSPxfmEgiLhqO3Q+aJqcx9Z0D2nfhyT9DkuVCyZhjzVzAR2V1rY9InUxOTkU8YuShk09/XqfhxlrjMn7ofBkg63k+JOPQaGKRkWnCccBCHDU/RGJ/gKA5Ke62RCchRxjOeu0iBGQ/e4hbgWzGViXDahg6LNYew6FhWPiNqD1Dqlg2ysqd3+ZEs85AdUE2LZbfqitexQH2fdPTNuBG6r4gM9xx0kLuBPrCK88UAZGRjeIYnnjjhwDPcsHJvgL+ki51L7OjaYLDGkpkP9Ac3fbDs7w6LcK/EGLHtAvWaYph9jgcU3etvdqkrADL32oBljfJeFfVJ+hmey/fDUg9IvkuRbqYcV3n+Ow+e1fqU4+UcDd9pyq0a8YaL4UweHpRtXC709LdPm+lCl49bjGldlhZMa4d/vz0gzx+89nmiZWJq7IqwllK3lxsUdRPFpJzbfY25PjU4RvJPI2LT+0lTnohlgaSiWSzlanHi8s2jKc7Xwiy2tSY1JNLaDMl4o4FchpIdXkYk1MKQNJF9SSEbgGpG7Q4mAadcqut19RyYLv39/fgDsAgMA/QX+C/4T8Cf0T9if8T8SfyD9Rf6L/xPyJ/RP3J/5Pwp/EP0l/kv+k/En9k/Yn/U/Gn8w/WX+y/+T8yf2T9yf/T8Gfwj9Ff4r/lPwp/VP2p/xPxZ/KP1V/qv/U/Kn9U/en/k/Dn8Y/TX+a/7T8af3T9qf9T8efzj9df7r/9Pzp/dP3p//PwJ/BP0N/hv+M/Bn9M/Zn/M/En8k/U3+m/8z8mf0z92f+z8KfxT9Lf5b/rPxZ/bP2Z/3Pxp/NP1t/tv/s/Nn9s/dn/8/Bn8M/R3+O/5z8Of1z9uf8z8Wfyz9Xf67/3Py5/XP35/7Pw5/HP09/nv+8/Hn98/bn/c/Hn88/X3++//z8Abj/y/9mz3F4aQT5s7EE7QRwbGPOAZ+AQ11/d//42E41TcqrdIBC/xlXDkY3fTkbH/xD3MVeH5QVNsB6TJrGVRtAEJglVIRFM29ZReDmHZ7c+4iufm0CVP+miAAtI7OMgmZ2l1NOfulwugqiN/uUuxzwpILOEe3txj56ApQf0cEC5EGvgSOaah+hO+nSa3BCGWeXD1ZjT6bF2V05iS2NJt3RwhcGh68PuWX95ftvxIL6WBaVrPmcFIGazUu84cTwLnLgBOqNxBzZZ7XUmkhhgJCdIXykswauj9XWWVXN5b3Db2cYF1+zPCkIqm7YcDDtiDnwhZpEPXMS7fWDY9C1bW6WG7cTFtlEjwlSZTsYtSVwR3C/Vt0HfgqxCLVsE8p2nBW6zK7HjVqWeayCs1yn5li7maMcELnpjALmQKQjwF39pb4TzA6eQxo9T8jHYtuiTRT2NQC1VvMfgK+jxZvtltPQAytrGG14WcB0JMvlpZ3qC4efhhxfRvgnlwaPnhNbRSPRoP9ey/mTJCxbZQ+RxXNc2Wg+g9Fa86mrcN1/MSMMbfioLlrKG8rFgsocysWSri0I+uWV2nyqt1m6yNU3KsXdH0C77Lwa3nzKe7rQyf/SlxZ2j00XAN8kF3FCy9HSGlwH5//b6Bi8Nuq2fTXU7XxW3GfluVNX8LQhPbMnFBfsvMfFISWs6RJ7k+srsmEEbU4uMyF17tCztvWNlzNiTvQgn5PnuojQ/iXMh0lqNe1ewOL8ISyIi8IgarhwTE0y6CGKvO/AeINneo0XnMmuowfk+SDdsNblwKTAZ+gNKZiRAQIp4PH+qGjQVc54VqIHpea92JRNDTaAe4Uo4cbYE+x+EZq0MjnTuu3E6IiVBqgLz9cossGskty4HTCiZqbluKcw6PG2s9Zb4evtq6oVwUgQ1xx6BFUun5QmCLoaJOBJuD2Egu0feeWfE7bHKntxFhM9ORBaDPmHCIb5Onhh5b8MSPgNnuRker86UzAHTpf96esB2Z1wpmeBuk+Jj/mFpfrloiLXr8zMUEnh5PoobKSpqwXsxGMlOMR7yBPdB3erVGwiu+3FONcbSguhEKlbfS1nybm8QdvcwvmpJVRtLW8ZW9ZsbWHd6SMCRNWEpiJWvV25crPYEjdZU4txvlxD2eySqtEJPofxTriOtBopp24CN5cPleczrOC1RonD9x1e+hPAECA5voTKVqP51SWq9ahKup8/jktok9EgmdxiOdFT5sSn+JIwW4hnebi5Rv77hHfGggiR7v9LgGqdHl0IPMRc3swJJL8bI5G9FZaH29eJnJdlIUHnYf20N20VpcaOoKyxsEGl+FJ4OL2bf/yfBzCu8HlxwZCnVrsMeuYOD0RDLiUOvqmruxFALNrGG+/2wFoQF1HKJJ4sSbMfmPR+/H0wlr2STHN/zQqu2/wS0CalLnhYqUunVWZMpsqwOG6f+M1RZi3ZdhGqjXzWfJLJz9Jzh+0+6wP5v76i77pvi7duaH2xX5bAKA0/kNUfgDh8Fpw4gCJkUPXK2XMwi9bdRhW9vtX7pM4OvcFcikqZ5xxYYCGGkn66hFDCN2EHvUBdZrUuRUUMbavjTVLgQizaGrRBlkYh700qf6iQRSmaRk6zW6MCmOU7F5YuwVFshDQXgyMYPWO3VJ0WvjxfcPFEPDnsTcw2vWXsF95El46dZxcAaEDA7Eb6kbBGlT3KhRr6ukrt+XeTs1pdSnyq2WcY4EaPMVCUtv/IThXxg7NroJNIRzItxvQpuFdoWLHEiKAd0WC0LpSLieSSh7Zd3NZJnGG8iUINZpTM8TgaJMDtuprAJN+bePU54nAPXbC3W9Bb3X0HmDQ7rgRyhXL5bmDREG5iRjL1iO20o1bdDzD3faG/CL9SGXTZOM8sQEugqN2J053tqq7TKsZXo7MkA6LXo4aUN9A6UYPPe5EWb+uKAJBm97FSVLRQymFVQfcUPQEo6pZApTu9+rA41tbiKJTkIN1WzlfiynHhIw4Z9y5pAVx1EHICZPYfnpUOTgCxryEvTO42vtsCX0yu8ZNuIwzavOXalOSV1YEM8gohieiHUT/mM5uCX/KkwJd+NvmFzlj5HgF+p63U0ozr6P997TzdHaLbgKOTNL9Ol3ZxxoyEH71GVF5ZgK5BJKbWhgY8aCjpYYAkq0Aqlqd/YCcBRMdwI/OF/2YEFYsFSZkFf508F5ESOO+B0j5pFESPWdM2pW/6A/hvyQ+Co+717y9FoZkS66RMi0KpO8v7SY80usSxxvFNmUDL89sqVmrS8zm0u5ex3SDmSJGOcwl+kXCeB/BLyHeHfWw0BkdbzQvVzdM0Ug/IkDYHrl2uyuhXSbaK00WaTmxIDVimA8mQR1jCDeufhEkBDdDAcFtQCCsBudEsMUtiXx+QF/IRPTRQhzY2FotLp3oMqMKb7RTiu1WtFiqFGiZZ1JgmK6eDF8mGUYWkCR5esI6Q0N2Ry7jniLIT7g4UEXnjEfYnaxgMW3FrGBRGghOhVcGjHawz3zWjPtG25Bd58KFbqFte+SCAckn4O7B5DqFC16ncpj50q3dcnTQCHB9DTBAYbFcYrCEBTZ3NBvk5mMDTw/4rHvssfjBIyep4xRtzgpb+qmXYO1XQvFqcNKYrc16pC+S3XlboG/N4OjpoN53/RjrUV6a7cyUeRaea9DrzuuqlSmDkRR0FGKTWoDzAaMUm6LGexG7otwo5QyzQaETsrDsGbBsQE8+dpl6n6WkDcC/WfV6HcUVwD9i519hef/nxJcxSgrbDrT0sn3L6fb1lT5+L9cuBKxVPtAXFuZsG2luFR2usaepcvxsTlm6L9wwQWMYRvk7QDFuEALeycK/iNIIqMNB6BuagQD8ZxULeKhqkFTCedh6b3ckwODv4fNux/2BHu4KSG8oN1vRjjhgg5ElhZJ+ONXQoL4uFXmSUsApx8SHpEiNTtMrK37s+jNUvpPHmJZqM+gfCcTfHrpeZtzJGxrUPZFbs1EPJbqgKREFvRUvAZFkp7y3Dc88B8GnvQ/ci8ZAhFYLKMb3zmnL3yjHuq2WFridXxTvO1td9wxlBG7AlaOo/4bSVC5kxJa5DtdPv6TEK/uqtC66wQrcuzUdxjEHdxcuag50zijxhKYEd+ss1VSauyBMpfdqqD1ZsxxQ2rUbl34zbeLEMF2aRi/RFGfGuBVK6hIgVnYL1PiZXKT1FhEJeCACgmkwr8riwvDrQhGVVr1m2b9rgoiUPpJrlbKypd+HoHCrXgFENhB0SsyuiOPWrQyTFOJtkWCBWz+GLlamezRuNEhJNk8jUhCabcZYmN368e2A6/0AkC3tRClSibGRB8NqH7EPsFJHt64CrjqQxfW9GyNzoDlyw0i0cpnGzGOKnpYcqICEwmrUR1IedBHosq9bzmVbKCkgchps7pOVNf9ePIbfPwLnUxoEgRM/z4t13YLgzGFMKl0A0penLXZn/2/xwAiARHKZndqjx4u1vGIoTzUtCF/qCgzzKAVvelRj0lKNS7toWDgALZDolfLpMB6lWKJ9x++mZcEC2SKDk40dg+3sJOu0p745mZKEv836zm2ggtgk3YKBa4PgaEmgmuF+dbLL3n30T1c8ZP5G1XCcPes/nKhrkm2GkECGrpqPxrxlZLkv4jNX4Lzbf3G79KHVXy9uFe1PGWdN5q7nl3AAGLuCUSzSNinRIqrEVzRmP3BeRqUJkEfP6QWy7s8J9ai/JuI9kaC4fJYfQmwoixJor+zgJN0jkmCl/ID9zjSwOvyhw701mGJP6C4YexzOWOTnTONG4FrnT6doSM3EPqDdfpqL6u4JCDwhdpwl/Rmo3l7lfTFlSOwHZ7x4KkvKBSEgJYnIyfRoKgLTghio=
*/