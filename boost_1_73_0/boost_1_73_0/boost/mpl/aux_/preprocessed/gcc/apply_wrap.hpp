
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
FSE7MpO0tidFe03mBySmtTMxBLd6GmSk3ekpkrZvD0tiI0M2DwT6+4jNjNh6cZBb5tIyWxnz9GCmvxd6mkHP9kKzDWVH0VnmWcZsH8j0D4C2M2jnxYE+h+xkyPOXRrlKRNWi7KmbpBT1iNrEQcZbXWSUKHNS5g4TIWooAGr4ubYcM9Mqip7c/BlbLuxzLszwVh9C/tiu7R7qrIRh4P51yuCaDsFrgud1T8+6jbbWQKiKmu31DhauCxCqO5QTRlOsGmrV5KPayS11wEbEZJ3eE2U6bWz0Wd9ENVZYkv4DzISMWaAxkqWrYqgHNzi9txvTO4yxE9+qtm2Fstligpr7SiidFhiSsLdZMYzELPG54IXptP6rtloOy4QEOEjQ2hFMCwp2LGIgqZjihz5In/NqgD+kI4GnLf1rSmK5HgpmT9st4Na0t+2EzJE+GSlU5FA4yHHZHtNY0ldUsvAmZf8PUvZVlezrCtnX1rGvLGNfS8W+idjNI/9Nw75p2DcNe5CGhf9CxL5J2DcJ+29IWB6ykVN2hkI4fddeG/fdxTWycwQfYqavd81dej8wX9DA3gpfOHploXn2Ffpa+dp7Z3upPaMsDTGbGB+uNUXD/CJeJyK/yAepRErGFAmuRRzB1VMSs4Ap9NaX9vq+W7EJ
*/