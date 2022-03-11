//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_IMAGE_TYPES_INDEXED_IMAGE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_IMAGE_TYPES_INDEXED_IMAGE_HPP

#include <boost/gil/extension/toolbox/metafunctions/is_bit_aligned.hpp>

#include <boost/gil/image.hpp>
#include <boost/gil/point.hpp>
#include <boost/gil/virtual_locator.hpp>
#include <boost/gil/detail/is_channel_integral.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>
#include <memory>

namespace boost { namespace gil {

template< typename Locator >
struct get_pixel_type_locator
{
    using type = mp11::mp_if
        <
            typename is_bit_aligned<typename Locator::value_type>::type,
            typename Locator::reference,
            typename Locator::value_type
        >;
};

// used for virtual locator
template< typename IndicesLoc
        , typename PaletteLoc
        >
struct indexed_image_deref_fn_base
{
    using indices_locator_t = IndicesLoc;
    using palette_locator_t = PaletteLoc;
    //using index_t = typename get_pixel_type_locator<indices_locator_t>::type;

    using const_t = indexed_image_deref_fn_base<IndicesLoc, PaletteLoc>;
    using value_type = typename PaletteLoc::value_type;
    using reference = value_type;
    using const_reference = value_type;
    using argument_type = point_t;
    using result_type = reference;

    static const bool is_mutable = false;

    indexed_image_deref_fn_base() {}

    indexed_image_deref_fn_base( const indices_locator_t& indices_loc
                               , const palette_locator_t& palette_loc
                               )
    : _indices_loc( indices_loc )
    , _palette_loc( palette_loc )
    {}

    void set_indices( const indices_locator_t& indices_loc ) { _indices_loc = indices_loc; }
    void set_palette( const palette_locator_t& palette_loc ) { _palette_loc = palette_loc; }

    const indices_locator_t& indices() const { return _indices_loc; }
    const palette_locator_t& palette() const { return _palette_loc; }

protected:

    indices_locator_t _indices_loc;
    palette_locator_t _palette_loc;
};


// used for virtual locator
template< typename IndicesLoc
        , typename PaletteLoc
        , typename Enable = void // there is specialization for integral indices
        >
struct indexed_image_deref_fn : indexed_image_deref_fn_base< IndicesLoc
                                                           , PaletteLoc
                                                           >
{
    using base_t = indexed_image_deref_fn_base
        <
            IndicesLoc,
            PaletteLoc
        >;

    indexed_image_deref_fn()
    : base_t()
    {}

    indexed_image_deref_fn( const typename base_t::indices_locator_t& indices_loc
                          , const typename base_t::palette_locator_t& palette_loc
                          )
    : base_t( indices_loc
            , palette_loc
            )
    {}

    typename base_t::result_type operator()( const point_t& p ) const
    {
        return * this->_palette_loc.xy_at( at_c<0>( *this->_indices_loc.xy_at( p )), 0 );
    }
};


template <typename IndicesLoc, typename PaletteLoc>
struct indexed_image_deref_fn
<
    IndicesLoc,
    PaletteLoc,
    typename std::enable_if
    <
        detail::is_channel_integral<typename IndicesLoc::value_type>::value
    >::type
> : indexed_image_deref_fn_base<IndicesLoc, PaletteLoc>
{
    using base_t = indexed_image_deref_fn_base<IndicesLoc, PaletteLoc>;

    indexed_image_deref_fn() : base_t() {}

    indexed_image_deref_fn(
        typename base_t::indices_locator_t const& indices_loc,
        typename base_t::palette_locator_t const& palette_loc)
        : base_t(indices_loc, palette_loc)
    {
    }

    typename base_t::result_type operator()(point_t const& p) const
    {
        return *this->_palette_loc.xy_at(*this->_indices_loc.xy_at(p), 0);
    }
};

template< typename IndicesLoc
        , typename PaletteLoc
        >
struct indexed_image_locator_type
{
    using type = virtual_2d_locator
        <
            indexed_image_deref_fn<IndicesLoc, PaletteLoc>,
            false
        >;
};

template< typename Locator > // indexed_image_locator_type< ... >::type
class indexed_image_view : public image_view< Locator >
{
public:

