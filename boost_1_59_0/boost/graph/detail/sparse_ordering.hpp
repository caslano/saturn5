//=======================================================================
// Copyright 1997, 1998, 1999, 2000 University of Notre Dame.
// Copyright 2004, 2005 Trustees of Indiana University
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek,
//          Doug Gregor, D. Kevin McGrath
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================//
#ifndef BOOST_GRAPH_DETAIL_SPARSE_ORDERING_HPP
#define BOOST_GRAPH_DETAIL_SPARSE_ORDERING_HPP

#include <boost/config.hpp>
#include <vector>
#include <queue>
#include <boost/pending/queue.hpp>
#include <boost/pending/mutable_queue.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/properties.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/depth_first_search.hpp>

namespace boost
{

namespace sparse
{

    // rcm_queue
    //
    // This is a custom queue type used in the
    // *_ordering algorithms.
    // In addition to the normal queue operations, the
    // rcm_queue provides:
    //
    //   int eccentricity() const;
    //   value_type spouse() const;
    //

    // yes, it's a bad name...but it works, so use it
    template < class Vertex, class DegreeMap,
        class Container = std::deque< Vertex > >
    class rcm_queue : public std::queue< Vertex, Container >
    {
        typedef std::queue< Vertex > base;

    public:
        typedef typename base::value_type value_type;
        typedef typename base::size_type size_type;

        /* SGI queue has not had a contructor queue(const Container&) */
        inline rcm_queue(DegreeMap deg)
        : _size(0), Qsize(1), eccen(-1), degree(deg)
        {
        }

        inline void pop()
        {
            if (!_size)
                Qsize = base::size();

            base::pop();
            if (_size == Qsize - 1)
            {
                _size = 0;
                ++eccen;
            }
            else
                ++_size;
        }

        inline value_type& front()
        {
            value_type& u = base::front();
            if (_size == 0)
                w = u;
            else if (get(degree, u) < get(degree, w))
                w = u;
            return u;
        }

        inline const value_type& front() const
        {
            const value_type& u = base::front();
            if (_size == 0)
                w = u;
            else if (get(degree, u) < get(degree, w))
                w = u;
            return u;
        }

        inline value_type& top() { return front(); }
        inline const value_type& top() const { return front(); }

        inline size_type size() const { return base::size(); }

        inline size_type eccentricity() const { return eccen; }
        inline value_type spouse() const { return w; }

    protected:
        size_type _size;
        size_type Qsize;
        int eccen;
        mutable value_type w;
        DegreeMap degree;
    };

    template < typename Tp, typename Sequence = std::deque< Tp > >
    class sparse_ordering_queue : public boost::queue< Tp, Sequence >
    {
    public:
        typedef typename Sequence::iterator iterator;
        typedef typename Sequence::reverse_iterator reverse_iterator;
        typedef queue< Tp, Sequence > base;
        typedef typename Sequence::size_type size_type;

        inline iterator begin() { return this->c.begin(); }
        inline reverse_iterator rbegin() { return this->c.rbegin(); }
        inline iterator end() { return this->c.end(); }
        inline reverse_iterator rend() { return this->c.rend(); }
        inline Tp& operator[](int n) { return this->c[n]; }
        inline size_type size() { return this->c.size(); }

