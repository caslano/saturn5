//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_FSTREAM_HPP_INCLUDED
#define BOOST_NOWIDE_FSTREAM_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#include <boost/nowide/detail/is_path.hpp>
#include <boost/nowide/filebuf.hpp>
#include <istream>
#include <ostream>
#include <utility>

namespace boost {
namespace nowide {
    /// \cond INTERNAL
    namespace detail {
        // clang-format off
        struct StreamTypeIn
        {
            static std::ios_base::openmode mode() { return std::ios_base::in; }
            static std::ios_base::openmode mode_modifier() { return mode(); }
            template<typename CharType, typename Traits>
            struct stream_base{
                using type = std::basic_istream<CharType, Traits>;
            };
        };
        struct StreamTypeOut
        {
            static std::ios_base::openmode mode() { return std::ios_base::out; }
            static std::ios_base::openmode mode_modifier() { return mode(); }
            template<typename CharType, typename Traits>
            struct stream_base{
                using type = std::basic_ostream<CharType, Traits>;
            };
        };
        struct StreamTypeInOut
        {
            static std::ios_base::openmode mode() { return std::ios_base::in | std::ios_base::out; }
            static std::ios_base::openmode mode_modifier() { return std::ios_base::openmode(); }
            template<typename CharType, typename Traits>
            struct stream_base{
                using type = std::basic_iostream<CharType, Traits>;
            };
        };
        // clang-format on

        /// Base class for all basic_*fstream classes
        /// Contains basic_filebuf instance so its pointer can be used to construct basic_*stream
        /// Provides common functions to reduce boilerplate code including inheriting from
        /// the correct std::basic_[io]stream class and initializing it
        /// \tparam T_StreamType One of StreamType* above.
        ///         Class used instead of value, because openmode::operator| may not be constexpr
        /// \tparam FileBufType Discriminator to force a differing ABI if depending on the contained filebuf
        template<typename CharType,
                 typename Traits,
                 typename T_StreamType,
                 int FileBufType = BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT>
        class fstream_impl;

    } // namespace detail
    /// \endcond

    ///
    /// \brief Same as std::basic_ifstream<char> but accepts UTF-8 strings under Windows
    ///
    template<typename CharType, typename Traits = std::char_traits<CharType>>
    class basic_ifstream : public detail::fstream_impl<CharType, Traits, detail::StreamTypeIn>
    {
        using fstream_impl = detail::fstream_impl<CharType, Traits, detail::StreamTypeIn>;

    public:
        basic_ifstream()
        {}

        explicit basic_ifstream(const char* file_name, std::ios_base::openmode mode = std::ios_base::in)
        {
            open(file_name, mode);
        }
#if BOOST_NOWIDE_USE_WCHAR_OVERLOADS
        explicit basic_ifstream(const wchar_t* file_name, std::ios_base::openmode mode = std::ios_base::in)
        {
            open(file_name, mode);
        }
#endif

        explicit basic_ifstream(const std::string& file_name, std::ios_base::openmode mode = std::ios_base::in)
        {
            open(file_name, mode);
        }

        template<typename Path>
        explicit basic_ifstream(const Path& file_name,
                                detail::enable_if_path_t<Path, std::ios_base::openmode> mode = std::ios_base::in)
        {
            open(file_name, mode);
        }
        using fstream_impl::open;
        using fstream_impl::is_open;
        using fstream_impl::close;
        using fstream_impl::rdbuf;
        using fstream_impl::swap;
        basic_ifstream(const basic_ifstream&) = delete;
        basic_ifstream& operator=(const basic_ifstream&) = delete;
        basic_ifstream(basic_ifstream&& other) noexcept : fstream_impl(std::move(other))
        {}
        basic_ifstream& operator=(basic_ifstream&& rhs) noexcept
        {
            fstream_impl::operator=(std::move(rhs));
            return *this;
        }
    };

