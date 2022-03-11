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