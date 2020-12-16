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
RpbYz2QwW71xmbZaQ4GQ/u61WvfFV/quxL7JqmLrI0ogFIqZbydwZXxYmpW9/fzCyDIdK2vPG0VnjlcYD4tqMvKRWkbmBhOZvnY9OYruz6IkCp6+HqfDqqGI5IGrpz+xp5Xpb5XSNwWdLJcnaNik6NevEwUJYiwpSpRMOJ0m9zzkHPTnHbhyIv7SAXgvakdXsr7swJFJZevLDjqZfAKVXCn69qRCO7rOueehk+XIpAcXq/VlwjFP347sFioqS9SszGSP2z8XVg1dZ6ykk7ntRRSHfVfYb69WcLPH1euSJ44uT5IeRyYxDfpfnRVxdLlzEwoPDypSX6RN6r5My7Rj+pIp/NB9alMQSyF5dZH7aWKMJE4j16gouvzJ10RRBxKhrjyAbyzdbdJf+iVKVq+UJ0CpkCgYJdO22QwwHNMJxqTSH0v4TSZgR1cHsSJxjejVSixso8RFJB28s8HJv/aL4bSx7hORnPVpfBpUQ39gRV+vaztER2lUbEyGGSqpHUW+haJzDDtsT4Oc4Eriud8vxidG6U97IsR4OdKNktIvJHL/opiqI9fGiUep8LlR+kOpIr37HTkBXS6/NYYd3RVov9vJja/SCOMphmv2+7f6mwfhNLq3vmLQzWiLy1g481cYWAsj4QlifLJZihfV9PRMSf86ngztTSpI1dejClBZdGFp9UkYCJJAiYKKxbdrudWGcO3X7QeRUtDeCAgbhQ2G+31So+lwwxPpti0y0Os+dWQYm7nfkezTrJO2RaHrKQzvEe4dTm/WYPrnEoxX0H/jq3N/9N0EbTw6/78asFUqzfiKo+z331ax45bV7LiN+IXOcg07Ht7IjnM20f6vHVPdbJsvSX5VKtxvDd9e1bZ8D1ZmoSAy11UzY3yvY+x39Pay47I9bH6PFM2v1352/Lab8ScT/9cOlUjRt9ASlz+uhxlnGncV2fIvYPObdobNz1k2H+eK5if6HBt+ia0f1g+9DP/X5c/2RH/QbpBvOpJ+xq3Y/GYfZ98DvsmO12+x+bpTNB+TWTn0AeNnE//Xjv74FH0rZfqJkv1dOW1+yT24MMPc+wo++8+Wh55spm3/J9jvKj5l28EzNt/P2XJm/bwXrPyK8fOJ/2tH97volPFKtgRZVRrOp5ix9c+e3+sNW55v2PTfss8f79jnjveM7/WFbc/E/7XzDwzi485Af3BZWdJy/Bd79wIPVb4HAPw/75cxGOM9xhiMMRjjzRhvqawkqZWVJEmS5HV7Sla2p1oryUpSSdbKSpIka1VSSSVbVpKkkiTZkuT+yO512+5j7/3cz331/+x3/87vnDlzzn/+vzM5/uecsW2e3Ix8ATDkv9ufsZfqv/s5SAigXgl1/FgNFoKYseUWL4uF0V2C31zH9kt+Xpz4fXtkoj3fTuzn6MR+T9RaGPy7foN7V98dr3+7vpm/c31n/7S+3zVuEv5dFrly1cSJm/H+FDx2ifOfhX/X8RnaG178F48PxLH9m3R/UDnyu+3VmqhNJuoFE/WKifrueA2F8tf3j/BL/2+YOP5PLP9soj5G/fPXy9HeTV+VmVhOBv93HP//NE2uPz0Q+oCyVJJ/8fPkb0Mrha++ertyYLldvyU70HbQ61DTxgdFCbNkvTnL7IXblhCywquchgtvJXFWcdczVS/f9UcYLA5PIJLIFCpNhi7LkKXiyRQGnYiRQVgaiYCjkWUQAcugU2VxRBKGgidRcBi6DE0WSyRQ8YhBpiACCYunMmQxNBkiGUfHyhCpiEbG4ekkAgQpMgQMQ5aOpyISEUfBkml0GklWBoOjEBADTyZiqUSGLIWGQ2QZLJ2EwVMJVCwZTyJiCAwaRRYnQ0d/Y/v+nksE/2o=
*/