#ifndef BOOST_ARCHIVE_BASIC_POINTER_OSERIALIZER_HPP
#define BOOST_ARCHIVE_BASIC_POINTER_OSERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_pointer_oserializer.hpp: extenstion of type_info required for
// serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/basic_serializer.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {
namespace detail {

class basic_oarchive;
class basic_oserializer;

class BOOST_SYMBOL_VISIBLE basic_pointer_oserializer :
    public basic_serializer
{
protected:
    explicit BOOST_ARCHIVE_DECL basic_pointer_oserializer(
        const boost::serialization::extended_type_info & type_
    );
public:
    virtual BOOST_ARCHIVE_DECL ~basic_pointer_oserializer();
    virtual const basic_oserializer & get_basic_serializer() const = 0;
    virtual void save_object_ptr(
        basic_oarchive & ar,
        const void * x
    ) const = 0;
};

} // namespace detail
} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_ARCHIVE_BASIC_POINTER_OSERIALIZER_HPP

/* basic_pointer_oserializer.hpp
80noEqrCisM39/kTWz36z74tY/YtAfo6uuln+P/wWXAQvHzz4vWbFy/cjPdXU2Lis6NIwoXN/G+vX3191by9vro6H74fjC6PfgLoPjVoswlEPJLcpv3C1OKq/k8OjJs4mBz91EzmnKndhZ8Qw/rSoObLspkx/c4Z2s0YDr9rxuEbP0xktmymffny35r3889u5vnJ96GYRG7GZHCJoOH7ZkFBUF3IzpxeT0bj75tIlyYKo1E21UieWfVAVoLrd3FjURs+4kISNy1R64qp2jlhISttSz/bnCvDMC9pFQTTYsDt3C6TsK0inm4pXFG+/8GNOQ1aIG66345F2SFX2OKOYWqAoxCWUbBuclNZcxEHq4DGh3aKw9tQfUIuicWp98iBSeSajKEKloHz1ltnkpUzBXa29gOh9ZyrATLBzXaqCOPaeK0F3HH872l+Votes2anY8J1I5mJG137jeZySnjGta8kkKxEPPoZlmvE2fQEaM46jIZgh1xS069HdUzTWFKsxcz6rX1bbKOp3mNT7Viov0sg/LTl2Nxll2GIX/7PmKbbfLvzMNo7hrF61DnGgXPL1ewYGjESlAhRdE/AbeBC7HU083MOeDo2wDPsCVvn/DrbKea2bIz2TFfwksqZ2LMnyKTYF3fUVrJb2QpF
*/