#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_IARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_IARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_iarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_iarchive :
    public detail::polymorphic_iarchive_route<xml_iarchive>
{
public:
    polymorphic_xml_iarchive(std::istream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<xml_iarchive>(is, flags)
    {}
    ~polymorphic_xml_iarchive(){}
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_iarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_IARCHIVE_HPP


/* polymorphic_xml_iarchive.hpp
6s/VRCWYHlF/NjyiZtrZHCSt5hWJyfZxnnZsBTizDvwsOtLUueJPNvoS41zxCFXRNnBEgMEUBcBZfB3n9fAuAdR8I9wG9Ef/tpOy47pbycDHCudMPwIMDf4jSq+1+0cWHcnwtpc6r3Bsp5dRSz3H87hIMjXbVYro9yGXUlWJS7hZiRn/CFp1rh1lBzWDURcPB7Li+znMW0D40zQZije9/Cp1tvvZWQvRP9JM6SopEtE9Hj/83ehba/rWTkbun0SNna4aG0nZA9lP50yi7BTXvs9wRUvoN7YlUJwrGpxnDBd0YzqbHkBEgLTFeJj05V2ZS30Wz4Lno+9pQxVdUvHTPKnYiysiW86MyV2+5D/KWXI9+4RFvcygv71Sgiobm7CDrCoxspOpjTEg3tTGiDyN537lwWqDXTX+TKatXiZ8DKsxAj9FPUCrOhF/Y78Q/y0lyHndzfe9mvCJ6DKOGzobQ6AAox3AfAoLwXzSdhOP3t86L7AJVKk93zmsKm1nIPGwV0I4lFPivJiixR0CNm+4O7DFlMcyD7fKiBiHeROeNz5Ohdr7F6LsHW++n/dsaL5zTm6+TX5xvmTyj7kyMBSEywjlRhOeEXsKJyz61ZEyP5qTo3ToMVaONled+o6mUt/EKH8DDeJDo5X12HM9DI2CB4qURgE0WmA9IrGXqK8YXr9qsurk8B4cyaOTh5fF05qjzJHLdD3RhkglBWdUQAc6wb+MYt4NRFFeHhHdIyWdRfxGxK+m9miQls3JgCTCO1xDziBCUeYP0VB8+WH+nqZBGWD5Ef7eLUdDo67lh/jX6Tmrcrpki3NrfMtald/FteqCLkP94biLjNuR6yFzgVgnAPtlLBQBvdfZEgNqO6TSMAuEF9u0XXLKH3Nl/5ls+t9qi35ZLRLo+XHiYTmTg/rR/TAzgjkHE0zw0nOACV4eczJ4ifveBC9HgZU3BpSgP5PVef/Ziv4UoEZZ6eXPUc5y6lXe2Fg52sKEpEhsAGngh45m0gT0vfA/M4VCgWTjUsxzEHHVvGeQYNyXEeVtzrrGOBjp+sWR7JEgXtied6ItsD1fVo5t0CA1dnmYMZVToBwNPGY5zEOrTpb/Hhr+TD1LKDeOecd2a9X6XvClUZogxLY8MCuY1GeJD8LU7vLGnxyMYHrRsP/sbtzgjxcHb7C6qXsCiQtmyU1ta97Uwc0lLsQTKPJaAhHzCxtzWyf+HGXTP4yX2zoreFunWm7rOMttLah1W4fQFX2N76q6p3x99bebmLLAtggLwreUEJ/nmrHmTici9F7sKwimuqgb+4mgZoFYoOJU+PdvPaUfvg+0v0mjy2Yx/6ubscgLrzUXeRIJuatLR/UKJLa4BousHOhfw8jTX8OJx72OmctYvO+yhN+x5btqRbVLpBB38gbZqvBvcGdXtQ8kbrpa9qsDrrTs140Jsl9fo9wrtF/VZLOvtmx7Q1v29FFs2VlNecucxaShZW6bcyWpdMnWyW+Shcv2yW+ihGtt4RzawlfqbaG2gYfpDoeDuNF2fW4qoXmvh/O0jw4RjsM3+jDmkx8Fsyo58ytvN31PtLnvbXJKI1Kw5xKLoMzJbKZI2tYO8CsgDT0vDemBTJH4Pqj0EtQCs7seHI2n0yT+xqygp4H9/xKkODUfKzwfcqZpb8Fh+Ti61jszsenMFaUFaaXfE29TYb8SLMBb/yyuVtDCiEaih7X6f62LxFdcFNFSxuAsfoTJtEUOm1A1vgx8WcNpgIKnuaEfcRoqur6tNjiEM8gNNfEEFx2uZg8fUym0C7YpdjCxbN6zo/i+r00eoxNFSXHowgi+0+must1CBXw4SDg5Z2UYER4uTUTVnDb4Keoa2OPg/P8=
*/