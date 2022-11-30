// (C) Copyright Jorge Lodos 2008.
// (C) Copyright Jonathan Turkanis 2003.
// (C) Copyright Craig Henderson 2002.   'boost/memmap.hpp' from sandbox
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

#ifndef BOOST_IOSTREAMS_MAPPED_FILE_HPP_INCLUDED
#define BOOST_IOSTREAMS_MAPPED_FILE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>                   // make sure size_t is in std.
#include <cstddef>                            // size_t.
#include <string>                             // pathnames.
#include <utility>                            // pair.
#include <boost/config.hpp>                   // BOOST_MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/close.hpp>
#include <boost/iostreams/concepts.hpp>
#include <boost/iostreams/detail/config/auto_link.hpp>
#include <boost/iostreams/detail/config/dyn_link.hpp>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#include <boost/iostreams/detail/ios.hpp>     // openmode, failure
#include <boost/iostreams/detail/path.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_same.hpp>

// Must come last.
#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4251)  // Missing DLL interface for shared_ptr
#endif
#include <boost/config/abi_prefix.hpp>

namespace boost { namespace iostreams {

//------------------Definition of mapped_file_base and mapped_file_params-----//

// Forward declarations
class mapped_file_source;
class mapped_file_sink;
class mapped_file;
namespace detail { class mapped_file_impl; }

class mapped_file_base {
public:
    enum mapmode {
        readonly = 1,
        readwrite = 2,
        priv = 4
    };
};

// Bitmask operations for mapped_file_base::mapmode
mapped_file_base::mapmode 
operator|(mapped_file_base::mapmode a, mapped_file_base::mapmode b);

mapped_file_base::mapmode 
operator&(mapped_file_base::mapmode a, mapped_file_base::mapmode b);

mapped_file_base::mapmode 
operator^(mapped_file_base::mapmode a, mapped_file_base::mapmode b);

mapped_file_base::mapmode 
operator~(mapped_file_base::mapmode a);

mapped_file_base::mapmode 
operator|=(mapped_file_base::mapmode& a, mapped_file_base::mapmode b);

mapped_file_base::mapmode 
operator&=(mapped_file_base::mapmode& a, mapped_file_base::mapmode b);

mapped_file_base::mapmode 
operator^=(mapped_file_base::mapmode& a, mapped_file_base::mapmode b);

//------------------Definition of mapped_file_params--------------------------//

namespace detail {

struct mapped_file_params_base {
    mapped_file_params_base()
        : flags(static_cast<mapped_file_base::mapmode>(0)), 
          mode(), offset(0), length(static_cast<std::size_t>(-1)), 
          new_file_size(0), hint(0)
        { }
private:
    friend class mapped_file_impl;
    void normalize();
public:
    mapped_file_base::mapmode   flags;
    BOOST_IOS::openmode         mode;  // Deprecated
    stream_offset               offset;
    std::size_t                 length;
    stream_offset               new_file_size;
    const char*                 hint;
};

} // End namespace detail.

// This template allows Boost.Filesystem paths to be specified when creating or
// reopening a memory mapped file, without creating a dependence on
// Boost.Filesystem. Possible values of Path include std::string,
// boost::filesystem::path, boost::filesystem::wpath, 
// and boost::iostreams::detail::path (used to store either a std::string or a
// std::wstring).
template<typename Path>
struct basic_mapped_file_params 
    : detail::mapped_file_params_base 
{
    typedef detail::mapped_file_params_base base_type;

    // For wide paths, instantiate basic_mapped_file_params 
    // with boost::filesystem::wpath
#ifndef BOOST_IOSTREAMS_NO_WIDE_STREAMS
    BOOST_STATIC_ASSERT((!is_same<Path, std::wstring>::value));
#endif

    // Default constructor
    basic_mapped_file_params() { }

    // Construction from a Path
    explicit basic_mapped_file_params(const Path& p) : path(p) { }

    // Construction from a path of a different type
    template<typename PathT>
    explicit basic_mapped_file_params(const PathT& p) : path(p) { }

    // Copy constructor
    basic_mapped_file_params(const basic_mapped_file_params& other)
        : base_type(other), path(other.path)
        { }

    // Templated copy constructor
    template<typename PathT>
    basic_mapped_file_params(const basic_mapped_file_params<PathT>& other)
        : base_type(other), path(other.path)
        { }

    typedef Path  path_type;
    Path          path;
};

typedef basic_mapped_file_params<std::string> mapped_file_params;

//------------------Definition of mapped_file_source--------------------------//

class BOOST_IOSTREAMS_DECL mapped_file_source : public mapped_file_base {
private:
    struct safe_bool_helper { int x; };
    typedef int safe_bool_helper::*                 safe_bool;
    typedef detail::mapped_file_impl                impl_type;
    typedef basic_mapped_file_params<detail::path>  param_type;
    friend class mapped_file;
    friend class detail::mapped_file_impl;
    friend struct boost::iostreams::operations<mapped_file_source>;
public:
    typedef char                                    char_type;
    struct category
        : public source_tag,
          public direct_tag,
          public closable_tag
        { };
    typedef std::size_t                             size_type;
    typedef const char*                             iterator;
    BOOST_STATIC_CONSTANT(size_type, max_length = static_cast<size_type>(-1));

