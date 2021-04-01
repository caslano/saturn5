/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_NO_LOCKING_HPP
#define BOOST_FLYWEIGHT_NO_LOCKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/no_locking_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>

/* null locking policy */

namespace boost{

namespace flyweights{

struct no_locking:locking_marker
{
  struct             mutex_type{};
  typedef mutex_type lock_type;
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* no_locking.hpp
HMVPZwAswMV9rIUinZVrXXn1D6wt6XGg5PyzwRzBTzQ6lQ2VlPk6ODi9o/p4xyxkk0Y2DvmRevq6OzCWDumTGt9UYx4mgHs9HDenAtIJD6evjz8PyDxpZQk3iVfSuJk8pbbVCOenaw2yuOuy4nAPOVqRf/qRGv/2ZSqqYKOJVLOWvAyouAU44VsJopHVXlMiNk94jOgGpwdl8vU3QKq7lushQwBbHFiCsOJLNbxKJWlAaJ0o2NazxbRY3wNDoIkzZuoQ6lcibR/hae3KT7KA6NeOhCn6iFLtQ7zpyHjEmgvvE7jx9LwIvGTHvB3PO5baRmJGaw5Q+wmuMxODqcGF9p2ELkugUqXtkDqVY98j3s5PAMSGTuSyUbQntG7TPoattN5/O6XPrPkBst6QFjxk1OPg40zmhYA6X27ZVFLBs2VsHFDtDNSlRpYiP9m6BX9UGY2MwGENf89TKWt0iEDXsFvDiWUKKCreSf5LFatuuVAv+3dCS7v9EYT3ugkYGf8afzHa7iHPxekdFIW0CmVXA/wbfkTn4jLcBFnBGRWfd6f26a/VGY5mEMxB+w==
*/