    using deref_fn_t = typename Locator::deref_fn_t;
    using indices_locator_t = typename deref_fn_t::indices_locator_t;
    using palette_locator_t = typename deref_fn_t::palette_locator_t;

    using const_t = indexed_image_view<Locator>;

    using indices_view_t = image_view<indices_locator_t>;
    using palette_view_t = image_view<palette_locator_t>;

    indexed_image_view()
    : image_view< Locator >()
    , _num_colors( 0 )
    {}

    indexed_image_view( const point_t& dimensions
                      , std::size_t    num_colors
                      , const Locator& locator
                      )
    : image_view< Locator >( dimensions, locator )
    , _num_colors( num_colors )
    {}

    template< typename IndexedView >
    indexed_image_view( const IndexedView& iv )
    : image_view< Locator >( iv )
    , _num_colors( iv._num_colors )
    {}

    std::size_t num_colors() const { return _num_colors; }


    const indices_locator_t& indices() const { return get_deref_fn().indices(); }
    const palette_locator_t& palette() const { return get_deref_fn().palette(); }

    indices_view_t get_indices_view() const { return indices_view_t(this->dimensions(), indices() );}
    palette_view_t get_palette_view() const { return palette_view_t(point_t(num_colors(), 1), palette());}

private:

    const deref_fn_t& get_deref_fn() const { return this->pixels().deref_fn(); }

private:

    template< typename Locator2 > friend class indexed_image_view;

    std::size_t _num_colors;
};

// build an indexed_image_view from two views
template<typename Index_View, typename Palette_View>
indexed_image_view
<
    typename indexed_image_locator_type
    <
        typename Index_View::locator
        , typename Palette_View::locator
    >::type
>
    view(Index_View iv, Palette_View pv)
{
    using view_t = indexed_image_view
        <
            typename indexed_image_locator_type
                <
                    typename Index_View::locator,
                    typename Palette_View::locator
                >::type
        >;

    using defer_fn_t = indexed_image_deref_fn
        <
            typename Index_View::locator,
            typename Palette_View::locator
        >;

    return view_t(
        iv.dimensions()
        , pv.dimensions().x
        , typename view_t::locator(point_t(0, 0), point_t(1, 1), defer_fn_t(iv.xy_at(0, 0), pv.xy_at(0, 0)))
    );
}

template< typename Index
        , typename Pixel
        , typename IndicesAllocator = std::allocator< unsigned char >
        , typename PalleteAllocator = std::allocator< unsigned char >
        >
class indexed_image
{
public:

    using indices_t = image<Index, false, IndicesAllocator>;
    using palette_t = image<Pixel, false, PalleteAllocator>;

    using indices_view_t = typename indices_t::view_t;
    using palette_view_t = typename palette_t::view_t;

    using indices_const_view_t = typename indices_t::const_view_t;
    using palette_const_view_t = typename palette_t::const_view_t;

    using indices_locator_t = typename indices_view_t::locator;
    using palette_locator_t = typename palette_view_t::locator;

    using locator_t = typename indexed_image_locator_type
        <
            indices_locator_t,
            palette_locator_t
        >::type;

    using x_coord_t = typename indices_t::coord_t;
    using y_coord_t = typename indices_t::coord_t;


    using view_t = indexed_image_view<locator_t>;
    using const_view_t = typename view_t::const_t;

    indexed_image( const x_coord_t   width = 0
                 , const y_coord_t   height = 0
                 , const std::size_t num_colors = 1
                 , const std::size_t indices_alignment = 0
                 , const std::size_t palette_alignment = 0
                 )
    : _indices( width     , height, indices_alignment, IndicesAllocator() )
    , _palette( num_colors,      1, palette_alignment, PalleteAllocator() )
    {
        init( point_t( width, height ), num_colors );
    }

    indexed_image( const point_t&    dimensions
                 , const std::size_t num_colors = 1
                 , const std::size_t indices_alignment = 0
                 , const std::size_t palette_alignment = 0
                 )
    : _indices( dimensions,    indices_alignment, IndicesAllocator() )
    , _palette( num_colors, 1, palette_alignment, PalleteAllocator() )
    {
        init( dimensions, num_colors );
    }

