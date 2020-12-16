// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLE_ITERATOR_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLE_ITERATOR_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::polygon_with_holes_data -> boost::geometry::polygon
//   hole_iterator  -> returning ring_proxy's instead of normal polygon_data

#include <boost/polygon/polygon.hpp>

#include <boost/iterator/iterator_facade.hpp>


namespace boost { namespace geometry
{

namespace adapt { namespace bp
{


template <typename Polygon, typename RingProxy>
class hole_iterator
    : public ::boost::iterator_facade
        <
            hole_iterator<Polygon, RingProxy>,
            RingProxy, // value type
            boost::forward_traversal_tag,
            RingProxy // reference type
        >
{
public :
    typedef typename boost::polygon::polygon_with_holes_traits
        <
            Polygon
        >::iterator_holes_type ith_type;

    explicit inline hole_iterator(Polygon& polygon, ith_type const it)
        : m_polygon(polygon)
        , m_base(it)
    {
    }

    typedef std::ptrdiff_t difference_type;

private:
    friend class boost::iterator_core_access;

    inline RingProxy dereference() const
    {
        return RingProxy(m_polygon, this->m_base);
    }

    inline void increment() { ++m_base; }
    inline void decrement() { --m_base; }
    inline void advance(difference_type n)
    {
        for (int i = 0; i < n; i++)
        {
            ++m_base;
        }
    }

    inline bool equal(hole_iterator<Polygon, RingProxy> const& other) const
    {
        return this->m_base == other.m_base;
    }

    Polygon& m_polygon;
    ith_type m_base;
};


}}}}

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLE_ITERATOR_HPP


/* hole_iterator.hpp
qSd/UvIC3BILf1zjJZxa9KC0Y0Fhe7K7scrhK2IeWFeHUj389aPpUmlfrDOBbute2yaUe9/faMk3331qiYwJzj7GfRqE5cz42lPSU8nYIoi82/v6h7QeVBfZXw/K0NNMoY5t4s65z3imYvZ4ZrGL+IJxQ1sXxyu2/NgI9U5eAfiJ+FHQ976ixmnc4xqnZwZ7ShCjKI8RLep9cLyss8ud5JkybYnEbQwzsDKir/WcL109QZqMQj1NXn3IbYsJdre9leOB7HGy2vge4q4zY94IiZf5jfI1er75IfrtOjF884fK0FrX9sORI1BUHJGTlDvy+749XhM3O/m9C5UPuRZyA7gH+TD+fAXXqBtDvYe8AH4EPybcNwLUsfyWPcYP4r/YXSfjRqhjihX/Y66yKGCuQpttzVVikFNV7tcTHR2DHM+25pSGTF+OrGvF/r1f/3cZZe4hbb/ozYSnxY22fUHv1gW1EzKmWSxlnnsoon1y4srQ85JFPXwPl6Lnr5+AjbBTbLU1xgl6+aiPbDlYQ9yQ7+rUFbePOFL5/zrpFG+dnzb9Tcjxjomek1fzWawcfM/7fm313RNK1RrZp7Z7KPPVqP1ZtkrYqCX93twcc2f93rb4VV/XKNgdED+uMBIqzPPHMQcrwfe9aocct7aAtcR9K0e2729b5X3wavO+63CfHtLropdmd/Od2RLGPiFjyB+fJP/jjD3AWeEuZ+Vwr9cdxYuzufisScC+y93XDuq97jsrGx0Qzi/yLC9Sc3tIXTPf62hEnbiDox9QteO0rN/nvMgov7lfDy6/oc/zB7/vInohxtUDJS1YT9Ay6Fnjkx/OGzzOXtHTF4nndM44DSVl8I17lcHAoXbo+XFNcT/C1iVwfix6cXcrf2o+mrFVQXpEh7UeJu9rBM4173P+ce+0C/4WeVI/n+P+xnfKYDJMMt4LtNLBnwR04Po2ccg5hropb/W5t0R+2JXtXLxVZ6+J+WfOxoxMVqIu2Vfp+Fv9oq6YeyDO9cjY0TNI/HG/0gj/fK75WsP8Cedg7CTY6zjkfXTLXQ1HFCPh7GW9hPZrv0lYj7j68MWwbY4nbUWd9W09uO80zTlMznTUHE3MsXdD7DVy+fcqWK4POFNxeq3EOXjPSOvT5HWyN+ZoYttnN9fiXtsg+4fZ74a11hHXi5sv7Y/ho+hZz1OV59mKP9YcihmU/0yJV+JR3BVq7tEG845iPsrZ2hFp24xPt1gfZyCZo02qoPtdiWJ/PTYeZ5aYbj9ln8c3LXvbTrE2XdBZzdbG2QS32MXWt/JMzaWNjBG/0oyHClpTPb1O3xtQ/8+IvNJehuc8QP5VZDzWCilGzM1nLuEIIy2yz1HM8lJZ/HBb3zq2S5xruvxr5/2N6mzExdoHc4mdB13y3IFjW41nPzFvZCtHvMw82y56rrveW5Aq8eBMk35n+h2x/zNx38guI/ko+jnLpTPcSivrDE+kuK3syt4XWN9qX6t302jcWkrYzzvy2V4nHZ8PKO9yvst6rvh1epcYOgnqtqHoLXAUwe3HuH2KGMdY7qm3pExg2K0l/l4rXbqLnF/GqqtpWzunyn3DvGGUccv4skIBryvWMLvdh/KUap6PiTYGixGMF839OjFPTtV7h8WpM7d1FkX9fhPzTeJ+POZ5ihj63dCbafm7AH/dEXJuRs3WorJ8bjxDMTXvQjOUGeeGfTXO3imfGAHn44MQob478agxn5D0umynF1A9M08rSZ4afmYRZrG+AWdufsBD/JBnUfOkvvqsviAjzTiNoe0vHDCO3UlF2axjyQT4JSoO9RUqXceXOvYU83pQ9Ph9Xn+fVPeooD56kI5HF0T/7/7F6K8PbcjZX6c=
*/