#ifndef BOOST_ARCHIVE_BASIC_XML_GRAMMAR_HPP
#define BOOST_ARCHIVE_BASIC_XML_GRAMMAR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_xml_grammar.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// this module is derived from simplexml.cpp - an example shipped as part of
// the spirit parser.  This example contains the following notice:
/*=============================================================================
    simplexml.cpp

    Spirit V1.3
    URL: http://spirit.sourceforge.net/

    Copyright (c) 2001, Daniel C. Nuffer

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the copyright holder be held liable for
    any damages arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute
    it freely, subject to the following restrictions:

    1.  The origin of this software must not be misrepresented; you must
        not claim that you wrote the original software. If you use this
        software in a product, an acknowledgment in the product documentation
        would be appreciated but is not required.

    2.  Altered source versions must be plainly marked as such, and must
        not be misrepresented as being the original software.

    3.  This notice may not be removed or altered from any source
        distribution.
=============================================================================*/
#include <string>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/spirit/include/classic_rule.hpp>
#include <boost/spirit/include/classic_chset.hpp>

#include <boost/archive/basic_archive.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/version.hpp>

namespace boost {
namespace archive {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// XML grammar parsing

template<class CharType>
class BOOST_SYMBOL_VISIBLE basic_xml_grammar {
public:
    // The following is not necessary according to DR45, but at least
    // one compiler (Compaq C++ 6.5 in strict_ansi mode) chokes otherwise.
    struct return_values;
    friend struct return_values;

private:
    typedef typename std::basic_istream<CharType> IStream;
    typedef typename std::basic_string<CharType> StringType;
    typedef typename boost::spirit::classic::chset<CharType> chset_t;
    typedef typename boost::spirit::classic::chlit<CharType> chlit_t;
    typedef typename boost::spirit::classic::scanner<
        typename  std::basic_string<CharType>::iterator
    > scanner_t;
    typedef typename boost::spirit::classic::rule<scanner_t> rule_t;
    // Start grammar definition
    rule_t
        Reference,
        Eq,
        STag,
        ETag,
        LetterOrUnderscoreOrColon,
        AttValue,
        CharRef1,
        CharRef2,
        CharRef,
        AmpRef,
        LTRef,
        GTRef,
        AposRef,
        QuoteRef,
        CharData,
        CharDataChars,
        content,
        AmpName,
        LTName,
        GTName,
        ClassNameChar,
        ClassName,
        Name,
        XMLDecl,
        XMLDeclChars,
        DocTypeDecl,
        DocTypeDeclChars,
        ClassIDAttribute,
        ObjectIDAttribute,
        ClassNameAttribute,
        TrackingAttribute,
        VersionAttribute,
        UnusedAttribute,
        Attribute,
        SignatureAttribute,
        SerializationWrapper,
        NameHead,
        NameTail,
        AttributeList,
        S;

    // XML Character classes
    chset_t
        BaseChar,
        Ideographic,
        Char,
        Letter,
        Digit,
        CombiningChar,
        Extender,
        Sch,
        NameChar;

    void init_chset();