    protected:
        // nothing
    };

} // namespace sparse

// Compute Pseudo peripheral
//
// To compute an approximated peripheral for a given vertex.
// Used in <tt>king_ordering</tt> algorithm.
//
template < class Graph, class Vertex, class ColorMap, class DegreeMap >
Vertex pseudo_peripheral_pair(
    Graph const& G, const Vertex& u, int& ecc, ColorMap color, DegreeMap degree)
{
    typedef typename property_traits< ColorMap >::value_type ColorValue;
    typedef color_traits< ColorValue > Color;

    sparse::rcm_queue< Vertex, DegreeMap > Q(degree);

    typename boost::graph_traits< Graph >::vertex_iterator ui, ui_end;
    for (boost::tie(ui, ui_end) = vertices(G); ui != ui_end; ++ui)
        if (get(color, *ui) != Color::red())
            put(color, *ui, Color::white());
    breadth_first_visit(G, u, buffer(Q).color_map(color));

    ecc = Q.eccentricity();
    return Q.spouse();
}

// Find a good starting node
//
// This is to find a good starting node for the
// king_ordering algorithm. "good" is in the sense
// of the ordering generated by RCM.
//
template < class Graph, class Vertex, class Color, class Degree >
Vertex find_starting_node(Graph const& G, Vertex r, Color color, Degree degree)
{
    Vertex x, y;
    int eccen_r, eccen_x;

    x = pseudo_peripheral_pair(G, r, eccen_r, color, degree);
    y = pseudo_peripheral_pair(G, x, eccen_x, color, degree);

    while (eccen_x > eccen_r)
    {
        r = x;
        eccen_r = eccen_x;
        x = y;
        y = pseudo_peripheral_pair(G, x, eccen_x, color, degree);
    }
    return x;
}

template < typename Graph >
class out_degree_property_map
: public put_get_helper< typename graph_traits< Graph >::degree_size_type,
      out_degree_property_map< Graph > >
{
public:
    typedef typename graph_traits< Graph >::vertex_descriptor key_type;
    typedef typename graph_traits< Graph >::degree_size_type value_type;
    typedef value_type reference;
    typedef readable_property_map_tag category;
    out_degree_property_map(const Graph& g) : m_g(g) {}
    value_type operator[](const key_type& v) const
    {
        return out_degree(v, m_g);
    }

private:
    const Graph& m_g;
};
template < typename Graph >
inline out_degree_property_map< Graph > make_out_degree_map(const Graph& g)
{
    return out_degree_property_map< Graph >(g);
}

} // namespace boost

#endif // BOOST_GRAPH_KING_HPP

