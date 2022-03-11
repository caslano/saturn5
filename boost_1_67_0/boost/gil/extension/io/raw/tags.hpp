//
// Copyright 2013 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_TAGS_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_TAGS_HPP

#include <boost/gil/io/base.hpp>

// Historically, LibRaw expects WIN32, not _WIN32 (see https://github.com/LibRaw/LibRaw/pull/206)
#ifdef _MSC_VER
#ifndef WIN32
#define WIN32
#endif
#pragma warning(push)
#pragma warning(disable:4251) // 'type' needs to have dll-interface to be used by clients of class
#endif

#include <libraw/libraw.h>

namespace boost { namespace gil {

/// Defines tiff tag.
struct raw_tag : format_tag {};

/// Defines type for image width property.
struct raw_image_width : property_base< int32_t > {};

/// Defines type for image height property.
struct raw_image_height : property_base< int32_t > {};

/// Defines type for samples per pixel property.
struct raw_samples_per_pixel : property_base< int32_t > {};

/// Defines type for bits per pixel property.
struct raw_bits_per_pixel : property_base< int32_t > {};

/// Defines type for camera manufacturer.
struct raw_camera_manufacturer : property_base< std::string > {};

/// Defines type for camera model.
struct raw_camera_model : property_base< std::string > {};

/// Defines type for raw images count.
struct raw_raw_images_count : property_base< unsigned > {};

/// Defines type for dng version.
struct raw_dng_version : property_base< unsigned > {};

/// Defines type for number of colors.
struct raw_number_colors : property_base< int32_t > {};

/// Defines type for colors description.
struct raw_colors_description : property_base< std::string > {};

/// Defines type for raw height.
struct raw_raw_height : property_base< uint16_t > {};

/// Defines type for raw width.
struct raw_raw_width : property_base< uint16_t > {};

/// Defines type for visible height.
struct raw_visible_height : property_base< uint16_t > {};

/// Defines type for visible width.
struct raw_visible_width : property_base< uint16_t > {};

/// Defines type for top margin.
struct raw_top_margin : property_base< uint16_t > {};

/// Defines type for left margin.
struct raw_left_margin : property_base< uint16_t > {};

/// Defines type for output height.
struct raw_output_height : property_base< uint16_t > {};

/// Defines type for output width.
struct raw_output_width : property_base< uint16_t > {};

/// Defines type for pixel aspect.
struct raw_pixel_aspect : property_base< double > {};

/// Defines type for image orientation.
struct raw_flip : property_base< uint32_t > {};

/// Defines type for iso speed.
struct raw_iso_speed : property_base< float > {};

/// Defines type for shutter.
struct raw_shutter : property_base< float > {};

/// Defines type for aperture.
struct raw_aperture : property_base< float > {};

/// Defines type for focal length.
struct raw_focal_length : property_base< float > {};

/// Defines type for timestamp.
struct raw_timestamp : property_base< time_t > {};

/// Defines type for shot order.
struct raw_shot_order : property_base< uint16_t > {};

/// Defines type for image description.
struct raw_image_description : property_base< std::string > {};

/// Defines type for artist.
struct raw_artist : property_base< std::string > {};

/// Defines type for libraw version.
struct raw_libraw_version : property_base< std::string > {};

/// Defines type for unpack function name.
struct raw_unpack_function_name : property_base< std::string > {};

/// Read information for raw images.
///
/// The structure is returned when using read_image_info.
template<>
struct image_read_info< raw_tag >
{
    /// Default contructor.
    image_read_info< raw_tag >()
    : _valid( false )
    {}

    // Here, width and height of the image are the ones of the output height (ie after having been processed by dcraw emulator)
    raw_image_width::type       _width;
    raw_image_height::type      _height;
    raw_samples_per_pixel::type _samples_per_pixel;
    raw_bits_per_pixel::type    _bits_per_pixel;

    raw_camera_manufacturer::type _camera_manufacturer;
    raw_camera_model::type        _camera_model;

