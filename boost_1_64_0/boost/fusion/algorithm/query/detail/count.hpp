/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_COUNT_09162005_0158)
#define FUSION_COUNT_09162005_0158

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/fusion/support/detail/access.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion { namespace detail
{ 
    template <bool is_convertible>
    struct compare_convertible;

    // T1 is convertible to T2 or vice versa
    template <>
    struct compare_convertible<true>
    {
        template <typename T1, typename T2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(T1 const& x, T2 const& y)
        {
            return x == y;
        }
    };

    // T1 is NOT convertible to T2 NOR vice versa
    template <>
    struct compare_convertible<false>
    {
        template <typename T1, typename T2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(T1 const&, T2 const&)
        {
            return false;
        }
    };

    template <typename T1>
    struct count_compare
    {
        typedef typename detail::call_param<T1>::type param;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        count_compare(param in_x)
            : x(in_x) {}

        template <typename T2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        bool
        operator()(T2 const& y) const
        {
            return
                compare_convertible<
                    mpl::or_<
                        is_convertible<T1, T2>
                      , is_convertible<T2, T1> 
                    >::value
                >::call(x, y);
        }

        param x;
    };
}}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif


/* count.hpp
dwpbIT9+nlWq/nSVNG6YWNpLusEjf8m3uKGVxdw1kSY1L7gQ8wfgSJAtvGnTPTCNOMMbrA+xf1ep3AWt2pI+THuksSLHHugOE4+2EqpoQ2sFjAvRy2KczduJWLB3CeQHW6V3jpfacOXIGQx3sW5zJTkJmmXTwpPMN/YW1QYNZOGzGW/pRzDJAhB4afHrC0XRFy6yfjlaNWVVzCJKX3ZJh8LZdAse0w46p/Ykp8clqqFchA7YuPzu3PacitSXJHI8qI5dALFYPpzDjzTQDd2TXA2JJ+PPrL0VvkqLqcvHHw/9CQ0XbH9+7Uf51QXmcRg7h2tZYO6ihU4k0yuzU4/T6RV/M2L96OvEZJEyIx/ueu0edtfP/3ksX05uAaO3a4XuaTZc3q8Mpiyfe6iejAyaxbFylAwZjImmdIXL+PZ2Gjz0KV759zPI4eWcLoT39JE3LLZCWaq/cAtm+V2371OIBs1Nj+skFbTWGTnBmi/clwv/kXd7duYVkMTmLPMTb2aaYdCcvMYF0drdMA4QYg4etPPeknO+3H2zfhwHrg0AumHM+mWJC9I0CXTcuQ==
*/