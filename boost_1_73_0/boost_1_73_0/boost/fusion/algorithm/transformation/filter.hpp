/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_02122005_1839)
#define FUSION_FILTER_02122005_1839

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct filter
        {
            typedef filter_view<Sequence, is_same<mpl::_, T> > type;
        };
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::filter<Sequence const, T>::type
    filter(Sequence const& seq)
    {
        return filter_view<const Sequence, is_same<mpl::_, T> >(seq);
    }
}}

#endif


/* filter.hpp
dbBic8Eldh2yp5kgGUuUKjbgdh5fB7S+xJpM7sN7umCNzwz8t0JWb62M7yM1iTnWeBHchve0JnpcjOarGL44oQrDyQT47KmNlIna7ErKTe3mgoK0dEprUqJWcHahVs8pzXru7oQN1PcdL3pBYWdE1LJ+pyVTW9CiXed7zl7JpXhkmW5x4EiSnKWKMOg1YXEyG2vxKGYYZRY32DomY//r2La28UMxIE86PU3d6taJthr0rzT9auQatJvjpv6eGxy7GqjvucFJrsFo1LWgUIPTsgYMhRqc5Rr4vbaOVcCyKO7Pwd7MwuvNbbprmjRkSYyZCXZBnh0atYBo8mKScleLRFsy8JPpnU8jD/UBG5fZSvsbRjM8NSRaWzGMkiv/jS2RpN+wZ4VKtcBfCIFgTLE+tnwggdvqY4yR6bTyh1p5y3kYJDqC3msSF25MnSLWKd0M7gHw6AkxsEyLmKXVVCU5IIIFsqcDhlkpiRQWiiMX/QbrrBIQQHqzXIVLIpmzA1heqGc2cBG7oEzjlmJoHiTrA6/HA9/zP/tD3Ff3CK8mGfbAYvzFMY8duDaJVowLBxbch79JGKHz3IBtsI8M2IHR1WAgfPdg2B/3W/2u4+jIxU9tOr3OOMN45I4QQWR/ju5Ff3jZzDTNHiWfLnI4
*/