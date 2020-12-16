#ifndef BOOST_ARCHIVE_POLYMORPHIC_TEXT_WOARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_TEXT_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/text_woarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_text_woarchive :
    public detail::polymorphic_oarchive_route<text_woarchive>
{
public:
    polymorphic_text_woarchive(std::wostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<text_woarchive>(os, flags)
    {}
    ~polymorphic_text_woarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_text_woarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_WOARCHIVE_HPP


/* polymorphic_text_woarchive.hpp
vyyL/4OmIfiflvxDhSH4n0Ms/t9C1N9lyf9bhxD8T0v+XdK+NZ4mG+UrJvkNqqj2JvQRcI2/j+NrfA3uPNn29fQVx9lEJGH6Q9+m5xSazIibAZzJ6PQtyc+0e3JAnsH5TALosrA5XytT//dxJat6G4H/b4zj+/+8Eg1QTxqK0Rl1C+ubKs+tcofv5PqEu12wy6HPOgtwc93Wf+HjukDFesTAxX4Xczi3Jb3xew3qQR8j1MOlRDo9alHTvOpsS5THi1hHZxab0MIMCtzWEjH9YPQlH2lusufI0h+MFQnPW2LPkbEiTnk5PzZSUAugpBQUJQJfHIRE/TxtmkWe0IqWLDFOi2ePZ8xJDGB5NmJ9j4bN+cRVFsMo+m0cQpHLdl8ZbyNB0QpOKkqHqdrLlAeBzIrnOV6Pc9WTNsJdAgFolN30ByY8THjpuUpA0TxOgeXJVn1eO7Z+hZ+1d2PEz1oG2929ni9vEiZcyyaM9ajyBaCrxaLROn3sNir8A1BByT4sQ9vd/uuxwgLAlgoAu2J0tPhGAwi7Vz/SHTs+wSwzT8oMs5Q5oL+HMnniz6D3afD7wP4M0k6rY+8boxK655n+DPpeyLiUPR71Mcs/MkZY3f0/Cj8qjay8oJ59/a5M4/1+5AIFj745Vt2A/btRvqnHKH9uQ/DRm2nx/9gihPzDkr/eEUL+Yck/r3cI+GfJb3NGCPiXYZH/jAgB/yz5Qx0h4J8l/65a9YMWd8rE9QYpKuaseJOJe9NcogeZSjdZrI/HHHK60mMBJrdGy6W+lwiPV/mqFtoiDHqzC/qEWWk+CM4CiM7hJHfFZk93crRVdDhjflSe8+Ftc+KR7LbnBSrgPrfaH4svLlxVWGLBaW5GMiur5gXW+yEgL9DyEuDdnw5znraTmEMiBtlmGMDqEzMZa+gtdGtqNEFX5+pZhmkVU+R0HcfWnRbIrU+3nspPQ/hyhwGKVCcbe3GeT+zI1oCth8ln6/kgt4ojTA9XCyieUztXWbKwIG44XwigKVRCCLLRrrKeknnV+axx79dtuAYKAU/n+F9N9dkJZnDaM90qsD62qQQq6lBKJ99Sd7bm5YsWxfHJ5TMUtElXePn5hFK9xL5TruhCXJEB0uvB84QrkjOSEjMk8VNOfEvvxYmZkvgWJWLwbUaeWnT+uB91/38n+tk7MZTm19rFkMuOL3IDSQLasP2bUd+TQP5IFqmK+yBaDapIHFce30FagfMTpR8bXzrUbhF345UXsafDRN0T6orEEe1NocaQ62J9X1H7D+8OYpRblq/k6FrVyUjSFfzrH4QfPyVZV4cO7BWKf36uKqXtwQlOJjIII9l/Lk5xGgah3BS+g9+usnwq345TY5H4KicWUKIjn6YxUqbxGNI5ytmIxvLRDXlyVT+llu5KwHiYMfOZyIwB9DsstBvxpbPBP3fkBSqHZuQ0CXhb5vkOR3r9G8MCyILW+k8svMFG4NSPxFgQL53KA293cflEt6W8WRxlbBmRXVHe2xTfs+wZkW3wwzNdMppZMyIp41zu4OeR0bYQ7UcE2//ZMpw7H4ki/5S1y7eylueTaKnRcYE9VPtRVN7G7R+1lJ6L0aD9xpSXaQ0faZnWYPzwTJWMq66OCmZMxg9PvmS0pRptVEaCWT0sIzKCqneVUs8/jOrJqtRj9KO9KvV7+tGMB2OdbPnVClx9IOBqcgGBqxcBro7oL3cwXaG0jDVcobSOrYMafR1TzxXK6fkK1c06/hn8d34U/Z/F9H+foP79HgStSADNkd1DeEfD1CokxBir0DymzipUN6m3Ci1GmKEe5b2UryXR5vKfKBnN4xV+6xjjXYyWcbvKjlKj2MmxNgEHd46IhiY=
*/