    // Default constructor
    mapped_file_source();

    // Constructor taking a parameters object
    template<typename Path>
    explicit mapped_file_source(const basic_mapped_file_params<Path>& p);

    // Constructor taking a list of parameters
    template<typename Path>
    explicit mapped_file_source( const Path& path,
                                 size_type length = max_length,
                                 boost::intmax_t offset = 0 );

    // Copy Constructor
    mapped_file_source(const mapped_file_source& other);

    //--------------Stream interface------------------------------------------//

    template<typename Path>
    void open(const basic_mapped_file_params<Path>& p);

    template<typename Path>
    void open( const Path& path,
               size_type length = max_length,
               boost::intmax_t offset = 0 );

    bool is_open() const;
    void close();
    operator safe_bool() const;
    bool operator!() const;
    mapmode flags() const;

    //--------------Container interface---------------------------------------//

    size_type size() const;
    const char* data() const;
    iterator begin() const;
    iterator end() const;

    //--------------Query admissible offsets----------------------------------//

    // Returns the allocation granularity for virtual memory. Values passed
    // as offsets must be multiples of this value.
    static int alignment();

private:
    void init();
    void open_impl(const param_type& p);

    boost::shared_ptr<impl_type> pimpl_;
};

//------------------Definition of mapped_file---------------------------------//

class BOOST_IOSTREAMS_DECL mapped_file : public mapped_file_base {
private:
    typedef mapped_file_source                      delegate_type;
    typedef delegate_type::safe_bool                safe_bool;
    typedef basic_mapped_file_params<detail::path>  param_type;
    friend struct boost::iostreams::operations<mapped_file >;
    friend class mapped_file_sink;
public:
    typedef char                                    char_type;
    struct category
        : public seekable_device_tag,
          public direct_tag,
          public closable_tag
        { };
    typedef mapped_file_source::size_type           size_type;
    typedef char*                                   iterator;
    typedef const char*                             const_iterator;
    BOOST_STATIC_CONSTANT(size_type, max_length = delegate_type::max_length);

    // Default constructor
    mapped_file() { }

    // Construstor taking a parameters object
    template<typename Path>
    explicit mapped_file(const basic_mapped_file_params<Path>& p);

    // Constructor taking a list of parameters
    template<typename Path>
    mapped_file( const Path& path,
                 mapmode flags,
                 size_type length = max_length,
                 stream_offset offset = 0 );

    // Constructor taking a list of parameters, including a 
    // std::ios_base::openmode (deprecated)
    template<typename Path>
    explicit mapped_file( const Path& path,
                          BOOST_IOS::openmode mode =
                              BOOST_IOS::in | BOOST_IOS::out,
                          size_type length = max_length,
                          stream_offset offset = 0 );

    // Copy Constructor
    mapped_file(const mapped_file& other);

    //--------------Conversion to mapped_file_source (deprecated)-------------//

    operator mapped_file_source&() { return delegate_; }
    operator const mapped_file_source&() const { return delegate_; }

    //--------------Stream interface------------------------------------------//

    // open overload taking a parameters object
    template<typename Path>
    void open(const basic_mapped_file_params<Path>& p);

    // open overload taking a list of parameters
    template<typename Path>
    void open( const Path& path,
               mapmode mode,
               size_type length = max_length,
               stream_offset offset = 0 );

    // open overload taking a list of parameters, including a 
    // std::ios_base::openmode (deprecated)
    template<typename Path>
    void open( const Path& path,
               BOOST_IOS::openmode mode =
                   BOOST_IOS::in | BOOST_IOS::out,
               size_type length = max_length,
               stream_offset offset = 0 );

