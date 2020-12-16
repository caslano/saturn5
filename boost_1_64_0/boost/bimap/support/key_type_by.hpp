// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/key_type_by.hpp
/// \brief Metafunction to access the set types of a bimap

#ifndef BOOST_BIMAP_SUPPORT_KEY_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_KEY_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::support::key_type_by

\brief Metafunction to obtain the key type of one of the sides in a bimap

The tag parameter can be either a user defined tag or \c member_at::{side}.
The returned type is one of the {SetType}_of definition classes.

\code

template< class Tag, class Bimap >
struct key_type_by
{
    typedef typename Bimap::{side}_key_type type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/


namespace boost {
namespace bimaps {
namespace support {

// Implementation of key type type of metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    key_type_by,
    left_key_type,
    right_key_type
)


} // namespace support
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_SUPPORT_KEY_TYPE_BY_HPP


/* key_type_by.hpp
JlwC58JSeD4sg4VwMayBlbBO7V0OK+AVatY9DbRPkfZcw+He06AD+WizI+yu5nSYAIfDRDgWdoLTYbLm+3ikUf3tqv7GwRz1t4f6mw47wp6wC+wFde167SPDnbp3r13fVd2nwFjYzeWuSd3FR3DXW91lwTjYR92tQXaquzQtV3Z4Vqi7fbqHw9+1PH6g9Ww/LIAfavrHqI7PAcyr4Cdang7Cu+GncDP8J9wOLey/bwP+Xd1/JPVa+1Hgao1HkqstOlvr/UzYC87Scp4Ph8M5cDqcC8+G58ALXLolBfBS+HV4GSTsel/9toc7Itx3mdbPy+BEuALmwSu0Pl0JF8CVWu5Wqf9Xw9vgavg9eC28V9LdKS/yXQz7RygvZ+h+82dqfKfCLDVrO6PfusQ9QjszQevTRK1Pp2h9OhVOg3maTqe72hm/+jciQjuzQf27A/aGm2C26iINhL+CJ8DN6u8WmA9/DIvhfXAZvB+ugFvhGnV3I3wINsJt8Luqe3SXXr8XboePwR2qE/e4ti9NcAj8ldFB0G8fmK570kgZN+li7PEt0jZ7uW20l99Ge/4j2NsTS/oNQ18A2YdkDWe+OtKAbEP2IEXDQvUnmhBHb8KtLxFZT+JAjqMr8SySMsKlKzECgXnIWH5/A06DlUgDsg7Z2kJXogmzoysRUS/C6EQMhfORZS69iDX83qU6EVv4betEbIfNSA6/98CgXkTaSLdehKMTMR/zFrhmYCxz74k74taPaEZ2I4cR1Y0wehFZuY5eRA6/l8FJ8BtIJdKAeOlD7IJ5cNpDida+XKMPYXQhCuzz8DDXkkc5+hDrCedQzCXIfGQFslZ1I55Cgvvj7+L324hbTyJuNPb5nQYHIW4diQJ+1yHNU0J1I1aPjqwfsZHzW5GnELeuxK7Rjq6ENYZ0IB5unYk0zg1CWupNrEDWiv6EozvRS3UmpiE7ObcHOYAkjG1dd2ISv2cilS4dikZ+Z/F7PKJ6E+hMhOtLHIKv2URSTqRMI7lIHpI2LaAfUcRvPzJpmtGP4IHn6Ec08nu9Xb6I+33IbiTuYXQkkGlICbIa2YQ0I3uQhG3oRyDzkRXIRqQJeQ05jPT6aVR3InpEj+gRPaJH9Ige0SN6RI+v6vhK5v8zEHws5v9nsv//Kns8N9fu17NXKKyrKbSHCetqrb5cu5prW0e7rtUQouqqWm4rugPTMy0zv7HI5+wF3ln6grhGJ092YG79mXPnBuYlBHwiGLXOWsdP4MOTKt7jaIyJu8bHGnztX0OsvWtttXdNMI9xM+9xNlmLbOj+Hlndjr9n6NRlVZ81Xtf5m17jOV7jXV7jY17jSMduHC/QV6h5rHnfZIX2Fc7SvsY5sA+cq32q8+DJ8Fx4KjwP5hK/5h2J1ts7Etvc/7QbCV2fI3xtjjwk2M+0Gm5CnP4k774k99oabyNxedJfRD9R5D6iLYjTJwQRpx/I6QNahrTW55OHtOzn2Ydo346uceGxvkV4f4321bRtDYvw9SvC+mDcfS/a79K2NSra26+i/Siu/hPTdyL9JnGPR/s6okf0iB7RI3pEj+gRPaLH//b4Sr7/F4wbeyy+/+1v+JMzLaP/lqL68WN8/IY5sMruH1jp6JkZXRqjntKqPo267Wf2iOq6SnSifRP4kl+E7EZ8vhijz+IL1X0x+r2x4i5LzGcbf7uH6av1Vb2dTLGf4Mvl/4XI88injm6Cuh8Wtr9fOb/6ids4n+ptqT6OZXTm7pfrVcxdT7QuQLx0rWQvLePfCmsgdvORiPpWqjdwrdgdZfSvksXc0xfcz2Wia5+ESS5dglMyRSdB+k/GH0GnJz+CTk8m5wuMXoE7D3QPBXNN9Ug4V+4=
*/