/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2012 - 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/caps_msvc_arm.hpp
 *
 * This header defines feature capabilities macros
 */

#ifndef BOOST_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#define BOOST_ATOMIC_INT8_LOCK_FREE 2
#define BOOST_ATOMIC_INT16_LOCK_FREE 2
#define BOOST_ATOMIC_INT32_LOCK_FREE 2
#define BOOST_ATOMIC_INT64_LOCK_FREE 2
#define BOOST_ATOMIC_POINTER_LOCK_FREE 2

#define BOOST_ATOMIC_THREAD_FENCE 2
#define BOOST_ATOMIC_SIGNAL_FENCE 2

#endif // BOOST_ATOMIC_DETAIL_CAPS_MSVC_ARM_HPP_INCLUDED_

/* caps_msvc_arm.hpp
7nUHujwuyrdvxFqE11G31x0Io20kD58r975jHz/Jb//EfyEIeyjf9dUzNMeW0D4uoZn7q5U7cJ3PijiD8bsX7JihdPC7mhD0tGpxQ0zxz57bWprg7xmSr27Sl7mlO/Esytd0jMFA5N/+kjeGXba1B5Oxjh15TjqWL9/k646TUbuKZX1jh/2bX2kXnnXt0R87iYnHswNfm8kvCN/9q6/g78VPbHVTdVLRi8NkOUKfML+f9s/uPEn8WCK+WZ8pNbOLZ/RrYP7KGPzwJCVgCgdwqDR+7Fw85N98c/2L2Cmx3TXwyP8UNCPY/yE2xf8iNiv3v7Kko52Zuct/bK3j66S26v09mxpKgUIibDR9f9dABE0KIssTJQGJ1TCjNWnANiiNFPVKX9R4HHV3w2Ym1KABn5BtGwRIgR41yjhT8GMaNncFGVQKWc46isnrCuvsQDi2VtVFqkbVVfZk3luxT/+TTf3aUJSkSwA7G49ln+/2jufsM+9Jnq+hr/vgBTYjk2/IWNhWiiRxnBmwJoXX+NfPzlCiqo+9iQnpIp/D+D1kOj+weZJ2iTQCtoSmaTZw7SC7AbsBAmEkI0YjIqM+FXAeKtQ7JQP+uqv4vW9PqwJmkxQ3F1XYyr8FDvQHS4zhzCns8x73EjcJtL/tl/Vy159fU/PXbzwOpcgIX1+2qhhDejCKFcTzS/RDtHMGYuS00UvB7gr/PsVO4hw7kTOf
*/