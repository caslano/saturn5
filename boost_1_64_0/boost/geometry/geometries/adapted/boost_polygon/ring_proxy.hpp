// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_PROXY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_PROXY_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::polygon_with_holes_data -> boost::geometry::polygon
//   pair{begin_points, end_points} -> ring_proxy

#include <boost/polygon/polygon.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/mutable_iterator.hpp>

#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tag.hpp>

namespace boost { namespace geometry
{

namespace adapt { namespace bp
{

namespace detail
{

template <bool Mutable>
struct modify
{};

template <>
struct modify<true>
{
    template <typename Ring, typename Point>
    static inline void push_back(Ring& ring, Point const& point)
    {
        // Boost.Polygon's polygons are not appendable. So create a temporary vector,
        // add a record and set it to the original. Of course: this is not efficient.
        // But there seems no other way (without using a wrapper)
        std::vector<Point> temporary_vector
            (
                boost::polygon::begin_points(ring),
                boost::polygon::end_points(ring)
            );
        temporary_vector.push_back(point);
        boost::polygon::set_points(ring, temporary_vector.begin(), temporary_vector.end());
    }

};

template <>
struct modify<false>
{
    template <typename Ring, typename Point>
    static inline void push_back(Ring& /*ring*/, Point const& /*point*/)
    {
    }

};


}


// Polygon should implement the boost::polygon::polygon_with_holes_concept
// Specify constness in the template parameter if necessary
template<typename Polygon>
class ring_proxy
{
public :
    typedef typename boost::polygon::polygon_traits
        <
            typename boost::remove_const<Polygon>::type
        >::iterator_type iterator_type;

    typedef typename boost::polygon::polygon_with_holes_traits
        <
            typename boost::remove_const<Polygon>::type
        >::iterator_holes_type hole_iterator_type;

    static const bool is_mutable = !boost::is_const<Polygon>::type::value;

    inline ring_proxy(Polygon& p)
        : m_polygon_pointer(&p)
        , m_do_hole(false)
    {}

    // Constructor used from hole_iterator
    inline ring_proxy(Polygon& p, hole_iterator_type hole_it)
        : m_polygon_pointer(&p)
        , m_do_hole(true)
        , m_hole_it(hole_it)
    {}

    // Default constructor, for mutable polygons / appending (interior) rings
    inline ring_proxy()
        : m_polygon_pointer(&m_polygon_for_default_constructor)
        , m_do_hole(false)
    {}


    iterator_type begin() const
    {
        return m_do_hole
            ? boost::polygon::begin_points(*m_hole_it)
            : boost::polygon::begin_points(*m_polygon_pointer)
            ;
    }

    iterator_type begin()
    {
        return m_do_hole
            ? boost::polygon::begin_points(*m_hole_it)
            : boost::polygon::begin_points(*m_polygon_pointer)
            ;
    }

    iterator_type end() const
    {
        return m_do_hole
            ? boost::polygon::end_points(*m_hole_it)
            : boost::polygon::end_points(*m_polygon_pointer)
            ;
    }

    iterator_type end()
    {
        return m_do_hole
            ? boost::polygon::end_points(*m_hole_it)
            : boost::polygon::end_points(*m_polygon_pointer)
            ;
    }

    // Mutable
    void clear()
    {
        Polygon p;
        if (m_do_hole)
        {
            // Does NOT work see comment above
        }
        else
        {
            boost::polygon::set_points(*m_polygon_pointer,
                boost::polygon::begin_points(p),
                boost::polygon::end_points(p));
        }
    }

    void resize(std::size_t /*new_size*/)
    {
        if (m_do_hole)
        {
            // Does NOT work see comment above
        }
        else
        {
            // TODO: implement this by resizing the container
        }
    }



    template <typename Point>
    void push_back(Point const& point)
    {
        if (m_do_hole)
        {
            //detail::modify<is_mutable>::push_back(*m_hole_it, point);
            //std::cout << "HOLE: " << typeid(*m_hole_it).name() << std::endl;
            //std::cout << "HOLE: " << typeid(m_hole_it).name() << std::endl;
            //std::cout << "HOLE: " << typeid(hole_iterator_type).name() << std::endl;

            // Note, ths does NOT work because hole_iterator_type is defined
            // as a const_iterator by Boost.Polygon

        }
        else
        {
            detail::modify<is_mutable>::push_back(*m_polygon_pointer, point);
        }
    }

private :
    Polygon* m_polygon_pointer;
    bool m_do_hole;
    hole_iterator_type m_hole_it;

    Polygon m_polygon_for_default_constructor;
};




// Support geometry::adapt::bp::ring_proxy for Boost.Range ADP
template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon>::iterator_type
            range_begin(boost::geometry::adapt::bp::ring_proxy<Polygon>& proxy)
{
    return proxy.begin();
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon const>::iterator_type
            range_begin(boost::geometry::adapt::bp::ring_proxy<Polygon const> const& proxy)
{
    return proxy.begin();
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon>::iterator_type
            range_end(boost::geometry::adapt::bp::ring_proxy<Polygon>& proxy)
{
    return proxy.end();
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon const>::iterator_type
            range_end(boost::geometry::adapt::bp::ring_proxy<Polygon const> const& proxy)
{
    return proxy.end();
}




}} // namespace adapt::bp


namespace traits
{

template <typename Polygon>
struct tag<adapt::bp::ring_proxy<Polygon> >
{
    typedef ring_tag type;
};


template <typename Polygon>
struct rvalue_type<adapt::bp::ring_proxy<Polygon> >
{
    typedef adapt::bp::ring_proxy<Polygon> type;
};

template <typename Polygon>
struct clear<adapt::bp::ring_proxy<Polygon> >
{
    static inline void apply(adapt::bp::ring_proxy<Polygon> proxy)
    {
        proxy.clear();
    }
};


template <typename Polygon>
struct resize<adapt::bp::ring_proxy<Polygon> >
{
    static inline void apply(adapt::bp::ring_proxy<Polygon> proxy, std::size_t new_size)
    {
        proxy.resize(new_size);
    }
};

template <typename Polygon>
struct push_back<adapt::bp::ring_proxy<Polygon> >
{
    static inline void apply(adapt::bp::ring_proxy<Polygon> proxy,
        typename boost::polygon::polygon_traits<Polygon>::point_type const& point)
    {
        proxy.push_back(point);
    }
};


} // namespace traits

}} // namespace boost::geometry

// Specialize ring_proxy for Boost.Range
namespace boost
{
    template<typename Polygon>
    struct range_mutable_iterator<geometry::adapt::bp::ring_proxy<Polygon> >
    {
        typedef typename geometry::adapt::bp::ring_proxy<Polygon>::iterator_type type;
    };

