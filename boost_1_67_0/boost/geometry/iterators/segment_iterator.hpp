// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_SEGMENT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_SEGMENT_ITERATOR_HPP

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/detail/point_iterator/inner_range_type.hpp>
#include <boost/geometry/iterators/detail/segment_iterator/iterator_type.hpp>

#include <boost/geometry/iterators/dispatch/segment_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// specializations for segments_begin


template <typename Linestring>
struct segments_begin<Linestring, linestring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            Linestring
        >::type return_type;

    static inline return_type apply(Linestring& linestring)
    {
        return return_type(linestring);
    }
};


template <typename Ring>
struct segments_begin<Ring, ring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            Ring
        >::type return_type;

    static inline return_type apply(Ring& ring)
    {
        return return_type(ring);
    }
};


template <typename Polygon>
struct segments_begin<Polygon, polygon_tag>
{
    typedef typename detail::point_iterator::inner_range_type
        <
            Polygon
        >::type inner_range;

    typedef typename detail::segment_iterator::iterator_type
        <
            Polygon
        >::type return_type;

    static inline return_type apply(Polygon& polygon)
    {
        typedef typename return_type::second_iterator_type flatten_iterator;

        return return_type
            (segments_begin
                 <
                     inner_range
                 >::apply(geometry::exterior_ring(polygon)),
             segments_end
                 <
                     inner_range
                 >::apply(geometry::exterior_ring(polygon)),
             flatten_iterator(boost::begin(geometry::interior_rings(polygon)),
                              boost::end(geometry::interior_rings(polygon))
                              ),
             flatten_iterator(boost::begin(geometry::interior_rings(polygon)),
                              boost::end(geometry::interior_rings(polygon))
                              )
             );
    }
};


template <typename MultiLinestring>
struct segments_begin<MultiLinestring, multi_linestring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            MultiLinestring
        >::type return_type;

    static inline return_type apply(MultiLinestring& multilinestring)
    {
        return return_type(boost::begin(multilinestring),
                           boost::end(multilinestring));
    }
};


template <typename MultiPolygon>
struct segments_begin<MultiPolygon, multi_polygon_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            MultiPolygon
        >::type return_type;

    static inline return_type apply(MultiPolygon& multipolygon)
    {
        return return_type(boost::begin(multipolygon),
                           boost::end(multipolygon));
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH





#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// specializations for segments_end


template <typename Linestring>
struct segments_end<Linestring, linestring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            Linestring
        >::type return_type;

    static inline return_type apply(Linestring& linestring)
    {
        return return_type(linestring, true);
    }
};


template <typename Ring>
struct segments_end<Ring, ring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            Ring
        >::type return_type;

    static inline return_type apply(Ring& ring)
    {
        return return_type(ring, true);
    }
};


template <typename Polygon>
struct segments_end<Polygon, polygon_tag>
{
    typedef typename detail::point_iterator::inner_range_type
        <
            Polygon
        >::type inner_range;

    typedef typename detail::segment_iterator::iterator_type
        <
            Polygon
        >::type return_type;

    static inline return_type apply(Polygon& polygon)
    {
        typedef typename return_type::second_iterator_type flatten_iterator;

        return return_type
            (segments_end
                 <
                     inner_range
                 >::apply(geometry::exterior_ring(polygon)),
             flatten_iterator(boost::begin(geometry::interior_rings(polygon)),
                              boost::end(geometry::interior_rings(polygon))
                              ),
             flatten_iterator( boost::end(geometry::interior_rings(polygon)) )
             );
    }
};


template <typename MultiLinestring>
struct segments_end<MultiLinestring, multi_linestring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            MultiLinestring
        >::type return_type;

    static inline return_type apply(MultiLinestring& multilinestring)
    {
        return return_type(boost::end(multilinestring));
    }
};


