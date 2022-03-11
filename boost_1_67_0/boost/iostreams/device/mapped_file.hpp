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