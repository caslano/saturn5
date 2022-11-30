// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <algorithm>                           // swap.
#include <memory>                              // allocator.
#include <boost/config.hpp>                    // member templates.
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>      // streamsize.
#include <boost/iostreams/read.hpp>
#include <boost/iostreams/traits.hpp>          // int_type_of.
#include <boost/iostreams/checked_operations.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace iostreams { namespace detail {

//----------------Buffers-----------------------------------------------------//

//
// Template name: buffer
// Description: Character buffer.
// Template parameters:
//     Ch - The character type.
//     Alloc - The Allocator type.
//
template< typename Ch,
          typename Alloc = std::allocator<Ch> >
class basic_buffer {
private:
#ifndef BOOST_NO_STD_ALLOCATOR
#if defined(BOOST_NO_CXX11_ALLOCATOR)
    typedef typename Alloc::template rebind<Ch>::other allocator_type;
#else
    typedef typename std::allocator_traits<Alloc>::template rebind_alloc<Ch> allocator_type;
    typedef std::allocator_traits<allocator_type> allocator_traits;
#endif
#else
    typedef std::allocator<Ch> allocator_type;
#endif
    static Ch* allocate(std::streamsize buffer_size);
public:
    basic_buffer();
    basic_buffer(std::streamsize buffer_size);
    ~basic_buffer();
    void resize(std::streamsize buffer_size);
    Ch* begin() const { return buf_; }
    Ch* end() const { return buf_ + size_; }
    Ch* data() const { return buf_; }
    std::streamsize size() const { return size_; }
    void swap(basic_buffer& rhs);
private:
    // Disallow copying and assignment.
    basic_buffer(const basic_buffer&);
    basic_buffer& operator=(const basic_buffer&);
    Ch*              buf_;
    std::streamsize  size_;
};

template<typename Ch, typename Alloc>
void swap(basic_buffer<Ch, Alloc>& lhs, basic_buffer<Ch, Alloc>& rhs)
{ lhs.swap(rhs); }

//
// Template name: buffer
// Description: Character buffer with two pointers accessible via ptr() and
//      eptr().
// Template parameters:
//     Ch - A character type.
//
template< typename Ch,
          typename Alloc = std::allocator<Ch> >
class buffer : public basic_buffer<Ch, Alloc> {
private:
    typedef basic_buffer<Ch, Alloc> base;
public:
    typedef iostreams::char_traits<Ch> traits_type;
    using base::resize; 
    using base::data; 
    using base::size;
    typedef Ch* const const_pointer;
    buffer(std::streamsize buffer_size);
    Ch* & ptr() { return ptr_; }
    const_pointer& ptr() const { return ptr_; }
    Ch* & eptr() { return eptr_; }
    const_pointer& eptr() const { return eptr_; }
    void set(std::streamsize ptr, std::streamsize end);
    void swap(buffer& rhs);

    // Returns an int_type as a status code.
    template<typename Source>
    typename int_type_of<Source>::type fill(Source& src) 
    {
        using namespace std;
        std::streamsize keep;
        if ((keep = static_cast<std::streamsize>(eptr_ - ptr_)) > 0)
            traits_type::move(
                this->data(),
                ptr_, 
                static_cast<size_t>(keep)
            );
        set(0, keep);
        std::streamsize result = 
            iostreams::read(src, this->data() + keep, this->size() - keep);
        if (result != -1)
            this->set(0, keep + result);
        return result == -1 ?
            traits_type::eof() :
                result == 0 ?
                    traits_type::would_block() :
                    traits_type::good();

    }

    // Returns true if one or more characters were written.
    template<typename Sink>
    bool flush(Sink& dest) 
    {
        using namespace std;
        std::streamsize amt = static_cast<std::streamsize>(eptr_ - ptr_);
        std::streamsize result = iostreams::write_if(dest, ptr_, amt);
        if (result < amt) {
            traits_type::move( this->data(), 
                               ptr_ + static_cast<size_t>(result), 
                               static_cast<size_t>(amt - result) );
        }
        this->set(0, amt - result);
        return result != 0;
    }
private:
    Ch *ptr_, *eptr_;
};

template<typename Ch, typename Alloc>
void swap(buffer<Ch, Alloc>& lhs, buffer<Ch, Alloc>& rhs)
{ lhs.swap(rhs); }

