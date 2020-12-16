#ifndef BOOST_ARCHIVE_BINARY_OARCHIVE_IMPL_HPP
#define BOOST_ARCHIVE_BINARY_OARCHIVE_IMPL_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// binary_oarchive_impl.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>
#include <boost/config.hpp>
#include <boost/archive/basic_binary_oprimitive.hpp>
#include <boost/archive/basic_binary_oarchive.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_oarchive;
} // namespace detail

template<class Archive, class Elem, class Tr>
class BOOST_SYMBOL_VISIBLE binary_oarchive_impl :
    public basic_binary_oprimitive<Archive, Elem, Tr>,
    public basic_binary_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    #if BOOST_WORKAROUND(BOOST_MSVC, < 1500)
        // for some inexplicable reason insertion of "class" generates compile erro
        // on msvc 7.1
        friend detail::interface_oarchive<Archive>;
        friend basic_binary_oarchive<Archive>;
        friend save_access;
    #else
        friend class detail::interface_oarchive<Archive>;
        friend class basic_binary_oarchive<Archive>;
        friend class save_access;
    #endif
#endif
    template<class T>
    void save_override(T & t){
        this->basic_binary_oarchive<Archive>::save_override(t);
    }
    void init(unsigned int flags) {
        if(0 != (flags & no_header)){
            return;
        }
        #if ! defined(__MWERKS__)
            this->basic_binary_oarchive<Archive>::init();
            this->basic_binary_oprimitive<Archive, Elem, Tr>::init();
        #else
            basic_binary_oarchive<Archive>::init();
            basic_binary_oprimitive<Archive, Elem, Tr>::init();
        #endif
    }
    binary_oarchive_impl(
        std::basic_streambuf<Elem, Tr> & bsb,
        unsigned int flags
    ) :
        basic_binary_oprimitive<Archive, Elem, Tr>(
            bsb,
            0 != (flags & no_codecvt)
        ),
        basic_binary_oarchive<Archive>(flags)
    {}
    binary_oarchive_impl(
        std::basic_ostream<Elem, Tr> & os,
        unsigned int flags
    ) :
        basic_binary_oprimitive<Archive, Elem, Tr>(
            * os.rdbuf(),
            0 != (flags & no_codecvt)
        ),
        basic_binary_oarchive<Archive>(flags)
    {}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_BINARY_OARCHIVE_IMPL_HPP

/* binary_oarchive_impl.hpp
qn+GWX9doz/v/yNE/beY9R/YpuDjQtXfwax/nVF/n1D1R5r1zzLg33OE0v8rNurfZcAfeTdE/a8peOjzGfC9HT+pz8cCgdtVUS2FtAPgeguN1gNiYjOeo/pJPlbXuohy+sv3fLSOIvIu/Zzr5HDJaPRFwJ+Ijsdeeg3fUE8a6iHZaFz6EhTYtIYVLOS4vi4VxiMbaSReq15WGj6wEmOGwGHuzE2osizE0BXFv/A4/1x5nLL/LOJJQqeu3qrmd+KpEOuRYMI/ZuynvqHg9+sG/J1G/Q1CwX9kwns/VfBHS0LAT9bN/hjwS0LBX2PAR968RcGPDgXfxISfZdTvCQV//DsDfqxRf81Q8CtM+EHG/OgnQ8DPMOFnGfB5J4svKF59af7nO+Nc7UM/menZqx+HYNOrbnKyslrwGoFW/hIXDpvP+qrQTUfmrKCH0ormyGVfDR3R87moxEnVmJRdlwGXF7CeGDRXSJn9TiOcWgE6TPEBsIGYqh3IDrZfT3c6ADf5JWrzi+3UJnQzRMl7QDx7/V6TlhyWVUfZ74Rw/r1K/36NmNzd6JQrvbvpJDh/ktzOuZ/S7fyC3n8Ld+arzaSXtlEf9qbxwDUyJLeUcDHKs2fzNOq2byzME0glpg4m5F7MqP7mGTYg5gm5n8hj0vh1QqU+K6YwNaIG0Q3R+FIbX8zxLT3P+ApofMkYH4w9eYh6NRnfpPqomamdy1V3hnB3RPM1Q7sExBp3aTeGp9c4ExTrfndOdelP8fotuw0CLuuvNHlvfcDk2a0iiduuVxULj+TFTAOBDEwGvUpU4HJUItHkRqEI2xxxSpTHMOgTq+lYsrSIm/yVoq8682I8TuLLuwCPFZH0ZvLu8v0WXhnQXTH6R8SBijpP/CIgYFbnqbqoDO1UtNCgnUx1nmpneVknLRK67WEi8hKsjbWXxh42G4vSPcHGXl1oNPbawjKNjS3f2Os/ovb57DGssKjgf8SVVln8Ipfu8b3q0i1iJfo14Gevf58F2yni6nMZrloSAfRx6UN3mfuut/LpU7iUt14z8fPZACXh53Mls4xl3ETKyzOt7Y8fkuqz25CBOw2KvD9vs8fozE+WM//sJlrsv+mDWR/S/+66X/Ox9Qd6dRDD+vcYz7LpGuHZO9fRljqtTzspEhRlJUxYB1jy8vcES1KsG5HfAVdicNMhlyC6BT1nd4ijWd/0/lRGOnXJKx9Uvfb5lduhu1lMEVWULDKgsxtRCuDNdgg2nMUnchzUwWL0hAUoQxgW707omX7qRJCLW6/U5kkJpMMSwTQLkLbg7xzr6zMqGc2Q1yNVnzavOBiG/Qku29+CsGvzeELj6x7EVz2onDv2RLf1rO3S5+aqvgkpqXGTK9KPwFJiTHvuCvZ3P7OsyxXLGn4qEAiyrFNJDY6QVW1ncPA182TwMsitep8CGeSnDl4PILTX3xWEdh+ZO8HKHWGa1Ab7lhk9jbCXkTRHeEGL38i2G7DT+g7Vj681eb8+8w3er9/8Miil+fxyvF//EkzI7VT5J1x5Gl0YV0oINZPNfYJ+r+XfOfR7Iv3ezb8fZewqysf+JEo/6DCvwGzp5KPr6Ti8qPdBJ8l+e7VoCw95hU5HWWUTbWzwgdE96I8S2vyOn/P752/3lTq57d2gi/hBl0V0R2l38KWQuJ7W0uMyLFHaIPSL/jpOFBsm3v52cQAiOcCV3BtOFFIcstMgF4zrvQbATvwSWRp84a6XE3q7Kgt02eptRpej6Se25lOHGF1M/oIfAQd/J2K8qhD9k3FdFaRtXSd1nPsBW6a9h30nz/yH+bh4m3pC241sRDoRzDB1rax12vfSLpDt3LcY2U5BbtG30so7KJKhfBs=
*/