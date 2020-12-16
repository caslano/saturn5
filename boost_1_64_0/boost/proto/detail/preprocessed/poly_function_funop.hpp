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
mTBVf5VgzWt7fs+ahpUSdrrpWn+eA8xS2MGICs85V2AGYb+MG3uZZwSzFhYe+akl8xpmI+zUtdw+yj7DSghrHHebvc4Kp+wnbPqc1nxnCITJdVdHrixUFqytmzsmrejfwcOchZnHnaXFadf0jdoSy5yHBQlb8s2E+8vU1uXkuH1mrGH+wobMm8Lvv3yYPIf7d1xfsEfCSgureXhhG2Vmceh1worvGFORMxxmKyxs8LspnDmwssKS2k+voCwcFvB/qwjzHlGrEucKzEOY36ZFyeyRME9ht1LuZrNHwvyFjcm7U4a5BKsi7Oyj8le4v1HoL8Lur1hfhX0eZhBm2bt0FHMCVlFY1Ihi25V1gVkJu2MTupe9DhYs7Ltz/q2VpcG8hG1uMbkWaxpWQ1hSXsUZzHmYrbCSrj+MYs5re6h/dxLPz+pn5K6wnwra2nJ/MG9hkWNPH1QWASshzHze2jHcO8xM2NzeO+uzHrR1P1otsWPvgcn9ucZtNLDPa+tWmSzjO3SGts7abyZjlgdzFebicJ+xfg+TufR32sIE5vVo/DsBYeUG7vRQFgaTeXaz1YlcZYNh8txfr9vFGouDybh4VQ7gHuJh9sLWN74aypyHyTMyyV7wlb0AJuMyJGV60b+9g5UTtnXAm0D2T5i5sE2Zy4M44zQ7ML9ZX844zeKPDApnPGGWcu8nG/I5TeLRr4WV/6XQRJkBZhD2a/WJ9jwHWNp/LfS/5un2UxL3DusqrEbVDU2U2Y4xNqf2FV+yv2jWcsC0b8pyYL2FNe71KU5ZrbHGfSK+sDvfyyNhPcS6xE67M/icsO/EurYL+s1k3cJknuU+W9Cee8dfZ+4jrtluYd4XzgdYjLAT2etMeX6wLsIcbo4/piwUb/37hY2Z7F+dfQJWWe6vVMEn9vIJxr2uSYvPfIfuAHMRtqzVefaJwTBVDwEwV5tdtDhYKWF97z2qrWwazFzYgqQnAawHmL2wYw8XMl/SYabC7q6YVfS7etqz3LRxOMTZodn+Hw9xFu/Urvl2TKNq7MkwO2ENrAqzlGVr6zp0P7CfeQZzExbU6ekz5gSstLD0UNdLPCOYhbDlPhVKcI5NxLwV1shi4lxlfjAZz/PTfq7LPg/zktfMaB/JPg+zFPbeprsTzx3mLiztQKfRrDFYTWG7jjRZyXPQrnn651NveQ4weba/ps8q+hvXMBnPsIl9+N1/eiJ/RvZfm/+8e1fOuEnGZ/stf2pL9gmYQeZE71asMQ+YvN/g7da/KPOGlRRWt9D2MeMJk2fULSag6OcaMHnuPtVu810jUrvfudRfHRhrmK2wEcVrc3ZEa+sW2qT+xpkKkzV2389uOmcOrLiwW1X7NlQ2HlZCWDH3Am9libB6sh7OhzMnjsNshJVYFM13/VyY9X/M+3/2u9nQWpxHMDOxbtK13ibK8rWYRRy8+qMyE0xsR2Huv5oOUuYIk/kZ57FgsbIgmJvMswZXwpjzMG9hr4uVdGE/g8laqbEm6BT7EswgLHK6b9G/64LJnM8bNp+xTofJXHJa+OQ860GzQzOH3Gfv0WzmluJ5PAeYs7zmD3vXK8uDOQhbVDs4h/Md5iLjcipmHOtosnE8a/ZO2sL+ApPxbH2qc9HMgcmaHlTC/hrzGlZGWOoxJ+5hMMxPmOmy+BrKkmFyf9t3xCcoy4DJHHx805e9Z692v6D2p/uzJ8NchU0235XKngyzkHl2x6y3stcw2VsNP14s6tea+eZfSmS/nmJcmx8qXPRh7sKchCVmvH3F/qLZQ7NtRf9mFiZz92tAx+/ZJ2AyB63c/pXFWMNkD1nlN20BeznMRcaz7qMV7AWw0sIu5434zJyHqXlUAdbQbHI=
*/