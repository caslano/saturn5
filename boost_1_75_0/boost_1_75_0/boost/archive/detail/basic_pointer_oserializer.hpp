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
s2uxCL+M8PhnX7zEbJvbNvJnuacIv4Jwj3bNz8wu+ZasrsMTRPgvDFHm9Z+ZU5f+vvXHU2NF+FUi5+deuszsmeA1rMvXX4TzCC/u9LvCPPF8Y6d32EIRTsaBSva7K0yhW4WpZZ+fCP+VyDNz/S+M4yfT1ssXTxPhFoQfegfqWfPnqwvTKh8U4W0IP/DEc1eZaXtkV8adni7CfyP22TyBZ/7FqjNXvC/Rv4bwns43eGbf9pVfPff1YyL8d4ST8cnngb+ODhkhE+HtRG5UrZlZ+PQnl1rWiPKpIPD26RN/Za6sfuyRGYHzRfzrxA631fzKTKx8K/LXlnkiPoH7RTlamJcK77s89cFhIv4NwufzhRbGuv03v03LPUR8Am8r+NHC+L/4Re5dfy8R/yZp7/DQNuZCas4wPluUcwWBryx9v415MOH+G6Wekpw7SH+8NOo35njZJ+k51RL/BH4sLu835mz12IjYYkkOnQif1X3kN2aucYJf/sRZIj6BB//L6xozLO2rR74YLtmDlfQLVek1Zkdn8YLSPXNFfAIv/aH5GuPx/Q+T/eVjRPwuhBeoPH9nti8NNHL6RSI+gTePKPqdqS6mftjn6ividxP8j02/MxnpmV8/0CT2owoCnzXWuZ35emvml3v/Giji30J41tcPtzMbrrt80WyV5E/gXusi25kVmoT9o5qXi/i3iV2NfbKdeTDpovzkUo2IT+DB
*/