//--------------Implementation of basic_buffer--------------------------------//

template<typename Ch, typename Alloc>
basic_buffer<Ch, Alloc>::basic_buffer() : buf_(0), size_(0) { }

template<typename Ch, typename Alloc>
inline Ch* basic_buffer<Ch, Alloc>::allocate(std::streamsize buffer_size)
{
#if defined(BOOST_NO_CXX11_ALLOCATOR) || defined(BOOST_NO_STD_ALLOCATOR)
    return static_cast<Ch*>(allocator_type().allocate(
           static_cast<BOOST_DEDUCED_TYPENAME Alloc::size_type>(buffer_size), 0));
#else
    allocator_type alloc;
    return static_cast<Ch*>(allocator_traits::allocate(alloc,
           static_cast<BOOST_DEDUCED_TYPENAME allocator_traits::size_type>(buffer_size)));
#endif
}

template<typename Ch, typename Alloc>
basic_buffer<Ch, Alloc>::basic_buffer(std::streamsize buffer_size)
    : buf_(allocate(buffer_size)),
      size_(buffer_size) // Cast for SunPro 5.3.
    { }

template<typename Ch, typename Alloc>
inline basic_buffer<Ch, Alloc>::~basic_buffer()
{
    if (buf_) {
#if defined(BOOST_NO_CXX11_ALLOCATOR) || defined(BOOST_NO_STD_ALLOCATOR)
        allocator_type().deallocate(buf_,
            static_cast<BOOST_DEDUCED_TYPENAME Alloc::size_type>(size_));
#else
        allocator_type alloc;
        allocator_traits::deallocate(alloc, buf_,
            static_cast<BOOST_DEDUCED_TYPENAME allocator_traits::size_type>(size_));
#endif
    }
}

template<typename Ch, typename Alloc>
inline void basic_buffer<Ch, Alloc>::resize(std::streamsize buffer_size)
{
    if (size_ != buffer_size) {
        basic_buffer<Ch, Alloc> temp(buffer_size);
        std::swap(size_, temp.size_);
        std::swap(buf_, temp.buf_);
    }
}

template<typename Ch, typename Alloc>
void basic_buffer<Ch, Alloc>::swap(basic_buffer& rhs) 
{ 
    std::swap(buf_, rhs.buf_); 
    std::swap(size_, rhs.size_); 
}

//--------------Implementation of buffer--------------------------------------//

template<typename Ch, typename Alloc>
buffer<Ch, Alloc>::buffer(std::streamsize buffer_size)
    : basic_buffer<Ch, Alloc>(buffer_size), ptr_(data()), eptr_(data() + buffer_size) { }

template<typename Ch, typename Alloc>
inline void buffer<Ch, Alloc>::set(std::streamsize ptr, std::streamsize end)
{ 
    ptr_ = data() + ptr; 
    eptr_ = data() + end; 
}

template<typename Ch, typename Alloc>
inline void buffer<Ch, Alloc>::swap(buffer& rhs) 
{ 
    base::swap(rhs); 
    std::swap(ptr_, rhs.ptr_); 
    std::swap(eptr_, rhs.eptr_); 
}

//----------------------------------------------------------------------------//

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_BUFFERS_HPP_INCLUDED