    ///
    /// \brief Same as std::basic_ofstream<char> but accepts UTF-8 strings under Windows
    ///

    template<typename CharType, typename Traits = std::char_traits<CharType>>
    class basic_ofstream : public detail::fstream_impl<CharType, Traits, detail::StreamTypeOut>
    {
        using fstream_impl = detail::fstream_impl<CharType, Traits, detail::StreamTypeOut>;

    public:
        basic_ofstream()
        {}
        explicit basic_ofstream(const char* file_name, std::ios_base::openmode mode = std::ios_base::out)
        {
            open(file_name, mode);
        }
#if BOOST_NOWIDE_USE_WCHAR_OVERLOADS
        explicit basic_ofstream(const wchar_t* file_name, std::ios_base::openmode mode = std::ios_base::out)
        {
            open(file_name, mode);
        }
#endif
        explicit basic_ofstream(const std::string& file_name, std::ios_base::openmode mode = std::ios_base::out)
        {
            open(file_name, mode);
        }
        template<typename Path>
        explicit basic_ofstream(const Path& file_name,
                                detail::enable_if_path_t<Path, std::ios_base::openmode> mode = std::ios_base::out)
        {
            open(file_name, mode);
        }

        using fstream_impl::open;
        using fstream_impl::is_open;
        using fstream_impl::close;
        using fstream_impl::rdbuf;
        using fstream_impl::swap;
        basic_ofstream(const basic_ofstream&) = delete;
        basic_ofstream& operator=(const basic_ofstream&) = delete;
        basic_ofstream(basic_ofstream&& other) noexcept : fstream_impl(std::move(other))
        {}
        basic_ofstream& operator=(basic_ofstream&& rhs)
        {
            fstream_impl::operator=(std::move(rhs));
            return *this;
        }
    };

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4250) // <class> : inherits <method> via dominance
#endif
    ///
    /// \brief Same as std::basic_fstream<char> but accepts UTF-8 strings under Windows
    ///
    template<typename CharType, typename Traits = std::char_traits<CharType>>
    class basic_fstream : public detail::fstream_impl<CharType, Traits, detail::StreamTypeInOut>
    {
        using fstream_impl = detail::fstream_impl<CharType, Traits, detail::StreamTypeInOut>;

