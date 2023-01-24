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
lFjcxZbi+MH2kBJLSbHFXWEpGeIFteQeonWTalvscc3FFIqfxxOPCE/m0VAKFtNPxzn49Bu4huqjq5iP7HPuoDCQtl1Qk+9AjrqGEdUefPlgTc2O2A4GhmcZYnNCHe/eJGpHIjqlAcRrZTB+HW+RnH8y4nF7XE0O9VHpmWN45kSdJo92qNMl1/209AWtGEwHn+/7mDUqGD95xBJYty5kDjjruEI6ET2iUnhwSyEZrAmJ4NwfczQ5OXr1DjnpBRUK858er2ESNID7brXfR3PO3s4l9tSmgymH85zq8WAV9hioTL4lqFHNRgvc+6XtSa23l6FmieXpQUnxAXkDPK7JROBc8bJA1LgGpq5tkJbZD9UdVxLlh6bKrafK06fK90+1w2QtomYJgF9v9rF/s43pyKKZVKu7f63n/WvNp1rjqVatya9WDtbKT9VyT4Ky4YdMGPj9/bWQ/NBEdg6+yTb4lAOKDkPdntnKZCjJUHmNoVEVfpaR34K07yGA5Bxv9OkUHmtsvNtDLbozOGGBeJgDhuqWEmGTPSLemD49C3d/chLrvPeKFHWuVaxhXUTFgHrSdP94jEyCw+VbtkTI2atW5g00jFWOuTsTCZdhouL7Sa59ARh5qbOwfAIqLKrBUTdW2pyDgumcZ8QH85ITz+476qB2D0gUrjNa7caxzY0cdY9uCJecVSi8DFrtpkSi3DMpydvFUTd5/QOOuuSC
*/