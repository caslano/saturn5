
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/apply_wrap.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F

    , typename has_apply_ = typename aux::has_apply<F>::type

    >
struct apply_wrap0

    : F::template apply<  >
{
};

template< typename F >
struct apply_wrap0< F,true_ >
    : F::apply
{
};

template<
      typename F, typename T1

    >
struct apply_wrap1

    : F::template apply<T1>
{
};

template<
      typename F, typename T1, typename T2

    >
struct apply_wrap2

    : F::template apply< T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3

    >
struct apply_wrap3

    : F::template apply< T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4

    >
struct apply_wrap4

    : F::template apply< T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5

    >
struct apply_wrap5

    : F::template apply< T1,T2,T3,T4,T5 >
{
};

}}


/* apply_wrap.hpp
AC1nSlKhqrkiWQEAAFMCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjIzVVQFAAG2SCRgbZJRa8IwEMff8ymOio9dwLE9SFYYzqEwsNi6PUpMrzYsNiVJnf32S6qdbuyhpHf3u3/+uYQ5tE5wiwlhsi61Xz6x+9KmsAnJZmn4oG2U5gV5fV6+bdZzwugVYfTcRUZkBBmaI5rYygIJM9ioLgCXn56YKYm1uxCiDzxi+76EWNF4foiA1fyAyY0DKLlUrUFfoucaMKEPB14XCYlj7wpEa9T2LLwNcRw37e6fwp1PQ9zCeJPN11OIc1B6T0up8HFyf+dODryZKaXjxSrLl+l0nGWLdLXOw7pNP15owGtd40laF45USIPCadP9ygZB70HWFkUwzuiPX9bXwjGeoj97RwnJ/bVAwR0npTZgbTWMINyXlwl0GO4ww36672hk2fVtwEuHBlyFfQdU3MIOsYbIVtpFhB171kscudobGRwV0vKdCiavOYbGaCN04XebPPjSTRzAQYVe39E3UEsDBAoAAAAIAC1nSlJY4d5IgwEAAA4DAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NjI0VVQFAAG2SCRghVM7T8MwEN79K05FGV0DQgyV
*/