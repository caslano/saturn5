/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_REPETITIVE_VIEW_ITERATOR_HPP_INCLUDED
#define BOOST_FUSION_REPETITIVE_VIEW_ITERATOR_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/view/repetitive_view/detail/deref_impl.hpp>
#include <boost/fusion/view/repetitive_view/detail/next_impl.hpp>
#include <boost/fusion/view/repetitive_view/detail/value_of_impl.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    template<typename Sequence, typename Pos =
        typename result_of::begin<Sequence>::type>
    struct repetitive_view_iterator
        : iterator_base< repetitive_view_iterator<Sequence,Pos> >
    {
        typedef repetitive_view_iterator_tag fusion_tag;

        typedef Sequence sequence_type;
        typedef typename convert_iterator<Pos>::type pos_type;
        typedef typename convert_iterator<typename result_of::begin<Sequence>::type>::type first_type;
        typedef typename convert_iterator<typename result_of::end<Sequence>::type>::type end_type;
        typedef single_pass_traversal_tag category;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit repetitive_view_iterator(Sequence& in_seq)
            : seq(in_seq), pos(begin(in_seq)) {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        repetitive_view_iterator(Sequence& in_seq, pos_type const& in_pos)
            : seq(in_seq), pos(in_pos) {}

        Sequence& seq;
        pos_type pos;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(repetitive_view_iterator& operator= (repetitive_view_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Sequence, typename Pos>
    struct iterator_traits< ::boost::fusion::repetitive_view_iterator<Sequence, Pos> >
    { };
}
#endif

#endif


/* repetitive_view_iterator.hpp
n05aroSBoj0rQUAJM73LciCOQb+PL5MUg5JmCGX2LaJHRsXcaJ2YvXmff4Ty+75JaHFiPRsE3aDox0Ov6HMXVcz0fCx5wspnyQDxaDdEPYcAwHPLbDpXBKcZLMxe5Midk875qpvhL19pCb06zaBzxQZmKMdstnsYvffO0QzLM0kbVO5FLH1+t60ZbD7SNvmO/0hnh13MMJClu9u1+b/oPLKXGSYZpOXPOCGE6hmOayRIO1k77Slql/5irgirvfl5dqoLWiFm+3L0Wktt1l+sdUpdys2U76lBS88s6lkbShfgNkNv0UdDAWBF3U9Lqc1Gm+kzPMOSz3fXt1pMZ5xjzDAGpM0L+vaWYhhrhlMGaXUnvG4r3wlkhjMsz/Unn7WidNFmaOYnLWFvy4cUX4wZSot0yYe3jypEy3dEzsZ+AGmm6nHz6LsYaDuYvfLr0YJimGOGH0Zpwd11d6j/For5ICzNxL9f07nwIjMsZpYQWGEX5bnYDCZWT1frxDjqhyVmWMhsl6Vsa7JleC32YekyfQ+hdllnhlmsvMf6Ys2oPdery3tapdNcGmcbzJDDIK3EwlX3KM/NZvgK0k6MuH+DxtkWM8Sydpnx/dAnSrdTnW7vhP59Kd0uM2xh5dV9MXobjaX96nRv7laU77Y7YIZ/MbutG0Fjwn3QDIVZfObyW3NSmx0yw2ZfaW1e/zWUPkt12gz1WboaUeuq0Xg5a6bnccmL1bu/es+nuqA1M0q7O2I1jYnEi+L+RVjaoX9OonpeEvcvwlTvDlOZ+l1l8SpTvwsqEa0Js74dm9ekfkg0Q39mVwpurUrp0DKTqd85loQWy+tyLKMf1eWyGXyYhd7tuprmEdpa0S7JN5ebBxYcSPFdN9MzqeQbyC4VDheleYSWlkz9Piu4YYYuzE5/0EfRWEJrzOyPb1HyuVMqu3KsZRj1319m6MVsZLo02Skd2k6dtNyWgaNpfN42QymQNtfelmIPQ6vJ7IJtVQi1C1oaluf6HHl3UJ53zdASpBXMPUZ+DhBtN7MKa5e1oNjvmWEDs9kB+dPIdx2boT0r7+avWYdTeQ/MEOYn7ejVtom0Lr0wg10vrcT4enVonXhthsmsvLiiH+kzpZBkhmhmxQ3DOtB4QcvKbMWm0pdpDKI1YJbPVX8szb83ZnACq0uDQD+KHe03ZmfevzpI6d6KezdhVVfe/0Tp0H5llu3+iyHU72/Vdel9M8dxiv2dGVrxsbvEPJP69p26vFlVrGa6bv5jhj910jZl2k/XzbAPZrgJ0oxDztSmdeKjmLfCQp+HZaC2/mSGDswuNXjziOJDm8fKSxtzAsi+mCEEpHU+diwb9QPaEWaDqpaLp/i+msHK8jxuOnKf4vuO4wWkxcc3fkZrD1p9ZrHhUV9onKGlZ3k2zwlXKb6fZpgA0q5Xu2qisYRmYOla7gzYSul0FnCBtDWjQudRe6JdZBZ478cFahe9Bfykqb97hTaU2fp8I/PRODNYIDezjy0OfaS+RcvF6hmxZMFdamujui7b6rWoTOugyQKvmb1/XOgItbWvBaYxq3Uz/SXqI7TufA1Z3NWX+sHPAguYxaxbJN+9aLYAGKTNv5tlCuVptUAYSCsdaepBedosqn6/HZpYidoarRFvsxJDQyh2tLbCRiffo/xcUoDmWBoLuJk1fpk1O7UL2nlmtxZO20SW1gItmD35Pr445Rkg2kVYuoZ3mlNd0JropLWct+QJjYn0FvgDpPV63bUpWQYLdGa29XVBOXYzeo8vEq0ns0rBEx3Ut5lEHwm71L+RXCPRQNQz+V56R8Qy+e7aLBYYAdKeb5vqpLmCNpNZ19k/T1IfZbVAc2a7BhyoRe2JVs4=
*/