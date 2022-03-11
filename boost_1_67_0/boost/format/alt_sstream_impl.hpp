// ----------------------------------------------------------------------------
//  alt_sstream_impl.hpp : alternative stringstream, templates implementation 
// ----------------------------------------------------------------------------

//  Copyright Samuel Krempp 2003. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/format for library home page

// ----------------------------------------------------------------------------

#ifndef BOOST_SK_ALT_SSTREAM_IMPL_HPP
#define BOOST_SK_ALT_SSTREAM_IMPL_HPP

namespace boost {
    namespace io {
// --- Implementation  ------------------------------------------------------//

        template<class Ch, class Tr, class Alloc>
        void basic_altstringbuf<Ch, Tr, Alloc>:: 
        clear_buffer () {
            const Ch * p = pptr();
            const Ch * b = pbase();
            if(p != NULL && p != b) {
                seekpos(0, ::std::ios_base::out); 
            }
            p = gptr();
            b = eback();
            if(p != NULL && p != b) {
                seekpos(0, ::std::ios_base::in); 
            }
        }

        template<class Ch, class Tr, class Alloc>
        void basic_altstringbuf<Ch, Tr, Alloc>:: 
        str (const string_type& s) {
            size_type sz=s.size();
            if(sz != 0 && mode_ & (::std::ios_base::in | ::std::ios_base::out) ) {
#ifdef _RWSTD_NO_CLASS_PARTIAL_SPEC
                void *vd_ptr = alloc_.allocate(sz, is_allocated_? eback() : 0);
                Ch *new_ptr = static_cast<Ch *>(vd_ptr);
#else
                Ch *new_ptr = alloc_.allocate(sz, is_allocated_? eback() : 0);
#endif
                // if this didnt throw, we're safe, update the buffer
                dealloc();
                sz = s.copy(new_ptr, sz);
                putend_ = new_ptr + sz;
                if(mode_ & ::std::ios_base::in)
                    streambuf_t::setg(new_ptr, new_ptr, new_ptr + sz);
                if(mode_ & ::std::ios_base::out) {
                    streambuf_t::setp(new_ptr, new_ptr + sz);
                    if(mode_ & (::std::ios_base::app | ::std::ios_base::ate))
                        streambuf_t::pbump(static_cast<int>(sz));
                    if(gptr() == NULL)
                        streambuf_t::setg(new_ptr, NULL, new_ptr);
                }
                is_allocated_ = true;
            }
            else 
                dealloc();
        }
        template<class Ch, class Tr, class Alloc>
        Ch*   basic_altstringbuf<Ch, Tr, Alloc>:: 
        begin () const {
            if(mode_ & ::std::ios_base::out && pptr() != NULL)
                return pbase();
            else if(mode_ & ::std::ios_base::in && gptr() != NULL)
                return eback();
            return NULL;
        }

        template<class Ch, class Tr, class Alloc>
        typename std::basic_string<Ch,Tr,Alloc>::size_type
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        size () const { 
            if(mode_ & ::std::ios_base::out && pptr())
                return static_cast<size_type>(pend() - pbase());
            else if(mode_ & ::std::ios_base::in && gptr())
                return static_cast<size_type>(egptr() - eback());
            else 
                return 0;
        }

