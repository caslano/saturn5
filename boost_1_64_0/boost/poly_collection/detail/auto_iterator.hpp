/* Copyright 2016 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_AUTO_ITERATOR_HPP
#define BOOST_POLY_COLLECTION_DETAIL_AUTO_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/iterator/iterator_adaptor.hpp>

namespace boost{

namespace poly_collection{

namespace detail{

/* auto_iterator<Iterator> (for want of a better name) behaves like Iterator
 * save for the fact that it derefs to Iterator& rather than
 * Iterator::reference. This is useful to "lift" std algorithms so that
 * user-defined predicates are passed iterators that can then be dereferenced
 * internally.
 */

template<typename Iterator>
class auto_iterator:
  public boost::iterator_adaptor<auto_iterator<Iterator>,Iterator,Iterator>
{
public:
  auto_iterator()=default;
  auto_iterator(const Iterator& it):auto_iterator::iterator_adaptor_{it}{}
  auto_iterator(const auto_iterator&)=default;
  auto_iterator& operator=(const auto_iterator&)=default;

private:
  friend class boost::iterator_core_access;

  Iterator& dereference()const noexcept
  {
    return const_cast<auto_iterator*>(this)->base_reference();
  }
};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* auto_iterator.hpp
Okns7OlNOb2m/o58bFdqZ3K4N79Mxsg7UrAMrjk0tLfLE7dnldHPKeATw0OpQUQihPmyx97rFCo3mEp2JXYM79zpOkWqP+BtonBbUm5XD2l7r8GXL3sMvPTl2/ox8elkpnvIMf1oIh+f2pfICnql72/5GOM4fBkacs3c0xX4z1S+//T07xywXMFJmL4Ue3Yetm9oVwA1PHTk4/pT+zJeDLEihLHp6Ez4oUSyC21keoZS8gXneUYfEeUGXHsODfcld/RK4By/LjK6nMovO5DOAB5y+owcZRfnYdJDu9V/g0r7DT4WjccZEcDCGx46IvDDg+mBoZSTMvYZzcfsGe7hv0Pdw5mugb39xFnT/ngelqtzeLAns9+2Z78fxwrj6QhXpnodZ7fvV1FY406EnP4MFqNu+Qp7u0ry8INpt3MmB0m9B0y/HIvGScdp+rPPea+peyKyjNf/Bwa7iP2ycSSOIWWQsJvpFo5/1ZE4N4r0J/tSxBD5w8w4W8e9xrdjkWXUv73R1y7XaXjqeE6+vod63XKuzoOx1fl5Hi7T05caGM44PcbOZZznEcb0DmEvl3XYyaSDcb20PL++vnSiqzvgMmHaLo/ADg4zVFpjf0ceRrKDMbKOFsIQDtPY6Txj91zccJquvpMTMPwc4pZcOsLFB3uuJPRtTO23xkznMzPgElVtzRWBPsZmwCqeg5WtP5eHbW2rymEh4ceKW2fCig1rbJmcGS9Wgj6S/kIYT8JBFN3Z00kBZ7/vG1+cCedx4ecPM2H5uzvZ0y8+dvsxZuYyLjoYNyrysMRP4guhwI1J3T39GceW8bYwXrHWHcEcK1f98gw45SPGx2JBf2qra2traGlO7BxMpRw/9kyF6YyvmXIllUGfmyqA6x4YymSDipVjOb+MxNqBNWPaLy+ATado3Qny6Xg0juDQuTuVCcaXkUgc7falGUeH4CFoeywaqxwkiAuTkTiqos/7NqmMxPQlhzKMlbvpLEEe5vwqAqv0oHMgCIrGT0sj8RKdJHRnyg2Rnjv5saxQGUzl67QQRvHW98t8XHdySO2TyxpfmzwRxpH37HUy4onJ3OwQHZm9PpAymPEFkRjS7HTA98ICGNRMWh7o4Dd5/BCLKzBcEC/GC2Lkq5Yeyn8bhTX+EsjQEYEL6340GiPdB3VN5OPMODFg9N7BmGwwrXE3Jnh93KfXhunkxD0Z5xzTRuC7yc7OVNq26bRF6+qqoL8zHvLPt9ebiix6MMd0rJxoKhfDJENz4eEdLyZ1xpPIojNewuCXebNdJhvUChYyvJTebPOazS/6BrqG3fi9w8+hivAdYXqpjyF5qJOK8J9ddgwbLS6IY9434IIH/NzmtBA2sz+dEtbOT8ejcKE6fVmWG1n8RIVJ52AvpF3GNmkLQ3VDaD+VHOSYcCPD9cWiM5alqCA7ogXjzSjlc+hpb/jNhiv4ln9wxq7BqQX8w+fzubk0M+uAtN9g4gFG/qEIB8a0EQtsR7/b2YMuUoaWfq5N68f6Qf8Ys2np/fackPZl89UBhrA9xCqFO53qcnlcLEzZJRYGNfvyXWru08n7UxJyZ29y11DQv3Ixqt7p9eNQLJdOR1cNge+OhDAktEnXiyEF+aKFGSAE93cNdSd3pxxk0DwioA+nnaTK8f5VkXU/WAAy9JH1ppxYRwWOlV+W1gf0fekBHBcHwWcZ3TIkHcleuy+8tjjAZlL9rjHos2m3GBpPGl5HgjqVj8jWjea+N75bi3AUD2SaDOFcpdm51FQEPZEcznQPuNPBIJ8fawrjpHx8XOM1Z4LmYKzJPH/uGsj0JHN5mwrhtSbp9+3pMD1FijBETHOCuXS6JYzR5M2KJ6MhjD/Z1Yg=
*/