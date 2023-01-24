
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
QUp+Gn5QWGRw/9vHb9PIMzIiecaq7YIfjssZJxX9cWfBpZzW7tcvlqLnPObspxlg4C4n2sYm8Z3UUYzIk4SC9claAkE6nXxN9sP6khMRpxyRbI3VsNKQhMibbElmJCokdCNnYyJvMge72SKEHcdmBGGQtsWTcbUu84wte6LzbFU/HqCksuSYPb3ef02bJabZvYPbvaGriMMIB5bM2uIQwEXMJi2ZNgMmk3FGgp+85fz8+vOTl+T8Rrs3GrRNP7EOqK7sxWSiFS0lTibRTbNf0GMSQg0qDoHOg5bY+5eBKXrYOjvexb2sVl5ubNGZl832KW0hb6Ia+9vUYYrYG07X2qfPAWA6WfGP3pRyQbwcHQGTp+fteJ8/KYhv3WykWhOQ8kQ7NfHVy8QyhbtFISVaTFHHODocSkHWm+Bek+PEwj/nGOvuV4LXm++59PWoWyrjq+xqeJ9HUMy+kkXQyhfI4p93FlCi22GFbRHKQcOX8Cdq32ewiV6aF3Jjc2nMi4ppXwhcnk4yPKam+mtB/DrbJm9gJ7vFnX0MZr53qHJDce17hFIuuyXNJTX0EI7OzsbbGkOmrFdjGeWN/nhribuncsIYoKr1spqqUDV4JJgjWBLHJ6kG+SUY+vqGmHlTCLcepx7XBxdGaIV38NB8TQGOg8CBEawTZVAa4Bj8wY9bh2MjbkaxGY0TjauO0xJcEnyHC3gc2UeXoo93iUsQ
*/