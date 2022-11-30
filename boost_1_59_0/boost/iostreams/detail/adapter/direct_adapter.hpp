// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_DIRECT_ADAPTER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DIRECT_ADAPTER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>       // SFINAE, MSVC, put ptrdiff_t in std.
#include <algorithm>              // copy, min.
#include <cstddef>                // ptrdiff_t.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/config/limits.hpp>        // forwarding.
#include <boost/iostreams/detail/config/wide_streams.hpp>  // locale.
#include <boost/iostreams/detail/double_object.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/detail/ios.hpp>  // openmode, seekdir, int types.
#include <boost/iostreams/traits.hpp>      // mode_of, is_direct.
#include <boost/iostreams/operations.hpp>
#include <boost/mpl/bool.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/preprocessor/iteration/local.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp> // VC7.1

namespace boost { namespace iostreams { namespace detail {
                    
//------------------Definition of direct_adapter_base-------------------------//

// Put all initialization in base class to faciliate forwarding.
template<typename Direct>
class direct_adapter_base {
public:
    typedef typename char_type_of<Direct>::type  char_type;
    typedef typename mode_of<Direct>::type       mode_type;
    struct category 
        : mode_type,
          device_tag,
          closable_tag
          #ifndef BOOST_IOSTREAMS_NO_LOCALE
          , localizable_tag
          #endif
        { };
protected:
    explicit direct_adapter_base(const Direct& d);
    typedef is_convertible<category, two_sequence> is_double;
    struct pointers {
        pointers() : beg(0), ptr(0), end(0) { }
        char_type *beg, *ptr, *end;
    };
    void init_input(mpl::true_);
    void init_input(mpl::false_) { }
    void init_output(mpl::true_);
    void init_output(mpl::false_) { }
    double_object<pointers, is_double>  ptrs_;
    Direct                              d_;
};

template<typename Direct>
class direct_adapter : private direct_adapter_base<Direct> {
private:
    typedef direct_adapter_base<Direct>      base_type;
    typedef typename base_type::pointers     pointers;
    typedef typename base_type::is_double    is_double;
    using base_type::ptrs_;
    using base_type::d_;
public:
    typedef typename base_type::char_type    char_type;
    typedef typename base_type::category     category;

        // Constructors

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
    direct_adapter(const Direct& d) : base_type(d) { }   
    direct_adapter(const direct_adapter& d) : base_type(d) { }
# define BOOST_PP_LOCAL_LIMITS (1, BOOST_IOSTREAMS_MAX_FORWARDING_ARITY)
#else
    template<typename U>
    struct is_direct
        : mpl::or_< 
              is_same<U, direct_adapter<Direct> >, 
              is_same<U, Direct> 
          >
        { };
    template<typename U>
    direct_adapter(const U& u) 
        : base_type(forward(u, is_direct<U>()))
        { }
# define BOOST_PP_LOCAL_LIMITS (2, BOOST_IOSTREAMS_MAX_FORWARDING_ARITY)
#endif

#define BOOST_PP_LOCAL_MACRO(n) \
    template<BOOST_PP_ENUM_PARAMS(n, typename P)> \
    direct_adapter(BOOST_PP_ENUM_BINARY_PARAMS(n, const P, &p)) \
        : base_type(Direct(BOOST_PP_ENUM_PARAMS(n, p))) \
        { } \
    /**/
#include BOOST_PP_LOCAL_ITERATE()
#undef BOOST_PP_LOCAL_MACRO

        // Device interface.

    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    std::streampos seek( stream_offset, BOOST_IOS::seekdir,
                         BOOST_IOS::openmode = BOOST_IOS::in | BOOST_IOS::out );
    void close();
    void close(BOOST_IOS::openmode which);
#ifndef BOOST_IOSTREAMS_NO_LOCALE
    void imbue(const std::locale&);
#endif

        // Direct device access.

