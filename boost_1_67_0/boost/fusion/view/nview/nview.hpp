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
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
*/