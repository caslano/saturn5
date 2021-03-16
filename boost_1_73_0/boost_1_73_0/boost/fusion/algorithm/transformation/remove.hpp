/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REMOVE_07162005_0818)
#define FUSION_REMOVE_07162005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct remove
        {
            typedef filter_view<Sequence, mpl::not_<is_same<mpl::_, T> > > type;
        };
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::remove<Sequence const, T>::type
    remove(Sequence const& seq)
    {
        typedef typename result_of::remove<Sequence const, T>::type result_type;
        return result_type(seq);
    }
}}

#endif


/* remove.hpp
pP8m17GG8zY3Yk9lMHIvb9YrjDzhYMz9V9FT1VLYUwWMuj6Hk6eqps6vms8ffMCeauSpSp7q+ljNoD/9tjvTnlfsidAZb2u/XJ08NTR1bemfFF2KPTXBFFfauQZ5aoExj1ejov5IYE9t1zg053Mt8tQB89AoT2rU+WD2RIIpo5SnDnnqggkzypOYsr8Xe6LAPFLKU5c89dw8+Z5/9C976oORsempR54GYMz9yfsdn65mT0PNPt8bkKcRGLlmynk=
*/