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