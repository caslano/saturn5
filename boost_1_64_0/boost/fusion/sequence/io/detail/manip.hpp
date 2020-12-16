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
hP3/r/S61N0Vd3kD3Xmf8DtdpuZYu9V1JuovFweG3k5Zti74vZmGzm1tt7fVmvdeeD9PMOiwBucOSj+/fA5MBsbO3f8MoYOMWJm+4z6k2btwszwSWSS44a4ZQEj/J6EjP9Z/dX9Hp28fv+1+p/mae+GOPtYm9WvbL2rUb9YG09L99kO7AILx2ufoLNK99rlsaZPbB+cPxJH2wfs7pONQR974Fi7NT/tfSN8ejg0zse24ZUcHBcDWkJz/j/bGQVzWvBbiZttXT9o3/Fbn5V/1WXvQAWCa84NxE4fTkn3rdXmrF88gUUEiZMbQDaLnN3JwvHsb5fKWLK9jqeoqaR0kD4lHw9Wws2Pb6vmjzXlWRrJomc6v7TaRSOHBjPZta7ZpJl8s89SYlrkqcxHGsjQOnfXP2RdpN6VNnC6q573pr9Ouj4+qSJMsli1nzyf5DvpgJ/kJxtMqT6OENffZxmOiDSw61ynLg45/occfKRGU0Pt7JXC857vyDOEvWCbiKspy1kZwfU5jz7wFyUAwUR1wF2qCCnXUw++6aSjGZcVFoIRJY3tzE5iWt57TXTasYCxaknfJZJwEZSAzn3EezAuMZ9jx2ou7hLp0LpN0JDQ8j4ooK/dKB6qxs955vnFiulyj9ajjXBVhErvJgLCurxvG+S7/67166A6sC1H5jJPrgbKwTX3Dc54HWVqVxquf7xW35X+x6GSB8EuW5xnnWR4ZflOSs2vPMeWA0UscfaNMkHQyFgVcqThL2MqF0TGTP5wyn7O103r1hES7ywiUq91eGnGapHnKdRrPv7lpvImkkbIqSkIpZMj0FDA5DRwfOAeRNDiral5FAgbY+bUt3SSbEAka/kWi14huDnJ5I85UVWlHtCUDJ1HD5yyvTwi3bA5R0D+ur+S/TbtyFaZBntfccdfd9g/6pO34ju7Q+5w6Saq6FIYP5zLkO97JgctXs1LVKiukk5+9B0LZS3doW3PtaEsEsWVCr97rsDnZNrK3hn4Qd3p3anGaVRWvLb9WmcDvCs33IuHLmA65XYZBZvma68T5ZsEfwlzUuwN8Wy/fXIiiSkMsN3ZJy4Y+vS8TPsEKHZScl4XPN483tcT3ea+9alh0q6ISDv947Bcb15l/En7OYpWLoKp77OQCE2X68AsorwjSLE8V5t3yYUeR9now4Q2g3FxoB1aWF+7H19Y7qbp/lyd7Qb+8WahklFs+fZVLRBnb6gzhTVjM44KXScDWnn9hZMYxJAONNGxjNT+f+p/eJfwxi7TjfBnHDCdSMskS3ks9XlGEWZiUJVtf3mv4I++zPz+gvj0DWRVBJFi3gPhrG/K+u5dvXhRVkMdZ4zO+1QDp2OHgqtw66Q7xfRtdk5OkLAQvWevV/+wQJm+osVngYQM1to5M5zEWHUlDsDTmUZhnAdsgywjEoNTz2Mhr86kX0v7mteKSZ3V7u693T5t6dBAP3KJbx54xQ3xqiTgL6zhUbHMEu0knxDxOnGZB2l5dG7vrISmDYFmlyjyCfseh2eiqOg/1no/3hV4dVCTqPFatz3y/DtRfm8tbslBC+xWZYCN0r47e+dDXefrdgcuTBXmYJHXBnj+BB2NLkDJWrIqiolQqZc3ijA029lqst2a/lqSTsyQsUh7wkJGpYGKDBRgXgqRRsqrMwjKJ6l4a5nbyRV0y3tx4laSTMBlF2hNj3FinPBIS2FxfP7sM5dCBCuDfnZ0FrrvVFIl1r0M+6veiJmb+eOMYtMzZ5w7P6ZG7AuOneWzX7XKdeDkv7Me7EbDuqgR8qjdm444/dtc3+fyjOn5XjhUroqyAvgktO123Rzg/71K5S4pQ8FqklvHC8vh5k+fKBxNewRQM/bA=
*/