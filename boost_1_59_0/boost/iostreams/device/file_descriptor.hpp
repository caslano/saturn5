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
+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
*/