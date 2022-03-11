// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Inspired by fdstream.hpp, (C) Copyright Nicolai M. Josuttis 2001,
// available at http://www.josuttis.com/cppcode/fdstream.html.

#ifndef BOOST_IOSTREAMS_FILE_DESCRIPTOR_HPP_INCLUDED
#define BOOST_IOSTREAMS_FILE_DESCRIPTOR_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <string>
#include <boost/cstdint.hpp>               // intmax_t.
#include <boost/iostreams/categories.hpp>  // tags.
#include <boost/iostreams/detail/config/auto_link.hpp>
#include <boost/iostreams/detail/config/dyn_link.hpp>
#include <boost/iostreams/detail/config/windows_posix.hpp>
#include <boost/iostreams/detail/file_handle.hpp>
#include <boost/iostreams/detail/ios.hpp>  // openmode, seekdir, int types.
#include <boost/iostreams/detail/path.hpp>
#include <boost/iostreams/positioning.hpp>
#include <boost/shared_ptr.hpp>

// Must come last.
#if defined(BOOST_MSVC)
# pragma warning(push)
# pragma warning(disable:4251)  // Missing DLL interface for shared_ptr
#endif
#include <boost/config/abi_prefix.hpp>

namespace boost { namespace iostreams {

// Forward declarations
class file_descriptor_source;
class file_descriptor_sink;
namespace detail { struct file_descriptor_impl; }

enum file_descriptor_flags
{
    never_close_handle = 0,
    close_handle = 3
};

class BOOST_IOSTREAMS_DECL file_descriptor {
public:
    friend class file_descriptor_source;
    friend class file_descriptor_sink;
    typedef detail::file_handle  handle_type;
    typedef char                 char_type;
    struct category
        : seekable_device_tag,
          closable_tag
        { };

    // Default constructor
    file_descriptor();

    // Constructors taking file desciptors
    file_descriptor(handle_type fd, file_descriptor_flags);
#ifdef BOOST_IOSTREAMS_WINDOWS
    file_descriptor(int fd, file_descriptor_flags);
#endif

#if defined(BOOST_IOSTREAMS_USE_DEPRECATED)
    // Constructors taking file desciptors
    explicit file_descriptor(handle_type fd, bool close_on_exit = false);
#ifdef BOOST_IOSTREAMS_WINDOWS
    explicit file_descriptor(int fd, bool close_on_exit = false);
#endif
#endif

    // Constructor taking a std:: string
    explicit file_descriptor( const std::string& path,
                              BOOST_IOS::openmode mode =
                                  BOOST_IOS::in | BOOST_IOS::out );

    // Constructor taking a C-style string
    explicit file_descriptor( const char* path,
                              BOOST_IOS::openmode mode =
                                  BOOST_IOS::in | BOOST_IOS::out );

    // Constructor taking a Boost.Filesystem path
    template<typename Path>
    explicit file_descriptor( const Path& path,
                              BOOST_IOS::openmode mode =
                                  BOOST_IOS::in | BOOST_IOS::out )
    { 
        init();
        open(detail::path(path), mode); 
    }

    // Copy constructor
    file_descriptor(const file_descriptor& other);

    // open overloads taking file descriptors
    void open(handle_type fd, file_descriptor_flags);
#ifdef BOOST_IOSTREAMS_WINDOWS
    void open(int fd, file_descriptor_flags);
#endif

#if defined(BOOST_IOSTREAMS_USE_DEPRECATED)
    // open overloads taking file descriptors
    void open(handle_type fd, bool close_on_exit = false);
#ifdef BOOST_IOSTREAMS_WINDOWS
    void open(int fd, bool close_on_exit = false);
#endif
#endif

    // open overload taking a std::string
    void open( const std::string& path,
               BOOST_IOS::openmode mode =
                   BOOST_IOS::in | BOOST_IOS::out );

    // open overload taking C-style string
    void open( const char* path,
               BOOST_IOS::openmode mode =
                   BOOST_IOS::in | BOOST_IOS::out );

    // open overload taking a Boost.Filesystem path
    template<typename Path>
    void open( const Path& path,
               BOOST_IOS::openmode mode =
                   BOOST_IOS::in | BOOST_IOS::out )
    { open(detail::path(path), mode); }

    bool is_open() const;
    void close();
    std::streamsize read(char_type* s, std::streamsize n);
    std::streamsize write(const char_type* s, std::streamsize n);
    std::streampos seek(stream_offset off, BOOST_IOS::seekdir way);
    handle_type handle() const;
private:
    void init();

    // open overload taking a detail::path
    void open( const detail::path& path, 
               BOOST_IOS::openmode, 
               BOOST_IOS::openmode = BOOST_IOS::openmode(0) );

    typedef detail::file_descriptor_impl impl_type;
    shared_ptr<impl_type> pimpl_;
};

class BOOST_IOSTREAMS_DECL file_descriptor_source : private file_descriptor {
public:
#ifdef BOOST_IOSTREAMS_WINDOWS
    typedef void*  handle_type;  // A.k.a HANDLE
#else
    typedef int    handle_type;
#endif
    typedef char   char_type;
    struct category
      : input_seekable,
        device_tag,
        closable_tag
      { };
    using file_descriptor::is_open;
    using file_descriptor::close;
    using file_descriptor::read;
    using file_descriptor::seek;
    using file_descriptor::handle;

    // Default constructor
    file_descriptor_source() { }

