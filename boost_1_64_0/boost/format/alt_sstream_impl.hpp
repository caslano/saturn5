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
d9aL1XXIlGPnUUfBHne48JEtXONfwk6gNTdYcH1O0VJ+LrIeVLSZ7GLqBAt/2ctIMfvqeqmYnSUVs9cvZar05i6+ZQeTLba4lmOiwshtAh1ty9003NrkFK2mmocATt0NTPB9FAnXUFYXJStVO86yXqGshpBF0vTgqcUizkZOSk7Rq5Qfz/PHaW2V/FSxC0+BHhXPqfx20Dp+P6DIgsf7UCnxC6KWXDgZ0lk5bkoCwRWSy24xp+bPko+DZnmjqVK6zuP10BtXSkBCBuuWpGkz2fjqUOk/cGpV0NkL5wepOCArYqGYYKAsZp6BP1xtvp3bh1pRvgmUf4FOXNJMfAeAtPcr4pdMoLsJ9MjrFqBTn9ONvgbQgOmVU/QhNfCK19Vu84JuWRrzPfq62m1NWNZHlHUvZNGXVPm94v+N74ZL8cP9n6/jH3jynprM/3n/E9DaqRWY//Mu8BzW/7k+6TgJB7Y2ufBug49xD6agGWcmXP7OhNHw7YqyDvIkEKhC6VO0ONxUJX7phxqbVihNZlFd22anvFNyfmpovm4k0fs1Qe8o5/gk/BM30Y0Sd3BHoAv+JeVOh+5AmPQh3Rj1khlAbisk90ZlzQyKInHkMwGcX9o5wldm2c2vMoKsVC7aSFiB2AlGE+Ztff8Wvu5Il9YZbMQ2/IZ9HyRJxAbeKgpGqsjg/l+JFOC+p0bcxznI61diO0jQDuAysAB55L1lo78KHe8Y37OjLQBNK89LrzBC2GL7wDLQ2JwNUtyCofT1H30Fv/55+PXPll//9KfxAw1QNEwEneW2vRqbd32NiACuGEbdQnUZPA3P/dtwO52ivUwdUp9eC+fgq/Ses+Nx5rUvvqgmam+OiCw6eG1A+7KcBTTZA0BvDzuTeZkD1UKgZQqQG2ymH8d3oY83eCvJDKezy9SuTOTnYM10f4PXQpq+yk3Jii6guV062wq4Aq9z7yZ1iNTMLVITkqHdtpuRGVtU609x26Ge/6zVXb+RRJfucLLx35h7PZmJxx9aTTBRIV6TQAYyZC17XWRNjXHY2i2ZRaOyRASJg1U2K+JgttZ4E2GH133Yox138R6tgT26Af6jcuMShaA5Ep/oHL7ooD6gvDCgDsriNyjSqNg1jGLFRCswxa+vGY1/RVKuxlO2Klvj2KL62HHNAo1CileVxUlYxsKpf5yrN13eNLXp66t1H2AWHZsteq8L2p6Qy0qwvTFkvQeTOyrGgwVcCshm7Zv1LDSdecJOZ1PqpI2876RMm019RxE1PBfIsGr/uoqxxXcX8MuHXhQqemlUTtor1lkb+OaEwffKOxyfus1J5Ck7sDFiGIid4W44/w1TX2dDfXbWbx7/7N/W+E69baLfpdC/9cLpHxKmvilv47riLKhgqNSpx4YoyzOKSuXO6P/+Jev6KvL6yDeT4Zs117ix1Br19ZQQJW3Q4rEa96zJ+BoCaAwPAAU9s2ZuxIIW8V+Qfhn/ZQqP/wKStTH+S3pOUTkSkd0vxcIf/JjW/QDMslXBGeF8odBmnonc6kyEKzHeETQUJUfnaooHUuKIiFEBpnwLjFAKpGfDfNYB/kNPbVFYqkegq6l2RBAtpkg1yy0JE2q6WMZyDGfZDrslyYNrXlTa//j5oKnd6+JjDI3abKBANA3X3UTba3VzvAgcEeTlslR7CFr/Xiy+qHgRJnQbV+jo5PSlLEU7DAMAhSB2/OnryA/vfje3ks+qlVyylfqzQXE15Sr9mmUon6oP5TSRIZdQzHJhVtwfofZR+385a4suLXeCDcGG4XL9f/xRSCcP9pO1sG4PaTHUENFBFxf70qhHlKxvIUue5WcikjciI94sL58DjZgMK2OSWaeroioIzxM=
*/