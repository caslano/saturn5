    ///////////////////////////////////////////////////////////////////////////////
    // poly_function_traits.hpp
    // Contains specializations of poly_function_traits and as_mono_function
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    template<typename PolyFun , typename A0>
    struct poly_function_traits<PolyFun, PolyFun(A0), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0>
    struct as_mono_function_impl<PolyFun(A0), true>
    {
        typedef typename PolyFun::template impl<const A0> type;
    };
    
    template<typename PolyFun , typename A0>
    struct as_mono_function_impl<PolyFun(A0), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0>
    struct as_mono_function<PolyFun(A0)>
      : as_mono_function_impl<PolyFun(A0), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1>
    struct as_mono_function_impl<PolyFun(A0 , A1), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1>
    struct as_mono_function_impl<PolyFun(A0 , A1), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1>
    struct as_mono_function<PolyFun(A0 , A1)>
      : as_mono_function_impl<PolyFun(A0 , A1), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2>
    struct as_mono_function<PolyFun(A0 , A1 , A2)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4 , A5), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4 , A5)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8), is_poly_function<PolyFun>::value>
    {};
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct poly_function_traits<PolyFun, PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9), mpl::size_t<sizeof(poly_function_t)> >
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8 , const A9> function_type;
        typedef typename function_type::result_type result_type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9), true>
    {
        typedef typename PolyFun::template impl<const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8 , const A9> type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9), false>
    {
        typedef PolyFun type;
    };
    
    template<typename PolyFun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct as_mono_function<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
      : as_mono_function_impl<PolyFun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9), is_poly_function<PolyFun>::value>
    {};

/* poly_function_traits.hpp
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
*/