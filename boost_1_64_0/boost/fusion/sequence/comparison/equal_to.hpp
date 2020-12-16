/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_EQUAL_TO_05052005_0431)
#define FUSION_EQUAL_TO_05052005_0431

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/detail/equal_to.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>
#include <boost/config.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4100) // unreferenced formal parameter
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    equal_to(Seq1 const& a, Seq2 const& b)
    {
        return result_of::size<Seq1>::value == result_of::size<Seq2>::value
            && detail::sequence_equal_to<
            Seq1 const, Seq2 const
            , result_of::size<Seq1>::value == result_of::size<Seq2>::value>::
            call(fusion::begin(a), fusion::begin(b));
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_equality<Seq1, Seq2>
              , bool
            >::type
        operator==(Seq1 const& a, Seq2 const& b)
        {
            return fusion::equal_to(a, b);
        }
    }
    using operators::operator==;
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

#endif

/* equal_to.hpp
xOZkfHi56r+nsP7j/hQDwCgSuhzzNWuOcZ+AUQXXAd0JXvGxczvGB6zKmvplPHyBXLcvbx4Ty477nNz/ROQ+TGUjJG+rWnsopx79Xnz/FNYaj2Zb4b+O99fy4biq543WnOJz/m0VnBdZ80t6N+1/ZEVPsRiishPENEd9AtcsryyL9/f7rP4mdsr++9DcOcR5+mR9fjyl8mFt47vKyHJ7FT9C8F5aeVU8fN5aw1S46YvrRbXYHvhQzsFPg95msML9xkHU99TM57E1UPuJiu9ngbaeMUR8/ypvj384rvBvz+bZ2s5Ezo+vmfOjam45nj9o3MO4X+bb5b4qJp06439G5elJq+bidzHnzM1D7Ss/t/cVy/b/nwLHPpet+El7b2i1zAimfH6JUFzg05pz/STouJ7yLb3FDfW5x/3CXk3nmeBZCDNlpBERV6Py/ZNjgDV5osiXyd/w1jc0tcFu6yLh8fOWpriKNVPOCeEQVLXzCpsTVZ9/mcaDBJ7y+3vkvlFaSqIK8i28wVrnbE6/XtL5SaeK+QV8+xzlvkV3B459bui28DHCZJLfXoG6/OVlCoh8VzGH0B6rY+T8+sTta2tZyqTvo/GqDDxRmhirkrd732CfIZr7xj3xxOG4atf9m9pO3VWN5YMEjr2PUx2q3x8BPH6+8Pht38fa0ROy+vZO9A/eKqh/BE9HqT5zyHk8taU7Kn/dlSBFkwpJe6xhnOo+yo8Hjr3P8/F2KhxzCVjn1gdoTEqzbFpAqs+/U9+XpV+j39g+fhb1Gnnk/k0FcPj5wc+Fb/L6n3I4rsZz+YZ55wrvg5N2H1jy1DPt/rZ8z/pWOfb8vCdwaht1+f015XnLV7mYN19E2yijh6zno3o8RIAG0xIXo1L12aq1L3I5+w1PEHysoK7lp8aZjt/wDjysPmOhPClKm5JyDkjYkT0CJiKL6bts2XYJv0Zw8aBbIclEjxiPCifZq3B2xjYW+kjiXSrxTo/G1cMw8ffQfeJ7edfFc03JAvF3mcE2YFJSwom/pZsSnCs8jXqP3EzjzLY3qN5n3lx+1/ohgn2bw4RgSHUeu4WE2Qoh6pOP3HIujtCjUD27tyK8tcrCQo/NVYKZD1F6XN90GwYX/BPt3W+rYTublWGUOa7RIocL5vrCANWYG4duJ3DorV+WoWOG3P32DC7tBGT772DCRtN1g+6Bd5QwbV9AdX6dYGIoyypZubt3YnABItj+OzPYBEBq78G7mjDWXKr7OsOh8aJ5dPe7E1xoeyi2yoF70HfTnoLqfuY9OVy/Emmc4iDh8Icwg7+H3ptwxDIrn1DRRppzD7wPh8P0ob+6AbV7xRKVMztEeMJCol9qe414L4fuR/Dt+rz6CMHYK67m8QE2fDhepbL/RHB6qCbYHR9MsOfLjYrKvVLBxHQYlQr4/uZgtrpO/Xf+IQSfwqprFX+V4WrMODYHHipwDJ2bGCM5hi8nmGW7QuP/5xJnY4ipPts6PSbevv0w8Z152eORTI/t4x9uwYXDAOPtKyZO1eVU/tIjTBi2IhS/saFpX8PhqFrD/sxgkx0sRL2WlgxYxRLB/l7CXoApiLb2B9PVluEbc4K/xeKpJ3WDqOsMzDDU5KJEtjGnTnBdOAxs4FXQBR1kCVH/aE2EOZoMZuui44fb44G0qNRlvLJWBryV8iDDm5edChcjON4awz+h/h586QR/M4BxPv50gqYyRlNZzCrxQjZdV8xyEicTtg5x13XEqdwfbuJdmvsGXTPxU7jdwDEU/iAlvpzVqoo+2bLxOmK3lxewusFZsDba1t4HDtmsLDP8IsAreQ9DA4LhLtbO4TXO0wETP3NgQRVkodtT+GPsVWckU316x18=
*/