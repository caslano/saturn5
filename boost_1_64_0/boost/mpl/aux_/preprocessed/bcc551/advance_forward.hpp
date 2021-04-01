
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
QxLR5Sgisr632wTw4MZzOktWFya1geSpOn+w5bRoHZQKf1TyprWumKrlF3ODUajG1174Byzb/oBDe8vR5GRY3frmyNaZbQVjMQFwln5Xb7wgKZf+DGmey1F9Wi5LdonNNpVjukN35xWfooGQ75WCOrRi+TopDXsIJQHGj9PZB2wKxwgYagJfOYiCI25kdJYlW7vmXmKaHfck1eUJ2WIJMeajHpgRs7iGbS9Qc3hX+cO9TVCSYMKbC5DRu56UjkWjhYmt1bmbJWUF/YAuAnIsc3gCfe55VW9/R8EsWuDXWgIHl9hL+u/GMnv0qCGPTabi/6P9BUu2hjoH9Xj9Bpcczfa/JXGHFjurKEScMi7lbKe9nD98sMomhj+YOboU+ndz0ePhn/u+6uE9bCaZgOMN5WiV4x9RMUW8lcLHkrY9N8rLbFEF4Ht8FBPTIp5UdXWeDhInFBcXFSK2TipvUrT5GuCF5rXj6t6x/QDUCkqFnW6VW5kj89weZSUkiNlOue2ySV9ipmpl4UgCvn5HSCx1zAzFdLfBiE9I/1Emcli/d8Wsq9yl1yUFvaUZRQ==
*/