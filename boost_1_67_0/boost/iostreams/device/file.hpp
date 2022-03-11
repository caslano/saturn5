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