    bool my_parse(
        IStream & is,
        const rule_t &rule_,
        const CharType delimiter = L'>'
    ) const ;
public:
    struct return_values {
        StringType object_name;
        StringType contents;
        //class_id_type class_id;
        int_least16_t class_id;
        //object_id_type object_id;
        uint_least32_t object_id;
        //version_type version;
        unsigned int version;
        tracking_type tracking_level;
        StringType class_name;
        return_values() :
            version(0),
            tracking_level(false)
        {}
    } rv;
    bool parse_start_tag(IStream & is) /*const*/;
    bool parse_end_tag(IStream & is) const;
    bool parse_string(IStream & is, StringType & s) /*const*/;
    void init(IStream & is);
    bool windup(IStream & is);
    basic_xml_grammar();
};

} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_BASIC_XML_GRAMMAR_HPP

/* basic_xml_grammar.hpp
LaAvx1CQj4hnIobfkcGbwZPBENZd16r79DHrk9BZ89GnGoHmp/tXei80mnu8lW/AKLXv/eMex6XrArOX0tMAVaTAvRSCExKiBSNUc6BFldC7H1rZs1yaqux0kxBms2EEEtQxyXFR+79JhdPdnGzMzA50D/hHXbFsN+8cHbtoO4UeoFvLW0f40eHTCecLFSgVKhVJFUuVCJUKlQmVC0vlK5Qr5aukq6VplGnl6ZPUuqABkrbQAIG71bZHnp/0LOIPLVeCV6u+zCMvvlvCfDMq3Zy24i+T49OAa0JwphAOCcxG+gkLQ92oNvOnNNQwI7IM1KiV7nMXU9irlUTNRW8azmiyZKyVyP7oEjMs3chdGWDDjD7dgoLTYpPEYh+qOLmRWtY59ETtKHaWffaKfFv2/9xrh2p1a9vtAO1AV/+RE+c0Z6LeGZ14mkq/sT8TMLjUr96vSm9BagAnmoKzylLjsc1tcXbwOpOdNSNKXEwWsRWvmqyeuwxQF+Oq4HrgFuOK4CbjgpZKZlZkTmReeEN5U9Us6YYzhmcXepdsrzavGqwWr1qsVq8KroqsSqwqxADJWco5ynlm8es56vn2oPQodx31JnWj9Cp3H3Un9cCQrErCzy2tcEnaL9QRmsqHk6NhMK620EGvJyWUHVGTBqu80P909tU2K0xash3JnG3lU6v2VyIhUz0TMZYP1VDIQgeqjkUXVzK1qMhAbZgkP0aqrkUnVzq2LNdAPVcwnoPWUMlOkUQ/n5P6oUO4ajw0HeiOV26Z7Xjl83RL/9TgJD2b3XnDphw4tYUiehrNVPDVktjSZUFNfclV55oXR0VjKZB/iX0dAz72MuAGHj5O0TDwBj7+JO7V5Wo/8F62UYSHQ6MMTw0ltP/N5o2Px8rHKsfJUpKnaHHaAe1JvyARyzwtDuErFZ6zucq8FCK8Lz/IVGjfp73BETrr3N8Hkht4NdwKJm1FwzZWSk+i2z8+RmszYd26Xu0PSdWU3oURtit2M3bnPh/bxpdv+2/7d/tjHy/vNYhjz1BcSg98cyZwz09PREeTZfyS+EVcuU8Fx6iOEyWAPTdNMVqpDyBuu6NnJgV+TvcUb6JfOK8bt1YrOoW9hn4XrvgB/qLWRb9Ub5Jvlm9Yl5X9ubF/3bvFmdpqt/RZRoQVRc07sEaMEzvyiXKmbfP2SfOvDXgRGklmTb8NasJ30/7ESOUGW7pwN1CxN0EZ8YBP72fVOdTswzqb0Y3BdPbPxEsFMkL0N0INPtwyfh1zs9N+63ETtEpb2VOX17zrsR3RsRSklA5Eh08I3bA6KWNeUaDIAyunulDbmP1LpglBJBKahfJDXpBD/GBV5zE8mgjdtDPS+tFBDs3xJveefoHbZF4k7njO/fAtCWWp0OhqG9gWHAejgxPFR7WUtTA9hSezeov+1wfAS76yVbIwvSntYojhV7qs2Resx89BVu6cAhrViLpUrvGphDG6gjG6unGqvkVwNbRMNUtzFPUgmkrV8FukY15nfqfBF9+nz30gXPs0UA5AvT+mgM0eVhy2+GvF58TnxSOUb+xH1s0iuBtHsr0ZUI3MKPUvlECV1GH8CfkoHmHnjDew1fNpvExPTCXnqH/9z7j75Rnmk2jSorBv9t2/AXTcRhQb0GzUSr+kgeb/3p/FwX3Wn1tnXAi2tEm3w0tK6x3GVTZV7lA1Oqe8rjrE0e+Vq1YZKpkFrbrW4uPIrczqclg8ca6ro20XcvfuwnQDfJm0TL5Uvjy+ir9EXpymyR+ez6gXSkte9boSuMB1rBpkdW4Iu5G4wNmmu1TfMhy9R95hnC5KUuBlDW4kaOFInApdP2td+Uzk7h6C2nwmJoqk4dinaSnPctf703KatxxqvocOUibyA4E3XHPf1+4hXNtMu4FPBXzN0YsFu99wZXhhSvxmgH2Yx23chBmMoCygbKCUW6CPVwIf7kZY3C73oGoDtw5s84G/DQ/eFz69Y6/6/XcPwn4OLZf4Wl2pvamtqQk2r7wYtao/Y61X177xVRIhlWPz7PS8MpyUUEpHw0vs9NxCXMecuNlBhDa+9/EQXJM7ABA0Tuv6XNJCUrI8fOjGlZhWdeR5AH6jfUHdISFLFGGzoAPXyh2vOX9bQdK8kS4aDK2nKEo8aVwnl6Fiw44kq00nm6lyEbA92vNd2qsy2U4bh2XvKbtnzP5LtYbjB7JGqJ99xO01kZuFhxYehoLji5xc6+rZw4CRrdxc2tgWfFd+vRxANGlnmTWabD9IUpc2PWdsDLc24WPv9k+dZwpDei5+F9HEPe3HPaGsOZUupbQZZYdw5j2lVjxH2W5J5VpC8QnlVXHxKWVOLb6I2Q3EdDWezpQZfYW2vcSTwoa/1NU6n5VS6bzjiV30cSO/YrtsHfw8mOaRcVM7Wt9RtXolJX5W6rrtRnzKpi88XjablBOw7vv3WFL7rvgpgsOz63kqKHjaqN078Kvg6RSAqpO6AGQn0EVQA3OQDht7LQc4v+rddLeWz3cOpWmwC9eITsLwfoGYiUOwizlMfCUW9/UT5rBGrCOOhVb6DV1CnRGCQgkbxUza86LIe3c8dFCUa412MYxRA+bNgr3yqmnzIpaY9KrWk+mPrvVqVOguWOMONVW7/uo1c/M+z1Q068+QkF8nf6ub13FfHk77D66B23VxXzh2wWCI6KiF95kzoYZE50zroTQoe9OAPED2lXnl8QApb5elX/y630l32nsSJO4y/hvEAMcrqwWEn/GbY1pnMeh3HfOctpxX6daf47YsZ9YtONGclA79aIG5nhfcQzxOmoYcm9JBUuAS39GthdAKCO+cXzBOgA+JKXaPvD7n+a3bP8oNpJ9XbCXI24gJLPbxW56A7blxoR5jvjXBHi8sEeMFj33XeblOPxK/g2dKzT7FEJdMH/bV+2aVQeDGAUB4AtYzz8uXBlq9MqbaGAzeO5X9hbR4TXqNrViy2lKMS2QWJiq3ySCe2IS6YBktaidtvThoxx/7SSKvbsGpn9lRuebtmcEmupI8ZeN0Iifggsf5F4mAtHk+y/9WKY/vncsH3GLiob/PN7cU1RZU74MFuKbOO2dxP4LZxFhNdDZY779bgR5YOTCUR5AY+tRcJBH9V1uCFbv888n6gQtzTrq9DxivKS02YEdJGiO6L/87CZewC6h154GF2iT0X6UDHNAhkZmy64uREmX/cvxtcH4yzZOnGOu+s6vSY/jUFiPd4j3WYWjPlqqqXGO6dSXlSxHMIfbeqxrDauvley9xOyK4ijd+HBL3PDZ1BVc/j8PLYzGtb23cOMPdzuQmpxF9Xf+swDN06E8QtH8K0ZsuRPcCV6jIegxoOsOLL591bX5lcY8rCNyqYdcQPQk/Xq1Kuq0fsYK66dN7JDIXg7enMwRt9vcWhuCNTmJpIMSIYBW2jNivhGAa0XuWBPIeyGmbahktp3qdTRD1hF9H0TJy2UrwFbDMKZty5+cfTEZiTLYz3YhviYo1TR2KlYBu9FXliF+9nbUfdOuQtEEZJaih8bz84CCaUCbL4rxUvFQmvho89gnSa6my54B4YU6KfaMRsZjASX7PNvPO6GMsi3U0+OGjAqG5wt2nJQ/QKph3x/V08KbHstMS8ge/SPK6/ZaRU0imtcmb/coHelHhZPu/V4L2AT3eLbAOnVLeY32ovLYV6Od9AV0QrtKzxNvBWde3LWDTGcJhHpWHFX0sMJTF9+PZdhdkELcizxn2UltP7NrZL039O8i2XtIwJNWdSGD+OIinkRusQH6qLQw5+wJ5IuJEljcI9/GqsFO25UefbM63EUPOfAPcEweX0w/MwPyw82t3q2DJyutUQHxyLRGBkQTDmOsRcgyT6TqHhYJeqEnYROW7b9zO/OUqZ2th88ep2mYooFkBVjAuixppc5/+5t1OHsEjBG9EMNOOTP/JIJUMzRDik8BcxX2VHA/Q8UFTV9X216praYg5gIz7KzIXa9qm6Ztb/fhje0ZjcL8GD2cd2u8pwQJ57aK5rmWjF3nM5sMe2Xp9UUqI7ifDSmPRavX4T5r949WtMcYcd7HgLndoKGKwgvzAorAwdtqnuNwH/k9Zpy7nlVYmu7fRT9sHCufjphza6GVfwJH3i0ls8fkBO6hYi+GS+vMYOB+EBojvXX1ukAEcWZhWgVZamLt5xHGEgQY5YmN/ekw4lnAwJau1zX1bByOUb0zES7royHPCnlFVc0AuIMDAGCCHDLKc+Gu/hhyh+lCokYFJ0vWno0Y/liBI8w4aRJBUDdYPCiuCBoyPFmzUdX+TWr6KfdZvcuvx5P3FO1/3q1+2FXfPMadthCOpLv50cce4ctm6OeFWQY8m0sR2gm1ij6bSkih8QEHe/Eb/dFt1wOx2HTNz4PonOodLChsmsYnq4QzOjgNHr9M90SPQNrdxHISFkVmiOkagsSZUsSHnVOVBJzbVLY8VO0yrkjl4xIRLNkEKv5Hcjf/WjE/MGrhoIg1knyh0oPOfhaxYT3ou98QOIN+LY4xIEsxxy3ZzOallJcourhSdptOwI+XWPFe+WtKcEKUxxpwoj1p6ZNRbJC1L7L98OlY5UYuFH56xiLgULsRYCaX++hlxfVuV3IclQwNX5EPc/Oo0LtZ/5Cgmk3c03+WrTQd8muvSaQf1b3U7x7xx0oPGV5B6fQtb+o7aZ+WjTQ3Mi0AumM1zU05KtS8qD2ahR9IG8x6d14vPMRt4eC6Vr4kJX5eMRgMdmUrDkPr/ACPMoqzKgvjAvkCS83btU0vJJVNHhcNbkYUHGwO6XRMvxlebXARsHlpYNxOb0/ttHjpc6GY9k0sytjC++0YMa9w7W3bdWtzbdz6L7XmR37ZXwnmK/ZoXdGk4RVsLV469xnWqM0+zZWeAwI8fdFCUcIAXO8QzFpXvz+GwKmVA60tUiIM3zaDiZR8NKWjJJJ9kJLG353UTSx3AkgB+QCTxVL7puyQ9l80bPtahpQqn15fPtk68csZvFYH2YrZnXyfTxQ8dtE9qFVkaG8cOoDd79lXQmUF1dG0XCgAKhE0idRBstwZBS3fNxzGvQYz2cj+Hh4Gsi8bxZvrcSkQt2/EuzQmlCSRilIgWkUy6Qogz60hBnO6QZFWz5MhuTxtf4qnbipO3mEIl4Xzj1lfbp0vpFbykXWPV8sZFcbZUU+Z6nrOXAXVh3XCFCxbSRJO4u9pFdVLxo5NFc2Dh75JujInHajL0KdETV7dAKKXaAqg+JaCe4Ax2JZqkijNDe9VRTCAfdQGpY4CQUkSbjsi+c0oSP/fRk9ertgyYWVozQi1jvUOhjGgarZiDgWEm7de8xWpfVTHxQdAODIQh+grG3MZftwZjxfgMiky+dyRvemv9xdW1/r3iw9UCTD5j58f3K9XkZ8u84SolLZ9zvlllqOLbXdTwi+jq1cY0rfyrisjauB5/Q3n0/cIy1Jfl7Mppeqm5MUINyiAoOzHOj/VHCldkVWFhUxfM5WajyHSt9BdNs+mQsrWKC6OSyrUAxo3FSgbmOH1OiONEHzbfmsuBzMWHBqmT1qwxWqAdMDrY0csJ7lNeYomk37TZK+Wh0pjbELS5LwVIu2xgTbxKI1nZ4/Kb9J03bMQl7eTdJaCEJHDgzSSjhKgb+G9qrDnRu/yQBAx+WCozZVbfUPf931yzpjvR+mZyC1LNtK5e6xdlJlRBLl5BQ0O38Hp5rKVTd0XLsn3ss2GNAA+Ym/go68vnymoq1bjQexo00T+v3ebOt2Dd+0b98AX98Hh9O3GshDA3J7WuyxMrP7js8/T5EBNaD9q1iYfOg1p0StE4XLQ3NiC9L14QyhK/Nk1mNLgh1zkx1d2whoNLFG8awCAq3M0n61MZZrWa9AumSoQzFPLUs/QzUU2ul6rCJ1pVaLfEz92enPu1BYAaWyvUs+N7R78+mzsBPJlQI2kxOucUydmGmvKkdcyVwSWPmcy8du4evmLSjLT0lejFHTy5tORSrwmHGjuZVLRWujJRTq4e01thafOdJLe5S9qUcPqN1C3+nFIKt1jA15NT6/6WGeWc17o1K2jSTzzhhmbvNg6fGpkFpTn6fO8xPMGD1f4K8YzwXjM0OXPeGOyno6Iqyhtp8/o4nBrhvIvNqm4ZZx6JxUfg1bw7B93ZGEalEeasmoiL6TO5NkATOPBlvFR+2xk3m012jq0boZzlko2HplK4BI9DCKTrjlradm9ykfljJk27x88BhOXCjS1RgqpUccM9YTkxA7yM+jSLy93K4ibwG6dZPSwiru8cKsuWyY77t7Q2YooAPfY+k11PBcjab+gwUtT5HFlfN7kYLQeQz09Gf8J0C9sF6HvPYeOE6dGbQAjgG5kDjgPjh2Ix+YwEZhvB6+NeECGJOrKLARwFazW6Feq3gOe7915/gsAaLGvfF7EHN/lBrGPmw2CH/HLOGpe3jBS7BIFj/abHd8XMBqkBmCYgGIpXrXZZGp4XyhZobq9oGMBy26bQ9I4yRAK2rWhPPtS1/As5OoigSdpzF88Eit4damsYIFLMnv+6FiF71KEPUr8JSTqNrnKYCuzz9uiv+Y3nD/fsyuSl22mP9JypNdHXkzcCvOFkQ+BedItGyAG8TO4e+8qC8Qk/jxYRp9y47xrVEZwYAMIaKb2vzKzqreNcyqbdAPqgu4QN9Q4PmoDbAf2uV2QKxglRN38JAIuSyX4QS0/WJDOlyFEV20hDwJLA+VJbwAsp9XF4Md4nXTKPpE7YMfyhsWaYIeAkoBQNl5DdzvvEjV/aoiRTcmbXVMUP/DeIVe0Y5nyyp0QkUt1FQF6wGJu1kN5em8SK6IzBd33AHXdtBZZBGp/U/oNSDNy7zfzh6waXse/QZ9W/aWMiJr7Xgy4V8nYw4NprchNsvM/H4AOWyQcNQLtraQ050EKny3Iz5SPvGYiZYAnQtqoN0F7DRd0R2bmfotff0ZEVmsgCZyoGOeP5r9C/yGpT0ruW5ffrGujADLLyt9SiS/slBxiBvc7hThgDbE37QqohJ4l1D53usPBA8kv7KhsCyCAyauIDkR12Edxp9P75li5jJyZYfpDHn+PYcQUXS5uhJYPTxEp9YjwxmDVZi50t+zYz52GBlKNu5AEHKC6jhVUYJNRSr8ltX9WmQCjBuo+FEH+6xM3AvBFLTckz0cXc+VKmP6of5ytl43U1ip8xLjGvs+ulYCz66ccRa0eew74lSFtWm6Fc4b/8G1p8/2/Y4KZOQoPZML/u60SrwUlaBnGVQtS1YGCHJEYvzGC2Ld+yxI5SOB+iuG0+aykGdvQiLQV5ZMSexZXef0li+A4NWxMvEzmQp1cu2bj/Pm0uOc1+ecGHpHTAI6Yl3MA3BbMhngYoI5JhAGYCdhPnsDdhLQFo91RBlsvTyHZ4omjiaZik4QuoQDz/RaNF9hGC4DXZ2euLE9+9nE+00UnqxcAtJyfRq3lilFMKhYZlZzWVWFf0d6/YkEDIHMJp23m19K2ly7KLhBeWfZi335yXPkTwU4bgsxPl3h2u2jyfAw1uBU1MrOi5KL3SE1irb94H6xjbxbSyl8TcbRpJ9jUdJGSub3KGFzOaZVJqBtIe6ySpgE8eqm2YRaLGMDLSro5znSxcFh53oo+SNW0ed/DdGKBkkWoP6RNa/+g139Vg9Jn9FybP8e4BhH1+QKqBYcXzdM0cNg+X+wnqRFYauQA3bDwekpBIqjRjUB46YbOVOLzksbgexPPfJDT9ZIEGH2TsFQENidsl+tFFum0SIxDAB02mNhiVjZRo9Wilgd5GnFhYrZhIxpQKvoErC253ALMs/k69Bb+fNclY5jeiaX2OnStnJh4TH+FtlO90YP4/Kw8UjZwpGSiqJEWwf5281AqTo03MxoC1X0Th1HyxoBGdbAO8Z5xyI5R6dS75kC+TdXKJOSNLJO5j6MgDlEglg0qQUIegrXFqmPKT+Ku0VuOCtTyx/8btN1x+tEU+yVDNHjhAphHHBolh+k/rKeu3gudgPs8hq6CEu1Ivcycs6F3qujs6Gpj7XasZUyNlYLOEqHeT44Xw2rec0rwq+uglIKG0oRI1+dLtpd/5ikbYliTVdJ9phx/FI9FzvgIWfS97mS2y4QTiezB3Il0Oq+rsgDexiNsIBs58De2L4bnKcuuFd17yQczl+lndjWLCV2FEzyCKpCQ27z7pN1e68qzlXBLbdU7S9fG4ypoOAHsY8cJzTurYP/hIOskxkqTDLYd8JP3OacDHTq/1FjhEyWU8gM1bneIPrV5KQ4HsSLQwDxRXDaIyMWPFufOib49wDUrET4CWQy285i88i/WNSZf3ZYM68rqLy3d10lTFpq9B/Q2lC0LvlJ6GJLppJH2kAE+zB2hCzFureI4883Ia59Zv50YL2jnvk3b+xScv/NhNqf1UJH42J8G5IHSDNRr1JCLUbEzUR5pa12WqorQmwUq9M6Y8wUKnnJgoCKdw1q5bZqemVxjSCrbKZ5nlhaZ/HwizGhFr/0CXDkh+H9QDzzSILg1WrccBYqcEESA2E5g15YZAC8D1scfRJwvujZ+2bBKGXH8RP8xICVxjoxHOWQbFYWEAJOvThm1CP3ZdYe3MU6LHNbeIkkeJHYCp5LVvk8ho1nu6A2TJ9QT0Qn8u64PMCTdBNAwtiumTpLMT1rR7ZdHQWlkQSw2Rjh3Hdew2M+/EeTl2Kdnrr9Arxu57me/qp7h53eu7roLurM3mvAvCt9oKHGG95njQNp5Cmgl3MqX0b4d7K0rXtJWACpLg+XLMkj5Q9Pp6amr6NHgHWyIXSFBzUlCme/VsZjQTym7Cyw4dAvh+RljcZQMaoHTVkVCagICU3O29nkTn8kwNUkfB7I8sBmmGACh/QtPboMTTRQuq2hbbBLf3c1CMzi/QMyLALjYCnxgApUVoWs01y5FXEYD3/FBsbN6vLN4vbWfhfUF/FfckoL+hfexaIekLMudz9G05tDxSyN1fxLquu5/LFBcuj1vbANxOaNxu52JoPwtsI7YG7izbPfBzFiL1QVQFfMJBayN1+rw6fS1gYUtZE8C+AmwE+HJd7zgRhrH3UO7AWQI1+DvYgO2golJvwZZ8Ppfz8q0IiHfCXbo4M7ZgMos1l0waHAH0KBmr92IHkS9+2mhO9qrsfTOPTSvpwkD8rooxRrzW8tiGbZ7cwzMyAbYK/RyB8BE0lhFA/ujo9XA+3wWUBNZ788uvMrkTvSw=
*/