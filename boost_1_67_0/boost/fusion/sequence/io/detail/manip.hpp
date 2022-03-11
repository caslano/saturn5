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