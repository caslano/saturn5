// ----------------------------------------------------------------------------
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

#ifndef BOOST_PROPERTY_TREE_STREAM_TRANSLATOR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_STREAM_TRANSLATOR_HPP_INCLUDED

#include <boost/property_tree/ptree_fwd.hpp>

#include <boost/optional.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <sstream>
#include <string>
#include <locale>
#include <limits>

namespace boost { namespace property_tree
{

    template <typename Ch, typename Traits, typename E, typename Enabler = void>
    struct customize_stream
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, const E& e) {
            s << e;
        }
        static void extract(std::basic_istream<Ch, Traits>& s, E& e) {
            s >> e;
            if(!s.eof()) {
                s >> std::ws;
            }
        }
    };

    // No whitespace skipping for single characters.
    template <typename Ch, typename Traits>
    struct customize_stream<Ch, Traits, Ch, void>
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, Ch e) {
            s << e;
        }
        static void extract(std::basic_istream<Ch, Traits>& s, Ch& e) {
            s.unsetf(std::ios_base::skipws);
            s >> e;
        }
    };

    // Ugly workaround for numeric_traits that don't have members when not
    // specialized, e.g. MSVC.
    namespace detail
    {
        template <bool is_specialized>
        struct is_inexact_impl
        {
            template <typename T>
            struct test
            {
                typedef boost::false_type type;
            };
        };
        template <>
        struct is_inexact_impl<true>
        {
            template <typename T>
            struct test
            {
              typedef boost::integral_constant<bool,
                  !std::numeric_limits<T>::is_exact> type;
            };
        };

        template <typename F>
        struct is_inexact
        {
            typedef typename boost::decay<F>::type decayed;
            typedef typename is_inexact_impl<
                std::numeric_limits<decayed>::is_specialized
            >::BOOST_NESTED_TEMPLATE test<decayed>::type type;
            static const bool value = type::value;
        };
    }

    template <typename Ch, typename Traits, typename F>
    struct customize_stream<Ch, Traits, F,
        typename boost::enable_if< detail::is_inexact<F> >::type
    >
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, const F& e) {
#ifndef BOOST_NO_CXX11_NUMERIC_LIMITS 
            s.precision(std::numeric_limits<F>::max_digits10); 
#else 
            s.precision(std::numeric_limits<F>::digits10 + 2); 
#endif 
            s << e;
        }
        static void extract(std::basic_istream<Ch, Traits>& s, F& e) {
            s >> e;
            if(!s.eof()) {
                s >> std::ws;
            }
        }
    };

    template <typename Ch, typename Traits>
    struct customize_stream<Ch, Traits, bool, void>
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, bool e) {
            s.setf(std::ios_base::boolalpha);
            s << e;
        }
        static void extract(std::basic_istream<Ch, Traits>& s, bool& e) {
            s >> e;
            if(s.fail()) {
                // Try again in word form.
                s.clear();
                s.setf(std::ios_base::boolalpha);
                s >> e;
            }
            if(!s.eof()) {
                s >> std::ws;
            }
        }
    };

    template <typename Ch, typename Traits>
    struct customize_stream<Ch, Traits, signed char, void>
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, signed char e) {
            s << (int)e;
        }
        static void extract(std::basic_istream<Ch, Traits>& s, signed char& e) {
            int i;
            s >> i;
            // out of range?
            if(i > (std::numeric_limits<signed char>::max)() ||
                i < (std::numeric_limits<signed char>::min)())
            {
                s.clear(); // guarantees eof to be unset
                e = 0;
                s.setstate(std::ios_base::badbit);
                return;
            }
            e = (signed char)i;
            if(!s.eof()) {
                s >> std::ws;
            }
        }
    };

    template <typename Ch, typename Traits>
    struct customize_stream<Ch, Traits, unsigned char, void>
    {
        static void insert(std::basic_ostream<Ch, Traits>& s, unsigned char e) {
            s << (unsigned)e;
        }
        static void extract(std::basic_istream<Ch,Traits>& s, unsigned char& e){
            unsigned i;
            s >> i;
            // out of range?
            if(i > (std::numeric_limits<unsigned char>::max)()) {
                s.clear(); // guarantees eof to be unset
                e = 0;
                s.setstate(std::ios_base::badbit);
                return;
            }
            e = (unsigned char)i;
            if(!s.eof()) {
                s >> std::ws;
            }
        }
    };

    /// Implementation of Translator that uses the stream overloads.
    template <typename Ch, typename Traits, typename Alloc, typename E>
    class stream_translator
    {
        typedef customize_stream<Ch, Traits, E> customized;
    public:
        typedef std::basic_string<Ch, Traits, Alloc> internal_type;
        typedef E external_type;

        explicit stream_translator(std::locale loc = std::locale())
            : m_loc(loc)
        {}

        boost::optional<E> get_value(const internal_type &v) {
            std::basic_istringstream<Ch, Traits, Alloc> iss(v);
            iss.imbue(m_loc);
            E e;
            customized::extract(iss, e);
            if(iss.fail() || iss.bad() || iss.get() != Traits::eof()) {
                return boost::optional<E>();
            }
            return e;
        }
        boost::optional<internal_type> put_value(const E &v) {
            std::basic_ostringstream<Ch, Traits, Alloc> oss;
            oss.imbue(m_loc);
            customized::insert(oss, v);
            if(oss) {
                return oss.str();
            }
            return boost::optional<internal_type>();
        }

    private:
        std::locale m_loc;
    };

    // This is the default translator when basic_string is the internal type.
    // Unless the external type is also basic_string, in which case
    // id_translator takes over.
    template <typename Ch, typename Traits, typename Alloc, typename E>
    struct translator_between<std::basic_string<Ch, Traits, Alloc>, E>
    {
        typedef stream_translator<Ch, Traits, Alloc, E> type;
    };

}}

#endif

/* stream_translator.hpp
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
*/