/* buffer.hpp
n2DFtm9E0Y5FWsSdGmTg43xXxjBBPawraExTGVdOEMmOHL9+5EEbKUEeiZp6hLWil9K9E1O98PcdJFY5poTacEJqWxsMwNmMb5GNUuHbEPTzTl9diOY1QnqtEBI3DP2wiuVKXm4pRRcqdjbiNeCmHXWNb2CK73enHtReMz3KUNQ40i6Br/SK758iJX0l8PIscpxffwdsVuw5/EWMN9VwmTqDtTmxxkyXe2/9habYILwVLci/hAZvCLP2c+eIYtfza4/b0P6qoincUTu+LTmFoZn1MDEWj2V8kxpsAGn6hr/HOlWnQyqV9Cn/evN61fpiFER0FT89h8LeaIXDA6UREXbyw/93SePgNPZWoOzEnEzHKgX8k6whOxKzglgFx6Fv5GjYHrCEqHMK3FgUQVbeSfQBlweF9FPJwskxRV6zblCZ7Ea03PG1Pc2/3WAExizxLUwOmSIYqmCyxcdhYVQZ30d5+OTiU6quMxlqaPhx9QAUgmPJh+WFvJ3incWNfpP9oEy18GSQ/S5r8Kxp+iLNJSgFB0jt+niaYwTsLf5EMsQxR7MBq5vOseseqMRZ+Vjn4ofITfsaRv7LNe3GZFz4SfUM4xkDzUNGtT5R9ufaypY3HPFpR/kJUjHWnD0gAi3ebhFk5LZAEOcuDl7WTq5Rf3/yY+97a/DRn9YZoWxzrgs5bgEv7OhaXBnfrBnsIEnIIbM/LYkP1BvMF6XsVQgwWUDYM7/zqRTuRVgwB972Nt2ol3fDqUcLm4g9fLcjBQ/wsjoauWwqHQJEwmMAKuwdb0G9aZhbLY7E7G8s68IGGsDx/+wmCJ5n5VN1DMQv23xoZHgJqKWQw88V+eWtFKltqhjOPGr43IGHnfiTb5usdnjCyoZsj1R9fOfDEbFYlN6gZhtZlOUhUTlx6/q0fcrZTDxX62LON9fQxbu4/adnDthf1811V7m0eEAzDf6d/dE9vWtugpbhUPVc1q35VCyiErEEf6GVxQr8GD2i6gmcCSsXGRlU2LO7/2VJaloZL25HDm95RJYcVWBMVHMZNVAmtaTGH/X34GuScgDL7RmL1tE2bi9MRQe4UooX5vB4SaZOQw3U7gpbkkud1dXX+g23Apf/ZH8oCzKvPDEgKYMM3NeTDXKtyVG0MRs6S4utKRKnFnfkY61KmjnHlupVcSlJzlxXBKrcfS5eeSnkwvYEks0uCcT4ou31eZP7JZztDkV4r4ewxhQz3eQ1Mo3fJLYek8ggV2HAoCnbR3EEakQoaNkLNyMxonSNvyOcJ78bHA2o4wxpvF8E60gpiN0vU3aAI0bUFSpx1SQ+SjzX+Yq3+36P62iveeDX9AI0clEagVipCIvvZKnAzHDeJUPpdV6VaXJMBbV5aFobUoTEUcjHUJmtBbIks63kravIuoQfTiCYLr/LJY9WyQeOOKUeWjDUDnqvLVjEr46p2WSwo90LZFMmJpKl1QBFqNRLDSOi3xTfW9/oQh3hqZx1gpzZtjgmfBOm69Pti9Yv0rSVFyJYProaxS7senG1ozBVkR5/y3ZvtcMcso451Q0HTwff5ZE0yEBsdD1fl8TmWoMZeAgBmpidNzbDbLPGxAi8qKDOm6AZZc1JzzJLccvvs8L0QFm1oBFJYld3jY6eVOFi53tEUM3aOoD87rtOGtOsjGK5+VKghJUhelyp42cQZxW/KPwG9wBWVLDVGdlHhmaMqOKxrsjCcdx/HHEkjrZ4QcMILua5tY7Z6rutv0D52XHaeTmxQxJrm/OCHIUQZVyuFlOAEGaiEb3OIlzmWONoqOmBupthBRMqRRNhLMMJEE+BvVNnZIphfDWFJV0ddkCOerbadGQrKQ+f169FN2VCaQwTF2Tum/O/1xO/z8f3sQLxCJR5Snn+8uNajejgDxqXPgcP6V8y4h5WjwtW5YPZjilyODUR94eZCOAtmWw/ThoQG0C3AmevGb1htEbCX7rSBbPw3ik2DqKBIBMHT6Z1Hq+jnKEX1peDlIfkVQf/fQXt3fzzLxuCQi6UM9t/sFKPmVEA0761Z10YeCPEvTC0CP47Q+JfzrkUVeFY3sIvheONlPWLo6SJADQgQOCPoB/BP0J+hP4I+xH+I+JH5I+oH9E/Yn7E/oj7Ef8j4Ufij6QfyT9SfqT+SPuR/iPjR+aPrB/ZP3J+5P7I+5H/o+BH4Y+iH8U/Sn6U/ij7Uf6j4kflj6of1T9qftT+qPtR/6PhR+OPph/NP1p+tP5o+9H+o+NH54+uH90/en70/uj70f9j4Mfgj6Efwz9Gfoz+GPsx/mPix+SPqR/TP2Z+zP6Y+zH/Y+HH4o+lH8s/Vn6s/lj7sf5j48fmj60ff35s/9j5sftj78f+j4Mfhz+Ofhz/OPlx+uPsx/mPix+XP65+XP+4+XH74+7H3x/3Px5+PP54+vH84+XH649/P95+vP/4+PH54+vH9w8gdCBAwKQoQdcAq+pDmUHsvyJ1ozolz0CQ2BwCiV4qKYjwCj73A7vXNPEJb5HArYi3N5MoZ/c6WhE3ju2sCvTWbrmN0fxx6B3tJYL/A0yAs3/BpOB5XE4DNzdiYFTYvg3RvzZ8e2bqCxIutbnq5U3+L8C0aoDuasSBpTmj193yQzhoveRfhhXQQlSlid396DWwvmubS/MysV1x1cItph9Wex3uzSv+/zW8bl6LkhZcOOg4PgmSCs8tgJ5OK1k1Mij/JrdTuN6EsnD5fBVMcOjwMt44wAImwa4VsWlPafsXHgdXxRUYOH+L3rdghXFLk9UF9PvcEzJthu5sTIzkDXV+cWdYY+oW91R4rSzBBxpxk1keK7dL4CdZ+O0oq7dw38pn56I8jyk++MZXYTkx/RU+zL7Z31j8GHUfwoB4zM4QTTgFMzv4ip/HIVl6An48Mns1pKO3njvdySABz9QECd4v3bybNJFIQN3oxwW/YVKKnH+zgwCdWi0mPwLM61mPICIg+iaZD5Yr0Ha2UsCrNtp6MBsDrsHpk0ZJDdDE9rGsgepG31e0cigKi+Cx7YtDygkO36uw+hIc9VZxK0laG5+xBmdxPoBiR5ipQum4UwnxCP8goPjm4wp2m2JtZ4jOFzlSu3a4qQ5EVU2ZlDLwXTJSWakcEF0tpy39jESIepoKUJ+KPDyYubXj1uPh4ZyRcvZ0BfdpWcan2LfFWF06wl1rVC/sEuPKeGgG5GSaolVFp0MyB0ErU3Zc3Kl0YL8ujrtZ1AkbQqecQRjaYWGw4WX+Tfn+GeBlGI3a8/2LOkmSAjrfNpfQMdkMYU84kmKrGwuysfrM36wVyD6yHhIXBBD4xbs9L3t/SNBG36XOop8/03aetxNHv3M/4JS5M7T33BNJtS76yOYOaXolJHssJGvkKkXllIjxNsfvu2es2dlVfWAM5choCed//Bphf4VdsZorhvNkqTDbZBWrCTMztOpoyuBpcVtU6vpEksMWpruv4lQN8L4wBFlsafi4u0o5+HgN4gI/LxgE0nQyyEJi50pWz9745IS6p+MYhsv5eM893RJOj7JnQJZoUuHSPEfseITDqYOs6qVk051voiMwDsrKXGltNdDS4BzboJnBMXNSP3r9X7IdUb73Ne5bIwv9xT4uVIbKmO4LW7a2Y07RN4BbKJKdvz6jXFXCLgpQVWUnrNLmmBEJQBl2neDTIJb7ZjVduRSIzukcLxc6afhDzQ7fLDIpeAVoZnm7hP4zghQ/hmljR5z8NdFF8KqPAWHPXuBSz+/2hpJvY6piplWWO1to+07FxdbVCQ+eb4CCyM80A51GfMmMXAX1NpiKN9Jj2PKZf0kcLF/39MT6Ut1TzyRAR0U6+/8qytOy9iAzvAvBqn0YiXkDMsue7M+C+RAOSqB/8lJ3ePWv2r3e8y7l00a/CIPdiZqMBxCaATan2Ihc0sNslK5uG/AhPLx0h063+6C4cnLkm3k/YMA1Z6jxnipGn7g7jk/SjDO7AAIs/dNNjuKAauK83+IuhAy9U6xVio3MDIkCppnXA2BgNTp55TJOKdnW+x0KpepvVx/+3eJUWoi4xVU8uG12LBHaxdc7FGnbL3jbqW6ecvreXGKQXe2uIx0OLRj2b5WqFaC57rwu4UeUvAwMMrSMNu3qs9n6O2F1Ih2/jB9dHTKp9cAk/giEdQUzGjWKtfw4NWcH2IwM3Cb6VgYUHF03FPA7+8YB4Fol8SMJfTs7w9NMDJxQfbmYETuwyc3APW1hUuIZ4oM+MbsU28nKuiqSmdukkWecP1y37857aU54rPlmn3A8BXcBv0RWr1rSkw6ZNJqSELIKwUVd8c1r0pXeBjjHvInbWTj0BtACpUFpSArqd1EX8ODpnOP8i5XYb6eDpfbfAchmLCx2vYl9ex0yoxizN6Qiv9kabSEsaGKplyi5hcHRssnjkOKvArtSEULLdd1CBOQtm2fqdwqpTBt/k1V2uLc83s1B5gMJ5ELYDdzDA0dfISzIKo9vRObSaFiyTRS82qr7yoXWHkPx8nTu24YlPRB+DdcSevONxYNI8QxPJpakVnjfkLUvgLu4rALNzHmadJqQqs1MIMEaebqDEmOPzIG162EYLJUonAAeNHNajwQ2DcW0FD07sjTYLsE1nQDD1Rhofmb9tFNp/SW2vzju7g05+sV7GmxKvtbwB75W8deyBoA06u4LMt3yfSJ1vRm6ZmU+QT8KG2KHY7nrOF1HDzWdjOJvyRMG0vUco1yVPXZolzPu5kPY5PamCld5jswyWO2w2nd6aUwwmG6uKH00Y9P7ErlLkOVG2emENAggiYqlxl/Y/os4d/8IlokRPvc7SPvQUSbq2+iP86gu5HGaDeFqenDHY186xOlshDmlryiZFGBFulcUcHoYpLd8gc+MlwlCVtEQMWDbAXEN21XhdE8/x+S2MEtHoalx6tCVvKoy1S6KFRnsTe7eWaQAFVvxMklWF6iUp54LXJ0SEznficl3lm1k9c9RSFGvQ9ct4wgU98e2ZJWGBlsnhXIq8F7Htqy5MCaYE15eZfJV7bVn5iCCk5RpeB+kCcu20dHKA7FavXr4SEehFjXeD/MZRrudR9vWOP3UI9tz1T3vNp1GmL3gKmOSSjtal/1xGXvw5Y2kvK3/rNFPyMV+7oFF8o1zqCk1XxUbWV8H5lZpQjfxjFlglX6agFo0da3eIzhMLFmHYbVbyR5a2HxNA+E+xgLpR1UdvRO0IeSCdWcfWPpghKb6SrQ4/VKm1Y+/Q+Gafdk5JNczNZOAQ39D4Xd4WSVGUNaaEDYz7s7ElUmSel17BCXqeIkO3JBoX5AFO7klJ8OnBb0uVpSv16eA9JlY0tXjNHv7fhZFOt1NUuQKpKz7FEeasQ+fvduLyYWUarZubJQuYzIPmPXgHRbHzaKlVVQ+/LjhiIYQYbDtmUrFau/stNUeE+VdeFswQQJkZvT9OZPxesLpekiEnoCdprxlAqZRgPtdWffyvHibifXUW16AsFgMuiDvg7J7vGDwEwYzPqNsGXIJjVOqLlshuu8cngURHFWPQpy1YeXRfleqPrWgQC5hA3jnBr35hYG4RrIJi0DPWOSPUd7obe6M6cwEqxPqcbz5q1UrnRuoAlgtCHO+9llMI8xMa9M1+G1a37BbG3pu87JudcjiMTPKIfpZ6vOLF0Doh211rAJd+S/kIiZNhqkTGQeYFfGmTej9PVX/n+xB6JMc8qzSVN5YMZdQ6gSupGWAhSn9vxLM3IIXZQQzrbkkUzbMZnXWvEmEY9Lseh90pNKM/Kn8XGLR5WGKgFwDeku6oBAzlXHOQyWJNX3AmNodAPdv8SO1rp9ecjKDRu1ZwvzDBfzAjNicHsXBovxFFbho6yKs6UWNIqUyRdIShx3fY4at58WjjzfTDDHRieiq/zFgIGj7A/xxCl7vqjyg5e59boyk9eAicQHGVmhMYdq41MqkJ3hzb4BPmykFRNuLzRCSG7DSCNqsKiZUJlQtemd83QPTk13Dz2+XCZi2V63R4CU9NRi7iC8CkZerbNoBoEP8s//gLoeAiudFejsn3RxeR2QJzRNWZsrA3KavKjokvWFk+BtZeAYI6HMyTUTKda6e3zgYNvuXFSmbBNZDMofLtgghD7ZDBeCC8VjFENi+4lqYHe2irJd4brxSSQ8ASsq/xmAuZTMsNE8RCY3bWRl8U5g0QMVuR6jZSg/UkcokNNgehxAYHbMoZvaPPD8UkwHF6fPgRO71f0mivnDf5UuYTCA+F5GXWGbFakaX2t1mtp+pSOZJCMqWCa1YCvJZ4xn1LHloGpftTHav8zd8CWPUFTK/tneK5NmyMIoqFlxo+dB1B+XEX+IZHxc3z5zuyjq47zw8+83eqqFz+Pcqjepxe+J2X9yRxUXo7BLKSFfU32eXD6cKkyodUEkWcBwpwwJBfqEL5VeD5+mPx9hQBunx5OIBYCrfsgb1JE37lq6tsx9Vi4QpSk5tDzOQjLpBHjEioiH0RAL9RAqJF32d0yKcGR1AWYd7XbOb9g7rydmu4ddQ2OCmnkbgSktvluSXm+IGEcBq9zJgI0e0ICXuhl16i03YEDAb2s8yPjj4IvQV9tY+FgnM+Kx4pWeB6vn3r1+jvn8V9koNHmdoZWta6ioeqScfXcT2EfAJsBpTEOMFUWeGNPXM/eUcZvVC4r2jsVY48EUEg4qPg0/v5ZJ80u6RJmG+AwnsXxjkhxRDGEfr30fcvgki4jxnwTuLMEO8BkKbJYwheaNETdnKVQEgLatI7Y3iFx7v2PHO9jC+9hYStIuwacsHKB3DbOlmgots3efEjeWLxWXNZ+IG+6dHgIvl0VstzreC/xzwsIRk3puBg6NAf0I4L6t29Ep8QLbafERx4WEwGHkeD5Js/cZzJbBKWUCh3acg7RYh7Mkq/N94BqQHajahv7NfcZyDKzezD207fXBTJ1AqEceQ0zVqa2BWV1ND3co90sdeF4XxnBzZZDVPwcm4oJJ+NVU875FiqAXEGlN/vbt5RXRYhdTmkMFPUJLa1oaFnDL+yPcV9FvBtY2cJTUjKuk77Zq+xfKaOrtuP1TwfQlSe4hg08T1hhy3VylBgV8V5Qsb+jSAYRBInr7incp6Lliy84d88WQHkOqyRYzqe0iqVX7jkzv2VdurkzS4Y1J/jz0ZxUmR01TVPhSVBJJKUN4fXY7JBwPgXMG0fWc60c06qH4RKgtsSbVKZCu1zmpyKaJVme7criujcHvEewT9khW0UrhXRXGo7UxXsNTLmDyZXKByrzuEoBa3UapsC9VQVH0BNZDv/lo1Jyuton2Un/BVeARRWjNAgldtjhnOHlbFTZmbymReSjDvRYXBgz5c4MWtVvyvUULFBMZalpuzjHrrA/+NxuJgQimoZdlXTgioslZ339hFgbc5mRHE6LW2WcjP0kNNOYn4rLBTtOLoTVu3v0zD57nH/DCWy7ZE20VJuwzlzFwbXVvioarURSwcyeCSDe9uJvAgH62ffDB0fjd14/9nTZDOS81QJKNBrito/OI3BUMmYnmRn1qEPVYKkv1DxlfFFB0FpRDwUIYnqqXX8sFX5rBwzKGmsibhF++nG2HaWAjpFJAyidtpDmW4AXMK7ngPkDYc0rwf8VM/fL2jgQO3ppamcp7Erin6eGnzraJTFJZ3fuU3kJqIYOoE9LhiELkk9phQ
*/