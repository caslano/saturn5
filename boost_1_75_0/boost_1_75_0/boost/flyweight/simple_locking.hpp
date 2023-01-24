/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SIMPLE_LOCKING_HPP
#define BOOST_FLYWEIGHT_SIMPLE_LOCKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/detail/recursive_lw_mutex.hpp>
#include <boost/flyweight/simple_locking_fwd.hpp>
#include <boost/flyweight/locking_tag.hpp>

/* simple locking policy based on native recursive mutexes */

namespace boost{

namespace flyweights{

struct simple_locking:locking_marker
{
  typedef detail::recursive_lightweight_mutex mutex_type;
  typedef mutex_type::scoped_lock             lock_type;
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* simple_locking.hpp
Dp/Wb43RZKk7A/a4zmeEc++P8bwAGy8egi8vsqk+EZbaS2OEeRIxcFCykryhjwye4G2QCiGpcbJLpBi5uFaF/E7S3pa2gkV5f5DvePnw5KPY7vqePfUwvcBsqYkz8yryVBKmQvvuKvyWQlGp9UyFevb6TdSzpTSwklNfaGt0/LBxxw+1WuT4YeMISOxxKMePI+j4UYgCKBEiwqjE4ypR/kKxrjqYaapvBX3T7o3raggcmISBtyCght1bZAqMhxS6VWmbjm/r096DtnPn1HGnVAqwImM+ZZphCTtx2kEhCkqCvL/Xqhbmh/6bYYxGReKgKZGmggZ+vTUl3aS2ZRtdW4KDR38+jfS2EPYrXS610NNuFu4Hks2TTeZ5Jlv4HgNiWiRJ3opUHLA0XHOL5UPzTjThsNthAvTHH53esmx7/ZXQK3wl2f6KrjSN78Rt1++4xjobJm1FhW+8yDUbgRY7tGSaBILjcybyj//l10yB4Di8K0E4fvEbLDLZjPYXQTgWeS9CCMftBOHo8M0ACMcLXRdxCEe23H+Cf0IQjkdcyQ7xgQJeO8h5lvPdv8KsTycqGT2T2K1Ab0RteTIue3IpPiQA97kfJMzG5jYcqzFVPyOdvFU/Ix1T43PqZqMsVoQuaJUNglbNU6hFr8GhNawebOQFLLuPD5BCxdr3KjMpMdl++YJ0YXb4rjnT5ADTFwirERvTTc3PsvrjSYNC
*/