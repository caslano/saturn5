//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2019-2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_FILEBUF_HPP_INCLUDED
#define BOOST_NOWIDE_FILEBUF_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#if BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT
#include <boost/nowide/cstdio.hpp>
#include <boost/nowide/stackstring.hpp>
#include <cassert>
#include <cstdio>
#include <iosfwd>
#include <limits>
#include <locale>
#include <stdexcept>
#include <streambuf>
#else
#include <fstream>
#endif

namespace boost {
namespace nowide {
#if !BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT && !defined(BOOST_NOWIDE_DOXYGEN)
    using std::basic_filebuf;
    using std::filebuf;
#else // Windows
    ///
    /// \brief This forward declaration defines the basic_filebuf type.
    ///
    /// it is implemented and specialized for CharType = char, it
    /// implements std::filebuf over standard C I/O
    ///
    template<typename CharType, typename Traits = std::char_traits<CharType> >
    class basic_filebuf;

    ///
    /// \brief This is the implementation of std::filebuf
    ///
    /// it is implemented and specialized for CharType = char, it
    /// implements std::filebuf over standard C I/O
    ///
    template<>
    class basic_filebuf<char> : public std::basic_streambuf<char>
    {
        typedef std::char_traits<char> Traits;

    public:
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4351) // new behavior : elements of array will be default initialized
#endif
        ///
        /// Creates new filebuf
        ///
        basic_filebuf() :
            buffer_size_(BUFSIZ), buffer_(0), file_(0), owns_buffer_(false), last_char_(),
            mode_(std::ios_base::openmode(0))
        {
            setg(0, 0, 0);
            setp(0, 0);
        }
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
#if !BOOST_NOWIDE_CXX11
    private:
        // Non-copyable
        basic_filebuf(const basic_filebuf&);
        basic_filebuf& operator=(const basic_filebuf&);

    public:
#else
        basic_filebuf(const basic_filebuf&) = delete;
        basic_filebuf& operator=(const basic_filebuf&) = delete;
        basic_filebuf(basic_filebuf&& other) noexcept : basic_filebuf()
        {
            swap(other);
        }
        basic_filebuf& operator=(basic_filebuf&& other) noexcept
        {
            swap(other);
            return *this;
        }
        void swap(basic_filebuf& rhs)
        {
            std::basic_streambuf<char>::swap(rhs);
            using std::swap;
            swap(buffer_size_, rhs.buffer_size_);
            swap(buffer_, rhs.buffer_);
            swap(file_, rhs.file_);
            swap(owns_buffer_, rhs.owns_buffer_);
            swap(last_char_[0], rhs.last_char_[0]);
            swap(mode_, rhs.mode_);
            // Fixup last_char references
            if(epptr() == rhs.last_char_)
                setp(last_char_, last_char_);
            if(egptr() == rhs.last_char_)
                rhs.setg(last_char_, gptr() == rhs.last_char_ ? last_char_ : last_char_ + 1, last_char_ + 1);
            if(rhs.epptr() == last_char_)
                setp(rhs.last_char_, rhs.last_char_);
            if(rhs.egptr() == rhs.last_char_)
            {
                rhs.setg(rhs.last_char_,
                         rhs.gptr() == last_char_ ? rhs.last_char_ : rhs.last_char_ + 1,
                         rhs.last_char_ + 1);
            }
        }
#endif
        virtual ~basic_filebuf()
        {
            close();
        }

        ///
        /// Same as std::filebuf::open but s is UTF-8 string
        ///
        basic_filebuf* open(const std::string& s, std::ios_base::openmode mode)
        {
            return open(s.c_str(), mode);
        }
        ///
        /// Same as std::filebuf::open but s is UTF-8 string
        ///
        basic_filebuf* open(const char* s, std::ios_base::openmode mode)
        {
            const wstackstring name(s);
            return open(name.get(), mode);
        }
        /// Opens the file with the given name, see std::filebuf::open
        basic_filebuf* open(const wchar_t* s, std::ios_base::openmode mode)
        {
            if(is_open())
                return NULL;
            validate_cvt(this->getloc());
            const bool ate = (mode & std::ios_base::ate) != 0;
            if(ate)
                mode &= ~std::ios_base::ate;
            const wchar_t* smode = get_mode(mode);
            if(!smode)
                return 0;
            file_ = detail::wfopen(s, smode);
            if(!file_)
                return 0;
            if(ate && std::fseek(file_, 0, SEEK_END) != 0)
            {
                close();
                return 0;
            }
            mode_ = mode;
            return this;
        }
        ///
        /// Same as std::filebuf::close()
        ///
        basic_filebuf* close()
        {
            if(!is_open())
                return NULL;
            bool res = sync() == 0;
            if(std::fclose(file_) != 0)
                res = false;
            file_ = NULL;
            mode_ = std::ios_base::openmode(0);
            if(owns_buffer_)
            {
                delete[] buffer_;
                buffer_ = NULL;
                owns_buffer_ = false;
            }
            return res ? this : NULL;
        }
        ///
        /// Same as std::filebuf::is_open()
        ///
        bool is_open() const
        {
            return file_ != NULL;
        }