    Direct& operator*() { return d_; }
    Direct* operator->() { return &d_; }
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
private:
    template<typename U>
    static Direct forward(const U& u, mpl::true_) { return u; }
    template<typename U>
    static Direct forward(const U& u, mpl::false_) { return Direct(u); }
#endif
};

//--------------Definition of wrap_direct and unwrap_direct-------------------//

template<typename Device>
struct wrap_direct_traits 
    : mpl::if_<
          is_direct<Device>,
          direct_adapter<Device>,
          Device
      >
    { };

template<typename Device>
typename wrap_direct_traits<Device>::type
inline wrap_direct(Device dev) 
{ 
    typedef typename wrap_direct_traits<Device>::type type;
    return type(dev); 
}

template<typename Device>
inline Device& unwrap_direct(Device& d) { return d; }  

template<typename Device>
inline Device& unwrap_direct(direct_adapter<Device>& d) { return *d; }  

//--------------Implementation of direct_adapter_base-------------------------//

template<typename Direct>
direct_adapter_base<Direct>::direct_adapter_base(const Direct& d) : d_(d)
{
    init_input(is_convertible<category, input>());
    init_output(is_convertible<category, output>());
}

template<typename Direct>
void direct_adapter_base<Direct>::init_input(mpl::true_) 
{
    std::pair<char_type*, char_type*> seq = iostreams::input_sequence(d_);
    ptrs_.first().beg = seq.first;
    ptrs_.first().ptr = seq.first;
    ptrs_.first().end = seq.second;
}

template<typename Direct>
void direct_adapter_base<Direct>::init_output(mpl::true_) 
{
    std::pair<char_type*, char_type*> seq = iostreams::output_sequence(d_);
    ptrs_.second().beg = seq.first;
    ptrs_.second().ptr = seq.first;
    ptrs_.second().end = seq.second;
}

//--------------Implementation of direct_adapter------------------------------//

template<typename Direct>
inline std::streamsize direct_adapter<Direct>::read
    (char_type* s, std::streamsize n)
{
    using namespace std;
    pointers& get = ptrs_.first();
    std::streamsize avail = 
        static_cast<std::streamsize>(get.end - get.ptr);
    std::streamsize result = (std::min)(n, avail);
    std::copy(get.ptr, get.ptr + result, s);
    get.ptr += result;
    return result != 0 ? result : -1;
}

template<typename Direct>
inline std::streamsize direct_adapter<Direct>::write
    (const char_type* s, std::streamsize n)
{
    using namespace std;
    pointers& put = ptrs_.second();
    if (n > static_cast<std::streamsize>(put.end - put.ptr))
        boost::throw_exception(write_area_exhausted());
    std::copy(s, s + n, put.ptr);
    put.ptr += n;
    return n;
}

template<typename Direct>
inline std::streampos direct_adapter<Direct>::seek
    ( stream_offset off, BOOST_IOS::seekdir way, 
      BOOST_IOS::openmode which )
{
    using namespace std;
    pointers& get = ptrs_.first();
    pointers& put = ptrs_.second();
    if (way == BOOST_IOS::cur && get.ptr != put.ptr)
       boost::throw_exception(bad_seek());
    ptrdiff_t next = 0;
    if ((which & BOOST_IOS::in) || !is_double::value) {
        if (way == BOOST_IOS::beg)
            next = off; 
        else if (way == BOOST_IOS::cur)
            next = get.ptr - get.beg + off; 
        else
            next = get.end - get.beg + off; 
        if (next >= 0 && next <= get.end - get.beg)
            get.ptr = get.beg + next;
        else
            boost::throw_exception(bad_seek());
    }
    if ((which & BOOST_IOS::out) && is_double::value) {
        if (way == BOOST_IOS::beg)
            next = off; 
        else if (way == BOOST_IOS::cur)
            next = put.ptr - put.beg + off; 
        else
            next = put.end - put.beg + off; 
        if (next >= 0 && next <= put.end - put.beg)
            put.ptr = put.beg + next;
        else
            boost::throw_exception(bad_seek());
    }
    return offset_to_position(next);
}

template<typename Direct>
void direct_adapter<Direct>::close() 
{ 
    BOOST_STATIC_ASSERT((!is_convertible<category, two_sequence>::value));
    detail::close_all(d_);
}

template<typename Direct>
void direct_adapter<Direct>::close(BOOST_IOS::openmode which) 
{ 
    BOOST_STATIC_ASSERT((is_convertible<category, two_sequence>::value));
    boost::iostreams::close(d_, which);
}

#ifndef BOOST_IOSTREAMS_NO_LOCALE
    template<typename Direct>
    void direct_adapter<Direct>::imbue(const std::locale& loc) 
    { boost::iostreams::imbue(d_, loc); }
#endif

} } } // End namespaces detail, iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DIRECT_ADAPTER_HPP_INCLUDED

/* direct_adapter.hpp
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
*/