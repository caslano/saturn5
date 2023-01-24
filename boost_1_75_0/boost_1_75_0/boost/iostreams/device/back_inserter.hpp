// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_BACK_INSERTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_BACK_INSERTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/detail/ios.hpp> // streamsize.
#include <boost/iostreams/categories.hpp>

namespace boost { namespace iostreams {

template<typename Container>
class back_insert_device {
public:
    typedef typename Container::value_type  char_type;
    typedef sink_tag                        category;
    back_insert_device(Container& cnt) : container(&cnt) { }
    std::streamsize write(const char_type* s, std::streamsize n)
    { 
        container->insert(container->end(), s, s + n); 
        return n;
    }
protected:
    Container* container;
};

template<typename Container>
back_insert_device<Container> back_inserter(Container& cnt)
{ return back_insert_device<Container>(cnt); }

} } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_BACK_INSERTER_HPP_INCLUDED

/* back_inserter.hpp
LL4mZnh/CGO095p88B90PZvyoKuazaAFKAFUOtniS9ujfnDbbzpolFjyx5naAbiMh3KGvcGdq1brMN0LP0DfUbTPHgLh2reBm1aQZwquUeD4BOQ/9GoN8GPA5gnQ3utgqFCt7Lxs1jQfqIUcGQUXurPdbc8n+Rcjn4p/0x39eT68viLD84MWvhFrDcAM1nbL3zwkUD7pt3YkUQJUQkw1rzapXnzFNxjfgxGMeIB7zgu2JCfixNOISF1iFHcLB05jtK5S/Fl+A7sX1oqFsob9cjOkqFOqfc3Zqq5tYUdHy43lLmuJx8eChGs/f3b+6m7p70+0mGH6OhAVPjfToxLEtRNCjUsaXB8eo2VM2qII2g0dCBUMP2Bc7YrykRULCCIx7Vk+a5B03qgprqN3U9xqbeXrWpMhnHIuiPI8JqS/uHmvYGYWqJv85/dOtADpQXp3f+GixZc+HoO/OHoGspp5aZS2y1PbUu7c5OSIGrqILhh30p1otMCVuiEf/LwUdHX9FFJdUhc2Txy9XVyba2rtP9rNJF4QWUGulQAsVTcKLZvo5ha9wDbho6hRoS1MX7dXBVEnmOFl2IawHORE9SNuefa+/ewFlZPTKoxX0tNuOLesSOzmGroXw4onSb6Vd6S2bm4896l1sBoAsFzTzf7IuVhT2zKk22qbtmDkZmpbXdsqL1023zMS4jfTRdlEv252/66/qvXQnlAX2cZK
*/