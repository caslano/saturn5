// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

template<bool IsSame>
struct translate_int_type_impl;

//
// Template name: translate_char.
// Description: Translates a character or an end-of-file indicator from the 
//      int_type of one character traits type to the int_type of another.
//
template<typename SourceTr, typename TargetTr>
typename TargetTr::int_type 
translate_int_type(typename SourceTr::int_type c) 
{ 
    typedef translate_int_type_impl<is_same<SourceTr, TargetTr>::value> impl;
    return impl::template inner<SourceTr, TargetTr>::translate(c);
}

//----------------------------------------------------------------------------//

template<>
struct translate_int_type_impl<true> {
    template<typename SourceTr, typename TargetTr>
    struct inner {
        static typename TargetTr::int_type 
        translate(typename SourceTr::int_type c) { return c; }
    };
};

template<>
struct translate_int_type_impl<false> {
    template<typename SourceTr, typename TargetTr>
    struct inner {
        static typename TargetTr::int_type 
        translate(typename SourceTr::int_type c)
            { 
                return SourceTr::eq_int_type(SourceTr::eof()) ?
                           TargetTr::eof() :
                           TargetTr::to_int_type(SourceTr::to_char_type(c));
            }
    };
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_TRANSLATE_INT_TYPE_HPP_INCLUDED

/* translate_int_type.hpp
bF9vdmVycmlkZS5wcm9wc1VUBQABtkgkYK1V72vbSBD97r9iTjTY+SDJsduLe7FdcrYTBG1SavvCgcHIq1G0PUkjdldxQ7n//Wb1I6WJQy7HgcHSzs7bt29mnsYfvmUp3KHSkvKJc+L1HcBcUCTz24lTmtgdOR+mnfEvrtu5QSg1gkmkhlim/ERAnKpkhKApQygUFaiMRA0U80aEPaXxcvnRRr6iMFWe9jqdIIddKdPItRu0TmGfYA57BBGmKWS6CtoD6ocWhjcUodYg85qGPVB3KjK7e2bHrKtjZ6U2lJ3HBtUnKRRpis2MsozyVahu0eiW6r3XcV2+3+eG34oo1X+0cry1crBAuZ44iTHFb76vRYJZqL2shfUEZX6Ed5haQL+h7g/6/aEz7QCMA4PZHGOZS8Ogl4rKwq5zZJYyp4LJ1++88lkhExOoNakfOXp61Hsmcnw29p9LakFt7erH61IBFVW0rmCj/rZZ9BJgUQUVEiMr6M8lMtTAvOktKS1txlyq400T3zyAeBAYLpFIy4g7wRbU1qQ9mGuYI0YN1pMSx6SYQVaERu5kKrlCsMRDTO3GjBTySTF5DZwtZnPtC1ICo6CmcWH7bvoS8bOj3tMsK/EBrKfqzglyMs2MIKxzyXPEHZ2EKhTciaDR
*/