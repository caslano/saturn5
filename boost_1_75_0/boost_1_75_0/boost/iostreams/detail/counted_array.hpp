// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_COUNTED_ARRAY_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_COUNTED_ARRAY_HPP_INCLUDED

#include <algorithm>                               // min.
#include <cstddef>                                 // size_t
#include <string>                                  // char_traits
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/ios.hpp>          // streamsize.

namespace boost { namespace iostreams { namespace detail {

template<typename Ch>
class counted_array_source {
public:
    typedef Ch          char_type;
    typedef source_tag  category;
    counted_array_source(const Ch* buf, std::streamsize size) 
        : buf_(buf), ptr_(0), end_(size)
        { }
    std::streamsize read(Ch* s, std::streamsize n)
    {
        using namespace std;
        streamsize result = (std::min)(n, end_ - ptr_);
        char_traits<char_type>::copy(
            s,
            buf_ + ptr_,
            static_cast<size_t>(result)
        );
        ptr_ += result;
        return result;
    }
    std::streamsize count() const { return ptr_; }
private:
    const Ch*        buf_;
    std::streamsize  ptr_, end_;
};

template<typename Ch>
struct counted_array_sink {
public:
    typedef Ch        char_type;
    typedef sink_tag  category;
    counted_array_sink(Ch* buf, std::streamsize size) 
        : buf_(buf), ptr_(0), end_(size)
        { }
        std::streamsize write(const Ch* s, std::streamsize n)
    {
        using namespace std;
        std::streamsize result = (std::min)(n, end_ - ptr_);
        char_traits<char_type>::copy(
            buf_ + ptr_,
            s,
            static_cast<size_t>(result)
        );
        ptr_ += result;
        return result;
    }
    std::streamsize count() const { return ptr_; }
private:
    Ch*              buf_;
    std::streamsize  ptr_, end_;
};

} } } // End namespaces iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_COUNTED_ARRAY_HPP_INCLUDED

/* counted_array.hpp
4a3cP5ls7LsNAiycguQUDaNamwcmz8+azxAhkZJpmZ5JWEWiz8c+rviVG02fqb1+79N2sb7SCg592yTDCnEnR1tv5UBb/KGZV8l3Y4A5rBKNOizbIc5exMyUWcJV6416mMlWqnkI7yNB03PSLwCsuUeAw/GEKrYiNyaxQpQ8D5rJiqP0n0LofUqMz2wNPj5p9LWy+3BoDQx6v91OFzvTFLdj6svPeAJGmyPBfX0byg75XOF4Z/JYhfyy8YF6K1DFOeb31Vx84tkWole2oY8ofGnAWkHaQDL2Qzg3hiJ66gOCaR0xOI3STFhXu/CNNfR8Dq46z+v6Ar+U3qoAT4mJN9yK5omt/o/GHyXEtQ8Z/cc7vvz6X2O72036fd/cWr0UzwgK2CEw4a41qIDfiak41i6w5TUU2nIR6+jzDiFxxSoRwRWGSO+f9mXxntx5bzRYNtxRDSh8ZuYXAiZyyLEtLnKBHFegFFTwGuZT4m0tYfNCWOkStOryH4s1aqcfsIJ7eF/Fr1EwzwWkkdHujbVzjmRbKrjTjdp5frU+YrPZ6YnLJPrd8GXpCn4XHlnEK+FMcZpiMjNEH/pMUDFssgFyjfeoYjHF8O5FpLDxfzlpZ9fv4PBFDzqct3l+FBNEo8iDbVecgCZuCFLwLOD5WMfhotluvuJh4jRIbbdqYV3lwE7H+WgTVDyTK139+Tg5PTThF63/px3n+XPK8rts
*/