/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_SEP_23_2009_0948PM)
#define BOOST_FUSION_NVIEW_SEP_23_2009_0948PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>

#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>

#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/view/transform_view.hpp>

#include <boost/config.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        struct addref
        {
            template<typename Sig>
            struct result;

            template<typename U>
            struct result<addref(U)> : add_reference<U> {};

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
            template <typename T>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename add_reference<T>::type 
            operator()(T& x) const
            {
                return x;
            }
#else
            template <typename T>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<addref(T)>::type
            operator()(T&& x) const
            {
                return x;
            }
#endif
        };

        struct addconstref
        {
            template<typename Sig>
            struct result;

            template<typename U>
            struct result<addconstref(U)> 
              : add_reference<typename add_const<U>::type> 
            {};

            template <typename T>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename add_reference<typename add_const<T>::type>::type 
            operator()(T& x) const
            {
                return x;
            }

            template <typename T>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename add_reference<typename add_const<T>::type>::type 
            operator()(T const& x) const
            {
                return x;
            }
        };
    }

    struct nview_tag;
    struct random_access_traversal_tag;
    struct fusion_sequence_tag;

    template<typename Sequence, typename Indicies>
    struct nview
      : sequence_base<nview<Sequence, Indicies> >
    {
        typedef nview_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef random_access_traversal_tag category;

        typedef mpl::true_ is_view;
        typedef Indicies index_type;
        typedef typename result_of::size<Indicies>::type size;

        typedef typename mpl::if_<
            is_const<Sequence>, detail::addconstref, detail::addref
        >::type transform_type;
        typedef transform_view<Sequence, transform_type> transform_view_type;
        typedef typename result_of::as_vector<transform_view_type>::type 
            sequence_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit nview(Sequence& val)
          : seq(sequence_type(transform_view_type(val, transform_type()))) 
        {}

        sequence_type seq;
    };

}}

// define the nview() generator functions
#include <boost/fusion/view/nview/detail/nview_impl.hpp>

#endif



/* nview.hpp
vKUYCyCW7bIvxC0d7zQImPeXTM9lPVEOuEI07dYijIux3NuQgSND0OGcaCtMjla+sX6+LJfFsf18A3/4NcPRk3eZtwp9uupBN+jsqv0Ty2otuTU2okAyMDeXzjovMO7ueNarxPFweiuHMmDNs9kgYK6fl+Sy25AHd/J10u8dekj0GW99hhoLHMpBbLJtOSAKtEZ6LZcdiDy4i1sQW7w0HFcG3pg9cB+3g8N5MW5ZN4qn+LVtySXfxrvh85I1d2Ns7ae9OR1QBto5lIF4tTUPT4NE6nnvLnlsd+TDPVwuWrfA9j7lLfBwrey7WCtHq2Ng7jrd3nhgEDB0A+CB0o/uNfSjJ70xLn07eBXFL4sakknC9HMDPqg9yfv4rT1ewyyJLvHGpqF9OQA+oO74YFkaiITZJ7rlsc+QD/fD5w1vnn2cRJ/wSlrgLm2Wg9hZcDC/SvwqLbN1/sEgkTpPHpTHTkM+cHtB6xnv9JTo496GHVBXcBELI1nJypClqMsGidR+cUJyfHjAGB8eo/Gh3nNwf7aqpEXXL5OEyYeiE/NYX+TDg/DZ4eTK/TGCmDemJe4/5jjw/aJK2hwfDBLmXvT4PNYF+cDtS98t37hZoo94HTzUnWCc3M0dH6rLbEVVM2mYOhTwIQ/X1Dym4IMTx+BKerGX3x7PCec7uAeQ6mjvnKBBInVdfVZyfHiYnxA7KvSdRB/2xvm4rnYrD/EySx6yBolUPersJB8WG+PkIsd6VCxhcYSkwo05Ato+B9v+CD8ZMPnxzyT6kDcde8VMF/eXiQ97w6JeOtkXL84j2xqPmXNn/mmoJzzobQ6gfTHNwfmAigT8K7XnlEDFm++++Iqk3D9myP0DFC9ltefCJwEqaFPyqfgUGzu0fxi2/3He6qvnFKtb6jbk4kmJLBfjH6+gvUizVHzqfvONeWwxtv8J+By15ZYGid7v9cJ4w4U5zuQ/WmFrp5GKT5n/FuexUdh+Hlh1x9aP4Kx3nzc3HfWAoIv9BVHBWDQSrrDllJNKgXTjx/LYAuTBk/x05N5nYsyQe70P0nCNAK1v6YgHtgKGUPGp8x8chu6K7X+Ky0Sfq2+X6D3ejJa4Vsx1JgNxu30g3qgPrH09jy3C9j/NLSb3pGPs+bu9teqstIu4slRBezHzDBKpOuA/zB17nJRT9N59v2d3Z2d3eqCUR1S2rU0SIo8QQhJi7c7MtqN9TDvbtkJCiELohSQKlTzyDMlS0QuRWIry6IEkpJI87jf3fHe+M8vv1z/nrN+v6ds9d3/3POZ8955z7rnnbMgUh0KOqpWc+sSlS2bq0fnSb+pGsMmhvpx0IYDpnbbAN5miGPTgLSuvf8/Eej06z9yXXhHPtg40FBeeUN+dUgSAAeVdbM00dz3eVs+aF3JgF5wrJ0s7V5sjTlAfqA0HqSoHmdlRjva2TNER8tSXWt/1t4vHa+6elCvibCkw9Oz0B1TQv0ylkQ+nKiHrxIDjAjszhcjSMlhmecEXls3QXD4hZ8VD7RSOvqWaQsJEbYQAx8qUALomaxkst3y/m9uP0qOPyz5wxtjIkaseIdFKow74iY6XnBjwOtAhS7QGGbxjZRl8MRXOWefIPvZewKYHFoW0iuDEYPaDzlmiDt6Fdy2P4IohQc3lbDnR7r/Aka8OFBK/Cw4EIqoHJ2eJTpCvvsLyCvodu0uPPiZnpEO8NI0hfq5IVB/CPDSEAJ+l/JQlNoBdtFL9WlSyHuzjR+Uu2BP7c+0L6mJNd1ohGAwoH/GXLPElyGCVVV3/raYtsBuYOGm7OCY9CPiI3wWDAPtJe7JEEdhGq9Xz1ClfF+vRR6Q3HvaFOIYYqUViufqZqlubY360Hh7IEqk=
*/