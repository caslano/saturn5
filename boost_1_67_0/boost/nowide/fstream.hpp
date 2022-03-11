//
//  Copyright (c) 2012 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NOWIDE_FSTREAM_HPP_INCLUDED
#define BOOST_NOWIDE_FSTREAM_HPP_INCLUDED

#include <boost/nowide/config.hpp>
#include <boost/nowide/filebuf.hpp>
#include <istream>
#include <ostream>

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
                typedef std::basic_istream<CharType, Traits> type;
            };
        };
        struct StreamTypeOut
        {
            static std::ios_base::openmode mode() { return std::ios_base::out; }
            static std::ios_base::openmode mode_modifier() { return mode(); }
            template<typename CharType, typename Traits>
            struct stream_base{
                typedef std::basic_ostream<CharType, Traits> type;
            };
        };
        struct StreamTypeInOut
        {
            static std::ios_base::openmode mode() { return std::ios_base::in | std::ios_base::out; }
            static std::ios_base::openmode mode_modifier() { return std::ios_base::openmode(); }
            template<typename CharType, typename Traits>
            struct stream_base{
                typedef std::basic_iostream<CharType, Traits> type;
            };
        };
        // clang-format on

        /// Base class for all basic_*fstream classes
        /// Contains basic_filebuf instance so its pointer can be used to construct basic_*stream
        /// Provides common functions to reduce boilerplate code including inheriting from
        /// the correct std::basic_[io]stream class and initializing it
        /// \tparam T_StreamType One of StreamType* above.
        ///         Class used instead of value, because openmode::operator| may not be constexpr
        template<typename CharType, typename Traits, typename T_StreamType>
        class fstream_impl;

        template<typename Path, typename Result>
        struct enable_if_path;
    } // namespace detail
    /// \endcond

    ///
    /// \brief Same as std::basic_ifstream<char> but accepts UTF-8 strings under Windows
    ///
    template<typename CharType, typename Traits = std::char_traits<CharType> >
    class basic_ifstream : public detail::fstream_impl<CharType, Traits, detail::StreamTypeIn>
    {
        typedef detail::fstream_impl<CharType, Traits, detail::StreamTypeIn> fstream_impl;

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
        explicit basic_ifstream(
          const Path& file_name,
          typename detail::enable_if_path<Path, std::ios_base::openmode>::type mode = std::ios_base::in)
        {
            open(file_name, mode);
        }
        using fstream_impl::open;
        using fstream_impl::is_open;
        using fstream_impl::close;
        using fstream_impl::rdbuf;
#if BOOST_NOWIDE_CXX11
        using fstream_impl::swap;
        basic_ifstream(const basic_ifstream& other) = delete;
        basic_ifstream& operator=(const basic_ifstream& rhs) = delete;
        basic_ifstream(basic_ifstream&& other) noexcept : fstream_impl(std::move(other))
        {}
        basic_ifstream& operator=(basic_ifstream&& rhs) noexcept
        {
            fstream_impl::operator=(std::move(rhs));
            return *this;
        }
#endif
    };

    ///
    /// \brief Same as std::basic_ofstream<char> but accepts UTF-8 strings under Windows
    ///

    template<typename CharType, typename Traits = std::char_traits<CharType> >
    class basic_ofstream : public detail::fstream_impl<CharType, Traits, detail::StreamTypeOut>
    {
        typedef detail::fstream_impl<CharType, Traits, detail::StreamTypeOut> fstream_impl;

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
        explicit basic_ofstream(
          const Path& file_name,
          typename detail::enable_if_path<Path, std::ios_base::openmode>::type mode = std::ios_base::out)
        {
            open(file_name, mode);
        }

        using fstream_impl::open;
        using fstream_impl::is_open;
        using fstream_impl::close;
        using fstream_impl::rdbuf;
#if BOOST_NOWIDE_CXX11
        using fstream_impl::swap;
        basic_ofstream(const basic_ofstream& other) = delete;
        basic_ofstream& operator=(const basic_ofstream& rhs) = delete;
        basic_ofstream(basic_ofstream&& other) noexcept : fstream_impl(std::move(other))
        {}
        basic_ofstream& operator=(basic_ofstream&& rhs)
        {
            fstream_impl::operator=(std::move(rhs));
            return *this;
        }
#endif
    };

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4250) // <class> : inherits <method> via dominance
#endif
    ///
    /// \brief Same as std::basic_fstream<char> but accepts UTF-8 strings under Windows
    ///
    template<typename CharType, typename Traits = std::char_traits<CharType> >
    class basic_fstream : public detail::fstream_impl<CharType, Traits, detail::StreamTypeInOut>
    {
        typedef detail::fstream_impl<CharType, Traits, detail::StreamTypeInOut> fstream_impl;

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
                               typename detail::enable_if_path<Path, std::ios_base::openmode>::type mode =
                                 std::ios_base::in | std::ios_base::out)
        {
            open(file_name, mode);
        }

        using fstream_impl::open;
        using fstream_impl::is_open;
        using fstream_impl::close;
        using fstream_impl::rdbuf;
