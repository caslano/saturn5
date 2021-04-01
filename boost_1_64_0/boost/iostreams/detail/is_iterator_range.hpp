// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED       
 
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/bool_trait_def.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { 

// We avoid dependence on Boost.Range by using a forward declaration.
template<typename Iterator>
class iterator_range;
    
namespace iostreams {

BOOST_IOSTREAMS_BOOL_TRAIT_DEF(is_iterator_range, boost::iterator_range, 1)

} // End namespace iostreams.

} // End namespace boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_IS_ITERATOR_RANGE_HPP_INCLUDED

/* is_iterator_range.hpp
SrlOifMpkGuO+FOPCNFYJgqRsXT5kne/ijC8la8fYQUJSR5z3/Tw5ur0HdFfqn5oDynuAp52XwLHIeeLnYHD5uXCckhf6p2v6xeEMgnKD1i7L3ORZheE4Em+qUNdUxp9Em7S1MehKyml7KMQshP9nUlKfVbRAgrGH7UjSOJv4OYOWEJodU+WOXOaMpQbopmTJHUBsq4IYYctSyxPtPLhZsAJm97PLVGV7yHJ3Y9seIdihnbdRXvPmpXJ7F0qUd/ZpSe5EJdMFZnVD5sdBKM/AKyLeY3P4kNuBecFSk9ZmDsAWOI7J82Wzd9ZeDF8MDGdDBvPMMooIoIJvgNn5fM2yN4GvaAt8ne4Ie2cPoTMEA4+zELBB/IKC0dAnMJQ+5grEuJRGbv4hwzv/g8JtGL2yrblnbFDrfO75kuGG7T2KSO0vfkGp0WGOTo1H+ACAi7jPF20GcCV5Yl5uaAUNLRtCIUF4guqxJ0sixPIyjYiaJQIuFlQOJZKcLP8HmndPDGVI7e0P2Vr3OFoyWPES0aT4j7RdLqDKmVDqs1diEhdKU7IgFnZuhxh7vZMUQ==
*/