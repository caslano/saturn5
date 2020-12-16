/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_DETAIL_DEQUE_KEYED_VALUES_26112006_1330)
#define BOOST_FUSION_DEQUE_DETAIL_DEQUE_KEYED_VALUES_26112006_1330

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/container/deque/detail/cpp03/limits.hpp>
#include <boost/fusion/container/deque/detail/keyed_element.hpp>

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/add_reference.hpp>

#include <boost/mpl/plus.hpp>
#include <boost/mpl/int.hpp>

#define FUSION_VOID(z, n, _) void_

namespace boost { namespace fusion
{
    struct void_;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque_keyed_values.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque_keyed_values" FUSION_MAX_DEQUE_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion { namespace detail
{
    template<typename Key, typename Value, typename Rest>
    struct keyed_element;

    struct nil_keyed_element;

    template<typename N, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(FUSION_MAX_DEQUE_SIZE, typename T, void_)>
    struct deque_keyed_values_impl;

    template<typename N>
    struct deque_keyed_values_impl<N, BOOST_PP_ENUM(FUSION_MAX_DEQUE_SIZE, FUSION_VOID, _)>
    {
        typedef nil_keyed_element type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct()
        {
            return type();
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_()
        {
            return type();
        }
    };

    template<typename N, BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, typename T)>
    struct deque_keyed_values_impl
    {
        typedef mpl::int_<mpl::plus<N, mpl::int_<1> >::value> next_index;

        typedef typename deque_keyed_values_impl<
            next_index,
            BOOST_PP_ENUM_SHIFTED_PARAMS(FUSION_MAX_DEQUE_SIZE, T)>::type tail;
        typedef keyed_element<N, T0, tail> type;

#include <boost/fusion/container/deque/detail/cpp03/deque_keyed_values_call.hpp>

    };

    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(FUSION_MAX_DEQUE_SIZE, typename T, void_)>
    struct deque_keyed_values
        : deque_keyed_values_impl<mpl::int_<0>, BOOST_PP_ENUM_PARAMS(FUSION_MAX_DEQUE_SIZE, T)>
    {};

}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef FUSION_VOID

#endif

/* deque_keyed_values.hpp
j73lyTzus7rL/tLEudkgzm0sF+skTtdtLYziNNl9f6xd1Wi/EfKM42QnuL3vSvN1+07Nq6Wqft9tJ315zvLKHnSnfO36DVXVl2c+cRRJHI4HPbvQ5fbLynKnwf5LqKaPbxfL+TxgGJ8bbTQc4jTYf8XVnBx3xnGyH9w/9or1x55atl1v0e+/3UpddRIvu89lPrXbD5YMTZJ24hNxD9vPtW0/dmhkXK9EWvprrkQu27NK+1XrBvkGPn1qaibp5lu5OjarJdvC5/7JSgeCLPIk38zPST+h5OxetgZwKdfmzfa1tUWzzd+tbjs1c0ZqxnQzCzaTthW32m9/ZpbJbCYOu/NZXnV9/XmEPEdsUPKsvTB7dm1Y3V1/bbhqENc+pXx1cXl2bSAu3bXBXMO4jprXOcbl2bWhZIfza8NrNfT1c/9/2DsT+KiKM4AvEBARMEC4QiABIoYbkgAREMOl4TCEOyo2CTlIIMeaA4IiBEVEjRAtIApiRBS0oBHQovVIERUUNbWoqGijoqJiGxUrVbT9v91vX2b3vb0C9vrt+/Xr3yxzfDPzzbxj5pvR+r6hfL7fGxy2ObKFse4eJu26tWZ7CdNUfvTxW2OMfoU7TPJ7hHCD1pnlpzWXv/k5jymR55m3V1KFWX7UvB9tFr/F/Ziy4jxjm/0O/aym5aTZfKhX2zoqSf/EecZ6fIz0K9cp51n52V47pb3UfGa0NOZTRbhaNR8/20nOx3JaF7a/pXk7RaxX8vGzfZKMfUovV1grY/s8rtmhml8D2mVFK2N9PUG6qUq605P8G/N2m7TLCZN8ntTa3ykf/8a73SbtMqe1ebvUOuXj31hXVum+Xfa0NrbL77XxyCk//8e5yPON9fUU6UbcJemqL3h+9pslJuPcWpP8ntbswCw/P/vPEpNxrmWweTuVrTHJz89+VHuf+3EuN9jYXn/Q7NCsnH70J8e970iwsR6fJf0aSb/+kcm/PrXU5DliXBtjXs8RLniDa17+9aulJs8Re9u4uS8Z8vKvbyXd5/45IqStsa2e12zSkKfv/cuR9nZJ+2JZPx6H7CPtCnvaGdE5Kco7rPe0HXVXLXXnWNc7z/bsic+cvjYUuuztPsrRnu2MOr2o3bsUnVzfzfx5h3mhAbo5+s1RE90OaPefu3XdXN87fNbrpQbo5WhHa4hRr1dJr6xeL+V50/e6OtgAnRx11by9UafXtTFA1Ul9nvKjDQ81QC+HfVWIXhfJHG4sUqPdU+5xo5d2WoMPujnv8zDXalH8ekVfJz06dTDq8SbhrG71yPLp+45DjyV23wlTPdR79/YOxnZ6i3DVTnrwXOVD3o72+XMD2sdhy1EdjfXyjjaeb3TR5yy0i+jpPCaa5P8u4VJd8z8L7fFnk/aI62Rsj6OEq3LJf3qS97wd7fHeGbTH3k7G+viQ9CybXPXRGsS7Tp7a4z2T9ojrbMy/lnBJxvyzfHn+M7aHMX91HKvpbGyPTwhXqeavPi/5oIOjXT46g3bJCDXq9Rnp1al66c8Gvut0rAE6OerqeKixrY6TXvy9Zjqdub2Irs7Ptl2MOnxJuApTHc7cZo6Z2OwJ0SFGdBiAnOCPWrsOOdEZDXuuujLKuW3m233GS1z39ygOM+Zfp93jNjvyP7NnqL/GuNdDbYtTJnqc1MZSXY+GPy9961kHvS1Kuxp1OKX1X12Hhj0b/d3HOjhtkv9pzRb0/Bv+HPRjjG/2sKKbnGEiOvSXs8ci7nPocPafeW41eeZpGW7UQ+ugqboeZ/+Z51aTe+yqcGObBKFHpa6H/888jWN9s8fmEcY6aEbcWj3vs/d8s9NkbFplkn9z8o+odOR/9p5vdprUfVB3Y9231Gw=
*/