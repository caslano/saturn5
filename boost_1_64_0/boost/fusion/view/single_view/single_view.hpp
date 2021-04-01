/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_05052005_0335)
#define BOOST_FUSION_SINGLE_VIEW_05052005_0335

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/view/single_view/single_view_iterator.hpp>
#include <boost/fusion/view/single_view/detail/at_impl.hpp>
#include <boost/fusion/view/single_view/detail/begin_impl.hpp>
#include <boost/fusion/view/single_view/detail/end_impl.hpp>
#include <boost/fusion/view/single_view/detail/size_impl.hpp>
#include <boost/fusion/view/single_view/detail/value_at_impl.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace boost { namespace fusion
{
    struct single_view_tag;
    struct random_access_traversal_tag;
    struct fusion_sequence_tag;

    template <typename T>
    struct single_view : sequence_base<single_view<T> >
    {
        typedef single_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef random_access_traversal_tag category;
        typedef mpl::true_ is_view;
        typedef mpl::int_<1> size;
        typedef T value_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        single_view()
            : val() {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit single_view(typename detail::call_param<T>::type in_val)
            : val(in_val) {}

        value_type val;
    };
    
    template <typename T>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline single_view<typename detail::as_fusion_element<T>::type>
    make_single_view(T const& v)
    {
        return single_view<typename detail::as_fusion_element<T>::type>(v);
    }
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif



/* single_view.hpp
VxRWKaFJVtcpnJY+ILAqC45kHU8Df44vcZc9Tpde9dnSwPEfX0nKPTBETAEErLC4wZ3Z4oPlPpkeEZtu9f8LSCa8Seb3yQuh6/4GLsfWD4XUQ6pQQ/O2g6lRjagAp3EjPiAhA6vrM8SHlH+jUpj0vxxbPYgSBY/GUBLFeWeFmncsztp5KCAnEHj3vxAk6cxa4guFL15ejhEiqIudoOXrGjlmiT0K+hr5AFF7Q1kRLNc2HUUUP793CIZdopdvrTXTIdxcLP4M/7BqJrOI9gHWK5jrHHGiet3DaHl+EEL2Ua+572TndcOqwU9hozPkb4nOdu2WRTC4Dv7x8/0xnDf0VIS3CnhKrGd5LlCpU7USjg2kQUZxm5cGGbsA6CIjj/4NvCSxoDvEu2cJUhzHtgGX3/y9OraaVlb1/cOCTCSTurfoR8Am6jGfRapIfDo491SDBnPySKm99W6irfZC7iYxYFns9VekvsREZrEvE06dE8Fn6ngtNCFjXU6c8E3ZckXyQSXimVYsM153TEwxdV19gzRaodheKm1Ut62lOT5CFVjEyFo0338nRuQrAw==
*/