#if BOOST_NOWIDE_CXX11
        using fstream_impl::swap;
        basic_fstream(const basic_fstream& other) = delete;
        basic_fstream& operator=(const basic_fstream& rhs) = delete;
        basic_fstream(basic_fstream&& other) noexcept : fstream_impl(std::move(other))
        {}
        basic_fstream& operator=(basic_fstream&& rhs)
        {
            fstream_impl::operator=(std::move(rhs));
            return *this;
        }
#endif
    };
#if BOOST_NOWIDE_CXX11
    template<typename CharType, typename Traits>
    void swap(basic_filebuf<CharType, Traits>& lhs, basic_filebuf<CharType, Traits>& rhs)
    {
        lhs.swap(rhs);
    }
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
#endif

    ///
    /// Same as std::filebuf but accepts UTF-8 strings under Windows
    ///
    typedef basic_filebuf<char> filebuf;
    ///
    /// Same as std::ifstream but accepts UTF-8 strings under Windows
    /// and *\::filesystem::path on all systems
    ///
    typedef basic_ifstream<char> ifstream;
    ///
    /// Same as std::ofstream but accepts UTF-8 strings under Windows
    /// and *\::filesystem::path on all systems
    ///
    typedef basic_ofstream<char> ofstream;
    ///
    /// Same as std::fstream but accepts UTF-8 strings under Windows
    /// and *\::filesystem::path on all systems
    ///
    typedef basic_fstream<char> fstream;

    // Implementation
    namespace detail {
        /// Holds an instance of T
        /// Required to make sure this is constructed first before passing it to sibling classes
        template<typename T>
        struct buf_holder
        {
            T buf_;
        };
        template<typename CharType, typename Traits, typename T_StreamType>
        class fstream_impl : private buf_holder<basic_filebuf<CharType, Traits> >, // must be first due to init order
                             public T_StreamType::template stream_base<CharType, Traits>::type
        {
            typedef basic_filebuf<CharType, Traits> internal_buffer_type;
            typedef buf_holder<internal_buffer_type> base_buf_holder;
            typedef typename T_StreamType::template stream_base<CharType, Traits>::type stream_base;

        public:
            using stream_base::setstate;
            using stream_base::clear;

        protected:
            using base_buf_holder::buf_;

            fstream_impl() : stream_base(&buf_)
            {}

#if BOOST_NOWIDE_CXX11
            fstream_impl(const fstream_impl& other) = delete;
            fstream_impl& operator=(const fstream_impl& other) = delete;

            // coverity[exn_spec_violation]
            fstream_impl(fstream_impl&& other) noexcept : base_buf_holder(std::move(other)),
                                                          stream_base(std::move(other))
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
#endif

            void open(const std::string& file_name, std::ios_base::openmode mode = T_StreamType::mode())
            {
                open(file_name.c_str(), mode);
            }
            template<typename Path>
            typename detail::enable_if_path<Path, void>::type open(const Path& file_name,
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
        /// Trait to heuristically check for a *\::filesystem::path
        /// Done by checking for make_preferred and filename member functions with correct signature
        template<typename T>
        struct is_path
        {
            typedef char one;
            struct two
            {
                char dummy[2];
            };

            template<typename U, U& (U::*)(), U (U::*)() const>
            struct Check;
            template<typename U>
            static one test(Check<U, &U::make_preferred, &U::filename>*);
            template<typename U>
            static two test(...);

            enum
            {
                value = sizeof(test<T>(0)) == sizeof(one)
            };
        };
        template<bool B, typename T>
        struct enable_if
        {};
        template<typename T>
        struct enable_if<true, T>
        {
            typedef T type;
        };
        /// SFINAE trait which has a member "type = Result" if the Path is a *\::filesystem::path
        template<typename Path, typename Result>
        struct enable_if_path : enable_if<is_path<Path>::value, Result>
        {};
    } // namespace detail
} // namespace nowide
} // namespace boost

#endif

/* fstream.hpp
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
*/