/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07162005_0115)
#define FUSION_BEGIN_IMPL_07162005_0115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<joint_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::first_type first_type;
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::concat_type concat_type;
                typedef typename Sequence::category category;
                typedef result_of::equal_to<first_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, first_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s, mpl::true_)
                {
                    return s.concat();
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s, mpl::false_)
                {
                    return type(s.first(), s.concat());
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return call(s, equal_to());
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
Wib/Z5M6cLGiyhVR8z4a6JcxL1q8Lhi75RdB29bjS6mVLrCuYtOKQqxim1TjbA1k5bCO9upyretytRvQtN/YaRcd3tW2+etpm4dBucw7tq3gT30iPRyDg2uNv6Xl6Gp5q0ECdbddqGm5prWF4Rj/rjmjauiq42v/0RmkT9VlfCPvC+abhOO5HsnkcPzJYOMe819iH1Fj/z4dOxlrpWuDEIaW6MnWVqk74cLr7huif5+pvusD8D9fHm8HveEYMDj3u47xU2cJTkLJ9ocR3FjXIzrcGe/dmMhcoNiLA1iA9rYv7Ly6ut86xvj6Du7CzpZp8w00E9FgG770GofvdTl4WFwdyILn4A5ez8r39/b6O3YS6KxZn+jg0PgjrMLN6nLs6nYVo5q0uxf1ddAFgPZHIBj76Zj9VvQgrmu7m2Ac3sPo/Ud/pfsbBjJWYBkC28DNlPo+/hZg2K9rTN0lFqFlvB/ot18F31AiQ+0OALk3qsb7hwADsxfVlTCfkd3J6IiEBDs5sUn8hTBYKj+Ye9Vj74Isi1j7z9Ry5MGCcO70fjKeVSkKY42NjM/qsmRFWVwspbcqZGhHL+JM3qbe7rj+ABnXCDbYT2laZYRwHJ8Enb4ye3D7451Hg5v+Tcdz41kXAyJ3rvTN5xuxk3z/SrCtjFHmeA5xB49P69c0r7Hr1bDsrlcq3K2DCDu4Dx5xcUOIuT3Y3R8hEHXzdjXvw0zNtBWnIoBzbOVw9g445+7y0U63PZHsboLZBhzYtrmj/xmnv11vNfM4b5kHUReMe5DhJ4TOvXdn22LcdeFHr7bmtjhxce34MSxTc5KDxUKb+gVXpkFUkkfdvl5yrvc36roe+89zL9vG34Ofa7N3KiferQXcf877Lew/t/OTTX/8d3V/tNPHd0Xs5mBjVF8AuyMGQ1ngurgzQzDbvSsjXFOzPW3HqkAnVeCr7j4Exf6v9efRgHv6Q/5DWQHz6P9YVsBML6uxYW+DNha5F4ddWXrcvIIpYphnwWRDT6Yq/8b/jOs8GTBvn4oxU13ju7csVl/UqdfCIO/gNrL+C3+p5g8bN3a6sMVeD1loozW4Co17VYDbrm3AurZ6/fF0hkqnts7/Z7lm7gc4VVVmVcLXypPS94IM8pzo+mj2v8mzPv826/4av69/bUBfDzReVxrH+uXNSV2AjFDEQR3ueey/kVff44Cfq7MHy8P1lcnX1GRU7bB3ITLYNf0aQ/X9gHXPsNqTAQkVzcTMgilLf0P/e19P/kYai74g8LM9e7DMZ9d5D7fdOuNqFm9w6uWjvue6MdhFDwi8E2D2Wc53yypd7+HBJhwD9//zXcJoPLY2LT9j59iZbuahnK/+t3JG672dlhioi/V7hnG2N3u4utg9o3nTpzA4x2YYTGLf1mUzd4dM4J3u3u4uHCxBOzJ2+oJDqNM81LvEmQsKLM6KhAOBBI5x8Hvwpl3TB7pkjrSNaqu7uw3wzo3FGnvS9Nf5diWRkbEXeZcuvRi2NSyPIjz7O3fgMnbtHedtvadW26zBPgoYtaLfku4mocfD5dpWBQwyhq2PVeHr84ht8Anhfch3MIRerdeVoo3x9vZ6N4z+An0T6YaWQHBgvbq/4Qp6srMX86rZOzRHx5krzSD2oGbAb9BvzVy4O+SV7iz3Xs23t/PeYMc5O118lW5Xk+sYpvq493KWpnf7MBSfaffaXkRtDIQ91c+M1bt+OCkbXIURAHDUkc5Fh69XnVTgyNaPyDr79rde7GD3zMlQC/toq0+Xpo9/+OdknofysN0cVGfdfgvUCxFn7NzVHtSob9cS3c16ETawevnNi1Pwa32YhvRJUTrOOcPNaTy9TRBMWLDdbk8rE60=
*/