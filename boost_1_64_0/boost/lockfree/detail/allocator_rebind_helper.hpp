//  boost lockfree: allocator rebind helper
//
//  Copyright (C) 2017 Minmin Gong
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED
#define BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED

#include <memory>

namespace boost    {
namespace lockfree {
namespace detail   {

template <class allocator_type, class value_type>
struct allocator_rebind_helper
{
#if !defined( BOOST_NO_CXX11_ALLOCATOR )
    typedef typename std::allocator_traits<allocator_type>::template rebind_alloc<value_type> type;
#else
    typedef typename allocator_type::template rebind<value_type>::other type;
#endif
};

} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_ALLOCATOR_REBIND_HELPER_HPP_INCLUDED */

/* allocator_rebind_helper.hpp
4DNFB954KzrwDgtr6sCd+yZV7hvRgYv9sb4/tH0P9wH75T7QenBZ/1j6u9v2ZnfxSbi/nAjF1f1sLXLZ3lCq+t1c7X4uzR9qvp+R4b6fJW/U+5n88d3P5Dfez9oPqJPOFbWhtOGepvxf9/ElbcL1VGsT2Rd/mzh+vrqKjvmALPfavtFtBsy2B/Hr7t9XtgrfjC+fdfKMp05q2+Ste99Z9PbquvOTZdbdR7M9iN82IF4/aGZbhehrGZttQqLbZphtRaLbJJhtUerOxgPdFroReYfJuzsH7kd8xFe1VmqS2CSkwu6wOTwE7iy2B23F5mBf2At2hYfDg8UG4USxQegPe4vtw9Fi+3As/JO9M4GvojgD+L73EnIQIBwJGCHcpxwxgJxyy31EQS6hOUgCAXKYhPsQARVFIVatiFGjAiJYSyu2tmJFpYpVW6xntSpabdGi4m2trf3vvO9N9m3mhReh9nqb3+T/dmZ2do5v59j5dqYQTobr4RS4E06Dd8MZ8BdwJnwMzoKH4fnwWXiB6DrMgR/CufBv8HvQTlQ2bATnwR4wV3Qb8uAQuBCOh4vgdLgYXgQvhgtgKdwMy+BWWA63wSVwO1wG98Hl8OdwBXwQroaH4Rr4KlwLP4GXwC/gevg3uAF6vMgYjIGXwwbwSngGvAq2gpthJ3g17A6vgUPhFjgKbtVrj0n9JXV3Vi1rmTWFXUQnoCtMgz1kDr47zApzjou5kf/Jea6sf9Fc13/Sfq7G+a7TPNdl2NdV7SWz7bHI/FbkiBzf8fh/Ua7a/u/Uv/1/3rH2/z4Z/7/m8bc7v4aD6K8evCewDvDYzAmjRmfOHJB5DtaOb1YZqsi4cjdjr3eU/wc8gbHam+o81jSOkLBlHGFJWP4uttZtb/xD20+Bp4uViN5Toml8ocOJ198NzFbx2U98PlZue3V83lXnDYzjDglHjzsJh9iYv3fUfh3fzBTlF6v7PsB9/6bc7/A0kft+rs63ewZZszym72DceSHhmdcDcN1/XnPbf2GuJeVwzzccyv1WT+A9xQfqfIdnIl/wF1s9PKbve93ptwiTCOjva2aqsmjjeRKbeO2nQL/nmKvcUz1PcA87jNc7+t+nBL6/2UG0bPu5LVTY6kVLsrwn6K2uHe2J5lvEDzGO9y1LA+nax/Uxyt8PPCocLiQcXmz4wz+A+znWbFWunUnUViLVFXZzmNbJfrvu8vvHieq3Gh/OMY/hR1J+pHegereQZHnUeH7hve7xvHxPLM+DHjtaYqffkzB21Prvs2XMKP6UvLm/g1dyoMJrIf7ETvu1y86WgSSRAexUXtv5nyT5j53Kn7nKn8ozPRbt7wk95my2yIP9R683evLKq3/8o3bPxo67dGv+mFBjvH/fms11XYvaPKYKNTYLPcb7WOmzyrMj9SflpMzTjnWRk2AruEj0cstgG7hSxlpXwXawQvTO98Gz4DHYQ8ZCvWBLmA57wz6wL+wL+8F+cCocAWfBkTAX2uGXwQGi1z0IXg8HwzvgMLhHrtsn1z0o1yVAGRvocYEl4wHGAkHjAMYAuu9fAisw7n7+MZsZ9K1dffjrMc2q9dPop+u+ue6X0yfX/fGNrj629K/dfWvdp6Y/Lf1oZ/9Z952ln2zuE8+Uvu+BSH83ckSOyBE5IkfkiBz/hvF/JlPCReWnPv5PsRLUwONlXiT7rLHnzcwcNW7MuGlTibp6N/BiKuEH9gWUvepewngxL2LOTWf+9G55N5CZMWXc5GmZOUXp/g+5OQLzyh7Ht9t2YH32+OfuGlkNiHqU6b0A4brXrclRY6cUeSfwonJfbZ2J7+mYYqu+8b2AM5z+at5RRU+PVwfYcaHEppr2E3Rdr9c=
*/