    private:
        void make_buffer()
        {
            if(buffer_)
                return;
            if(buffer_size_ > 0)
            {
                buffer_ = new char[buffer_size_];
                owns_buffer_ = true;
            }
        }
        void validate_cvt(const std::locale& loc)
        {
            if(!std::use_facet<std::codecvt<char, char, std::mbstate_t> >(loc).always_noconv())
                throw std::runtime_error("Converting codecvts are not supported");
        }

    protected:
        virtual std::streambuf* setbuf(char* s, std::streamsize n)
        {
            assert(n >= 0);
            // Maximum compatibility: Discard all local buffers and use user-provided values
            // Users should call sync() before or better use it before any IO is done or any file is opened
            setg(NULL, NULL, NULL);
            setp(NULL, NULL);
            if(owns_buffer_)
                delete[] buffer_;
            buffer_ = s;
            buffer_size_ = (n >= 0) ? static_cast<size_t>(n) : 0;
            return this;
        }

        virtual int overflow(int c = EOF)
        {
            if(!(mode_ & std::ios_base::out))
                return EOF;

            if(!stop_reading())
                return EOF;

            size_t n = pptr() - pbase();
            if(n > 0)
            {
                if(std::fwrite(pbase(), 1, n, file_) != n)
                    return -1;
                setp(buffer_, buffer_ + buffer_size_);
                if(c != EOF)
                {
                    *buffer_ = Traits::to_char_type(c);
                    pbump(1);
                }
            } else if(c != EOF)
            {
                if(buffer_size_ > 0)
                {
                    make_buffer();
                    setp(buffer_, buffer_ + buffer_size_);
                    *buffer_ = Traits::to_char_type(c);
                    pbump(1);
                } else if(std::fputc(c, file_) == EOF)
                {
                    return EOF;
                } else if(!pptr())
                {
                    // Set to dummy value so we know we have written something
                    setp(last_char_, last_char_);
                }
            }
            return Traits::not_eof(c);
        }

        virtual int sync()
        {
            if(!file_)
                return 0;
            bool result;
            if(pptr())
            {
                result = overflow() != EOF;
                // Only flush if anything was written, otherwise behavior of fflush is undefined
                if(std::fflush(file_) != 0)
                    return result = false;
            } else
                result = stop_reading();
            return result ? 0 : -1;
        }

        virtual int underflow()
        {
            if(!(mode_ & std::ios_base::in))
                return EOF;
            if(!stop_writing())
                return EOF;
            if(buffer_size_ == 0)
            {
                const int c = std::fgetc(file_);
                if(c == EOF)
                    return EOF;
                last_char_[0] = Traits::to_char_type(c);
                setg(last_char_, last_char_, last_char_ + 1);
            } else
            {
                make_buffer();
                const size_t n = std::fread(buffer_, 1, buffer_size_, file_);
                setg(buffer_, buffer_, buffer_ + n);
                if(n == 0)
                    return EOF;
            }
            return Traits::to_int_type(*gptr());
        }

        virtual int pbackfail(int c = EOF)
        {
            if(!(mode_ & std::ios_base::in))
                return EOF;
            if(!stop_writing())
                return EOF;
            if(gptr() > eback())
                gbump(-1);
            else if(seekoff(-1, std::ios_base::cur) != std::streampos(std::streamoff(-1)))
            {
                if(underflow() == EOF)
                    return EOF;
            } else
                return EOF;

            // Case 1: Caller just wanted space for 1 char
            if(c == EOF)
                return Traits::not_eof(c);
            // Case 2: Caller wants to put back different char
            // gptr now points to the (potentially newly read) previous char
            if(*gptr() != c)
                *gptr() = Traits::to_char_type(c);
            return Traits::not_eof(c);
        }