    raw_raw_images_count::type   _raw_images_count;
    raw_dng_version::type        _dng_version;
    raw_number_colors::type      _number_colors;
    raw_colors_description::type _colors_description;

    raw_raw_width::type      _raw_width;
    raw_raw_height::type     _raw_height;
    raw_visible_width::type  _visible_width;
    raw_visible_height::type _visible_height;
    raw_top_margin::type     _top_margin;
    raw_left_margin::type    _left_margin;
    raw_output_width::type   _output_width;
    raw_output_height::type  _output_height;
    raw_pixel_aspect::type   _pixel_aspect;
    raw_flip::type           _flip;

    raw_iso_speed::type         _iso_speed;
    raw_shutter::type           _shutter;
    raw_aperture::type          _aperture;
    raw_focal_length::type      _focal_length;
    raw_timestamp::type         _timestamp;
    raw_shot_order::type        _shot_order;
    raw_image_description::type _image_description;
    raw_artist::type            _artist;

    raw_libraw_version::type       _libraw_version;
    raw_unpack_function_name::type _unpack_function_name;

    /// Used internaly to identify if the header has been read.
    bool _valid;
};

/// Read settings for raw images.
///
/// The structure can be used for all read_xxx functions, except read_image_info.
template<>
struct image_read_settings< raw_tag > : public image_read_settings_base
{
    /// Default constructor
    image_read_settings()
    : image_read_settings_base()
    {}

    /// Constructor
    /// \param top_left Top left coordinate for reading partial image.
    /// \param dim      Dimensions for reading partial image.
    image_read_settings( const point_t& top_left
                       , const point_t& dim
                       )
    : image_read_settings_base( top_left
                              , dim
                              )
    {}
};

/// Write information for raw images.
///
/// The structure can be used for write_view() function.
template<>
struct image_write_info< raw_tag >
{
};

}} // namespace boost::gil

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

