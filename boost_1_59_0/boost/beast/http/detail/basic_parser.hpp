//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_DETAIL_BASIC_PARSER_HPP
#define BOOST_BEAST_HTTP_DETAIL_BASIC_PARSER_HPP

#include <boost/beast/core/string.hpp>
#include <boost/beast/core/detail/char_buffer.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/detail/rfc7230.hpp>
#include <boost/config.hpp>
#include <boost/version.hpp>
#include <cstddef>
#include <utility>

namespace boost {
namespace beast {
namespace http {
namespace detail {

struct basic_parser_base
{
    // limit on the size of the obs-fold buffer
    //
    // https://stackoverflow.com/questions/686217/maximum-on-http-header-values
    //
    static std::size_t constexpr max_obs_fold = 4096;

    enum class state
    {
        nothing_yet = 0,
        start_line,
        fields,
        body0,
        body,
        body_to_eof0,
        body_to_eof,
        chunk_header0,
        chunk_header,
        chunk_body,
        complete
    };

    static
    bool
    is_digit(char c)
    {
        return static_cast<unsigned char>(c-'0') < 10;
    }

    static
    bool
    is_print(char c)
    {
        return static_cast<unsigned char>(c-32) < 95;
    }

    BOOST_BEAST_DECL
    static
    char const*
    trim_front(char const* it, char const* end);

    BOOST_BEAST_DECL
    static
    char const*
    trim_back(
        char const* it, char const* first);

    static
    string_view
    make_string(char const* first, char const* last)
    {
        return {first, static_cast<
            std::size_t>(last - first)};
    }

    //--------------------------------------------------------------------------

    BOOST_BEAST_DECL
    static
    bool
    is_pathchar(char c);

    BOOST_BEAST_DECL
    static
    bool
    unhex(unsigned char& d, char c);

    BOOST_BEAST_DECL
    static
    std::pair<char const*, bool>
    find_fast(
        char const* buf,
        char const* buf_end,
        char const* ranges,
        size_t ranges_size);

    BOOST_BEAST_DECL
    static
    char const*
    find_eol(
        char const* it, char const* last,
            error_code& ec);

    BOOST_BEAST_DECL
    static
    char const*
    find_eom(char const* p, char const* last);

    //--------------------------------------------------------------------------

    BOOST_BEAST_DECL
    static
    char const*
    parse_token_to_eol(
        char const* p,
        char const* last,
        char const*& token_last,
        error_code& ec);

    BOOST_BEAST_DECL
    static
    bool
    parse_dec(string_view s, std::uint64_t& v);

    BOOST_BEAST_DECL
    static
    bool
    parse_hex(char const*& it, std::uint64_t& v);

    BOOST_BEAST_DECL
    static
    bool
    parse_crlf(char const*& it);

