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
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
*/