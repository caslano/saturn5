// (C) Copyright Toon Knapen    2001.
// (C) Copyright David Abrahams 2003.
// (C) Copyright Roland Richter 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PERMUTATION_ITERATOR_HPP
#define BOOST_PERMUTATION_ITERATOR_HPP

#include <iterator>

#include <boost/iterator/iterator_adaptor.hpp>


namespace boost {
namespace iterators {

template< class ElementIterator
        , class IndexIterator>
class permutation_iterator
  : public iterator_adaptor<
             permutation_iterator<ElementIterator, IndexIterator>
           , IndexIterator, typename std::iterator_traits<ElementIterator>::value_type
           , use_default, typename std::iterator_traits<ElementIterator>::reference>
{
  typedef iterator_adaptor<
            permutation_iterator<ElementIterator, IndexIterator>
          , IndexIterator, typename std::iterator_traits<ElementIterator>::value_type
          , use_default, typename std::iterator_traits<ElementIterator>::reference> super_t;

  friend class iterator_core_access;

public:
  permutation_iterator() : m_elt_iter() {}

  explicit permutation_iterator(ElementIterator x, IndexIterator y)
      : super_t(y), m_elt_iter(x) {}

  template<class OtherElementIterator, class OtherIndexIterator>
  permutation_iterator(
      permutation_iterator<OtherElementIterator, OtherIndexIterator> const& r
      , typename enable_if_convertible<OtherElementIterator, ElementIterator>::type* = 0
      , typename enable_if_convertible<OtherIndexIterator, IndexIterator>::type* = 0
      )
    : super_t(r.base()), m_elt_iter(r.m_elt_iter)
  {}

private:
    typename super_t::reference dereference() const
        { return *(m_elt_iter + *this->base()); }

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    template <class,class> friend class permutation_iterator;
#else
 public:
#endif
    ElementIterator m_elt_iter;
};


template <class ElementIterator, class IndexIterator>
inline permutation_iterator<ElementIterator, IndexIterator>
make_permutation_iterator( ElementIterator e, IndexIterator i )
{
    return permutation_iterator<ElementIterator, IndexIterator>( e, i );
}

} // namespace iterators

using iterators::permutation_iterator;
using iterators::make_permutation_iterator;

} // namespace boost

#endif

/* permutation_iterator.hpp
WXznUWYtq01Qaomn1F3Rv6Hu8q0v2GhZk3KePJu4ifmRAHP4LPt6+2Qm+gjfXV7ju4sz26LT9BKI0PosXsLt9GxnvQx3GBfucJ+T6jF0Ge3dkPOIHxT3z10xK6120yl01myrztKyfpu4V/GIWccVZdc9s626R+9v/YW457u10WY/6vzJqUl9V1Hsn+f7Tjl8w97ibvXE6Pf/529U7pOp/5gG+342TENoHVR/tv95vY3EXOT/zsP7LlduyPtGThjkaSXO+bmeacLdJU1l9LvTOvHbNOR7TnVxL691QS0x7zDfc/Tc3Ycl7g1OPdTBBD7za2L3M2KYhbOirtC6bLvYV3ND6bI5cp+aHg9KaASkt5zbF1q+uVOHuusTcf/ADYc2a4NZBd86mZhr0dN52o3Vcngf88H11Drl+1MT8bcBumuqn+6KEft9eH/K89Nd+bODdBftwv+r3ntq3uj/nvNmgDnnJvt7TwETOpHvPfl871k0x6ojSvTec7+EvdpzpacMy4fx4S7LnZd1+037U77ztJor5eJmODfod55Usbvd/cGpqt95PisMrT9wD7v+YNqaSHwv67MJd0pcMVon1BX3Km4fpHiB00632Qfhz9y74UYxT0G59LWvmZpz6veeleKe7hmk33uK820t8kDrELE/s/ce+g+pcx6a4//eUyTm/tb3nuqSH0fdFtA5eU6hfu85R+wPoVwOmO89+kyBaoXyLE4N9CL7c0wilmVnvvukiPmtwHcffQ5zObnPsy76S7CrijVy9XRbME+5cd50ZV1G0cU6TdzfPuX7zRZ59iugI2r56Yj7xD4D7zfxfjriuzmBOoJ2+Mv2rtJI0lT1d/Hu8dBc/3eNloX+5jsL7eu3xnIy8v1wjATXgWqsrujmYL1i7l2xybIfwaMSZrl7B0qcdZbxnKtlnHb2PSwoNy3mybxoPGOkTU8gvLV+6jrSVsJXsNVtMyzlKl0CN6P8qF/hLcrPPPiJdmriaobrIlyXIc6hSNUkyHMDYx73avE/DPcr7yTgaoDrAsR8iVOFe2B4f0/JvSv67TG5R+y6Y1wwWeyr0v4WifMpxJLrnTNOeb1cns2j969Rdm9JHFPcwHG/xsYePfvFz1anK96lh+M58nDNQFoW4VqFy5yX/rj4rYrnLk57JUnP+/AX6aTg+VJxdcS7W29cw3HlICVJvF84ricljoVuRdwxDT4qi5v5DBFcP1xcrxZVPRvjhaHX2Zlyv5f7cHSl3HcBH1Frs+YFyz334QiUey1vH88XedO67WmJ43zbeCHjd4PPLGdcR8Q90Sr3CGs/u5f15pi4x9rknmFNuc/MEt1jyP178hxJfrI9T+z6I0418hwpst0a1yW4Khvy+q74q23EPzYXgP9iGazMuFhPjLii/GTt+3k8tz2g/l2Oa6hTQWQtwZC1H8V/eTfSGaXXNT31K8eeA88Qjrac7fLFPLtOPZyk/pX5lXru+w7cY/iCYNniHgSB8mCTHYS3lr9VVuiXMsu1/sYaskniXt07Xs81/LuSTr9+/xRnLJv547//JvdkSGZEyvgE0rTKlh/8jhXUv7XnCePgWl3u/Rr4DE4Jyt0sv09reD2rufERYGvwz/B7MDi93B8gKK06nw9JmOYe7/s140DMW53e+jlob9snQOuFS2/l9yG2tTli3q37kF0WKvMCmyww7tDnVr0p7oNdMeu4/sxzrIrTfBdm6Js6hfGGHC+/XNK4HWP5w90pboShG3D/VMdv37LBck/s4Gboi35i18Axx88HiB3e8OGXe0dLWrLkXve6AWP9Eu6IuE0w2htev1JHnGaNvuiI4wvtOqJhLUd+qdQRzVW6VJ1YZJExadJCy9g=
*/