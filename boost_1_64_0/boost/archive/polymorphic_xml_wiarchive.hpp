#ifndef BOOST_ARCHIVE_POLYMORPHIC_XML_WIARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_XML_WIARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_xml_wiarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#ifdef BOOST_NO_STD_WSTREAMBUF
#error "wide char i/o not supported on this platform"
#else

#include <boost/archive/xml_wiarchive.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_xml_wiarchive :
    public detail::polymorphic_iarchive_route<xml_wiarchive>
{
public:
    polymorphic_xml_wiarchive(std::wistream & is, unsigned int flags = 0) :
        detail::polymorphic_iarchive_route<xml_wiarchive>(is, flags)
    {}
    ~polymorphic_xml_wiarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_xml_wiarchive
)

#endif // BOOST_NO_STD_WSTREAMBUF
#endif // BOOST_ARCHIVE_POLYMORPHIC_XML_WIARCHIVE_HPP


/* polymorphic_xml_wiarchive.hpp
kk8kLyhw9rcvGAvkxV9E2WiM6ceqmUfBHFrhUQzSUF3xKHqTb3TFoziTzYUMArfVqnCGV6tG2FeNCstZlR0uor0TFvEZ7+OoVjx+fho3F0zJSqAA5F7zgcOK99SyT6Ob1jyQ3Zr7hq39aZIL0sC7y0jmJNAVEUtT0EbcsnVwnIOnyOZ9YTgFHdfe1jeJ+4aHfdkJEZYqlA0BEJWICmM223KUCCuzN8Ltyi/Pb7Twnua2NNgil14R5D3hacWpyAngw0JjIgmwRVnYPvxxA5kNbhv2C/bNGfonNQQYvC1MJs+nnYUbC/7iFDRmsFJorbr7cJ5gWUZkk5UHoGo+btakc+cLJHj+hizIqMOXve2Ngq/u0/2bfYfDvDF0pjM3emL85fi2Ft+eh4X1XDKRK1L84lSgJIAmxEo93QNxcgKnx6Ulb0zbiVjTegwS86cwfnkBxqhJzZzMNz19gdUjhA1eFI7+EP42iuclb2aNz/Bt+hbYmolhA/l+cCaAK+NsFiUpyb++Zl1QnkUXvbXhVv2R0xQ4cPGrClV9Cpu/lBCkgbmkmG68N8618QgSbQ9s1+fZ2C79IzjddL5aEbsbxiifalWuVZfYK3WHaxVPyeoXi7bkxF2UW/kXgRYySGzMYSCcIJ1arBHaibTDRD/M+5VIc2BdEkhsNZkjgbcHBpMJ7OW0gcAQLMNSnrpOiK0g/HKBodeo8dQAe6IldQOQsoJsoIcoyK5g87qBpe7vIJAepI8MVFuk5amXVOntCIsmRzmGau0GVbOEa840/Z/WrVmU2ZMBtRdUYxVH/fSHaceKMlO97Zxrs+09xj7+CW6UryqM/esQOv3Zh9WI24BvnKKPaMm8tqnuu7LS+7b2XlwcIF4N5exMZM293GP8EzZEqXuqA/ydLkMhiFBgE2JX+SSL2rOn+vujevTyERFi6VzFe20ZrTScGEXswcvUy0E8jfKZ8nxsT6bnY63eE+Cb61rmekKn5cQ/Sv+rWVCfqfkn1YF6/j8t+dND+MOYasnvVF2/fq4l//mP6+efacl3RYfwf27Jj/m2fv3PEyz+zzuGiH9iye8Tov9HLfmV2KZ687fkT+8YYv6W/Mmfh5i/Jf+HD0PM35LvCtF/pCU/5psQ83cG8+216rs1e74WBvegij8CZ0BDM+JsuDesWPoN3CuBn7rJXvWL9uLNCrTdZDLOFFVqXmbFvM65CPudC4DSyqVIqkNC1iqSai+TVPklzdwlYVXHhSfgX7G9QT49ipDOCmxp4TR5xaVMdxzWbyLpHlEr+doWFijRNbKJoJ2FSkUT4m10ZRoSYyr933ilUfO64M4juyut59+DRRza/5nUgHAMKJkHQCY2kKijP8YOA4BHNq9fITf8I0jKs3tobQugJFlJaG/U4XaJrA06MNB7P+TOPOpJcq51BhJXS9soth2JXj8cA2V+4onIWjXfnpWeJnYRzpyP8bQwFXfS+MwvxfeRWZc2VRC+dOy+tC9zYW5MZmz72MCT8Ea8k9iZvIMfY8zu8kA40J1ozO7w2d7LYchWGjfY96k9r/ScgDtzkyduaNHijvYUZjrAsbri7RZvJEdfVQ5nMSlJU+DZtcwt2wCn+9TL4zaRABFri6T/9F2iIB/07T/mv6rUdf/A0+f1KXXtGHj2/CbwzuV2Prx+TicQ+d74mqpI75UvU0+BDf7sosM9vRfXVNm9Y31bIvx98c3TA1HM8pLfcCdvdOO1n9NOJOoUzasry1wCiYnj+QUN921x+PYfcQc25pVGDM7L3Oi8Lga4CnUQA6WkxRDZvEGa2HWpZezKbxz6Jms07Z+yf4/l3RteGoFQK98WsLG4ewBY73Pj+HSm0sigMovo/5M=
*/