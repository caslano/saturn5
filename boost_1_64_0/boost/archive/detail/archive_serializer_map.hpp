#ifndef BOOST_ARCHIVE_SERIALIZER_MAP_HPP
#define BOOST_ARCHIVE_SERIALIZER_MAP_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// archive_serializer_map.hpp: extenstion of type_info required for
// serialization.

// (C) Copyright 2009 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note: this is nothing more than the thinest of wrappers around
// basic_serializer_map so we can have a one map / archive type.

#include <boost/config.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {

namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {
namespace detail {

class basic_serializer;

template<class Archive>
class BOOST_SYMBOL_VISIBLE archive_serializer_map {
public:
    static BOOST_ARCHIVE_OR_WARCHIVE_DECL bool insert(const basic_serializer * bs);
    static BOOST_ARCHIVE_OR_WARCHIVE_DECL void erase(const basic_serializer * bs);
    static BOOST_ARCHIVE_OR_WARCHIVE_DECL const basic_serializer * find(
        const boost::serialization::extended_type_info & type_
    );
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // must be the last header

#endif //BOOST_ARCHIVE_SERIALIZER_MAP_HPP

/* archive_serializer_map.hpp
/LsD/9PA3wn4S4H/jrDyAy47tFvqst9rcdaIt399HXK/w8h5rX+OcZ7o63fk9pPTEYOnOy071MTjZdCMCj5fDgeXs8+JtbnWdFNSn0WBiePOWys/fRBlxM+ucWlJ39x+4m1TpYpOod9f7Lze38q/x/IJC0ZPvrqaN37PRfOPD3qW3rGZXyavVYNJpzpamB5cv7eUSbV/JLhOqeIdEnfz6aw3584WbHmomrlG3fjR2rbp9z63f1xPc0cW8LrOwPq2R8fKt8dUXlVrX91v3T27HLuQSs29ceBHypne7xreWtEms+xxx41VLXs1T3seFd1t+MraWztXsvvnoIXTTs5/lZ3v1nVdi/cbTjzb7T4qfI6gZkuzYbuSrzS7K6kujGxUcSiQM8FhisMMRzkcljgoHF707RhHXRzteP93/3f/d/93/3f/d//FDnsY8L9cIZapVFI7R3tHe4fYvkJlqkIt7ysQq+gjShInthfqxROoVGKlWiKXUbECiVQscqUkMqpZM0quUdNegjiV9iRJYmFx8Wy8+eFR/GDfsF6hEZSHByWWCW2pIUMYvR+/iB4JFJsPG6lYFqeOp6wpOgGfoBDfLlHhgb35tnQiDvrxcX02CgFSEEhtiy0PlcyxryAqRqJWqZX2wpKXIxNP5CSJilX8jXgof5X6b8TTkJMZdybk+LUTskdFHA1x1MThxh4ViW/oOgtkPH9xDK+rQMnzVijhp/I6a2Q4pDxvTRwvXKzghQjVvGB5Es9PLCzpdcSJZepE/SuxdnAWWTs4GRy92XAqoGsEsVNR1k4iig5y1f1jbd8CapG1qjA9H4GIUksSxVSSQKoR/1E5S5xEf6teJTJU6h/xyMRLjNFrftZSES9RIlNJBok9tLpEQUoRubmNbctWdvatXT06lvQ88pgBYiE3i8GRQUHa3+6Bwd29gwL9PEueb5UkTmZwwaZmprx/578U0o5t2NQseZZmlma80bV5tXmWXpYUZGOOVx7/0f9a0nH+hsM5zcgJ/3Z84pB/B0enNs5t27V36eDt4+vH99eG/OQ4RjAxMWGOn2Y/TXn/ruvbw9rBRdqzUI4EUazclz7ACS31hdCkhPWrVopTuBXsiqMx+3BkTvstKV4r+C3pvc9QulHQeVA8D06+KpH6ZB6myrDVWpkuKb3DgrVL49hZGtFVMZJeVSM6B05cS/YcjqzuJ1wN1q6dEV17jk6bnpDomAS1OpERndiITqLNH+d653PaBK8co1trJO46jp027hiTwvxpry3HxDC9XMaO/KO121vKsOyfl2LsKnIehl+wukoc3UtWV4HV/futtnjX1Tu8C93uZHLSTRKdIkGSog3XqGNd5DJpqlYWiWMFGqn6T/pfJCuTiPR6stL0Pwd+na9arH+1V800Y/dd7/Bgx6iIwK78kueDvl0VyYVjBx7PyaFk9/g/vbeXID8atdDYfdrpd/dp4/dncm8u8XmTxEpJbOof338Txer4KKkkpmhEAW7mpC5CfDrzfSM4egmjDwyO4Afwwwz04RFhgcEBhfYKnFoUJU5RcOrXJzCCtYtSidX0QFJnT+cpShijJ8eLhQlRagxo9fRyqRS3Zp2MkSXOFKVQShIlaoy59dsVM/LkFbFXigUi5EDOtWNGmhw7eZRAFFNElsqFCTp7jDC5+aLzIHSSFMqxEhQBikFrH8AP5od5B2Ew7kc3dSQ+gJtPeqQnVgrU4qikNtx0oVfTo6V2znrXBT07SuEZ2GuYCFx7jNTIJXNllAsnXC1O5BYWV08ulqTPyuLEGLGItobWUC8TJ+vF153cUG/0fAoBXdIGejKM+pU+SqhO0ddrZExK+noGG66eGVlKZHFRMqFcwQQ=
*/