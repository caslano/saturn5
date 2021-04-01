/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADVANCE_IMPL_14122005_2015)
#define FUSION_ADVANCE_IMPL_14122005_2015

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/mpl/negate.hpp>

namespace boost { namespace fusion {

    struct reverse_view_iterator_tag;

    template <typename Iterator>
    struct reverse_view_iterator;

    namespace extension
    {
        template<typename Tag>
        struct advance_impl;

        template<>
        struct advance_impl<reverse_view_iterator_tag>
        {
            template<typename Iterator, typename Dist>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename mpl::negate<Dist>::type negative_dist;
                typedef typename result_of::advance<first_type, negative_dist>::type advanced_type;
                typedef reverse_view_iterator<advanced_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(boost::fusion::advance<negative_dist>(i.first));
                }
            };
        };
    }
}}

#endif

/* advance_impl.hpp
DaJn3K3pIryEcS1wGGYe9xaaLSJy1WHnVPAx3hwr6+OpphKpcOQcJouvGuhcFJlY4f6MRS+PtfHV89oczMEXT7PXCs5L+yMcNDaU7X1xyg/Y4Wl+bATCC+T5i+XYZYhiLdeSiawFm88JpcOonqxGxsoPk8NnuLoEgLv/bGJCIL/5YlBBBJgheYolMgO2UO9qbdqrUYVv3RGmra+urufDgGLOEK8Kpk56kXg9uYr/VgaRzcCbv9qaLlWxOjwj4gGfQhGk7CI615h1Hi9UAC+nk38PxCHW4F+zTW053ZRRpNDA6PbWPlcyM6fO5KtEWTPjLWttZVOVRW4CaziEc4bnPBkUsL5mHXKcytAGIpmUOA3O4/75Vd8MF96NulGK7k3J5B1ovYYxEBNZ8MYX51ntIHmI8s+hguy+ySaOoNKJV37Qo23FSauWgSlClDIOHmAG5CrjSwMWSc9LQkgvDLTLTB9b4nzek8GypzQlwe/rAoBIVUxHFYaoO6Xl3VEV2e0dBMLRikb86jW48Z/V6mzqEMU6t2XDqz2CMb0BWBHnSav+AAx+LJ+bQdWIIA==
*/