
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
I5tv04ni1ycmf/hS/LdJ2W1ouY3Z29f+Q7TceLyjJL6huMbAZ7IH3d5xC1N+3PN9WfP3Y0s7GYotGCdfnNr3ykydDwf+VF7dd3wiy+owaJh/8nwraj7sti/7W3bEzo+1h8rH6wbEfSsPJ1ev1bHA83jyUEEKOzVdPE7i37DQwUayO/c0sVDviq2u2MDDsVVB5QntYjk9z8PqG7VGHf9QyDJkp21o2JwextvDT7xJvFf/FKbFEKFVqzv4cfTINVmrU60X3XkecUKtXRPY+imJTVPn+FqnduMVvSnJIlYsdCpo7mRHtqTrkpRW1fP5D2O/ggblG1C1jimDU3KgXEA30e/YDZwsJ/RWMyfVdltk610Gf5R38Smn3uV6+ZJ1cfOmgiqIrwuNpti6aXfk/kBR7/7rNgAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA+P8BZWLDe1IDa71ngRQhIYMoPAcWlCEhbtHoIWlFHLrNSN5D51wDVnK5IOVFaEMPBZSmrOejiaXY2ZDeZ0JJkYiALzElnxEjyQrn4YngTZKRMlbkXzJE2HRcOR+W2BwbJ/bK
*/