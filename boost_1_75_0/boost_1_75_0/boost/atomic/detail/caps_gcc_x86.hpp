/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2013 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_gcc_x86.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/hwcaps_gcc_x86.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#if defined(__x86_64__) || defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG8B)
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#endif
#if defined(BOOST_ATOMIC_DETAIL_X86_HAS_CMPXCHG16B) && (defined(BOOST_HAS_INT128) || !defined(BOOST_NO_ALIGNMENT))
#define BOOST_ATOMIC_INT128_LOCK_FREE 2
#endif
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_GCC_X86_HPP_INCLUDED_

/* caps_gcc_x86.hpp
ZnUm/mRG91w0NN038Mkku3KoJs5S/ewV4h9tuqA/1EN6hQgZBBq7e5LEGGYHMEDtb2depfr671Ws1ntIFb2A6nhblQOdYupI1G85yjyQf9qSG/xSfF5uymTsV/Aazpp0PJP765eU57Z+3y8lZgJ+XGXCwXkrJb0qQECWIc3lo62xI05JAIy59Wa/WFqMZex7i2SXom3Jv990nyIf9UMBMvKO0nNuOe5C4XUjZsJrbt45hdnmL+LEiAOxA//b+HGDWOKR9kKv4H4BVF/aJ7PLsDXFfV+Ug6cXnhEBtHfjy8Q12Sr52E+Sp5os96nCsbzR+AX028K16nyct2mry9u1axPFmA1EgxYFwpUyi670ufIIu05p6gKhic9FVgfcnUiivZPH9oUhUIZijOHUlwgESJyyZ9YMP9nIS7zWe603ltCk105oI7z7A7wtwr1wHD6Q0lF93na1Oa7a5euW8uOQo/XbYkx1Wo461lJAkFZ3DV/Jn1hCL+oCo9L+TyO/+fBv24Pi3WL2JGa+5Ed0jFZnvyrBvy3BjoqiSlEbaeNWqb1iAvyOqX8EwHPv/P1wn4PXwJXZFzRHTekxlCxdrmanaChdnnBQ2lJiK1vSWZNLk89bSMWnepbikqiAPOnt/DSQiC0zLgBYp3DMn092acPmBxxgPyBY8z+SfEa67XuJjnvLr1BMZk9O66ZJi4x6l1Df1LhEzjJWEE7nShcT
*/