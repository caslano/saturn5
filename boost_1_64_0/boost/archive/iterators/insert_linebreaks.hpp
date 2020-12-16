#ifndef BOOST_ARCHIVE_ITERATORS_INSERT_LINEBREAKS_HPP
#define BOOST_ARCHIVE_ITERATORS_INSERT_LINEBREAKS_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// insert_linebreaks.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ using ::memcpy; }
#endif

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// insert line break every N characters
template<
    class Base,
    int N,
    class CharType = typename boost::iterator_value<Base>::type
>
class insert_linebreaks :
    public iterator_adaptor<
        insert_linebreaks<Base, N, CharType>,
        Base,
        CharType,
        single_pass_traversal_tag,
        CharType
    >
{
private:
    friend class boost::iterator_core_access;
    typedef iterator_adaptor<
        insert_linebreaks<Base, N, CharType>,
        Base,
        CharType,
        single_pass_traversal_tag,
        CharType
    > super_t;

    bool equal(const insert_linebreaks<Base, N, CharType> & rhs) const {
        return
//            m_count == rhs.m_count
//            && base_reference() == rhs.base_reference()
            this->base_reference() == rhs.base_reference()
        ;
    }

    void increment() {
        if(m_count == N){
            m_count = 0;
            return;
        }
        ++m_count;
        ++(this->base_reference());
    }
    CharType dereference() const {
        if(m_count == N)
            return '\n';
        return * (this->base_reference());
    }
    unsigned int m_count;
public:
    // make composible buy using templated constructor
    template<class T>
    insert_linebreaks(T  start) :
        super_t(Base(static_cast< T >(start))),
        m_count(0)
    {}
    // intel 7.1 doesn't like default copy constructor
    insert_linebreaks(const insert_linebreaks & rhs) :
        super_t(rhs.base_reference()),
        m_count(rhs.m_count)
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_INSERT_LINEBREAKS_HPP

/* insert_linebreaks.hpp
iFYK02jJ8RHsF0H/NMpXYHXfGh6o6gf9KZPf2m9J9bvOVVLsvvs8JsVO9KHvOY8pxy6SRIZ2Mcoc6li2kLy+U3BSOcIqPd8quekki9z05nIG8vKF/iXjmWMFOZ2sSn9bet9Sb3nttIn/ZeOre8qQF3+gIjHkhwd+X/rRX/evwLCgAF3CEYE+ulM7DPji/AUVHa4hD1+0nhbjku67wDSs0S3zdbyxEUoMRKsSEbQqckGrIhd0npETXxWpGEc6qyMWtGIjvmqsHzlV+spQotDyIQhqur9GZavmh0X6++nyHRkaG6XiqwtCtFwQFa0er9V6uhMd/BP8AgOjc/O1v5M+neEQrQmS6TiasUS5tQnhCq3Kh6DVFSpodcUNComws82j3QVfKalSUBV/QGRIBMWopw3iEymq5Hk2oVpfXQNqvjYqLCSGLAz0VSWgSGOiI8Mk3VM7v4hA5VQy9X0VqT/XXWeTI9OER8UkSLralbQx0bEBBl/nB8OjVnPaQTi4/UP65/ADwjR+EbFRim9Jf+LNV/kIofkxOloTEKOkmRAR4xef63lKbFigbo4RuRQTieLSplE92i86Z+Ej8iAOmw7zyysh8qvn6jJ+4mgfg7gkmqsCKReD/LRSrFadTaA+p49AHTdlSJRRHOFBVeYXEKqb+nSFio2Kyascuj5FtSWKohzdTDmgbupPzaXkLy+72IjfqwF1yKlomsSpHdVne3z7eYuBWgHqefMrv34t0eFqGWRFae7vTEdEpUqptqpfWSk8qh89aamtHximjFAdwQW6gjv9dwM7sIX60Abc6JMTnMWpRV6RkWHBmrAoO1vPCPppquBIfct0EufR2NmKH1BT0e6a+Bh1uZObTWT7s2vgO8ujzPd6Y9jp1hKPtm4Btm4r2O0VbujWYjnGtrSALtMcMc7JFJZp07BASn0Y+uAVFk6ZAvYVjsCuV24wYkptduBVSRyydjD6j2gDCakzoLumCv6p/wKY2NMZX9w/wJyLbIcTWeP5c5d9mDmwOVpiU3TZsoMnnd8KcRWG8XwF0zDbthN2O3UcL439gOWtA3Fv6jZu7h0CnhcWs/xafzDe2JyvaxyBV7ebY6l9a2H6wiDeI20jRg9ewB7XXQuJJi9Y2tNM2JT/GtgMaIEFWp9HowER2CWzJF4JPYTOc55DyTpheL/bQGbbZiyaDygEtv0ZerA1rPrcKmi2Zjdr0vMRai5+gtof2sHptZ3RtP4L9Oj0AvandUTzSe+hpocbHugWC93vrYWFfz7Pjp5bgbNbu+Gm22Y4ycOfuV17CSeWRUP99Lmw4IdsvmBpMG4p9IkHRlwG0/yr4fGL5VhpziKmmV4Y+eK2vN37e+BdxZbOLliKB8sFsxGtR+Ah225osjUFa374BbQeS2HUg4EwzHsG9GpzEj67LYZKGAcDP3Bo3bE+PEj/Ae7H72Ez2/wA44Y+Z3tDj6NXwzdoF8PRbu9KMDLfBK29lrK3DlWgulND7vL0INQb85otH3IDpIhSaF92JexJawePN/vCyxeNWNOeKeAJXjhuaSD0mRzPg4cegO0/tcQPtbvB3JF1mO+nNzBnTiv+IrklSE0WQr3V+3Fy8lY2qvsl2Lt1Nv+w1hTbDCyNN/c0w9YFs5lLAVfovjCMN17dE8Ltr/Fim8visboD8MWsdrhi4jBcsoGBXe2HMK1lVUiJ7Mt2e7rAVG198JtjhuXuVQCbq3dgYMdMfnheUdxh7YumxSpA0tH33OVwMxht2YUPG9Ac0rJ+ZCvutoaLy93B0n4OBHSqAM8XpmLqoQusfX0vKOVUmzU62xl+GTWdr40shz9VteXrap5C97cxcOHGPEhO2sIc6paHX2o1Y/s=
*/