        virtual std::streampos seekoff(std::streamoff off,
                                       std::ios_base::seekdir seekdir,
                                       std::ios_base::openmode = std::ios_base::in | std::ios_base::out)
        {
            if(!file_)
                return EOF;
            // Switching between input<->output requires a seek
            // So do NOT optimize for seekoff(0, cur) as No-OP

            // On some implementations a seek also flushes, so do a full sync
            if(sync() != 0)
                return EOF;
            int whence;
            switch(seekdir)
            {
            case std::ios_base::beg: whence = SEEK_SET; break;
            case std::ios_base::cur: whence = SEEK_CUR; break;
            case std::ios_base::end: whence = SEEK_END; break;
            default: assert(false); return EOF;
            }
            assert(off <= std::numeric_limits<long>::max());
            if(std::fseek(file_, static_cast<long>(off), whence) != 0)
                return EOF;
            return std::ftell(file_);
        }
        virtual std::streampos seekpos(std::streampos pos,
                                       std::ios_base::openmode m = std::ios_base::in | std::ios_base::out)
        {
            // Standard mandates "as-if fsetpos", but assume the effect is the same as fseek
            return seekoff(pos, std::ios_base::beg, m);
        }
        virtual void imbue(const std::locale& loc)
        {
            validate_cvt(loc);
        }

    private:
        /// Stop reading adjusting the file pointer if necessary
        /// Postcondition: gptr() == NULL
        bool stop_reading()
        {
            if(gptr())
            {
                const std::streamsize off = gptr() - egptr();
                setg(0, 0, 0);
                assert(off <= std::numeric_limits<long>::max());
                if(off && std::fseek(file_, static_cast<long>(off), SEEK_CUR) != 0)
                    return false;
            }
            return true;
        }

        /// Stop writing. If any bytes are to be written, writes them to file
        /// Postcondition: pptr() == NULL
        bool stop_writing()
        {
            if(pptr())
            {
                const char* const base = pbase();
                const size_t n = pptr() - base;
                setp(0, 0);
                if(n && std::fwrite(base, 1, n, file_) != n)
                    return false;
            }
            return true;
        }

        void reset(FILE* f = 0)
        {
            sync();
            if(file_)
            {
                fclose(file_);
                file_ = 0;
            }
            file_ = f;
        }

        static const wchar_t* get_mode(std::ios_base::openmode mode)
        {
            //
            // done according to n2914 table 106 27.9.1.4
            //

            // note can't use switch case as overload operator can't be used
            // in constant expression
            if(mode == (std::ios_base::out))
                return L"w";
            if(mode == (std::ios_base::out | std::ios_base::app))
                return L"a";
            if(mode == (std::ios_base::app))
                return L"a";
            if(mode == (std::ios_base::out | std::ios_base::trunc))
                return L"w";
            if(mode == (std::ios_base::in))
                return L"r";
            if(mode == (std::ios_base::in | std::ios_base::out))
                return L"r+";
            if(mode == (std::ios_base::in | std::ios_base::out | std::ios_base::trunc))
                return L"w+";
            if(mode == (std::ios_base::in | std::ios_base::out | std::ios_base::app))
                return L"a+";
            if(mode == (std::ios_base::in | std::ios_base::app))
                return L"a+";
            if(mode == (std::ios_base::binary | std::ios_base::out))
                return L"wb";
            if(mode == (std::ios_base::binary | std::ios_base::out | std::ios_base::app))
                return L"ab";
            if(mode == (std::ios_base::binary | std::ios_base::app))
                return L"ab";
            if(mode == (std::ios_base::binary | std::ios_base::out | std::ios_base::trunc))
                return L"wb";
            if(mode == (std::ios_base::binary | std::ios_base::in))
                return L"rb";
            if(mode == (std::ios_base::binary | std::ios_base::in | std::ios_base::out))
                return L"r+b";
            if(mode == (std::ios_base::binary | std::ios_base::in | std::ios_base::out | std::ios_base::trunc))
                return L"w+b";
            if(mode == (std::ios_base::binary | std::ios_base::in | std::ios_base::out | std::ios_base::app))
                return L"a+b";
            if(mode == (std::ios_base::binary | std::ios_base::in | std::ios_base::app))
                return L"a+b";
            return 0;
        }

        size_t buffer_size_;
        char* buffer_;
        FILE* file_;
        bool owns_buffer_;
        char last_char_[1];
        std::ios::openmode mode_;
    };

    ///
    /// \brief Convenience typedef
    ///
    typedef basic_filebuf<char> filebuf;

#endif // windows

} // namespace nowide
} // namespace boost

#endif

/* filebuf.hpp
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
*/