    bool is_open() const { return delegate_.is_open(); }
    void close() { delegate_.close(); }
    operator safe_bool() const { return delegate_; }
    bool operator!() const { return !delegate_; }
    mapmode flags() const { return delegate_.flags(); }

    //--------------Container interface---------------------------------------//

    size_type size() const { return delegate_.size(); }
    char* data() const;
    const char* const_data() const { return delegate_.data(); }
    iterator begin() const { return data(); }
    const_iterator const_begin() const { return const_data(); }
    iterator end() const;
    const_iterator const_end() const { return const_data() + size(); }

    //--------------Query admissible offsets----------------------------------//

    // Returns the allocation granularity for virtual memory. Values passed
    // as offsets must be multiples of this value.
    static int alignment() { return mapped_file_source::alignment(); }

    //--------------File access----------------------------------------------//

    void resize(stream_offset new_size);
private:
    delegate_type delegate_;
};

//------------------Definition of mapped_file_sink----------------------------//

class BOOST_IOSTREAMS_DECL mapped_file_sink : private mapped_file {
public:
    friend struct boost::iostreams::operations<mapped_file_sink>;
    using mapped_file::mapmode;
    using mapped_file::readonly;
    using mapped_file::readwrite;
    using mapped_file::priv;
    using mapped_file::char_type;
    struct category
        : public sink_tag,
          public direct_tag,
          public closable_tag
        { };
    using mapped_file::size_type;
    using mapped_file::iterator;
    using mapped_file::max_length;
    using mapped_file::is_open;
    using mapped_file::close;
    using mapped_file::operator safe_bool;
    using mapped_file::operator !;
    using mapped_file::flags;
    using mapped_file::size;
    using mapped_file::data;
    using mapped_file::begin;
    using mapped_file::end;
    using mapped_file::alignment;
    using mapped_file::resize;

    // Default constructor
    mapped_file_sink() { }

    // Constructor taking a parameters object
    template<typename Path>
    explicit mapped_file_sink(const basic_mapped_file_params<Path>& p);

    // Constructor taking a list of parameters
    template<typename Path>
    explicit mapped_file_sink( const Path& path,
                               size_type length = max_length,
                               boost::intmax_t offset = 0,
                               mapmode flags = readwrite );

    // Copy Constructor
    mapped_file_sink(const mapped_file_sink& other);

    // open overload taking a parameters object
    template<typename Path>
    void open(const basic_mapped_file_params<Path>& p);

    // open overload taking a list of parameters
    template<typename Path>
    void open( const Path& path,
               size_type length = max_length,
               boost::intmax_t offset = 0,
               mapmode flags = readwrite );
};

//------------------Implementation of mapped_file_source----------------------//

template<typename Path>
mapped_file_source::mapped_file_source(const basic_mapped_file_params<Path>& p)
{ init(); open(p); }

template<typename Path>
mapped_file_source::mapped_file_source( 
    const Path& path, size_type length, boost::intmax_t offset)
{ init(); open(path, length, offset); }

template<typename Path>
void mapped_file_source::open(const basic_mapped_file_params<Path>& p)
{
    param_type params(p);
    if (params.flags) {
        if (params.flags != mapped_file::readonly)
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("invalid flags"));
    } else {
        if (params.mode & BOOST_IOS::out)
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("invalid mode"));
        params.mode |= BOOST_IOS::in;
    }
    open_impl(params);
}

template<typename Path>
void mapped_file_source::open(
    const Path& path, size_type length, boost::intmax_t offset)
{
    param_type p(path);
    p.length = length;
    p.offset = offset;
    open(p);
}

//------------------Implementation of mapped_file-----------------------------//

template<typename Path>
mapped_file::mapped_file(const basic_mapped_file_params<Path>& p)
{ open(p); }

template<typename Path>
mapped_file::mapped_file( 
    const Path& path, mapmode flags, 
    size_type length, stream_offset offset )
{ open(path, flags, length, offset); }

template<typename Path>
mapped_file::mapped_file( 
    const Path& path, BOOST_IOS::openmode mode, 
    size_type length, stream_offset offset )
{ open(path, mode, length, offset); }

template<typename Path>
void mapped_file::open(const basic_mapped_file_params<Path>& p)
{ delegate_.open_impl(p); }

template<typename Path>
void mapped_file::open( 
    const Path& path, mapmode flags, 
    size_type length, stream_offset offset )
{
    param_type p(path);
    p.flags = flags;
    p.length = length;
    p.offset = offset;
    open(p);
}