    // Constructors taking file desciptors
    explicit file_descriptor_source(handle_type fd, file_descriptor_flags);
#ifdef BOOST_IOSTREAMS_WINDOWS
    explicit file_descriptor_source(int fd, file_descriptor_flags);
#endif

#if defined(BOOST_IOSTREAMS_USE_DEPRECATED)
    // Constructors taking file desciptors
    explicit file_descriptor_source(handle_type fd, bool close_on_exit = false);
#ifdef BOOST_IOSTREAMS_WINDOWS
    explicit file_descriptor_source(int fd, bool close_on_exit = false);
#endif
#endif

    // Constructor taking a std:: string
    explicit file_descriptor_source( const std::string& path,
                                     BOOST_IOS::openmode mode = BOOST_IOS::in );

    // Constructor taking a C-style string
    explicit file_descriptor_source( const char* path,
                                     BOOST_IOS::openmode mode = BOOST_IOS::in );

    // Constructor taking a Boost.Filesystem path
    template<typename Path>
    explicit file_descriptor_source( const Path& path,
                                     BOOST_IOS::openmode mode = BOOST_IOS::in )
    { open(detail::path(path), mode); }

    // Copy constructor
    file_descriptor_source(const file_descriptor_source& other);

    // Constructors taking file desciptors
    void open(handle_type fd, file_descriptor_flags);
#ifdef BOOST_IOSTREAMS_WINDOWS
    void open(int fd, file_descriptor_flags);
#endif

#if defined(BOOST_IOSTREAMS_USE_DEPRECATED)
    // open overloads taking file descriptors
    void open(handle_type fd, bool close_on_exit = false);
#ifdef BOOST_IOSTREAMS_WINDOWS
    void open(int fd, bool close_on_exit = false);
#endif
#endif

    // open overload taking a std::string
    void open(const std::string& path, BOOST_IOS::openmode mode = BOOST_IOS::in);

    // open overload taking C-style string
    void open(const char* path, BOOST_IOS::openmode mode = BOOST_IOS::in);

    // open overload taking a Boost.Filesystem path
    template<typename Path>
    void open(const Path& path, BOOST_IOS::openmode mode = BOOST_IOS::in);
private:

    // open overload taking a detail::path
    void open(const detail::path& path, BOOST_IOS::openmode);
};

class BOOST_IOSTREAMS_DECL file_descriptor_sink : private file_descriptor {
public:
#ifdef BOOST_IOSTREAMS_WINDOWS
    typedef void*  handle_type;  // A.k.a HANDLE
#else
    typedef int    handle_type;
#endif
    typedef char   char_type;
    struct category
      : output_seekable,
        device_tag,
        closable_tag
      { };
    using file_descriptor::is_open;
    using file_descriptor::close;
    using file_descriptor::write;
    using file_descriptor::seek;
    using file_descriptor::handle;

    // Default constructor
    file_descriptor_sink() { }

    // Constructors taking file desciptors
    file_descriptor_sink(handle_type fd, file_descriptor_flags);
#ifdef BOOST_IOSTREAMS_WINDOWS
    file_descriptor_sink(int fd, file_descriptor_flags);
#endif

#if defined(BOOST_IOSTREAMS_USE_DEPRECATED)
    // Constructors taking file desciptors
    explicit file_descriptor_sink(handle_type fd, bool close_on_exit = false);
#ifdef BOOST_IOSTREAMS_WINDOWS
    explicit file_descriptor_sink(int fd, bool close_on_exit = false);
#endif
#endif

    // Constructor taking a std:: string
    explicit file_descriptor_sink( const std::string& path,
                                   BOOST_IOS::openmode mode = BOOST_IOS::out );

    // Constructor taking a C-style string
    explicit file_descriptor_sink( const char* path,
                                   BOOST_IOS::openmode mode = BOOST_IOS::out );

    // Constructor taking a Boost.Filesystem path
    template<typename Path>
    explicit file_descriptor_sink( const Path& path,
                                   BOOST_IOS::openmode mode = BOOST_IOS::out )
    { open(detail::path(path), mode); }

    // Copy constructor
    file_descriptor_sink(const file_descriptor_sink& other);

    // open overloads taking file descriptors
    void open(handle_type fd, file_descriptor_flags);
#ifdef BOOST_IOSTREAMS_WINDOWS
    void open(int fd, file_descriptor_flags);
#endif

#if defined(BOOST_IOSTREAMS_USE_DEPRECATED)
    // open overloads taking file descriptors
    void open(handle_type fd, bool close_on_exit = false);
#ifdef BOOST_IOSTREAMS_WINDOWS
    void open(int fd, bool close_on_exit = false);
#endif
#endif

    // open overload taking a std::string
    void open( const std::string& path, 
               BOOST_IOS::openmode mode = BOOST_IOS::out );

    // open overload taking C-style string
    void open( const char* path, 
               BOOST_IOS::openmode mode = BOOST_IOS::out );

    // open overload taking a Boost.Filesystem path
    template<typename Path>
    void open( const Path& path, 
               BOOST_IOS::openmode mode = BOOST_IOS::out )
    { open(detail::path(path), mode); }
private:

    // open overload taking a detail::path
    void open(const detail::path& path, BOOST_IOS::openmode);
};

} } // End namespaces iostreams, boost.

#include <boost/config/abi_suffix.hpp> // pops abi_suffix.hpp pragmas
#if defined(BOOST_MSVC)
# pragma warning(pop)  // pops #pragma warning(disable:4251)
#endif

#endif // #ifndef BOOST_IOSTREAMS_FILE_DESCRIPTOR_HPP_INCLUDED

/* file_descriptor.hpp
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
*/