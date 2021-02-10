#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_WOARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_WOARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_woarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/xml_woarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_woarchive :
    public detail::polymorphic_oarchive_route<xml_woarchive>
{
public:
    polymorphic_xml_woarchive(std::wostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<xml_woarchive>(os, flags)
    {}
    ~polymorphic_xml_woarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_woarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_WOARCHIVE_HPP


/* polymorphic_xml_woarchive.hpp
7aaUz9oH4+opsOgO3UfSPWAAzk/5euC3gH8Es2yDDjKWJsg3HgErH3fsu/I7WcCjWGpp3VZa/awtAHHRZc5KuJlbhCVoR5jKJZZ5rYKru10waMiwirJLG/6t2qyUlfNaZq5qrH6ReM1rrNppL/CxTst/mv4kz7alwfqtloYWV7qOEvZd66Xb1ucSLqTNXeh0AvYrC0fyndAvJkS4yOu22lpZtHUWgZ+yfYhA8gs5jhzDKfIDMcQeZwkvXk+vsOgBT8g2nQOs5edP9yfLQdwVcvUebx/my0cK5PGP20+Lu4fZipwLGtG6tODg7ePrx6sV1wznZGusFabObJtrOrVtNl7hY4m44IepOSumNtEgFPJeB7ZMj0uXPiuLtIm0lVDAo5QIhDN3IZi13RG2GQ6wKrLd6F3eZnymawiphC/5g3UolcFFWCuUsdIUonZRNsmgpuedt1M5PuW7tiv1hALszAo6oisXRcnGekfQd7gfJiL8RSb+n6mgHhE39/OZPENpz+azc9pa640D/lHLVKZDa+Bd5mpUXqu5hUdADCiI/wVh+Q3CA0rI5akQQCsruVVohzzXORXM2+nPb6dXkh7hxY4LJDyNDwPXFWjBDn1qYvq4kOs2SvRR9kSLqC3XO5nrQrU28iqmVOnAlrSe
*/