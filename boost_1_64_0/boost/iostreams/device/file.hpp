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
M1v3vRwf8vXvF97evEGUqNurXlpdUlvpvhdtbmOGq94ne3ivN2XrejvrmNU/vI7P9mJ5szoq528Zpy3XMctVxxNR2JayjXU8ZKjjXjYYaF5HOrc3OwZOoW9rO7r9xweE1zGJfZ3fvI6Vqyq925K8eh67Sr2f3M66rLai2NSvtb7jnrr3dmnbO+KN2CbL9Dab7ZOdA8Pb+zAVKXS1t7a6zFNbyee43lfHJOVzboypdbXzrSj2H/Vwj185HrM91z7dPCi8jU9RicrmbRQPcW99rzKKearyFOapx3u1Pk+dgB/6ovcRN/tMR/bJNvsoR/YtNvsKR+9T/obyBf9rSXr8pf33LfrJ3KLrpj9tPRe9z7HZ9zqyz7fZJz6yL7jZ9z16H/RofbI/UP626qeeJRbCImRWatPf7zqWv+f4+339d/DcOwPbfda+xnf8vdRRzs9ZfhhuFv/swriQX4DyqVDrZiOL4preO+eHw2EaHAr7wGGwvywvhqPhCjgGVsKxcB2cDzfA6+FGuBFuhuPgHXA8vBueCbfDs+B34dnwITgRPgcnwYNwPXwBboAvwSnwGDwHnoDZ8B/wXBhHowKwM5wGU+B0mAbz4GiYDyfA+XAevB7mw43wIpgDy+AMWAkvgNWSvkLS18KZcKuk75X0t+EsuBvOht+HF8EfwE/B/fBi+BJcDF+Bl8BfwUvhe3AJ7MC++AxMhYWwP1wKT4dlcAr8HJwKq+D5sBbOkPRMSV8EV8NyeAVcBzfA9fDz8BY4En4VDodbJb0TXgMfhF+Ae+EX4T5JPy3pn8I6/r0M18LX4Q3i94tt5Jmhepaq+lkWssknN8KYyLvCPNgLzofpcAEcDhfCTPgpOAFeDKfDxXAWvBReCC+DS2ARXA2Xws/DYngdLIU3weVwKyyDd8JyuAN+Dj4AV8D9cCU8ACvgIbgKvgqr4O9gDXwD1sI34RXwY3gljPdhV9gNXgVT4Rdgf/hFOAzWwTFwLRwH18GJ8FqYCzfAEngzXAY3w1XwVlgLvwyvkOUbZPlNsvxLcAncKfkfEL2HRe8x0Tsu16uBifp9iGr/dEByQjEe6NnMhhnwXNkvAXganAqnwvNgAAak3H2hZ1Lw+1JuL3mGpq5F7PEJ34L94NtwEHwHToTHYDbsIOW+T3oW/AucC/8K58vyS2V5oSwvgR/ClfAj+AVZfq2kbxI/+80wCX5VtrNV/PR3S/o4PBx6FgIfk7TyNZF2PI5+J/hD2A3+CKZKurek+8AnYYakR8OnYA58Gs6Gv4YXwh/DS+Bz8DPwp3AZ/BlcLulySa+GDdK+n8NN8EW4GR6Ct8GX4Q4p/174K/iopI/DOn1PnD4j7esi5yqWxGP44C2wI9wM+8Jb4RB4GxwB74Yj4RZ4HvwqnAm/BufK+nnwTmnfXfAyx/trd+p7vxzzpB49lF7wt03iNe6FQ+F9MAs+KtvbJdv7DpwDH5XyvwsLYD0slHSJpKvgg2K/h+Ct8GHIMvopdpJynhX91yR9HB7Q9wWxpcxracheqW9nGSdd4BjYE86DqbAUpsEVcCK8CqbLPNUX3gj7w7vgILgdZsBH4RBoH8+GwcFwOLwGToSb4Fi4DZ4B74NZcDccB/fI+mfhBPi8yidxLqH7NjInHHbFuWyVeeAO2AHeCQfAu+BgeDccAb8OR8Od0u7t8Fz4TXg+3AFnwm/BuaI3D94H81Ra4kX0PRDGqmp/83iRzzrfn+tRL8OhV4g49Yocelke9QIe9fI96hV61KtsRS81gf5b1z6xMK44GGMMzGHEEPvSUtyLI9alfeJcnDEu7vgWZ2yLM66FeBZnLIuOY3HGsGxBXLErxrgVZ8xKykuJxK2YY1Y=
*/