/* sparse_ordering.hpp
bMh+rRuHC2LGTedri4Z3BOopNnpXdtdt9/5ptypM4s2WGl/7oIFwy1mQ3IhAqeNeTEqHvQmWzRsqlloTGvispil36Pn9V9LkSFGS0kPNqnla9XhesgEEjWAhub4nXrBo9ZkdaaolvR/K9EmvVbVskq4IVID2UbhA7MNacE/935QyPtauoR17fcU4BTP0zvjxneIcXayRaMkiMpZ8Fkou6tOsnDi6mRZiRLUOrS6UfDL/cZgj668la5+T0ISGiBTRnrbMZhUzlkKFmyyJZYKh/Eghx51WZhEw6j/OtttWRF1V8CztqIWLdx6y6+Cy1bMeF2iRdcPKRCs6VdPSYJ+NjYhhOPIoN70DhbxJE3BIG9obh6dc9rtySctOglPNCcTdwsBT4/8yFkQEiFDVE4uDNEfPy8Gdt2PGBQ2EV+EChxOI0qUktwEf0A5dUkcm88ZHBDDFgFd5uVPYESJEQYunlA2TdsWoqjI9wnGzHBXuflKYTqB2zJ6gl14mGMYNF0LxjssqDBFHjpVE8Kp6ZtCiblVj1DTBAaEVVsR2me/AGFX3YUtkLekThPrBixxI1uCOlVsNAfZwf0emr5p9LXMBYy7YoXbgdYX997jYxDbSPRKYq+wG4XlqENH6mjG3l8w0wmISTS+IHxc/TgH97lNUV196kWh02oNBD+Nn/jv0E5b3IQ/mwoxyz+azZ6UBIgUBTmD81K37D5PsqkSzhC1IXXMsOXLqvYKJhik3TkEnhKpQHfbZz5N38OG6siOdkw/3LsoLskvneZB6OeSi+y53o/gH2yCTfhafScyzLeWePmO4qmnZ1MUAkjYHShoeIk8gwjrRaboJFz5mUYnGp++lI6XprMOJNjH9QjmtHz0DSVVvaFzNBXgrjhG0uXa5rhP9kpkdUSgTSUoKNVViD0gzOCDNfG/jpujf+/VcCzNzdhlQejjNN/R64K2cFKcKSyRs9H8+Z4kNEhHRw+OfRLpBfhvw1p0PUs3/1QjpJMhZLK6gEGwBywP4E5AS2sCIj4Md/SPwWprqol2aiv4kkCf5151jP8AxFI7QdSAYXMLyWfYTn9nbyGXUxaFioRgFlnWfdK0uxaoKpwafzAy/D3mxGWVQ0d/VO5XPda7Iizde4oN5CKpHaNKei743YSbjCaJArpjLw8wFsplxrOs1+tHPikL/Ju8rdQgrkqkyo022fHJunrAijWSA5Ux7bnKhicmrarR6Zlsk6Gtc77QSRPwl3+35nHac9mbS06Rno0X0wnhnyAZrpFkti4w+B4C/XFpTTK2t9mohnhJ/7WXgw14DWcJ/3OUHRx/iYfCt5qxXvvOIAdKZrGbITVf9KwubzGRKCt1YiJskq8R8uxTLWj+B8BnAZuty0/0R8EnNz1Bfo5mn2ZzDKcc2mzZNFZ0ilRyfKedVmM1lrCfBrX/4a5Hb26iJk0D8vNN2YX23LMxS8cVPm8y+p0uSkC7W52fyuy2yOSF63QTtEadvwhRGid2TX2yT2TMXZxgC6IKiF0hweVrysB3TVMxfiNR8mh6/f99tlcHsxtFtUWLsVqR4d10EAlTjyf5foa+r5T9Gew5ts1v0F7CH8AOULnolUI9AN1BeVSlaRwsJREM4l9M7DyhFGAdQsdrEx9OqfGrcCQabSknsJAxGbep+6neqe2wX0OSmY62Q0esxbNOx2wfkkfMTHhEUnShU1H/rtIG3WZ36lCuSEuu4RWudE+gpuAAz0NbEfRnKXOGPPY5nHLf0wvY7t7922a9nttFB07bdXPG07vzOAOspofSigWE4IxJfB0LPgNt+hwh3XYSBAHJb2Doe/CHwq7oAfNmrg3f7nRD3TuDL2hl7HZ+oF7GPOxBkC0eZSSnEysJ5N2F9n/aMqFgFrvQL39WTrKOktFp3zEpeF5tnmPGGrCmJ2zZQs46GGhypCstF2+1Nst8yljM3b4b5OjVpByVqYMens8gx+WFFmRjQ77OSM927eqaUSxYwS2RvQnJFP0clph1pYhaUnsxYn7IiBU3DI31hXcqLcp13kuSBD2fAqOiY5X40Axf4BTOiYZlMlhvD85isNoFxvaFom84uUuzC0ve1snUL5cb0C2vhTcCC5GueEILCBgOKGh/2mgRFIzjjH2QRey1kil3Zb3GS4dxT2h4QO37kDQo4wjqQgbTKmcus0bMRadc282S1+uWlsJGFuwtWF/WiwucV0t99ebC9SrwIKGM8S6QpmS4JdQMQoO4zkITvyliU69loGOo7/1lgum3W4JUhJUrLr6S8TJbso31+op2VSMFD8xGiG41ZE11KZVxyt2wyTg9GOcV01FnkbVO564VNwnemqLcnk6XjgacHR6s36imoiOqwMKSsIK35/OakYuj42MEGjVUnWYRcr7BzduS05bXrUu+A7yScHcXYrcdkj+Hw176BSlUxep6jeUFc1ceNTAjDIzD8MFN1iMaVf3faJKeQvPUUV6eFF3HLqrmw0ETDWf6DLDyevVbfCNZipvdqx4q2kXidKWhX6f32ORDlzuhlgy7QyUQceuhEg99sYkwiBivZXSO++bKdECUSk88fc37mZVkoxgFrdqVTjfCDAtAUCtaS9Ok54dQvzzI78nvKvocZMZZPLKP7DTRbD+nq8C5s8XUhZSCGNVpOqZ7Bnw/8WQ898nykff/OnV0tyfSrBLnffl4ZyWe9e2eYRb8M7T2taO9bztgetLiYBiKkWCtzFaTGTF+L9Ncp0coIdFQgjTDPHCawfEuzMDV0IUHfESpZexWC2W+MowIq4KR0QmH9eUsFZMIIuN1WY6B+aW39a3ov08wURxk4GVktZXkxbosQUjPqUOZbWGOz4IlS7a9ft5tmn/UQuhrpgFk3yd07Kcm7m+AXohiSdFmIlbS6Jj/gNfutogJWN1iWFUF8yAjZXeDIyrZEtbAeMWg2p1s0uvaySOxlEIMJYH4O8BcZ02p7q7/vqm4rB9WQyrs+roW8BV/P+c1K9joTN1Q4lXwmMYfP4togmNdLZcfB6Tttcdj9s2yj3Z9uv/sB4n6E7v0Oi3Ldz1MsK1VdmURYtbvRI5qQG8PbAC6c9YbHSNfU4JRkuE+QjZEmg/KRZZxbMeHKw6oac4CX9vIprU+EzjD2Tf5V9VDsdM4xzPAGhLjedc+ZEEzsottDp3F0SkMbuzlfjIWbKRVKxRpAouVV//u8IYi2p+JEVyXnxR/s50Ml58+1tAbgrGBha7C2vAFoYiWh2eIMdrJd03Wepw1fImy91f5yBt9muxrZ1XqDRoElND/h/H7BZeH4r/6hkTppItvSkdRYUwQe0bWDcHPsnd0A3AqAZTK6qeG6LpMO1LCk61FTVLplBDbt0ZCCMQB7J9sHdrt4+Xi7WMZImi7+2i27zsZUa29e5ZeGpnZs7DfyBR0Sp/mBd81aVYGxX7Kmrjry0Jy4KsSDLpDj3ayhRhjqS0BWBswMNzXfvduGJypxv9uFpyikSN2caVsOSHuMGZOJy0kLBDMn8rTtFwBylCKLwCDVmU9sDcBWyOi7SJ4xyUDsACb9g6uZkZ4AZeu+yTZY5cOYT8iiLEIV7ZlnGTdWW3hYCu2qNkfOTCrpcdC+pWjuPPlapy/HQKsx/UQhDl10CjZzWLIeHp5bf0G2wsg8WQh1Ee+Xpwf1fhy7HXZlJg7qWv+WEeGVp5e+hpsWwQhez7e8IJZMDa894GcRqPpZDmiAZHnfUOyB0Cy4CpByRsKsuomGyKf4EiJ90hzSwminQJ41WB026NXD44qvgyubLgWqaagF7ZwNyLNZisIGC6TePCtI0quZkeh48RhXzC3StBBn8aqgKZ4HFlUBWstQHu28BSTZOopMJyyKAX52QSt5m0/9wJ3lXL2SsJL7NC/HWlIjU+bxPxp51aVwgHSxpjgEqNIlu1vNjT7deXQRYgcg2uw18emYpMe3E2tmtY5dnOOQWSpQHqE923UjAWVhshC2yVImFMXRQSXC+O05yRgMbd1l63sD+tVaQ6/21+3PAtMSnTZi6IF5uv1xAAfofmMiM8gwOo0uFov7h2PqGz0avvoDwliLKdWenuaPENWcl87VWjdGSzXAi0HnS/5K3keZw+pnbMNP88vaTX2sMInFPEdgujkkozDNEXS0T58LThzncE9kY2UQAGtPiPCqGWxo7ywbK41lldvPVNEWETGkLypfx1DcBQ2b+8+PmfOd43I+HleGV8eceMxcfzuBiRC/+4DR4SelAs1nprntK4mAngJQoh/gCgVA6uTovWfsqzcYd6JddVjIos/KDjMN9Pk++SIsv3s6iH1GBEkMiOyBb7iLauiLlLtGUYBKtuxFjT72F+R5Dv6F42OWrIu7xyvJbeC2DJFbNhldCIKsSFBGE7jECgm50uIOUK15EdcXkXLkV+D/qozEEW4hlOwot60axp9c7bFJwrDu28qrOGQfXaLO6xUR6SenkGCdsi+yqD+akXrNmZzLU76yDZs9KmxxKcw0+unMDbN/bA3Eq5cqXWgCbeRT/0s5Y52dqkb63Qa7B3N38jY836MMcb0IaJwr0G1x6GPUADeRpPWeesX1YlXN63CA480OJiHXkUfWFQIRTbJy/+CvJObYI8WNzLlA7uao2FdmfxGyf2T53J360TP9rWv4FcuJpStSi9RZPmxVYr1fMTefSrFTjEq2gEze9/ScVT14ietg29vY6xfiu3iozwoBvSrN3OZYi0kOQcpmuuZrGtcCcZCCWiYzKWBAlDhcjxHuxZRlxwjg6LA0uhmm7oRkZoQ//cwgFuw6nouz/cIlI1Rjboq1o1hMP9sr1yVbYLDBsoxlkckKvRXHGtko5KvC59esNBYM3/948ARRMqrDW4Rjv5rrpd3QuRcz/awQekOnEpyry8rZYOFZ7fU/UJY3JD1VtuvF/09yLMsyGcqdaCDCmILaTmmb2D04+HyjidLNQ+Wm0mSSowONDjknKq1Tw3Mm3hlOAYLWt+13N01qkcbkhyGlnDLIfDzlI2k1eG29nox/1ljJkWvzt0m5gpSwA7AjDrT1ujTE1qWkR9R50+ddfSl6sChXO7VuMmehIyKlWRaaW18SZP34hK/N8qh10MpyRjyYlJMUe2GweCvW75ek93t+RK2y1Z/T0e9qtpsgpCYuegAQ/bkux1Mg7FKjZmPpmoVrt37OoE3t7Xp7HU3yDpdHaJfQs3nbVRdH69OJrDtx0qN9i0Y+fhK5pLMauGBwqi+c9uLeY88a9iLSQziiY7qi6WQhlmH2I5gkAjEpasARcQCUDHKH094/pO8yihjExT1lz6sSpTgyedds7lneAtwxEtHGvud33sVu4GTaTaAJsg5cf+9lqEOJ4CckUO0NGakIZNctruGuD5DBMGLoeAVPZBOcGJVNipXQ8+lVr95+dyl8/o69VMV4CsW7iOL8gSGvVrV3O9DJD87lSsOUfYwHKtYUiw9D40RDf1J1evLcsVmjVi75sTra0T/QiH665nVGcKd7yfqTZqBcempJSdBdIZW4YxHojUWaP18oBD7WX6rHfQlgpZtokMz9V8oi+9UJTSyOEC6hXxsdkRZl93337MXrlegnQ4PXK1JSXzdXOv3rpCgIi0SrikM1Y5Y7JaXri4Ge251UBZN2l0bLgvikfaJr26hnU7HG13xAfZz1KRRUhF95NzxlznDX1W85yMbx3LXdNEy7sXP4B43jGM2LgPKFXW3iRfVCR5tdvGtnDPdMtVO7yNPyoN3UK6/BsWAvqkD7GU0AroMP0+Tq/t+20tXsLpueRYlh1wcN49njscl9rVtlqwr31/u1uwavrSG5dIbyYTzPf7qTVb+DwXGV2hsaahtmnwJ3mK4MIyN9EolftSVMxonakpwzJzlUObvKFtvdwN2dUK6nk0I4M6Yhd6CGj+hIOflyJeBe3FotqsItwtow90guItx7RRiL8ozk7z7p6J6QjCAuDnEaPoGZC0uGANeL/Q13KXhjad6vI4iA6v3I5zYnE6EQ7ym6Wr0cocPaq9AnQ5gZ9CucPMjbi8oiwae2jY5orE3pCpwXim6Fu9NBIcUzxVED9Y3h88MXKmYN+EipFYzEseandBgiCOmmV2zohvQUJQELV9dKBKzQ4OKqObXLT0HtYeXGNaX4U9u90NStJmP9W9edCMqypJ7GfSmO8ZaGfFnfjUg5cC6P/3xpr8eu4wn4RiZVUqOJVNy/vhdZVlVM50hqpIwOT1cQY35Gq7VabVV61PKues5I8jOhNYdSRML1WLf7D7iDbDzoiy3s9qZQHNrqy1PJHK/6bNv04rTD+qJ6zHIB07OXVDsLdZW2i5K11VT9KX395GBTJrVDpFKjxjsQjRTveGVQxQ9okECF2Ide+TjIJ+RmD7Bzh/HYJ7fueDo1sXT1SXhoZSlxtIxqFE6m/6mOoX2STczcKKwn0QBHwanx0xM21NL5oOGBPIMToFmFb8gAwKqqpfFiz/YsYPTyna0/P/PPWccI6xa40kQCYshvO4eyMiRzg3yPIMf8TI0Gi6BsqMY6s2MOpUtd8m7LdmEQd5vd2DIdTrixaziwurKT7lue2TJFlm68chwQhqzCU8V4CSLIW++A418G0htFJGS9Bex9g3Hd6c6l2qquCYRkEQHVd5FOFQPiIWh6wslv8d8HIcY0ZRpgJsjFLXQwl4ZgbAOyFbw8BWM4weyj7C8vxBvCewDHKVFPtuRbWs4SPqKNHcUftPrXiE6M8QUnG0CDxW54QVyraL7avyoawUP1PD8V+KwHf5C3IJgR0HUx1sdOrPeTuv82BUuupAwiX5/kEiPHxXJYc1O95WoPxMY2lR5ria3R8sYs0VxIb3yLxRq4Oi+MgQrSHRppy4xqXVlerSEKFtbPZxRb8G4MqdI054609Cjk7X2u+ojp24msPecUNGmOECS19Sod1BFoLmB2HDZZL0h/gtzm2vn3pdsTv7XahY4oveqoGR7JeSMikgFMbJZz0no/vLi1IOFK+FG1khiaM/cvtzykWD7D3DHkfZFA0YgHjAx/rEpn+YPWdLao0hfsBj1Vleal+Z7f2tbsSKyKOuO+f+R7e4N3/1zmaFUBP0HPx22W8FcdsYrVlkdJKbgAU0ACXOJnht9yDkTDGUcpWsokvjw2d7u0XlXXYo6MwWqiiO9I5I8OT/wIxtQ50lWe4I+MTRETC2IiVHIxKJnRYSXMpzt72dixdneWUtIq7BxtPDK4oGXrjO/t8SzXSg94xaYdpbC1IwmWQJ+u+bMWvYkjkP7qRdd00TzluW9OvG2PCjdZXIGu8E66hoC4hPAWtnI0x7RkE0HP0w3dT3iYakLBFWKeUIdptvFhqa4bqMwiSymmIVf07g7YQM35/ktgazF6Yp6r833dBZvplJ7sWIM0I7fx86n/xzVpbKJDFZVmA48MPr12QrcOIvfh8eG6HlAu7sdxzACAY5RZIu4hd/fLNjIm2DlxSyf46TCn4TBKXZoGMfntSZ3wY4UM0b9KKJrjGfF6utByvTVBgQDNbayrJCRjCwSGIQ6xTDtkctt6oVfVqkXQQZgY9tLRoR2GRJwFoVKKmw82AWra3lc49Q9tsl1V6/CiKvnxZ+st2bdCrRyrZAg+qYZTyb8VVV3Np+hIkzoEScto2f43U2/4MvWtmS0ew7b1KZ11pFsoAzUP
*/