    ///////////////////////////////////////////////////////////////////////////////
    // poly_function_funop.hpp
    // Contains overloads of poly_function\<\>::operator()
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename This , typename A0>
    struct result<This(A0)>
      : Derived::template impl<
            typename normalize_arg<A0 >::type
        >
    {
        typedef typename result::result_type type;
    };
    template<typename A0>
    typename result<
        Derived const(
            A0 const &
        )
    >::type
    operator ()(A0 const &a0) const
    {
        result<
            Derived const(
                A0 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0));
    }
    template<typename This , typename A0 , typename A1>
    struct result<This(A0 , A1)>
      : Derived::template impl<
            typename normalize_arg<A0 >::type , typename normalize_arg<A1 >::type
        >
    {
        typedef typename result::result_type type;
    };
    template<typename A0 , typename A1>
    typename result<
        Derived const(
            A0 const & , A1 const &
        )
    >::type
    operator ()(A0 const &a0 , A1 const &a1) const
    {
        result<
            Derived const(
                A0 const & , A1 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0) , static_cast<typename normalize_arg<A1 const &> ::reference>(a1));
    }
    template<typename This , typename A0 , typename A1 , typename A2>
    struct result<This(A0 , A1 , A2)>
      : Derived::template impl<
            typename normalize_arg<A0 >::type , typename normalize_arg<A1 >::type , typename normalize_arg<A2 >::type
        >
    {
        typedef typename result::result_type type;
    };
    template<typename A0 , typename A1 , typename A2>
    typename result<
        Derived const(
            A0 const & , A1 const & , A2 const &
        )
    >::type
    operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
    {
        result<
            Derived const(
                A0 const & , A1 const & , A2 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0) , static_cast<typename normalize_arg<A1 const &> ::reference>(a1) , static_cast<typename normalize_arg<A2 const &> ::reference>(a2));
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3>
    struct result<This(A0 , A1 , A2 , A3)>
      : Derived::template impl<
            typename normalize_arg<A0 >::type , typename normalize_arg<A1 >::type , typename normalize_arg<A2 >::type , typename normalize_arg<A3 >::type
        >
    {
        typedef typename result::result_type type;
    };
    template<typename A0 , typename A1 , typename A2 , typename A3>
    typename result<
        Derived const(
            A0 const & , A1 const & , A2 const & , A3 const &
        )
    >::type
    operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
    {
        result<
            Derived const(
                A0 const & , A1 const & , A2 const & , A3 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0) , static_cast<typename normalize_arg<A1 const &> ::reference>(a1) , static_cast<typename normalize_arg<A2 const &> ::reference>(a2) , static_cast<typename normalize_arg<A3 const &> ::reference>(a3));
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct result<This(A0 , A1 , A2 , A3 , A4)>
      : Derived::template impl<
            typename normalize_arg<A0 >::type , typename normalize_arg<A1 >::type , typename normalize_arg<A2 >::type , typename normalize_arg<A3 >::type , typename normalize_arg<A4 >::type
        >
    {
        typedef typename result::result_type type;
    };
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    typename result<
        Derived const(
            A0 const & , A1 const & , A2 const & , A3 const & , A4 const &
        )
    >::type
    operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
    {
        result<
            Derived const(
                A0 const & , A1 const & , A2 const & , A3 const & , A4 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0) , static_cast<typename normalize_arg<A1 const &> ::reference>(a1) , static_cast<typename normalize_arg<A2 const &> ::reference>(a2) , static_cast<typename normalize_arg<A3 const &> ::reference>(a3) , static_cast<typename normalize_arg<A4 const &> ::reference>(a4));
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5)>
      : Derived::template impl<
            typename normalize_arg<A0 >::type , typename normalize_arg<A1 >::type , typename normalize_arg<A2 >::type , typename normalize_arg<A3 >::type , typename normalize_arg<A4 >::type , typename normalize_arg<A5 >::type
        >
    {
        typedef typename result::result_type type;
    };
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    typename result<
        Derived const(
            A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const &
        )
    >::type
    operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
    {
        result<
            Derived const(
                A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0) , static_cast<typename normalize_arg<A1 const &> ::reference>(a1) , static_cast<typename normalize_arg<A2 const &> ::reference>(a2) , static_cast<typename normalize_arg<A3 const &> ::reference>(a3) , static_cast<typename normalize_arg<A4 const &> ::reference>(a4) , static_cast<typename normalize_arg<A5 const &> ::reference>(a5));
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
      : Derived::template impl<
            typename normalize_arg<A0 >::type , typename normalize_arg<A1 >::type , typename normalize_arg<A2 >::type , typename normalize_arg<A3 >::type , typename normalize_arg<A4 >::type , typename normalize_arg<A5 >::type , typename normalize_arg<A6 >::type
        >
    {
        typedef typename result::result_type type;
    };
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    typename result<
        Derived const(
            A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const & , A6 const &
        )
    >::type
    operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
    {
        result<
            Derived const(
                A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const & , A6 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0) , static_cast<typename normalize_arg<A1 const &> ::reference>(a1) , static_cast<typename normalize_arg<A2 const &> ::reference>(a2) , static_cast<typename normalize_arg<A3 const &> ::reference>(a3) , static_cast<typename normalize_arg<A4 const &> ::reference>(a4) , static_cast<typename normalize_arg<A5 const &> ::reference>(a5) , static_cast<typename normalize_arg<A6 const &> ::reference>(a6));
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
      : Derived::template impl<
            typename normalize_arg<A0 >::type , typename normalize_arg<A1 >::type , typename normalize_arg<A2 >::type , typename normalize_arg<A3 >::type , typename normalize_arg<A4 >::type , typename normalize_arg<A5 >::type , typename normalize_arg<A6 >::type , typename normalize_arg<A7 >::type
        >
    {
        typedef typename result::result_type type;
    };
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    typename result<
        Derived const(
            A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const & , A6 const & , A7 const &
        )
    >::type
    operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
    {
        result<
            Derived const(
                A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const & , A6 const & , A7 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0) , static_cast<typename normalize_arg<A1 const &> ::reference>(a1) , static_cast<typename normalize_arg<A2 const &> ::reference>(a2) , static_cast<typename normalize_arg<A3 const &> ::reference>(a3) , static_cast<typename normalize_arg<A4 const &> ::reference>(a4) , static_cast<typename normalize_arg<A5 const &> ::reference>(a5) , static_cast<typename normalize_arg<A6 const &> ::reference>(a6) , static_cast<typename normalize_arg<A7 const &> ::reference>(a7));
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
      : Derived::template impl<
            typename normalize_arg<A0 >::type , typename normalize_arg<A1 >::type , typename normalize_arg<A2 >::type , typename normalize_arg<A3 >::type , typename normalize_arg<A4 >::type , typename normalize_arg<A5 >::type , typename normalize_arg<A6 >::type , typename normalize_arg<A7 >::type , typename normalize_arg<A8 >::type
        >
    {
        typedef typename result::result_type type;
    };
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    typename result<
        Derived const(
            A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const & , A6 const & , A7 const & , A8 const &
        )
    >::type
    operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
    {
        result<
            Derived const(
                A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const & , A6 const & , A7 const & , A8 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0) , static_cast<typename normalize_arg<A1 const &> ::reference>(a1) , static_cast<typename normalize_arg<A2 const &> ::reference>(a2) , static_cast<typename normalize_arg<A3 const &> ::reference>(a3) , static_cast<typename normalize_arg<A4 const &> ::reference>(a4) , static_cast<typename normalize_arg<A5 const &> ::reference>(a5) , static_cast<typename normalize_arg<A6 const &> ::reference>(a6) , static_cast<typename normalize_arg<A7 const &> ::reference>(a7) , static_cast<typename normalize_arg<A8 const &> ::reference>(a8));
    }
    template<typename This , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
      : Derived::template impl<
            typename normalize_arg<A0 >::type , typename normalize_arg<A1 >::type , typename normalize_arg<A2 >::type , typename normalize_arg<A3 >::type , typename normalize_arg<A4 >::type , typename normalize_arg<A5 >::type , typename normalize_arg<A6 >::type , typename normalize_arg<A7 >::type , typename normalize_arg<A8 >::type , typename normalize_arg<A9 >::type
        >
    {
        typedef typename result::result_type type;
    };
    template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    typename result<
        Derived const(
            A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const & , A6 const & , A7 const & , A8 const & , A9 const &
        )
    >::type
    operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8 , A9 const &a9) const
    {
        result<
            Derived const(
                A0 const & , A1 const & , A2 const & , A3 const & , A4 const & , A5 const & , A6 const & , A7 const & , A8 const & , A9 const &
            )
        > impl;
        return impl(static_cast<typename normalize_arg<A0 const &> ::reference>(a0) , static_cast<typename normalize_arg<A1 const &> ::reference>(a1) , static_cast<typename normalize_arg<A2 const &> ::reference>(a2) , static_cast<typename normalize_arg<A3 const &> ::reference>(a3) , static_cast<typename normalize_arg<A4 const &> ::reference>(a4) , static_cast<typename normalize_arg<A5 const &> ::reference>(a5) , static_cast<typename normalize_arg<A6 const &> ::reference>(a6) , static_cast<typename normalize_arg<A7 const &> ::reference>(a7) , static_cast<typename normalize_arg<A8 const &> ::reference>(a8) , static_cast<typename normalize_arg<A9 const &> ::reference>(a9));
    }

/* poly_function_funop.hpp
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
*/