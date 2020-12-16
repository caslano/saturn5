#ifndef BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_HPP
#define BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_unescape.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/assert.hpp>

#include <boost/serialization/throw_exception.hpp>

#include <boost/archive/iterators/unescape.hpp>
#include <boost/archive/iterators/dataflow_exception.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// replace &??? xml escape sequences with the corresponding characters
template<class Base>
class xml_unescape
    : public unescape<xml_unescape<Base>, Base>
{
    friend class boost::iterator_core_access;
    typedef xml_unescape<Base> this_t;
    typedef unescape<this_t, Base> super_t;
    typedef typename boost::iterator_reference<this_t> reference_type;

    reference_type dereference() const {
        return unescape<xml_unescape<Base>, Base>::dereference();
    }
public:
    // msvc versions prior to 14.0 crash with and ICE
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1900)
        typedef int value_type;
    #else
        typedef typename super_t::value_type value_type;
    #endif

    void drain_residue(const char *literal);
    value_type drain();

    template<class T>
    xml_unescape(T start) :
        super_t(Base(static_cast< T >(start)))
    {}
    // intel 7.1 doesn't like default copy constructor
    xml_unescape(const xml_unescape & rhs) :
        super_t(rhs.base_reference())
    {}
};

template<class Base>
void xml_unescape<Base>::drain_residue(const char * literal){
    do{
        if(* literal != * ++(this->base_reference()))
            boost::serialization::throw_exception(
                dataflow_exception(
                    dataflow_exception::invalid_xml_escape_sequence
                )
            );
    }
    while('\0' != * ++literal);
}

// note key constraint on this function is that can't "look ahead" any
// more than necessary into base iterator.  Doing so would alter the base
// iterator refenence which would make subsequent iterator comparisons
// incorrect and thereby break the composiblity of iterators.
template<class Base>
typename xml_unescape<Base>::value_type
//int
xml_unescape<Base>::drain(){
    value_type retval = * this->base_reference();
    if('&' != retval){
        return retval;
    }
    retval = * ++(this->base_reference());
    switch(retval){
    case 'l': // &lt;
        drain_residue("t;");
        retval = '<';
        break;
    case 'g': // &gt;
        drain_residue("t;");
        retval = '>';
        break;
    case 'a':
        retval = * ++(this->base_reference());
        switch(retval){
        case 'p': // &apos;
            drain_residue("os;");
            retval = '\'';
            break;
        case 'm': // &amp;
            drain_residue("p;");
            retval = '&';
            break;
        }
        break;
    case 'q':
        drain_residue("uot;");
        retval = '"';
        break;
    }
    return retval;
}

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_XML_UNESCAPE_HPP

/* xml_unescape.hpp
dDvR0mZFszrEKGn/GXbTQxZXFJN559Y9cNJ7zKYMXS7oZakjMcCRZh9S5qnbBLm4ajJWxWnjpOsKHrknhtpLL2JyVQyd2NjIv+jU0LaIRzBx16BZiu+ZSPhasojz4iKi6xFefppFfVpMceYjWGWuPU3M9Kadpk2o1j/EIvuHktWZapr9x4BeNGTzKJMoGMq106klizFsfRfdzbsDd7VpWNL4CN4O2kytPpYmNNTx6npjEpnnzUKOZeKvgCNF6tylcDtJRL64g39zDBG62QMxJfcw5FgfmUocgciWs0hV/82ORLVQeVcRO/IgDyravZjY+g0+ogIewmfQ7yw/2ntGGtd9unnwmNmUFJ+AVy934M+U2Wx7qBbmrtSC+4vn1I0EJP2SQvGhLzi27wIFL8hhuofHUay2FlugVozrbyTJ6VQK3XB6Rs7xhbBY1U2vDlpQPz/Ds8psyMRCDcP3GNAUTvz50sm0vnYvze1bi59H1NAZfRw1P/cgPMoeb+O9eLfqSbTO6eMKd6ch16OZPs68SuUDX9nJxf60fulIbqOyHxNOqfFCEscf0SK2bOFujH+5jVTmCPJS3BK2dOMaKtE05J3LfDC1vhZ1J61Jqr6MRlYHoFj2O9sZYgZdRRNBX3QqWmVG8Nfd55GYsATqyvV0QGU9jcz8glqhQpp/5RuR9R4uotCMqac2snLFX5g2V5bsy4/S0ogcEu6vQL7udK465ROlHXpJHqKeiDsUTgGazjRWsBdcTFNw8fNJGibkR2opUqR7eT75HrvIbYTuQyh5OUzr3iPS8jEbl6qPRlN1enndgBbk67LonUrkEdOArj8Cf1Z0i04b1tGLjeOZ/CsFintUQx+8f9GnT3mUf6+TBtOv0BMNcZzLuMPztwvOtHU3adrwQoS/3U2WAm6/wduAic+6BzbcgUu9GoWmNmFoSlXi1IhqbrgwBasazJj7gwLwwh3sel862Vy6y62H7KWb1ka02mE9rVnqy3uV9eHw8yjvjdpJ8zTLuc7ONsRkJpJ590zsk2WgnAd08OY4nqbri8M/fsLSaAkWr/Gkw09c4DH0Fmq7K+E3S5nHyckjJcyVqV7dR143v8PotQgJTSlm8t/fYrPMO6Zq5UwlElI8tf0JQuceYe1PImApk0vLNl8TZPKp3P/IcuqMlaYFpYl4Ku5GquNeQqJekv23/xzcJuXg+eUQ1AUZ42bzTXrQ9J4c5twh9UmnaMp9C1JVSeLRSn9wbW8tNpQJY9qKXfyFuC/dHlzMK9lWCnPh9DlhOuoG3zKdEbPwavwv+L5RgdOVcrjqVMDZ+AOfPSmPeh0WUfZpMcqTVKNNFmJY029PDQol9OjjS6ocnwKHgG1MsVkLfPRzcihYQh6FA3zDngX4duc+u7vClcqvJ9F859vkbZqEsAQNihk9lKIaLSnspB3Xa5UnG4WFtDexHdHLOUYFC/KL43rec+kklt0y4FnexTRu8WwUmStQxLYsikYxRfD91GB5lXw+/oHohHocM/Dkj6aMJLWal1CtWolWSsSQipGo0fgs6BP8IptFr1h39hCasTWRNSufovvN1dCar0f7Rl9E1tZoTG+2h92W/1BsEUop653QZ3yFSbY2U+QkM647uhBRc2R4XmQPfa0yZekCb1KaFotfum04830oW/ZJF4/2r2WHel6TfnosTKTiaMOqWVy0xZnOOE3iPlMD6OZ4HYos1cartFKUe32BXLoIRerZ0CKtOArRDSWlvRHUERpLFZtn8EdjKuFgb82jx0ehIa8aId/nCXLyJG44dQaNXWrNpy8qRtbivyxnxE8k7zhP60yOk2/te1aQ5ivwyHZQddWlj00D8Nh7CnPFvLm/6nc=
*/