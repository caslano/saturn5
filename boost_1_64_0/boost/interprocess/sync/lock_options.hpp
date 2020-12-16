//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_LOCK_OPTIONS_HPP
#define BOOST_INTERPROCESS_LOCK_OPTIONS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

//!\file
//!Describes the lock options with associated with interprocess_mutex lock constructors.

namespace boost {

#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace posix_time
{  class ptime;   }

#endif   //#if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)

namespace interprocess {

//!Type to indicate to a mutex lock constructor that must not lock the mutex.
struct defer_lock_type{};
//!Type to indicate to a mutex lock constructor that must try to lock the mutex.
struct try_to_lock_type {};
//!Type to indicate to a mutex lock constructor that the mutex is already locked.
struct accept_ownership_type{};

//!An object indicating that the locking
//!must be deferred.
static const defer_lock_type      defer_lock      = defer_lock_type();

//!An object indicating that a try_lock()
//!operation must be executed.
static const try_to_lock_type     try_to_lock    = try_to_lock_type();

//!An object indicating that the ownership of lockable
//!object must be accepted by the new owner.
static const accept_ownership_type  accept_ownership = accept_ownership_type();

} // namespace interprocess {
} // namespace boost{

#include <boost/interprocess/detail/config_end.hpp>

#endif // BOOST_INTERPROCESS_LOCK_OPTIONS_HPP

/* lock_options.hpp
/0mDSf//2Gl52eOyR8N2X+6UnOzR2WPNNgC6sW7+McRLDLOyJ4+b4tW7343D2kjuSN/ieSvnFy4oKC8qowC6w92FPd67Tf6nzhiVQ2EUzJ9bNrfI0P9/ysoj42GevkMEz4zpY6dNnpKXPXpsc3cXuXvcpo0dx84eu4YLEzRDR1auwj7AVqQzbjntt1QIReqm3+xfbyT8h6S/2UfvFcK16G8+5sdGQG25n3SGaCeg92D/+ptHKOwEVCGNGf5k1EJbAUM5vvcUtgLuFGf6PPEZhcrHN6gs0pIC2GsIoywQrlEWgzh9OX7sBDSV+6YPgrQt/+oh/vXTP6OwD7Ad8nA1kwdJvQV6s73x5ClsAxxFvqo88chGb9JhfiQxgJ7i0OTuo8P8iMI2wFE/tgHqy5ulL0Td5UWD/cs+Q2EbYIc4B9VcJmHqLN8fpc6bxvFYOkwteB0W9lhWI63HKH84PVEIHTBF5Jnj5j6wrbXcF6LeNyjjlmVfGKDNNYRR9oUK2xxH2/qxkVLeLI0tKP+4If5tcwyOtpb/XZBpU3PZhFEHvHXtbYUtgXvEWLSC4pKDnakMDiX4LQP4C6kMfPo9hGtpfxPa+bHNUd4sfSHKPy9A31ersB1QLcae5jJpoey9Y9yYGI/DJlBH0B2gXWLM8cRDB+g8hT1n8pQxY+eQQis/eqySgLPI31rtBrUuXoQrz0q85jlrsWx+oepcBvOq9VBJ/XDEk644S+Yb17rOdNapwKxzq4DcK7D3wOGjh+pV1j0lrhcl2NPxF0gPlchnMuUzoE4xqb/UadXp/YD4U4H0su5869zD0y7u8z83g3/7Or21Cvs6vbWKluv0vq8FOr29bWSTwsbAg/iTKuVkzBE0r67eAPJJDUE+qSHIJzUM+dSEIZ/9CvsCD+FPlpSPHMdZPnsCyCcrBPlkhSCfrDDks6cF8vGOcQ0K+wKP4E++r3x4nJMyejiAjPJDkFF+CDLKD0NGD7dARt461KSwL/AY/riljORYxPJ5NIB83CHIxx2CfNxhyOfRFsjH21cfj7fqmj6A8GooPaRrWtVXB32Prqmwr2u6pqLluqY3d7anF70uwZrPJ+C3XuZT9rU23k3rQ8hffRj5S0uyl7/qRGv+nhR632X+TH1l8HfAxhDy1xhG/o7Y1Pu+SqG7/2nRmFfK/Pn2dcHfdbSV9vOorWx5HgttluG1Ct39z4r5gMyjqa8K/h6RGkL+UsPI36EEe/reI1nf+xTWfXgl8Dnx7MZ4Q997YUkZFiE956Q/Twh+Tlr45TxyfwTv6jyCN7Be9wxyT1SckWa/6rm8PCNMPF31Sdrjat3uNyrshfFcPp7chuvDtA8MPYbJ/CyW26oGHdvFC5YZehMmeOLTSF8BImlKQYgJ4pxxjDO6Pc4ZJzmj2/k5ZzyU/eR28rwjOMqjIhyJMRdFdXLER0U6Osf0jop3xMX0xdO4qI6OiKh2zhSMoYY+8RHx1neNGxIISb4nqexuLC8oKjXOdHvke77uzfM8uj+CM/RrAurLLye+Wj5frnM5JeljxTNu4xrFReIx5LON+NYodemvILfHSVf+p2IdFR6WkD7TFVAQuYMOaCvPZzN/DviLyI6he2Pz89nEx/ItA99SOiOeEUj3M8sxuH5I71lrtA3VWWseD9EGWqBD36sTOo51e1/qgAyAw4CviXm3px8qXla2eF6hPxt86nZKfn11FJQjHM3QabKf3N+ISMMO76ERW1XtF2FY2mDBkGUwzqOaU0l+vzp6v3OzcB9q6Og9Qvy99STsVo71qVdS//Fs4unqKMIJyY1Ip9XvSaO+F9CzLo5Y7qc1TWRZ6iTeSe4nIm6Hj2h9Os4w5WrZEZM=
*/