        template<class Ch, class Tr, class Alloc>
        typename std::basic_string<Ch,Tr,Alloc>::size_type
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        cur_size () const { 
            if(mode_ & ::std::ios_base::out && pptr())
                return static_cast<streamsize>( pptr() - pbase());
            else if(mode_ & ::std::ios_base::in && gptr())
                return static_cast<streamsize>( gptr() - eback());
            else 
                return 0;
        }

        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::pos_type  
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        seekoff (off_type off, ::std::ios_base::seekdir way, ::std::ios_base::openmode which) {
            if(pptr() != NULL && putend_ < pptr())
                putend_ = pptr();
            if(which & ::std::ios_base::in && gptr() != NULL) {
                // get area
                if(way == ::std::ios_base::end)
                    off += static_cast<off_type>(putend_ - gptr());
                else if(way == ::std::ios_base::beg)
                    off += static_cast<off_type>(eback() - gptr());
                else if(way != ::std::ios_base::cur || (which & ::std::ios_base::out) )
                    // (altering in&out is only supported if way is beg or end, not cur)
                    return pos_type(off_type(-1));
                if(eback() <= off+gptr() && off+gptr() <= putend_ ) {
                    // set gptr
                    streambuf_t::gbump(static_cast<int>(off));
                    if(which & ::std::ios_base::out && pptr() != NULL)
                        // update pptr to match gptr
                        streambuf_t::pbump(static_cast<int>(gptr()-pptr()));
                }
                else
                    off = off_type(-1);
            }
            else if(which & ::std::ios_base::out && pptr() != NULL) {
                // put area
                if(way == ::std::ios_base::end)
                    off += static_cast<off_type>(putend_ - pptr());
                else if(way == ::std::ios_base::beg)
                    off += static_cast<off_type>(pbase() - pptr());
                else if(way != ::std::ios_base::beg)
                    return pos_type(off_type(-1));                    
                if(pbase() <= off+pptr() && off+pptr() <= putend_)
                    // set pptr
                    streambuf_t::pbump(static_cast<int>(off)); 
                else
                    off = off_type(-1);
            }
            else // neither in nor out
                off = off_type(-1);
            return (pos_type(off));
        }
        //- end seekoff(..)

        
        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::pos_type 
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        seekpos (pos_type pos, ::std::ios_base::openmode which) {
            off_type off = off_type(pos); // operation guaranteed by fpos.operations table 127
            if(pptr() != NULL && putend_ < pptr())
                putend_ = pptr();
            if(off != off_type(-1)) {
                if(which & ::std::ios_base::in && gptr() != NULL) {
                    // get area
                    if(0 <= off && off <= putend_ - eback()) {
                        streambuf_t::gbump(static_cast<int>(eback() - gptr() + off));
                        if(which & ::std::ios_base::out && pptr() != NULL) {
                            // update pptr to match gptr
                            streambuf_t::pbump(static_cast<int>(gptr()-pptr()));
                        }
                    }
                    else
                        off = off_type(-1);
                }
                else if(which & ::std::ios_base::out && pptr() != NULL) {
                    // put area
                    if(0 <= off && off <= putend_ - eback())
                        streambuf_t::pbump(static_cast<int>(eback() - pptr() + off));
                    else
                        off = off_type(-1);
                }
                else // neither in nor out
                    off = off_type(-1);
                return (pos_type(off));
            }
            else {
                BOOST_ASSERT(0); // fpos.operations allows undefined-behaviour here
                return pos_type(off_type(-1));
            }
        }
        // -end seekpos(..)


        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::int_type
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        underflow () {
            if(gptr() == NULL) // no get area -> nothing to get.
                return (compat_traits_type::eof()); 
            else if(gptr() < egptr())  // ok, in buffer
                return (compat_traits_type::to_int_type(*gptr())); 
            else if(mode_ & ::std::ios_base::in && pptr() != NULL
                    && (gptr() < pptr() || gptr() < putend_) )
                {  // expand get area 
                    if(putend_ < pptr()) 
                        putend_ = pptr(); // remember pptr reached this far
                    streambuf_t::setg(eback(), gptr(), putend_);
                    return (compat_traits_type::to_int_type(*gptr()));
                }
            else // couldnt get anything. EOF.
                return (compat_traits_type::eof());
        }
        // -end underflow(..)


        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::int_type 
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        pbackfail (int_type meta) {
            if(gptr() != NULL  &&  (eback() < gptr()) 
               && (mode_ & (::std::ios_base::out)
                   || compat_traits_type::eq_int_type(compat_traits_type::eof(), meta)
                   || compat_traits_type::eq(compat_traits_type::to_char_type(meta), gptr()[-1]) ) ) { 
                streambuf_t::gbump(-1); // back one character
                if(!compat_traits_type::eq_int_type(compat_traits_type::eof(), meta))
                    //  put-back meta into get area
                    *gptr() = compat_traits_type::to_char_type(meta);
                return (compat_traits_type::not_eof(meta));
            }
            else
                return (compat_traits_type::eof());  // failed putback
        }
        // -end pbackfail(..)