    indexed_image( const indexed_image& img )
    : _indices( img._indices )
    , _palette( img._palette )
    {}

    template <typename Pixel2, typename Index2>
    indexed_image( const indexed_image< Pixel2, Index2 >& img )
    {
        _indices = img._indices;
        _palette = img._palette;
    }

    indexed_image& operator= ( const indexed_image& img )
    {
        _indices = img._indices;
        _palette = img._palette;

        return *this;
    }

    indices_const_view_t get_indices_const_view() const { return static_cast< indices_const_view_t >( _view.get_indices_view()); }
    palette_const_view_t get_palette_const_view() const { return static_cast< palette_const_view_t >( _view.get_palette_view()); }

    indices_view_t get_indices_view() { return _view.get_indices_view(); }
    palette_view_t get_palette_view() { return _view.get_palette_view(); }

public:

    view_t _view;

private:

    void init( const point_t&    dimensions
             , const std::size_t num_colors
             )
    {
        using defer_fn_t = indexed_image_deref_fn
            <
                indices_locator_t,
                palette_locator_t
            >;

        defer_fn_t deref_fn( view( _indices ).xy_at( 0, 0 )
                           , view( _palette ).xy_at( 0, 0 )
                           );

        locator_t locator( point_t( 0, 0 ) // p
                         , point_t( 1, 1 ) // step
                         , deref_fn
                         );

        _view = view_t( dimensions
                      , num_colors
                      , locator
                      );
    }

private:

    indices_t _indices;
    palette_t _palette;
};

template< typename Index
        , typename Pixel
        >
inline
const typename indexed_image< Index, Pixel >::view_t& view( indexed_image< Index, Pixel >& img )
{
    return img._view;
}

template< typename Index
        , typename Pixel
        >
inline
const typename indexed_image< Index, Pixel >::const_view_t const_view( indexed_image< Index, Pixel >& img )
{
    return static_cast< const typename indexed_image< Index, Pixel >::const_view_t>( img._view );
}

// Whole image has one color and all indices are set to 0.
template< typename Locator
        , typename Value
        >
void fill_pixels( const indexed_image_view< Locator >& view
                , const Value&                         value
                )
{
    using view_t = indexed_image_view<Locator>;

    fill_pixels( view.get_indices_view(), typename view_t::indices_view_t::value_type( 0 ));
    *view.get_palette_view().begin() = value;
}

} // namespace gil
} // namespace boost

#endif

