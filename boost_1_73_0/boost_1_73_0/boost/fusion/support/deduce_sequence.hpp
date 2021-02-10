/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Use modification and distribution are subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_SUPPORT_DEDUCE_SEQUENCE_HPP_INCLUDED)
#define BOOST_FUSION_SUPPORT_DEDUCE_SEQUENCE_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/deduce.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/view/transform_view.hpp>
#include <boost/config.hpp>


namespace boost { namespace fusion { namespace traits
{
    template <class Sequence> struct deduce_sequence;

    namespace detail
    {
        struct deducer
        {
            template <typename Sig>
            struct result;

            template <class Self, typename T>
            struct result< Self(T) >
                : fusion::traits::deduce<T>
            { };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template <typename T>
            BOOST_FUSION_GPU_ENABLED
            typename result< deducer(T) >::type
            operator()(T&&) const;
#endif
        };
    }

    template <class Sequence>
    struct deduce_sequence
        : result_of::as_vector<
            fusion::transform_view<Sequence, detail::deducer> >
    { };

}}}

#endif


/* deduce_sequence.hpp
cmVmb3gtZGIycGVtLnNoVVQFAAG2SCRgrVTvb9s2EP2uv+JNMeDEkK0mn9Y2CZa6SWtsjYPERRHMg0ORVMSVJgWSyo8u+993pJ2kLYKlHypbIkXdvXf37siNX8pKmdI32QYGP++KaHj2WqR7QReNK5cTZ/+WPDxtvljcYfUjtzmNz9KUePS5W2zhB3zusJl8Fmue3ThfLJ6lmsfw4qOMrvNFnNJK9Eu+Y9veOnXZBGyOt7D98uWvGGLnxc6LAm+ZUVLjLEhTSXdZYFekld8adnMz8nK/gAxgevQANmuUh7d1uGZOguZacWm8FGAeQnruVEUvyiA0ErXSEuPpyfnk+F2B60bxVG7c2g6+sZ0WaNiVhJNcqqsVSMtcgK3Jn9CF8oEQu6CsGRG5RJBu6RNIDIBpb8GumNKsIioW0ITQ+ldlyTunKYNSWO5Lfi/BqAnLr7I5pziW7Ba2DQgWnZcFom2BpRWqjiPJQottV2nlm+IxICIzorQOXmqdwMhRSb8KXeJsrVER7dBS1CrEwVvjI9d1Y5ffGJKYCabunCEqEoOshCWxC3RGSJesU/r3HGtlk8z/U6LHmAWsoXiQH5xhcpajYl75Ap8ms/fTjzN8Ojg9PTienWN6hIPj84T2++T4LXWBIj4HedM66Ynf
*/