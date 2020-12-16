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
6KMTtL+bpKUOdAchhlOoC5lyP/mUjN1HiT2BLB9MH3syWQBMH3vQaSoPptzTYeat3KMOMbAwA/NwU/v2tIzPS+1bsnwwpW/JAmBK36I8MrVvz8jyzEp5QWT5YPrywsgCYMq6KmSNTNLKWv7rizz/TL+8EAPzkKVXlxiy9OqSYJBnkoGJv9Ivz02WXnkeMgtM6VsDizawGAOLM7B4sqXmb2aiDYfrOK4gvgvyWtuk3INwk7U1SesbdFqu/3KRpVPuF7guafu0ZrN+fbgb7XJFtrVQ2jqaLB9M39bxZAEwfVsnkVlgyr17smqafaW/w+oEbMY4u5q+xSjWxV47GOUZmPsa3V9i9o/13i2MQbJrzA5uCviKOfI6nRcwu1+4ovxm/g29nT/jfw9jiawbM1Pc3+0Qu4FF3KRzFGaf/m6UHW1N5qPZF6F/hzGBbI+XtOZfzg5DnrdpntfsM/17R4NFdzA+72v35DR74SmSDe1J1sckrdU/VSegLg/p/pJZ2vL393cg3RMnvpuUSn8b/jnrB9TlqbRP9PfS4g4fMeafyec10jZ2Pt/oMdKRZWZ2oNR+ua40WTlm9WvfXIy6kP3IbKrP3BdI99wpQpn9e+XPBegjsmRmmxLm7ke/v3CK7czq1BhfBTEk0zOQzEJy5LiOGMisMP31UTRZVWbVm5fugDFIVobZjLm97dinU5yiArNcXT/Kb7mSlWZW1/9QMvqdrBuzHDvv7EN8L53iB2aRzhLzEIOBJRiY61X65lFsjM8bee1EloP37dFJV9AuZBaYch+FzM2s66lypxHfa6fYy+x9rlZzUc83dL7ErKj3eif6SLGKDwZVwHhRbOZ99q3ht/QsFbOkCTN6oJ5kvN9P9H3mgznrHc0vfOy2KHAZdVFsYTvrF7QLWTVm2eaN+Auxv9en+znx1Ub0LRnvh+bvbnmhb8l4P7QsE/UcMZDlYrYy86bDaM8P+n2z5gy77HeyBszap0zLhvLIoph1Kfjld6T7SNdAzCZlrz8e44XM18T2o4udMC+JVFxXkSnXY2S1mLUd/iw72posVLMP9Lfx2RMpiJ2sqUnaszNDTmF++SLTvVfSJZPVMkl70ad7K6QTLnxv4h39+3KRTz7Yb80uMVizt/Tvv0rMWY/+83bh2+lv6N9LP32dhHr6uMQ8Ic1xvNZY5JnBJQqydEVWl3qA/vtOn27xwu+KY5yRpbJ0MTVG1MT5p1Vfl3bhIVXRtzZ9nv1uX9iHtra7RABL96ZT4ZFoM4dLzGHpto1bNg397nSJ6czy/z1jFsaLS5/u0pVBoeh3P5cozMpb16ooLCaTPp3vu9Q7iC+zC3P5a6F865SsLLNs1duGo55kDmaD19dcgvYku8msY9KWeYg9C9WFWcU6q1Yhz6wuMYtZ4fBPq1GXbC7xmll0m6UYE3HZ9Xm6G15KQjp/l8jJLFf89LvoI7I2zPK+T3yNepJl1trzFf17Y+2WaM+wnC5xXUg7ER7oj/JyuUQIS3c6Q9VU5JnbJYaydM8ebv8FfZSH+gGmv8cZpxi/VxmvGL9vmsBNOU4nKsbvmyaRRTJLnOflgzYLcInszMoumByLeip2bdbbLqiLYv0qLo1DeWQOmP7beSKQm/5eehBZQ2ar4mIdqCdZB2bXU099r1naRvG9SdryV0+nI11el5goWP9luy6v0fO5RAlmdzq8z4s5i6wQs91dkuuhXchczP4zMG4z2kWxq1njfdEuZIWZhZ9avAPzWX69/Wfj37hGCFEs97gzuVBPxW7MypkZ9STjdfHf4Zb3DpV087wHTcO4VuzSua4r0UcF9Hbu12JoszDFct++uQT9oNi8hh9OYMwrxr8Pm6TYksg=
*/