/* indexed_image.hpp
LE4X090JYp8J8A5jZjtsBkdiCKpC+wR6Rumx6cJLrpemrmZN+fNx9IkmWXSPMUL+wBHlI7EtTrSfg0k3lH4riSFRBzuOtatdGMTsmhggPBTS1aelfxpprXdXL+5674u0mtJqjT6ohZ/rrrslkIQgmg1c15GeiEL3OcsxGmVa2gp1KFVRnmw4a9yV+ABJ5txkrkjPikgKB8psY4sfqUXr0vOfZ9Y9XxVUILFgRWldT/QeBOgtUiuwz/6Q0WPUmYJKkvaNQlys3LGYLvCzrNkrjET4BlbgzvE6U78bJATtTEz/IYReDOE/hAsYaRD2QPA0+m73RFuLSEqUlJlRYcQZBG+wl7h5TN5zstMHV4ZBcmDB5nijCUQqT5f62yVtNtVosOhQx40V+HOxYvcmf8rtON8IHw+VUfm6hg5DNJlqPGayC8+udhmH1MYVhhqxSXJ2Erpp7xhZZET/EpnvvHhguaZ8BP5bbzqWJM9xvd1r5LP2okqOVNGOdfMGLjiijVX7LFwAs1bXNikKmV2aCk+hZMVDvOmez4Dv8LmElXh/kCj4Ca1bZ+IxIH/Y2OHpFyWzBJKa/2Wkun0c4N+yEt2G8OYgBvFV4tSIvIGBOjuAy76LqICdTdhV4PUn8Kj9PTgn1YYF5YNscA74lh2b9CWgveRm36K34F/ocOYmOghQmGiz+w8RZF1g9ipyKSCc2xpwofQSqlU9c808T7d/S5OYtm0OCMJuIhVhdCTQONQurrMy5K5K/b+B+X/gfA0Rjgaf8vqJyOgTzsTjafAAH7uhlgxDouPT3M782iHJ6g9v8ESBJinos83hr+eBhgSKLBD6PNlq9bE5Pf7DxfIaqoaQmL7gZ/yKI0vku5zeWddOL6M7yaOTrZcnSdb0JpqLXk2YyCKr97RORgHHK1+fspw+hzdhp9f6XBIeRT0VEYsaQ+X9jQmG56pEGyUB2zMZtvnXYvxrEU/CulUvx4sn41K/Ad/S82AzDW2Mr/JSqoTaxHNrI2JRqde5iuZ5w5LAgTQphKXiMblzbHkN41AfQtfblJIk786Ie/eYP9VYAEWYBV3OzgQZ8B9p3no95JkUH/Xtl/8a8GczFUPHLuVilfhVSNxFnTAvZObdddadt8gjWyJHzYKm7+4c9wbwBBJz2oqfDpMxwTmeu0gfNICl9SW+LjJOzEmQlpqRhzo+anMTTvjC2sgU4M4wQCIDMxmxG7j40ETwHg/MB6vwSZn9OWmTQcCqDQHwwVvzzrRnYl5I9ql43ccC//UEee/OBzs8pAbnvGCE9R5+O2wv8lzFDge2YmToiPcvgZ0FHki++SrvlXTKuzt/H7UvXAebEagdO8RueBVuFx2h+YCGoz28K87yGV6CIRggjU2Xmvq3T/L4CL/rHxM7Zhwx4yzSmPspgLg2oXFFIUommn67lHJu3QaL2HMqPO9HqDq19PzHqFH2GwCBMDidfDZTG6eOFdHPmP+0YfwUpB7CIoIpHZQh0OrwfJrZay5Y750f0jp83wSBsO76brFqimlBrvpsvcDnMbMUvxcaFr+aliKuiErzHbFM5UtCK/6GAjQAK/yaUyxep+HZvCv7Coxq1G6b4+nYnVPNJ80a9YmAKVOi0jieFQhytdUQpjLYS/zcUSuf+uj5Gc5eY5AA/Zw+qWCr/F3QyFTFIzxP221eQab1ppxs0DzBUIyRi+tIX3OuHGnThJ8tKhMBMZ5DyEwmNgaHTZaYn0X8ht6bfqUQDnPUNJFzl0I0WOLtguXw4UjZxoqEBgiKI9eVAXTAypuAAr5b0XMTen2FkYPz3MzbEaqW0G5y7eHhr6M68oPw1LG4K4X83OFdhuzR5wPLC3Pg18+89uaCMZvzlo/zoGKVd9agerntyhTXOLK/grfQGDKwLfW+hy2A5wIHO0aGR2MljtRWIaAHTF83kva1vYlpv0C0kUrv47jblqfRx6YUPYdFcHVnOZ6AgM0bD5tXOWYGrVrwYkQRgVMXIK837wU0pjo5m6a5uz0KGgh3zG3kAc/7D10pYsBst/yGvxW0/lA/m8xTvIWYXWhfFYKmwLr0Cu/YoXhiHoybL/0j9zzfMynHrE7nmEHHk966Xtk0vKTXnJBc8Z1bP+f09yyXIIAj4nOIIRk0L5WtiZKMAETwDeh+wVoPmWwKrx8Utsx+K6eAtenIoJApmlNnzKBt9u4iGnKR4x9YzA6qYvW9TE/X6n9AN42PBGSYgdXQAAAs/9MjmSrf/VQ90guP28F0KUOHU2VZ7HHP2DDU1Z8Wz72iJwBlgMNZWdroqhSla21NsCumRJFYyyrdg948MQGmxQB7enyvxca4E8Ta20YgW8o/7gXta5dSbDAXvcJ0zYgmch/BiTr8lkq5n0Ym6lDnL9vniz+JhCVxC26CTUqe2tJd3OqAs5+ge93Z3uDzVT9rHx+WwUewa62NGPo35CIowhCmtKYLqwL/eS0eg6a9+ty0sVmWhcliJO4RHS8axuDS7wlNCODr+KRQ+FEGMQZ3qH0sAv96lxOurIwbQ/Dm+yp5uqufjS/S+UShzUlbTh8ed5Z0+Q00J7xYSIZCMp2hTi9fp2NHlHb+xjUiMuE6O8xEJ6TJdVEXqZmspvaO2ePLsYmnfhpd3Wt1o600XadMzlKybCMvsuHOtrmfMMysyMyk5GbwjORPHKC8On8Q8nxEUqsci26m+m0OX46brTN6mNyISuiPIuq3TqaMIUzWJXlgXI3Nhp7Pz598WPB8rkvL118bSYTdp97Sg3SRqOYPFKQOtQpctC4CRf1XZ2O7qXq03tvG1evXQrc7rDU2IFYlcR0dG9/CZqB1I1Wdbp1Qp9uuHi1/U2h6mGpNAqm+qw6jCjoMv7nfuzK/U/Aswfi3CmtqhkRDT0B0jpMNMXILvz2vI0VxVxiv1FxB5CmtWbxOiRA/AXzDlcTQr832ythktsdpN/DSR/HMct9+4Bh2uGD4mwkhqgKwCrXMJU2JPMjrjkmzKcRuZtkazmqTbarKaWQTtaJHaEWRT78i2RICGMjB9AEwqll7USvjc3HHYqnCKrH5SXobPsqGE0g2v4d/j6i11UeBhEowSZ3j4zdExWBvtxiCr3GMYZNZxOeROrOgdU/7LTbaT8zxk7myJEesdJsrtQyedNYJ3UyWCiYRHZGvvp//BDLPYjSzMPxz5rJOjWaPiEKp5QMCy0NFPgknPVCaVaPow4E5U4qqwXusGt70z9pdYFug7HCStnLe8qCnR/pzh7BG0RalXzg99qchRWKGGuBfGfr0Z8AjvoYVXMYDdctKhrGJnAszieP4+y7IAG5xddd6nMK7G29KIjHSjX0JjbvUQJD3ZHF4qSFgFRiwl9qSFR9+KA/FqULEAOeWDHr8Yl3LDXmI80FmdL1nkC1wXXRPB+ajcqJQopEAPxb3FUh0ip9Fo4Pp9T/oyS9JzglpDHINi1SKlMyBj41U+rHIHID3WaNSrEFotfLb2XYFDiy3zNUJLXafFtuyP+7FI+i7uAvTE9xwvzD4vqx/55lj3yml7zrM8oogAYyACCkuRevgDufEe449fpQv6f7pDazB0VXLGf+U0nn+oMLRKINn1NtWtkDUQPqnb/Y0Ux8CX+uPfw4QNdCshAXC6yyfxdnNt4daEqIxjOpFuEzo/QTcEvELFdM22e+fPi4hv6yLC7aTaOW9A+VXLeRxJzjiOYwZ+JgjXLb4lLlUuHeIr3YV/grt7otPbvjTwL8pU/t1JGso9wC+OBs2P4DyRrysZfTVk74+wLs8wo7D+tqfSb3/92p2n0KaaDJxevd8Ux2gfksTxCoscPOvG+eyPv65PFgsf4KrH0SOLzZZW6sbwM9LAcPq0j9sFpjdjFZSnH7c6x8EWw8tZU8LSZuVCSmvYwAfHsLOslupRe+c69EjXenDlaaZb2gE0s3uvjQvQymxT6AiIR4dvU56j0kKuZq6NxWQmj1ldkWssuQEvwcki7eolrwYrB69r/7X3TJSqem68PCHu+1DWcPnsDrwBuZNn0yab+zNeUuoS6t3FFRMxcEktsGCkzSE9nyLIva6k0YH+UPX7DpgPcMWhDaT9vGlkOBJcdtFcFyvjutkpNRLoYw6G3zjWWfu7Z4pSfbA5ZVu6/X6KzpYsR5QgX+tkO3wLudg2IRFwsJgS3migTD6uUKgIs3Tqe05weYsPICEmxFTbrV+x+q1A/8q/IXLEAH2pM4Fhxn8IP0LrdqSpH4uNITAgRBvS3lWh/ixus8pNw9scyytpfve5wFrzPfFf/Bt3qphJl6Mr519CAtG2Q4YzGugBVmGqByGaC8SzWRNG3S9SWWuYMThPzeSFUHNxfeI2QTv9lq5hK7g1UH6M5SIeQAX1S48e1OMdHdXr48oQiluvi2w+H6eaHrvOiCLJahA8QUgd1J6IM/+v7ypCZJ7rHzhIkD/rPy5zsr+hX416+HgfgbYLz0G2qvoF7R7jqUIunHNI6U1Kfpx4H08RD84VulU6n6VIbXkVqrkjsVTHm7EJCl7iItdrz8AgkBirXmi4NX5azjPyuUhjOcyMBdCRALDx9pspq7fC7jNdfshFOxYdF4iFJrcmpKOumJ1ZpE6v4yT9CZWmsfL3DBLpJLy4v4exTzCqqkXzToweuTGXS48lio+NiRKcfQDV1kds9YRFTxrhhYsd20vHxanU15wD8HX1nqjMGHVPdCU9Ogxxwd3s8yLl3Q7anC5xfIF8ME+vecJOmCHEN2wVnUz3vwXqb4wWbmBDTzjZmR/o9lorGCGWeKjI6MFPgEmnIcOYY6Q6KfSrerhywMyGcJi7xorftD5Nei2+JLpLh/mpJlSfPWd4NkdBfs4FiSSBSJ+ovs9Ax+ArSj/IaPDnv9N0CllAxFlskQ7HRQvsT6if8nt39/lTcI7bNlKwqNKwZpdnoFVQQllIU5fCo5JBRu1xMBd8mQpOuOWwCgF9z3hbptvBHouAho42dcoaCH5xX4/qWdYV/QBxsOY5k/6Ht0Z69cc6U1pRoiw23EXBkFcFSZFaVCqbDPSyB6/N224jROCkKgq6xrIV+h7xj9PWZ9hSdS/iWqkayYveJB3WG743ycsKsbZuxjG5ulhySeRmhtBXoHL8RZBFK3nuzoM7ZLjL+lDlN/A7hvJz+XNydUuAzqfGxNtoZgLo40XvaaYUZPdxFc7ZB7z6Ocy6Q+2Ler2r+JQxDH2idKp3PkWPky8vnzZZPrxqYAZpR5EAV4UQGNgVOvkHbAeJ5kb+uIx/G+H8NLrj0zWWdrRCV/z9BqzbmGazCDIsVDWf7btuBhRQqj6FfTvLQrcCqJO3Zj/uOF34tlrfIFAEGwa6/NNNpissJBgjVSInFdgKLfOqhXhi712UnuIaJ6cd3x0W27gu332w05D685erZEAabqM5gc7X8WzpooCDmuLAL4V8Y2u/ZCjrDWgqo2NPp9VFamwDwTqza75570MiyuWlWZctEaQNgoJ40Ddi/2TIKKrRaxsDlQQzwyJ20Hcm+lJCZMxnFWTxXSvsjrThFSnJxNEczKzZq9sJ8TDMedNsaUJ7Dpw3q+BHTnZMGokyNGYR3b/i8cWitGXDNhC0eWpP+7Kqym1uek2lMgT+o31XfBMMK7KmxFminJcMO2z/HJcjte/DCXh6kAxXl8jNPPPjyyIZ+gURAV+IfNf1qE1PRF3pP06p8sav8dbvE0nnX0RMB7DMgnbM8+nyn6CsDJcdllwoDdik2LcKNFHVJpyyWwtWPHhgURk8eqS6EdNx2R9/2Fn/TVlNfUiH7IHYv8Bm8ila9YQwh2wmsidSZA92E1HGPCS8khzRUWDmURbhsOIxPosHJhtaCL4/v39DXoAAAj+E/In9E/Yn/A/EX8i/0T9if7z70/Mn9g/cX/i/yT8SfyT9Cf5T8qf1D9pf9L/ZPzJ/JP1J/tPzp/cP3l/8v8U/Cn8U/Sn+E/Jn9I/ZX/K/1T8qfxT9af6T82f2j91f+r/NPxp/NP0p/lPy5/WP21/2v90/On80/Wn+0/Pn94/fX/6/wz8Gfwz9Oe/P8N/Rv6M/hn7M/5n4s/kn6k/039m/sz+mfsz/2fhz+KfpT/Lf1b+rP5Z+7P+Z+PP5p+tP9t/dv7s/tn7s//n4M/hn6M/x39O/pz+Oftz/ufiz+Wfqz/Xf27+3P65+3P/5+HP45+nP89/Xv68/nn78/7n48/nn68/339+/gA8/vV/u3e9QhhlITC5mrgB/vAnAwcgiqQn3fo4v+WOZAtMIpA5pNuWrawMm8UGhNaV4iy9OlfWSFhD91vJYgnzmQwkzYrtk8yJ8GqZ0y2ROwGN4egzhPYN6VsfLqhvgCvgJ5kY7L679FxUYRQLbLqlv8vL852p7jvoQkwtAv6aI3PeGIWbb1LQYK8xgnwC8oDq4hstjCkaRYBzouu9G3BB+TS91s86HPehLgz1u1l9b0wjmCYFeQscw6I+Np5v2jWpYjCwsKWdTCgPa7cTwaTw5bygkTexbU88y8xZsLa/g1HQKmmfQrcUZWgCXnT2iVjwnONgyNfdwzGP8i3sK38EBOBXL3HJRS8rx98kB/3Vdt8jfnAvdkNlhWXbph7gcWNXopcB/wUq8B0UZRF18fxQvDnFZURIv55rw5pl+/5SG1cQwki6kPtYim+4UCttXNxHqoNsgvVukBrZ5UbTFTejRDpMlHsTNTUg7JxW3wO/YOPBr47gyaqDCeehd5vrYeiYE0Q5V8ffUuiBQFXE7wSb/0Wa+TR1B4KZ1U9llpJnxVqw2N/9LFOFPtlXRIgHzT628ZXwD+2M3V+n3G0yRWEBIwwsCJM+HoZkWvARH0gqtBLijIW5q/Ea2Jd1HFwVSSfDnEM4663Ais5lq0ep+AJLApNVhuJjHXtMyye8+zxBle7rb8L8CswByRL6Ln0rj80Rzeo++TIhp7ALWUkPCJBPav2Fz2driNzwBwgQlsbNNtVB0cUeEQQRARGRkgQtEe6UphTU6uzqKpYW+Csl1papN/GxJdhoGkJoqTWrp98OORkd5H6v2Zynmb+8+GEf9n3Zl8qE42NqQRw6nXe1gy3fq5HcNLBrEELfhtCmMu0s0TVHqc8KZ3exc8C1/xpRzPvu4GaznxcRIliuVW/gh+qplNkIhYZ8KMcR2tpAfDgdgQhruIO4FToJv8bmhvzl8dRDKuTvdpdGYs65DT/cJ0Vg9T+Bc61eLL+IXNKE1M7dnrcznZr5t8sZhA/UXid/3ieNLObF/UXNqIUO7164CVnNrAO3VnFvwtBP06kJ9RIW+R0LZe9Dc7nC8abRwG7u2PeI6umHPhqxGOKEytwddHdpPhKDLfWMbQ37P3PcSO4H7F3ypPZUJGDx/F3Ou3Y9f7bV9u5TMAacOBhAfD4FOEIBId2/hjjNv/mWLMK/qPhxaFqlypHwTLfC+1Vh7ZNOqrvLdodUufTimtYMv/weDCHoeZuLEYznf2OGomWArh0SBw1bVzdLQ+DpKxpAhWX1eJG4jVSeIvuOslp+PkjKZk3Dt9CGtcrMpX5nZweB3PaSL9d2CClD5wKw/JQVCQexvuJ0fDlLE1Nw6dU16tJRc10k93kfd5vRiJfghHtLDpUThcM1rt+6Qw40XijZEDAP/kt6heaZizHcTdAGCWm84uhA8sQKgQSWsG/oM6II3XmQMdTvmRuOPsIomYKzLoHrV4AkdyuI22C0yh8brjT+hEgpXRkGCLEL1yuT/33FMrDPZ/kvwcxZ+SeN+iiPcBAUZ+gW6lVU/zQdqe6ANKR3w9J7Z5PesWSsM/ZAhxwFgpbxuqkOcpdQ0TthG5u0MBp/9BfrCa0sy6D3NjgTdjRh7JU8Vt5VqMYidqzvMIe/5bxIscssvaEDbuUwnW2jUf3RLKQRFJ8V/PQCaozMFo2UUnyZAZmVHCJBY9OLjzxUv7CZzFilJm/G5ufeNorVWkeShqn0gemzO6HhI8gKoPEeJ34yisEj8nukJlvmbKXszJCMQkna8hMUY1y7LM64ItV4wJoyk4CSVCp9dJDxm+j6AN+F4qOadM1RZYHEsb4VtvLO2enLiRvJQl+0FcWraRIz8bpvy2wjNA9zZRUUZWpL5F5rYXld15hge1OL5ztIei3uCpcVMWK1yKzDvktrWbT5RwFkPFv8i2izFanV1o7A7dOFZEmJTBHPAUnc9Pfahq2U+LUCEIXB+DfUe+L4iftAc7UBM2n2sqvblcg/OFIMDBKtNNP7TuB2Dd0pvrijgyRhDGZIn91DulE7K6f6Nb/37p+il1Oa3vWS4/n+Z1fzJ/0gB1AGeVVRrCTxzFW+xzw9mr3iLXyG2+4ofJ8hHpoSR8DbUYnTId80yLSFxsSmtpNK8U4Fk4JqnK6fDNFhhXHscbhVeTmyXeQEVN3HME2ZLVG8dmbFvosVIy4EwqTIf+DTiAfqrUgKJMLwnxbztFFec9m1ABfPcoWAoUdtbB7Yec9kKtaV19bh7la2YYXz+rjiI4YT87YISKDsbUC9kYzrenwI1f5wX0JhBksdE5gQCyTAUXqlJWnMM7xWSpGwrmwrsV0YPVmwG+wIoSdTApA1ZG+o6vsHlMSj9vk/NJRxx/STNqqaKKc32qosMUqcsKI8VxuxkMNLl5h2OtzACJtXodvS8t0hHCl6cM41SQpjOkOOIcgkirn1dqaOptDg5boyDNcWj3G+wfvWpz3iYij/GH27XFJEPJg7H8uKnVi+SI00G7pVr4t7IB8yOmlHX5hV/1lIynwObydhyh4olm2ROAzPjkejD7kN5m1/QS+9FivULSwrhA0qqo1dj/WkraLeLK3K9ekL25DF6v50R67vHsvKdrcapup4BOBDk5/FR87apqjWxheauRCO+pK21MutcpBPbhFZTY6IMJYr7uJ+y5Rrf2Q0TXsk10jfR3yl7MA26HsFyAj7mD4CAif7vrztEvk/iDPr18kSViyiM5KaKJ+ZHEyBeJzlJJQ7HEWHuCvqIVo8vnXCS+GWt4Z+KPzG/YviUlGTq6tVj4VSuT6m5evRy5HGwKy8X4mKNou798zYL03bwKk5jfXzr+XStuHg1ZuatgW6xNDuMiwjqVCLO9fFj9+SS3rmcN4jcQrnLFYO1vDTgtG+DA5jugnxAqWrtLA4V5wDKIYuziHbbmjbIhsCQZmbSgwYwNy5P4gP5ztVDHrOA3FaiWROpvebaNoy+VVyy8Kltj+WAPI3xNM=
*/