template<typename Path>
void mapped_file::open( 
    const Path& path, BOOST_IOS::openmode mode, 
    size_type length, stream_offset offset )
{
    param_type p(path);
    p.mode = mode;
    p.length = length;
    p.offset = offset;
    open(p);
}

inline char* mapped_file::data() const 
{ return (flags() != readonly) ? const_cast<char*>(delegate_.data()) : 0; }

inline mapped_file::iterator mapped_file::end() const 
{ return (flags() != readonly) ? data() + size() : 0; }

//------------------Implementation of mapped_file_sink------------------------//

template<typename Path>
mapped_file_sink::mapped_file_sink(const basic_mapped_file_params<Path>& p)
{ open(p); }

template<typename Path>
mapped_file_sink::mapped_file_sink(
    const Path& path, size_type length,
    boost::intmax_t offset, mapmode flags )
{ open(path, length, offset, flags); }

template<typename Path>
void mapped_file_sink::open(const basic_mapped_file_params<Path>& p)
{
    param_type params(p);
    if (params.flags) {
        if (params.flags & mapped_file::readonly)
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("invalid flags"));
    } else {
        if (params.mode & BOOST_IOS::in)
            boost::throw_exception(BOOST_IOSTREAMS_FAILURE("invalid mode"));
        params.mode |= BOOST_IOS::out;
    }
    mapped_file::open(params);
}

template<typename Path>
void mapped_file_sink::open(
    const Path& path, size_type length,
    boost::intmax_t offset, mapmode flags )
{
    param_type p(path);
    p.flags = flags;
    p.length = length;
    p.offset = offset;
    open(p);
}

//------------------Specialization of direct_impl-----------------------------//

template<>
struct operations<mapped_file_source>
    : boost::iostreams::detail::close_impl<closable_tag>
{
    static std::pair<char*, char*>
    input_sequence(mapped_file_source& src)
    {
        return std::make_pair( const_cast<char*>(src.begin()),
                               const_cast<char*>(src.end()) );
    }
};

template<>
struct operations<mapped_file>
    : boost::iostreams::detail::close_impl<closable_tag>
{
    static std::pair<char*, char*>
    input_sequence(mapped_file& file)
    { 
        return std::make_pair(file.begin(), file.end()); 
    }
    static std::pair<char*, char*>
    output_sequence(mapped_file& file)
    { 
        return std::make_pair(file.begin(), file.end()); 
    }
};

template<>
struct operations<mapped_file_sink>
    : boost::iostreams::detail::close_impl<closable_tag>
{
    static std::pair<char*, char*>
    output_sequence(mapped_file_sink& sink)
    { 
        return std::make_pair(sink.begin(), sink.end()); 
    }
};
                    
//------------------Definition of mapmode operators---------------------------//

inline mapped_file::mapmode 
operator|(mapped_file::mapmode a, mapped_file::mapmode b)
{
    return static_cast<mapped_file::mapmode>
        (static_cast<int>(a) | static_cast<int>(b));
}

inline mapped_file::mapmode 
operator&(mapped_file::mapmode a, mapped_file::mapmode b)
{
    return static_cast<mapped_file::mapmode>
        (static_cast<int>(a) & static_cast<int>(b));
}

inline mapped_file::mapmode 
operator^(mapped_file::mapmode a, mapped_file::mapmode b)
{
    return static_cast<mapped_file::mapmode>
        (static_cast<int>(a) ^ static_cast<int>(b));
}

inline mapped_file::mapmode
operator~(mapped_file::mapmode a)
{
    return static_cast<mapped_file::mapmode>(~static_cast<int>(a));
}

inline mapped_file::mapmode 
operator|=(mapped_file::mapmode& a, mapped_file::mapmode b)
{
    return a = a | b;
}

inline mapped_file::mapmode 
operator&=(mapped_file::mapmode& a, mapped_file::mapmode b)
{
    return a = a & b;
}

inline mapped_file::mapmode 
operator^=(mapped_file::mapmode& a, mapped_file::mapmode b)
{
    return a = a ^ b;
}

} } // End namespaces iostreams, boost.

#include <boost/config/abi_suffix.hpp> // pops abi_suffix.hpp pragmas
#if defined(BOOST_MSVC)
# pragma warning(pop)  // pops #pragma warning(disable:4251)
#endif

#endif // #ifndef BOOST_IOSTREAMS_MAPPED_FILE_HPP_INCLUDED

/* mapped_file.hpp
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
*/