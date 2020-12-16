// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_IS_AREAL_HPP
#define BOOST_GEOMETRY_CORE_IS_AREAL_HPP


#include <boost/type_traits/integral_constant.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename GeometryTag> struct is_areal : boost::false_type {};

template <> struct is_areal<ring_tag> : boost::true_type {};
template <> struct is_areal<box_tag> : boost::true_type {};
template <> struct is_areal<polygon_tag> : boost::true_type {};
template <> struct is_areal<multi_polygon_tag> : boost::true_type {};

} // namespace core_dispatch
#endif



/*!
    \brief Meta-function defining "true" for areal types (box, (multi)polygon, ring),
    \note Used for tag dispatching and meta-function finetuning
    \note Also a "ring" has areal properties within Boost.Geometry
    \ingroup core
*/
template <typename Geometry>
struct is_areal : core_dispatch::is_areal<typename tag<Geometry>::type>
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_IS_AREAL_HPP

/* is_areal.hpp
6Px4u1hZxQQ39NcE/c0WME/zMNShq8xfzhwijkAcgTgiFGdRdi71A7m69y4T3b2GfnLN4mIV89UIH7hq2LgJt6ZVvw4pO0QYWiY2A7+5t4N9YVqsd9aLloX0fPNsqpQcVvZ9ATjf7w2tExeegjnep2I/1u8Nf3h5LcHeijDuwREssAh9rXrRvRWyQ57mudRwckDJct6TxU0L9+oa+NtO+Nu1Il2FXI/Gbw0+BmsFOq0gzNQBtX3LRRfS6xpstfumY2lxTOIhWxdk8+NhBSTR49lxQpReKMTzEEp/0OmaMEtb21g5RWlYJxsDOrlkls+VbtHxDsw5IvzCk2dDSmy42iXSH99A8LF3Yu77j0bZVW9OsN8juASnPFhhQXqCRdKj+oH0BGQRSFOAfzROsxnHgk8QLgzvvtUysXbvA5y1zqCTLi0bbsbCAdlFi1D4WzSLtc4qkZ6HhmaVfmjrBukhDT2sEGurK0VHrgO2jAW110Dfr8Nc7J90foIwKruADZi+avg9sG+E4T8ZclvhIgJziq2ieHmFGIMveSB8yZoR+CEqVaH94ZVmUUIBfx/hPZpXBFazvWV4pG26eYu4ebVV3DyHO/J1c+BuPrhuPmp/aeR7GdmfznczfvNViDcg3P/PvkwRmFNoFYUrKZG73Cb2oQ3oPLRsoWlW9rT8/JF/7fki8oLwYs0rAuveAd07G0TrwvL5ZXNNJdYTlf2saf8f3yp6PiXEhxCuaH5BGPFLg9+TPH6znq/rSBn9v+oTYSPPEaXvCfFRhL1/8flFYN23bYXv2iw2O6tFx8KK+ba5ltmAfXp9hFWOWHUIPNbCTqspsQL1G/rEb9DCzhHeotOIwLqPtoujqEvu0Fbh7r2FcJ1NYs3CqvmVc+hVD6t05gL9sEi5s5xbIGeXVc5Lwb6MtKNh3WYvExe/g3rxXTR7fzXsPQKn+NS3OgbYExEe7ccXERjVaciTXmieV60OyxJod1wx9zGs8X0C5a15hWHclrSjLWlDPpHXckegHnS/uVW8+XIRuiupsp8lW+pJcP4Hkkaa47cXB34hxPLfol/zN52mhtX27WG9U/pvT5SUXuCsVjriLgiv9fiuSolVV+A3LTjq69TA0TgK7VgT8vonwP+OME84LhvgwvDuZ7eKZ1++Cey/k3UQrE/U3ps6o7qyVteVUqgtXp0Sq3NrUEadYqDVER9FGP67r68IzHlyWjwZ9X49ymj9IPU2tI3BJ3U0OWJFsyMuaR4GzN6v9330Xu2ju2/TAhvoFpu/HLR0KbtM8Lr0tWu14WuTYu0ILLoU9HUX7uSI1yG84B+ct1u2iFvCR2653CTWfrxZtOfaYB+tFOfdCK/9h2kDCMBHcSLC18Ei+Pa9KZKN3tc1i3VIf10vyhA60PpOi0t3cMQvEG7xT59fBMZ6Lnn+f+COjigi5P5p2JoFTvr5Ie5eW7KX2hLrmO7AXkdMIrzH5GmFiwiM8je4fMGzT9WXbxadGLesHGpHf3qFuLTGEW6nA002B8c1wAnEieKFCQva3fqEWN/bwuPB2nMx1jHxxrTYCNvfiPLYOAjLLMF7x4wfTXjdeR9rX9oe1xx3xqa/WY4T7og2Y6/gtoIuNc5sxzizLTLObEgvjY6R/l33WuVA8NYgnPoMy5CH5yAPz4Y/fLpALshfHqA+Q/05E6vPgE+HvpX/a0d9rao5sblB2N0p2HeiOTjeDeKuzYeZfYNcq1/eW1ZinuxKC8a9SoaOvCOaxhyxL2nWF7RBwIswnuqgI9ZZ+jYDOUeMITzV5yMiMK8+UT1GmaAuzy8rGXq5qsbic5OO2DTliM8nDb0AJyw4yh/Pf5p9146iIw4gdKWatZ+JwO0=
*/