/* tags.hpp
4hxgVaFig3KR17bDhN+e4m+10xmM3GaskWji4r14miZya1EsQmRbehD7anNbsBCF/dBXzMyhWy2GRJ1T72BMpiVSKNR+vntXjEInNbcFKMjTzyfvBKBCjaPtrYnyHVCeSJ6fDYNGt4e9KY44uC2WjoMAemyCEgdgPr2CrLLSjuigY7OmgNEPoGmL7fzDU+QeSeKh5p0EHh5AxLXk4MBnwsCzK7y8ve07hj33HRr2j3HYOGb//zpoc/qgD+w8Y9DntQAEtRvTBt3ZkRj0BbHEoKfcCIO+62T6oNVDQN0CD5UGrUrQGbQrtYEMPDUDE34CTD5Xmzox0WR9hz7MyK14Uqb0IMZeLYG/VgAd7D4d9JtAyzJpQUui2vc70iDPPRPymreg0cvvS4P87CTkd5wkCR9wNF2NkO8YyNT9REUx1x5gY6YSw4bInYESrRAAGAc1MGzg+AMUVNaPwGDMAahgBUS5eJIcrXTXPfF7ZuIXVfbc0ZJvWhhtLHMouV6MQ+WzW2MUkAomzvXAsUoj70F/obZinAitGAbBuwYImej9+1MzwGnaNDrxsZ2aZ5Fpt2X1A79uKy1sgp+kXtFWOotcD/Ko249wNNtPZCbOKGANckB9eCLb/rpyfLKd//hfgwkNjuLxrgU0uVZZVHPoZguqo1m6kQmPedAvLwG4UjsSj6WFAE59IMWE+vp/GxOpL0tPA17YuKBYndy4YJ46ji2YjRIg0wg8PzK2qCUyKvTD2YYmTBJ7lK8vyECRAGLpplkjxFIPP7ngTLHUw6+/5rvFUg+//5o0sZT+Bo9Qe9OuP3OgxTy/EN12IHMDRq1qtlZVrFXNE+/f1tiydnRoyTxjaElxRmQ8EC5lWSArA7KMIve5VozLx8teaFdPnsK35A4KZ9VsW+OfcErmz4am38DoOpGbvwff8xy6sdzWuIWYX80ovOERj6gEKB5QvI8+c8zHDUNvIktZwNy98zMy8Ja8+Zn4s3S+MYM+OIg3lSmLwBjPCgX5FOVKPFJVmp86T0Xhn1rpbAlvgXvYldnzyWT76mw94DRUNxtYcSXu5MqbMUpnj7iXp9xHCxpUpjh/bj+dgmOlPeElPaArQR6L8j1v0zlLUg91+pt7TKc//uenkQe0Zb00CwnXUQM/Wl0+iBetbpZWVxgw4TmFutlaXbFWN4/f/yV+raUXT73NZfPX7cKIpJqtUOeNp4/n4FZrTTvqj+sgp+LZbjzn9f6zOJq2TKyDwwmY+I4vKTL8/mPpVHsDwJGg2ts2p+2839jUiBB/Ec3EwFWm2jXP02HPNn4ZmenoNImqprC6DVDo6lLGVoTr8v3yMHRkhuZ+UXO/FHa/6JVn24T6ErwW6ovwAH/9+qelD/BLVTr2MErHeeQsf+JmDGXcMzgOrxdyduNNGlfxup/E8FCm8AOfVvMSge/b+Obf0Ccb90R1LvF0TfHmXDt/e35c1HTBE9vP4nwHpEK3Pgf67nOo0mKzT6OZoj4X2fHtizVwblEh8SXCvzBBR3QT968lBvaty9aSNyrgPRjAC8+GdQb1rNgMBnY8ix9bk3vd+rWATzVnpj7khz03xsh1eFHoKvvdg2K1JflZmn+B4vpihvJJze2bR9sDt3jpnZ2uXGptmnlxToIrXtV1WoRuWwXq8/UXp394DF6d34UfG7NopauSLyspFg8Tfdd1nfmJsZ4eyFm8qhoqJCIy6Ktdd36ZaQgo/JT27U92YSgpz/8qM/2TXdg6/+L9VFjf19q375sGvX8dHiKYyuwCzMl2sXoVmFH09TuYMrwUXixdjtF8jgSu0r7rRV/xkp82qzVX6982e8Z712T6Wjab8xh+0yMulCv8b2U4jIYyxVqm5vkramZdkmOPZMNDDjyIw9o5WCWQKXJrgS1QfdwtOlgdKKmoEIfBpuCXZ+F5gCZcHbd9kWkoijnn3HwrfmsQWVtoPlY5LfkYMHwhL7SKZZb0wkJUzw+NpYfXHfAXJecVhkFRcwmeWd23K5MUjxVvzIR3FbCWdk+wO+dMhQQg9W9NMbzndcGW0XZ+cREZpc/iK9ee1Xk4rInoFM2d3YoRhJZnEYZIlkaVoaUSaCkyMfGCPjsh3/EgDACl499NAMFj/QnutMkwKHS34RKlLUsB1PAD5mFcZtd9kZzYhKWBF6npn+KcTOoo2w924F0fkWMiU78LlW7XhJ4+Q7xd0p+Uw9i2fiqITxg/KKBDcuvHM5PH80rPGxT8vX7qV94C6L05GROAJltrk/eShGBEIv9Vmih+8L4zCA1EGxna7AP+yKJBPNoPms1p3Vm/GDcKfT4vquAbvPAPTARfTc+lOXaMNXQVUUjlaNdpxcTWOLR7bkx8VENykHkjvx1s9bMPAtYV4eC+E8/jIaJ+dWEoGBXKfGcwqhSH3bvB4ImGr1P4kGlY0Jk5mbwUhq7B+3b9vRZs50bEvrtdc0eZCW+koHt3ay7HfbatFJmbuIfF+1f9/BwyGzxyR9/tlmG3CUjp2t6RL9O+64zGmsWngQwrM5eLQg0mgZgZHeO7zq/fk0cfRAPO6OcDNrorw8zaIrMwsMCXOMMMqzbu45vscfn1tLHAc63EyFibksH2pH2zmlw8gVnVfuCxfEYzqpxWoHDtKvTKFAmYmFoHnXlQJ/ll91qppa0UvWoGrc4aGR26zQwPwNasI65xzZffqA5kr8D95YCBnQgHu088j7cqUKxdjd2sx+Sx63JwxNflwXCZp6d+pwGd6O7u0KlRa8aAPMcTJjgq2w73sG2HJ76zxz5mJ31yvRvarclOtEM6Ahjx5sIEQY64foQ+1Q7C1E9n8q1e/FoxEOIgfvw5BqvH7oMGA6AP/Wx7psHLWfAkGtRYCjqh2b7HoeGdClEpP+Sc39SUmf4p2Nln3Lind3eKeuPsW32ZqK9psi8eRrWlxAraPIwVfqLpvSe+Api4xeTjHf9Tz8QgZK+5uC8lGyoyywOJiYawnV/vkFSbogZkI6egAR//EI+0ghpYWlgzB6qCcp/2McK0yT6jc3KEBO0Sxcf4w9BKwO7Xh2x/DYc8a106emefARcN0LgjM/3yrbQ+kp8/Bx64Ovn5QDAbJrwCjO+IMojfxBvn5xMimYYV83Gbe00vGm/ufXjAh5u/SSLEKTv+9rw2bJed1+Cpiqaxy4BzVn5OliSrMmuezZraUD+ESrKSXz+ExzCUqfVDpA3n1A+ROmytH8ItclvjBDzJSRp9wEgau22TQO06Q08cx4RZT3wKCd4EdpkAqaoFN0QmDpYsR3ahTiSVXt5nMGcURUT2utyblRwMIqmHPqYvLgndsEj0qXRydDOrnsdvs+FxtU2AkguAh35zPir6m5Rc/cr05Ifzio5o1fMaj6g312CsLv9NPXn2MbYB3iQ/beM9Jb8Di6IBHWmbEl8nxsjFZFt9sQxDGge8JzGpagP0gR/CbMEbff72OuCyNEdrXEUH9/K0RgUjKXZbw5TjZe7NNFxc91hpK1bahJVgYEYst2zrUvEaVmpzb51FQQJYUXgVtmxzuMw4+MGUjvPfkYPQPJucixepK5w3lKg3Dl6zHAlCmRumgze6NmnbQSVtO8KYSRwGyWNC+hD6UJsHCW5ryMZ90Qo+YUiIviGDnkkbJ+6HUeqoW8PBlhPPXwBNXf0W9sbe0dy7G9cuV7JC7Q54xDMIRTFfgq3I9gfdGHRdAkvHs5kXzyH1vMQHhtdIRLo3N9YuV3KwCXg3Pv1dzUTUcPEfZW3D43zBDYB6APZWdAosLkNXgpIbKp51t93rk/wg1fImbXEJkyhbvMi5pkydFCjkD66PiUChz6stLuNZwO1Cu+1sfZkc5onnQ8FXYewZiJngNiB2uipMfZVHt8HS68PojW/TQt9PcNLdm9/CXBiMdMCJuZEcpOfpkDOC2MvochP1E3hpa8TPJcLCg/7uttQPoUm6ekw4hNuuobhpTWby9vfNgwtontUAVL25fohM0+X1Qyb89dYPkY1aVj+Uhb8l9UPZ+FsMLeJvYf0Qxi8qM+uHME5RcdQP4cUUSl790Av4a68fwnviFIDgdwa8vs7Lx8djgjd/kmlIWf8Y2MjfHMLPFCfVlEVnyCPktZr7TZC59HUIkEe34+ewPW82bwIpFg5Gn3++JhOGcdvz/Mo9J0WNwYII9WruXv7z7SirezFELlqeSS9Ge/lf/ozcdf9q5K4OohFDTfHIWe5NFKbrhC6N4JSC7F6JGiN/7I94HPHNgOAXvYUhbSAieO3L/5YRk+kw6i10csEYa+epN+PVL1XLlZ85V5Wo2QEjj8eAJQtlAR0Fd+Fa3odr+c3XkAE4UNNwd9LH11MCao2jzb1vFp1xpAOQ+vJ4b3rV8shkEN2NdctVG7+5OSbaSornPT7aPqpuOQmNFmDdJSt5+7Y0iUZfIOMLhCDHTNMq0MJbiw75gFCKYtrLdL3Hg3SjyIN0D0k93SjyIH0P+kG6M6Se7gx5kO4MqccdxOSWWfG3lAsr+yD0Bq5igx+vlVbbbY0HMJBfftS9KFYaCk41aK/Q2cZRzCS8qwDpoI9hTBleRql2AZue14axJj8D1Y0+h9KNN7DGNPc+J9WzNeC9LXjgiU8wfC2cc+7EL7jmOefUglEBgtt90NSCH4Nwd+Jvp/MVHNz/R9v3BzZVXY8nTVoDDSRAkTLrrFonM2xfteDo4g8QX61ANKW0BTGADlhXcUPMQxRSwLTI8xFEBT/oQFDBsYlSXamdVpbQ2h/QQcF+ZkKTrtNuuzWdVoU2SOV9zzn3vTQF2efzz2eT9N3f95577rnn3HvuOWVrZLHJ5+nhvcgR09yjZaFFdsQMfluTzdEGQmTUIqPl/xafMc8gtErC6f7pWTqdAU0I/nETIT/b9OuYkrN8mTiyVK+a2x+7nHzFtzrJh7kspOHRjrez3+sfhoNhXughtPdHZJPdqwf7IItp2Yq93z0KlUPVNgELYlErdes071ar5OgZ7MUHai9SsBerLupFfwf244o+us3w/tPgbUAmKAijpy6I6WKePD3r91TZlXxI4tgcMcN9E8SN1Yk3sLceiSmlSdHL2B780MtWEn99Is5dAU5N017ledRGiTMJC99GRMtUn9013nFeyW7Oz/Y7fWS1mW0vJe48k5vVrGh2X17EJv4T41aZeRzs5MlnlUTn5LieOj46rxTzpw+b3wFpcKlJ532DHCnNm8et7UplyxL9H+vR0IFpxhgrWwD55/UH513h7w8u5JoVQ65jvGSDUyeiqcXXdNxmKZq4+gf16nP1DWKZleuyy/eY+qZl6d36qTAk0pgY/da3OKQA735BsbzKJOvlhZnFypYuMk0izgBmI9d7DlZ8AXv3TIxb0HBmQcqNXIMYvSQWsJ+N+E6hB59UEXvoin68hC8ZpVcfKy4iqWnh1Pn0ghCE15nIgj0a0cTk7T9HYDem7AcyCXIDt5MtbSZn5qtqSXcG7f6wqvfPkHaNVa+q21zfdg4F27P4GLeBxaDCumx/ndaANRKXjrFmXk6TkdOwKFWLOvil1Wc0KTl7MqzYtyJcnqczmqZwsq4E1ajY7FUXH9OgPjfzRBIPA1cnyM3zVl3oUz0fiEsIFxI5cYJVY8puzj4pmSTgt44jRk6fWJyz/LT4k0NP3InWapa9TwcAI4ucvpkT2W7/Ga7e+s3vgLhPn0j2p77G6hD27mtkL1nuJWqzWOPnEpqI/po9V5pIjuSYSnZGqGQnuTRpftSQ3T4dScvVeGmx3IjyKPvNubOKrLMcqPOZV+H5kElaboxeRUlzMGmqUUuzymQQzirlGVWfwADLZ3BO1rRrk/76lEtPuvf9wUn/c80Fk37zSZx00vbTIR8k4OE7zyzRK3e2/yNSsmDtdDGuPWXwFQ0+ZdifBtkq/pD4lAG2v8HHDNkKGmeYE1WUnNtKyON81jCdjjv6tlSkD0N9bBc6hZR2PhBF69iWcsMwzWxyTo0xFabicv42yK+P2+Ld2GLGN/TkTWG8ulhmHe9Tfo9vb2AZN0+TA9FkmCr/NMlbM1KrDx/NSx8uws7wmlMkH4Zk0mPyHlMk3+IoqqrNxa40WsrJ/ko89DCG5pr6pmfp5SZ5mOTDBHdazodYyFLxCWrLHbeUt6O+0aqHx1nloxIlMf9+Ylstsg/HCGzn0hEDqNVYkGn/BORgHst+BZFSRQl8R2fnUC/dRvlYdAQaSkmWZ06JGuSZk5THjICrzvzi2T5fBtqUWCegnibV4EQ7LKkj8EFIBlnDwLrwTO/3N51Xcj7EkGXTTaSYit+8FBsfbxbHOBqBPHVizqrT7rSSHatxEExP3VetDFHOnFWZlvJTCPVrakgRaBnWtKAa1TGp6umZTs2yTsUsTOut7qP6t5JQglG8kJOlf3gGDTOXFQNu8nqqi+kABCz7083vMqCvFXlRJV7/Fy7gqOomOuWjhLOWOlQcxgzaG4d/v3NGgWqgy4/xKn4MNTixBoha9ACe1h8lPcK2w1jUyYuy6ncwtIyHEF57MYIG2jjVRHrbH86lKUZjHnIFYXMNLhDL5p+kIJrSTm7WJnJ36oCaS17H0XhOKrIoICboSuqtALWCxzj5oy6oWsX24+7R7IrCOA6ksvtf71MkmjZ5J9XGKdI6MvsmDiA4u2m6JkgVi9T5m4Firhpyf4hv7QBTadfkqM5m/wF14AZR/EVSCcTncKv03KIgvvTkSJ9Ts9uMHV+BJHtK9eBMu6sQYpjFV0GzqL5Ro1szNU8Oi38enA8UljICXok3l7DbIWtHFWIEHXOOohit8ss+QL011MwL4HI6g6rDHxykxmk19f9Ra5zeuo1owaQKTCrp+js53gmcIaHZtxyzNxUMKMXKwcVRTZ2sqLhUT6rwwp3nYdHwbKSYfnzYwKDK2WVsxU9haVXU9ihYfhmVx0CRsgVlB+DufEbs2/lpuAJxmop8FUZV+34Ye4oqM55XK7sOKos3lcL2zBlAHXgVAycduAADr4UITgMsFT/BVwE0BQerBqfgq3ehiIwIMTgFeLvMloyJw736n/HPm+//nimY/8dLTEH5n4ZMwQokNFOqBqfAHW8cFTnZM0cunIJr/YlTIMz+/ikws8NTh0zBCDbLlDAFZvblxP/VFKye+j1TMJIplyVMgZm9NjFhClLZ1QWJU/DOWxdMwW6M8JLxbydIpCQxqDTXnNgcxiDwyVWxD1pkI/84CKkZQEpKnryTAGVln7+TAHCM1bKNqRkCcD1qSlEDuDBp47OqAJSbipTntcFPgnys7A6tNyC+SRUMy45CAIzC5540S1gn+rbO+dNcokRoCIaZviBXz+X41Ird/y71mUjEi5UJszuaTerh+SJ4o1t+J75pTxxGOR8GlZz13pBhoKoodHsRzVsPKfeX9rA20aBTSRkRzNfdX6Ib4Yoedd7GqObC2dSUAbUc9eM5LEftcHo/in33Jm44D/B5QFggnR8OpeDPSEIkjGz01li5fWSagx03nE+Y9vehCj6rUVeJFweXW8l3qqsABymm+4eKRvXljYQP+YAPlRwfSHN14Lb4HuyrwBjEhzQcgidZQ2dEqauxabUiPi3uUcyDln+osLQ+i0gvfvPzmvhLzoXouwjfcia9mpzgdo5LRnfZoNqnWZxt8z2NvdTYPgbkVH6axPgN+Cs/TaI76aTLTyMLtZCrjA+1Yzb3pn5+L5sGHHpuupSbwfVYGlPabkINgQl6rsqi3sF+CDwhY60aT/qDm8jXML37dJh5mYqT4jC0dMCe2oG6QFbv0nQdVI/CcX/rtQHv0gk6bOLeDKkoC5jOx07w6/NpWcBw52dJ+ZlSfoaUnx53Lc1G7kzWzUtQLCHzMnO+hMh5XFclPftkXJYolssycjymlTfLuWloEZfV/7ZPMcTsHtOKs3JuVjFZyU1RnHOjKWitb/YDwLC1o95OWYbqJWxaplYdKlDiGc/jJjSvpCgrk9lKqE3OzchuznGYV4x83GiPrTSpTwlL5Nx0in982AqIf8wglaVLZZkLB90S4UyayQY8Lqmfk1pOMpuPVd6bLudm2pse/5cvLcfeCvWeeMxoC8gxGWCUUmw4MZubL3Yu0pelDxqGTqzTPUutL5W6mO4zT7E3rfjKfm8G9jBf6yFG35vxeEi+N0u+HI0iG5owbTZVnJtuz81caYDpGdrCWfnxdOSycxxW6IaIPuWjP/F6rHr31fCbJNph1GtGrU3OcZhWDs8vVUqHsV0H0ZJcZrbfIJrGCGZ7YG3Kmn/Yv1rxd/vjmdAhcvLpLJEeT18oN2SfVK9TSGUyqzhbkcrSCHoZAEB0/JBTNsHN52uxVJaFett6ZZFTU24yQDlxZLbfnpuGon93Jb8CTxLToaP63MRxgeT/PMruqrKfF5G7MK3ipHsNettEWKJ+rwq8HPvxFZMRgKlxABamQaohNwtzSwaQ4KH2ezMMjfamx5LkAADV0CQNj05gG14CHlZRxBRARxtBVr43U8sG5aUkmwF7Bn8WIg2YT2oDNVU3oZUgdZmt/0tcHMd1xTX3yrJgZZ08x5ileAeAAIBDSwEAgP9/rymEJQKK1f60X2HXHkuOu2W30mJB642s+yF8RmPy1luH+OzekiB5/63kQotHhSZZv/7wrcBrzsaatqBIOeh9naciLRuaCv3/CvsfaEElBei/LOFrWlhDRfnFSB9fBckPzz7FgUahl/hu0ey+FupgC4CykDNketbKjH+GXTX2GansxA6RIcO7/sKVt+/Kjmuk6V3KokkleDZVc1UxiswtCLfs9pwFaeRVA61C8ueejipyoDPAvgM5uIBu4wt8QhWyQ4r61q3ud2gtxyzrfdswbjaKIIrTxHOwx14jTkvLPAcyQ6WsCR+qQeVCl1TI2E14uhKznxOtEIcvom3I2aGZMEXsilsid04oloQe9tF2GLGaz0DvYXvYohYuhzs62S0v9ik1qyuHJ441a/DTyYftxGFXHIVh632FptnotREawesrBgNWnHeReQ1XD6DOv19ExcXoaljMrh7LNr+9zh0tIPOeVYpIsLk8DhvUhL4APHve+A/gkURGmW57g8CCQ7rxO46pqA66dinuB2weW3dUHV8XK9rWR+k1q96BMUaDOOY7tbjZ72jjzkfjAXhqIZidpESgClPKTcrYDD/df47Aq3tm5GewI+In4HTzieuAlxtawOplBrUArgpvwNi9frFqXdH7RJo=
*/