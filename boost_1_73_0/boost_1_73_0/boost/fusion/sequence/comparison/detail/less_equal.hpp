/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_EQUAL_05052005_1141)
#define FUSION_LESS_EQUAL_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_less_equal
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) <= extension::as_const(*b)
                && (!(extension::as_const(*b) <= extension::as_const(*a)) || 
                    call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* less_equal.hpp
XpL3u+X6SfyGWAD4fHrYrA+ry6404Gq7vNrtyaHYbIQt4K2LQ1XsguR1eC6FGnmGEq+P4tdhtz0IVx9Xu/eKIsRRWHk67bfgCOIASssdhPmSnLbLYl8qlzVvXNQxLQOMNk1X3iXZbaEw5IWXkzB/QR4Wh/XhktyFbJxMGbnzssyL2ZwkQ+LFc2HsNowDaPo1ONuT4r/P++IAzvdk/f55sy6Wtc8/7+fq4uKqrcJp/1hATJdlLd4V22K/EHV4KBsLusJRNPeb5w104CAhccIIDUJGBnMy9uKACGNfrLePmxNYeCG6Aj8Ux9Pzm9ULCS8Wh0+VuYMQCPeLzYYIGNr1KLpFLYY+fjhWnXqxeV4tHorj+nGxgXCItgFvEOYTzBSlp84s8aW/D//8F/mJ/HZByG8vvEHOMs9nfBqH9zxP/FvKXlwSf5pFScq4TVxLGQdROZau/7isbPk+TRkLJxQakk9y2Y4mam1EiWmB09hPAjBtGGgleBmCIKN5znPolVTmyzjmPWL5zJdJJYD7KsXcZ1lkkEoU85OmNA5kSglg2lOWZHRIM5rJlA7FeHdQ23A0+1pmNRhap8F0CEbz8Fc5eB2I+PK9MB4mEqMCUC++l3psrOgLANenGdM91BBWovE0vuWDUcyH09hnYRLL
*/