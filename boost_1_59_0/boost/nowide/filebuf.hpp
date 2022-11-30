//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//  Copyright (c) 2019-2020 Alexander Grund
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
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
#include <ios>
#include <limits>
#include <locale>
#include <stdexcept>
#include <streambuf>
#else
#include <fstream>
#endif

namespace boost {
namespace nowide {
    namespace detail {
        /// Same as std::ftell but potentially with Large File Support
        BOOST_NOWIDE_DECL std::streampos ftell(FILE* file);
        /// Same as std::fseek but potentially with Large File Support
        BOOST_NOWIDE_DECL int fseek(FILE* file, std::streamoff offset, int origin);
    } // namespace detail

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
    template<typename CharType, typename Traits = std::char_traits<CharType>>
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
        using Traits = std::char_traits<char>;

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
        basic_filebuf(const basic_filebuf&) = delete;
        basic_filebuf& operator=(const basic_filebuf&) = delete;
        basic_filebuf(basic_filebuf&& other) noexcept : basic_filebuf()
        {
            swap(other);
        }
        basic_filebuf& operator=(basic_filebuf&& other) noexcept
        {
            close();
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
            if(pbase() == rhs.last_char_)
                setp(last_char_, (pptr() == epptr()) ? last_char_ : last_char_ + 1);
            if(eback() == rhs.last_char_)
                setg(last_char_, (gptr() == rhs.last_char_) ? last_char_ : last_char_ + 1, last_char_ + 1);

            if(rhs.pbase() == last_char_)
                rhs.setp(rhs.last_char_, (rhs.pptr() == rhs.epptr()) ? rhs.last_char_ : rhs.last_char_ + 1);
            if(rhs.eback() == last_char_)
            {
                rhs.setg(rhs.last_char_,
                         (rhs.gptr() == last_char_) ? rhs.last_char_ : rhs.last_char_ + 1,
                         rhs.last_char_ + 1);
            }
        }

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
            if(ate && detail::fseek(file_, 0, SEEK_END) != 0)
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
            setg(0, 0, 0);
            setp(0, 0);
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
            if(!std::use_facet<std::codecvt<char, char, std::mbstate_t>>(loc).always_noconv())
                throw std::runtime_error("Converting codecvts are not supported");
        }

    protected:
        std::streambuf* setbuf(char* s, std::streamsize n) override
        {
            assert(n >= 0);
            // Maximum compatibility: Discard all local buffers and use user-provided values
            // Users should call sync() before or better use it before any IO is done or any file is opened
            setg(NULL, NULL, NULL);
            setp(NULL, NULL);
            if(owns_buffer_)
            {
                delete[] buffer_;
                owns_buffer_ = false;
            }
            buffer_ = s;
            buffer_size_ = (n >= 0) ? static_cast<size_t>(n) : 0;
            return this;
        }

        int overflow(int c = EOF) override
        {
            if(!(mode_ & (std::ios_base::out | std::ios_base::app)))
                return EOF;

            if(!stop_reading())
                return EOF;

            size_t n = pptr() - pbase();
            if(n > 0)
            {
                if(std::fwrite(pbase(), 1, n, file_) != n)
                    return EOF;
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

        int sync() override
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

        int underflow() override
        {
            if(!(mode_ & std::ios_base::in))
                return EOF;
            if(!stop_writing())
                return EOF;
            // In text mode we cannot use a buffer size of more than 1 (i.e. single char only)
            // This is due to the need to seek back in case of a sync to "put back" unread chars.
            // However determining the number of chars to seek back is impossible in case there are newlines
            // as we cannot know if those were converted.
            if(buffer_size_ == 0 || !(mode_ & std::ios_base::binary))
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

        int pbackfail(int c = EOF) override
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

        std::streampos seekoff(std::streamoff off,
                               std::ios_base::seekdir seekdir,
                               std::ios_base::openmode = std::ios_base::in | std::ios_base::out) override
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
            if(detail::fseek(file_, off, whence) != 0)
                return EOF;
            return detail::ftell(file_);
        }
        std::streampos seekpos(std::streampos pos,
                               std::ios_base::openmode m = std::ios_base::in | std::ios_base::out) override
        {
            // Standard mandates "as-if fsetpos", but assume the effect is the same as fseek
            return seekoff(pos, std::ios_base::beg, m);
        }
        void imbue(const std::locale& loc) override
        {
            validate_cvt(loc);
        }

    private:
        /// Stop reading adjusting the file pointer if necessary
        /// Postcondition: gptr() == NULL
        bool stop_reading()
        {
            if(!gptr())
                return true;
            const auto off = gptr() - egptr();
            setg(0, 0, 0);
            if(!off)
                return true;
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-constant-out-of-range-compare"
#endif
            // coverity[result_independent_of_operands]
            if(off > std::numeric_limits<std::streamoff>::max())
                return false;
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
            return detail::fseek(file_, static_cast<std::streamoff>(off), SEEK_CUR) == 0;
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
    using filebuf = basic_filebuf<char>;

    /// Swap the basic_filebuf instances
    template<typename CharType, typename Traits>
    void swap(basic_filebuf<CharType, Traits>& lhs, basic_filebuf<CharType, Traits>& rhs)
    {
        lhs.swap(rhs);
    }

#endif // windows

} // namespace nowide
} // namespace boost

#endif

/* filebuf.hpp
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
*/