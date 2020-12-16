#ifndef BOOST_ARCHIVE_ITERATORS_UNESCAPE_HPP
#define BOOST_ARCHIVE_ITERATORS_UNESCAPE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// unescape.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/assert.hpp>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/pointee.hpp>

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// class used by text archives to translate char strings to wchar_t
// strings of the currently selected locale
template<class Derived, class Base>
class unescape
    : public boost::iterator_adaptor<
        unescape<Derived, Base>,
        Base,
        typename pointee<Base>::type,
        single_pass_traversal_tag,
        typename pointee<Base>::type
    >
{
    friend class boost::iterator_core_access;
    typedef typename boost::iterator_adaptor<
        unescape<Derived, Base>,
        Base,
        typename pointee<Base>::type,
        single_pass_traversal_tag,
        typename pointee<Base>::type
    > super_t;

    typedef unescape<Derived, Base> this_t;
public:
    typedef typename this_t::value_type value_type;
    typedef typename this_t::reference reference;
private:
    value_type dereference_impl() {
        if(! m_full){
            m_current_value = static_cast<Derived *>(this)->drain();
            m_full = true;
        }
        return m_current_value;
    }

    reference dereference() const {
        return const_cast<this_t *>(this)->dereference_impl();
    }

    value_type m_current_value;
    bool m_full;

    void increment(){
        ++(this->base_reference());
        dereference_impl();
        m_full = false;
    };

public:

    unescape(Base base) :
        super_t(base),
        m_full(false)
    {}

};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_UNESCAPE_HPP

/* unescape.hpp
Izr9IlkqboXhBWXMHe9KH0/YUXXxFJ6lqYpa80A6Nk4Xrx+l0aNDFeS47g0reXuXho85zGuf69Isl2d8wNENXxuGMk/t4VRTuIm7Hp+G+yWldDooEm0Lb5Kemj6i96ZR9WZGrkGNSJh6D69t8/ivE06wvqDGiu2i4DLajM66ZdDBqhIIl93Fj8RRPK9zMdo9Rbm9twOllj7mym3v8PC4KjmkeeBBvjQ7OEmJ+vxXwXWYN71TvcOTW2fDqmgn//f1JQnplDIFe2V8niNNaU9kYXOkkMUp1mHbquPc89VDHC7qpKz89cSVh7D+lAfY5CuG5/uTqW/Gfb7qYhmVG66m1xKrMGq8KKs0MSLz8kf0X48TdYR40jOvNjo5Rodkqr3pfLYu7xojCQPYMRkpWTrIrMl2VwsVXdJhjxK7UFamRRIZKrAwjmUKRu/xK6oVk1VM0HlUgzf6zaG/h6zZkQB33OCP2LDvpuSS2cIGpufAt8+ab8o9BqM7i5F57B62a57gzpJfUNOqzSY6rAHEryBw7CSM1FhIEyyCkTlbB5uSPKj+SxsNX5VM3gdJ8F71on+4IftYnYcqaSOS9cnEfbtKHOiYR/IFaVzpXgxMrMQRcKUQXuX2NNZkHj2P2whDbcHMcuAhV5MNR8yHJ9gxRRS6/e+pNeA77co8w8aLWCFkhgvv+KlEFz52MrvU+dS3eTybnrmYtPgC1Lb8h2QlNy5635a+Gqmh5JcNiqM92fLZK2iM/hW+Q8wSKUWetHxBHsl/KsD+VBWY77nPpm6cSXnWiexr1w8yyNHE9SIrchrZyp55nqN1qqPI+doeshw6g6b/2k9rtEdjcXUvecWU8HOVt+g/LV+m2C9CO/ZNZ/PNfpLeykjSXC1MUlMvoWKqGU79WIPEbQU4oyvJEw79pfzMK4gSHY+Kffr8eeBcMt+rSv5TDalm2nu+e481zWifwYPwhs4edWFVq5vQuiyFP2HlFDBB4Bg+WmKZgAHUVZ5FtqYfa3Usxscb1eTaJEGZMdbc8HkvqRgcJ6ETzTS5Zj//vu8trnlu4wM1Q6Dkd4nvsflI3Rq3+dvlSrRbdjp+XTJCfImtwEOMpfxl53FtwV94JNwi04mjoaDwiIVdvkp3v+2DcdMkMtQ8i2lGs9F7Yj59nptDVvWlTOyMCK3I+UlX3X9jpLMju3bnD62b30GbKm/SW6fTmCs7GqsmRWKV3wq8NI7lZ45PguG+dP5FQYey8Z7NOvYTbYNjWe76EXCRWk29Ifdx7fUntiZmBZ3qVaXYmdvhs0aw9pv1SLopixb7FNIFswK22rMKFd69PKhClqK05zGrFe9IZIw5DV5Ipn+vXUl3nSk1HnHBbdtB0nSbxROrN5I8m0ayicmU6JDG9c6tpEfJonDqN0CRvhpYtijRbkaKF6Rpw75UuGSmQn6PEn0WeUmJrcFckbkLnsMT3Np4mU5tOUxVHZZ0TvoInxKciIH38/jxlU60o3EDt0pbiPcKqjhwezPN+jaNpb+dgsU3vfnM4xLU8HAxrFdewB2F3Uz8YT2VlARTX9scRGiF4MmicuJ+K2nmjS6SrH4Gl+0HKaCpD19b62jOhwp+K6uC7iol8Xq7Azhpl0oNtelIGqvKKr+/oMGh0/nKK1H49kCDm/61psXvjVlmZjZdUTOAl0o5lqRVECpLUJ8/j61O2IiRN8+SmFEhSeqkMAnFGEx/8AAhBb749v05tcGZFuhfhq75N/L6F8kHW/2p2EWemRobUom4Dnf8102TxrymHwb3YVlcxhrSjwryShkWNQeAmd2F8wMF9CzPYM5fY1CSdZhJX7lLWSqbyfJTGv2NXocy7oJhGoo4Y69PS0LFsdI=
*/