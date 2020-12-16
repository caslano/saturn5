// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_UTILS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_UTILS_HPP_INCLUDED

#include <boost/property_tree/detail/ptree_utils.hpp>
#include <boost/property_tree/detail/xml_parser_error.hpp>
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>
#include <string>
#include <algorithm>
#include <locale>

namespace boost { namespace property_tree { namespace xml_parser
{

    template<class Str>
    Str condense(const Str &s)
    {
        typedef typename Str::value_type Ch;
        Str r;
        std::locale loc;
        bool space = false;
        typename Str::const_iterator end = s.end();
        for (typename Str::const_iterator it = s.begin();
             it != end; ++it)
        {
            if (isspace(*it, loc) || *it == Ch('\n'))
            {
                if (!space)
                    r += Ch(' '), space = true;
            }
            else
                r += *it, space = false;
        }
        return r;
    }


    template<class Str>
    Str encode_char_entities(const Str &s)
    {
        // Don't do anything for empty strings.
        if(s.empty()) return s;

        typedef typename Str::value_type Ch;

        Str r;
        // To properly round-trip spaces and not uglify the XML beyond
        // recognition, we have to encode them IF the text contains only spaces.
        Str sp(1, Ch(' '));
        if(s.find_first_not_of(sp) == Str::npos) {
            // The first will suffice.
            r = detail::widen<Str>("&#32;");
            r += Str(s.size() - 1, Ch(' '));
        } else {
            typename Str::const_iterator end = s.end();
            for (typename Str::const_iterator it = s.begin(); it != end; ++it)
            {
                switch (*it)
                {
                    case Ch('<'): r += detail::widen<Str>("&lt;"); break;
                    case Ch('>'): r += detail::widen<Str>("&gt;"); break;
                    case Ch('&'): r += detail::widen<Str>("&amp;"); break;
                    case Ch('"'): r += detail::widen<Str>("&quot;"); break;
                    case Ch('\''): r += detail::widen<Str>("&apos;"); break;
                    default: r += *it; break;
                }
            }
        }
        return r;
    }

    template<class Str>
    Str decode_char_entities(const Str &s)
    {
        typedef typename Str::value_type Ch;
        Str r;
        typename Str::const_iterator end = s.end();
        for (typename Str::const_iterator it = s.begin(); it != end; ++it)
        {
            if (*it == Ch('&'))
            {
                typename Str::const_iterator semicolon = std::find(it + 1, end, Ch(';'));
                if (semicolon == end)
                    BOOST_PROPERTY_TREE_THROW(xml_parser_error("invalid character entity", "", 0));
                Str ent(it + 1, semicolon);
                if (ent == detail::widen<Str>("lt")) r += Ch('<');
                else if (ent == detail::widen<Str>("gt")) r += Ch('>');
                else if (ent == detail::widen<Str>("amp")) r += Ch('&');
                else if (ent == detail::widen<Str>("quot")) r += Ch('"');
                else if (ent == detail::widen<Str>("apos")) r += Ch('\'');
                else
                    BOOST_PROPERTY_TREE_THROW(xml_parser_error("invalid character entity", "", 0));
                it = semicolon;
            }
            else
                r += *it;
        }
        return r;
    }

    template<class Str>
    const Str &xmldecl()
    {
        static Str s = detail::widen<Str>("<?xml>");
        return s;
    }

    template<class Str>
    const Str &xmlattr()
    {
        static Str s = detail::widen<Str>("<xmlattr>");
        return s;
    }

    template<class Str>
    const Str &xmlcomment()
    {
        static Str s = detail::widen<Str>("<xmlcomment>");
        return s;
    }

    template<class Str>
    const Str &xmltext()
    {
        static Str s = detail::widen<Str>("<xmltext>");
        return s;
    }

} } }

#endif

