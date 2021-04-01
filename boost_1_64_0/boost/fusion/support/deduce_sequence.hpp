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
lx4JeYxVs0f9KeErqrXfLvNK9jyXEWc9AbwF53kLomQTHlss12YOSt/1oIgpKgHnZXaL+9ip7uCFC9v3jowRs2lr1Jzz/3k7fx7w38oDYwgjzGhq26boNx/2Tk+HnL9oYGl2J6Vk4I9u9M54NCHYkyibe+jrdMBtNSYT81c2ZqIZF+nZNjugjSwibwttB9K9g4LxjnBkh24euE+wDeDr1e/d8dAuAgpR6WBinZeAndPzI+GVyPQJgUzMpfA4pLNVK9n/JAIPcnuFG39Ta/6fMyzqu/bKyirjqd+0mJBpCAtbiwGvBWyJdacFCYPP8VtrZZ3Y5XY1QNbdZveg0x+HsrkziISlBDIIYP+Ee/rLs61LZC+rT6xRc0c52AINhgSnVepqxJ++xWNaJzGE4J/kNguW3nI/ikKTuqDNFWeMiBlMH07JpBbe0dzbwQk4uyHNCOynbZuSz4tv0OgLGDXqyu8sG2riaxARcQOVrfP8DUHg+tlp++3JZORfdT/n/BnmpnIZGAbkjCcFyNrH/+EBOZzWB7Xo0/0gzb4KEcWJWDGdkH6EGXiynpphig==
*/