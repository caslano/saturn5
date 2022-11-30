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
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
*/