/* xml_parser_utils.hpp
dYNn/Nt8JZJS5/dX/fuyHOcmWkZZt/z3ZblGDc4k+3Zk//y4onn3xkz6/Bp5dip9L2l3B6fTryt93/aJier8nGxD4J/0lu7u5itLG2PNHV0trc3u+2rnmWSe7qvtz/OUnnZTMJEp3c656+3mcWngqwdtnckrtdQ+Krh2soy9KhI7uN3VS7KOuRsH0r3c09Pf3ZdxZg3SdVx6QCBP6oJq91qj1/GYPG/7XE+6+vv2LiaTrwcPSb7uEuBs+rgI6lKv791vTpfldzwk07TX8ZB8fS79+pnWjOuMsdrU6z5tCVJ1zD0i9Xp/5xM7u57Sma4jJ53mIyXtStb98NTr3vjvpaX62JRKS3w/I7XN+XsFXt87BsN5lk4rSadpXU/LuYz2HRhTK1y6HQ9KpSVKzEwzsVL7c/eeeWtGfSV5gbRwPys08C/V59un05wV0nXdKfV68rSSSjuZakd/d3Nb51UuPVLzKudQIM0YWZx628JU+zG57dR1Uu084z1/1ynHaSqtKFVneJ2RTovef6/Olie3HUjT1nvv1ekG22Vp531PT1prV/oyOzXHl67I2A8Gxv8Sq1FvYI4nt9+M7x6vZxMbO5w7vXQ6uX3r3jroaxB7h6Cjba8a2yfXngc9/z/kaS596AlrTzLfE1JlGTv9ly19cZ6Rb+78fypPxoy17MfPvDxf8nokee6t3W1btNmgneqX6dxe/x30XU9sb4sekuWq5Dw5udcPOZ7Y2/fEoC/xeuBf34w/77e3zjjT+JUN4esj5k/m/ZeGUnfv4pWVUfdXKnuP3dsNF7dufRcgcdTsflie/o7SoWP3SX48mrqvWziXWV5TtL6qtKGqwoe7D9n/pQ2FdHd3tCducPQ9pf1UW7KoZLvq932mGItWN1aXV5WWN6XbVdP5ZG8EEtvv3U3Yu4IP71BpsXxalvyMsntfeRXRqrrayvKYB5eXt3s5f3mB6baNHGhbVVWtrxm4SZoqK/nRucZZa8O72YkP4M39q5KNS7Vt5iH7vo/hc2k3zn02nbEPdpdAnw2nPv1QRiIxOWyFyc+4p67IHH8f+yZuaTVW+0zd9YWtnMv6XKekv7GT3ofHkveAlzPbUx9tbKyviFX4blVlV88pOyx919i1VrIPlzK3cdO/rLGpprHJhOps293HXfZ4d9sp11g+f058HqyQvY/0+3u1R1lBYfIz/YE7Z36mH6uvLq8pc5th79R44LtYRw4HmfvVvcuyUt8CqE72t94ipfyMW1oaYrd6YJcG0WT7c4/vnx/1jaW1db5jEX243bXXB83uzvzSk06FNw3cLohqf7JNy/fbf0zVxhobGqobqqK713h63NndcuqJWrXvRnxqR7Sn+qZNmcdSra5VxOorog9JnuVNTodV+tbBbgVhQely8qzJmfumJlZTZUAbMstpNfPdXTFNnc9Pnc64dxMN7pM8JjPLaYo21ZkZtU2xzGK6npieTy33SK4Jtwwy76OVVscbfakk/V2h5PdxkvOv46P7voNQF2uqiMcbm6Lll92CDaLJtp3IHKu47y3UNVRXlbtZ4cbDZdtpW/Ke3enjB+5BNdTVVcfKjXHF8WOHz1qwn3zvfZPn3ntFpO6J2j7jOy8NjTWlTdITWx9qO3vvZH1nk/kHM/Pfr7LWl3HKSmuj9zp26H6Jf8cOHSj/eHPmsVBZVlNf3liW/PqTkTt4f2pkf3vq4/U1VQ2N4ffsUhuk7/Eczdw3V1RUNPiiXE1dNLkXY+Ex6b1G5v2npsrSeEWZe4ThIrT/O0Sj2pCx/3wto7yqqqIxqvqGRsdMaeLzG0+a0nOlMNn+7sz+3qe+vqG0sj5cWUuOdJxNtSu5/yYO7L/q0tJYXWU=
*/