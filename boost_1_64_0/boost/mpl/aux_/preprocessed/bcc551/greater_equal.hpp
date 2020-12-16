
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
9lwgZ5Qb68YhAUlGBbwExC/p1QM/f8X7g3catf+x7wMUVTZiiATCNEZSMwq19zx5SMKRD7pIKJKAnefQ1xOGvh4b3YXD6TGokLu0KKvOTNaRDYUWOcXyWKgWrQnkvYO176B6b6FGVNENvZ0+EBzkuH4TTLkSeHI8WPJBdAJdhyarwCkSjlf5fn6UX+OKKCeIaCkSxbfoPvgFqWhpaO1msheyhYPyMnzFUugUbWr2COBKNtYPwxUxD95CUZ+jpiGJzkD9zPSd+7WooRv/qWOkPXKJgcjcR+Mcz8I5Pm+2sNZY19BvVdTXWlX/+rzw/pci8+2PDORtqK4NSHEvQ5GsYZ+DJVxkT8DK62ovwTt4BD1QW/fQ8zoSDoIB3fWyMQL+wRLkcoeNCfxtJDcb+EF+mT/lpZDA7RcX4ZCUkHXlS7I7PI8IszYUeFfc0zvmR2Y78NARyLiWwH05DE8r3f7Q3oBuvMtIbUrBGz7jXHSeIOmt676ESvgaEpPanud19UZ673gfefCfLxT1ef9AMoJMJUvIl8gtf0Gisxaa9KB6WX2qlkJvXVOs3BM4qnWhSruz19gMJuBWdEUHwztwRDZj7SZZgbpaVCEYwtUt8NwT7P+N3Qp+ivlcryDZpf2X5AwMshx2QLRxy6yAnsj1yHiKKTE+H2tGBkEf7Eelvob8aRPNhb5/blQP1LnoYv7a3tb+X3VrZE0EFv9q/QL1MR09fS58hUAxwTX8OVmDdGuIGk37QDfPMLrzGbyf9ZI9yz0AH6OYEudr1BL0Lfo9+m9+ZWXR3zwYXusm8MEyekd9HhjhJSj1Cti/041P4evXAk9Ixk5KN3+E+4i/69vn/X8CU65iDOdzRZKUqAwVAxoqsZi/Lp3JJPUntR9UfC6bpU3XZyH3eAtdfO9DiUWKeqK/GCf2wPOZKK9aE523wHsqoaOmCyrG1+hG/QSM6ixqRTG/7ieQ4VjjUDoepy5Mi9SitHJaJZy/GK2OFot6qGkCJzAUzlMX/V09C6rtV7gM9Y0geUT+Zo62CNAi2LnrKCnFfL1VFoxpDxRaovo6dn8krUENqrJB8JS2sNssCqf4fWTPZY0V6JUpBLxKEbPQXfhY2mAASe5S4Gn+fcXAC/kS3zNTfUYVFsxCWRiLRLdPOZYLtHzGJKrTFNSm/fAsAtrZAgfLNg4YS5FqTkSXw1JrF7pZA5hUTInEsEtuMy+aRxwlu1h+LwypTBWtilYOleas/aNzybnqJEKBbUQHXXlv1F9ydOxFDGXpn1hBbRTY1h7gUaz+kk7gi4yFN61g5wj+zBxub4VaXRb4naPFFIEhBr0Qu9lu7Ym+me/i40RD+TrckcUyE/06q9D/PBb9ETuhdz+xTzqPAvvzQjFlOobipCppCHfjM+QoCeDxj5G+LKThbBcrjie9Cxd9rJ6JDpCzeh/k9t8YTfgkvha4ECE0YH8t4HyYWcpsAIT6Azoiv4QTOxu7uSo6RIfghK0EqncHptdEh3tHpKZJ4MEfonvgsVsMGLA6wDLz8u+jEqmHTufv0JcTDxybAkRcolZGDWPUAXPoRFPoUrobPSmPaTqc0Kvo1GgPZ+A8EoVAV8F5P5WviLlpxvvyYTgj6XwZ7nMrfILbvCk40hR4Rp3lc/Mcqn203cweY59GMlQalXa+t8VPh8L8/TQb53k5GPhgVItR6L46Bd3yEV+DhOJ3GYTO5U7mIszkdbjNJnyXhcj0n6JTohee9isg3i3o9zB/PX6DV9de9IDC2AleVl9OkbPkAzji/YCZJ1ERm1kd0K2wF5o2Dj3WX9gKCfNxyzNaGrONBcZPqLqxqLhv8lQ4rMd4Hcz3DPTCX0f/URv4fkrj/Os=
*/