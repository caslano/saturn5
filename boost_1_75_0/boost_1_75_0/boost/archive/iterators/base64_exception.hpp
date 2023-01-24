#ifndef BOOST_ARCHIVE_ITERATORS_BASE64_EXCEPTION_HPP
#define BOOST_ARCHIVE_ITERATORS_BASE64_EXCEPTION_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// base64_exception.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifndef BOOST_NO_EXCEPTIONS
#include <exception>

#include <boost/assert.hpp>

namespace boost {
namespace archive {
namespace iterators {

//////////////////////////////////////////////////////////////////////
// exceptions thrown by base64s
//
class base64_exception : public std::exception
{
public:
    typedef enum {
        invalid_code,       // attempt to encode a value > 6 bits
        invalid_character,  // decode a value not in base64 char set
        other_exception
    } exception_code;
    exception_code code;

    base64_exception(exception_code c = other_exception) : code(c)
    {}

    virtual const char *what( ) const throw( )
    {
        const char *msg = "unknown exception code";
        switch(code){
        case invalid_code:
            msg = "attempt to encode a value > 6 bits";
            break;
        case invalid_character:
            msg = "attempt to decode a value not in base64 char set";
            break;
        default:
            BOOST_ASSERT(false);
            break;
        }
        return msg;
    }
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif //BOOST_NO_EXCEPTIONS
#endif //BOOST_ARCHIVE_ITERATORS_ARCHIVE_EXCEPTION_HPP

/* base64_exception.hpp
53Vfzm8ZBSEzCAUElgZBCBfpATKAdmppbXSOA//RuTs2iOW8s4rnwBBvg9gcY7lmGGyT03UQ7TY2aI4pSbRr4m+DAAGsv+n/Bh7uWe4CI8ZxF4Rp9W7GqHj/CeUu0fw7seBj87eBUv2209WrLlae0l8/rLkkM0at5GfH4pkKPXtl1ZqfqzWXuI1aEqNtANa5m5CMhMYuC9io1cnRo9VcsDiyiReMIbvx5Ba1t8HkwWrOGMNo/oFYlIv+MTZ5pTE0Xhxzt9ULVCHAHrcHfPpt9T6nqqyuO74BJsSzzHj8KpI5B8dYoQ9w+hbD4YRYY5SW39OBUmupjo+I5SLO8DkdZJbl9Bd4PKRzm+Zn8xphYilr3qa5BFVBFqc5w8bT4M5LfryQveoiYEBTRvbjr558v+Ou6PPsFe/Sc+ycvrXIBXOcxbjM0DaLW6UQFtPK3X2afM6z4V5KttTLveqUblmXAw5kuiXGUIWWO8JDdAxetn4G9xxZdlvp5c7JVtj0Ckj5wfC4wqZ159xxQQ2Ks8FeSg4UCHYAsZHSUK6i2AQvFVD3gun1OM/SJGhScrEIm8U9RXNL5AiAgm6cgyP8BfwZwIlHQHfZY1XndZOnlkLOEiUguRki5DLWo5FLAAiWCW+B4gruhOcyOfpUC6s5iODUELJYxkZHc4eAOTaM5o6w7rwjvgpVHk5xz+wCQeicbGq5xdGmTuAg7K3Gd7y4
*/