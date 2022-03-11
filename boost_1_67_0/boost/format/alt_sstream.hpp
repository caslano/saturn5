// ----------------------------------------------------------------------------
//  alt_sstream.hpp : alternative stringstream 
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------



#ifndef BOOST_SK_ALT_SSTREAM_HPP
#define BOOST_SK_ALT_SSTREAM_HPP

#include <string>
#include <boost/format/detail/compat_workarounds.hpp>
#include <boost/utility/base_from_member.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/config.hpp>
#include <boost/assert.hpp>

namespace boost {
    namespace io {

        template<class Ch, class Tr=::std::char_traits<Ch>, 
                 class Alloc=::std::allocator<Ch> >
        class basic_altstringbuf;

        template<class Ch, class Tr =::std::char_traits<Ch>, 
                 class Alloc=::std::allocator<Ch> >
        class basic_oaltstringstream;


        template<class Ch, class Tr, class Alloc>
        class basic_altstringbuf 
            : public ::std::basic_streambuf<Ch, Tr>
        {
            typedef ::std::basic_streambuf<Ch, Tr>  streambuf_t;
            typedef typename CompatAlloc<Alloc>::compatible_type compat_allocator_type;
            typedef typename CompatTraits<Tr>::compatible_type   compat_traits_type;
        public:
            typedef Ch     char_type;
            typedef Tr     traits_type;
            typedef typename compat_traits_type::int_type     int_type;
            typedef typename compat_traits_type::pos_type     pos_type;
            typedef typename compat_traits_type::off_type     off_type;
            typedef Alloc                     allocator_type;
            typedef ::std::basic_string<Ch, Tr, Alloc> string_type;
            typedef typename string_type::size_type    size_type;

            typedef ::std::streamsize streamsize;


            explicit basic_altstringbuf(std::ios_base::openmode mode
                                        = std::ios_base::in | std::ios_base::out)
                : putend_(NULL), is_allocated_(false), mode_(mode) 
                {}
            explicit basic_altstringbuf(const string_type& s,
                                        ::std::ios_base::openmode mode
                                        = ::std::ios_base::in | ::std::ios_base::out)
                : putend_(NULL), is_allocated_(false), mode_(mode) 
                { dealloc(); str(s); }
            virtual ~basic_altstringbuf() BOOST_NOEXCEPT_OR_NOTHROW
                { dealloc(); }
            using streambuf_t::pbase;
            using streambuf_t::pptr;
            using streambuf_t::epptr;
            using streambuf_t::eback;
            using streambuf_t::gptr;
            using streambuf_t::egptr;
    
            void clear_buffer();
            void str(const string_type& s);

            // 0-copy access :
            Ch * begin() const; 
            size_type size() const;
            size_type cur_size() const; // stop at current pointer
            Ch * pend() const // the highest position reached by pptr() since creation
                { return ((putend_ < pptr()) ? pptr() : putend_); }
            size_type pcount() const 
                { return static_cast<size_type>( pptr() - pbase()) ;}

            // copy buffer to string :
            string_type str() const 
                { return string_type(begin(), size()); }
            string_type cur_str() const 
                { return string_type(begin(), cur_size()); }
        protected:
            explicit basic_altstringbuf (basic_altstringbuf * s,
                                         ::std::ios_base::openmode mode 
                                         = ::std::ios_base::in | ::std::ios_base::out)
                : putend_(NULL), is_allocated_(false), mode_(mode) 
                { dealloc(); str(s); }

            virtual pos_type seekoff(off_type off, ::std::ios_base::seekdir way, 
                                     ::std::ios_base::openmode which 
                                     = ::std::ios_base::in | ::std::ios_base::out);
            virtual pos_type seekpos (pos_type pos, 
                                      ::std::ios_base::openmode which 
                                      = ::std::ios_base::in | ::std::ios_base::out);
            virtual int_type underflow();
            virtual int_type pbackfail(int_type meta = compat_traits_type::eof());
            virtual int_type overflow(int_type meta = compat_traits_type::eof());
            void dealloc();
        private:
            enum { alloc_min = 256}; // minimum size of allocations

            Ch *putend_;  // remembers (over seeks) the highest value of pptr()
            bool is_allocated_;
            ::std::ios_base::openmode mode_;
            compat_allocator_type alloc_;  // the allocator object
        };


// ---   class basic_oaltstringstream ----------------------------------------
        template <class Ch, class Tr, class Alloc>
        class basic_oaltstringstream 
            : private base_from_member< shared_ptr< basic_altstringbuf< Ch, Tr, Alloc> > >,
              public ::std::basic_ostream<Ch, Tr>
        {
            class No_Op { 
                // used as no-op deleter for (not-owner) shared_pointers
            public: 
                template<class T>
                const T & operator()(const T & arg) { return arg; }
            };
            typedef ::std::basic_ostream<Ch, Tr> stream_t;
            typedef boost::base_from_member<boost::shared_ptr<
                basic_altstringbuf<Ch,Tr, Alloc> > > 
                pbase_type;
            typedef ::std::basic_string<Ch, Tr, Alloc>  string_type;
            typedef typename string_type::size_type     size_type;
            typedef basic_altstringbuf<Ch, Tr, Alloc>   stringbuf_t;
        public:
            typedef Alloc  allocator_type;
            basic_oaltstringstream() 
                : pbase_type(new stringbuf_t), stream_t(pbase_type::member.get())
                { }
            basic_oaltstringstream(::boost::shared_ptr<stringbuf_t> buf) 
                : pbase_type(buf), stream_t(pbase_type::member.get())
                { }
            basic_oaltstringstream(stringbuf_t * buf) 
                : pbase_type(buf, No_Op() ), stream_t(pbase_type::member.get())
                { }
            stringbuf_t * rdbuf() const 
                { return pbase_type::member.get(); }
            void clear_buffer() 
                { rdbuf()->clear_buffer(); }

            // 0-copy access :
            Ch * begin() const 
                { return rdbuf()->begin(); }
            size_type size() const 
                { return rdbuf()->size(); }
            size_type cur_size() const // stops at current position
                { return rdbuf()->cur_size(); }

            // copy buffer to string :
            string_type str()     const   // [pbase, epptr[
                { return rdbuf()->str(); } 
            string_type cur_str() const   // [pbase, pptr[
                { return rdbuf()->cur_str(); }
            void str(const string_type& s) 
                { rdbuf()->str(s); }
        };

    } // N.S. io
} // N.S. boost

#include <boost/format/alt_sstream_impl.hpp>

#endif // include guard


/* alt_sstream.hpp
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
*/