template <typename MultiPolygon>
struct segments_end<MultiPolygon, multi_polygon_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            MultiPolygon
        >::type return_type;

    static inline return_type apply(MultiPolygon& multipolygon)
    {
        return return_type(boost::end(multipolygon));
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


// MK:: need to add doc here
template <typename Geometry>
class segment_iterator
    : public detail::segment_iterator::iterator_type<Geometry>::type
{
private:
    typedef typename detail::segment_iterator::iterator_type
        <
            Geometry
        >::type base;

    inline base const* base_ptr() const
    {
        return this;
    }

    template <typename OtherGeometry> friend class segment_iterator;

    template <typename G>
    friend inline segment_iterator<G const> segments_begin(G const&);

    template <typename G>
    friend inline segment_iterator<G const> segments_end(G const&);

    inline segment_iterator(base const& base_it) : base(base_it) {}

public:
    // The following typedef is needed for this iterator to be
    // bidirectional.
    // Normally we would not have to define this. However, due to the
    // fact that the value type of the iterator is not a reference,
    // the iterator_facade framework (used to define the base class of
    // this iterator) degrades automatically the iterator's category
    // to input iterator. With the following typedef we recover the
    // correct iterator category.
    typedef std::bidirectional_iterator_tag iterator_category;

    inline segment_iterator() {}

    template <typename OtherGeometry>
    inline segment_iterator(segment_iterator<OtherGeometry> const& other)
        : base(*other.base_ptr())
    {
        static const bool is_conv
            = boost::is_convertible<
                typename detail::segment_iterator::iterator_type
                    <
                        OtherGeometry
                    >::type,
                typename detail::segment_iterator::iterator_type<Geometry>::type
            >::value;

        BOOST_MPL_ASSERT_MSG((is_conv),
                             NOT_CONVERTIBLE,
                             (segment_iterator<OtherGeometry>));
    }

    inline segment_iterator& operator++() // prefix
    {
        base::operator++();
        return *this;
    }

    inline segment_iterator& operator--() // prefix
    {
        base::operator--();
        return *this;
    }

    inline segment_iterator operator++(int) // postfix
    {
        segment_iterator copy(*this);
        base::operator++();
        return copy;
    }

    inline segment_iterator operator--(int) // postfix
    {
        segment_iterator copy(*this);
        base::operator--();
        return copy;
    }
};


// MK:: need to add doc here
template <typename Geometry>
inline segment_iterator<Geometry const>
segments_begin(Geometry const& geometry)
{
    return dispatch::segments_begin<Geometry const>::apply(geometry);
}


// MK:: need to add doc here
template <typename Geometry>
inline segment_iterator<Geometry const>
segments_end(Geometry const& geometry)
{
    return dispatch::segments_end<Geometry const>::apply(geometry);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_SEGMENT_ITERATOR_HPP

/* segment_iterator.hpp
zcjKRY0+SVHF1rpv7cs6P4qjE/hK1KbMeC40PEa9OmR4rhuafxsG6CsyfQ28I5WQj13QZqZ4KD2ecfLGd0CMCAOH+oTf3QC35eO872DHkEDE59eRknLkxEPQSU05HS8cvnjCnx7qKVz2b5HYOAzTWYtyfulJnr2sC3BgqQnubIaFyngWZ5CCYxOzwkDDObYLP2P3w+H5JuXyuyJxr5PMvBYqv5gbrZdHEYnou4FmLc8Y2kij12KhARQ/NVIlfVWuNaRjW3bdXWLj0yq8OOuFk2ZruWUo6chbisukI/LWaDLuY/dzDDOp3dO8e7gtwfCRYMRuUkpOYjBW6absEZO6g9uttwmB4y4eHzAMw9JE2Pyn36D/adA0cjDM8xZe0HZO/Md/565EYOcOBVuK5tCNx0AxpgpLpsXPq3STTOsR0mjgHdKGIsyvGdFXQkIxQ9eIhDO4hZN/K6oTPGKWJTBS2U/Z5IVhiAIfdrGovxfGK1xFi29piOE9Hn32wTOxyHURoSfTENQ2c9xJkVhSrS8tK2D6kXuewLuJ0ls3V+BooDaBFTg0xcDBxHTdqN10tBjXGtKr+REmqfclKNCqIO67Oq+3yKA207WgWJk3ogmHCJ5icEuWGg22SLX4j6s4YQxAZYZ6o9jR2maSbg88Js5OQLoFwWmoN0gs3wGKjIM9sZqDRMZQOU42/QVfIQ2SMjslYREqwuIaaKs1OBST6BMe4BMyt6REus2joD+8b4ob4oGALlyY5XvXI12ufUM3PdFmwbYQDQZD8rYBMCQ4ctn727dr1vbU54oq0Gbh+yr0QEjV+4CSW5fFZ7OslfR2tMU27gv1fJTISP0cMoMjC8p6LyyZVqbcdAbQjo8J58vQYC0bjUNsbXhZVIUJF68qBq64Ht0iStNYpfGLSXyP6VLanq4FtIcRxucszobxRZdTotdueR9QKpgKomuV/bqkKHO0VG5DGk/yduKfFMon8Pj9w9eulolkE2YasjzJ0TnadYv6sc15mjyV1ML703XBvQsx8ux1AGdGR34DsXPI9lKaEQiDKQYSWmFP+Ndix5KXBJ3cxTHjrV2n7Zj5BwpCrEpu1p5mTrJNljlo8ayGn0Ja4EvGQrRDz3m01bQC1TJEq+HsP7KUfMeD1hV1ztoLFmPy+/X1RhoR9//oqfdzi2q8NCJquIEqHr7DvdTMelbfGRBS0S47EjkOS59n/zUXV4+KT9N6avFlOv9jI/gxT3RdIGhT5OxFn3MCn5kW05f+MOzPz/MygDKQ9cWypHEjYjygfplCcya29NnnQ85kewsjzpepxHlx52rgozZ/t7J6vcGA+zkr6y0msTuDirG0KudqUDOtclqL+dASYdL5kcrm1j2vI6jase1o93DNk3Rx68qDqjPCERxBftdEQgDJVOVaW/2aw9DWMqx2Dr5mp+SbcLXu3RHPXFe7Jw8IPgRa3r0M+k07m7p3NX8udfiy4RiTSG+5eYOwkcvAtZiyQKZCUK4Cg0WMwRJaurE9LS1y9jxCs2Z6YktMA8jctlL/cpdN4BLKopaEY54kuwUJ9OcsBkvVu66M1Cbh7avz6t43yF8rpF8caxkXLn2JcELMe+Jvlq3iz2N92dtSN8ayO+Ql1mAFBDtUEskDmS+bPfQmlrIZZAZjxTj/fB6TGpu72hVcAqTrSXKrZ7fRjekdvrFdKphm9aeeLhNeiOm6YzyELBPCWV4VBucF+5pRHLDu0CyvxZZi4ql/Fp+q/nwCw/kIlP0WSNVlIogeVHxzZfyV3d+1+OIK9NVIqGlH4Ohe5fee+ajC18uS6n0gBbs/qGdp1fKoKlWwdJDJ2dz6dJw9Y8CktOe8Tx1T6nmR7omn9XYiIp4BybYsG1LZYuMNV5HdKzrM5UfSbZ+EQemyQh6wmivP0z0UP/y26PA8Z+Gn8pg2v5kT4NZNZIGUi8qnwvgChq+/D28JuScecFa+1fnKTEeHMAhPzWlooZIXWIf2hEyhFgXAZtCiFktnjzP7PCdLLF9L1RRqot/PNU+iaKxPlENyfOZMcuCujILQyh6lubLfkbNQECPtQGpgNGZ67pGktlNFJ/lPDwbJtneCkQh7WXNcGDiAxtm8GZeI7dzM84car1ejg40kcvYgWWcCAuWMZofkks4IEfrrzcMk9bwcgrFpboDmN5VdmgaFkYrsC2MmsdDMFUMEBc7e/F08KVFcwAxNoOFsP4w/Ub4TeWOzq3IzzFd00Z7V2XwfLj1x/0ViK3XL0X6BJ4poiWXKsx4BcDR5E0bVFrPRg8Ef6xse6tMMBRk5VvX1qI+AR/Re50QiJlK+KMSEBUvKBjIVqRZO5bTBvs4jW46zrJowM2gWFlg7QflZXIoQEEDRanIkWmTmyqI/muG/NXiXGVzEDXPlaCG/ryfqeqTVZrR8sZbyUCeYY7WoUtf5VDpGTj76gIuOe2brsI3IOfpNeYQJYbvancSM05Y6PcINLsq8Ya1uzPffG2OCinpDWzeXKtBBNina0kgNDd5eKsaWtG+JmHwjMGMrAnVT2BVd3tpIJEQdxMr+OjnPaQXrWDbirspmtA5oFVKOYbpLc/cCNL6OxSUS2OUKNSMiAjAUsEpic7duA/Xh76mktto2mEK9c87h48w0ov8iT+f6sCj9kdMWMc8B6SeCj0vNorfibYqMo5tY8Xcii4Y0f0y48/fg1sJWLJRUjnZDKgVhjLBc2x+egSin7z1XcG6DjyZ5RaJiFi4FiVmVD+ZW5TNIPZZqNvs2/Mqo3EPI2chuYcY0e0yfZ6r3ubkX5NMtokXvo+kOs3ihqrJn8MwYZF49P9IDpxWisvo0hGQu6R6dn2Mz2GEIFw6sIMIqay8Yqx/0tzAZY0TCLCihXTHwql6i785Y5BpsePoPZYq5INlK7/zXveqT6Fw2ZDjpf6qdkq+8ggf6NVS+r2VinUmuZYR8nTroQ6X1sfPAWusLGqz2/7kdaw3pqXJyuF0b9Dgg6J0fUZ3eJSM4FVvLUVDB/fDCqF3ZOmOpHgu9PAfe4mMzu9QA0r5zGlubCTqgM4zcnF6aVqbHdTvGHwDeVJ14v/Aj31UeQhVg1B69Z2zPHuA4Sf3Y0xbq2rUHu2l76TRR3gecA6wLof90CbIoNJhLcabmZqI21Vj/4G+3mBt4K3B0K3jTncV5wjz4oowYSskiXrcBqmJWpXIm84lQTliFWWCQgF7EAvLiozE0dQ3MDWTQPt+5j56ZXWcox6znNEBSNSpV+ZAy/bhFpdm70zpfNVzdllB/r9tb2qn2glp5JMD8EH82mZg4kPUeQWp2jSpMwxZfd1mlzT3WfpbDeX8i2yw/Zu9vRuIwkg01sy6LtJMDBw3posutVFj1H8w7fAEMTMOKlJjcYncZINq8Gz3CxHoArQYMCx23xuAS8XITZ57tx72b0+BElt9trkNoIhmq5VyL/OPnJ381D+vLx0zar3P1Z+Jml5CePgs7qLpAR71OWYalrd/a42NOtTmbthYFq6zGp0eW9CfxFsjtyUMyIJ1MDY4SN5vvIF7CZqWmgFbprPVKdFnOQJEO5dJfJ0jSSQBNbofOLf8H7gluDzuGrPKMCCbtOgQYGiUeuXVMRH7n+vLJDDO0q/ER5oEC3dVFHVqobK3mkq65IPSQ/iiH6YAAU97T8fSzyMw+s+oBrpe6VQuSBbqQDJy8R7zrDmphNhAJvHppEAugL9TL5FXYMXTiUDiRWLJQWxm5cE98aUmLvGkvuemsgmYFyJlzFhCxrpF296sDXFBkyaoJ6kI1TFQUctyK2kd0frWBO+zpTPiKX/94pr3uizXSC32uqjOFGvtya6hHXGjNB1+LXnYtR6UPF2nH+SXRdryghkpreC06r10ktR7x/HOEwMp+gdK5Rv5ftf0wK7FpmXOtpVTjE8ONOlNmYN/KMLbJAKrWwfzudpQyNPZLmZp1f30vC4bwXo0bbG1X5IiXVj4fCfwKVcU7ckbSGDzNRX0w2BFmY5xRdNiYqirpzeHpXYb2wiDxcnF3rJIWe3aO93+ckt2AGtFHVq0CAAws89NWGJH7xi7597SYp/oTru7M0ZI2FCw+V563QgoSDjLWQGZ+a2bKAi/0jv8RbKg7r3XZgY+de2vTK4MRDcbtU7rWztyOMgH/itAPjpHAxT4cvWkt/l5xnfkkDTp/4RADabrAI+azC4jIAiEIzr+fKp3Ht6QdWiJUL2Nin9gZpd/cvROG1DyYnpRPrSNNcXCX5snPtFWvhv2GPlxmVfEzTF5puyFfSFXsL+C71zlsi2yHWE65oT2CPB4AG9TsC5jA9hNaTpqtDfyrl/vJBMonhL1OnRYS3svbW8Ksx3BBnn/B+9Lfgiy6VJyNQsYswpLZGAh8fOBtMwfJ2jUNT4dF4C7poQBFWVCDPD2rp8mKM0yVBAhEMqx/y3ydZ8NTvN4u/BAZqM2oOlDCcva1scfTglLfCR+2ZChrZJRjVIjH+qcQ51fZGHk9ETEEpNaCy9o7JU8cvPtlC2cQ8l6pjkZ7qlfm5VrTlesy1JXc5+dwICfveQuMpo9NlVsCNE8+21k/6RarbqMlorOmYp05/ZKRaSs8DD2iH0VgQVQbbHeoC1Tq+T4UO53Re05UBoO0yEAydZuFxFhRgbHsjBitGx+wJdhfsEs2X9U7yJ7FnwBpD+qPi3Le3ZVhZ5W3yOh+5YTD9Mm0XcrZgNliMudXMJEkJ7/6+9hmwDuxJlHfbQNHvLazJchkbe0kXi/zkI6VfnRnvydqWndcLgmMYaYy6i8/U3FkGFHK9mHeMN+LTB6DSyLB5f25ddyorvSK4yE0RLIapxlq4HbKkTqbjzBh4nTAta/rDfs2j1jKxYpdNcccysFmNoS9HGB6Ys9PtO+r1+35nMqaU4nq/luUCNrMIKUbIyqZVWxLCq7pPlFlPo+qyYHfHVF4oyIec6w1dxDTPaHVpsG+EpDhHWdUc25iRryKfCkRObCygqeuIvKpmJqyxsTFfbssudOpU22sQza5qwfHayo9eqo2KDrmtWUB9WaClkoxvDDJJoYk/lsC6A6vZlI+Re1bUYCioQHLKy3d8CY2vHG9x8qLNP2QiZce2L5otNx2BT2CKxIq+FAozsaIQTXwrwdJkY0BobU3C1a18Wx/yMZt0zeEU6b+XJSYhzVbdFUiym7ikt6IJXQJm5hW4jLQtbtSs0r6+ui/9cCnAW6mh7M8oxCvoqz2B8K8lYvGlHl6MIM0BbN/rewHXMe62TkCVK2J/XwuXgAxKASRcH74sJKJnWgGaHIr5/4OeoGMCrjYfaBTObUGfVWoGwwt4vTNnFDpgYzdiRsxsQ9BOjA+Ye2stkWcWTViLsXseX8N8L8zHQITHe3LTSRcWeAwK8LyLWS3cS4LCOU8dmWche9NZF4zmThfJNmnbCz1qAGS+UIxNqKBk4T/3p5oXd+Vzlf0vTy3Km+P8tCgkdxz+A+7421uluvyPYA2t+qtrrHZz3dF3ZLSfFHGFCd1EaLFHTHWTDAvw2OgfkmRsc9SUfPGOlrlftwotUFdEBS4fI6yuoXXmuhKzZ19idwV4awhJpZvuayZ78i6tfrRQ3WY5WB8rCGwQrRsKhhIT5wxJEnyP9UmI8+lX9UMJG0p6HPDZglPxpc0v5xRHwe0NA6Z11tLndItqD6SLag8AB/hHZPDBXrgBoFqnr3RMYhz/KCtc3k8MizuLZjNNDly7Wr0M8bugixI1k2tNCRozQSt00cLon+Ezn9oOnpJfNKnOFon82bx2PTeLsB0zffRYFGQhFH5+RJB+x6APEfqMo+91bQoYt+xfTRRVp2I/Ls5X23jHkldsM5ypOiRpxYK6YbBvn0BAAB+f6u6YdyQl5/pezJ1EkACOgX9yMsUFObnMHWUV0SwoJEK2pyE8KEMETcLZFrfqC6iRMdBFyQAFyeFlZvWNCNompr4NPPzQgLS4KUGxN7nwgQKZD5LnkuwrOLiqOHTfzlOZ67+xfHOfvLO5oqxMTn2zvK8em073pgsxGjLbIwZSm/sK7lQlUtv6zeuM1uMXmrM3+PKaC4zQuNdvSm4T5dWOa/i+Z+WBYqwCv7nTpzYslFMS/osHDoYK7RRIcGzfkdQx5GFYIw4m8IZGLJgQp49/OX1gwGElcBKm3vZu6frvR9g8OZa7f+x9ZF6N7W0fFfFhZU23bnbO/vtkPhb11mCowhtUrlxRgGLaYTWFPuCHPq0UXzHMAb7MIYxmHYce1X2UWg/egM34ul0bj7nphSibET9a9cEJjlAVmnsFsTQcgD0Rtk9UrT6taD5akl39EQB07Apv1IXGNLAaX362BM0I14JbRJYYyTUK4puZ/uvF8ElWQhNKSL/OCKdPqPvxPCnABgOlrzTFKQvHGTlHW6SCGZ4+GoEMxOpR7glaDLiHo9rAAy/8V46hcFlW6yQ57h50LrlwNDDlp13oxAUFGaekI+ne/fuxbXXfBCTTSi6fPjrhAAmOFTA+TCh0uhVn09DX8pwIY2TZNh0UpWs39ZNO6488ZwFyscx0IDIGvlRrH6lyFr+pyDLdOQ8TgFJRnil/2v5CxtL3EgsimXLoHGZtcOK+W3gl+k8CmEJCKbLSRjvCS0HMvo6TPVKP5I5rJtxhXktFDVZDF0SKMpMA9cJtMcqHmYkY9hFWpG29L9//v+Bvm+QzaD7eS2A/vKuK/1zRXxLydgz8gcNyttYmsSZ4S30SstOyGVM9JaM7nzpPIXPbEl6HDfi9hrM8gkcRqV90osbDX5b/t20pYbeFKpK5vPaj5r3RjMG0b/DGxR23QWk2xH9UU5ebFm1gNp86zUKmYdue4D70tqBKrR0+zqfx/VhP2iqV/o6M5JnP+E556stcsfqTF10i4xqZR/4L2Q7DE/zPZIv9j9MvP1jpFmsu1PcN6VNdRbuKLr0uwG9Xlz/ci4EMlqsHbOr8m440OJk6IcxZzNo38aDJ1ZRMRQtjS8Mb9CqbFNtLrBkgy/9E4zCMTekRadtkF6D3zf0dDA/AD8hqf8A/H59C8u2XkimFi7V9PzQzD3xpiD0uPa70g1QlL8749GieJzX4PF8y1V5sROXIr4aa1n0R0EdEjHF93cIYJD1gajK/VtruoWBHByAbjK49rAKWSMi6n+Qy/SUR/h6KOcjAn+fJ45UfxgOAvJnz4+/XfoGUX9cihdXpqLeq0IlaFHF1bBKgd8dkfKKR7YSumm1OGZkBnGzhvbjkrPJF56xrQ9bOj+jCbtRc7vD1lk0jePkfo16/fMeRVQniZxNql9OkMVjAQW0i5cPiC5RrJyBpppUM4MBBDXflFNQz5cIdTSDrOJxjaxp40ginQQeFmUFWr06s+oetp5/g3iT2fgpuaZ+j27FypoAlJs2xuXzf8GlGfBClZPDaAcZb3WtLpuDA4IDLgSDr2JUxPKjD/mjRWDzxvMFiyaiOCPaUzgJeOYScc4M6QxS5PN9cnUqs4PGbQ/okEMA1z2hAkwJKAXcQZJDFwheYEmnYUzxyIckc/2pRzLXFPpOmACESxR/VvyRgoGuBTBv11TRqbHuMGtPB/ADnxBCNC2esEZw3iRWmeArrwh+CKH1aqfxB3zT4i6eOxMBGOMBDmrCCXvXYp6iEJ4pwS+azwvga7MisvknSB2ODkZjbAW15IYlpmxiByOo9LoxyX8iwPwIqYUvhlSrCDiLoa3sWvqNAfy5raeysVsaBzWrweKJWYt35Xf7LVroeqWnvqwolI0rOiAM9JVcu0ETLSozkFsy5TnUp3bf4bjnjBkZiilNK67mXI/3mNGN2AC8/JpWcgQ6JNwGQJ/G5mXu5Ly7bNATN6DLdWywSyRwxj4RG4XMnzzgIcPcj6obwaBB74ZSBZtHB0FhBjS8uVhBnutXZEYiecQHGmsJKgJxDi6zhIfPSWTH7JshKH8+EvAGiRVQPIrsF0vqbPK8kaSNjOwSOdqXwsJFygFa9GPQKanOjA4nyKrzAvziwOcdRK8BIEohcnz2m/JvJ2RCghyI2HD7/Ov8ixjUu8keJPWWdNLlp0h9sdSbv+j87AsZExHsoLyIj8hd9yoUPA/tlpNlMftLZDKecGH3CNU1gQSEgZrSmWHmTmTkvJQTQUoIZcwJqHU8wOrSUmtBi2CW+tSw6P4DJVLnjk+23Vm3vbuk9CNnuTNj5J6GoaLca/WiAmgmuMbIE7xgGpLc+SB72dFxxFTouEEAduL5wbQKgPXKuQrBoMJ0nCHPfV83T9vFpwb4OcTyq8kGrgi27S+o00kSGFFIcl7RT5o8SMGDBUy7ROXv6NXAPdTaS6Izugxc2uJ+i44xKu/QBQCBNMizKjEUJJ10tmyGG2jdSIzA8uNivNLo2xgme2H8CbFxjHz6pF00KwWFErn0GodiEKp1DVgafMyc/W/CiNfmm/ttj6d8mcavt+eZFT0Wntbpmwd78g1x0Lx8eLRcipF7RCtNgDj9AfiWAoy5JtcLA7ZOhYpjQ1ErHCq+aEXlq+SeIXDZiGJP1WIK9pLuDDkOGquAsDEQk+VfVfp5X72c/4d6jZQ0xsnCBX3676NBEkiT3tSQHLD+rocwtat3C47AmS4P2O8KxPgL79HTs2BDtWn6RUM5fcfsHcssUlTtbQYcgiMaxyC+FjJDRYe4Gk7fmT7OjBB5V4Jvv7iTh27BIkAQcubyJSES3lcd4xpdna0mqRTNgLtQvFDtqAYr2b9ebm3vFYtEnH7zmPRSGK5NWCUPIoLnDAvhgSPpZxxqA7+kL1IZOyrbbZjHVdwRUAve0yf/IGWuxSHKxtlKx7xZ4HztND2Pu1WEMlXfsGXo/hPZM95xaxF8suo+OeIWe6EQkoHrHKYRgoMdS7n+S47a6Fe33wKJQBEClwGrt9+TGgiCB+pJh9Wp/lCdtpptltd8v+ljXwB0Yv327B9UjoLKoHOaB3a9YKWerPKg802ERZZzcnyusKrqYPE+iEUd63IlKOxnOPKYutIn4NftRVBsfhdvxiv4r+iSLHPueXTZ36NdqN+V9/Hwn1dTWqxNhoq9QIacGIPqd36AF180VHsr5uNEl1EDmrnxmzMg2kMWwfw7lpEXh6GWw4N2A2zeS8XYOASPJvFa1PNFQgYCorJqUdZ6uaN4HtRDp7POuNFzSTjFvsDMoLZ80Q59cpybDB0AYOdUKINxj2RlGy7ej7PWCS8jaILhInUXpZalSjk82K4=
*/