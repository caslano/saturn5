/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP
#define BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>

namespace boost {
namespace intrusive {
namespace detail {

//This functor compares a stored value
//and the one passed as an argument
template<class ConstReference>
class equal_to_value
{
   ConstReference t_;

   public:
   equal_to_value(ConstReference t)
      :  t_(t)
   {}

   BOOST_INTRUSIVE_FORCEINLINE bool operator()(ConstReference t)const
   {  return t_ == t;   }
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_EQUAL_TO_VALUE_HPP

/* equal_to_value.hpp
B8DtcCh8Gl4Ed8hxip1nQfIs108CsipgPZv2Ul8dYRLsBJvDDKmvLvZxYHeYBXvAS2AWzIGDpP4y5TrqDa+S8KthP7hatu+QeHepbTmfvuclWE3t9/eJPKHp5YSpV1CJ3iq3VZFvpeN/uXyIx5q+3d/PcuhqN76W/n6W2/x9LMW30uxXuYj4Zr9K9rPP50+ZhRh8KMV/UvedDPKR1Pwjg30jj3KMRj10n8hgX8gViL8PZJD/Y5DvY3ckB8HX0fFz9NzhFj9Hx7fR8WnMYF824vVrrNyncQUUP8YgH8aNyDe2Lunt62XyWwzPZ3El8XVfxUOZ5T6KJew7BI9Ak4/iccJD+ymG9lGsf6cbP8UKfRQd/8T47ejDYJ/EqvkjHobRY7EbxOd7uAIx+RyORfbx94dIFnnVfQwn2HmH1jjyDVtBzafQ8Sdcz3V0hO1Sm0j0UI/VBslG8pEVSMnQiH/hv9k7G/gqqzqOP8+9d2NvwBjbmIAwcPKuTkV8Q5uACoowARV8G2MbMJnb3AsvSjp8iwQVU0MJjRKVTBPTAg1zFhaVJSUVmRmVmaYpGfmSqH2f//3fZ+fee+52B5jVZ1f//HbO8z//8/Z/zvM85/8/53T9un5dv65f16/r99/y+w/Z/yurGzzz//6t/4/Y/7e12f+R65v/xf6/PM/x7VLFCez/2V+Js//PL2+c7wlLygcgYqOo1EnLt8knA3wT/CfyC8PyyyvViopcmYf8R6HaKIxz008V3gfcMViHLmAP8no3xTaficxYmwRS7fOZ8NptXv4+7V/1rne32TP8tBmaD1/+ej4+dgS59lt3MHvbSxyhUok7hj3VPzLS1DsD1EZ3ulz/mjvBmcqZhyHnQqgO6qF7lk+W6xvMfdd9u8UVcm2wu5oy6H71mt8UdyQnzw53i5Djl7PR3D++XPgG+v4BKyQ81bdvzJc2wIame6GLXOrlybtLFm2ydb4h70653k3LQZtJ+t8yXzPe+Qrx7ZWvWepVU1Wr/Z4LVgjfCjfFPdgZ66ZxDnGq+ldEZIxwezsprrdXwmj06tkg9mfPxyB4blZaSlbwzKy0kHWvBOXfHeHPbHnCtFOYPLko1g0eT1Z9vG+D8hwHzwqPJ6XluQjPm8qTrzyz4VkpPMvcrJQ0X9bpvaJlXQvfjZLfstERnjdUVqSeO+G5CZ7gsjWpgWB2aiCrd3etJ/s2hMmTtxy+HdDNnrzuyx6I9bsw965eQ5pJxLeAyAaT2aM8PL/PPWu3Y+r9Z7Fjij3qca8PiftDfrS9Y6IORsdBLnQs9GX0bdU9ateUIQ3da1hi2njQSfgNnewD3i5pjrKMFypP9/ieTyPApG2V78S2VXT72mx69nNMvDLlaZlMm1tutzDzwZqoP7SrP2TWMTzkVuDDI+PGS1K/cltdNJ1r8Nlt/crX4RjeQ8uPLMpfLuE0Pzwnqi5btC65KqA39DP4stfH1kW6S/pqtZTRi7PapkgbbW+izTssc6TNPdl5Ktsr5+FazgK1l9fpWuhatZe3rpFyUsjkbeWta5K3lbeuSd5WDq/NVu7brp+X69O9frbZyUlvsZPX2+3k8Nr3IdG8hnxJztTw76UPhH+g/5xmvK40/dl+KtfLae9C5txdw45O0xpyX4bPtKO/LeFuTmQsWkUBb4G+IOMQ+N9gQ68Pj1kvrTFs6IZuhdSGfjyUomPXbK7skjZs8fTeuwsM3appTmCXJY3qvt/O5X4f/E2ujXS850p/lHgzdKs8V1Ky0qhs7LiVQzhI+AFuyu55HY5d8W2p5TTH5z05YebfI/hY8CnwUe6j4rVSV86rCL/TceM3Ns+5pKqiyfRlWlzjqN/Pro8+/rhB0tw=
*/