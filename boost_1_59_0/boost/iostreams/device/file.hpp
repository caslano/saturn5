// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_FILE_HPP_INCLUDED
#define BOOST_IOSTREAMS_FILE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_LOCALE
# include <locale>
#endif
#include <string>                               // pathnames, char_traits.
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/ios.hpp>       // openmode, seekdir, int types.
#include <boost/iostreams/detail/fstream.hpp>
#include <boost/iostreams/operations.hpp>       // seek.
#include <boost/shared_ptr.hpp>      

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

template<typename Ch>
class basic_file {
public:
    typedef Ch char_type;
    struct category
        : public seekable_device_tag,
          public closable_tag,
          public localizable_tag,
          public flushable_tag
        { };
    basic_file( const std::string& path,
                BOOST_IOS::openmode mode =
                    BOOST_IOS::in | BOOST_IOS::out,
                BOOST_IOS::openmode base_mode =
                    BOOST_IOS::in | BOOST_IOS::out );
    std::streamsize read(char_type* s, std::streamsize n);
    bool putback(char_type c);
    std::streamsize write(const char_type* s, std::streamsize n);
    std::streampos seek( stream_offset off, BOOST_IOS::seekdir way, 
                         BOOST_IOS::openmode which = 
                             BOOST_IOS::in | BOOST_IOS::out );
    void open( const std::string& path,
               BOOST_IOS::openmode mode =
                   BOOST_IOS::in | BOOST_IOS::out,
               BOOST_IOS::openmode base_mode =
                   BOOST_IOS::in | BOOST_IOS::out );
    bool is_open() const;
    void close();
    bool flush();
#ifndef BOOST_IOSTREAMS_NO_LOCALE
    void imbue(const std::locale& loc) { pimpl_->file_.pubimbue(loc);  }
#endif
private:
    struct impl {
        impl(const std::string& path, BOOST_IOS::openmode mode)
            { file_.open(path.c_str(), mode); }
        ~impl() { if (file_.is_open()) file_.close(); }
        BOOST_IOSTREAMS_BASIC_FILEBUF(Ch) file_;
    };
    shared_ptr<impl> pimpl_;
};

typedef basic_file<char>     file;
typedef basic_file<wchar_t>  wfile;

template<typename Ch>
struct basic_file_source : private basic_file<Ch> {
    typedef Ch char_type;
    struct category
        : input_seekable,
          device_tag,
          closable_tag
        { };
    using basic_file<Ch>::read;
    using basic_file<Ch>::putback;
    using basic_file<Ch>::seek;
    using basic_file<Ch>::is_open;
    using basic_file<Ch>::close;
    basic_file_source( const std::string& path,
                       BOOST_IOS::openmode mode = 
                           BOOST_IOS::in )
        : basic_file<Ch>(path, mode & ~BOOST_IOS::out, BOOST_IOS::in)
        { }
    void open( const std::string& path,
               BOOST_IOS::openmode mode = BOOST_IOS::in )
    {
        basic_file<Ch>::open(path, mode & ~BOOST_IOS::out, BOOST_IOS::in);
    }
};

typedef basic_file_source<char>     file_source;
typedef basic_file_source<wchar_t>  wfile_source;

template<typename Ch>
struct basic_file_sink : private basic_file<Ch> {
    typedef Ch char_type;
    struct category
        : output_seekable,
          device_tag,
          closable_tag,
          flushable_tag
        { };
    using basic_file<Ch>::write;
    using basic_file<Ch>::seek;
    using basic_file<Ch>::is_open;
    using basic_file<Ch>::close;
    using basic_file<Ch>::flush;
    basic_file_sink( const std::string& path,
                     BOOST_IOS::openmode mode = BOOST_IOS::out )
        : basic_file<Ch>(path, mode & ~BOOST_IOS::in, BOOST_IOS::out)
        { }
    void open( const std::string& path,
               BOOST_IOS::openmode mode = BOOST_IOS::out )
    {
        basic_file<Ch>::open(path, mode & ~BOOST_IOS::in, BOOST_IOS::out);
    }
};

typedef basic_file_sink<char>     file_sink;
typedef basic_file_sink<wchar_t>  wfile_sink;
                                 
//------------------Implementation of basic_file------------------------------//

template<typename Ch>
basic_file<Ch>::basic_file
    ( const std::string& path, BOOST_IOS::openmode mode, 
      BOOST_IOS::openmode base_mode )
{ 
    open(path, mode, base_mode);
}

template<typename Ch>
inline std::streamsize basic_file<Ch>::read
    (char_type* s, std::streamsize n)
{ 
    std::streamsize result = pimpl_->file_.sgetn(s, n); 
    return result != 0 ? result : -1;
}

template<typename Ch>
inline bool basic_file<Ch>::putback(char_type c)
{ 
    return !!pimpl_->file_.sputbackc(c); 
}

template<typename Ch>
inline std::streamsize basic_file<Ch>::write
    (const char_type* s, std::streamsize n)
{ return pimpl_->file_.sputn(s, n); }

template<typename Ch>
std::streampos basic_file<Ch>::seek
    ( stream_offset off, BOOST_IOS::seekdir way, 
      BOOST_IOS::openmode )
{ return iostreams::seek(pimpl_->file_, off, way); }

template<typename Ch>
void basic_file<Ch>::open
    ( const std::string& path, BOOST_IOS::openmode mode, 
      BOOST_IOS::openmode base_mode )
{ 
    pimpl_.reset(new impl(path, mode | base_mode));
}

template<typename Ch>
bool basic_file<Ch>::is_open() const { return pimpl_->file_.is_open(); }

template<typename Ch>
void basic_file<Ch>::close() { pimpl_->file_.close(); }

template<typename Ch>
bool basic_file<Ch>::flush()
{ return pimpl_->file_.BOOST_IOSTREAMS_PUBSYNC() == 0; }

//----------------------------------------------------------------------------//

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp> // MSVC

#endif // #ifndef BOOST_IOSTREAMS_FILE_HPP_INCLUDED

/* file.hpp
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
*/