        template<class Ch, class Tr, class Alloc>
        typename basic_altstringbuf<Ch, Tr, Alloc>::int_type 
        basic_altstringbuf<Ch, Tr, Alloc>:: 
        overflow (int_type meta) {
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4996)
#endif
            if(compat_traits_type::eq_int_type(compat_traits_type::eof(), meta))
                return compat_traits_type::not_eof(meta); // nothing to do
            else if(pptr() != NULL && pptr() < epptr()) {
                streambuf_t::sputc(compat_traits_type::to_char_type(meta));
                return meta;
            }
            else if(! (mode_ & ::std::ios_base::out)) 
                // no write position, and cant make one
                return compat_traits_type::eof(); 
            else { // make a write position available
                std::size_t prev_size = pptr() == NULL ? 0 : epptr() - eback();
                std::size_t new_size = prev_size;
                // exponential growth : size *= 1.5
                std::size_t add_size = new_size / 2;
                if(add_size < alloc_min)
                    add_size = alloc_min;
                Ch * newptr = NULL,  *oldptr = eback();

                // make sure adding add_size wont overflow size_t
                while (0 < add_size && ((std::numeric_limits<std::size_t>::max)()
                                        - add_size < new_size) )
                    add_size /= 2;
                if(0 < add_size) {
                    new_size += add_size;
#ifdef _RWSTD_NO_CLASS_PARTIAL_SPEC
                    void *vdptr = alloc_.allocate(new_size, is_allocated_? oldptr : 0);
                    newptr = static_cast<Ch *>(vdptr);
#else
                    newptr = alloc_.allocate(new_size, is_allocated_? oldptr : 0);
#endif
                }

                if(0 < prev_size)
                    compat_traits_type::copy(newptr, oldptr, prev_size);
                if(is_allocated_)
                    alloc_.deallocate(oldptr, prev_size);
                is_allocated_=true;

                if(prev_size == 0) { // first allocation
                    putend_ = newptr;
                    streambuf_t::setp(newptr, newptr + new_size);
                    if(mode_ & ::std::ios_base::in)
                        streambuf_t::setg(newptr, newptr, newptr + 1);
                    else
                        streambuf_t::setg(newptr, 0, newptr);
                }
                else { // update pointers
                    putend_ = putend_ - oldptr + newptr;
                    int pptr_count = static_cast<int>(pptr()-pbase());
                    int gptr_count = static_cast<int>(gptr()-eback());
                    streambuf_t::setp(pbase() - oldptr + newptr, newptr + new_size);
                    streambuf_t::pbump(pptr_count);
                    if(mode_ & ::std::ios_base::in)
                        streambuf_t::setg(newptr, newptr + gptr_count, pptr() + 1);
                    else
                        streambuf_t::setg(newptr, 0, newptr);
                }
                streambuf_t::sputc(compat_traits_type::to_char_type(meta));
                return meta;
            }
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
        }
        // -end overflow(..)

        template<class Ch, class Tr, class Alloc>
        void basic_altstringbuf<Ch, Tr, Alloc>:: dealloc() {
            if(is_allocated_)
                alloc_.deallocate(eback(), (pptr() != NULL ? epptr() : egptr()) - eback());
            is_allocated_ = false;
            streambuf_t::setg(0, 0, 0);
            streambuf_t::setp(0, 0);
            putend_ = NULL;
        }

    }// N.S. io
} // N.S. boost

#endif // include guard


/* alt_sstream_impl.hpp
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
*/