#ifndef BOOST_ARCHIVE_ITERATORS_TRANSFORM_WIDTH_HPP
#define BOOST_ARCHIVE_ITERATORS_TRANSFORM_WIDTH_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// transform_width.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// iterator which takes elements of x bits and returns elements of y bits.
// used to change streams of 8 bit characters into streams of 6 bit characters.
// and vice-versa for implementing base64 encodeing/decoding. Be very careful
// when using and end iterator.  end is only reliable detected when the input
// stream length is some common multiple of x and y.  E.G. Base64 6 bit
// character and 8 bit bytes. Lowest common multiple is 24 => 4 6 bit characters
// or 3 8 bit characters

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>

#include <algorithm> // std::min

namespace boost {
namespace archive {
namespace iterators {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// class used by text archives to translate char strings to wchar_t
// strings of the currently selected locale
template<
    class Base,
    int BitsOut,
    int BitsIn,
    class CharType = typename boost::iterator_value<Base>::type // output character
>
class transform_width :
    public boost::iterator_adaptor<
        transform_width<Base, BitsOut, BitsIn, CharType>,
        Base,
        CharType,
        single_pass_traversal_tag,
        CharType
    >
{
    friend class boost::iterator_core_access;
    typedef typename boost::iterator_adaptor<
        transform_width<Base, BitsOut, BitsIn, CharType>,
        Base,
        CharType,
        single_pass_traversal_tag,
        CharType
    > super_t;

    typedef transform_width<Base, BitsOut, BitsIn, CharType> this_t;
    typedef typename iterator_value<Base>::type base_value_type;

    void fill();

    CharType dereference() const {
        if(!m_buffer_out_full)
            const_cast<this_t *>(this)->fill();
        return m_buffer_out;
    }

    bool equal_impl(const this_t & rhs){
        if(BitsIn < BitsOut) // discard any left over bits
            return this->base_reference() == rhs.base_reference();
        else{
            // BitsIn > BitsOut  // zero fill
            if(this->base_reference() == rhs.base_reference()){
                m_end_of_sequence = true;
                return 0 == m_remaining_bits;
            }
            return false;
        }
    }

    // standard iterator interface
    bool equal(const this_t & rhs) const {
        return const_cast<this_t *>(this)->equal_impl(rhs);
    }

    void increment(){
        m_buffer_out_full = false;
    }

    bool m_buffer_out_full;
    CharType m_buffer_out;

    // last read element from input
    base_value_type m_buffer_in;

    // number of bits to left in the input buffer.
    unsigned int m_remaining_bits;

    // flag to indicate we've reached end of data.
    bool m_end_of_sequence;

public:
    // make composible buy using templated constructor
    template<class T>
    transform_width(T start) :
        super_t(Base(static_cast< T >(start))),
        m_buffer_out_full(false),
        m_buffer_out(0),
        // To disable GCC warning, but not truly necessary
	    //(m_buffer_in will be initialized later before being
	    //used because m_remaining_bits == 0)
        m_buffer_in(0),
        m_remaining_bits(0),
        m_end_of_sequence(false)
    {}
    // intel 7.1 doesn't like default copy constructor
    transform_width(const transform_width & rhs) :
        super_t(rhs.base_reference()),
        m_buffer_out_full(rhs.m_buffer_out_full),
        m_buffer_out(rhs.m_buffer_out),
        m_buffer_in(rhs.m_buffer_in),
        m_remaining_bits(rhs.m_remaining_bits),
        m_end_of_sequence(false)
    {}
};

template<
    class Base,
    int BitsOut,
    int BitsIn,
    class CharType
>
void transform_width<Base, BitsOut, BitsIn, CharType>::fill() {
    unsigned int missing_bits = BitsOut;
    m_buffer_out = 0;
    do{
        if(0 == m_remaining_bits){
            if(m_end_of_sequence){
                m_buffer_in = 0;
                m_remaining_bits = missing_bits;
            }
            else{
                m_buffer_in = * this->base_reference()++;
                m_remaining_bits = BitsIn;
            }
        }

        // append these bits to the next output
        // up to the size of the output
        unsigned int i = (std::min)(missing_bits, m_remaining_bits);
        // shift interesting bits to least significant position
        base_value_type j = m_buffer_in >> (m_remaining_bits - i);
        // and mask off the un interesting higher bits
        // note presumption of twos complement notation
        j &= (1 << i) - 1;
        // append then interesting bits to the output value
        m_buffer_out <<= i;
        m_buffer_out |= j;

        // and update counters
        missing_bits -= i;
        m_remaining_bits -= i;
    }while(0 < missing_bits);
    m_buffer_out_full = true;
}

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_TRANSFORM_WIDTH_HPP

/* transform_width.hpp
PPHDNhZ4MQ6inedhWe8K2HN+H3Y9fiJOjT6Hn7QfsNpZV0hJTkSTLUNZj45+UPx+H57lPIrms7t8enwwTktFNmJvW7w2qBGwkhug3uyZ7J2nK5x6/CObHNoE3r6vyeq99MAqj/uDb9e2UPaXSOhSi54X7XTHI5lVsc3difzPZ2OgbcUnGDy1M6x40JenjV0I8/e+5PtKjcIa4RthSVQ25I+YxWqsTIdVlUuyLfXbQ98fJP5u/zMIWjAJful7FLMnfMbikf4Y5rScL+h8ANtvPMzfWFljqHcR/qtfN/x8ugQOfNkaIpYe4edL7IEupZvDvuDVOHSVH7+YPBmavBzPa0eOhMg5DiwydRLuXJ+NNQscw90Fh2D9Im/gdcggVtzoT2hyth6W+LUDeg7VssuTFoGnyQU+gfZB6xtt4LZvR0Pa/lSYuisEbvF3gDOysOw+Vyho1wj2ld/Gr28D9FxaCpbv/w0dLhzBHu2bw4ByNvD6/XUos2E1xBU5iiWHP4OIJZbYrGsD2La3O+ybeZ4FWiZjwajDMGLfQvQaMAKTb/8Kpk8j0aqUBtavt+F2jTrgx927sO+CDNz2PoM9oL23a9NGfEvLXTDojCvsfvEZWxRPh2POTTBTWsfqX7sH58MysVSrR7iy4UmWfC8/2p8JhQ7PJ+Lshdf4i/Vb8OP+W1yafAnTi6ew7GMeUKmGPy+TeRJaPLuOb5pawmTzybioZQX44bkPz0fza2r5LFbr+kacf8aalyx2CF9Va8Qnmi2ArO35+YLDzWFVkjHWmNYEZ2ddg3i7adB13l8YOA9HLrswDN8naaeipEGDZERmZVU0NKikhJDRJNKwkq+MaFAhIzTILJGUiIaK0ELaZkIkRCmj83y/f+G87znv/VzXfV4FFtweBierv+z+KCEsOdGNN3MlIFYWz25Mu0eVAu4qX5FAOfwypR/SwJNdtfzlCh0B/5Nnn1QeY0NlNyoLXiM/Pp5/mMBwomE/+nOXoE7KnhunJkBHMxNipaPodP1jhBfGUNX9MZyVZJDa8f3MJtsSN3KCYJO1H4oW7+nEoCN5B5py4d8GtFF1LqseUg873ywY61hATzKWPb9eTVbrTiN01h1KkwhhCyOzcVp3A32aayfgdE6k+3cVbjTPZ8NMc2j8ngR+ssqEbucGsrm1iVSzZ4B1uvpgyXA7LNndSOe1x8BSt542VQ1i/ftU/K15xg56Mcike2JmQj5pOalSuMIkOBYrMq01W/DfcxPyDRIw9hlZqDn9GEK17+G/vAVZZrf4kajbyD0iy1ZenYC+gTtMYWEjvsTPw+R2F6hHnGHWwu34dNeRL5MwhtzvCqr1uoAkLSmY+uhipexG1jSsAM61F2mh+xJ6GXUPjbMiiN/sZY1ZjZjteJXfVFwPx23rWN7Pw5QnogcZVoaxtxLoj4BLxjdbMX2WR1VqSSwkbCld6v6ESYk+eHv6MFtmuAXPL91iUVaKiN4nTHOFOukj9dPNJYa05rcx688QpdmqjdSrPEAx0irM56IeOcqsI7v2CziR70n7A6+T2NuP/INNBQ0K68FGqAxCU+/S0oeKJDV5EnxDjGmn53D22CgYBZkaNMHkPL6ZLWQNKukIVFCgDrX5SBPlmBguyCFPOmnFn8noaDpGWaquSLUfIC/Dv+gZEcp7Gy/Q57QsPnA6icZczaNEuet04fI03uO8lWolXJnouxY4XbzDn4SDHjvsJovgB5Rl8B93zDOA6qcZGMy4hIL1zaxDvh5VbSPYCYH3TnYzpeVPbKAcUIquaHMkaq3gV+oVSOf9MvJ4EkIyt7346/kjKKOyTsA8lxNtDGH9J1thZ3acjd+wAgH+l3HIejuUQk4=
*/