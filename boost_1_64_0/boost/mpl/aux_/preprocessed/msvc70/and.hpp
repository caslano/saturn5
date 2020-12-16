
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/and.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {
template< bool C_ > struct and_impl
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : false_
    {
    };
};

template<> struct and_impl<true>
{
    template<
          typename T1, typename T2, typename T3, typename T4
        >
    struct result_
        : and_impl<
              BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
            >::template result_< T2,T3,T4,true_ >
    {
    };

    template<> struct result_< true_,true_,true_,true_ >
        : true_
    {
    };
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename T3 = true_, typename T4 = true_, typename T5 = true_
    >
struct and_

    : aux::and_impl<
          BOOST_MPL_AUX_NESTED_TYPE_WKND(T1)::value
        >::template result_< T2,T3,T4,T5 >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , and_
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC2(
      2
    , 5
    , and_
    )

}}

/* and.hpp
iX0c67FLXgsdxBlXvcafkqE13g51vIQJ40cocVURlTaWJNVzFks87OcaHg3k+D3l3sQuobrvNYMpS0fKstdcFvN9Ku/Tzovz8XScr0Hy1Z6cuvNUrp/E1syXUc4tK+oxRCGHbHmvdn59oeQbIvm2IuxU7sXs81WmLdaZr+U+LIQ00lGd1yGHx0jwsM2L6nHhHt5SryOKHdWrtv0gUPL0J5RTtmT742P6aN15qu9jy73s6+4B0s6TtLUfTPfqb5jUnzq/aG/H9Vfp4Sg/9+pw9WJ1HWrzXe1tX4cPUr4Sh8fpfj16neL4uMo8bds13b82SjSfOe2832In+fpJvnZfUi7ka/nc+Sxx+LmreZ7rKfbXjpfSFuMwb+XSqTvvmnYY+2tn1qmOj7XKw0F+1JQrbWiWOk5b4vza2X+q/bVTEUG+Do+TS8eFfEnf+kwco499PT4coVSmKn03689XPnvqfEp9nPy7oM7HzXrro/nMafM74WNfb7uV72V1fvWor2KZt3+GpHs64RHSTa5Ol/WCZfEAF9K11FcLqS/L3OtPZE1Xy1oXAQTaTjXfy77N7Muxl3SKteWQ72bXy/KoG2WxXKObHZTlSdIpU5VF+x3nenker0d5opvbl+dp0qmyK498btw4V/vcKI/lmtkq5Wkr5WlD2E86ftX9P6yp7P4146suh6zxy7q7mmskzNc+3+d4X7w13/pdIyGO89acg1IHeR/gfXnWvOt/TQxzIf+wFvb5v8j7Sq351/8a+L2z8/yP87qiAdvCnbV5jz9N2d+y0nf5jE4fxn23u8+uVtkjZzlr23bWpn7y27zdbdt23EburI3fWVu4s7b/f08beaa5jXzpiZmTHmr1Y0Rct637X0pd/3PjtJGHKcGzZs5pvId2Tuco9VzXWuJFquIZJV6Ig3g9VPGOejhPr5t6rqukF1hHenm15BumngNcS77t1XNiNfk6T6+slnoZrornV0u8Aap4e2s5jkT1HOVajiNeHU9zHM7TM3g5z7e1NR7By3m+werrwEvyrSO9ZIl3Rh3xijXxnF8HZbXEC1PXiyqe83qRf7uxbR3li9fGc36dauI5L1+ps3hSPqWNIO1P9u4FLopqD+D4KlJ584FeEFI0fL8VTVOLFJ/hK1GxME0eLioqsPJQ1DIqUyst6pqPfFFpmllpLy0ttezGNTUyLLtZkVlhUWFZeUPz/mb3v8vM7C7sAmrdO/Pp9HWGeZxz5szszJwzZx7ztdYz3I7rCfsIhYRaq3xNoYQoQiYhZ5Wv13URuSzjqj5ixVt/rjqJ4vY+l6xeoqz3s3e89eeonzj6lvfvaUd38DGFYtFbbKcv0/b9dessChZf+HqLYxwrptW+phBCOCGWkEVYT8glFBH81viauhGiCZmE1YQdhDxCEeGKtbzHTRhGsBAWE7YQ8tYadR7GYAzGYAzGYAzGcOGHi1b/bzZXuv5fqZeOUNVLR0gb/GB5HtiQkKc8Cz1XX1UfYP/sXxotZz1/Hiht/j1+J1/dpriN1JfnSVveA4TDrZiXeOm+vWeJmzgtRloHlNsOWukHvdMf9aUfdImr6nt57r67J/1qd9H3S8+0ruo204GtJM2qfvglbpr0bZX0dZJ870DIZ9msP9TpsyYtLiN9irIKr963kP7LJe/V/dJr69HCpe58j+TzLsKRVow7x8PSQ/kwnkf9lfvWSz7vlMfS/7NTv/yafMlkP1iVbwum40cst/W8i/jwxUVblMr/FqUSpwbV9P3fS/njS4XsR4/LqX3/q/pa0HyfQfpokD7wnb9fEKL//oF8v6JrPVtclL4n1N9y6GSbXma+FUm+jZbyNJJwlG1kV1PX62Uka0uU5+U=
*/