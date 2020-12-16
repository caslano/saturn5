#ifndef BOOST_ARCHIVE_ITERATORS_OSTREAM_ITERATOR_HPP
#define BOOST_ARCHIVE_ITERATORS_OSTREAM_ITERATOR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// ostream_iterator.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note: this is a custom version of the standard ostream_iterator.
// This is necessary as the standard version doesn't work as expected
// for wchar_t based streams on systems for which wchar_t not a true
// type but rather a synonym for some integer type.

#include <ostream>
#include <boost/iterator/iterator_facade.hpp>

namespace boost {
namespace archive {
namespace iterators {

// given a type, make an input iterator based on a pointer to that type
template<class Elem>
class ostream_iterator :
    public boost::iterator_facade<
        ostream_iterator<Elem>,
        Elem,
        std::output_iterator_tag,
        ostream_iterator<Elem> &
    >
{
    friend class boost::iterator_core_access;
    typedef ostream_iterator this_t ;
    typedef Elem char_type;
    typedef std::basic_ostream<char_type> ostream_type;

    //emulate the behavior of std::ostream
    ostream_iterator & dereference() const {
        return const_cast<ostream_iterator &>(*this);
    }
    bool equal(const this_t & rhs) const {
        return m_ostream == rhs.m_ostream;
    }
    void increment(){}
protected:
    ostream_type *m_ostream;
    void put_val(char_type e){
        if(NULL != m_ostream){
            m_ostream->put(e);
            if(! m_ostream->good())
                m_ostream = NULL;
        }
    }
public:
    this_t & operator=(char_type c){
        put_val(c);
        return *this;
    }
    ostream_iterator(ostream_type & os) :
        m_ostream (& os)
    {}
    ostream_iterator() :
        m_ostream (NULL)
    {}
    ostream_iterator(const ostream_iterator & rhs) :
        m_ostream (rhs.m_ostream)
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_OSTREAM_ITERATOR_HPP

/* ostream_iterator.hpp
P7eZrNxHJ7A4VBZ2Xf4Fhzxext5ucIVlPa7x4WN6wpIiRfmqkMrQvuI9NjB+J7ZeHs4uTymCSx6uYZjUC5qaOvCe9oXxs8lyBtMuYuER3Vj97RWh/7ilfPi+C1iteiRcuVYOLxdJ45r8cfDoeDLeWh2Ozzy6Y9sJ/WDx4YNsQXE7LH5AC+5jz+H7whXZ9mGPwWd9Mb429U9Y62kK+vTtgQeSfGBY8bOwavYSuFt8MZ5dHI91JiWBZks8Wxg+CtJN6/K3a87i5ahKEGV+D3uZWbLjN8OAn/PEQr1+w99erYcK3lo8EzMYDj44DNsCi7Crlr44330hPMm0wLNbtuCsQx9hx4ex8KZMCAw9HI5GF2fhj+ZryZkegbGFTJjtECs8vD8Aqt1dCtYebfklu6dQb/BrXnejCWywfIyLndbBYJcr2MvDCEcN8OV3o8fCGZtBfHNLR+xqZ47ZpX7DkcVMeNLV33BZRcZ7xWXDmxNvsLFZHP68ZBEsN2cwMTQBuv0pDmvCLFjY4DkUWrWKdfTfjrYdykPr4g1gwu0l4JZvMpo+3wVFzjXEnYf2sHXSRjzodoO9XXsNyq+35VcLPYZTw9vgzj7WkLh6J3Oy4WDWKpHx0mtpXZfIy1i3woruI7nV0crwYXQUr35qKgT/uAbOfa6CwVY1eb973nDWLAkvNx6Mt8pkwq3jifB5+3Y2LSgOns6rgZevumKpmuV4SsuWMHeiMTy4HoCs9GWc+ctDeDWkEId1F8HOwRIZmuKrndM4vFwFZTqMhoQ/1wafo9E8udwcXHjnIb7N3wnfzNTy23264E2PN3ztkJ7Y4eQkqFzKBFPGtcW+HfvAjRk23H74Hbg/tCzUL7Qdzjjas1G8EsxZfBlGObrD2fLrAB5MgIOfI3j/t6vB0cqK1VmZjc063uNDf9uPx/pswZETu+Oknk3YjBP58dS7xXzqsklQZP0dGFmnNLLVU3BqjRpo7b2Cr1l7HfzbpUHv851hidsvbFWdNHRBwAJJw/AAmwjTPdPxynNXNjixIeyPWYleJq0xLd95TI1IhqNr6rLFD11gmePPvLdDMOxw2Mvf3xsHp8a48YAbj6EjT+MeLvPBce47/nTcr7goZB6ftakUlKleEocmPIY9H07w0fcnwHiPjbhyWBuY+utM/uTFOxi7K472o+Y42LUtdxk5HRJvvmMuiXFYpesVvq9DSby/+giPLd8anTKb8NQyC2FOs768XqWKuGf4CpQKvIDE6AB2zd4IA3xX8ZYHhmPYzTWs452N8ODOSWgem46f3pViaftOg8WRMXyIyyH8cUMN3ti/N9yqE8THsyBY1Ks8vBjsiJ8KPIaCjUph15iNMNayERbfMwzuRm3CwG23sc6zV/hqwx3+rkRVWBcwGzs8scXYrhIfsOYZnAs/z+4V2gNjm//It/aZAq/WBuOTekOxbcAeiB2/EzIsroBVoUCoYObD2lztASZzSmGFQAfcvPIUs49rCwUlzl/x17h66hEcNrAsbk7YDuO8LkBKgSrY07oSVF1giuWz5sOkM+GsrbYllrIK5SnzT2K/W3dw0bqasPyn8rxeXD40vVmWXTjQBeOGPGLFUjU4pPEQXpH8BLYBbjgxTUI/J2csV7QSbOzuzhzf+sLSsc7QuvFvOOO0L1YoUBX97TzZvFTybe1qhOXTi4CN8xteYpYrFivvCnU6p0Ed45qs4oSpOGtvWSixYjS89trF408E4/B0X2gSm4nFKqfxNg0K4+r5o/ncmieg9Zae+HP9dVgswBMv7v2Ma+vVYSkXhkIa9c2iDxZCUI0onm+GM9hfGYKP1zVC//Et4W16LXyY/hTeHkyEo9O9YOXmPljycj8=
*/