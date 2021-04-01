/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_10022005_1620)
#define FUSION_BEGIN_10022005_1620

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/adapted/mpl/detail/begin_impl.hpp>
#include <boost/fusion/iterator/mpl/fusion_iterator.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct begin_impl;

    template <>
    struct begin_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef fusion_iterator<typename fusion::result_of::begin<Sequence>::type> type;
        };
    };
}}

#endif

/* begin.hpp
fWWdJEhBds3k2D8KvZLq8qBIG2SaaFBTiAeRyaif4Fq+jt0mWaIQJPhBR6kqRXM8X8l2G0UDMHfarM4iJPvxeYZFA+tlWZJLX0gdRAqbj0PBj3J6EA1nogmfdvXN53qAu4A6Sxd1oG8CHatGsJqw8Y85gn0Im2FfZuVGYWJBIST42+U9DQ12aWMxEaXOIVHc5NTXO2jlHwK1vpW07VbgmIH+K4zETrDLhf1a91PrgAx4gcX9X1eyquFJsFHyZwbdeyfEynJNa5COP7FaE0IUnfZnxdS3p9X0AN62LtDdhOMRPFjaSqq8YGPDrluLiVLyurl0w9ekSK8He5l3z85V+U2OBdwkEO8gGN4tba0vMO3DzZwX4nQ/o5Zk00uZZNUkWSMRdbodWkrS4lmABnTv9lRTXuCoKBzgB6pCql6oiSI4a8za1LJKkk+poC0WkfQ9BvyZbGQid++mk8Q+JvgIP3jfeaYx+QSAPrwcTtrB2Zzz1EieCtgRLEjcb+t8iDLbwrWo8HprPWOpS2AjjLFVWdQNHyCoc4VhKEJc/mH4dNKk+OCvZBCwOHi5iA==
*/