// ----------------------------------------------------------------------------
//  format_class.hpp :  class interface
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_FORMAT_CLASS_HPP
#define BOOST_FORMAT_CLASS_HPP


#include <vector>
#include <string>

#include <boost/optional.hpp> // to store locale when needed

#include <boost/format/format_fwd.hpp>
#include <boost/format/internals_fwd.hpp>
#include <boost/format/internals.hpp>
#include <boost/format/alt_sstream.hpp>

namespace boost {

    template<class Ch, class Tr, class Alloc>
    class basic_format 
    {
        typedef typename io::CompatTraits<Tr>::compatible_type compat_traits;  
    public:
        typedef Ch  CharT;   // borland fails in operator% if we use Ch and Tr directly
        typedef std::basic_string<Ch, Tr, Alloc>              string_type;
        typedef typename string_type::size_type               size_type;
        typedef io::detail::format_item<Ch, Tr, Alloc>        format_item_t;
        typedef io::basic_altstringbuf<Ch, Tr, Alloc>         internal_streambuf_t;
        

        explicit basic_format(const Ch* str=NULL);
        explicit basic_format(const string_type& s);
        basic_format(const basic_format& x);
        basic_format& operator= (const basic_format& x);
        void swap(basic_format& x);

#if !defined(BOOST_NO_STD_LOCALE)
        explicit basic_format(const Ch* str, const std::locale & loc);
        explicit basic_format(const string_type& s, const std::locale & loc);
#endif
        io::detail::locale_t  getloc() const;

        basic_format& clear();       // empty all converted string buffers (except bound items)
        basic_format& clear_binds(); // unbind all bound items, and call clear()
        basic_format& parse(const string_type&); // resets buffers and parse a new format string

        // ** formatted result ** //
        size_type   size() const;    // sum of the current string pieces sizes
        string_type str()  const;    // final string 

        // ** arguments passing ** //
        template<class T>  
        basic_format&   operator%(const T& x)
            { return io::detail::feed<CharT, Tr, Alloc, const T&>(*this,x); }

#ifndef BOOST_NO_OVERLOAD_FOR_NON_CONST
        template<class T>  basic_format&   operator%(T& x) 
            { return io::detail::feed<CharT, Tr, Alloc, T&>(*this,x); }
#endif

        template<class T>
        basic_format& operator%(volatile const T& x)
            { /* make a non-volatile copy */ const T v(x);
              /* pass the copy along      */ return io::detail::feed<CharT, Tr, Alloc, const T&>(*this, v); }

#ifndef BOOST_NO_OVERLOAD_FOR_NON_CONST
        template<class T>
        basic_format& operator%(volatile T& x)
            { /* make a non-volatile copy */ T v(x);
              /* pass the copy along      */ return io::detail::feed<CharT, Tr, Alloc, T&>(*this, v); }
#endif

#if defined(__GNUC__)
        // GCC can't handle anonymous enums without some help
        // ** arguments passing ** //
        basic_format&   operator%(const int& x)
            { return io::detail::feed<CharT, Tr, Alloc, const int&>(*this,x); }

#ifndef BOOST_NO_OVERLOAD_FOR_NON_CONST
        basic_format&   operator%(int& x)
            { return io::detail::feed<CharT, Tr, Alloc, int&>(*this,x); }
#endif
#endif

        // The total number of arguments expected to be passed to the format objectt
        int expected_args() const
            { return num_args_; }
        // The number of arguments currently bound (see bind_arg(..) )
        int bound_args() const;
        // The number of arguments currently fed to the format object
        int fed_args() const;
        // The index (1-based) of the current argument (i.e. next to be formatted)
        int cur_arg() const;
        // The number of arguments still required to be fed
        int remaining_args() const; // same as expected_args() - bound_args() - fed_args()


        // ** object modifying **//
        template<class T>
        basic_format&  bind_arg(int argN, const T& val) 
            { return io::detail::bind_arg_body(*this, argN, val); }
        basic_format&  clear_bind(int argN);
        template<class T> 
        basic_format&  modify_item(int itemN, T manipulator) 
            { return io::detail::modify_item_body<Ch,Tr, Alloc, T> (*this, itemN, manipulator);}

        // Choosing which errors will throw exceptions :
        unsigned char exceptions() const;
        unsigned char exceptions(unsigned char newexcept);

#if !defined( BOOST_NO_MEMBER_TEMPLATE_FRIENDS )  \
    && !BOOST_WORKAROUND(BOOST_BORLANDC, <= 0x570) \
    && !BOOST_WORKAROUND( _CRAYC, != 0) \
    && !BOOST_WORKAROUND(__DECCXX_VER, BOOST_TESTED_AT(60590042))
        // use friend templates and private members only if supported

#ifndef  BOOST_NO_TEMPLATE_STD_STREAM
        template<class Ch2, class Tr2, class Alloc2>
        friend std::basic_ostream<Ch2, Tr2> & 
        operator<<( std::basic_ostream<Ch2, Tr2> & ,
                    const basic_format<Ch2, Tr2, Alloc2>& );
#else
        template<class Ch2, class Tr2, class Alloc2>
        friend std::ostream & 
        operator<<( std::ostream & ,
                    const basic_format<Ch2, Tr2, Alloc2>& );
#endif

        template<class Ch2, class Tr2, class Alloc2, class T>  
        friend basic_format<Ch2, Tr2, Alloc2>&  
        io::detail::feed_impl (basic_format<Ch2, Tr2, Alloc2>&, T);

        template<class Ch2, class Tr2, class Alloc2, class T>  friend   
        void io::detail::distribute (basic_format<Ch2, Tr2, Alloc2>&, T);
        
        template<class Ch2, class Tr2, class Alloc2, class T>  friend
        basic_format<Ch2, Tr2, Alloc2>& 
        io::detail::modify_item_body (basic_format<Ch2, Tr2, Alloc2>&, int, T);
        
        template<class Ch2, class Tr2, class Alloc2, class T> friend
        basic_format<Ch2, Tr2, Alloc2>&  
        io::detail::bind_arg_body (basic_format<Ch2, Tr2, Alloc2>&, int, const T&);

    private:
#endif
        typedef io::detail::stream_format_state<Ch, Tr>  stream_format_state;
        // flag bits, used for style_
        enum style_values  { ordered = 1, // set only if all directives are  positional
                             special_needs = 4 };     

        void make_or_reuse_data(std::size_t nbitems);// used for (re-)initialisation

        // member data --------------------------------------------//
        std::vector<format_item_t>  items_; // each '%..' directive leads to a format_item
        std::vector<bool> bound_; // stores which arguments were bound. size() == 0 || num_args

        int              style_; // style of format-string :  positional or not, etc
        int             cur_arg_; // keep track of wich argument is current
        int            num_args_; // number of expected arguments
        mutable bool     dumped_; // true only after call to str() or <<
        string_type      prefix_; // piece of string to insert before first item
        unsigned char exceptions_;
        internal_streambuf_t   buf_; // the internal stream buffer.
        boost::optional<io::detail::locale_t>     loc_;
    }; // class basic_format

} // namespace boost


#endif // BOOST_FORMAT_CLASS_HPP

/* format_class.hpp
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
*/