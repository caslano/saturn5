/*=============================================================================
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MANIP_05052005_1200)
#define FUSION_MANIP_05052005_1200

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>
#include <string>
#include <vector>
#include <cctype>

// Tuple I/O manipulators

#define FUSION_GET_CHAR_TYPE(T) typename T::char_type
#define FUSION_GET_TRAITS_TYPE(T) typename T::traits_type

#define FUSION_STRING_OF_STREAM(Stream)                                         \
    std::basic_string<                                                          \
        FUSION_GET_CHAR_TYPE(Stream)                                            \
      , FUSION_GET_TRAITS_TYPE(Stream)                                          \
    >

//$$$ these should be part of the public API$$$
//$$$ rename tuple_open, tuple_close and tuple_delimiter to 
//    open, close and delimeter and add these synonyms to the
//    TR1 tuple module.

namespace boost { namespace fusion
{
    namespace detail
    {
        template <typename Tag>
        int get_xalloc_index(Tag* = 0)
        {
            // each Tag will have a unique index
            static int index = std::ios::xalloc();
            return index;
        }

        template <typename Stream, typename Tag, typename T>
        struct stream_data
        {
            struct arena
            {
                ~arena()
                {
                    for (
                        typename std::vector<T*>::iterator i = data.begin()
                      ; i != data.end()
                      ; ++i)
                    {
                        delete *i;
                    }
                }

                std::vector<T*> data;
            };

            static void attach(Stream& stream, T const& data)
            {
                static arena ar; // our arena
                ar.data.push_back(new T(data));
                stream.pword(get_xalloc_index<Tag>()) = ar.data.back();
            }

            static T const* get(Stream& stream)
            {
                return (T const*)stream.pword(get_xalloc_index<Tag>());
            }
        };

        template <typename Tag, typename Stream>
        class string_ios_manip
        {
        public:

            typedef FUSION_STRING_OF_STREAM(Stream) string_type;

            typedef stream_data<Stream, Tag, string_type> stream_data_t;

            string_ios_manip(Stream& str_)
                : stream(str_)
            {}

            void
            set(string_type const& s)
            {
                stream_data_t::attach(stream, s);
            }

            void
            print(char const* default_) const
            {
                // print a delimiter
                string_type const* p = stream_data_t::get(stream);
                if (p)
                    stream << *p;
                else
                    stream << default_;
            }

            void
            read(char const* default_) const
            {
                // read a delimiter
                string_type const* p = stream_data_t::get(stream);
                std::ws(stream);

                if (p)
                {
                    typedef typename string_type::const_iterator iterator;
                    for (iterator i = p->begin(); i != p->end(); ++i)
                        check_delim(*i);
                }
                else
                {
                    while (*default_)
                        check_delim(*default_++);
                }
            }

        private:

            template <typename Char>
            void
            check_delim(Char c) const
            {
                using namespace std;
                if (!isspace(c))
                {
                    if (stream.get() != c)
                    {
                        stream.unget();
                        stream.setstate(std::ios::failbit);
                    }
                }
            }

            Stream& stream;

            // silence MSVC warning C4512: assignment operator could not be generated
            BOOST_DELETED_FUNCTION(string_ios_manip& operator= (string_ios_manip const&))
        };

    } // detail


#if defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

#define STD_TUPLE_DEFINE_MANIPULATOR_FUNCTIONS(name)                            \
    template <typename Char, typename Traits>                                   \
    inline detail::name##_type<Char, Traits>                                    \
    name(const std::basic_string<Char, Traits>& s)                              \
    {                                                                           \
        return detail::name##_type<Char, Traits>(s);                            \
    }                                                                           \
                                                                                \
    inline detail::name##_type<char>                                            \
    name(char const* s)                                                         \
    {                                                                           \
        return detail::name##_type<char>(std::basic_string<char>(s));           \
    }                                                                           \
                                                                                \
    inline detail::name##_type<wchar_t>                                         \
    name(wchar_t const* s)                                                      \
    {                                                                           \
        return detail::name##_type<wchar_t>(std::basic_string<wchar_t>(s));     \
    }                                                                           \
                                                                                \
    inline detail::name##_type<char>                                            \
    name(char c)                                                                \
    {                                                                           \
        return detail::name##_type<char>(std::basic_string<char>(1, c));        \
    }                                                                           \
                                                                                \
    inline detail::name##_type<wchar_t>                                         \
    name(wchar_t c)                                                             \
    {                                                                           \
        return detail::name##_type<wchar_t>(std::basic_string<wchar_t>(1, c));  \
    }

#else // defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

#define STD_TUPLE_DEFINE_MANIPULATOR_FUNCTIONS(name)                            \
    template <typename Char, typename Traits>                                   \
    inline detail::name##_type<Char, Traits>                                    \
    name(const std::basic_string<Char, Traits>& s)                              \
    {                                                                           \
        return detail::name##_type<Char, Traits>(s);                            \
    }                                                                           \
                                                                                \
    template <typename Char>                                                    \
    inline detail::name##_type<Char>                                            \
    name(Char s[])                                                              \
    {                                                                           \
        return detail::name##_type<Char>(std::basic_string<Char>(s));           \
    }                                                                           \
                                                                                \
    template <typename Char>                                                    \
    inline detail::name##_type<Char>                                            \
    name(Char const s[])                                                        \
    {                                                                           \
        return detail::name##_type<Char>(std::basic_string<Char>(s));           \
    }                                                                           \
                                                                                \
    template <typename Char>                                                    \
    inline detail::name##_type<Char>                                            \
    name(Char c)                                                                \
    {                                                                           \
        return detail::name##_type<Char>(std::basic_string<Char>(1, c));        \
    }

#endif

#define STD_TUPLE_DEFINE_MANIPULATOR(name)                                      \
    namespace detail                                                            \
    {                                                                           \
        struct name##_tag;                                                      \
                                                                                \
        template <typename Char, typename Traits = std::char_traits<Char> >     \
        struct name##_type                                                      \
        {                                                                       \
            typedef std::basic_string<Char, Traits> string_type;                \
            string_type data;                                                   \
            name##_type(const string_type& d): data(d) {}                       \
        };                                                                      \
                                                                                \
        template <typename Stream, typename Char, typename Traits>              \
        Stream& operator>>(Stream& s, const name##_type<Char,Traits>& m)        \
        {                                                                       \
            string_ios_manip<name##_tag, Stream> manip(s);                      \
            manip.set(m.data);                                                  \
            return s;                                                           \
        }                                                                       \
                                                                                \
        template <typename Stream, typename Char, typename Traits>              \
        Stream& operator<<(Stream& s, const name##_type<Char,Traits>& m)        \
        {                                                                       \
            string_ios_manip<name##_tag, Stream> manip(s);                      \
            manip.set(m.data);                                                  \
            return s;                                                           \
        }                                                                       \
    }                                                                           \


    STD_TUPLE_DEFINE_MANIPULATOR(tuple_open)
    STD_TUPLE_DEFINE_MANIPULATOR(tuple_close)
    STD_TUPLE_DEFINE_MANIPULATOR(tuple_delimiter)

    STD_TUPLE_DEFINE_MANIPULATOR_FUNCTIONS(tuple_open)
    STD_TUPLE_DEFINE_MANIPULATOR_FUNCTIONS(tuple_close)
    STD_TUPLE_DEFINE_MANIPULATOR_FUNCTIONS(tuple_delimiter)

#undef STD_TUPLE_DEFINE_MANIPULATOR
#undef STD_TUPLE_DEFINE_MANIPULATOR_FUNCTIONS
#undef FUSION_STRING_OF_STREAM
#undef FUSION_GET_CHAR_TYPE
#undef FUSION_GET_TRAITS_TYPE

}}

#endif

/* manip.hpp
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
*/