    BOOST_BEAST_DECL
    static
    void
    parse_method(
        char const*& it, char const* last,
        string_view& result, error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_target(
        char const*& it, char const* last,
        string_view& result, error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_version(
        char const*& it, char const* last,
        int& result, error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_status(
        char const*& it, char const* last,
        unsigned short& result, error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_reason(
        char const*& it, char const* last,
        string_view& result, error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_field(
        char const*& p,
        char const* last,
        string_view& name,
        string_view& value,
        beast::detail::char_buffer<max_obs_fold>& buf,
        error_code& ec);

    BOOST_BEAST_DECL
    static
    void
    parse_chunk_extensions(
        char const*& it,
        char const* last,
        error_code& ec);
};

} // detail
} // http
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/http/detail/basic_parser.ipp>
#endif

#endif

/* basic_parser.hpp
/8oFaCzdwCm3tVKFQDQSVf8B4cNaiBeMHNTVB3VFj2Ex6LQKi+vYkVPHyJ8KPQtneCAE+8aqrNDpwXVEGNSVGnBh1J7ahN2hRPxEGHuDiduDCHmQz2k4jxsz+IbQWTFzP76RiY0CvZONhE8HrU8fCpScOIueUfaDtUr/rZV03J8TFwI1T+8vcaMwhFtYvS9Dj5BLEBvP+HU/wWRXqAGmUYiPCE0wC3mAP1UM6sQjH4ZZwviIEnJPncuvvgC0HKauRAhyzO4pA334FC+OGRQnBGJ4FiN774Jb+gbSfyxT5b2FD+NNqIcUzLFA7b+2Utu/cYvH3iOzHfjr+CMyiG93gDSvbK4SHbUwknYuCv3UPOdvo1DeGyMWW32uJQ5T1/MwzczOtEgO5RZC7fuMZiVQ07n+weJrQZlzYkvgnY49vuCkBB2fgh4qPQeM3nEBV9Y4hu3ayzdVmm4G20vrNruWzl+Z/nhtR4r+8N9gMVWHwIPK0YNeIb5Pd0MY7FCCqOkp1WeKpnlfZlNl45cfODSU+PGLmDaehbUrElMTxTSedcAWhLgKzpcw2IBUgRMfD1VzjqaIN7UCTvvUdyMQWVy0TSdq7IMEN+wBh+rttxMbjuRcTMT0iqJFZsDsuLRwqO6sNVmER0fFhg2SPhI4Mu9lffCww9bupbne6/4A3UtARiqtxWd8rCchC2+ZeXqAkvRCSVCPNUPDUgAwVDeAZIDu2sAR3N+8mfKkFBQwMsSnLWVWjWeh12u4vUZg/7SkjpwVLNnlfVu0YtAQ2Fh0Jscajxw7QuCmwwML8/noy4XH6tHhkGqazJkl2A7qQJ/zBqLnMIRpwzQiRWfYWkRSpTl1L31CRjSAUJwxWrmkdu5LecbbP94ABl8Oc28YLV1FUMVlnQJoZmUAyvl4W1IinbAt+BOfu2OMEuKrMS6vz/DedP04ICZK0wc+jseVZYbO+R+jEgLWG6iQ1i1ksz2c/nTMNku2ox0Dsw/8jfd2QUeAgvNoA7czTouWFa8ytLJ7NY/8Q06JwVWTQrmKlfRWq8Ni8Nxqu0CiGntK5xj2ZYsQlX5/X9KBbMP8O4fZX3uPP36/gYS9CfyzDUn2zL6UXdPgvp6IlHvWqDjISOuXbxxOFzWtLceKzRkLpMgupy1yW9fJe/SCRKbSeLLQTDrRI0NIpUxhthMoM24CeBIbJ68s4NJZWmzthGbEWAqoJquGhuDM8XP2s0ZmzCg6qD4ulgGuXuPESnxMIKkWRQ7xcR2AE1aqCH6LrXeonBk233OVvF81FsJOhw3auI5v98rOnFfITt6tr+8pO3wFUaUlMFr6CL8nBjrFNoYjQ6AKZX5QIqqvh6oT01VGc/2BMW6nRAnV7MZtZuWfHX7Bojzlyr2SU+GcFUW5DYIHNwwJ1hvgh34FwiCAg5PcuDslmK+H7UF/aAgcsx5fYMTySeSu3ZhhHxBwZsYv8VqU36eCA+lfWq7c6VlQ/vh1wZAwczxsoMOQDoRnAyHER1ps/lCqo67WsS0Mdf9pI+1KaFEwpINxn2SiI/PuESqQGvHICnfbde3nVTs7hv7vA2jTlJBckse9E4EFN5lfv86ZmKKIO322B0ijUOJFeV6RQqdPSR3903yLtsT6BkKxZp+EiRIoUrIcyw/4IgQRlKMsLglTR6Sc2QOoe1dzwSy1+yWX0p23vhAUbvU4h7YXg9y+LxqmHJ5v95DjKJL9GM7tdPdApv29Km3zNdwfhAe3spXa3p/jyILuns56FqV1CB0+FEFjhXlTnVa/CrfXuTTIM8xFqjuyKzCmfTTF5RSK8GL2MJ8yCIN/PLbCYmlwznZDdAXl2eHIvQORNvOaaYOpbCwdjok839RCWD9vrXJz6pDkpDIFdwsRoERW24xz5xBE4Xnx5WSRalZiTzR5eoyShqfkrBICisUIrLWYSRsaAYbBXRHurMIYSFyZE52zw9i658GMOsVM4s53xgLRI2WkFdAC7WSuls63ISfamLKzzVk5Cx862BLc6GYX3Tkb/TNFsHthhAJlTH4tseAlDypZbKUKgfYVARZfCZ4oKD+4JPHz3gDH7H7wmRQ9c/alQT7qXIJ4rrLgjxsFQt4axl+gJhnN1rIdE9FuMH709EDNEZKyhA7qi7vZoDZEbkLr9UgDNiQ8KRVCbQ1KcahGmgy2PtsnYg6UgS4WjJFQUKN/fKWjUFhoAVRX/MU6o7RjVhQxnwAP4Yz5lHs1opOtc5Wyo6xlCO6OjMAIB4cuoulRHeug765vmSdxoHwCyQppn2S5tPSbRl4DbYD47xmMnFe0GkgFPN4x5t3kvaFzNi/TOGc418KRhANBQq7ewK4R/oT3gDab5xC73vibKah+G3WdhdDWLHxseJRV4Ec2WNGrMaF/9pRhyRzfMcpWhN5Oq3d/i0uTlC2x5fO0td5oKMDIvxdIGmWIdCfJuT5ABzhpwbBobAL+m1GtgFHF1R3Ef2cz7jMjtPhXZhniQ+ehrofRUffHpkevtvZPvEx8d45RHVqYal9jjajWRi41JvJhuZtC8/oT40Ja3dAwU944JgAj0KCfR6DgbqVhPSil01Lge7bdYRooCpq5byMagmW9LLfG3H3aycpMA/QHkUZ3fp4onFihaJbnj/qky3Z4Cg8PUMV2o4q2xBVWBdBj8GpPpACY6eC7APvZ6UDoeyIyrpGYYtsDEJYXwA0RaOfRko0Y97Fqu7JzFNNM3Oap8PB6xkwlvyZHZPnGqW/S86Lma9+Hvb13QynRmf9PNjRA6z0Xa/wSXe1vj1+vHO/8MOiivAuaYlUPGMIQv26cKT08shfOhTh/5HR9jquE2T0MvuQkzFt4SL77BCY3J+zHuXciqnAy3bBk5O90EUu11k4IvQpNtzG7YLUH2Evjj2+zxFvoimMKC2GAYTqGW7BlnxmGhwTFnnYWkDBBE71tVsLoH3ZT+zQfVJ42dMmhQ+3ngKolV94zpg1ohAKZAAUs+tPo9dJPpzV4Kc+p/RKC1CzEoA776C6Vl9C0wyEpen9TBwcQT5ISPaCXvoQjHYzikZa+0FlHQTv+Qj3xRPSqgP+iQT68DCOYeS1ZE3+HHUHOPc54TRidceeiDnOM/R2FfYs5B9a9TNE//2lCDFdWc+qBnMgmb5ekhixi6IVyGGvKlh0yk2XMRsDWUBPyLi+KsFISwtIlrovVxVafFzCRedCJRIW0FmDwNWnH2dVBb4p/XD7gDkQ5jj+1S2CtW7bL90Shu0XTHoUr7eFQKl0MUgIRZybP/uuNxpsJBcbAdVUwtgpYK8JbezmNRdh4ZdyKw1PbREpYmFuPwr6ghxvpsZlw4RTYkKr+25+CMLhstHl224FR/IQ4OKzMkTsZplHZ2yaB2PhbwE08JvWExvNZO2R7EJth1SDynqnG4TgJTx2qb8dC98e29NdjIj35HQ6xW2qAC36OcnYYnHSFI/jdJc9nexnDJMw9nPt0q36+RtHVvd4/nRcNmxDjOq07Ufwt7iPjxf7RiLs7ZyPBm/Xd+CF+x2js638wJJSPTcDw/jjLFt6inKB3q7brnCFSEeC/CmUkpXN9/4CC5Zprx5b3t0QsesbLQS1Zb9yVVgXbTRcnn2+3OqsH3UfhRQqsy8XSdc1XdKYp8laE6E81+igi+ZPoj3tpRoChMmR7QHQI8L379xBfMiIdA/TJw4N7oGnzXO7cXFDyUcxbB+yJi7OKK4pHzYB4W44ZtWYbtPRCzKbQuiciSgdx/ahH+JHzCdP4xgzXCvjguwOb8+PWIvbEkP2g8Mf8tSPh6d2dg3vKydlg05G4QNpvAWdaXtyzSeHx0wZCYUlWxUy98DgTahuoRDIHw4E5g9I0Hnr/7C89+3YExClOAs4/eNtnE3D0WrsAWDvboDvyOtpPl8wzjhtfW1YUtBwUeJ7LftTY5bA+DXPlVWfskifcFbujs5RY4eSmrvf2CxJcyLDG/YmhJ8TANAUuy5HG94g4Pf4KwoUuGl2zTTNiGfefOBr7pnFCMmRNugi8jPrC52y2bu2+IsgPvTh4JVk8Rgc8m3bgzNu2p+fJreXyPCkRZwkjCaOM91Dyerv2XXtSZzHNbnAq6o8evgsYByl+Cc7uUlEIZ846WQEG+Nzg4lKkIsN1rpTDM0Ghs6EnXpAuWWojJ12LJSNtq/1GudGd6LEdbzx7FVl6qvoEX93yYe/nh3WFE83+ZZcWjpMqIVbFlglpr2jl/fA2jFTa1JfChGTgW9God/jdB4hbPjh3+T0Ebdswb6vin8BTqPCz7tAqxu1rc/7u+ZUKHZwYW7px9btVWL9c2y4hP5Oph9e15vbog7+gZAr93uARDg1I+8aZznnMWJrzFAs2/OGkJ4nljGYJOOGjkf1vRE5GxA39hSyfkU78HsZCXrrv8rL0B41v37Q826apahZ6ay5WRw74fC4TVEUwaW5Z7nF6VDjtjGkXyT1Zzvb9+nOSIgfMW6GnAkeP2a57AuwCWj/2hdFSLAvgAbiGSA/8nLSZ5jirrM17+7UbCT9TORNn2NtyE3YJ7Uz3lrqhDf8mzMIidfsv1NBsXd+dt0YXQKb19PLehV1zTpTqtv0bLNo1eIBnQIhDRBNcxU0hGI3At72GqmuxJcc2t9NxsyfDyBOpfVoIY/+fE+w/nn3qg/o9t/54HZ4OjK1zEmdoU8sbgvc7iNvZVNFkcVVBM6Zy+jksHrkaqfW2NjNNCF4cO0Jndp4DVdY8F/F4MPyj8QjkiA1y9aiD47rwEIPunv+8u7fz1AdksPcbqPyB5mctxUPTKAatFbIlCfOMJUZgYHTOeWRXWybgBBvEknnbozNgFgypq7Xd63QJkfA+s07PMvKo0tVTJe4CTKQOIZgEK0rVKZ+CyGgKtH25fiP0H6F2QhClNlb8M3cqPokfD1VgFceWfsfSEbVPE8dKGBq3mfrjmBQRKe2IIMp9AYPEOV3w6zS5OfvG1oLd9qCEwLbzqiV1H5XowTmqM+uDuc7jEchdemS4AF0MbZkqL1rNAa4swgPGYbfdRdVQekqWCDBboYw0IVHx+GBMQF+4MbcoEOhwwR1hnF+V50qlwreDm7zjupmHIEP+0zP+ONL8zw3Yp64jcL+MXphxMWAy7bUC3xNBPqAOVB6BtVIfTvwut2K7BlPMCjh9IyJuCQCQ4MCmcYcDhafuTTX/4hKdPXw7GZCXLtVnyRQQmb/2Y/8B8gdNONAY0XwFxCFyrBI/xR7DntrXVSsTvv3NPWZ5Q9dPVVNz2/pIQO5/kzEZtOPxB0ArEXHlWY/v1R1OIZKLn3eKXBFCFHOjstRzBDHPfYaaYeG2haUMW7KsuID7T5iS5fyjM06Vw5a1TXgwPkHPLqfM+oc5/F6utGgHP8TSBG9DRJ/dQ1c+MCUIThpd7hNHWOgnbjgi+VzOhXtxvBJmg4o7q9cpzyrTpd9FcRurScywK4hrTXVNERpwjQr9rQnxGaB9Zp9GBL+Y51BCNCTsCNZ1UrUPzKez114f8r43+/XVtk3H56Fx9NU4r1BzNixXdN3k5xp0EEZYVA3Hd22IN01Wp2jEVzIW1iqmFd6mqK5OeByzB7V7ArR0PBNV9RiAW79nBP4WI4fY8EuhzxEQr4j5CITpkYLRkb0V5i11/ZoXa0AuQwfnbiDzCMWiDLUlJ64dU1Qsn4K/XarzdYkiesB8c2sri4TSGW0W17y1yS83Z7NzkR53IHO7/qDY7phnqLW9xz6KuRrmwHWPcebJvmCfOf/EYjO95TywZY03O7wSegJ7cCKXyB2Q59xio4mHnPxxYyG3KA/tzCI9IqVhxEFwK5xrq4vBYqr/Nq7eotQ2rTb4A61ezv82aJI0T+EmJCecCqmOvsp2PX+jy+NLCp7zSxL3vv4pKxakLtfOVwWpVQtJHMoRPqKjxiQAHhcVWBdsnirCjWG3T63IyYs7/XjLnvMtfcgARTCYNnfBIl4fbhYa33nZKBvVU4oS1bgcSVfZutGmhWmaIfdyoffSQU4kmFSz8T5m9/aDsP3B6OPKzm+jX7wr5+5vO5xrEjbf4UgGEbFvqgTHcMpA+QKSVZDpej71zyGoeTFH1pQxodxw0equwFc5geqlYNCHT+Vd/OAgJCxI4GhVbQctOxqiqejZb4UHMMLNnu+/Pa2vF8Gs46XUmxXeOY+kXcyM+0AmoVC1D1XdaCeu1DOMUkbeQ/mZqXPVsg1q+aIJtT4NSdU/6WZ6/h8ViRd0QRxIzho8eccE/eqWxK3KBRxZJdxSbGg9zJG0B1VO5LbNCBBa3b8DBEP2cEnxpIqTvLc6RmeWte22eke4bod48K9bcoUPORlCF0GvAB0DxxTij7fgtgdCx1351WQ5s8otsVVZM21yyPE9Qazf3MEKzhu55s6EfONZ1v72cyhRutF+S/hGCcdnlu2tsQlCct5WTYlHb0LkHTuGnsjThMQg599rM76pCMGeaEEUA/06BnfcmPSv3O+nRdrGbok0rNs5RzHWZjO5W6tmWTZoY6lxHuEfK4hBMHy+JLoOQ5iwnEfKbQrTT49keW8Q2IYC/PXaay5iMDZzRTvzLsenCNjX7ktVekuZRAgHhRGnErQ/0lhnhkGjUw4N/4xnSg00irLuXqcVvfQKI8s9INde3xf1PWsRdflDj+zI9Xw91dkdNKl3JU+Yapy0Z71vIs3OTDERvc+GrVu4eXJykW0F9zEM/bJH/5ri3Nncp5kZccoIuuGppSfy3p1Ent2wqDSJ/JO/4u5MgD/+TZevmxUAYdJDHhRKNyZkTU6M4LHeb62VjZnqRSNoAV4QZiSFabl/U/6mojwPxMheWBCdyqO+BAiclxfNq58C1EPnn1L7Gh1V70zb8PPS2HPs/P5u4G13X2CHLdyzuOT1GXN/33x/2VVkF9Qk0RUJMqmHTnSlt/6X3sTgGb0BfCbkQDtT5jGq4uuJdWnBgclwGHfmV2r1E+yr1eliYMCV1UPdaoWFKOwKcv7jtuRCDALxVGPnQzcXEHBr3ecMH4MNI8jV8vL94vftlhjmwVBFhgk4InqQ+q2WudZkzokk+HErFvG22/fPCtk6jfvDg+91rkBi68yGMqli+epIhtMiJNYlTThkKIqerjuMEGyEKpduzL5bby3H2uNJzfsszJoR/0QA69uAkQXVxNYzMZHYnlygRLn3QrMa2tMezf9TSYYwHbCq3MMfI565Y3vokPngBl60C/vg+n4qKbj+Q8geVVAPv3kW6jWGc7vNYZymrNmCnSm0e17OQ0/o9cb3pXNMajZKoVaBd3FMlP8wCCn7LeBEE3cs2YY5gse6W21N3DNjBvtP2POO3/cyHJZ7mINYiUj/6qEj7dLkH/ZJxxtDKEcp5H0rfzmg3Zswl9oYWwNuKG5meBl2n9AtTI26uQBCn/gre52H/MHWja+bLGrOtjx/+8c5n/oeJ+JsuL7blgvef7A1f/VSnOHa3821IKmJAL52j8Z3ku2U2Ih2k0a1Rwtdq1BrmzvKuUfgulrwJMI2hSpSFANebmfxx/i54nvYFo1zUigcOgOudJLHinllS0kMl2HOkDLwv7qrrPnBVm+qAOckveCVGPDP/zIAFrRjYE0EFs9LCe+PEQ3Ejccec268zfF6pmXbV6nFDe+dLyJvUczND3a5rjTNc5ZW7QcQ0T9j
*/