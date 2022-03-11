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