    template<typename Polygon>
    struct range_const_iterator<geometry::adapt::bp::ring_proxy<Polygon> >
    {
        typedef typename geometry::adapt::bp::ring_proxy<Polygon const>::iterator_type type;
    };

} // namespace boost


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_PROXY_HPP

/* ring_proxy.hpp
31GyV/2N0fsLPzBkWrrWtvGqZ8aziZsvtbr970bzqkPAOfaF0j7ESzrMNc+c9NNrHgPe/e4mZfxRylZpnQ+Z9TqvvE95MqjM3w6fE1U78J1RyrqvYiZoHY/7VN5RsydRpk+jqtip62LGDVrH5XwycjTfNGoa0DYOssbYf4r7CvpehelmubhpZWsR0GYPscp4L3HzC3HIXo6PRRrllzgHhDXMKgNLxO/mNvLbGtNniN4pWyTz/w6E+QxhBrz/NzSwPZskdvuyQxd392e03I6x1rmWiZ2m1EDCFT1/uPltJTXcoGe15injxV4avWrcvZ5XxpX7mCuffJE2gIkPu8pyaEzGTWpW6SU9e9bH2LKIFTffYN/7ko5Fx/h2K8SNmpXDbIPpJjyXf4ysfma+ZO5TzDROg2LJHWaYVUU/Tf1lBDofn92RNl2DUPM5qCydX7g5b+N5WDYncoRxVcPw5ptSxplAEJF5JO7z0D9ixn1KexyHucR/NbuMyhKzMoYjDxby5Anca1H/e71snk0/ZUwtPH08Y+WeRsP8D/xIxNy63/GCcSAvwviZS8bTaqc7drJ8fvAsYVHY4kRBlI7tg8M7boX3toZHuvH8hnkqZqsDw3sfn2RxJiJKwlM7x6zw3g4ILyIovBIaXot5ZngzdOGovy/EMN+a7gn8ip8XEOZC2U8ywoyUdVe10xQ7WaY/LBoRXKg9Jau8nZin88epp0POH2N0zWzvESd6y+QGoTjR87d5UTY3taak2/CzDf5tR60XP8/555Bqdhzlm0NOPZ09DRbNN+OywzNA9uycLs8YwHghW7ysOfRyiVcdHZeZcWKMR5zkbAzhdZ7v3++b+oGRCxGS6y5NjwS1N2++FbcdRuHyUjflPQf0M1FrMTP0px70n/XM/gzdF5jPsOi+n2GmPEPcXZ9hKWHHLwh4hpUhnkHtdVtgPcOiwGcojH5nlDyDm2dYjR/6DNnr8iTTHrGe1sgIJI/Ys9ovzDdHy/yvlDcszrpryzqrov1YBXMchbsM3JxAyb2l00rhdVSYNyxvjnbk5gJtGx3TGvj2Q11ip4KaN1xM+RI/jnjKhufmDcw8TheJ7AzPBaO8EZ6773Xnhd9Y4z1kfo3+zFd+orGRY59b8+eKuKmrMrcJiJsQZ58wXwIjjhrmi5jBFFY9vkUkenkivLYL4YH74F+K322D9sE/FL0u1Hv/PnhJcT8lojh9UIbtX+G9I3JjrnvilnmviC7cazyWNJ9pOxqeoPen7RX/Krkn2PrxDb8N4YdwK3vGpPXJRea7OdP+bRTWaK8nIkc51fz83oyryGbaJZJ2Pv/a4Nd2lPQnzun2cAeeme/lqPkJlKyb+IKLtNpdjU8S+btOzD+lHSzgq0FOm/j/DW7jMTfrwbSfZAVJ/DfNa2O+wXTPGhP1RMyzt++lXtFyNL0pXlUNM4pODdu9y04jSeNaVtmZI3KJiFjbH+H3OuvQVOyVDrpXuYXo0Zb681j9ixf/4sw7lS39Ij59zdM6ovd2xBTyMymiqKRPU579wBLyU56rt5578LhytOk6hmwtY5QVnhURefT9E/TE30Z6X5H5jF0jOthmhl+k95O2hDBWoMx8mN7fn8+m+T6U7/zE9N5GRgSenzDjWuwVzevpLY2mxs0mpPh/BLc2zNaLWQdp5cx8jFPzwphvsNw6w0K1Y+nLzDzeT1tBBte7d/5+Jc9a2XrvL+wjOc8Z7rJ1D0/n2e92DuayuCtonYPJPlfMXjZyazvxt7iLwh2yFd5IexHbGe7+rBdUhj4Tu4lBZeiA5lUJfxlSP14Nxw9OOzdmznPdRdwD7+hWO6vDPbYu8lxSpoLmFB85mUNKXpQjnd0=
*/