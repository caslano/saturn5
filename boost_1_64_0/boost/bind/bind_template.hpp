//
//  bind/bind_template.hpp
//
//  Do not include this header directly.
//
//  Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

    typedef typename result_traits<R, F>::type result_type;

    result_type operator()()
    {
        list0 a;
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    result_type operator()() const
    {
        list0 a;
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1> result_type operator()(A1 & a1)
    {
        list1<A1 &> a(a1);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1> result_type operator()(A1 & a1) const
    {
        list1<A1 &> a(a1);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1> result_type operator()(A1 const & a1)
    {
        list1<A1 const &> a(a1);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1> result_type operator()(A1 const & a1) const
    {
        list1<A1 const &> a(a1);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#endif

    template<class A1, class A2> result_type operator()(A1 & a1, A2 & a2)
    {
        list2<A1 &, A2 &> a(a1, a2);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2> result_type operator()(A1 & a1, A2 & a2) const
    {
        list2<A1 &, A2 &> a(a1, a2);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2> result_type operator()(A1 const & a1, A2 & a2)
    {
        list2<A1 const &, A2 &> a(a1, a2);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2> result_type operator()(A1 const & a1, A2 & a2) const
    {
        list2<A1 const &, A2 &> a(a1, a2);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }


    template<class A1, class A2> result_type operator()(A1 & a1, A2 const & a2)
    {
        list2<A1 &, A2 const &> a(a1, a2);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2> result_type operator()(A1 & a1, A2 const & a2) const
    {
        list2<A1 &, A2 const &> a(a1, a2);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }


    template<class A1, class A2> result_type operator()(A1 const & a1, A2 const & a2)
    {
        list2<A1 const &, A2 const &> a(a1, a2);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2> result_type operator()(A1 const & a1, A2 const & a2) const
    {
        list2<A1 const &, A2 const &> a(a1, a2);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#endif

    template<class A1, class A2, class A3> result_type operator()(A1 & a1, A2 & a2, A3 & a3)
    {
        list3<A1 &, A2 &, A3 &> a(a1, a2, a3);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3> result_type operator()(A1 & a1, A2 & a2, A3 & a3) const
    {
        list3<A1 &, A2 &, A3 &> a(a1, a2, a3);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3)
    {
        list3<A1 const &, A2 const &, A3 const &> a(a1, a2, a3);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3) const
    {
        list3<A1 const &, A2 const &, A3 const &> a(a1, a2, a3);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#endif

    template<class A1, class A2, class A3, class A4> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4)
    {
        list4<A1 &, A2 &, A3 &, A4 &> a(a1, a2, a3, a4);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4) const
    {
        list4<A1 &, A2 &, A3 &, A4 &> a(a1, a2, a3, a4);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4)
    {
        list4<A1 const &, A2 const &, A3 const &, A4 const &> a(a1, a2, a3, a4);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4) const
    {
        list4<A1 const &, A2 const &, A3 const &, A4 const &> a(a1, a2, a3, a4);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#endif

    template<class A1, class A2, class A3, class A4, class A5> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5)
    {
        list5<A1 &, A2 &, A3 &, A4 &, A5 &> a(a1, a2, a3, a4, a5);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4, class A5> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5) const
    {
        list5<A1 &, A2 &, A3 &, A4 &, A5 &> a(a1, a2, a3, a4, a5);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4, class A5> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5)
    {
        list5<A1 const &, A2 const &, A3 const &, A4 const &, A5 const &> a(a1, a2, a3, a4, a5);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4, class A5> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5) const
    {
        list5<A1 const &, A2 const &, A3 const &, A4 const &, A5 const &> a(a1, a2, a3, a4, a5);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#endif

    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6)
    {
        list6<A1 &, A2 &, A3 &, A4 &, A5 &, A6 &> a(a1, a2, a3, a4, a5, a6);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6) const
    {
        list6<A1 &, A2 &, A3 &, A4 &, A5 &, A6 &> a(a1, a2, a3, a4, a5, a6);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6)
    {
        list6<A1 const &, A2 const &, A3 const &, A4 const &, A5 const &, A6 const &> a(a1, a2, a3, a4, a5, a6);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6) const
    {
        list6<A1 const &, A2 const &, A3 const &, A4 const &, A5 const &, A6 const &> a(a1, a2, a3, a4, a5, a6);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#endif

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7)
    {
        list7<A1 &, A2 &, A3 &, A4 &, A5 &, A6 &, A7 &> a(a1, a2, a3, a4, a5, a6, a7);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7) const
    {
        list7<A1 &, A2 &, A3 &, A4 &, A5 &, A6 &, A7 &> a(a1, a2, a3, a4, a5, a6, a7);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7)
    {
        list7<A1 const &, A2 const &, A3 const &, A4 const &, A5 const &, A6 const &, A7 const &> a(a1, a2, a3, a4, a5, a6, a7);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7) const
    {
        list7<A1 const &, A2 const &, A3 const &, A4 const &, A5 const &, A6 const &, A7 const &> a(a1, a2, a3, a4, a5, a6, a7);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#endif

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8)
    {
        list8<A1 &, A2 &, A3 &, A4 &, A5 &, A6 &, A7 &, A8 &> a(a1, a2, a3, a4, a5, a6, a7, a8);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8) const
    {
        list8<A1 &, A2 &, A3 &, A4 &, A5 &, A6 &, A7 &, A8 &> a(a1, a2, a3, a4, a5, a6, a7, a8);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8)
    {
        list8<A1 const &, A2 const &, A3 const &, A4 const &, A5 const &, A6 const &, A7 const &, A8 const &> a(a1, a2, a3, a4, a5, a6, a7, a8);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8) const
    {
        list8<A1 const &, A2 const &, A3 const &, A4 const &, A5 const &, A6 const &, A7 const &, A8 const &> a(a1, a2, a3, a4, a5, a6, a7, a8);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#endif

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9)
    {
        list9<A1 &, A2 &, A3 &, A4 &, A5 &, A6 &, A7 &, A8 &, A9 &> a(a1, a2, a3, a4, a5, a6, a7, a8, a9);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9) const
    {
        list9<A1 &, A2 &, A3 &, A4 &, A5 &, A6 &, A7 &, A8 &, A9 &> a(a1, a2, a3, a4, a5, a6, a7, a8, a9);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING) \
 && !BOOST_WORKAROUND(__EDG_VERSION__, <= 238)

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8, A9 const & a9)
    {
        list9<A1 const &, A2 const &, A3 const &, A4 const &, A5 const &, A6 const &, A7 const &, A8 const &, A9 const &> a(a1, a2, a3, a4, a5, a6, a7, a8, a9);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(A1 const & a1, A2 const & a2, A3 const & a3, A4 const & a4, A5 const & a5, A6 const & a6, A7 const & a7, A8 const & a8, A9 const & a9) const
    {
        list9<A1 const &, A2 const &, A3 const &, A4 const &, A5 const &, A6 const &, A7 const &, A8 const &, A9 const &> a(a1, a2, a3, a4, a5, a6, a7, a8, a9);
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

#endif

    template<class A> result_type eval(A & a)
    {
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class A> result_type eval(A & a) const
    {
        BOOST_BIND_RETURN l_(type<result_type>(), f_, a, 0);
    }

    template<class V> void accept(V & v) const
    {
#if !defined( BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP ) && !defined( __BORLANDC__ )

        using boost::visit_each;

#endif
        BOOST_BIND_VISIT_EACH(v, f_, 0);
        l_.accept(v);
    }

    bool compare(this_type const & rhs) const
    {
        return ref_compare(f_, rhs.f_, 0) && l_ == rhs.l_;
    }

private:

    F f_;
    L l_;

/* bind_template.hpp
SFcx7hAzaJu4G7jG65oOyskvn1tC3zqiePi5xMvw3hPymyu5i/PeA0r4Q8xNa6x9v9s17YX6en/dxDWO4zoPWtMnbV3fcbPE7e7uTXs2xr8zkfZoofvG4/q2gLr3+xHYiPaecwL9ZFZAu+scXr3P03pW2Vwz35c8Blw/w5uqrVS12TgUVpJuxot++jCavRAddEFlyXWy6sIE8fdz/4G2+4y/3G637b67WDKh7a9xW5k9kMeKv4/7ea6cA+TzO1ycaR9fuZL12vmzyI+hTNGuGFwCzrsXctluWf+r5zZtZMbGlVZcfBG0ZbJe61Pl2Occy3Q9yhW/jzb2rvnMkvQ6yZrk1lxHNcxzbGxd850bd2hcbC3UiWzQeFb9qJhY0tP7GtqdxqG/oL0vjKONyUegHidofi6Uc2fgj3B1wWk59LztpH/QNQiiM0us+yXcBlwM+Ugn/bm17yNc61jr0SFpJ7++I4bjMuZoX/syrqd1v7/b6Irsh5wvD1/B+tJR6/iQyD/j6sm/Z+PG4n6MuwP3kNlLU9I90T2Sj7sH5mDvmKnlSNPn1Ta4HtaY8Uf/chTqU+TkJaXHu7/WeHGip9ubS7sWVkgcn65F1IgM2hllxoQm2sd3PsE+3t4mRc3Muw75ReJuoiypNf5lqbCVYXhqUBlUvp7kx1VLfqIhaYTMzyar/Gp3Nl55M7IZfvnx3I+UO9epyrcKfY+s/f4EkdnqiuXfm3C6TxJ1LKJm/K4UuUXY82sg66njtUAjtU2S5ZhbjuXIsfWuTNrpCuQD77sT+WueyFzLu6WY4Ptu7ceuF5mL0bkkPebWfJyHzg2W++4SamxXnPe+u2dMVNOYyHOd7rtV/kCc3nc3CbrvNjKxzXFJyMRUBD+TqUxfZJpZMtGzA5/JjEw2MnGWTNPKbWYfO5XRPHKPf/L3dna92dMiWG9us/TmpQC94cH1ONeiyrcK8ayrOvOSn86Ebl9k7O3bQXRKkvHp1EsOOvVSCJ3imE2nQjxfq868FEJnOGbXmc20yVFOdn+YOmPJp1K3v3DSGZUZjky8k86oTBEyLZx0RmXWIJNQi85EJp38/a1dZ6oSPMI9vXt34n5u6czLRmeKy1mcWZGXX1TobAtD5eMCx2UTPuJlv2c5xvST77e9Y9Dhlh7hXH1um4LbnMqZTd5lb++wxyDiGb1PaibvN41djbEmPMG8y1kp/q7UWxM95natlWOD0Pq2occy1f0bjFx9OV8TKZGImefDapGJdUibPcB1/Dtg7W19Anulh3rWobwco7yBzzpJngRu0zpehbvbGuf96tgoiPP4ru3ve79roogMaatMC7MPetQrsh5W7nHm44Lu+bQum4hcqasd+Z6Jk3cnqmPLkH+49rXMY5zueRL0fk7X4Gme/euob7LWkd7T3azv7ne8YmwgDOf+n363kNe3Rv/4EWTTiXdEfqlrtlxJ3B8nkSau2Op3Ypv6v+/X/qCrytUjD0kwJrJP4/rcRp8WGdW4o8WY1Kj6DWIa9CCe6gz1YuoksE6Nbrv3iI0T14/87PaEt3+6/f12fzVicUzfH36Kq6bsVXt8dVM8u7C84uyS2fPLiiuK5ubM4u259alB8nYTisGzLF6jSxo3xfT5D4j/ddfjei3pc3JRXvE8836gy5/E1o3RmfskzmuMJbGu3+jzyViTdivb3q1zCzBPIOFZJryL6SNchHPV4B8qz447JPxF29pTtRuiOr1HwrezdsZtykcasliaNETXXheZba4zqPMY/FHxnvv2c/V5N5HztsIJafOr4nzPxa2Tam8fr55zbnRa6jbguUXqTo5lmf1lpR7kWLbpL6TsGtekR1n8daD6dJf8dmkf8hg=
*/