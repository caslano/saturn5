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
#if !defined( BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP ) && !defined( BOOST_BORLANDC )

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