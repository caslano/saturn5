/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_IMPL_07162005_0136)
#define FUSION_NEXT_IMPL_07162005_0136

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_iterator_tag;

    template <typename Category, typename First, typename Last, typename Concat>
    struct joint_view_iterator;

    namespace extension
    {
        template <typename Tag>
        struct next_impl;

        template <>
        struct next_impl<joint_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename Iterator::last_type last_type;
                typedef typename Iterator::concat_type concat_type;
                typedef typename Iterator::category category;
                typedef typename result_of::next<first_type>::type next_type;
                typedef result_of::equal_to<next_type, last_type> equal_to;

                typedef typename
                    mpl::if_<
                        equal_to
                      , concat_type
                      , joint_view_iterator<category, next_type, last_type, concat_type>
                    >::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::true_)
                {
                    return i.concat;
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i, mpl::false_)
                {
                    return type(fusion::next(i.first), i.concat);
                }

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return call(i, equal_to());
                }
            };
        };
    }
}}

#endif



/* next_impl.hpp
ReZ/WOQDkUgZJx/x2ScoD3vB9/ufeay7RAf7RdgvFgRd8qEGQjVb5gOR0NYXT/msAfnANzLWTNl1JbbUD2LL69NczRf8OvmYzVmTCBg2l2WwB4hrbe4g+ORudw6W6ECfxxmRsRFc6VCiinW2eVCXOi48B3u0KAdd4fvBx3+LeuThPj/fKM8NuuJBaFLM9rhAJEw+zH3JJ38vvs/33ie/pkt0gF+PLe/kzOZQVWrXIk/lJ/WFN32IKybb3433hZGdZwsQesg4tDfE0ty1Py7CI1hlAZEwbPLv+2wtygHfp/rgyGMukGh/fzqOCeMCrvSmcI9Ku+MiETBsLh/45IPDlcbSY+agptTP74U8WOq7kgWoot1xUREweNDwYXK/HxQE4Ucm0cP8TjgyFAdd7c2ASjcxZNP6RgSMMfHjpK1lf64jPN6zg0QP9SPY6ukgBy3c8ABOmJ5mkwVUPo2JnyRl4ABDBg7xN2GLi9JcyUCsd2ms3OaKWhEwZGDpF0keFBg86Ou3wX2ptRlueTCph3UucBKmnvSdz7bg+ok7o5Sf9yvOjwf763E8qHfJhzj/blNHMGnQuPiHzyaiPHCno42JF2eilc0vyXDeJwptD4w6BVo7bfHZq8iDnjxOwRV33iNbeZAfDKCuGHSlI0AE3XAiblMSFAXDruIFWFvsD734GYHK2QWylX38F1FbaO/MhyVhWwyIgDE2pgdYFNePvXmcjWGz0Pbc27/Hw31K4FEHRzyIxyaGrfKACGj21qwAexr7Aj+b9Nm6UEeJ9vJL2qEPC3y2dMMD+M0jRNvkApEwdaUBAbYB10/8HF3wu66PSrSnPxv3Y4rznMkCr2SoxjofBAlTHsYG2P4oD4X8jNM1DYsl2sMHPUH6daW52qcUlayqtak1EQmTD+Oqknw42ODDgX4+6k3FmU77RU1osm0+CBKm3lSb5ENfriWc8Qnu2hf4C2EnX8V53t0dH2K1NvdriYTJh4Uzknw4hO9b/1WNdoUD/F9RZ3g06MqPQVQyXmGdD4KEaXe+LEBnsMD3kc5gQWQbP9YL7Y2wf5/jjg/ghWWbD4KEuT93W4DdgnbXw/ioMOzCNhLt7rfJRI3amb+fqGRdwub2HJFI0aHuTspDP0Me9vNXZOD6EjiQ74QP9aVlkfFRmwY3RcFYUy0M0PkY/nnPoilPylbu68/AteWENFc2+PrScnBVrrPp9EckUmyv4Nh2JvKhiPu0PPziKRLt5s/0kA/O9Ol6EXjRKheIgGZ7fTjA7sVxgXeEkwev3kGi+/hrc9H2mulqXOBVhBBflpmgKJAu/VSAzuIezvcinvu4GD27/JJ0/CvdXX+IRK3uRBABw/68PMCmIw8GwufRJ+fcJdG9/bke7lM77AuW19dEwNiffT5AtsdBhu2xiz80iHLgzAZfD0c47IqBKp905xeSc+NgY27cy1+a5noPot62fUERMGSAvZyUgSGGDOzp5wdwDyLgjgeTymwqSVS+aMOWLUx+wg99p589/K7KxuQ7mQ+m1FSM5XdSyz9La+oi1ljRHCm2HXzp/B/zJRaNh62domqWFo2ZrwRYOvaXI3k82X2vfkm2fHd/dkCNmU7mjZS6Tg5bW242pmSeJ1kRoBgyw7htZl1wAFrp/UfR9y3fjW0Oqsd/27PMEYFUe9SHAdrLPco4P9DRH6v8Gjwn626qos0TBAaRVBsl8GIv1LGH89jIV/Q5T6K7+ZtoL8+tPEAE5bC1PZzGVLQzdwG2DM9ajeCxsmt+wfPYu/rD1VlkD/La5kV5Ffwrragqt7XcMAiYeua3sIeB+zgj4fvUNy9cKtEO/moPfWOZMx6EKiydo6DiU9ec30Msppay/Uc=
*/