    public:
        basic_fstream()
        {}
        explicit basic_fstream(const char* file_name,
                               std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
        {
            open(file_name, mode);
        }
#if BOOST_NOWIDE_USE_WCHAR_OVERLOADS
        explicit basic_fstream(const wchar_t* file_name,
                               std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
        {
            open(file_name, mode);
        }
#endif
        explicit basic_fstream(const std::string& file_name,
                               std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
        {
            open(file_name, mode);
        }
        template<typename Path>
        explicit basic_fstream(const Path& file_name,
                               detail::enable_if_path_t<Path, std::ios_base::openmode> mode = std::ios_base::in
                                                                                              | std::ios_base::out)
        {
            open(file_name, mode);
        }

        using fstream_impl::open;
        using fstream_impl::is_open;
        using fstream_impl::close;
        using fstream_impl::rdbuf;
        using fstream_impl::swap;
        basic_fstream(const basic_fstream&) = delete;
        basic_fstream& operator=(const basic_fstream&) = delete;
        basic_fstream(basic_fstream&& other) noexcept : fstream_impl(std::move(other))
        {}
        basic_fstream& operator=(basic_fstream&& rhs)
        {
            fstream_impl::operator=(std::move(rhs));
            return *this;
        }
    };

    template<typename CharType, typename Traits>
    void swap(basic_ifstream<CharType, Traits>& lhs, basic_ifstream<CharType, Traits>& rhs)
    {
        lhs.swap(rhs);
    }
    template<typename CharType, typename Traits>
    void swap(basic_ofstream<CharType, Traits>& lhs, basic_ofstream<CharType, Traits>& rhs)
    {
        lhs.swap(rhs);
    }
    template<typename CharType, typename Traits>
    void swap(basic_fstream<CharType, Traits>& lhs, basic_fstream<CharType, Traits>& rhs)
    {
        lhs.swap(rhs);
    }

    ///
    /// Same as std::filebuf but accepts UTF-8 strings under Windows
    ///
    using filebuf = basic_filebuf<char>;
    ///
    /// Same as std::ifstream but accepts UTF-8 strings under Windows
    /// and *\::filesystem::path on all systems
    ///
    using ifstream = basic_ifstream<char>;
    ///
    /// Same as std::ofstream but accepts UTF-8 strings under Windows
    /// and *\::filesystem::path on all systems
    ///
    using ofstream = basic_ofstream<char>;
    ///
    /// Same as std::fstream but accepts UTF-8 strings under Windows
    /// and *\::filesystem::path on all systems
    ///
    using fstream = basic_fstream<char>;

    // Implementation
    namespace detail {
        /// Holds an instance of T
        /// Required to make sure this is constructed first before passing it to sibling classes
        template<typename T>
        struct buf_holder
        {
            T buf_;
        };
        template<typename CharType, typename Traits, typename T_StreamType, int>
        class fstream_impl : private buf_holder<basic_filebuf<CharType, Traits>>, // must be first due to init order
                             public T_StreamType::template stream_base<CharType, Traits>::type
        {
            using internal_buffer_type = basic_filebuf<CharType, Traits>;
            using base_buf_holder = buf_holder<internal_buffer_type>;
            using stream_base = typename T_StreamType::template stream_base<CharType, Traits>::type;

        public:
            using stream_base::setstate;
            using stream_base::clear;

        protected:
            using base_buf_holder::buf_;

            fstream_impl() : stream_base(&buf_)
            {}
            fstream_impl(const fstream_impl&) = delete;
            fstream_impl& operator=(const fstream_impl&) = delete;

            // coverity[exn_spec_violation]
            fstream_impl(fstream_impl&& other) noexcept :
                base_buf_holder(std::move(other)), stream_base(std::move(other))
            {
                this->set_rdbuf(rdbuf());
            }
            fstream_impl& operator=(fstream_impl&& rhs) noexcept
            {
                base_buf_holder::operator=(std::move(rhs));
                stream_base::operator=(std::move(rhs));
                return *this;
            }
            void swap(fstream_impl& other)
            {
                stream_base::swap(other);
                rdbuf()->swap(*other.rdbuf());
            }

            void open(const std::string& file_name, std::ios_base::openmode mode = T_StreamType::mode())
            {
                open(file_name.c_str(), mode);
            }
            template<typename Path>
            detail::enable_if_path_t<Path, void> open(const Path& file_name,
                                                      std::ios_base::openmode mode = T_StreamType::mode())
            {
                open(file_name.c_str(), mode);
            }
            void open(const char* file_name, std::ios_base::openmode mode = T_StreamType::mode())
            {
                if(!rdbuf()->open(file_name, mode | T_StreamType::mode_modifier()))
                    setstate(std::ios_base::failbit);
                else
                    clear();
            }
#if BOOST_NOWIDE_USE_WCHAR_OVERLOADS
            void open(const wchar_t* file_name, std::ios_base::openmode mode = T_StreamType::mode())
            {
                if(!rdbuf()->open(file_name, mode | T_StreamType::mode_modifier()))
                    setstate(std::ios_base::failbit);
                else
                    clear();
            }
#endif
            bool is_open()
            {
                return rdbuf()->is_open();
            }
            bool is_open() const
            {
                return rdbuf()->is_open();
            }
            void close()
            {
                if(!rdbuf()->close())
                    setstate(std::ios_base::failbit);
            }

            internal_buffer_type* rdbuf() const
            {
                return const_cast<internal_buffer_type*>(&buf_);
            }
        };
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
    } // namespace detail
} // namespace nowide
} // namespace boost

#endif

/* fstream.hpp
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
*/