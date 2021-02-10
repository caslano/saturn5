/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_IMPL_20061024_1959)
#define FUSION_DEREF_IMPL_20061024_1959

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    namespace detail
    {
        struct poly_deref
        {
            template<typename Sig>
            struct result;

            template<typename It>
            struct result<poly_deref(It)>
            {
                typedef typename remove_const<
                    typename remove_reference<It>::type>::type it;

                typedef typename mpl::eval_if<is_same<it, unused_type>,
                    mpl::identity<unused_type>,
                    result_of::deref<it> >::type type;
            };

            template<typename It>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_deref(It)>::type
            operator()(const It& it) const
            {
                return fusion::deref(it);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct deref_impl;

        template<>
        struct deref_impl<zip_view_iterator_tag>
        {
            template<typename It>
            struct apply
            {
                typedef typename result_of::as_vector<
                    typename result_of::transform<typename It::iterators, detail::poly_deref>::type>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(It const& it)
                {
                    return type(
                        fusion::transform(it.iterators_, detail::poly_deref()));
                }
            };
        };
    }
}}

#endif

/* deref_impl.hpp
43MojOzTMBGmVw8RHBVhTLn01yZPoKvzKkPRFQi22UY1LmXOaJubsq+O7KqmkufYDhtZjpF2LBgPihimxBq3iVyDXGnb+CmTopAR8hGbHSVWw3J3BnFBUZvFEt6yAQ+SCxwBk7yEhGVRS9l0NQJaZoH9cZHrlYEj1rht7imHTbUAfzACX7X5ogqfSdzyUQrVLboVlD2+6EtoVZoHjVOHf/zToHaZ0mVY6Bn4Hp/kER0/fnxi327QKUWlnbLaAhWhIVKJrYNs5OUaGududn9vS5M6+37VVDltJOLnlhR6CpnPRehH71XX0rZJZw3DZZoHNI5EpEyo4TL3tqSidtQ/OnzKCG5ilWV4NltXEPC0wwMW/DBuhqu8tZf0nqsXeFpIg+oC/ObK7ib/G1GfHJ48sSHnfzl2RNqe26DMFrmIttj+rX/cQbRyWpoYyGL1qcDmwbZN7LMDdCuL9UEVjq5R89HouzQ6PGK57PzViuPLlCPErzFk4aZksko1bPTZyDSas42qxOFYqosK8rbGGr74bdewByhig26zY/uI+nXi69dw/BPCSy1UIRJ6narbwXVePn3So5dXr3+io8c9G25/99wGLvdxiJ70T1gXdF4y90DApuVp2N3QY3zgJmImQ2Gnm/NKuWo2g4ArnBnQ
*/